// Chương trình nhận biết khối Trí Uẩn ghép hình chữ nhật
// Update 140709 - 18:00

#include <thAvr.h>
#include <thVLC.h>
#include <thLedMatrix.h>


void setup()
{
  thVLC.begin();
  thLedMatrix.begin();
  
  //Serial.begin(9600);
  //Serial.print("TriUan Block 0");
}


// Kiểm tra xem tại cổng [port] có nhận được dữ liệu [value] không
boolean thVLC_checkReceiveValue(byte port, byte value)
{
  if (thVLC.receiveReady(port))
  {
    if (thVLC.receiveResult(port) == value)
    {
      return true;
    }
  }
  return false;
}


BITMAP Rectangle[] =
{
  0x00, 0x00,
  0x00, 0x00,
  0x00, 0x7C,
  0x00, 0x7C,
  0x00, 0x7C,
  0x00, 0x7C,
  0x00, 0x00,
  0x00, 0x00,
};


void TriUan_0()
{
  boolean receiveCorrectData = false;

  // Gửi đi lần 1
  thLedMatrix.setPixel(0, 0, RED);
  thVLC.sendByte(8, 100);
  delay(500);
  if (thVLC_checkReceiveValue(3, 107))    // kiểm tra dữ liệu nhận về
  {
    receiveCorrectData = true;
  }

  // Gửi đi lần 2
  thLedMatrix.setPixel(0, 0, BLACK);
  thVLC.sendByte(8, 100);
  delay(500);
  if (thVLC_checkReceiveValue(3, 107))    // kiểm tra dữ liệu nhận về
  {
    receiveCorrectData = true;
  }

  // Nếu nhận về được ít nhất 1 lần đúng từ 2 lần gửi đi
  if (receiveCorrectData)
  {
    thLedMatrix.setBitmap(Rectangle);     // Nhận đúng - ghép đủ hình chữ nhật
  }
  else
  {
    thLedMatrix.clear();                  // Không nhận đúng
  }
}


void loop()
{  
  TriUan_0();
}
