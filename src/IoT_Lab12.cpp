/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/aiden/Desktop/IoT-Engineering/VisualStudioCodeProjects/IoT_Lab12/src/IoT_Lab12.ino"
/*
 * Project IoT_Lab12
 * Description:
 * Author:
 * Date:
 */

void callback(char *topic, byte *payload, unsigned int length);
void setup();
void loop();
#line 8 "c:/Users/aiden/Desktop/IoT-Engineering/VisualStudioCodeProjects/IoT_Lab12/src/IoT_Lab12.ino"
SYSTEM_THREAD(ENABLED);

#include "MQTT.h"
#include <blynk.h>
#include "oled-wing-adafruit.h"

OledWingAdafruit display;

#define LIGHT D7

String message;

void callback(char *topic, byte *payload, unsigned int length)
{
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;

    if (String(p).equals("1"))
    {
        digitalWrite(LIGHT, HIGH);
    }
    else if (String(p).equals("0"))
    {
        digitalWrite(LIGHT, LOW);
    }
    else if (String(p).equals("a"))
    {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Button A was pressed.");
        display.display();
    }
    else if (String(p).equals("b"))
    {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Button B was pressed.");
        display.display();
    }
    else if (String(p).equals("c"))
    {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Button C was pressed.");
        display.display();
    }
    else if (String(p) != message)
    {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println(String(p));
        display.display();
    }
}

MQTT client("lab.thewcl.com", 1883, callback);

BLYNK_WRITE(V1)
{
    message = param.asStr();
    client.publish("christianity", message);
}

void setup()
{
    Blynk.begin("K03uUDBp2fm0xabHSdhf2gbv0rGs08rf", IPAddress(167, 172, 234, 162), 8080);

    pinMode(LIGHT, OUTPUT);

    client.connect(System.deviceID());
    if (client.isConnected())
    {
        client.subscribe("christianity");
    }

    display.setup();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.display();
}

void loop()
{
    display.loop();
    Blynk.run();

    if (client.isConnected())
    {
        client.loop();
    }
    else
    {
        client.connect(System.deviceID());
        client.subscribe("christianity");
        client.subscribe("christianity/led");
        client.subscribe("christianity/button");
        client.publish("christianity", "HELLO Jesus!");
    }

    if (display.pressedA())
    {
        client.publish("christianity/buttons", "a");
    }
    else if (display.pressedB())
    {
        client.publish("christianity/buttons", "b");
    }
    else if (display.pressedC())
    {
        client.publish("christianity/buttons", "c");
    }
}