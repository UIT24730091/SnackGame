#include <iostream>
#include <windows.h> // Cho gotoxy, Sleep, SetConsoleCursorPosition, GetStdHandle
#include <cstdlib>   // Cho system("cls"), rand, srand
#include <conio.h>   // Cho kbhit, getch
#include <ctime>     // Cho time() để khởi tạo seed cho rand

using namespace std;

// Hàm di chuyển con trỏ console đến vị trí (column, line)
void gotoxy(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );
}

// Cấu trúc để lưu trữ tọa độ điểm (x, y)
struct Point {
    int x, y;
};

// --- Lớp Snake ---
class Snake {
public:
    Point body[100];  // Mảng lưu trữ tọa độ các đốt của rắn (kích thước tối đa 100)
    int length;       // Độ dài hiện tại của rắn
    int direction;    // Hướng di chuyển hiện tại (0: Phải, 1: Xuống, 2: Trái, 3: Lên)
    int prevDirection;// Hướng di chuyển trước đó (để dùng cho Turn Prevention)

    // Hàm khởi tạo (Constructor)
    Snake() {
        length = 3;
        body[0] = {10, 10};
        body[1] = {11, 10};
        body[2] = {12, 10};
        direction = 2;     // Bắt đầu đi sang Trái
        prevDirection = 2; // Hướng trước đó cũng là Trái
    }

    // Phương thức vẽ rắn
    void Draw() {
        for (int i = 0; i < length; ++i) {
            gotoxy(body[i].x, body[i].y);
            if (i == 0) {
                cout << "O"; // Đầu rắn
            } else {
                cout << "o"; // Thân rắn
            }
        }
    }

    // Phương thức di chuyển rắn
    void Move() {
        // 1. Cập nhật vị trí các đốt thân (từ đuôi lên gần đầu)
        for (int i = length - 1; i > 0; --i) {
             body[i] = body[i - 1];
        }

        // 2. Cập nhật vị trí đầu rắn dựa vào direction hiện tại
        Point head = body[0]; // Lấy vị trí đầu hiện tại (trước khi di chuyển)
        switch (direction) {
            case 0: head.x++; break; // Phải
            case 1: head.y++; break; // Xuống
            case 2: head.x--; break; // Trái
            case 3: head.y--; break; // Lên
        }
        body[0] = head; // Cập nhật vị trí mới cho đầu rắn

        // 3. QUAN TRỌNG: Cập nhật prevDirection SAU KHI đã xác định hướng di chuyển cho bước này
        //    Nó sẽ lưu lại hướng vừa đi (direction) để dùng cho lần kiểm tra input tiếp theo
        prevDirection = direction;
    }

    // Phương thức tăng độ dài rắn khi ăn mồi
    void Grow() {
        if (length < 100) {
            length++;
            // Đốt mới sẽ tự động được đặt đúng vị trí ở lần gọi Move() tiếp theo
        }
    }

    // Phương thức kiểm tra va chạm (với tường hoặc với thân)
    bool CheckCollision(int boardWidth, int boardHeight) {
        Point head = body[0];
        // 1. Kiểm tra va chạm với tường
        if (head.x <= 0 || head.x >= boardWidth - 1 || head.y <= 0 || head.y >= boardHeight - 1) {
            return true;
        }
        // 2. Kiểm tra va chạm với thân
        for (int i = 1; i < length; ++i) {
            if (head.x == body[i].x && head.y == body[i].y) {
                return true;
            }
        }
        return false;
    }

