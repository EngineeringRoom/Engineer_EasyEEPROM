/*
 *  Пример с Массивами
 *  Посмотрите обязательно пример Variables
 *  а потом возвращайтесь
 *  
 * Объявляем экземпляры класса
 * 
 *   eepromArrayVariable<тип переменной, SIZE> имя;       // Value = 0 Ноль поумолчанию
 *   
 * или
 * 
 *   const тип переменной Value[] = 25;                   // Задавайте именно const что бы не жрать аперативку
 *   eepromArrayVariable<тип переменной, SIZE> имя(Value); 
 * 
 * Value - при этом будет заводской настройкой то есть если сбросить флаг и перезагрузить
 *         контроллер, то память будет опять инициализированна этим значением 
 * SIZE  - размер массива
 */

//#define USE_EEPROM_ESP8266_METHOD   // Раскоментируйте если пользуютесь ESP8266
#define USE_EEPROM_AVR_METHOD         // Раскоментируйте если пользуютесь Arduino
#include <Engineer_EasyEEPROM.h>

//AddrMachine FirstAddr(50);          // Так можно задать первый адрес в EEPROM (по умолчанию 0)

#include "EasyPrintInfo.h"            // Тут функции что бы удобно выводить в монитор порта
                                      // Это все не относится к примеру, но то де стоит изучить

// Объявим разные переменные  
eepromArrayVariable<bool, 3> Bool1;        // Будет false по умолчанию

const bool cBool[5] = {0,1,0,1,0};
eepromArrayVariable<bool, 5> Bool2(cBool); // Задаем массив cBool[5] значений по умолчанию


eepromArrayVariable<int, 7> Int1;                // Будет 0 по умолчанию

eepromArrayVariable<int16_t, 5> Int2((int16_t[]){ 5, 25, 125, 245, 345 });     // Задаем массив по умолчанию

const int16_t cInt3[3] = {10,20,30};             // Мне кажется это лучший способ
eepromArrayVariable<int16_t, 3> Int3(cInt3);     // Задаем массив cInt3[3] по умолчанию


const float cFloat[4] = {10.87, 20.05, 30.11, 40.89};                   
eepromArrayVariable<float, 4> Float(cFloat);     // Задаем массив cFloat[4] по умолчанию



void setup() {
  Serial.begin(115200);
  delay(1000); // Просто маленькая задержка
  Serial.println();
  
// Время компиляции скетча
  Serial.print("Compilation Date Time:\t"); Serial.println(AddrMachine::getCompilationDT());
  Serial.println();
  
// Флаг который говорит нашим переменным что делать:
// Читать из памяти или сохранить значения по умолчанию в EEPROM
  Serial.print("ReadFromMemory:\t"); Serial.println(AddrMachine::getReadFromMemory());
  Serial.println();

// Количество экземпляров класса
// По идее бесполезная инфа и нужно это вообще из библиотеки ликвидировать :D
  Serial.print("Count:\t\t"); Serial.println(AddrMachine::getCount());
  Serial.println();

// Выводим информацию о переменных в Монитор порта
  PRINT_INFO_ARRAY(Bool1);
  PRINT_INFO_ARRAY(Bool2);
  PRINT_INFO_ARRAY(Int1);
  PRINT_INFO_ARRAY(Int2);
  PRINT_INFO_ARRAY(Int3);
  PRINT_INFO_ARRAY(Float);

  Serial.println();
// Следующий свободный Адрес в EEPROM (не занятый нашими переменными)
  Serial.print("AddrMachine Next addr = "); Serial.println(AddrMachine::getAddrNext());
  Serial.println();
  
// Выводим код и результат его работы в Монитор порта для наглядности
  Float.v[3] = 99.99;   Serial.print("Float.v[3] = 99.99; -> \t");  PRINT_VALUE_ARRAY(Float);
  Float.Save();         Serial.print("Float.Save(); -> \t");        PRINT_VALUE_ARRAY(Float);
  Float.v[3] = 12.41;   Serial.print("Float.v[3] = 12.41; -> \t");  PRINT_VALUE_ARRAY(Float);
  Float.v[3] = 10.11;   Serial.print("Float.v[3] = 10.11; -> \t");  PRINT_VALUE_ARRAY(Float);
  Float.v[3] = 15.99;   Serial.print("Float.v[3] = 15.99; -> \t");  PRINT_VALUE_ARRAY(Float);
  Float.Load();         Serial.print("Float.Load(); -> \t");        PRINT_VALUE_ARRAY(Float);

// Обратите внимание что только первый раз при загрузке скетча флаг ReadFromMemory = 0 (false)  
// И теперь сколько бы раз мы не перезагружали контроллер           ReadFromMemory = 1 (true)
// А это значит что в памяти переменной Float.v[3] 99.99
// Перезагрузите контроллер и убедитесь в этом
}

void loop() {
  delay(1);
}
