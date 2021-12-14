/*
 * wifi_info.h
 *
 *  Created on: 2020-05-15
 *      Author: Mixiaoxiao (Wang Bin)
 *      
 *  Modified on: 2021-11-26
 *      Author: Rohaizan Roosley
 *      
 */

#ifndef WIFI_INFO_H_
#define WIFI_INFO_H_

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif

const char *ssid = "";
const char *password = "";

void wifi_connect()
{
	WiFi.persistent(false);
	WiFi.mode(WIFI_STA);
	WiFi.setAutoReconnect(true);
  	WiFi.hostname("Fridans");
	WiFi.begin(ssid, password);
	Serial.println("WiFi connecting...");
	while (!WiFi.isConnected())
	{
		delay(100);
		Serial.print(".");
	}
	Serial.print("\n");
	Serial.printf("WiFi connected, IP: %s\n", WiFi.localIP().toString().c_str());
}

void wifi_status()
{
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("[isWifiConnection:1]");
  } else {
    Serial.print("[isWifiConnection:0]");
  }
}

#endif /* WIFI_INFO_H_ */
