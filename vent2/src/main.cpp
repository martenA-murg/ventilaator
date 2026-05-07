#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Stepper.h>

#define ONE_WIRE_BUS 8
#define OUT1 7
#define OUT2 6
#define OUT3 5
#define OUT4 4

#define STEPS_PER_ROUND 2048

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Stepper stepper(STEPS_PER_ROUND, OUT1, OUT2, OUT3, OUT4);
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

void setup() {
  stepper.setSpeed(15);
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(100);
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  sensors.begin();
}


void loop() {
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);

  display.clearDisplay();
  display.setCursor(0, 0);

  Serial.print("Temperature = ");
  Serial.print(temp);
  Serial.println(" °C");

  display.print("Temp: ");
  display.print(temp);
  display.println(" C");

  if (temp >= 25) {
    display.println("");
    display.println("       VENT ON!");
    stepper.step(2048);
  } else {

  }

  display.display();

  delay(500);
}
