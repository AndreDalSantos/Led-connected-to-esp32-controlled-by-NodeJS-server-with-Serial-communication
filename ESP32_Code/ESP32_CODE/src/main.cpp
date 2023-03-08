#include <Arduino.h>

const short led = 14;
const short button = 14;

char led_status = 'd';

void ledControl();

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  ledControl();
  delay(100);
}

void ledControl()
{
  if (Serial.available() > 0)
  {
    String command = Serial.readStringUntil('\n');

    if (command == "1")
    {
      digitalWrite(led, HIGH);
      led_status = 'l';
    }
    else if (command == "0")
    {
      digitalWrite(led, LOW);
      led_status = 'd';
    }

    Serial.print(led_status);    
  }
}
