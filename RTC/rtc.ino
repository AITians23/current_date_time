#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

// LCD address 0x27, 16 columns and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 rtc;

void setup() {
  Wire.begin();
  lcd.begin(16, 2, 0x00);  // <-- Corrected here
  lcd.backlight();

  if (!rtc.begin()) {
    lcd.print("RTC not found!");
    while (1);
  }

  // Uncomment this once to set RTC time to compile time:
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  DateTime now = rtc.now();

  lcd.setCursor(0, 0);
  lcd.print("Date: ");
  if (now.day() < 10) lcd.print("0");
  lcd.print(now.day());
  lcd.print('/');
  if (now.month() < 10) lcd.print("0");
  lcd.print(now.month());
  lcd.print('/');
  lcd.print(now.year());

  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  if (now.hour() < 10) lcd.print("0");
  lcd.print(now.hour());
  lcd.print(':');
  if (now.minute() < 10) lcd.print("0");
  lcd.print(now.minute());
  lcd.print(':');
  if (now.second() < 10) lcd.print("0");
  lcd.print(now.second());

  delay(1000);
}
