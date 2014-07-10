// Chương trình nhận biết khối Trí Uẩn ghép hình chữ nhật
// Update 140709 - 19:00

#include <thAvr.h>
#include <thVLC.h>


byte blockID;


void setup()
{
  blockID = thVLC.getID();
  thVLC.begin();
  
  //Serial.begin(9600);
  //Serial.print("TriUan Block ");
  //Serial.println(BlockID);
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


void TriUan_1()        // TriUan_1 có 2 vị trí
{
  if (thVLC_checkReceiveValue(4, 100))
  {
    thVLC.sendByte(3, 101);
  }
  
  if (thVLC_checkReceiveValue(3, 106))
  {
    thVLC.sendByte(4, 107);
  }
}


void TriUan_2()        // TriUan_2 có 2 vị trí và có đặt thể ngửa hay xấp
{
  if (thVLC.receiveReady(4))
  {
    byte rxData = thVLC.receiveResult(4);
    switch (rxData)
    {
      case 102:  thVLC.sendByte(5, 103);  break;
      case 104:  thVLC.sendByte(5, 105);  break;
    }
  }
  
  if (thVLC.receiveReady(5))
  {
    byte rxData = thVLC.receiveResult(5);
    switch (rxData)
    {
      case 102:  thVLC.sendByte(4, 103);  break;
      case 104:  thVLC.sendByte(4, 105);  break;
    }
  }
}


void TriUan_3()
{
  if (thVLC_checkReceiveValue(3, 105))
  {
    thVLC.sendByte(6, 106);
  }
}


void TriUan_4()
{
  if (thVLC_checkReceiveValue(4, 101))
  {
    thVLC.sendByte(7, 102);
  }
  if (thVLC_checkReceiveValue(8, 103))
  {
    thVLC.sendByte(9, 104);
  }
}


void loop()
{  
  switch (blockID)
  {
    case TRI_UAN_1:  TriUan_1();  break;
    case TRI_UAN_2:  TriUan_2();  break;
    case TRI_UAN_3:  TriUan_3();  break;
    case TRI_UAN_4:  TriUan_4();  break;
  }
}
