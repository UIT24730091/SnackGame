#include <iostream>     // su dung cout de in ra man hinh
#include <windows.h>    // su dung ham gotoxy va Sleep cua Windows
#include <cstdlib>      // su dung rand, srand, system
#include <conio.h>      // su dung _kbhit va _getch
#include <ctime>        // su dung time de tao ngau nhien
using namespace std;

// Ham gotoxy de di chuyen con tro den vi tri (column, line) tren console

class CONRAN{
public:
    struct Point A[100];
    int DoDai;
    CONRAN(){
        DoDai = 3;
        A[0].x = 10; A[0].y = 10;
        A[1].x = 11; A[1].y = 10;
        A[2].x = 12; A[2].y = 10;
    }


// Cau truc Point dai dien cho 1 diem tren man hinh voi toa do x, y
struct Point
{
    int x, y;
};

// Lop Snake dai dien cho con ran
class CONRAN{
public:
    struct Point A[100];
    int DoDai;
    CONRAN(){
        DoDai = 3;
        A[0].x = 10; A[0].y = 10;
        A[1].x = 11; A[1].y = 10;
        A[2].x = 12; A[2].y = 10;
    }
    // Ham khoi tao ran
    Snake()
    {
        length = 3;
        direction = 0;
        prevDirection = 0;
        body[0].x = 10; body[0].y = 10;
        body[1].x = 9;  body[1].y = 10;
        body[2].x = 8;  body[2].y = 10;
    }

    // Ve ran tren man hinh
    void Draw()
    {
        for (int i = 0; i < length; i++)
        {
            gotoxy(body[i].x, body[i].y);
            if (i == 0)
                cout << "O"; // dau ran la ky tu 'O'
            else
                cout << "o"; // than ran la ky tu 'o'
        }
    }

    // Di chuyen ran
    void Move()
    {
        // dich than ran (dot sau bang vi tri dot truoc)
        for (int i = length - 1; i > 0; i--)
        {
            body[i] = body[i - 1];
        }

        // thay doi vi tri dau ran theo huong dang di
        if (direction == 0) body[0].x = body[0].x + 1;
        if (direction == 1) body[0].y = body[0].y + 1;
        if (direction == 2) body[0].x = body[0].x - 1;
        if (direction == 3) body[0].y = body[0].y - 1;

        prevDirection = direction; // cap nhat huong cu
    }

    // ---- FIX: Thêm hàm EatFood vào class (trước đây thiếu định nghĩa) ----
    // Tang do dai khi an thuc an
    void EatFood()
    {
        if (length < 256) // Thêm kiểm tra giới hạn (tùy chọn nhưng nên có)
        {
             length++;
        }
    }
    // ---- END FIX ----

