/******************************************************************************
Hedorah.h
Library for Hedorah gas sensor breakout, along with temp and RH for compensation and basic data 
Bobby Schulz @ Northern Widget LLC
5/9/2018
Hardware info located at: https://github.com/NorthernWidget/TP-DownHole

Hedora is a compact breakout board which contains a SGP30 gas sensor and a SHTC3 temperature and RH sensor 

"Size matters not. Look at me. Judge me by my size do you? And well you should not. For my ally is the
Force, and a powerful ally it is"
-Yoda

Distributed as-is; no warranty is given.
******************************************************************************/

#ifndef Hedorah_h
#define Hedorah_h

//Conditionally include to make compatible with Particle 
#if defined(ARDUINO) && ARDUINO >= 100
    #include <Arduino.h>
    #include <Wire.h>
#elif defined(PARTICLE)
    #include <Particle.h>
#endif

#include "Adafruit_SGP30.h"
#include "SHTC3.h"

class Hedorah
{
public:
    Hedorah();  // Constructor
    uint8_t begin(); // Collect address value, use default
    uint16_t GetTVOC();
    uint16_t GeteCO2();
    uint16_t GetH2();
    uint16_t GetEthanol();
    float GetTemperature();
    float GetRH();
    bool UpdateBaseline(uint16_t eCO2_base = NULL, uint16_t TVOC_base = NULL); //Discard values if not passed in
    String GetHeader();
    String GetString();

private:
    SHTC3 RH; //Humidity sensor instance
    Adafruit_SGP30 Gas; //Gas sensor instance 
};

#endif
