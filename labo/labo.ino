#define BTN_PIN 2
#include <LCD_I2C.h>
LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

unsigned long currentTime = 0;

uint8_t anchor[8] = {
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

  lcd.begin();
  lcd.backlight();





void loop() {
  currentTime = millis();
}


void debut(){
int i = 0;
if(i == 0){
  
}

}


