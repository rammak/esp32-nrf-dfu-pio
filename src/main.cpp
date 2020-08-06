#include <dfu.h>

esp32_dfu dfu;

void setup() {
  Serial.begin(115200);
  dfu.initialize();

}

void loop() {
  // put your main code here, to run repeatedly:

}
