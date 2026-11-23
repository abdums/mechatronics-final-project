/*
 * Smart Automatic Gate — INITIAL PROTOTYPE (NOT YET HARDWARE TESTED)
 * Mechatronics Final Project — Fall 2026
 *
 * Author: Student project (adapt and add your name)
 * References: Arduino Servo library and HC-SR04 sensor documentation.
 * AI assistance: Initial code draft and debugging assistance from ChatGPT.
 *
 * PROPOSED wiring:
 * HC-SR04 TRIG -> D6, ECHO -> D7, VCC -> 5V, GND -> GND
 * SG90 signal -> D9, red -> regulated 5V, brown -> GND
 * Use shared GND if powered from separate regulated supply.
 *
 * Safety: a lightweight classroom model only; not a real access-control system.
 */
#include <Servo.h>

const byte TRIG_PIN = 6;
const byte ECHO_PIN = 7;
const byte SERVO_PIN = 9;
const int CLOSED_ANGLE = 10;
const int OPEN_ANGLE = 100;
const float OPEN_DISTANCE_CM = 15.0f;
const float CLEAR_DISTANCE_CM = 20.0f;  // Hysteresis: avoids rapid switching.
const unsigned long SAMPLE_INTERVAL_MS = 100;
const unsigned long CLOSE_DELAY_MS = 2500;

Servo gate;
bool gateOpen = false;
unsigned long lastSample = 0;
unsigned long clearSince = 0;

float readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Timeout prevents waiting indefinitely for a missing echo.
  unsigned long echoUs = pulseIn(ECHO_PIN, HIGH, 25000UL);
  if (echoUs == 0) return -1.0f; // Invalid reading: don't close the gate.
  return echoUs * 0.0343f / 2.0f;
}

void openGate() {
  gate.write(OPEN_ANGLE);
  gateOpen = true;
  clearSince = 0;
  Serial.println("Gate OPEN");
}

void closeGate() {
  gate.write(CLOSED_ANGLE);
  gateOpen = false;
  clearSince = 0;
  Serial.println("Gate CLOSED");
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
  gate.attach(SERVO_PIN);
  closeGate();
}

void loop() {
  unsigned long now = millis();
  if (now - lastSample < SAMPLE_INTERVAL_MS) return;
  lastSample = now;

  float distanceCm = readDistanceCm();
  if (distanceCm < 0) {
    clearSince = 0; // Missing sensor data should not trigger closing.
    return;
  }

  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  if (distanceCm <= OPEN_DISTANCE_CM) {
    clearSince = 0;
    if (!gateOpen) openGate();
  } else if (distanceCm >= CLEAR_DISTANCE_CM && gateOpen) {
    if (clearSince == 0) clearSince = now;
    if (now - clearSince >= CLOSE_DELAY_MS) closeGate();
  } else {
    // Keep the current state in the 15–20 cm hysteresis band.
    clearSince = 0;
  }
}
