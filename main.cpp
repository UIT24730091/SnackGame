#include <iostream>     // su dung cout de in ra man hinh
#include <windows.h>    // su dung ham gotoxy va Sleep cua Windows
#include <cstdlib>      // su dung rand, srand, system
#include <conio.h>      // su dung _kbhit va _getch
#include <ctime>        // su dung time de tao ngau nhien
using namespace std;

// Ham gotoxy de di chuyen con tro den vi tri (column, line) tren console
void gotoxy( int column, int line )
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle( STD_OUTPUT_HANDLE ),
        coord
    );
}

// Cau truc Point dai dien cho 1 diem tren man hinh voi toa do x, y
struct Point
{
    int x, y;
};

// Lop Snake dai dien cho con ran
class Snake
{
public:
    Point body[100];     // mang luu vi tri cac dot tren than ran
    int length;          // do dai hien tai cua ran
    int direction;       // huong di chuyen (0: phai, 1: xuong, 2: trai, 3: len)
    int prevDirection;   // huong di chuyen truoc do (de tranh quay dau dot ngot)

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
            cout << "X"; // moi dot tren ran la ky tu 'X'
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

    // Tang do dai khi an thuc an
    // Ngoc Long
    void EatFood()
    {
        length++;
    }
    // End Eat Food

    // Kiem tra va cham tuong hoac than ran
    bool CheckCollision(int width, int height)
    {
        // va cham tuong
         bool CheckWallCollision() const {
        Point head = GetHead();
        // Va cham neu dau ra ngoai bien (tru vien)
        return head.x <= 0 || head.x >= WIDTH - 1 || head.y <= 0 || head.y >= HEIGHT - 1;
    }
       // va cham voi than ran
       bool CheckSelfCollision() const {
        Point head = GetHead();
        // Bat đau kiem tra tu đot thu 2 (chi so 1), vi đau luôn trung voi đot 0
        for (size_t i = 1; i < body.size(); ++i) {
            if (head == body[i]) {
                return true;
            }
        }
        return false;
    }
};


// Tao vi tri moi cho thuc an khac vi tri cua ran
// Food on Snake
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
// Food on Snake

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
    int gameSpeed = 200; // toc do game
    char input;
    bool gameOver = false;

    food = GenerateFood(gameWidth, gameHeight, snake); // tao thuc an ban dau

    while (!gameOver)
    {
        // xu ly dieu khien
        if (_kbhit())
        {
            input = _getch();
            if (input == 'a' && snake.prevDirection != 0) snake.direction = 2; // trai
            if (input == 'w' && snake.prevDirection != 1) snake.direction = 3; // len
            if (input == 'd' && snake.prevDirection != 2) snake.direction = 0; // phai
            if (input == 's' && snake.prevDirection != 3) snake.direction = 1; // xuong
        }

        system("cls"); // xoa man hinh
        DrawBoard(gameWidth, gameHeight); // ve khung

        // ve thuc an
        gotoxy(food.x, food.y);
        cout << "*";

        // ve ran
        snake.Draw();
        snake.Move();

        // kiem tra an thuc an
        if (snake.body[0].x == food.x && snake.body[0].y == food.y)
        {
            snake.EatFood();
            score += 10;
            food = GenerateFood(gameWidth, gameHeight, snake);
        }

        // kiem tra va cham
        if (snake.CheckCollision(gameWidth, gameHeight))
        {
            gameOver = true;
        }

        // hien thi diem
        gotoxy(gameWidth / 2 - 5, gameHeight + 1);
        cout << "Score: " << score;

        // ket thuc game
        while (!gameOver) {
        snake.Move();

        if (snake.CheckCollision(gameWidth, gameHeight)) {
            gameOver = true;
        }

        // Cap nhat score o dau do
        // score = snake.GetScore(); // Neu ban co ham nhu vay
    }

    // Sau vong lap while hoac ben trong if (gameOver)
    if (gameOver) {
        system("cls"); // Xoa man hinh
        int centerX = gameWidth / 2 - 5;
        int centerY = gameHeight / 2;

        gotoxy(centerX, centerY);
        cout << "Game Over!";
        gotoxy(centerX - 2, centerY + 1);
        cout << "Score: " << score;

        gotoxy(centerX - 6, centerY + 3);
        cout << "Press any key to exit...";
        _getch();
    }

    return 0;
}
