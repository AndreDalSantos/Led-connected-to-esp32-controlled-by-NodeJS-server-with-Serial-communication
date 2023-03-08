#include <Arduino.h>

const short led = 14;
const short button = 12;

void serialLedControl(char* led_status, char* last_led_status);
void buttonLedControl(char* led_status, char* last_led_status);

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  static char led_status = 'd';
  static char last_led_status = 0;

  serialLedControl(&led_status, &last_led_status);
  delay(100);
  buttonLedControl(&led_status, &last_led_status);
  delay(100);
}

void serialLedControl(char* led_status, char* last_led_status)
{
  if (Serial.available() > 0)
  {
    String command = Serial.readStringUntil('\n');

    if (command == "1")
    {
      digitalWrite(led, HIGH);
      *led_status = 'l';
    }
    else if (command == "0")
    {
      digitalWrite(led, LOW);
      *led_status = 'd';
    }

    if (*last_led_status != *led_status || command == "2")
    {
      Serial.print(*led_status);
      *last_led_status = *led_status;
    }
  }
}

void buttonLedControl(char* led_status, char* last_led_status)
{
  if (!digitalRead(button))
  {
    digitalWrite(led, !digitalRead(led));
    *led_status = *led_status == 'l' ? 'd' : 'l';
    delay(200);

    if (Serial.availableForWrite() > 0)
    {
      if (*last_led_status != *led_status)
      {
        Serial.print(*led_status);
        *last_led_status = *led_status;
      }
    }
  }
}
