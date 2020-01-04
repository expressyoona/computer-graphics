# STICKS GAME

## Danh sách thành viên
1. Lường Khắc Tuấn Anh - 17IT1
1. Lê Quang Duật - 17IT1
1. Nguyễn Bảo Minh Hoàng - 17IT1

## Rules
* Khởi đầu sẽ có N thanh hình chữ nhật nằm đè lên nhau
* Mỗi thanh sẽ có độ sâu z, thanh có z nhỏ hơn sẽ nằm đè lên thanh có z lớn hơn
* Nếu người chơi click vào 1 thanh không bị đè bởi bất kỳ thanh nào. Thanh đó sẽ biến mất
* Mỗi T(s) sẽ có 1 thanh được sinh ra ngẫu nhiên
* Điều kiện game kết thúc: Không còn thanh nào trên màn hình hoặc số thanh đạt đến số lượng MAX_STICKS(MAX_STICKS > N)

## Quy tắc sinh ngẫu nhiên 1 thanh:
* Đầu tiên sinh ngẫu nhiên 1 cặp tọa độ (x, y) với x < 1000, y < 500. Đây là tọa độ góc dưới bên trái của thanh hình chữ nhật.
* Sinh tiếp ngẫu nhiên chiều dài(l) và chiều rộng(r) của thanh. Đảm bảo rằng l+y và r+x < MAX_WIDTH/MAX_HEIGHT(không bị tràn)
* Sinh lần lượt 3 số m, n, p ngẫu nhiên trong đoạn [0, 255]. Sau đó chia từng số cho 255. Dùng glColor3f với các số sau khi chia để có mã màu ngẫu nhiên.
* Sinh ngẫu nhiên độ sâu z trong đoạn [0, MAX_DEPTH]
* Vẽ hình chữ nhật với các đỉnh (x, y), (x, y + l), (x+r, y), (x+r, y+l) và màu như trên.

## Các hằng số
* MAX_WIDTH, MAX_HEIGHT: chiều rộng, cao của cửa sổ
* N: số thanh khởi đầu
* TIME_REFRESH: thời gian(giây) thêm 1 thanh mới
* MAX_STICKS: số lượng thanh tối đa
* MAX_DEPTH: độ sâu tối đa của 1 thanh
* MIN_LENGTH: chiều dài/rộng tối thiểu của thanh nằm ngang/dọc
* MIN_WIDTH: chiều rộng/dài tối thiểu của thanh nằm dọc/ngang

## Các phương thức/hàm
* initGl(): khởi tạo cấu hình OpenGL
* paint(): vẽ các thanh chữ nhật
* onMouseClick(): được sử dụng khi có sự kiện click chuột trên màn hình
* timer(): được sử dụng mỗi TIME_REFRESH(s)
* clickedRectangle(): kiểm tra hình chữ nhật được click
* generateStick(): sinh ra 1 thanh với các tham số ngẫu nhiên
* random(a, b): sinh ngẫu nhiên 1 số nguyên trong đoạn [a, b]
* drawStick(): vẽ 1 thanh chữ nhật lên màn hình
* printRectangle(): chỉ để debug thôi
