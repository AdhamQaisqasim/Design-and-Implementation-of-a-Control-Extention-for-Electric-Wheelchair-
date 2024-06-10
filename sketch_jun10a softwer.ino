#include <Wire.h>

const int MPU_ADDR = 0x68;

int16_t accelerometer_x, accelerometer_y;

#define RELAY_1 2 // Relay 1
#define RELAY_2 3// Relay 2
#define RELAY_3 4// Relay 3   b
#define RELAY_4 5// Relay 4  forward  g
#define RELAY_5 6// Relay 5   b
#define RELAY_6 7// Relay 6   b
void setup() {
  Serial.begin(9600);
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);
  pinMode(RELAY_5, OUTPUT);
  pinMode(RELAY_6, OUTPUT);
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);
  digitalWrite(RELAY_3, LOW);
  digitalWrite(RELAY_4, LOW);
  digitalWrite(RELAY_5, LOW);
  digitalWrite(RELAY_6, LOW);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 2 * 2, true);

  accelerometer_x = Wire.read() << 8 | Wire.read();
  accelerometer_y = Wire.read() << 8 | Wire.read();

  // Check the direction based on accelerometer readings
  if (accelerometer_x < -8000 && accelerometer_y < 3000) {
     //Moving LIFT
    digitalWrite(RELAY_1,HIGH );
    digitalWrite(RELAY_2, LOW);
    digitalWrite(RELAY_3, HIGH);
    digitalWrite(RELAY_4, LOW);
    digitalWrite(RELAY_5, HIGH);
    digitalWrite(RELAY_6, HIGH);
  } else if (accelerometer_x < 3000 && accelerometer_y > 8000) {
    // Moving forward
    digitalWrite(RELAY_1, LOW);
    digitalWrite(RELAY_2, LOW);
    digitalWrite(RELAY_3, HIGH);
    digitalWrite(RELAY_4, LOW);
    digitalWrite(RELAY_5, HIGH);
    digitalWrite(RELAY_6, HIGH);
  } else if (accelerometer_x > 8000 && accelerometer_y < 3000) {
    // Moving to the right
    digitalWrite(RELAY_1, LOW);
    digitalWrite(RELAY_2, HIGH);
    digitalWrite(RELAY_3, HIGH);
    digitalWrite(RELAY_4, LOW);
    digitalWrite(RELAY_5, HIGH);
    digitalWrite(RELAY_6, HIGH);
  } else if (accelerometer_x < 3000 && accelerometer_y < -8000) {
    // Moving to the BACK 
    digitalWrite(RELAY_1, HIGH);
    digitalWrite(RELAY_2, HIGH);
    digitalWrite(RELAY_3, LOW);
    digitalWrite(RELAY_4, HIGH);
    digitalWrite(RELAY_5, LOW);
    digitalWrite(RELAY_6, LOW);
  } else {
    // No specific direction, turn off all relays
    digitalWrite(RELAY_1, HIGH);
    digitalWrite(RELAY_2, HIGH);
    digitalWrite(RELAY_3, HIGH);
    digitalWrite(RELAY_4,HIGH);
    digitalWrite(RELAY_5, HIGH);
    digitalWrite(RELAY_6, HIGH);
  }

  Serial.println();
  
  delay(2000);
}