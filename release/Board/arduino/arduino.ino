#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <SerialCommand.h>  // Thêm vào sketch thư viện Serial Command
const byte RX = 11;          // Chân 3 được dùng làm chân RX
const byte TX = 10;          // Chân 2 được dùng làm chân TX
/* config pin button */
#define button1 A0
#define button2 A1
#define button3 A2
#define button4 A3
#define button5 A4
#define button6 A5
#define button7 6
#define button8 7
#define button9 6
/* config pin device */
#define DEN_PHONG_KHACH 30  // THIET BI
#define DIEU_HOA_PHONG_KHACH 31
#define DEN_PHONG_NGU_1 32
#define DIEU_HOA_PHONG_NGU_1 33
#define DEN_PHONG_NGU_2 34 
#define DIEU_HOA_PHONG_NGU_2 35 
#define DEN_PHONG_BEP 36  
#define QUAT_THONG_GIO_BEP 37
#define BINH_NONG_LANH 38  
/* config sensor device */
/*
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */

/* Khai cao mang trang thai */
String Liststatus[] = {"true","false","true","false","true","false","true","false","true"};
bool Listbutton[] = {true,true,true,true,true,true,true,true,true};
/* config Serial  */
SoftwareSerial mySerial = SoftwareSerial(RX, TX); 
SerialCommand sCmd(mySerial); // Khai báo biến sử dụng thư viện Serial Command

void setup() {
    //Khởi tạo Serial ở baudrate 57600 để debug ở serial monitor
    Serial.begin(9600);
    /* cai dat chan chuc nang */
    pinMode(button1,INPUT);
    pinMode(button2,INPUT);
    pinMode(button3,INPUT);
    pinMode(button4,INPUT);
    pinMode(button5,INPUT);
    pinMode(button6,INPUT);
    pinMode(button7,INPUT);
    pinMode(button8,INPUT);
    pinMode(button9,INPUT);
    pinMode(DEN_PHONG_KHACH,OUTPUT);
    pinMode(DIEU_HOA_PHONG_KHACH,OUTPUT);
    pinMode(DEN_PHONG_NGU_1,OUTPUT);
    pinMode(DIEU_HOA_PHONG_NGU_1,OUTPUT);
    pinMode(DEN_PHONG_NGU_2,OUTPUT);
    pinMode(DIEU_HOA_PHONG_NGU_2,OUTPUT);
    pinMode(DEN_PHONG_BEP,OUTPUT);
    pinMode(QUAT_THONG_GIO_BEP,OUTPUT);
    pinMode(BINH_NONG_LANH,OUTPUT);
    /* set trang thai ban dau */
    digitalWrite(DEN_PHONG_KHACH,HIGH);
    digitalWrite(DIEU_HOA_PHONG_KHACH,HIGH);
    digitalWrite(DEN_PHONG_NGU_1,HIGH);
    digitalWrite(DIEU_HOA_PHONG_NGU_1,HIGH);
    digitalWrite(DEN_PHONG_NGU_2,OUTPUT);
    digitalWrite(DIEU_HOA_PHONG_NGU_2,HIGH);
    digitalWrite(DEN_PHONG_BEP,HIGH);
    digitalWrite(QUAT_THONG_GIO_BEP,HIGH);
    digitalWrite(BINH_NONG_LANH,HIGH);
    digitalWrite(button1, HIGH);
    digitalWrite(button2, HIGH);
    digitalWrite(button3, HIGH);
    digitalWrite(button4, HIGH);
    digitalWrite(button5, HIGH);
    digitalWrite(button6, HIGH);
    digitalWrite(button7, HIGH);
    digitalWrite(button8, HIGH);
    digitalWrite(button9, HIGH);
    //Khởi tạo Serial ở baudrate 57600 cho cổng Serial thứ hai, dùng cho việc kết nối với ESP8266
    mySerial.begin(9600);
    sCmd.addCommand("LED",   led);
    updateStatusServer();
    updateDedvice();
}

void loop() {
    //button();
    sCmd.readSerial();
    //Bạn không cần phải thêm bất kỳ dòng code nào trong hàm loop này cả
}
/* Kiem tra su kien tu button */
void button(){
  int i = 0;
  int buttonState1 = digitalRead(button1);
  int buttonState2 = digitalRead(button2);
  int buttonState3 = digitalRead(button3);
  int buttonState4 = digitalRead(button4);
  int buttonState5 = digitalRead(button5);
  int buttonState6 = digitalRead(button6);
  int buttonState7 = digitalRead(button7);
  int buttonState8 = digitalRead(button8);
  int buttonState9 = digitalRead(button9);
  if(buttonState1 == LOW){
    while(digitalRead(button1) == LOW);
    Listbutton[0] = !Listbutton[0];
    Serial.println("Listbutton[0] : " + (String)Listbutton[0]);
    i = 1;
  }
  if(buttonState2 == LOW){
    while(digitalRead(button2) == LOW);
    Listbutton[1] = !Listbutton[1];
    i = 1;
  }
  if(buttonState3 == LOW){
    while(digitalRead(button3) == LOW);
    Listbutton[2] = !Listbutton[2];
    i = 1;
  }
  if(buttonState4 == LOW){
    while(digitalRead(button4) == LOW);
    Listbutton[3] = !Listbutton[3];
    i = 1;
  }
  if(buttonState5 == LOW){
    while(digitalRead(button5) == LOW);
    Listbutton[4] = !Listbutton[4];
    i = 1;
  }
  if(buttonState6 == LOW){
    while(digitalRead(button6) == LOW);
    Listbutton[5] = !Listbutton[5];
    i = 1;
  }
  if(buttonState7 == LOW){
    while(digitalRead(button7) == LOW);
    Listbutton[6] = !Listbutton[6];
    i = 1;
  }
  if(buttonState8 == LOW){
    while(digitalRead(button8) == LOW);
    Listbutton[7] = !Listbutton[7];
    i = 1;
  }
  if(buttonState9 == LOW){
    while(digitalRead(button9) == LOW);
    Listbutton[8] = !Listbutton[8];
    i = 1;
  }
  for(int i = 0;i<6;i++){
    if(Listbutton[i]){
      Liststatus[i] = "true";
    }else{
      Liststatus[i] = "false";
    }
  }
  if(i == 1){
    updateStatusServer();
  }
  i = 0;
}


