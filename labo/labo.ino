#define BTN_PIN 2 // allo
#include <LCD_I2C.h>
LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

unsigned long currentTime = 0;

uint8_t chiffre[8] = {
  0b11100,
  0b00100,
  0b11100,
  0b00100,
  0b11100,
  0b00111,
  0b00001,
  0b00001
};
uint8_t anchor[8] =
{
    0b01110,
    0b01010,
    0b01110,
    0b00100,
    0b10101,
    0b10101,
    0b01110,
    0b00100
};




void setup() {
  Serial.begin(115200);
start();




}

void loop() {
  currentTime = millis();
}

void start(){

  lcd.begin();
  lcd.backlight();
  lcd.createChar(2, chiffre);
   lcd.createChar(3, anchor);
  lcd.print("Blais");
  lcd.setCursor(0,1);
  lcd.write(3);
   lcd.write(2);

  delay(3000);

}





