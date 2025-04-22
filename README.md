Bước 1: Mở git bash chạy 2 lệnh này:

	git config --global user.name "UIT.MSSV"
	git config --global user.email "mail tk github"

Bước 2: 
	Mở trình duyệt mặc định của máy lên đăng nhập vào github và để đó.

Bước 3:
	git clone https://github.com/UIT24730091/SnackGame.git

Bước 4: Vào thư mục dự án vừa clone về
	SnackGame


Bước 5: Muốn chắc chắn bạn đang làm việc với phiên bản mới nhất từ GitHub, chạy lệnh:
	git pull origin main


Bước 6: Tạo nhánh mới (ko được làm trên nhánh main)
	git checkout -b feature/tên_nhánh_mới	(nên thay bằng tên phù hợp với issue được yêu cầu trên github)

Bước 7: Mở file main.cpp trong thư mục dự án và nhờ AI hỗ trợ theo yêu cầu của issue

Bước 8: Chạy lệnh để thêm file sửa vào Stage:
	git add main.cpp

Bước 9: Commit:

	git commit -m "Merge remote-tracking branch"  -> nội dung trong " " mô tả theo issue

Bước 10: Đẩy code lên repo trên github:

	git push -u origin feature/tên_nhánh_mới

Nếu đẩy thành công thì lên Github 
Vào repository dự án trên GitHub sẽ thấy một thông báo màu vàng gợi ý tạo Pull Request từ branch vừa push lên. 
Nhấn vào nút "Compare & pull request".
