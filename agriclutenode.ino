/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on NodeMCU.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right NodeMCU module
  in the Tools -> Board menu!

  For advanced settings please follow ESP examples :
   - ESP8266_Standalone_Manual_IP.ino
   - ESP8266_Standalone_SmartConfig.ino
   - ESP8266_Standalone_SSL.ino

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
//#define BLYNK_TEMPLATE_ID   "YourTemplateID"


#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>
#include "DHT.h"
#define DHTPIN D5 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
BlynkTimer timer;
char auth[] = "qbTmzab1z9ADEnsHeuOBj4GAbB6E-8BS";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "vivo 1723";
char pass[] = "244466666";
int soil=A0;
int soilval;
WidgetLED R(V3);
WidgetLED Y(V4);
WidgetLED G(V5);
int wat=D2;
int watvle;
int pmp=D1;




void setup()
{
  // Debug console
  Serial.begin(9600);
  timer.setInterval(1000,sen);
  pinMode(soil,INPUT);
  pinMode(wat,INPUT);
  pinMode(pmp,OUTPUT);
 timer.setInterval(3000,temp);
  
  

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  timer.run();
}
void sen()
{
  
  soilval=analogRead(soil);
  watvle=digitalRead(wat);
  
  
  Blynk.virtualWrite(V6,soilval);
   if(soilval>700)
  {
    
    R.on();
    Y.off();
    G.off();
    Blynk.virtualWrite(V2,"DRY");
    if(watvle==1)
    {
      Blynk.virtualWrite(V8,"PRESENT");
      digitalWrite(pmp,0);
      Blynk.virtualWrite(V7,"ON");
    }
      else
      {
        Blynk.virtualWrite(V8,"NOT_PRESENT");
        digitalWrite(pmp,1);
        Blynk.virtualWrite(V7,"OFF");
      }
      
    }
    
    else if(soilval>450 && soilval<500)
    {
    R.off();
    Y.on();
    G.off();
     Blynk.virtualWrite(V2,"MODERATE");
      if(watvle==1)
    {
      Blynk.virtualWrite(V8,"PRESENT");
      digitalWrite(pmp,0);
      Blynk.virtualWrite(V7,"ON");
    }
      else
      {
        Blynk.virtualWrite(V8,"NOT_PRESENT");
        digitalWrite(pmp,1);
        Blynk.virtualWrite(V7,"OFF");
      }
      
    }
    else if(soilval>300 && soilval<450)
    {
    R.off();
    Y.off();
    G.on();
      Blynk.virtualWrite(V2,"WET");
       if(watvle==1)
    {
      Blynk.virtualWrite(V8,"PRESENT");
      digitalWrite(pmp,1);
      Blynk.virtualWrite(V7,"OFF");
    }
      else
      {
        Blynk.virtualWrite(V8,"NOT_PRESENT");
        digitalWrite(pmp,1);
        Blynk.virtualWrite(V7,"OFF");
      }
    }
   
    
  }
  void temp()
  {
  float h = dht.readHumidity();
   float t = dht.readTemperature();
   if (isnan(h) || isnan(t))
   {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Blynk.virtualWrite(V9,h);
  Blynk.virtualWrite(V10,t);
  }
  
