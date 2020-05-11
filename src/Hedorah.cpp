/******************************************************************************
Hedorah.cpp
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

#include <Wire.h> // Wire library is used for I2C
#include "Hedorah.h"

Hedorah::Hedorah()
// Base library type I2C
{
}


uint8_t Hedorah::begin()
{
    //Only use isEnabled() if using particle
    #if defined(ARDUINO) && ARDUINO >= 100 
        Wire.begin();
    #elif defined(PARTICLE)
        if(!Wire.isEnabled()) Wire.begin(); //Only initialize I2C if not done already //INCLUDE FOR USE WITH PARTICLE 
    #endif
    Gas.begin();
    RH.begin();
}

uint16_t Hedorah::GetTVOC() 
{
    if(!Gas.IAQmeasure()) return 0; //Grab new values, if error, return error value //FIX! Don't call everytime, return error better 
    return Gas.TVOC; //Otherwise return TVOC data
}

uint16_t Hedorah::GeteCO2()
{
    if(!Gas.IAQmeasure()) return 0; //Grab new values, if error, return error value //FIX! Don't call everytime, return error better 
    return Gas.eCO2; //Otherwise return eCO2 data
}

uint16_t Hedorah::GetH2()
{
    if(!Gas.IAQmeasureRaw()) return 0; //Grab new values, if error, return error value //FIX! Don't call everytime, return error better 
    return Gas.rawH2; //Otherwise return H2 data
}

uint16_t Hedorah::GetEthanol()
{
    if(!Gas.IAQmeasureRaw()) return 0; //Grab new values, if error, return error value //FIX! Don't call everytime, return error better 
    return Gas.rawEthanol; //Otherwise return H2 data
}

float Hedorah::GetTemperature() //Returns temp in C from SHTC3
{
    float AtmosData[2] = {0}; //Create array for envrio data
    RH.Wake(); //Wake RH sensor
    bool Error = RH.GetData(AtmosData); //Read data from sensor into array, grab I2C status
    RH.Sleep(); //Sleep sensor again to reduce power
    if(Error == 0) return AtmosData[1]; //If no error, return temp value
    else return -9999.0; //Else return error condition 
}


float Hedorah::GetRH() //Return RH in % from SHTC3
{
    float AtmosData[2] = {0}; //Create array for envrio data
    RH.Wake(); //Wake RH sensor
    bool Error = RH.GetData(AtmosData); //Read data from sensor into array, grab I2C status
    RH.Sleep(); //Sleep sensor again to reduce power
    if(Error == 0) return AtmosData[0]; //If no error, return RH value
    else return -9999.0; //Else return error condition 
}

bool Hedorah::UpdateBaseline(uint16_t eCO2_base, uint16_t TVOC_base)
{
    return ~Gas.getIAQBaseline(&eCO2_base, &TVOC_base); //Check error state, recalculate baseline, return status 
}

String Hedorah::GetHeader() 
{
    return "TVOC [ppb], eCO2 [ppm], H2 [ppm], Ethanol [ppm], Relative Humidity [%], Air Temperature [ºC],"; //return header string
}

String Hedorah::GetString()
{
    return String(GetTVOC()) + "," + String(GeteCO2()) + "," + String(GetH2()) + "," + String(GetEthanol()) + "," + String(GetRH()) + "," + String(GetTemperature()) + ","; //Return concatenated data string
}
