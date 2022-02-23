#pragma once

#include <Arduino.h>  // for type definitions
#include <AddrMachine.h>

template<typename T>
class TemplateAddrMachine : public AddrMachine {
  private:
   const uint16_t addr = addrNext;       // Адрес Значения в памяти
    
  public:
    T v;                  //Значение (v - value)
  protected:  
    TemplateAddrMachine()
    : AddrMachine:: AddrMachine()
    {
      addrNext += sizeof(v);
    }
  public:  
    uint16_t getAddr();                 // Возвращает адрес класса
    uint16_t getSizeof();               // Возвращает размер занимаемый в памяти
    
    void Save();              // Сорранить данные в EEPROM
    void Load();              // Загрузить данные из EEPROM
};


///////////////////////////////////////////////////////////
// Save и Load Методы класса

  template <typename T>
  void TemplateAddrMachine<T>::Save() { 
    eepromWirte(this->addr,this->v);
    } 

  template <typename T>
  void TemplateAddrMachine<T>::Load() { 
    eepromRead(this->addr,this->v);
    }

///////////////////////////////////////////////////////////
// GET Методы класса

  // Возвращает адрес класса
  template <typename T>
  uint16_t TemplateAddrMachine<T>::getAddr(){ return this->addr; }
  
  // Возвращает размер занимаемый в памяти
  template <typename T>
  uint16_t TemplateAddrMachine<T>::getSizeof(){ return sizeof(this->v); }

/////////////////////////////////////////////////////////////////
/*
 *  Для массивов
 * 
 */
template<typename T, uint16_t SIZE>
class TemplateArrAddrMachine : public AddrMachine {
  private:
   const uint16_t addr = addrNext;       // Адрес Значения в памяти
    
  public:
    T v[SIZE];                  //Значение (v - value)
  protected: 
    TemplateArrAddrMachine()
    : AddrMachine:: AddrMachine()
    {
      addrNext += sizeof(v);
    }
  public:  
    uint16_t getAddr();                 // Возвращает адрес класса
    uint16_t getSizeof();               // Возвращает размер занимаемый в памяти
    
    void Save();              // Сорранить данные в EEPROM
    void Load();              // Загрузить данные из EEPROM

};

///////////////////////////////////////////////////////////
// Save и Load Методы класса

  template <typename T, uint16_t SIZE>
  void TemplateArrAddrMachine<T, SIZE>::Save() { 
    eepromWirte(this->addr,this->v);
    } 

  template <typename T, uint16_t SIZE>
  void TemplateArrAddrMachine<T, SIZE>::Load() { 
    eepromRead(this->addr,this->v);
    }
    
///////////////////////////////////////////////////////////
// GET Методы класса

  // Возвращает адрес класса
  template <typename T, uint16_t SIZE>
  uint16_t TemplateArrAddrMachine<T, SIZE>::getAddr(){ return this->addr; }
  
  // Возвращает размер занимаемый в памяти
  template <typename T, uint16_t SIZE>
  uint16_t TemplateArrAddrMachine<T, SIZE>::getSizeof(){ return sizeof(this->v); } 
