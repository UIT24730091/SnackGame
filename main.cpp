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
    int prevDirection;// Hướng di chuyển trước đó (để tránh quay đầu 180 độ)

    // Hàm khởi tạo (Constructor) - Được gọi khi tạo đối tượng Snake
    Snake() {
        // Khởi tạo giá trị ban đầu cho rắn
        length = 3;          // Rắn bắt đầu với 3 đốt
        body[0] = {10, 10};  // Đầu rắn ở vị trí (10, 10)
        body[1] = {11, 10};  // Đốt thứ 2
        body[2] = {12, 10};  // Đốt thứ 3 (đuôi)
        direction = 2;       // Bắt đầu di chuyển sang Trái (2)
        prevDirection = 2;   // Hướng trước đó cũng là Trái
    }

    // Phương thức vẽ rắn lên màn hình console
    // --- ĐÂY LÀ CODE CHO ISSUE Snake::Draw ---
    void Draw() {
        // Lặp qua từng đốt của con rắn
        for (int i = 0; i < length; ++i) {
            // Di chuyển con trỏ đến vị trí của đốt thứ i
            gotoxy(body[i].x, body[i].y);
            // In ra ký tự đại diện cho đốt rắn (ví dụ: 'O' hoặc '*')
            // Ở đây dùng 'X' cho đầu và 'o' cho thân để dễ phân biệt (tùy chọn)
            if (i == 0) {
                cout << "O"; // Đầu rắn
            } else {
                cout << "o"; // Thân rắn
            }
            // Hoặc đơn giản là: cout << "X"; cho tất cả các đốt
        }
    }
    // --- KẾT THÚC CODE CHO ISSUE Snake::Draw ---

    // --- CÁC PHƯƠNG THỨC KHÁC CẦN IMPLEMENT CHO CÁC ISSUE TIẾP THEO ---

    // Phương thức di chuyển rắn (Cần implement)
    void Move() {
        // 1. Cập nhật vị trí các đốt thân (từ đuôi lên gần đầu)
        //    body[i] = body[i-1]
        for (int i = length - 1; i > 0; --i) {
             body[i] = body[i - 1];
        }

        // 2. Cập nhật vị trí đầu rắn dựa vào direction
        Point newHead = body[0]; // Lấy vị trí đầu hiện tại
        switch (direction) {
            case 0: // Phải
                newHead.x++;
                break;
            case 1: // Xuống
                newHead.y++;
                break;
            case 2: // Trái
                newHead.x--;
                break;
            case 3: // Lên
                newHead.y--;
                break;
        }
        body[0] = newHead; // Cập nhật vị trí mới cho đầu rắn

        // Lưu lại hướng vừa di chuyển
         prevDirection = direction;
    }

    // Phương thức tăng độ dài rắn khi ăn mồi (Cần implement)
    void Grow() {
        // Tăng length lên 1
        // Vị trí đốt mới sẽ tự động được cập nhật đúng trong lần gọi Move() tiếp theo
        // vì vòng lặp di chuyển thân sẽ không ghi đè lên đốt cuối cùng cũ nữa.
        if (length < 100) { // Đảm bảo không vượt quá kích thước mảng
            length++;
        }
    }

    // Phương thức kiểm tra va chạm (với tường hoặc với thân) (Cần implement)
    bool CheckCollision(int boardWidth, int boardHeight) {
        Point head = body[0];

        // 1. Kiểm tra va chạm với tường
        if (head.x <= 0 || head.x >= boardWidth - 1 || head.y <= 0 || head.y >= boardHeight - 1) {
            return true; // Va chạm tường
        }

        // 2. Kiểm tra va chạm với thân
        for (int i = 1; i < length; ++i) {
            if (head.x == body[i].x && head.y == body[i].y) {
                return true; // Tự cắn vào thân
            }
        }

        return false; // Không va chạm
    }

    // (Tùy chọn) Phương thức thay đổi hướng đi
    void ChangeDirection(int newDirection) {
         // Chỉ thay đổi hướng nếu không phải là quay đầu 180 độ
        if (newDirection == 0 && prevDirection != 2) direction = newDirection; // Phải (ko phải đang đi Trái)
        else if (newDirection == 1 && prevDirection != 3) direction = newDirection; // Xuống (ko phải đang đi Lên)
        else if (newDirection == 2 && prevDirection != 0) direction = newDirection; // Trái (ko phải đang đi Phải)
        else if (newDirection == 3 && prevDirection != 1) direction = newDirection; // Lên (ko phải đang đi Xuống)
    }

}; // --- Kết thúc lớp Snake ---


// --- Hàm vẽ khung trò chơi ---
void DrawBoard(int width, int height) {
    // Vẽ đường viền ngang trên và dưới
    for (int i = 0; i < width; ++i) {
        gotoxy(i, 0);
        cout << "=";
        gotoxy(i, height - 1);
        cout << "=";
    }
    // Vẽ đường viền dọc trái và phải
    for (int i = 0; i < height; ++i) {
        gotoxy(0, i);
        cout << "|";
        gotoxy(width - 1, i);
        cout << "|";
    }
    // Vẽ góc (tùy chọn)
    gotoxy(0, 0); cout << "+";
    gotoxy(width - 1, 0); cout << "+";
    gotoxy(0, height - 1); cout << "+";
    gotoxy(width - 1, height - 1); cout << "+";
}
// --- Kết thúc hàm vẽ khung ---


