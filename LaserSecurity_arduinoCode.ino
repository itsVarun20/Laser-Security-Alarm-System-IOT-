#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "auth_key";


char ssid[] = "name";
char pass[] =  "password";

int ledPin = 4;
int buzzerPin = 13;
int ldrPin = 12;
WidgetLED led1(V1);
WidgetLED led2(V2);
WidgetLED led3(V3);

void setup ()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  led1.on();
}


void sendEmail()
{

  String body = String("Laser Breached!!!");
  Blynk.email("user@gmail.com", "Subject: Alert", body);
}

// Notification
void notification()
{

  Blynk.notify("Laser is breached!!!");
}

void loop()
{

  int ldrStatus = analogRead(ldrPin);
  int i=0; 
  if(digitalRead(ldrPin))
  {
    led1.off();
    led2.on();
    led3.on();
    sendEmail();
    notification();
    a:

      tone(buzzerPin, 1000);
      digitalWrite(ledPin, HIGH);
      delay(100);
      noTone(buzzerPin);
      digitalWrite(ledPin, LOW);
      delay(100);
      i++;
      if(i<50)
      {
        goto a;
      }
    Serial.println("------ ALARM ACTIVATED-------");
  }
  else
  { 
    led2.off();
    led1.on();
    noTone(buzzerPin);
    digitalWrite(ledPin, LOW);
    Serial.println("ALARM DEACTIVATED");
  }
  Blynk.run();
}
