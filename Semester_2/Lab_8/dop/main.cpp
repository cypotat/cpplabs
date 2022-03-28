// Сортировка вставками: пусть первые k элементов упорядочены по возрастанию
// Берется (k+1)-ый элемент и размещается среди первых k так,
// чтобы упорядоченными оказались k+1 элементов.
// Этот метод применяется при k от 1 до n-1

// доп: реализовать алгоритм быстрой сортировки
// и сравнить скорость их выполнения

#include "sort.h"
#define N 15 // кол-во элементов

int main() {
  int arr[N] = {7,2,12,16,8,17,11,13,4,1,15,20,19,3,18};
  printf("%-11s","original:"); print_arr(arr, N);

  // сортируем массив
  qsort(arr, N);
  printf("%-11s","sorted:"); print_arr(arr, N);
}