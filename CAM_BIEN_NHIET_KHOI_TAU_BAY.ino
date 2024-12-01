
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
int speaker = 7;                 // chân điều khiển còi
int khoi = 9;                    // out ket noi Pin 9
int led = 8;                     // chân đèn báo
int nhiet = A0;                  // Thiết lập chân nhận tín hiệu đo nhiệt độ
float maxs = 60;                 //Thiết lập nhiệt độ cảnh báo
void setup() {
  pinMode(nhiet, INPUT);
  pinMode(khoi, INPUT);
  pinMode(speaker, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("CAM BIEN TAU BAY");
  lcd.setCursor(0, 1);
  lcd.print("SV: NGUYEN LONG VU");
}
void loop() {
  int v = analogRead(nhiet);
  float te = v*5.0/ 1024.0;
  float t = te * 100.0;
  lcd.setCursor(0, 2);
  lcd.print("NHIET DO:         *C");
  lcd.setCursor(10, 2);
  lcd.print(t);
  if (digitalRead(khoi) == 1 && t < maxs) {
    lcd.setCursor(0, 3);
    lcd.print(" PHAT HIEN CO KHOI  ");
      digitalWrite(speaker, 1);
      digitalWrite(led, 1);
      delay(300);
      digitalWrite(speaker, 0);
      digitalWrite(led, 0);
      delay(300);
    
  }
  if (digitalRead(khoi) == 0 && t >= maxs) {
    lcd.setCursor(1, 3);
    lcd.print("  NHIET DO QUA LON  ");
      digitalWrite(speaker, 1);
      digitalWrite(led, 1);
      delay(300);
      digitalWrite(speaker, 0);
      digitalWrite(led, 0);
      delay(300);
    
  }
  if (digitalRead(khoi) == 0 && t < maxs) {
    lcd.setCursor(1, 3);
    lcd.print("HE THONG BINH THUONG");
    digitalWrite(speaker, 0);
    digitalWrite(led, 0);
  }
  if (digitalRead(khoi) == 1 && t >= maxs) {
      lcd.setCursor(0, 3);
      lcd.print(" CANH BAO NGUY HIEN ");
      digitalWrite(speaker, 1);
      digitalWrite(led, 1);
      delay(500);
      lcd.setCursor(0, 3);
      lcd.print("   CO KHOI VA LUA   ");
      delay(500);
    
  }
}
