#include <SoftwareSerial.h>

// Ultrasonic Sensor 1 - Entry
#define TRIG1 2
#define ECHO1 3

// Ultrasonic Sensor 2 - Exit
#define TRIG2 4
#define ECHO2 5

// Buzzer
#define BUZZER 6

// HC-05 Bluetooth
// Arduino RX = D10, Arduino TX = D11
SoftwareSerial bluetooth(10, 11);

int peopleCount = 0;
const int MAX_CAPACITY = 20;   // Bus capacity limit

long distance1;
long distance2;

unsigned long lastEventTime = 0;
const unsigned long cooldown = 800; // ms gap before re-checking, avoids double count

long getDistance(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0)
    return 999;

  return duration * 0.034 / 2;
}

void fullAlertBeep()
{
  // Beeps only when the bus is full
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
    delay(100);
  }
}

void setup()
{
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);

  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW); // buzzer off by default

  Serial.begin(9600);
  bluetooth.begin(9600);

  Serial.println("Bus People Counter Started");
  bluetooth.println("Bus People Counter Started");
}

void loop()
{
  // Skip everything until cooldown has passed since the last count
  if (millis() - lastEventTime < cooldown) {
    return;
  }

  distance1 = getDistance(TRIG1, ECHO1);
  delay(50);
  distance2 = getDistance(TRIG2, ECHO2);

  // Object detected by Sensor 1 first -> possible entry
  if (distance1 < 10)
  {
    unsigned long startTime = millis();

    while (millis() - startTime < 2000)
    {
      distance2 = getDistance(TRIG2, ECHO2);
      if (distance2 < 10)
      {
        if (peopleCount < MAX_CAPACITY)
        {
          peopleCount++;
          // No beep here - buzzer stays off for normal entry

          Serial.print("Person Entered. Count = ");
          Serial.println(peopleCount);

          bluetooth.print("Person Entered. Count = ");
          bluetooth.println(peopleCount);

          // Check immediately after this entry: did it just become full?
          if (peopleCount == MAX_CAPACITY)
          {
            fullAlertBeep();
            Serial.println("Bus FULL!");
            bluetooth.println("Bus FULL!");
          }
        }
        else
        {
          // Someone tries to enter while already full
          fullAlertBeep();

          Serial.println("Bus FULL! Entry denied.");
          bluetooth.println("Bus FULL! Entry denied.");
        }

        break;
      }
    }

    lastEventTime = millis(); // start cooldown
    return; // skip exit-check this loop cycle
  }

  // Object detected by Sensor 2 first -> possible exit
  if (distance2 < 10)
  {
    unsigned long startTime = millis();

    while (millis() - startTime < 2000)
    {
      distance1 = getDistance(TRIG1, ECHO1);
      if (distance1 < 10)
      {
        if (peopleCount > 0)
          peopleCount--;

        // No beep here either - buzzer stays off for normal exit

        Serial.print("Person Exited. Count = ");
        Serial.println(peopleCount);

        bluetooth.print("Person Exited. Count = ");
        bluetooth.println(peopleCount);

        break;
      }
    }

    lastEventTime = millis();
    return;
  }

  delay(100);
}