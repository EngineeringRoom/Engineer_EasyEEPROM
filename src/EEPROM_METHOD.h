#pragma once
#include <EEPROM.h>


#if defined(USE_EEPROM_AVR_METHOD)

  #define eepromWirte(addr, data)   EEPROM.put(addr, data);
  
  #define eepromRead(addr, data)    EEPROM.get(addr, data);
  
#elif defined(USE_EEPROM_ESP8266_METHOD)

  #define eepromWirte(addr, data)     \
      EEPROM.begin(AddrMachine::addrNext); \
      EEPROM.put(addr, data); \
      EEPROM.end();   
  
  #define eepromRead(addr, data)  \
      EEPROM.begin(AddrMachine::addrNext); \
      EEPROM.get(addr, data); \
      EEPROM.end();
#else
  #error "No eeprom method selected"
#endif
