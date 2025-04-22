# Đồ án Cuối kỳ: Snake Game (C++)

Đây là đồ án cuối kỳ môn Kỹ năng nghề nghiệp tại trường Đại học Công nghệ thông tin. Dự án là một phiên bản đơn giản của trò chơi Snake (Rắn săn mồi) cổ điển, được xây dựng hoàn toàn bằng ngôn ngữ C++ và thư viện `windows.h` để tương tác với cửa sổ console.

Dự án được phát triển bởi "GROUP 10 - CN1.K2024.2" gồm 5 thành viên, sử dụng Git và GitHub để quản lý mã nguồn và cộng tác.

## Mục lục
* [Tính năng](#tính-năng)
* [Công nghệ sử dụng](#công-nghệ-sử-dụng)
* [Yêu cầu](#yêu-cầu)
* [Cài đặt và Chạy](#cài-đặt-và-chạy)
* [Cách chơi](#cách-chơi)
* [Cấu trúc dự án](#cấu-trúc-dự-án)
* [Thành viên nhóm](#thành-viên-nhóm)
* [Hướng phát triển (Tùy chọn)](#hướng-phát-triển-tùy-chọn)

## Tính năng
*   **Giao diện Console:** Toàn bộ trò chơi hiển thị và hoạt động trên cửa sổ dòng lệnh (console) của Windows.
*   **Điều khiển Rắn:** Người chơi điều khiển rắn di chuyển Lên, Xuống, Trái, Phải bằng các phím `W`, `A`, `S`, `D`.
*   **Ăn mồi & Tăng trưởng:** Rắn ăn mồi (`*`) để tăng độ dài và điểm số.
*   **Phát hiện va chạm:** Trò chơi kết thúc khi rắn đâm vào tường biên hoặc tự đâm vào thân mình.
*   **Ngăn chặn Quay đầu:** Rắn không thể quay ngược 180 độ ngay lập tức.
*   **Hiển thị Điểm số:** Điểm số hiện tại của người chơi được hiển thị trên màn hình.
*   **Tạo mồi ngẫu nhiên:** Mồi xuất hiện ở các vị trí ngẫu nhiên trên màn hình (không trùng với thân rắn).
*   **Màn hình Game Over:** Hiển thị thông báo "GAME OVER" và điểm số cuối cùng khi thua.

## Công nghệ sử dụng
*   **Ngôn ngữ:** C++
*   **Thư viện:**
    *   `<iostream>`: Nhập/xuất chuẩn.
    *   `<windows.h>`: Cung cấp các hàm API của Windows để xử lý console (như `gotoxy`, `SetConsoleCursorPosition`, `GetStdHandle`, `Sleep`, `CONSOLE_CURSOR_INFO`).
    *   `<conio.h>`: Cung cấp hàm `kbhit()` để kiểm tra phím nhấn và `getch()` để đọc phím không cần Enter.
    *   `<cstdlib>`: Sử dụng cho `system("cls")` (xóa màn hình), `rand()`, `srand()`.
    *   `<ctime>`: Sử dụng cho `time()` để khởi tạo bộ sinh số ngẫu nhiên.
*   **Công cụ:**
    *   Git: Hệ thống quản lý phiên bản phân tán.
    *   GitHub: Nền tảng lưu trữ mã nguồn và cộng tác.
    *   CodeBlock: IDE để lập trình C/C++

## Yêu cầu
*   **Hệ điều hành:** Windows (Do phụ thuộc vào thư viện `windows.h` và `conio.h`).
*   **Trình biên dịch C++:** Cần có một trình biên dịch C++ hỗ trợ chuẩn C++11 trở lên (ví dụ: g++ trong MinGW, hoặc trình biên dịch của Visual Studio).

## Cài đặt và Chạy
1.  **Clone repository về máy:**
    ```bash
    git clone [URL đến repository GitHub của nhóm bạn]
    ```
2.  **Di chuyển vào thư mục dự án:**
    ```bash
    cd [Tên thư mục dự án]
    ```
3.  **Biên dịch mã nguồn:**
    *   **Sử dụng g++ (MinGW):** Mở terminal (như Git Bash hoặc CMD đã cài MinGW) trong thư mục dự án và chạy lệnh:
        ```bash
        g++ main.cpp -o snake_game.exe -static-libgcc -static-libstdc++
        ```
    *   **Sử dụng Visual Studio:** Mở file mã nguồn hoặc project bằng Visual Studio và chọn `Build` -> `Build Solution` (hoặc nhấn F7). File thực thi (`.exe`) thường sẽ nằm trong thư mục `Debug` hoặc `Release` bên trong thư mục project.

4.  **Chạy trò chơi:**
    *   Mở terminal hoặc CMD, di chuyển đến thư mục chứa file `snake_game.exe` và chạy lệnh:
        ```bash
        ./snake_game.exe
        ```
        hoặc (trên CMD):
        ```bash
        snake_game.exe
        ```
    *   Nếu dùng Visual Studio, bạn có thể chạy trực tiếp từ môi trường phát triển (nhấn F5 hoặc Ctrl+F5).

## Cách chơi
*   Khởi chạy file `snake_game.exe`.
*   Sử dụng các phím `W`, `A`, `S`, `D` để điều khiển hướng di chuyển của rắn (Oooo).
    *   `W`: Đi lên
    *   `A`: Đi sang trái
    *   `S`: Đi xuống
    *   `D`: Đi sang phải
*   Mục tiêu là điều khiển rắn ăn các viên mồi (`*`) xuất hiện trên màn hình. Mỗi lần ăn mồi, rắn sẽ dài ra và điểm số tăng lên.
*   Tránh để đầu rắn (`O`) va chạm vào các đường biên (`=`, `|`) hoặc vào thân rắn (`o`). Nếu va chạm, trò chơi sẽ kết thúc.
*   Nhấn phím `ESC` bất kỳ lúc nào để thoát khỏi trò chơi.

## Cấu trúc dự án
```text
📁 SnakeGame/
├── 📄 main.cpp    # File mã nguồn chính chứa tất cả logic và hàm main()
├── 📄 README.md   # File hướng dẫn này
└── 📄 .gitignore  # (Tùy chọn) Các file/thư mục được Git bỏ qua

`main.cpp`: Chứa định nghĩa cấu trúc `Point`, lớp `Snake`, các hàm tiện ích (`gotoxy`, `DrawBoard`, `GenerateFood`, `DrawFood`) và hàm `main()` điều khiển luồng chính của game.
