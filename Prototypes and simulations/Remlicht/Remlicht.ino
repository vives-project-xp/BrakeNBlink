#include <Arduino_BMI270_BMM150.h>

  const int led4 = 5;

void setup() {

  Serial.begin(115200);
  while (!Serial);
  if (!IMU.begin()) {
    Serial.println("IMU init failed!"); while (1);
  }
  delay(150);
}

void loop() {
  pinMode(led4, OUTPUT);
  float ax, ay, az, gx, gy, gz;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);

    Serial.print(-2.0); 
    Serial.print(",");
    Serial.print(0.5);
    Serial.print(",");

    if (ax < -0.20) {
      Serial.println(ax); 
      digitalWrite(led4, HIGH);
    } else {
      Serial.println(0.0);
      digitalWrite(led4, LOW);
    }

    delay(10); 
  }

  Serial.println("----------------------");
  delay(100);
}