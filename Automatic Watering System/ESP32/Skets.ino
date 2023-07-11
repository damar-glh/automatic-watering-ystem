#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHTesp.h"
#include <ESP32Servo.h>

const int DHT_PIN = 15;
const int SERVO_PIN = 18;
const int SERVO_MIN_ANGLE = 0;
const int SERVO_MAX_ANGLE = 180;
const int SERVO_STEP_DELAY = 10; // Delay antara setiap perubahan posisi servo (ms)
int Buzzer=12;

DHTesp dhtSensor;
LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C dan ukuran LCD
Servo myservo;


void setup() {
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  pinMode (Buzzer,OUTPUT);
  lcd.init(); // Inisialisasi LCD
  lcd.backlight(); // Nyalakan backlight
  lcd.print("Automatic");
  lcd.setCursor(0,1);
  lcd.print("Watering System!");
  delay(1500);
  lcd.clear();
  lcd.print("T = ");
  lcd.setCursor(9,0);
  lcd.print("H = ");
  lcd.setCursor(0,1);
  lcd.print("WP = ");
  myservo.attach(SERVO_PIN);
  myservo.write(90); // Posisi awal servo
}

void loop() {
  TempAndHumidity data = dhtSensor.getTempAndHumidity();

  lcd.setCursor(4, 0); // Atur posisi kursor LCD untuk suhu
  lcd.print(data.temperature, 1); // Cetak suhu

  lcd.setCursor(13, 0); // Atur posisi kursor LCD untuk kelembapan
  lcd.print(data.humidity, 1); // Cetak kelembapan

  if (data.temperature < 25 || data.humidity < 20) {
    for (int angle = myservo.read(); angle >= SERVO_MIN_ANGLE; angle--) {
      myservo.write(angle); // Menggerakkan servo ke posisi tertentu jika kondisi terpenuhi
      delay(SERVO_STEP_DELAY);
      lcd.setCursor(6,1);
      lcd.print("ON ");
    }
    tone(Buzzer,450);
    delay(50);
    noTone(Buzzer);
    delay(100);
  } else {
    for (int angle = myservo.read(); angle <= SERVO_MAX_ANGLE; angle++) {
      myservo.write(angle); // Menggerakkan servo ke posisi awal jika kondisi tidak terpenuhi
      delay(SERVO_STEP_DELAY);
      lcd.setCursor(6,1);
      lcd.print("OFF");
      digitalWrite(12, LOW); // Turn on the buzzer
      delay(SERVO_STEP_DELAY);
    }
  }
  
  Serial.println("Temperature: " + String(data.temperature, 1) + "°C");
  Serial.println("Humidity: " + String(data.humidity, 1) + "%");
  Serial.println("Servo Angle: " + String(myservo.read()) + "°");
  Serial.println("---");

  delay(2000);
}
