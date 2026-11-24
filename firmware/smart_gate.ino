/*
  Smart Automatic Gate — HC-SR04 / SG90 Integration Prototype
  Mechatronics Final Project — Fall 2026

  Wiring:
    HC-SR04 TRIG -> D10, ECHO -> D11, VCC -> 5V, GND -> GND
    SG90 signal -> D9, red -> 5V, brown -> GND

  AI assistance: ChatGPT (OpenAI) helped draft and debug the control logic.
  Libraries: Arduino Servo library. Ultrasonic readings use pulseIn().
  Prototype only — not a safety-rated real gate.
  NOTE: No echo is treated as a clear path by this classroom test sketch.
        A real gate must fail safe on missing sensor data.
*/
#include <Servo.h>

const int trigPin = 10;
const int echoPin = 11;
const int servoPin = 9;
const int closedAngle = 0;
const int openAngle = 90;
const float openDistance = 15.0;
const float clearDistance = 20.0;
const unsigned long closeDelay = 2000;

Servo gateServo;
bool gateOpen = false;
bool clearTimerStarted = false;
unsigned long clearStartTime = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
  Serial.begin(9600);
  gateServo.attach(servoPin);
  gateServo.write(closedAngle);
  Serial.println("Smart Automatic Gate Started");
  Serial.println("Gate: CLOSED");
}

float measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  unsigned long duration = pulseIn(echoPin, HIGH, 25000UL);
  if (duration == 0) return -1;
  return duration * 0.0343 / 2.0;
}

void loop() {
  float distance = measureDistance();
  if (distance < 0) {
    Serial.println("No echo detected");
  } else {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  if (distance > 0 && distance <= openDistance) {
    clearTimerStarted = false;
    if (!gateOpen) {
      gateServo.write(openAngle);
      gateOpen = true;
      Serial.println("GATE OPENING");
    }
  } else if (gateOpen && (distance < 0 || distance >= clearDistance)) {
    if (!clearTimerStarted) {
      clearStartTime = millis();
      clearTimerStarted = true;
      Serial.println("Path clear - waiting 2 seconds");
    }
    if (millis() - clearStartTime >= closeDelay) {
      gateServo.write(closedAngle);
      gateOpen = false;
      clearTimerStarted = false;
      Serial.println("GATE CLOSING");
    }
  } else {
    clearTimerStarted = false;
  }
  delay(100);
}
