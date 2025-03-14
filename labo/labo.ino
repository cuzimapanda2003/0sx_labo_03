#define BTN_PIN 2
#include <LCD_I2C.h>
LCD_I2C lcd(0x27, 16, 2);  // Default address of most PCF8574 modules, change according
int photoresistence = A0;
int led = 8;
int button = 2;
int pinX = A1;
int pinY = A2;
int valX = 0;
int valY = 0;

unsigned long previousMillis = 0;
const long interval = 5000;

unsigned long previousMillis2 = 0;
const long interval2 = 100;

bool pharesON = false;
int luminosite;
const int referenceLuminosite = 512;

unsigned long currentTime = 0;

int compteur = 0;
int etatBouton = 0;
int dernierEtatBouton = 0;

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
  buttonPress();
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
  luminosite = analogRead(photoresistence);



  if (luminosite < referenceLuminosite) {
    if (!pharesON) {

      if (currentMillis - previousMillis >= interval) {
        pharesON = true;
        digitalWrite(led, HIGH);
      }
    } else {

      previousMillis = currentMillis;
    }
  }

  else {
    if (pharesON) {

      if (currentMillis - previousMillis >= interval) {
        pharesON = false;
        digitalWrite(led, LOW);
      }
    } else {

      previousMillis = currentMillis;
    }
  }
}

void afficherVitesse() {
  lcd.setCursor(0, 0);

  if (valX >= 0) {
    lcd.print("Avance : ");
  } else {
    lcd.print("Recule : ");
  }

  lcd.print(valX);

  if (valX >= -9 && valX <= 99) {
    lcd.print(" ");
  }

  if (valX >= -9 && valX <= 9) {
    lcd.print(" ");
  }

  lcd.setCursor(0, 1);
  lcd.print("Direction : ");

  if (valY > 506) {
    lcd.setCursor(13, 1);
    lcd.print("D");
  }
  if (valY < 506) {
    lcd.setCursor(13, 1);
    lcd.print("G");
  }
}
void direction() {
  valY = analogRead(pinY);
}
void vitesse() {
  valX = analogRead(pinX);

  if (valX < 511) {

    valX = map(valX, 0, 510, -25, 0);
  } else if (valX > 511) {

    valX = map(valX, 512, 1023, 0, 120);
  } else {

    valX = 0;
  }
}
void buttonPress() {
  etatBouton = digitalRead(button);

  if (etatBouton != dernierEtatBouton) {
    if (etatBouton == HIGH) {
      compteur++;
      lcd.clear();
    }
    dernierEtatBouton = etatBouton;
  }
  if (compteur % 2 != 0) {

    afficherLuminosite();
    surveillerLuminosite();
  } else {

    afficherVitesse();
    direction();
    vitesse();
  }
}