    // --- ĐÂY LÀ CODE CHO ISSUE Turn Prevention ---
    // Phương thức thay đổi hướng đi, có kiểm tra ngăn quay đầu 180 độ
    void ChangeDirection(int newDirection) {
        // Chỉ cập nhật 'direction' nếu hướng mới không phải là hướng ngược lại của 'prevDirection'

        // Muốn đi Phải (0) và hướng trước đó KHÔNG PHẢI là Trái (2)
        if (newDirection == 0 && prevDirection != 2) {
            direction = newDirection;
        }
        // Muốn đi Xuống (1) và hướng trước đó KHÔNG PHẢI là Lên (3)
        else if (newDirection == 1 && prevDirection != 3) {
            direction = newDirection;
        }
        // Muốn đi Trái (2) và hướng trước đó KHÔNG PHẢI là Phải (0)
        else if (newDirection == 2 && prevDirection != 0) {
            direction = newDirection;
        }
        // Muốn đi Lên (3) và hướng trước đó KHÔNG PHẢI là Xuống (1)
        else if (newDirection == 3 && prevDirection != 1) {
            direction = newDirection;
        }
        // Nếu người chơi nhấn phím quay đầu, 'direction' sẽ không thay đổi.
    }
    // --- KẾT THÚC CODE CHO ISSUE Turn Prevention ---

}; // --- Kết thúc lớp Snake ---


// --- Hàm vẽ khung trò chơi ---
void DrawBoard(int width, int height) {
    for (int i = 0; i < width; ++i) {
        gotoxy(i, 0); cout << "=";
        gotoxy(i, height - 1); cout << "=";
    }
    for (int i = 0; i < height; ++i) {
        gotoxy(0, i); cout << "|";
        gotoxy(width - 1, i); cout << "|";
    }
    gotoxy(0, 0); cout << "+";
    gotoxy(width - 1, 0); cout << "+";
    gotoxy(0, height - 1); cout << "+";
    gotoxy(width - 1, height - 1); cout << "+";
}

// --- Hàm tạo thức ăn cho rắn ---
Point GenerateFood(int width, int height, const Snake& snake) {
    Point food;
    bool onSnake;
    do {
        food.x = rand() % (width - 2) + 1;
        food.y = rand() % (height - 2) + 1;
        onSnake = false;
        for (int i = 0; i < snake.length; ++i) {
            if (food.x == snake.body[i].x && food.y == snake.body[i].y) {
                onSnake = true;
                break;
            }
        }
    } while (onSnake);
    return food;
}

// --- Hàm vẽ thức ăn ---
void DrawFood(const Point& food) {
    gotoxy(food.x, food.y);
    cout << "*";
}

// --- Hàm chính của chương trình ---
int main() {
    srand(time(0));

    const int gameWidth = 40;
    const int gameHeight = 20;
    int score = 0;
    bool gameOver = false;
    int gameSpeed = 200;

    Snake mySnake;
    Point food = GenerateFood(gameWidth, gameHeight, mySnake);

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);

    while (!gameOver) {
        // 1. Xử lý input từ người dùng
        if (kbhit()) {
            char key = getch();
            // Gọi ChangeDirection thay vì gán trực tiếp direction
            // Logic kiểm tra quay đầu đã nằm trong ChangeDirection
            switch (key) {
                case 'a': case 'A': case 75: // Trái
                    mySnake.ChangeDirection(2); // <--- Gọi hàm đã sửa
                    break;
                case 'd': case 'D': case 77: // Phải
                    mySnake.ChangeDirection(0); // <--- Gọi hàm đã sửa
                    break;
                case 'w': case 'W': case 72: // Lên
                    mySnake.ChangeDirection(3); // <--- Gọi hàm đã sửa
                    break;
                case 's': case 'S': case 80: // Xuống
                    mySnake.ChangeDirection(1); // <--- Gọi hàm đã sửa
                    break;
                case 27: // Esc
                    gameOver = true;
                    break;
            }
        }

        // 2. Cập nhật trạng thái game
        if (!gameOver) {
            mySnake.Move(); // Di chuyển rắn (bao gồm cập nhật prevDirection bên trong)

            // Kiểm tra ăn mồi
            Point head = mySnake.body[0];
            if (head.x == food.x && head.y == food.y) {
                mySnake.Grow();
                score += 10;
                food = GenerateFood(gameWidth, gameHeight, mySnake);
                // if (gameSpeed > 50) gameSpeed -= 5; // Tùy chọn tăng tốc độ
            }

            // Kiểm tra va chạm
            if (mySnake.CheckCollision(gameWidth, gameHeight)) {
                 gameOver = true;
            }
        }

        // 3. Vẽ lại màn hình game
        system("cls");
        DrawBoard(gameWidth, gameHeight);
        mySnake.Draw();
        DrawFood(food);
        gotoxy(gameWidth + 2, 2);
        cout << "Score: " << score;

        // 4. Tạm dừng
        Sleep(gameSpeed);

    } // --- Kết thúc vòng lặp game ---

    // --- Xử lý khi Game Over ---
    system("cls");
    gotoxy(gameWidth / 2 - 5, gameHeight / 2);
    cout << "GAME OVER!";
    gotoxy(gameWidth / 2 - 8, gameHeight / 2 + 1);
    cout << "Your Score: " << score;
    gotoxy(0, gameHeight);

    cursorInfo.bVisible = true; // Hiện lại con trỏ
    SetConsoleCursorInfo(out, &cursorInfo);

    return 0;
}
// -------Hàm sửa đổi định dạng lớp Snake và thêm biến director và predirector------
// Lớp Snake
class Snake
{
public:
    Point body[100];
    int length;
    int direction;       // hướng hiện tại
    int prevDirection;   // hướng trước đó

//-----------Hàm khởi tạo (constructor) của lớp Snake---------
Snake()
{
    length = 3;
    direction = 0;        // 0 - sang phải
    prevDirection = 0;    // cùng hướng với direction
    body[0].x = 10;
    body[0].y = 10;
    body[1].x = 9;
    body[1].y = 10;
    body[2].x = 8;
    body[2].y = 10;
}}
//End

