#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <rgb_lcd.h>

#define PIN 0
#define NUMPIXELS 4
#define SENSOR1 2
#define SENSOR2 3
#define SENSOR3 4
#define SENSOR4 5

rgb_lcd lcd;
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);
#define DELAYVAL 500

void setup() {
  //pinMode(PIN, OUTPUT);
  pinMode(SENSOR1, INPUT);
  pinMode(SENSOR2, INPUT);
  pinMode(SENSOR3, INPUT);
  pinMode(SENSOR4, INPUT);

  // LED Setup
  pixels.begin();
  pixels.setBrightness(128);
  pixels.setPixelColor(0, pixels.Color(255, 0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 255, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 255, 0));
  pixels.setPixelColor(3, pixels.Color(255, 255, 255, 255));
  pixels.show();

  // LCD Setup
  lcd.begin(16, 2);
  lcd.clear();
  lcd.home();
  lcd.setRGB(0, 255, 0);
  lcd.display();

  Serial.begin(9600);

  delay(1000);
}

uint8_t cooldown1 = 0;
uint8_t cooldown2 = 0;
uint8_t cooldown3 = 0;
uint8_t cooldown4 = 0;

void loop() {
  uint32_t green = pixels.Color(0, 255, 0, 255);
  uint32_t red = pixels.Color(255, 0, 0, 255);

  // check sensors
  bool detect1 = digitalRead(SENSOR1);
  bool detect2 = digitalRead(SENSOR2);
  bool detect3 = digitalRead(SENSOR3);
  bool detect4 = digitalRead(SENSOR4);

  if (detect1 || detect2 || detect3 || detect4) {
    lcd.setRGB(0, 255, 0);
  } else {
    lcd.setRGB(255, 0, 0);
  }

  // print out free parking spaces
  // " [3]  PARK  [2] "
  // " [4]  HERE  [1] "

  lcd.setCursor(1, 0);
  lcd.print(detect3 ? "[ ]" : "[X]");
  lcd.print("  PARK  ");
  lcd.print(detect2 ? "[ ]" : "[X]");

  lcd.setCursor(1, 1);
  lcd.print(detect4 ? "[ ]" : "[X]");
  lcd.print("  HERE  ");
  lcd.print(detect1 ? "[ ]" : "[X]");

  String result = String("LED: ");
  result = String(result + (detect1 ? "1 " : "0 "));
  result = String(result + (detect2 ? "1 " : "0 "));
  result = String(result + (detect3 ? "1 " : "0 "));
  result = String(result + (detect4 ? "1 " : "0 "));
  Serial.println(result);

  pixels.clear();
  pixels.setPixelColor(0, detect1 ? green : red);
  pixels.setPixelColor(1, detect2 ? green : red);
  pixels.setPixelColor(2, detect3 ? green : red);
  pixels.setPixelColor(3, detect4 ? green : red);
  pixels.show();

  delay(DELAYVAL);
}
