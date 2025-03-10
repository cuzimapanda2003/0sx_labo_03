#define BTN_PIN 2
#include <LCD_I2C.h>
LCD_I2C lcd(0x27, 16, 2);    // Default address of most PCF8574 modules, change according
int photoresistence = A0;
int led = 8;
int button = 2;
int pinX = A1;
int pinY = A2;
int valX = 0;
int valY = 0;

unsigned long previousMillis = 0; 
const long interval = 5000;       
bool pharesON = false;         
int luminosite;                   


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
  start();
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(photoresistence, INPUT);
}

void loop() {
  currentTime = millis();

  afficherLuminosite();

  surveillerLuminosite();
}

void start() {

  lcd.begin();
  lcd.backlight();
  lcd.createChar(2, chiffre);
  lcd.createChar(3, anchor);
  lcd.print("Blais");
  lcd.setCursor(0, 1);
  lcd.write(3);
  lcd.write(2);

  delay(3000);
}

void afficherLuminosite() {
  lcd.setCursor(0, 0);
  lcd.print("Luminosite: ");
  lcd.print(map(luminosite, 0, 1023, 0, 100));  // Convertir en pourcentage
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Phares: ");
  lcd.print(pharesON ? "ON " : "OFF");
}

void surveillerLuminosite() {
  unsigned long currentMillis = millis();


  if (luminosite < 512) {
    if (currentMillis - previousMillis >= interval) {
      if (!pharesON) {
        pharesON = true;
        digitalWrite(led, HIGH);
      }
    }
  } else {
    previousMillis = currentMillis;
  }


  if (luminosite > 512) {
    if (currentMillis - previousMillis >= interval) {
      if (pharesON) {
        pharesON = false;
        digitalWrite(led, LOW);
      }
    }
  } else {
    previousMillis = currentMillis;
  }
}
