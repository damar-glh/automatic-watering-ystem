#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h> 
#endif

#define PIN 8
#define NUMPIXELS 16
#define DELAYVAL 1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int SMP = A1;
const int motor = 13;
const int LedRed = 12;
const int LedGreen = 11;
const int peizo = 9;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
  pixels.begin();
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Automatic");
  lcd.setCursor(0,1);
  lcd.print("Watering System!");
  delay(1500);
  pinMode(SMP, INPUT);
  pinMode(motor, OUTPUT);
  pinMode(peizo, OUTPUT);
  pinMode(LedRed, OUTPUT);
  pinMode(LedGreen, OUTPUT);
  lcd.clear();
  lcd.print("Moisture = ");
  lcd.setCursor(0,1);
  lcd.print("Motor ");
}

void Neoboard(float moisture) {
  if (moisture < 10) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, 255, 0, 0);
    }
    for (int j = 255; j > 0; j -= 2) {
      pixels.setBrightness(j);
      pixels.show();
    }
  } else if (moisture < 20) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, 255, 125, 5);
    }
    for (int j = 255; j > 0; j -= 2) {
      pixels.setBrightness(j);
      pixels.show();
    }
  } else if (moisture < 30) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, 255, 255, 0);
    }
    for (int j = 255; j > 0; j -= 2) {
      pixels.setBrightness(j);
      pixels.show();
    }
  } else if (moisture < 50) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, 0, 255, 0);
    }
    for (int j = 255; j > 0; j -= 2) {
      pixels.setBrightness(j);
      pixels.show();
    }
  } else if (moisture < 60) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, 130, 200, 250);
    }
    for (int j = 255; j > 0; j -= 2) {
      pixels.setBrightness(j);
      pixels.show();
    }
  } else if (moisture < 75) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, 31, 70, 220);
    }
    for (int j = 255; j > 0; j -= 2) {
      pixels.setBrightness(j);
      pixels.show();
    }
  } else {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, 20, 30, 250);
    }
    for (int j = 255; j > 0; j -= 2) {
      pixels.setBrightness(j);
      pixels.show();
    }
  }
}

void loop() {
  float value1 = analogRead(SMP);
  float Moisture = value1 * 1/8.75;

  lcd.setCursor(11,0);
  lcd.print(Moisture);
  lcd.setCursor(6,1);
  pixels.setBrightness(100);

  if (Moisture < 25) {
    tone(peizo, 100,200);
    delay(10);
    digitalWrite(motor, HIGH);
    digitalWrite(LedRed, HIGH);
    digitalWrite(LedGreen, LOW);
    lcd.print("ON ");
    delay(100);
  } else if (Moisture < 75) {
    digitalWrite(motor, LOW);
    digitalWrite(LedRed, LOW);
    digitalWrite(LedGreen, HIGH);
    lcd.print("OFF");
    delay(100);
  } else {
    digitalWrite(motor, LOW);
    digitalWrite(LedRed, LOW);
    digitalWrite(LedGreen, HIGH);
    lcd.print("OFF");
    delay(100);
  }

  Neoboard(Moisture);
  delay(100);
}
