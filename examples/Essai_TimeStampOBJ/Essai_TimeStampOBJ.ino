#include <Wire.h>
#include "TimeOBJ.h"
#include "TimeStampOBJ.h"

TimeOBJ time_now = TimeOBJ();
TimeStampOBJ objTimeStamp = TimeStampOBJ();


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  objTimeStamp.compute();
}

void loop() {
  objTimeStamp.compute();
  time_now = objTimeStamp.get();
  time_now.print();
  delay(1000);
}
