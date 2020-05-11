#include <Hedorah.h>

Hedorah Sense; //Initalize Hedorah sensor

const unsigned long PeriodLog = 5000;
const unsigned long PeriodBaseline = 30000;

void setup() {
  Sense.begin(); //Initalize system
  Serial.begin(9600);
  while(!Serial); //Wait for serial to start

  Serial.println("Tremble Before Hedorah!"); //Print out header for system
}

void loop() {
  static bool Baseline = true; //Used to trigger a baseline update, perform baseline update on POR
  static unsigned long LocalTimeLog = millis(); //Used to track local time relative to log period
  static unsigned long LocalTimeBaseline = millis(); //Used to track local time relative to baseline period
  if(millis() - LocalTimeLog > PeriodLog) { //If logging period is triggered 
    if(Baseline) { 
      Sense.UpdateBaseline(); //If flag is set, update values
      Baseline = false; //Clear flag
    }
    PrintData(); //Print out new line of data
    LocalTimeLog = millis(); //Reset local time
  }
  if(millis() - LocalTimeBaseline > PeriodBaseline) { //If baseline time triggered 
    Baseline = true; //Set flag
    LocalTimeBaseline = millis(); //Clear time value
  }
  delay(1); 
}

void PrintData() //Print out all data in single line
{
  PrintSensor("TVOC", String(Sense.GetTVOC()), "ppb");
  PrintSensor("eCO2", String(Sense.GeteCO2()), "ppm");
  PrintSensor("H2", String(Sense.GetH2()), "ppm");
  PrintSensor("Ethanol", String(Sense.GetEthanol()), "ppm");
  PrintSensor("RH", String(Sense.GetRH()), "%");
  PrintSensor("Temperature", String(Sense.GetTemperature()), "ºC");
  Serial.print("\n"); //Close with newline
}

void PrintSensor(String Name, String Data, String Unit) //Helper function for breaking up the print statments 
{
  Serial.print(Name);
  Serial.print(" = ");
  Serial.print(Data);
  Serial.print(" ");
  Serial.print(Unit);
  Serial.print("\t");
}
