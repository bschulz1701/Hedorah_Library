#include <Hedorah.h>

Hedorah Sense; //Initalize Hedorah sensor

const unsigned long PeriodLog = 5000;
const unsigned long PeriodBaseline = 30000;

void setup() {
  Sense.begin(); //Initalize system
  Serial.begin(9600);
  while(!Serial); //Wait for serial to start

  Serial.println(Sense.GetHeader()); //Print out header for system
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
    Serial.println(Sense.GetString()); //Print new data point
    LocalTimeLog = millis(); //Reset local time
  }
  if(millis() - LocalTimeBaseline > PeriodBaseline) { //If baseline time triggered 
    Baseline = true; //Set flag
    LocalTimeBaseline = millis(); //Clear time value
  }
  delay(1); 
}
