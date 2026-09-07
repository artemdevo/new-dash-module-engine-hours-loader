#include <EEPROM.h>
#include <Arduino.h>

const uint8_t ENGINE_HOURS_INTEGER_ADDRESS_0 = 4; //integer value is written into these two bytes, big endian, so address 0 is bigger
const uint8_t ENGINE_HOURS_INTEGER_ADDRESS_1 = 5;
const uint8_t ENGINE_HOURS_DECIMAL_ADDRESS_LOW = 6;
const uint8_t ENGINE_HOURS_DECIMAL_ADDRESS_HIGH = 25;//using 20 addresses for the decimal portion

const float engineRuntime = 1800.7; //THIS IS THE VALUE THAT WILL BE CHANGED. THIS REFLECTS THE TOTAL ENGINE RUNTIME

void setup() {
  EEPROM.update(ENGINE_HOURS_INTEGER_ADDRESS_0, ((uint16_t)engineRuntime >> 8) & 0xFF);//big endian. typecasting to uint16_t to drop decimal
  EEPROM.update(ENGINE_HOURS_INTEGER_ADDRESS_1, (uint16_t)engineRuntime & 0xFF);

}

void loop() {
  // put your main code here, to run repeatedly:

}
