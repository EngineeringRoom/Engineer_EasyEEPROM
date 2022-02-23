#pragma once

#include <Arduino.h>  // for type definitions
#include <EEPROM_METHOD.h>

class AddrMachine {
  protected:
    static uint8_t Count;       // Счетчик количества экземпляров класса
    static uint16_t addrNext;   // Следующий свободный адрес в памяти
    static bool ReadFromMemory; // Флаг читать из памяти или нет
    static char CompilationDateTime[21];      // Время компиляции скетча
    static uint16_t addrCompilationDateTime;  // Адрес в памяти переменной CompilationDateTime
    

    
  protected:
// Конструктор класса
    AddrMachine() {
      Count++;
      // Только для первого экземпляра класса
      if (this->Count == 1){  
        CompilationDT();
        addrCompilationDateTime = addrNext;
        addrNext += sizeof(CompilationDateTime);
        CheckReadFromMemory();// Проверяем память (Поднимает флаг ReadFromMemory)
      }
    }
  public:  
  AddrMachine(const uint16_t &AddrFirst){
    setAddrFirst(AddrFirst);
  }
  
  private:
    void CheckReadFromMemory();    // Проверяем память (Поднимает флаг ReadFromMemory)
  
// Статические методы класса 
  private:
    static void     CompilationDT(); // Записыват время компиляции в статичискую переменную
    static void     setAddrFirst(const uint16_t &addrFirst);  // Устанавливает начальный адресс с которого записывать
  public:
    static void     setAllFactorySettingsAndRestarting();  // Сброс к заводским настройкам (Сработает при перезагрузке)
    static void     setAllFactorySettingsAndRestarting(void (&ResetMethod_callback)());  // Сброс к заводским настройкам и обратный вызов функции которая перезагрузит ваш Микроконтроллер
    static uint16_t getAddrNext();  // Возвращает следующий свободный адрес
 
    static char*   getCompilationDT();      // Возвращяет время компиляции скетча
    static bool    getReadFromMemory();     // Возвращяет флаг читать из памяти или нет 
    static uint8_t getCount();      // Возвращяет количество экземпляров класса

};

///////////////////////////////////////////////////////////
// SET Методы класса
  // Устанавливает начальный адресс с которого записывать
  void AddrMachine::setAddrFirst(const uint16_t &addrFirst){ addrNext = addrFirst; }

  // Сброс к заводским настройкам
  // и обратный вызов функции которая перезагрузит ваш Микроконтроллер
  void AddrMachine::setAllFactorySettingsAndRestarting(){ 
   eepromWirte(AddrMachine::addrCompilationDateTime, "NULL"); 
  }
  
  // Сброс к заводским настройкам
  // и обратный вызов функции которая перезагрузит ваш Микроконтроллер
  void AddrMachine::setAllFactorySettingsAndRestarting(void (&ResetMethod_callback)()){ 
   setAllFactorySettingsAndRestarting();
   ResetMethod_callback(); 
  }
  
  // Записыват время компиляции в статичискую переменную
  void AddrMachine::CompilationDT(){
      strcpy(CompilationDateTime,__DATE__);
      strcat(CompilationDateTime,"-");
      strcat(CompilationDateTime,__TIME__);
  }
  

///////////////////////////////////////////////////////////
// GET Методы класса
  
  // Возвращяет количество экземпляров класса
  uint8_t AddrMachine::getCount() { return Count; }

  // Возвращает следующий свободный адрес
  uint16_t AddrMachine::getAddrNext()  { return addrNext; }

  // Возвращяет время компиляции скетча
  char* AddrMachine::getCompilationDT()  { return CompilationDateTime; }

  // Возвращяет флаг читать из памяти или нет
  bool  AddrMachine::getReadFromMemory()  { return ReadFromMemory; }

  // Проверяем память (Поднимает флаг ReadFromMemory)
  void AddrMachine::CheckReadFromMemory(){
    char CompilationTimeFromMemory[21];
    eepromRead(AddrMachine::addrCompilationDateTime, CompilationTimeFromMemory);
    if (strcmp(CompilationTimeFromMemory, AddrMachine::CompilationDateTime) == 0) {
      AddrMachine::ReadFromMemory=true;
      }
    else {
      eepromWirte(AddrMachine::addrCompilationDateTime, AddrMachine::CompilationDateTime);
      }
  }
  
///////////////////////////////////////////////////////////
// Статические(общие) переменные класса
// Общие переменные для всех экземпляров класса

// Счетчик количества экземпляров класса
  uint8_t AddrMachine::Count=0;

// Следующий свободный адрес в памяти
// И заодно количество памяти которое нужно активировать
// при работе с EEPROM с ESP8266
  uint16_t AddrMachine::addrNext=0;

// Флаг читать из памяти или нет
  bool AddrMachine::ReadFromMemory = false;

// Время компиляции скетча
  char AddrMachine::CompilationDateTime[21]="NULL";
  uint16_t AddrMachine::addrCompilationDateTime=0;
