#include <BleKeyboard.h>
#include <Arduino.h>

BleKeyboard bleKeyboard;

#define BUTTON_PIN 18   // GPIO 18 for BLE keyboard button
#define TRIG_PIN 5      // GPIO for ultrasonic sensor trigger
#define ECHO_PIN 4      // GPIO for ultrasonic sensor echo
#define BUZZER_PIN 19   // GPIO for buzzer

// Forward declaration of measureDistance
long measureDistance();

unsigned long lastKeyPressTime = 0; // To track the time of the last keystroke
const unsigned long keyPressInterval = 1000; // 1 second (1000 milliseconds) between keystrokes

void setup() {
  Serial.begin(115200);

  // Initialize BLE Keyboard
  bleKeyboard.begin();

  // Configure GPIO pins
  pinMode(BUTTON_PIN, INPUT_PULLDOWN); // Pull-down resistor for button
  pinMode(TRIG_PIN, OUTPUT);           // Trigger pin for ultrasonic sensor
  pinMode(ECHO_PIN, INPUT);            // Echo pin for ultrasonic sensor
  pinMode(BUZZER_PIN, OUTPUT);         // Buzzer pin

  digitalWrite(BUZZER_PIN, LOW);       // Ensure buzzer is off initially
}

void loop() {
  // BLE Keyboard functionality
  if (bleKeyboard.isConnected()) {
    if (digitalRead(BUTTON_PIN) == HIGH) {
      unsigned long currentTime = millis();
      if (currentTime - lastKeyPressTime >= keyPressInterval) {
        Serial.println("Button pressed, sending Ctrl + Alt + N");
        bleKeyboard.press(KEY_LEFT_CTRL);
        bleKeyboard.press(KEY_LEFT_ALT);
        bleKeyboard.press('n'); // 'n' key
        delay(10); // Small delay to ensure key press is recognized
        bleKeyboard.releaseAll();
        lastKeyPressTime = currentTime; // Update the last key press time
      }
    }
  }

  // Ultrasonic sensor functionality
  long distance = measureDistance();
  if (distance > 0 && distance <= 30) {
    // Obstacle detected within 30 cm, turn on buzzer
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println("Obstacle detected! Buzzer ON.");
  } else {
    // No obstacle or outside 30 cm range, turn off buzzer
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("No obstacle detected. Buzzer OFF.");
  }

  delay(50); // Small delay for debounce and processing
}

// Function to measure distance using ultrasonic sensor
long measureDistance() {
  // Send a 10us pulse to the trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the echo time
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Convert echo time to distance (cm)
  long distance = duration * 0.034 / 2; // Speed of sound: 343 m/s or 0.034 cm/us
  return distance;
}
