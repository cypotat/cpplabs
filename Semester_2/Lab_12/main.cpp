// Создайте класс HugeInt, который хранит в 40-элементном массиве
// цифр целые числа разрядностью до 40 знаков
// Разрядность указать в конструкторе.
// Предусмотреть функции сложения, вычитания, сравнения и проверки на 0

// Используйте приватные поля для данных,
// определите конструктор, который должен содержать значения по умолчанию,
// напишите методы установки и извлечения значений (set, get),
// выполнения операций ввода и вывода значения объекта созданного класса.
// Напишите конструктор копий, оператор присваивания, деструктор.
// Напишите программу для тестирования вашего класса

#include <iostream>
#include "HugeInt.h"

int main() {
  HugeInt test(2);
  test.print();

  test.set(42);
  test.print();
  test.set(7);
  test.print();
}

