#include <LiquidCrystal.h>
// توصيلات شاشة LCD
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// توصيل البازر
const int buzzer = 8;

int sensorValue;

void setup()
{
  Serial.begin(9600); // ضبط منفذ السيريال بسرعة 9600
  lcd.begin(16, 2);   // تهيئة شاشة LCD بحجم 16x2
  lcd.print("Air Quality");
  lcd.setCursor(1, 0);
  lcd.print("  System");

  pinMode(A0, INPUT);  // ضبط مستشعر الهواء كمدخل
  pinMode(buzzer, OUTPUT); // ضبط البازر كمخرج
}

void loop()
{
  sensorValue = analogRead(A0); // قراءة قيمة مستشعر الهواء
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AQI: ");
  lcd.print(sensorValue);
  Serial.println(sensorValue);

  // تحليل جودة الهواء وعرض الرسالة
  if (sensorValue <= 180)
  { 
    lcd.setCursor(1, 1);
    lcd.print("Good ");
    digitalWrite(buzzer, LOW); // إيقاف البازر
  }
  else if (sensorValue >= 181 && sensorValue < 350)
  {
    lcd.setCursor(1, 1);
    lcd.print("Poor ");
    digitalWrite(buzzer, HIGH); // تشغيل البازر
  }
  else
  {
    lcd.setCursor(1, 1);
    lcd.print("Toxic ");
    digitalWrite(buzzer, HIGH); // تشغيل البازر
  }

  delay(3000); // تأخير لمدة 3 ثوانٍ
}