/* function cap nhat trang thai len server */
void updateStatusServer(){
  mySerial.flush();
  Serial.flush();
  String JSONMessage = "{\"LED_STATUS\":["+Liststatus[0]+","+Liststatus[1]+","+Liststatus[2]+","+Liststatus[3]+","+Liststatus[4]+","+Liststatus[5]+","+Liststatus[6]+","+Liststatus[7]+","+Liststatus[8]+"]}";
  Serial.println("JSONMessage : " + JSONMessage);
  mySerial.print('\r');
  mySerial.print(JSONMessage);
  delay(500);
  JSONMessage = "";
}


void led() {
  Serial.println("LED");
  char *json = sCmd.next(); //Chỉ cần một dòng này để đọc tham số nhận đươc  Serial.println(tach[0]);
  Serial.println("LED");
  Capnhattrangthaitheoserver(json);
}

/* function slip String  */
void Capnhattrangthaitheoserver(String DataServer) {
    String result[9];
    int r=0, t=0;
    for (int i=0; i < DataServer.length(); i++)
    { 
      if(DataServer.charAt(i) == '['){
         r = i + 1;
      }
     if(DataServer.charAt(i) == ',') 
      { 
        result[t] = DataServer.substring(r, i); 
        r=(i+1); 
        t++; 
      }
      if(DataServer.charAt(i) == ']') 
      { 
        result[t] = DataServer.substring(r, i); 
        r=(i+1); 
        t++; 
      }
    }
    for(int runi = 0 ; runi < 9;runi++ ){
      Liststatus[runi] = result[runi];
    }
    Serial.println("TACH 1: " + Liststatus[0]);
    Serial.println("TACH 2: " + Liststatus[1]);
    Serial.println("TACH 3: " + Liststatus[2]);
    Serial.println("TACH 4: " + Liststatus[3]);
    Serial.println("TACH 5: " + Liststatus[4]);
    Serial.println("TACH 6: " + Liststatus[5]);
    Serial.println("TACH 7: " + Liststatus[6]);
    Serial.println("TACH 8: " + Liststatus[7]);
    Serial.println("TACH 9: " + Liststatus[8]);
    updateDedvice();
    
}
/***************************************************************
*                          UPDATE STATUS LIGHT
***************************************************************/
void updateDedvice(){
  for(int i = 0; i < 9; i++){
    if(Liststatus[i] == "true"){
      turn_on_device(i);
    }else{
      turn_off_device(i);
    }
  }
  updateStatusServer();
}

/***************************************************************
*                          TURN ON DEVICE 
***************************************************************/
void turn_on_device(int  device)
{
  Serial.println(F("TURN ON DEVICE ...."));
  switch(device)
  {
    case 1:
    {
      digitalWrite(DEN_PHONG_KHACH,HIGH);
      break;
    }
    case 2:
    {
      digitalWrite(DIEU_HOA_PHONG_KHACH,HIGH);
      break;
    }
    case 3:
    {
      digitalWrite(DEN_PHONG_NGU_1,HIGH);
      break;
    }
    case 4:
    {
      digitalWrite(DIEU_HOA_PHONG_NGU_1,HIGH);
      break;
    }
    case 5:
    {
      digitalWrite(DEN_PHONG_NGU_2,HIGH);
      break;
    }
    case 6:
    {
      digitalWrite(DIEU_HOA_PHONG_NGU_2,HIGH);
      break;
    }
    case 7:
    {
      digitalWrite(DEN_PHONG_BEP,HIGH);
      break;
    }
    case 8:
    {
      digitalWrite(QUAT_THONG_GIO_BEP,HIGH);
      break;
    }
  case 9:
    {
      digitalWrite(BINH_NONG_LANH,HIGH);
      break;
    }
  }
}
/***************************************************************
*                           TURN OFF DEVICE
***************************************************************/
void turn_off_device(char device)
{
  Serial.println(F("TURN OFF DEVICE...."));
  switch(device)
  {
    case 1:
    {
      digitalWrite(DEN_PHONG_KHACH,LOW);
      break;
    }
    case 2:
    {
      digitalWrite(DIEU_HOA_PHONG_KHACH,LOW);
      break;
    }
    case 3:
    {
      digitalWrite(DEN_PHONG_NGU_1,LOW);
      break;
    }
    case 4:
    {
      digitalWrite(DIEU_HOA_PHONG_NGU_1,LOW);
      break;
    }
    case 5:
    {
      digitalWrite(DEN_PHONG_NGU_2,LOW);
      break;
    }
    case 6:
    {
      digitalWrite(DIEU_HOA_PHONG_NGU_2,LOW);
      break;
    }
    case 7:
    {
      digitalWrite(DEN_PHONG_BEP,LOW);
      break;
    }
    case 8:
    {
      digitalWrite(QUAT_THONG_GIO_BEP,LOW);
      break;
    }
  case 9:
    {
      digitalWrite(BINH_NONG_LANH,LOW);
      break;
    }
  } 
}
