/*
 * FRIDANS_ESP8266.ino
 *
 *  Created on: 2021-11-26
 *      Author: Rohaizan Roosley
 *
 */

#include <Arduino.h>
#include <arduino_homekit_server.h>
#include "wifi_info.h"

// Serial communications
bool dataIn = false;
String receivedCommand = "";

// Homekit
extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_current_position_x;
extern "C" homekit_characteristic_t cha_target_position_x;
extern "C" homekit_characteristic_t cha_position_state_x;
extern "C" homekit_characteristic_t cha_current_position_y;
extern "C" homekit_characteristic_t cha_target_position_y;
extern "C" homekit_characteristic_t cha_position_state_y;

void setup()
{
  Serial.begin(115200);
  Serial.setRxBufferSize(32);
  Serial.setDebugOutput(false);
  wifi_connect();
  my_homekit_setup();
}

void loop()
{
  my_homekit_loop();
  readSerial();
  wifi_status();
}

void my_homekit_setup()
{
  cha_target_position_x.setter = cha_target_position_x_set;
  cha_target_position_y.setter = cha_target_position_y_set;
  arduino_homekit_setup(&config);
  homekit_characteristic_notify(&cha_target_position_x, cha_target_position_x.value);
  homekit_characteristic_notify(&cha_target_position_y, cha_target_position_y.value);
}

void my_homekit_loop()
{
  arduino_homekit_loop();
}

void cha_target_position_x_set(const homekit_value_t value)
{
  cha_target_position_x.value.uint8_value = value.uint8_value;
  Serial.print("[homekitPositionX:");
  Serial.print(value.uint8_value);
  Serial.print("]");
}

void cha_target_position_y_set(const homekit_value_t value)
{
  cha_target_position_y.value.uint8_value = value.uint8_value;
  Serial.print("[homekitPositionY:");
  Serial.print(value.uint8_value);
  Serial.print("]");
}

void readSerial()
{
  while (Serial.available())
  {
    char c = Serial.read();
    if (c == '[')
    {
      receivedCommand = "";
      dataIn = true;
    }
    else if (dataIn && c != ']')
    {
      receivedCommand += c;
    }
    else if (dataIn && c == ']')
    {
      if (receivedCommand.substring(0, 17).equals("xfinish.position:"))
      {

        int currentPosition = receivedCommand.substring(17, receivedCommand.length()).toInt();
        uint8_t value = currentPosition;

        cha_current_position_x.value.uint8_value = value;
        cha_position_state_x.value.uint8_value = 2;

        homekit_characteristic_notify(&cha_current_position_x, cha_current_position_x.value);
        homekit_characteristic_notify(&cha_position_state_x, cha_position_state_x.value);
      }
      else if (receivedCommand.substring(0, 17).equals("yfinish.position:"))
      {

        int currentPosition = receivedCommand.substring(17, receivedCommand.length()).toInt();
        uint8_t value = currentPosition;

        cha_current_position_y.value.uint8_value = value;
        cha_position_state_y.value.uint8_value = 2;

        homekit_characteristic_notify(&cha_current_position_y, cha_current_position_y.value);
        homekit_characteristic_notify(&cha_position_state_y, cha_position_state_y.value);
      }
    }
  }
}
