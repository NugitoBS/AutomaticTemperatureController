#include <LiquidCrystal_I2C.h>
#include <DHT.h>

DHT dht(4, DHT22);
int lcdColumns = 16;
int lcdRows = 0;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  
#define RELAY_PIN 17

void setup(){
  lcd.init();
  lcd.backlight();
  dht.begin();
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
}

void loop(){
  float temp = dht.readTemperature();
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C");

  // === Relay Control ===
  if (!isnan(temp)) {
    if (temp > 20.00) {
      digitalWrite(RELAY_PIN, HIGH);
    } else {
      digitalWrite(RELAY_PIN, LOW);
    }
  }
  delay(1000);
  lcd.clear();
}