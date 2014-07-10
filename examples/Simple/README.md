Ví dụ Simple
=============

Các chương trình Arduino này sẽ nhận biết khi các khối Trí Uẩn được ghép thành hình chữ nhật theo cách trong hình sau:

http://trochoihoctap.com/UserFiles/image/HD_1.JPG



TriUan_0.ino là sketch nạp cho khối TriUan_0 (chọn board *Arduino Uno*)

TriUan_1234.ino là sketch nạp cho các khối Trí Uẩn còn lại (1a, 1b, 2a, 2b, 3, 4) (chọn board *ATmega8*)


Hoạt động
---------

Khi ghép thành hình chữ nhật thì:

- _Cổng 8_ của khối 0  nằm đối diện với cổng 4 của khối 1a (100)
- Cổng 3 của khối 1a nằm đối diện với cổng 4 của khối 4  (101)
- Cổng 7 của khối 4  nằm đối diện với cổng 5 của khối 2a (102)
- Cổng 4 của khối 2a nằm đối diện với cổng 8 của khối 4  (103)
- Cổng 9 của khối 4  nằm đối diện với cổng 5 của khối 2b (104)
- Cổng 4 của khối 2b nằm đối diện với cổng 3 của khối 3  (105)
- Cổng 6 của khối 3  nằm đối diện với cổng 3 của khối 1b (106)
- Cổng 4 của khối 1b nằm đối diện với cổng 3 của khối 0  (107)

