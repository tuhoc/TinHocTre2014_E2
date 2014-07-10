Ví dụ Simple
=============

Các chương trình Arduino này sẽ nhận biết khi các khối Trí Uẩn được ghép thành hình chữ nhật theo cách trong hình sau:

http://trochoihoctap.com/UserFiles/image/HD_1.JPG



TriUan_0.ino là sketch nạp cho khối TriUan_0 (chọn board *Arduino Uno*)

TriUan_1234.ino là sketch nạp cho các khối Trí Uẩn còn lại (1a, 1b, 2a, 2b, 3, 4) (chọn board *ATmega8*)

_Chú ý_: Đây chỉ là một cách nhận biết đơn giản. Có rất nhiều cách nhận biết khác.



Hoạt động
---------

Khi ghép thành hình chữ nhật thì:

- Cổng 8 của khối 0  nằm đối diện với cổng 4 của khối 1a (100)
- Cổng 3 của khối 1a nằm đối diện với cổng 4 của khối 4  (101)
- Cổng 7 của khối 4  nằm đối diện với cổng 5 của khối 2a (102)
- Cổng 4 của khối 2a nằm đối diện với cổng 8 của khối 4  (103)
- Cổng 9 của khối 4  nằm đối diện với cổng 5 của khối 2b (104)
- Cổng 4 của khối 2b nằm đối diện với cổng 3 của khối 3  (105)
- Cổng 6 của khối 3  nằm đối diện với cổng 3 của khối 1b (106)
- Cổng 4 của khối 1b nằm đối diện với cổng 3 của khối 0  (107)

Như vậy nếu ta lần lượt gửi các dữ liệu 100, 101,..., 107 qua tám cặp cổng giao tiếp VLC này thì sẽ nhận biết được khi hình chữ nhật đã được ghép xong.

Cụ thể có các bước sau:

- Khối 0 gửi ra cổng 8 dữ liệu 100
- Khi khối 1a nhận từ cổng 4 dữ liệu 100 thì gửi tiếp ra cổng 3 dữ liệu 101
- Khi khối 4 nhận từ cổng 4 dữ liệu 101 thì gửi tiếp ra cổng 7 dữ liệu 102
- Khi khối 2a nhận từ cổng 5 dữ liệu 102 thì gửi tiếp ra cổng 4 dữ liệu 103
- Khi khối 4 nhận từ cổng 8 dữ liệu 103 thì gửi tiếp ra cổng 9 dữ liệu 104
- Khi khối 2b nhận từ cổng 5 dữ liệu 104 thì gửi tiếp ra cổng 4 dữ liệu 105
- Khi khối 3 nhận từ cổng 3 dữ liệu 105 thì gửi tiếp ra cổng 6 dữ liệu 106
- Khi khối 1b nhận từ cổng 3 dữ liệu 106 thì gửi tiếp ra cổng 4 dữ liệu 107
- Khi khối 0 nhận từ cổng 3 dữ liệu 107 thì hình chữ nhật đã được ghép xong

Như vậy, ví dụ thuật toán cho khối 1 (cả 1a và 1b) sẽ là:
- Nếu cổng 4 nhận dữ liệu 100 thì gửi ra cổng 3 dữ liệu 101
- Nếu cổng 3 nhận dữ liệu 106 thì gửi ra cổng 4 dữ liệu 107

Tương tự cho các khối 2, 3, 4

Với khối 0, ta có thể làm như sau:
- Liên tục gửi ra cổng 8 dữ liệu 100. Giữa các lần gửi đợi 0.5 giây.
- Nếu cổng 3 nhận dữ liệu 107 trong hai lần gửi, thì hình chữ nhật đã được ghép.



