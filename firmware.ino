#include <Keyboard.h>
#include <EEPROM.h>

int toggleMode()
{
  if (digitalRead(9) == HIGH)
  {
    return 1;
  }
  else if (digitalRead(9) == LOW)
  {
    return 0;
  } 
}

float bottomCal()
{
  bool bottom = false;
  float sumBot = 0;

  if (bottom == false)
    {
      Serial.println("Hold Down Switch Fully");
      delay(1000);

      for (int i = 0; i < 5; i++)
      {
        sumBot += analogRead(A1) * (5 / 1023.0);
        delay(1000);
      }

      bottom = true;
      float calBot = sumBot / 5;
      Serial.println(calBot);
      return calBot;
    }
}

float topCal()
{
  bool top = false;
  float sumTop = 0;

  if (top == false)
  {
    Serial.println("Release Switch Fully");
    delay(1000);

    for (int i = 0; i < 5; i++)
    {
      sumTop += analogRead(A1) * (5 / 1023.0);
      delay(1000);
    }
    top = true;
    float calTop = sumTop / 5;
    Serial.println(calTop);
    return calTop;
  }
}

float distanceIndex(float t, float b)
{
  float temp = t - b;
  float mmVoltage = temp / 40;
  return mmVoltage;
}

void regKey(float v, float aD, float mmV, float bV)
{
  if (v < (aD * mmV) + bV)
    {
      Keyboard.press(120);
    }
  else
    {
      Keyboard.release(120);
    }
}

void rapidTrigger(unsigned long t, unsigned long pT)
{
  while(1)
  {
    t = micros();
  }
}

//Global Variables
float mmVolt = EEPROM.get(0, mmVolt);
float botVoltage = EEPROM.get(4, botVoltage);
float topVoltage = EEPROM.get(8, topVoltage);
float hysteresis = 1;
bool rapidTrig = true;
float lowVoltage = topVoltage - hysteresis * mmVolt;
float highVoltage;

void setup(){
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(10, INPUT);
  Keyboard.begin();
}

void loop() {
  //Calibration Variables
  float actuationDistance = 20;

  //ON/OFF switch
  digitalWrite(9, HIGH);
  int mode = toggleMode();

  //Voltage Information
  float voltage;
  voltage = analogRead(A0) * (5 / 1023.0);
  float voltage1 = voltage;
  Serial.println(voltage);

  //Rapid Trigger Variables

  if (digitalRead(10) == HIGH)
  {
    botVoltage = bottomCal();
    float topVoltage = topCal();
    mmVolt = distanceIndex(topVoltage, botVoltage);
    //Serial.println(mmVolt);

    EEPROM.put(0, mmVolt);
    EEPROM.put(4, botVoltage);
    EEPROM.put(8, topVoltage);
  }

  //Regular Keyboard 
  if (mode == 1)
  {
    if (rapidTrig == false)
    {
      regKey(voltage, actuationDistance, mmVolt, botVoltage);
    }
    else if (rapidTrig == true)
    {
      //Find highest and lowest points of a press, lowest is for release, highest is for press
      if (voltage < lowVoltage)
      {
        lowVoltage = voltage;
      }

      if (voltage > highVoltage)
      { 
        highVoltage = voltage;
      } 

      //If switch position is higher than the lowest voltage plus a threshold release the key
      if (voltage > lowVoltage + hysteresis * mmVolt)
      {
        Keyboard.release(120);
        lowVoltage = voltage;
      }

      //If switch position is lower than the highest point plus a threshold press the key 
      if (voltage < highVoltage - hysteresis * mmVolt)
      {
        Keyboard.press(120);
        highVoltage = voltage;
      }
    }
  }
}