// --- Hàm tạo thức ăn cho rắn ---
Point GenerateFood(int width, int height, const Snake& snake) {
    Point food;
    bool onSnake;
    do {
        // Tạo tọa độ ngẫu nhiên trong phạm vi bảng (tránh biên)
        food.x = rand() % (width - 2) + 1;  // Từ 1 đến width - 2
        food.y = rand() % (height - 2) + 1; // Từ 1 đến height - 2

        // Kiểm tra xem thức ăn có xuất hiện trên thân rắn không
        onSnake = false;
        for (int i = 0; i < snake.length; ++i) {
            if (food.x == snake.body[i].x && food.y == snake.body[i].y) {
                onSnake = true;
                break;
            }
        }
    } while (onSnake); // Lặp lại nếu thức ăn xuất hiện trên rắn

    return food;
}

// --- Hàm vẽ thức ăn ---
void DrawFood(const Point& food) {
    gotoxy(food.x, food.y);
    cout << "*"; // Ký tự đại diện cho thức ăn
}

// --- Hàm chính của chương trình ---
int main() {
    srand(time(0)); // Khởi tạo seed cho hàm random

    // --- Cài đặt trò chơi ---
    const int gameWidth = 40;  // Chiều rộng màn hình game
    const int gameHeight = 20; // Chiều cao màn hình game
    int score = 0;
    bool gameOver = false;
    int gameSpeed = 500; // Tốc độ game (ms), số nhỏ hơn -> nhanh hơn

    Snake mySnake; // Tạo đối tượng rắn
    Point food = GenerateFood(gameWidth, gameHeight, mySnake); // Tạo vị trí thức ăn đầu tiên

    // Ẩn con trỏ console (tùy chọn, cho đẹp hơn)
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // ẩn con trỏ
    SetConsoleCursorInfo(out, &cursorInfo);


    // --- Vòng lặp chính của game ---
    while (!gameOver) {
        // 1. Xử lý input từ người dùng
        if (kbhit()) { // Kiểm tra xem có phím nào được nhấn không
            char key = getch(); // Lấy ký tự phím được nhấn
            switch (key) {
                case 'a': // Trái
                case 'A':
                case 75: // Mũi tên trái (cho một số hệ thống)
                    mySnake.ChangeDirection(2);
                    break;
                case 'd': // Phải
                case 'D':
                case 77: // Mũi tên phải
                    mySnake.ChangeDirection(0);
                    break;
                case 'w': // Lên
                case 'W':
                case 72: // Mũi tên lên
                    mySnake.ChangeDirection(3);
                    break;
                case 's': // Xuống
                case 'S':
                case 80: // Mũi tên xuống
                    mySnake.ChangeDirection(1);
                    break;
                case 27: // Phím Esc -> Thoát game
                    gameOver = true;
                    break;
            }
        }

        // 2. Cập nhật trạng thái game
        if (!gameOver) {
            mySnake.Move(); // Di chuyển rắn

             // Kiểm tra ăn mồi
            Point head = mySnake.body[0];
            if (head.x == food.x && head.y == food.y) {
                mySnake.Grow(); // Rắn dài ra
                score += 10;     // Tăng điểm
                food = GenerateFood(gameWidth, gameHeight, mySnake); // Tạo thức ăn mới
                // Có thể tăng tốc độ game ở đây nếu muốn
                // if (gameSpeed > 50) gameSpeed -= 5;
            }

            // Kiểm tra va chạm
            if (mySnake.CheckCollision(gameWidth, gameHeight)) {
                 gameOver = true;
            }
        }


        // 3. Vẽ lại màn hình game
        system("cls"); // Xóa màn hình cũ
        DrawBoard(gameWidth, gameHeight); // Vẽ lại khung
        mySnake.Draw(); // Vẽ rắn ở vị trí mới
        DrawFood(food); // Vẽ thức ăn

        // Hiển thị điểm số
        gotoxy(gameWidth + 2, 2); // Vị trí hiển thị điểm (bên ngoài khung)
        cout << "Score: " << score;


        // 4. Tạm dừng để điều khiển tốc độ game
        Sleep(gameSpeed);

    } // --- Kết thúc vòng lặp game ---


    // --- Xử lý khi Game Over ---
    system("cls");
    gotoxy(gameWidth / 2 - 5, gameHeight / 2);
    cout << "GAME OVER!";
    gotoxy(gameWidth / 2 - 8, gameHeight / 2 + 1);
    cout << "Your Score: " << score;
    gotoxy(0, gameHeight); // Đưa con trỏ xuống dòng cuối để tránh ghi đè thông báo

    // Hiện lại con trỏ console trước khi kết thúc
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(out, &cursorInfo);


    return 0; // Kết thúc chương trình
}
