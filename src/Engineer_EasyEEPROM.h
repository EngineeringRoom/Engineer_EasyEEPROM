#pragma once

#include <TemplateAddrMachine.h>

template<typename T>
class eepromVariable : public TemplateAddrMachine<T> {

  public:
    eepromVariable()
    : TemplateAddrMachine<T>:: TemplateAddrMachine()
    {
      if (AddrMachine::ReadFromMemory) {
        TemplateAddrMachine<T>::Load();
        }
      else {
        this->v = 0;
        TemplateAddrMachine<T>::Save();
        }
    }
    
    eepromVariable(const T v)
    : TemplateAddrMachine<T>:: TemplateAddrMachine()
    {
      if (AddrMachine::ReadFromMemory) {
        TemplateAddrMachine<T>::Load();
        }
      else {
        this->v = v;
        TemplateAddrMachine<T>::Save();
        }
    }
};


/////////////////////////////////////////////////////////////////
/*
 *  Для массивов
 * 
 */

template<typename T, uint16_t SIZE>
class eepromArrayVariable : public TemplateArrAddrMachine<T, SIZE> {

  public:
      eepromArrayVariable()
    : TemplateArrAddrMachine<T, SIZE>:: TemplateArrAddrMachine()
    {
      if (AddrMachine::ReadFromMemory) {
        TemplateArrAddrMachine<T, SIZE>::Load();
        }
      else {
        for (uint16_t i=0; i < SIZE; i++){
          this->v[i] = 0;
          }
        TemplateArrAddrMachine<T, SIZE>::Save();
        }
    }

    eepromArrayVariable(const T *v)
    : TemplateArrAddrMachine<T, SIZE>:: TemplateArrAddrMachine()
    {
      if (AddrMachine::ReadFromMemory) {
        TemplateArrAddrMachine<T, SIZE>::Load();
        }
      else {
        for (uint16_t i=0; i < SIZE; i++){
          this->v[i] = v[i];
          }
        TemplateArrAddrMachine<T, SIZE>::Save();
        }
    }
 
};

//////////////////////////////////
// Специализация Шаблона char[]

template<uint16_t SIZE>
class eepromArrayVariable<char, SIZE>: public TemplateArrAddrMachine<char, SIZE> {

  public:
    eepromArrayVariable()
    : TemplateArrAddrMachine<char, SIZE>:: TemplateArrAddrMachine()
    {
      if (AddrMachine::ReadFromMemory) {
        TemplateArrAddrMachine<char, SIZE>::Load();
        }
      else {
        strcpy(this->v, "");
        TemplateArrAddrMachine<char, SIZE>::TemplateArrAddrMachine::Save();
        }
    }

    
    eepromArrayVariable(const char *v)
    : TemplateArrAddrMachine<char, SIZE>:: TemplateArrAddrMachine()
    {
      if (AddrMachine::ReadFromMemory) {
        TemplateArrAddrMachine<char, SIZE>::Load();
        }
      else {
        strcpy(this->v, v);
        TemplateArrAddrMachine<char, SIZE>::Save();
        }
    }
    
};
