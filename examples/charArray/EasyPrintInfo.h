// Макросы что бы ручками не вводить имя переменной
#define PRINT_VALUE_ARRAY(Variable) printValueArray(#Variable, Variable)
#define PRINT_INFO_ARRAY(Variable)  printInfoArray(#Variable, Variable)
#define PRINT_VALUE(Variable)       printValue(#Variable, Variable)
#define PRINT_INFO(Variable)        printInfo(#Variable, Variable)

/*
 * Для переменных
 */
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

// Шаблон функции что бы получить в виде строки тип переменной
template <class T>
String type_name(const T&){   
    String s = __PRETTY_FUNCTION__;
    
    int start = s.indexOf("[with T = ") + 10;
    int stop = s.lastIndexOf(']');
    
    return s.substring(start, stop);
}


/*
 * Для Массивов
 */
 
// Шаблон функции для вывода Значения
template <class T>
void printValueArray (const char* Name, T &Variable){
  int len = (int)Variable.getSizeof()/sizeof(Variable.v[0]);
  bool TypeNameIsChar = type_name(Variable.v[0]) != "char";
  
  Serial.print(Name); Serial.print(" = ");
  for (int i = 0; i < len; i++){
    if (TypeNameIsChar) Serial.print(" ");
    Serial.print(Variable.v[i]);
    if (TypeNameIsChar) Serial.print(" ");
  }
  Serial.println();
}

// Удобный шаблон функции для вывода информации о переменных
template <class T>
void printInfoArray (const char* Name, T &Variable){
  Serial.print(Name); Serial.print("\t->");
  Serial.print("\t addr = "); Serial.print(Variable.getAddr());
  Serial.print("\t size = "); Serial.print(Variable.getSizeof());
  Serial.print("\t->\t");
  printValueArray("Values = ", Variable);
}
