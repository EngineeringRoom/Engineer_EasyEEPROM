/*
 *  (про массивы смотрите в другом примере)
 *  http://arduino.ru/Reference вот шпаргалка
 *  
 *       Размеры переменных
 *       8бит = 1 байт
 *       u - перед int значит что число положительное
 *       
 *     int8_t     |  char                |   от -128 до 127               | 1 byte
 *     uint8_t    |  byte, unsigned char |   от 0 до 255                  | 1 byte
 *     int16_t    |  int                 |   от -32768 до 32767           | 2 byte
 *     uint16_t   |  unsigned int, word  |   от 0 до 65535                | 2 byte
 *     int32_t    |  long                |  от  -2147483648 до 2147483647 | 4 byte
 *     uint32_t   |  unsigned long       |  от 0 до 4294967295            | 4 byte
 *  
 *  float
 *  double
 *  
 *  ну и советую все же указывать точный тип 
 *  например int16_t тогда что на AVR что на ESP8266 одна и таже переменная
 *
 * Объявляем экземпляры класса (про массивы смотрите в другом примере)
 * 
 *   eepromVariable<тип переменной> имя;       // Value = 0 Ноль поумолчанию
 *   
 * или
 * 
 *   const тип переменной Value = 25;          // Задавайте именно const что бы не жрать аперативку
 *   eepromVariable<тип переменной> имя(Value); 
 * 
 * Value - при этом будет заводской настройкой то есть если сбросить флаг и перезагрузить
 *         контроллер, то память будет опять инициализированна этим значением
 */

//#define USE_EEPROM_ESP8266_METHOD   // Раскоментируйте если пользуютесь ESP8266
#define USE_EEPROM_AVR_METHOD         // Раскоментируйте если пользуютесь Arduino
#include <Engineer_EasyEEPROM.h>

//AddrMachine FirstAddr(50);          // Так можно задать первый адрес в EEPROM (по умолчанию 0)

// Програмный способ перезагзить МК (Впринципе работает для любой платформы)
void(* resetFunc) (void) = 0;         //объявляем функцию reset с адресом 0

// Какой то ваш способ перезагрузить Микроконтроллер. Можно дернуть PIN Reset
// Вот мой вариант.
void Restarting(){
  #if defined(USE_EEPROM_AVR_METHOD)
    resetFunc(); //вызываем reset
  #elif defined(USE_EEPROM_ESP8266_METHOD)
    ESP.restart();
  #else
    #error "No board selected"
  #endif
}


#include "EasyPrintInfo.h"            // Тут функции что бы удобно выводить в монитор порта
                                      // Это все не относится к примеру, но то де стоит изучить
                                      
// Объявим разные переменные  
eepromVariable<int16_t> Int2(5687);   // Задаем 5687 по умолчанию



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
  PRINT_INFO(Int2);

  Serial.println();
// Следующий свободный Адрес в EEPROM (не занятый нашими переменными)
  Serial.print("AddrMachine Next addr = "); Serial.println(AddrMachine::getAddrNext());
  Serial.println();
  
// Выводим код и результат его работы в Монитор порта для наглядности
  Int2.v = 20;     Serial.print("Int2.v = 20;    -> \t");  PRINT_VALUE(Int2);
  Int2.Save();     Serial.print("Int2.Save();    -> \t");  PRINT_VALUE(Int2);
  Int2.v = 12;     Serial.print("Int2.v = 12;    -> \t");  PRINT_VALUE(Int2);
  Int2.v = 10;     Serial.print("Int2.v = 10;    -> \t");  PRINT_VALUE(Int2);
  Int2.v = 11;     Serial.print("Int2.v = 11;    -> \t");  PRINT_VALUE(Int2);
  Int2.Load();     Serial.print("Int2.Load();    -> \t");  PRINT_VALUE(Int2);

// Обратите внимание что только первый раз при загрузке скетча флаг ReadFromMemory = 0 (false)  
// И теперь сколько бы раз мы не перезагружали контроллер           ReadFromMemory = 1 (true)
// А это значит что в памяти переменной Int2 20
// Перезагрузите контроллер и убедитесь в этом


/*  
 *   Дальше есть два способа
 *   раскоментируйте их поочериди и проверьте работу
 *   конечно это все должно быть обернуто в какую то логику, но здесь это лишнее.
 */
// Способ №1
// Сброс к заводским настройкам (Сработает после перезагрузки. Самостоятельно ручками перезагрузите.)
  //AddrMachine::setAllFactorySettingsAndRestarting();

/*
 * или вот такой вариант. он отличается тем что мы в метод должны прикрепить функцию 
 * которая произведет перезагрузку нашего микроконтроллера 
 * Уж как она это сделает... Дернет ножкой вывод Reset или как то програмно.... Это ваши заморочки.
 */

// Способ №2
// Сброс к заводским настройкам и обратный вызов функции которая перезагрузит ваш Микроконтроллер
  //delay(30000); // Задержка что бы перезагрузка МК не происходила мгновенно
  //AddrMachine::setAllFactorySettingsAndRestarting(Restarting);  
}

void loop() {
  delay(1);
}
