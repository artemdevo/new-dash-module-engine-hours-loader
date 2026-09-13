#include <EEPROM.h>
#include <Arduino.h>

const uint8_t ENGINE_HOURS_INTEGER_ADDRESS_0 = 4; //integer value is written into these two bytes, big endian, so address 0 is bigger
const uint8_t ENGINE_HOURS_INTEGER_ADDRESS_1 = 5;
const uint8_t ENGINE_HOURS_DECIMAL_ADDRESS_LOW = 6;
const uint8_t ENGINE_HOURS_DECIMAL_ADDRESS_HIGH = 25;//using 20 addresses for the decimal portion
const uint8_t TOTAL_ADDRESS_COUNT = 20; //20 addresses

const float engineRunTime = 2500.5; //THIS IS THE VALUE THAT WILL BE CHANGED. THIS REFLECTS THE TOTAL ENGINE RUNTIME. ONLY LIST TENTHS OF AN HOUR DUE TO FLOAT LIMIT
const uint16_t engineRunTimeWholeNumber = (uint16_t)engineRunTime;

void setup() {
   
  Serial.begin(115200);
  EEPROM.update(ENGINE_HOURS_INTEGER_ADDRESS_0, (engineRunTimeWholeNumber >> 8) & 0xFF);//big endian. typecasting to uint16_t to drop decimal
  EEPROM.update(ENGINE_HOURS_INTEGER_ADDRESS_1, engineRunTimeWholeNumber & 0xFF);

  uint16_t engineRunTimeDecimalToWholeNumber = round((engineRunTime - (float)engineRunTimeWholeNumber)*100);//isolate the decimal portion but converted to whole number. round() is for float error
  uint8_t difference = engineRunTimeDecimalToWholeNumber-((engineRunTimeDecimalToWholeNumber/TOTAL_ADDRESS_COUNT)*TOTAL_ADDRESS_COUNT); 
  //if the decimal as a whole number is divided by the address countand the value is a whole number, there is no difference
  Serial.println(difference);
  for(uint8_t i = ENGINE_HOURS_DECIMAL_ADDRESS_LOW; i <= ENGINE_HOURS_DECIMAL_ADDRESS_HIGH; i++){
    if(i < (difference+ENGINE_HOURS_DECIMAL_ADDRESS_LOW)){
      EEPROM.update(i, (engineRunTimeDecimalToWholeNumber/TOTAL_ADDRESS_COUNT)+1);
    }
    else{
      EEPROM.update(i, engineRunTimeDecimalToWholeNumber/TOTAL_ADDRESS_COUNT);
    }
  }
  
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