    // ---- FIX: Khai báo CheckCollision đúng cách, xóa các hàm thừa khỏi class ----
    // Kiem tra va cham tuong hoac than ran
    bool CheckCollision(int width, int height); // Chỉ khai báo ở đây
}; // ---- FIX: Đảm bảo có dấu ; kết thúc class ----


// ---- FIX: Định nghĩa CheckCollision bên ngoài lớp Snake ----
bool Snake::CheckCollision(int width, int height)
{
    // va cham tuong
    if (body[0].x <= 0 || body[0].x >= width -1 || body[0].y <= 0 || body[0].y >= height -1)
    {
        return true;
    }

    // va cham voi than ran
    for (int i = 1; i < length; i++) // Bắt đầu từ 1 vì đầu không thể tự va vào chính nó
    {
        if (body[0].x == body[i].x && body[0].y == body[i].y)
        {
            return true;
        }
    }
    return false; // Không có va chạm
}


// ---- FIX: Xóa hàm GenerateFood thừa trong class, chỉ giữ hàm global này ----
// Tao vi tri moi cho thuc an khac vi tri cua ran
Point GenerateFood(int width, int height, const Snake& snake)
{
    Point food;
    bool onSnake;
    do
    {
        onSnake = false;
        food.x = rand() % (width - 2) + 1;
        food.y = rand() % (height - 2) + 1;

        // dam bao thuc an khong trung vi tri ran
        for (int i = 0; i < snake.length; ++i)
        {
            if (food.x == snake.body[i].x && food.y == snake.body[i].y)
            {
                onSnake = true;
                break;
            }
        }
    }
    while (onSnake);
    return food;
}

// Ve khung tro choi
void DrawBoard(int width, int height)
{
    for (int i = 0; i < width; ++i)
    {
        gotoxy(i, 0); cout << "=";             // vien tren
        gotoxy(i, height - 1); cout << "=";    // vien duoi
    }
    for (int i = 0; i < height; ++i)
    {
        gotoxy(0, i); cout << "=";             // vien trai
        gotoxy(width - 1, i); cout << "=";     // vien phai
    }
}

// Ham chinh
int main()
{
    srand(time(0)); // khoi tao random
    Snake snake;
    Point food;
    int score = 0;
    int gameWidth = 40;
    int gameHeight = 20;
    int gameSpeed = 100; // Change speed game for test
    char input;
    bool gameOver = false;

    food = GenerateFood(gameWidth, gameHeight, snake); // tao thuc an ban dau

    // ---- FIX: Xóa bỏ vòng lặp while(!gameOver) bị lồng bên trong ----
    while (!gameOver)
    {
        // xu ly dieu khien
        if (_kbhit()) // Sử dụng _kbhit và _getch như code cuối
        {
            input = _getch();
            // ---- FIX: Logic kiểm tra hướng cũ giống code cuối ----
            if (input == 'a' && snake.prevDirection != 0) snake.direction = 2; // trai
            if (input == 'w' && snake.prevDirection != 1) snake.direction = 3; // len
            if (input == 'd' && snake.prevDirection != 2) snake.direction = 0; // phai
            if (input == 's' && snake.prevDirection != 3) snake.direction = 1; // xuong
        }

        system("cls"); // xoa man hinh
        
        // Đảm bảo thứ tự đúng: vẽ khung trước, sau đó vẽ thức ăn và rắn
        DrawBoard(gameWidth, gameHeight); // ve khung
        
        // ve thuc an
        gotoxy(food.x, food.y);
        cout << "*";
        
        // ve ran
        snake.Draw();
        
        // di chuyen ran (sau khi vẽ)
        snake.Move();

        // kiem tra an thuc an
        if (snake.body[0].x == food.x && snake.body[0].y == food.y)
        {
            snake.EatFood(); // Gọi hàm đã sửa/thêm
            score += 10;
            food = GenerateFood(gameWidth, gameHeight, snake);
        }

        // ---- FIX: Gọi CheckCollision đúng cách, xóa định nghĩa thừa ----
        // kiem tra va cham
        if (snake.CheckCollision(gameWidth, gameHeight))
        {
            gameOver = true;
        }

        // ---- FIX: Đặt hiển thị điểm và Sleep/Game Over logic hợp lý ----
        // hien thi diem (chỉ khi game chưa kết thúc)
        if (!gameOver)
        {
             gotoxy(gameWidth / 2 - 5, gameHeight + 2); // Hiển thị điểm dưới khung, cách 2 dòng
             cout << "Score: " << score;
             Sleep(gameSpeed); // Chỉ tạm dừng khi game đang chạy
        }
    } // ---- Kết thúc vòng lặp while (!gameOver) chính ----

    // ---- FIX: Xử lý Game Over SAU khi vòng lặp chính kết thúc ----
    // Màn hình Game Over
    system("cls"); // Xóa màn hình lần cuối
    gotoxy(gameWidth / 2 - 5, gameHeight / 2);     // Căn giữa tương đối
    cout << "Game Over!";
    gotoxy(gameWidth / 2 - 5, gameHeight / 2 + 1);
    cout << "Score: " << score;
    gotoxy(gameWidth / 2 - 10, gameHeight / 2 + 3); // Dịch xuống chút
    cout << "Press any key to exit...";
    _getch(); // Doi nhan phim bat ky

    return 0;
}
