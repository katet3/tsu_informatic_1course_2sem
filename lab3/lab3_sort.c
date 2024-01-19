/*
Функция name

Входные значения:

Возращаемое значение:

Описание функции:

*/

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <stdbool.h>
#define TACT 1000000

/*
Фунция randInRange

Входные значения: 
границаИнтервала1, границаИнтервала2

Возращаемое значение: 
случайное значение в заданном интервале

Описание функции: 
принимается интервал, с помощью случайного числа берется
остатоток от разности границ. Далее прибавлятся наименьшая 
граница к данному числу тем самым получая случайно число в 
заданном диапозоне 
*/
int randInRange(int _min, int _max) 
{ 
    if (_min == _max)
    { 
        return _min; 
    };

    if (_min > _max)
    { 
        int tmp = _min; 
        _min = _max; 
        _max = tmp; 
    };

    return rand() % (_max - _min + 1 ) + _min; 
};

/*
Функция checkSortedArray

Входные значения:
указатель на массив, размер массива

Возращаемое значение:
находится ли массив в порядке неубывания

Описание функции:
Посимвольное сравнение i и i+1 элемента

*/
//Проверка на сортировку 
bool checkSortedArray(int* _array, size_t _size) 
{ 
    if(NULL == _array)
    {
        return false;
    };

    if (_size == 1)
    {
        return true;
    };

    for (int i = 0; i < _size-1; i++)
    { 
        if (_array[i] > _array[i+1])
        {
            return true;  
        };
    };

    return true; 
}
//Создание динамического массива 
int* createArray(size_t _size)
{ 
    int *result = NULL;
    result = (int*)calloc(_size,sizeof(int)); 

    if (NULL == result)
    { 
        return result; 
    };

    for (int i = 0, *tmp = result; i < _size; i++, tmp++)
    { 
       *tmp = randInRange(1,100); 
    };

    return result; 
};

/*
Функция bubbleSort

Входные значения:
указатель на массив, размер массива

Возращаемое значение:


Описание функции:

*/

// Сортировка пузырька(шейкер) 
void bubbleSort(int* _array, size_t _size) 
{ 
    int left = 0, right = _size - 1; // левая и правая границы сортируемой области массива
    bool flag = true;  // флаг наличия перемещений
    // Выполнение цикла пока левая граница не сомкнётся с правой
    // и пока в массиве имеются перемещения
    while ((left < right) && flag)
    {
        flag = false;
        for (int i = left; i<right; i++)  //двигаемся слева направо
        {
            if (_array[i] > _array[i + 1]) // если следующий элемент меньше текущего,
            {             // меняем их местами
                int tmp = _array[i];
                _array[i] = _array[i + 1];
                _array[i + 1] = tmp;
                flag = true;      // перемещения в этом цикле были
            }
        };
        right--; // сдвигаем правую границу на предыдущий элемент
        
        for (int i = right; i > left; i--)  //двигаемся справа налево
        {
            if (_array[i - 1] > _array[i]) // если предыдущий элемент больше текущего,
            {            // меняем их местами
                int tmp = _array[i];
                _array[i] = _array[i - 1];
                _array[i - 1] = tmp;
                flag = true;    // перемещения в этом цикле были
            };
        };
        left++; // сдвигаем левую границу на следующий элемент
    };
};

//сортировка включение 
void inclusionSort(int* _array, size_t _size) 
{ 
    //Организации проверок!!!
    for (int i = 1; i < _size; i++)
    { 
        int value = _array[i]; 
        int index = i;

        while ((index > 0) && (_array[index - 1] > value))
        { 
            _array[index] = _array[index - 1]; 
            index--; 
        }; 
        _array[index] = value; 
    };
};
//  сортировка вставка

void insertionSort(int* _array, size_t _size) 
{ 
        //Организации проверок!!!

    int newElement; 
    int location; 

    for (int i = 1; i < _size; i++)
    { 
        newElement = _array[i]; 
        location = i - 1; 
        while(location >= 0 && _array[location] > newElement)
        { 
            _array[location+1] = _array[location]; 
            location = location - 1; 
        } 
        _array[location+1] = newElement; 
    };
};

// Копирование массива 
int* copyArray(int* _array, size_t _size)
{
        //Организации проверок!!!

    int *tmpArray = NULL;
    tmpArray = (int*)calloc(_size, sizeof(int));

    if (tmpArray)
    {
        for (int i = 0; i < _size;i++)
        {
            tmpArray[i] = _array[i];
        }
        return tmpArray;
    }
    
    else
    {
        return tmpArray;
    };
};
//Вывод массива
void printArray(int* _array, size_t _size)
{
    int i = 0;
    printf("{");

    for(i = 0; i < _size - 1; i++)
    {
        printf("%d, ", _array[i]);
    };

    printf("%d", _array[i]);
    printf("}\n");
}
//Эта функция написана имеено под этот случай, чтобы уменьшить код. Чтобы в main после каждой сортировки не очищать массив и выводить данные строки 
void print_check_sorted_array(int* _tmp, size_t _size)
{ 
    if (checkSortedArray(_tmp, _size))
    {
        printArray(_tmp, _size); 
        printf("Done!\n"); 
    }

    else
    { 
        printf("Error last sort!!! \n");
    };
    free(_tmp);
};




int main()
{
    //srand() позволяет запускать программу несколько раз с различными последователь­ностями псевдослучайных чисел
    srand((unsigned int) time(NULL));

    int size = 10; 
    int* array = createArray(size);
    if(NULL == array)
    {
        return 1;
    };

    //bubble_sort -------------------------------------------------------------
    int* tmp = copyArray(array, size);
    if(NULL == tmp)
    {
        return 1;
    };

    clock_t start = clock(); 
    for(int i=0;i<TACT; i++)
    { 
      bubbleSort(tmp, size); 
    };
    clock_t end = clock();

    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("Bubble sort - %f second\n", seconds);
    print_check_sorted_array(tmp, size);
    
    //inclusion_sort -------------------------------------------------------- 
    tmp = copyArray(array, size);
    if(NULL == tmp)
    {
        return 1;
    };

    start = clock(); 
    for(int i=0;i<TACT; i++)
    { 
      inclusionSort(tmp, size); 
    };
    end = clock(); 
    double seconds1 = (double)(end -start) / CLOCKS_PER_SEC; 
    
    printf("Inclusion sort - %f second\n", seconds1);
    print_check_sorted_array(tmp, size);
    
    //insertion_sort -------------------------------------------------------------
    tmp = copyArray(array, size);
    if(NULL == tmp)
    {
        return 1;
    };

    start = clock(); 
    for(int i=0;i<TACT; i++)
    { 
      insertionSort(tmp, size); 
    } 
    end = clock(); 
    double seconds2 = (double)(end - start) / CLOCKS_PER_SEC; 
    
    printf("Insertion sort - %f second\n", seconds2);
    print_check_sorted_array(tmp, size);
    
    return 0;  
};