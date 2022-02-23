[![Foo](https://img.shields.io/badge/Version-1.0.1-brightgreen.svg?style=flat-square)](#versions)

# Engineer_EasyEEPROM
EasyEEPROM  - это библиотека для Arduino и ESP8266 для удобной работы с EEPROM.
- Работает на базе стандартной EEPROM.h
- Библиотека сама проверяет нужно ли загружать данные из памяти или сохранить значения по умолчанию
- Работает с любыми типами переменных и массивами
- Но не надо работать со String (как придумаю как ограничить это то будет обновление)


### Совместимость
Совместима со всеми Arduino (UNO, NANO, MEGA и т.д.)
Совместима с esp8266

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Методы](#method)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **Engineer EasyEEPROM** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/EngineeringRoom/Engineer_EasyEEPROM/releases/tag/v1.0.1) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив

<a id="init"></a>
## Инициализация
```cpp
//#define USE_EEPROM_ESP8266_METHOD   // Раскоментируйте если пользуютесь ESP8266
#define USE_EEPROM_AVR_METHOD         // Раскоментируйте если пользуютесь Arduino
#include <Engineer_EasyEEPROM.h>

//AddrMachine FirstAddr(50);          // Так можно задать первый адрес в EEPROM (по умолчанию 0)
```

<a id="usage"></a>
## Использование

"Простые переменные"

eepromVariable<тип переменной> имя;       // Value = 0 Ноль поумолчанию
  
или

const тип переменной Value = 25;          // Задавайте именно const что бы не жрать оперативку
eepromVariable<тип переменной> имя(Value); 

Value - при этом будет заводской настройкой то есть если сбросить флаг и перезагрузить
        контроллер, то память будет опять инициализированна этим значением
        
```cpp
// Объявим разные переменные  
eepromVariable<bool> Bool1;           // Будет false по умолчанию
eepromVariable<bool> Bool2(true);     // Задаем true по умолчанию

eepromVariable<int> Int1;             // Будет 0 по умолчанию
    
eepromVariable<int16_t> Int2(5687);   // Будет 5687 по умолчанию

const float cFloat = 10.87;           // Лучше задавать вот так
eepromVariable<float> Float(cFloat);  // Будет 10.87 по умолчанию
```

"Массивы"
Объявляем экземпляры класса
 
eepromArrayVariable<тип переменной, SIZE> имя;       // Value = 0 Ноль поумолчанию
 
или

const тип переменной Value[] = {};                   // Задавайте именно const что бы не жрать аперативку
eepromArrayVariable<тип переменной, SIZE> имя(Value); 

Value - при этом будет заводской настройкой то есть если сбросить флаг и перезагрузить
        контроллер, то память будет опять инициализированна этим значением 
SIZE  - размер массива

```cpp
// Объявим разные Массивы  
eepromArrayVariable<int, 7> Int1;                // Будет 0 по умолчанию

const int16_t cInt2[3] = {10,20,30};
eepromArrayVariable<int16_t, 3> Int2(cInt2);     // Задаем массив cInt2[3] по умолчанию

const float cFloat[4] = {10.87, 20.05, 30.11, 40.89};                   
eepromArrayVariable<float, 4> Float(cFloat);     // Задаем массив cFloat[4] по умолчанию
```

"Строки char[]"

```cpp
// Объявим разные переменные  
const char cSSIDwifi[32] = "SSIDWiFi";                   
eepromArrayVariable<char, 32> SSIDwifi(cSSIDwifi);     // Задаем массив cSSIDwifi[32] по умолчанию

const char cPASSwifi[32] = "123456";                   
eepromArrayVariable<char, 32> PASSwifi(cPASSwifi);     // Задаем массив cPASSwifi[32] по умолчанию
```
<a id="example"></a>
## Пример
```cpp
//#define USE_EEPROM_ESP8266_METHOD   // Раскоментируйте если пользуютесь ESP8266
#define USE_EEPROM_AVR_METHOD         // Раскоментируйте если пользуютесь Arduino
#include <Engineer_EasyEEPROM.h>

//AddrMachine FirstAddr(50);          // Так можно задать первый адрес в EEPROM (по умолчанию 0)
                                      
// Объявим переменную
const float cFloat = 10.87;           // Лучше задавать вот так
eepromVariable<float> Float(cFloat);  // Будет 10.87 по умолчанию

// Макросы что бы ручками не вводить имя переменной
#define PRINT_VALUE(Variable)       printValue(#Variable, Variable)
#define PRINT_INFO(Variable)        printInfo(#Variable, Variable)

// Шаблон функции для вывода Значения
template <class T>
void printValue (const char* Name, T &Variable){
  Serial.print(Name); Serial.print(" = "); Serial.println(Variable.v);
}

// Удобный шаблон функции для вывода информации о переменных
template <class T>
void printInfo (const char* Name, T &Variable){
  Serial.print(Name); Serial.print("\t-> ");
  Serial.print("\t addr = "); Serial.print(Variable.getAddr());
  Serial.print("\t size = "); Serial.print(Variable.getSizeof());
  Serial.print("\t->\t");
  printValue("Values = ", Variable);
}

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
  PRINT_INFO(Float);

  Serial.println();
// Следующий свободный Адрес в EEPROM (не занятый нашими переменными)
  Serial.print("AddrMachine Next addr = "); Serial.println(AddrMachine::getAddrNext());
  Serial.println();
  
// Выводим код и результат его работы в Монитор порта для наглядности
  Float.v = 20.05;  Serial.print("Float.v = 20.05; -> \t");  PRINT_VALUE(Float);
  Float.Save();     Serial.print("Float.Save();    -> \t");  PRINT_VALUE(Float);
  Float.v = 12.41;  Serial.print("Float.v = 12.41; -> \t");  PRINT_VALUE(Float);
  Float.v = 10.11;  Serial.print("Float.v = 10.11; -> \t");  PRINT_VALUE(Float);
  Float.v = 05.99;  Serial.print("Float.v = 05.99; -> \t");  PRINT_VALUE(Float);
  Float.Load();     Serial.print("Float.Load();    -> \t");  PRINT_VALUE(Float);

// Обратите внимание что только первый раз при загрузке скетча флаг ReadFromMemory = 0 (false)  
// И теперь сколько бы раз мы не перезагружали контроллер           ReadFromMemory = 1 (true)
// А это значит что в памяти переменной Float 20.05
// Перезагрузите контроллер и убедитесь в этом
}

void loop() {
  delay(1);
}
```

<a id="method"></a>
## Методы

Можно задать первый адресс в памяти по умолчанию 0
```cpp
// Раскоментируйте если хотите изменить начальный адресс
// AddrMachine FirstAddr(50);          // Так можно задать первый адрес в EEPROM (по умолчанию 0)
```

Создаем переменную
```cpp
const float cFloat = 10.87;           // Лучше задавать вот так
eepromVariable<float> Float(cFloat);  // Будет 10.87 по умолчанию
```

Создаем массив
```cpp
const float cFloat[4] = {10.87, 20.05, 30.11, 40.89};                   
eepromArrayVariable<float, 4> Float(cFloat);     // Задаем массив cFloat[4] по умолчанию
```

Созадаем строку типа char[] при этом не используйте String
```cpp
const char cSSIDwifi[32] = "SSIDWiFi";                   
eepromArrayVariable<char, 32> SSIDwifi(cSSIDwifi);     // Задаем массив cSSIDwifi[32] по умолчанию
```

Вот так можно узнать статические(общие) переменные всех экземпляров класса eepromVariable или eepromArrayVariable

AddrMachine это класс родитель для всех других классов
```cpp
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

// Следующий свободный Адрес в EEPROM (не занятый нашими переменными)
  Serial.print("AddrMachine Next addr = "); Serial.println(AddrMachine::getAddrNext());
```

Можно обнулить сохраненные данные при помощи вызова Метода одного из двух методов для AddrMachine
Способ первый.
    // Сброс к заводским настройкам (Сработает при перезагрузке)
    static void     setAllFactorySettingsAndRestarting();  
```cpp
  // Сброс к заводским настройкам (Самостоятельно ручками перезагрузите. Сработает после перезагрузки)
  AddrMachine::setAllFactorySettingsAndRestarting(); 
```
или вот такой вариант.
он отличается тем что мы в метод должны прикрепить функцию которая произведет перезагрузку нашего микроконтроллера
Уж как она это сделает... Дернет ножкой вывод Reset или как то програмно.... Это ваши заморочки.
    // Сброс к заводским настройкам и обратный вызов функции которая перезагрузит ваш Микроконтроллер
    static void     setAllFactorySettingsAndRestarting(void (&ResetMethod_callback)());
```cpp
  void Reseting(){
    // Какой то ваш способ перезагрузить Микроконтроллер
  }
  // Сброс к заводским настройкам и обратный вызов функции которая перезагрузит ваш Микроконтроллер
  AddrMachine::setAllFactorySettingsAndRestarting(Reseting); 
```

Работа с переменными. происходит через вызов поля 
```cpp
.v        // Для простой переменной
.v[i]     // Для массива переменной
```

И вы работаете с переменной так же как если бы это была обычная "привычная" переменная
все операторы доступны + - = -- ++ / * %   < > <= >= == !=  (можт что то забыл но вы поняли)
```cpp
const float cFloat[4] = {10.87, 20.05, 30.11, 40.89};                   
eepromArrayVariable<float, 4> Float(cFloat);     // Задаем массив cFloat[4] по умолчанию
.
.
.
  Float.v[3] = 99.99;   // Присваеваем значение
  Float.Save();         // Сохраняем в EEPROM
  Float.v[3] = 12.41;   // Присваеваем значение
  Float.v[3] = 10.11;   // Присваеваем значение
  Float.v[3] = 15.99;   // Присваеваем значение
  Float.Load();         // Загружаем из EEPROM
```

А так же можно узнать адрес и размер переменной
    uint16_t getAddr();                 // Возвращает адрес
    uint16_t getSizeof();               // Возвращает размер занимаемый в памяти
```cpp
    Float.getAddr();                 // Возвращает адрес
    Float.getSizeof();               // Возвращает размер занимаемый в памяти
```

<a id="versions"></a>
## Версии
- v1.0.1

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [sib.eng24@gmail.com](mailto:sib.eng24@gmail.com)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!