//----Hàm di chuyển-----
void Move()
{
    // Di chuyển thân: mỗi đốt đi theo vị trí đốt trước
    for (int i = length - 1; i > 0; i--)
    {
        body[i] = body[i - 1];
    }

    // Di chuyển đầu: thay đổi tọa độ theo hướng hiện tại
    if (direction == 0) body[0].x = body[0].x + 1;  // Sang phải
    if (direction == 1) body[0].y = body[0].y + 1;  // Xuống
    if (direction == 2) body[0].x = body[0].x - 1;  // Trái
    if (direction == 3) body[0].y = body[0].y - 1;  // Lên

    // Cập nhật hướng trước
    prevDirection = direction;
}
//End

//--------Hàm Move Call In Main----------

while (!gameOver)
{
//----------Hàm Handle keyboard input------------
 // 1. Xử lý phím người chơi
if (_kbhit()) // kiểm tra nếu có phím được nhấn
{
    input = _getch(); // đọc phím nhấn

    if (input == 'a' && snake.prevDirection != 0) snake.direction = 2; // trái (không cho quay ngược phải)
    if (input == 'w' && snake.prevDirection != 1) snake.direction = 3; // lên (không cho quay ngược xuống)
    if (input == 'd' && snake.prevDirection != 2) snake.direction = 0; // phải (không cho quay ngược trái)
    if (input == 's' && snake.prevDirection != 3) snake.direction = 1; // xuống (không cho quay ngược lên)
}
// 2. Xóa màn hình & vẽ lại trạng thái
    system("cls");
    DrawBoard(gameWidth, gameHeight);

    gotoxy(food.x, food.y);
    cout << "*";
    snake.Draw();

    // 3. Cập nhật vị trí rắn sau khi đã xử lý input và vẽ
    snake.Move();
 // 4. Kiểm tra ăn thức ăn
    if (snake.body[0].x == food.x && snake.body[0].y == food.y)
    {
        snake.EatFood();
        score += 10;
        food = GenerateFood(gameWidth, gameHeight, snake);
    }

    // 5. Kiểm tra va chạm
    if (snake.CheckCollision(gameWidth, gameHeight))
    {
        gameOver = true;
    }

    // 6. Hiển thị điểm số
    gotoxy(gameWidth / 2 - 5, gameHeight + 1);
    cout << "Score: " << score;
 // 7. Kết thúc hoặc delay khung hình
    if (gameOver)
    {
        gotoxy(gameWidth / 2 - 8, gameHeight / 2);
        cout << "Game Over! Score: " << score << endl;
        gotoxy(gameWidth / 2 - 12, gameHeight / 2 + 1);
        _getch();
    }
    else
    {
        Sleep(gameSpeed);
    }
}
// -----------End-----------
