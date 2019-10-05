#include <WiFiUDP.h>
#include <ESP8266WiFi.h>
#include <OSCMessage.h>

static const char *ssid = "";
static const char *password = "";

static WiFiUDP udp;
static const char *ip_addr = "192.168.68.104";
static const int port = 8080;

static void wifi_setup()
{
    static const int local_port = 7000;

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
    udp.begin(local_port);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("");
    wifi_setup();
}

void loop()
{
    int value = system_adc_read();
    OSCMessage msg("/sensor");
    msg.add(value);

    udp.beginPacket(ip_addr, port);
    msg.send(udp);
    udp.endPacket();

    delay(50);
}
