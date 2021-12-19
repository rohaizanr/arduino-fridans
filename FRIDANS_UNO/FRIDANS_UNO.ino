/*
 * FRIDANS_UNO.ino
 *
 *  Created on: 2021-11-26
 *      Author: Rohaizan Roosley
 *
 */
#include <AccelStepper.h>

// Wifi Ready Pin
#define WIFI_READY_PIN 12

// Stepper Motor X
#define MOTOR_X_ENABLE_PIN 8
#define MOTOR_X_STEP_PIN 2
#define MOTOR_X_DIR_PIN 5
AccelStepper motorX(1, MOTOR_X_STEP_PIN, MOTOR_X_DIR_PIN);

// Stepper Motor Y
#define MOTOR_Y_ENABLE_PIN 9
#define MOTOR_Y_STEP_PIN 3
#define MOTOR_Y_DIR_PIN 6
AccelStepper motorY(1, MOTOR_Y_STEP_PIN, MOTOR_Y_DIR_PIN);

// I need 10 revolutions to open/close the window blinds, therefore (12 * 200) * 3 (gear ratio)
const int MAX_STEPPER_POSITION=7200;

// Serial communication
bool dataIn = false;
String receivedCommand = "";
bool motorXBusy = false;
bool motorYBusy = false;
bool homekitXUpdated = true;
bool homekitYUpdated = true;

void setup()
{
  Serial.begin(115200);

  pinMode(WIFI_READY_PIN, OUTPUT);
  pinMode(MOTOR_X_ENABLE_PIN, OUTPUT);
  pinMode(MOTOR_Y_ENABLE_PIN, OUTPUT);

  motorX.setEnablePin(MOTOR_X_ENABLE_PIN);
  motorX.setAcceleration(250);
  motorX.setMaxSpeed(500);
  motorX.enableOutputs();
  motorX.setCurrentPosition(0);

  motorY.setEnablePin(MOTOR_Y_ENABLE_PIN);
  motorY.setAcceleration(250);
  motorY.setMaxSpeed(500);
  motorY.enableOutputs();
  motorY.setCurrentPosition(0);
}

void loop()
{
  readSerial();
  stepperLoop();
}

void stepperLoop()
{
  motorX.run();
  if (!motorX.isRunning() && !homekitXUpdated)
  {
    int homekitValue = stepperPositionToHomekitValue(motorX.currentPosition());
    Serial.print("[xfinish.position:");
    Serial.print(homekitValue);
    Serial.print("]");
    motorXBusy = false;
    homekitXUpdated = true;
  }

  motorY.run();
  if (!motorY.isRunning() && !homekitYUpdated)
  {
    int homekitValue = stepperPositionToHomekitValue(motorY.currentPosition());
    Serial.print("[yfinish.position:");
    Serial.print(homekitValue);
    Serial.print("]");
    motorYBusy = false;
    homekitYUpdated = true;
  }
}

void moveX(int homekitPositionX)
{
  motorXBusy = true;
  homekitXUpdated = false;
  int position = homekitValueToStepperPosition(homekitPositionX);

  motorX.moveTo(position);
}

void moveY(int homekitPositionY)
{
  motorYBusy = true;
  homekitYUpdated = false;
  int position = homekitValueToStepperPosition(homekitPositionY);

  motorY.moveTo(position);
}

int homekitValueToStepperPosition(int targetPosition)
{
  int step = (targetPosition == 0) ? 0 : MAX_STEPPER_POSITION / 100;
  return targetPosition * step;
}

int stepperPositionToHomekitValue(int position)
{
  float result = (position == 0) ? 0 : ((float)position / (float)MAX_STEPPER_POSITION) * 100;
  result = round(result);
  return (int)result;
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
      if (receivedCommand.substring(0, 17).equals("homekitPositionX:"))
      {
        int targetPositionX = receivedCommand.substring(17, receivedCommand.length()).toInt();
        int currentPositionX = stepperPositionToHomekitValue(motorX.currentPosition());
        
        if (targetPositionX != currentPositionX && !motorXBusy)
        {
          moveX(targetPositionX);
        }
      }
      else if (receivedCommand.substring(0, 17).equals("homekitPositionY:"))
      {
        int targetPositionY = receivedCommand.substring(17, receivedCommand.length()).toInt();
        int currentPositionY = stepperPositionToHomekitValue(motorY.currentPosition());
        
        if (targetPositionY != currentPositionY && !motorYBusy)
        {
          moveY(targetPositionY);
        }
      }
      else if (receivedCommand.substring(0, 17).equals("isWifiConnection:"))
      {
        int status = receivedCommand.substring(17, receivedCommand.length()).toInt();
        
        (status == 0) ? digitalWrite(WIFI_READY_PIN, LOW) : digitalWrite(WIFI_READY_PIN, HIGH);
      }
    }
  }
}
