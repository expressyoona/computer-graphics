# STICKS GAME

## Rules - Luật chơi
* Khởi đầu sẽ có N thanh hình chữ nhật nằm đè lên nhau
* Mỗi thanh sẽ có độ sâu z, thanh có z nhỏ hơn sẽ nằm đè lên thanh có z lớn hơn
* Nếu người chơi click vào 1 thanh không bị đè bởi bất kỳ thanh nào. Thanh đó sẽ biến mất
* Nếu người chơi không làm biến mất được 1 thanh nào trong vào T(s), sẽ có 1 thanh được sinh ra ngẫu nhiên
* Điều kiện game kết thúc: Không còn thanh nào trên màn hình hoặc số thanh đạt đến số lượng MAX_STICKS(MAX_STICKS > N)

## Quy ước cách sinh ngẫu nhiên 1 thanh:
* Đầu tiên sinh ngẫu nhiên 1 cặp tọa độ (x, y) với x < 1000, y < 500. Đây là tọa độ góc dưới bên trái của thanh hình chữ nhật.
* Sinh tiếp ngẫu nhiên chiều dài(l) và chiều rộng(r) của thanh. Đảm bảo rằng l+y và r+x < MAX_WIDTH/MAX_HEIGHT(không bị tràn)
* Sinh lần lượt 3 số m, n, p ngẫu nhiên trong đoạn [0, 255]. Sau đó chia từng số cho 255. Dùng glColor3f với các số sau khi chia để có mã màu ngẫu nhiên.
* Sinh ngẫu nhiên độ sâu z trong đoạn [0, MAX_DEPTH]
* Vẽ hình chữ nhật với các đỉnh (x, y), (x, y + l), (x+r, y), (x+r, y+l) và màu như trên.