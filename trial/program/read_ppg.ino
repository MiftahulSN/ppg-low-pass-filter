#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

MAX30105 ppg;

void setup() {
  Serial.begin(115200);

  if (!ppg.begin(Wire, I2C_SPEED_FAST)) // Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power.");
    delay(500);
    while (1);
  }

  byte ledBrightness = 0x1F; // Options: 0=Off to 255=50mA
  byte sampleAverage = 4; // Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 3; // Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  int sampleRate = 100; // Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 411; // Options: 69, 118, 215, 411
  int adcRange = 4096; // Options: 2048, 4096, 8192, 16384

  ppg.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);

  // Print header for CSV
  Serial.println("Timestamp,IR Value");
}

void loop() {
  float ir = ppg.getIR();
  unsigned long timestamp = millis();

  Serial.print(timestamp);
  Serial.print(",");
  Serial.println(ir);

  delay(100); 
}
