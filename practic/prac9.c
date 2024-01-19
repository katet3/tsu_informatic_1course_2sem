/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdbool.h>

// Побитовые операции &(И),|(ИЛИ),^(),~(Не), >>, <<

// 1. 128 = 1000 0000
// 2. 127 = 0111 1111
//-----------------------------
// 3.  &   = 0000 0000
// 4.  |   = 1111 1111
// 5.  ^   = 1111 1111
// 6.  ~   = 0111 1111
// 7.  ~   = 11111000   << 2
// 8       = 00111110   >>

/*
Обмен значений переменных
vecA = vecA ^vecB;
vecB = vecA ^vecB;
vecA = vecA ^vecB;
*/

// 0000000(0)
// 0000001(1)
// 0000010(2)
// 0000011(3)
// 0000100(4)
// 0000101(5)
// 0000110(6)
// 0000111(7)
// 0001010(8)
// 0001011(9)

// 0001011(10)
// 0001100(11)
// 0001000(8)
// 0000111(7)
//  vec&(vec-1)


void PrintBVToConsol (unsigned int vec)
{
    unsigned int  mask = 1;
    mask = mask<<31;

    //printf("%u\n", mask);

    for(int ix=0; ix < 32; ix++){

    if( mask & vec)

    printf("%c", '1' );
    else
    printf("%c", '0' );

    mask = mask>>1;

    }
    printf("\n");

}

unsigned int StrToUL(const char*vec)
{
    unsigned int res = 0;
    unsigned int mask = 1;

    if (vec)
    {
        while (*vec)
        {
            res = res << 1;
            if (*vec!= 48)
            {
                res = res | mask;
            }
            //res = res << 1;
            vec++;
        }
    }
    return res;
}




//Функция опреhttps://www.onlinegdb.comделяет, являются ли входные ветора ортогоналными только по одной компоненте

bool isOrthogonalTheOnlyOneComponent(unsigned int vecA, unsigned int vecB){

    unsigned int tmp = vecA ^ vecB;
    if( tmp & (tmp - 1)  == 0)
    return true;
    return false;

}







//Функция определяет вес вектора
/*

Входные аргументы:
unsigned long vec - булев ветор длины 32
Выходные аргументы: вес вектора

*/
int weightOfVector(unsigned long vec) {
    int weight = 0;

    while (vec)
    {
        weight++;
        vec = vec & (vec - 1);
    }
    return weight;
}



int main()
{
    unsigned int vecA = 10;//(4 байт)
    /*
         ( 0000 0000 0000 0000 0000 0000(8) 0000 1011)
         ( 0000 0000 0000 0000 0000 0000(8) 0000 0001)


|        ( 0000 0000 0000 0000 0000 0001(8) 0000 1010)
mask   = ( 0000 0000 0000 0000 0000 0000(8) 0000 0001)
mask*  = ( 0000 0000 0000 0000 0000 0001(8) 0000 0000)*/
    unsigned int mask = 1;
    int k = 8;

    // 1. Установка к ого разряда (1)
    //формируем маску
    mask = mask <<  k;
    vecA = vecA | mask;
  // 2. Сброс к ого разряда (0)
 /*
   ( 0000 0000 0000 0000 0000 0001(8) 0000 1010)
   ( 1111 1111 1111 1111 1111 1110(8) 1111 1111
  */
    mask = 1;
    mask = mask <<  k;
    mask = ~mask;
    vecA = vecA & mask;




 mask = 10;
    unsigned int vecB = 10;

    vecA = 127;
    PrintBVToConsol (vecA);

    vecA = -1;
    PrintBVToConsol (vecA);

    vecA = vecA >> 1;
    PrintBVToConsol (vecA);

    vecA = vecA >> 1;
    PrintBVToConsol (vecA);

    vecA = vecA >> 1;
    PrintBVToConsol (vecA);

    vecA = vecA << 1;
    PrintBVToConsol (vecA);

    vecA = vecA << 1;
    PrintBVToConsol (vecA);

    vecA = vecA << 1;
    PrintBVToConsol (vecA);

    vecA = 6;
    vecA = vecA >> 1;
    //vecA = vecA << 1;

    printf("%u\n", vecA);


vecA = 2;
vecB = 3;
printf("%u , %u\n", vecA, vecB);
vecA = vecA ^vecB;
vecB = vecA ^vecB;
vecA = vecA ^vecB;

printf("%u , %u\n", vecA, vecB);


PrintBVToConsol (StrToUL("110011"));


unsigned int sdnf[5]={0};

char strdnf[5][6+1] = { "110011",
                        "111000",
                        "001100",
                        "110000",
                        "100001"};

//Converting
for(int ix = 0; ix < 5; ix++)
{
    sdnf[ix] = StrToUL(strdnf[ix]);
    PrintBVToConsol(sdnf[ix]);
}

char vecStr[6+1] = "110010";

unsigned int vec = StrToUL(vecStr);

//Solution
bool function = false;

for (int ix = 0; ix < 5; ix++ )
{
    if(sdnf[ix] == vec)
    {
        function = true;
        break;
    }

}


 for( int ix = 0; ix < 5 && !function; ix++)
 {
     if(sdnf[ix] == vec)
     function = true;

 }



//   110011 - Ki
//   110010 - value
//   1*1*1*1*1*0 = 0

//   110011 - Ki
//   111011 - value
//   111111  - 1



return 0;
}


/*

//Значения(численное), которые есть в массиве от 0 до 32

unsigned long FillVectorFromArr(int *mx, int sz)
{
unsigned long vec = 0, mask = 1;
if (mx && sz > 0 && sz < 32) {
for (int i = 0; i < sz; i++) {
if (mx[i] >= 0 && mx[i] < 32) {
mask = (unsigned long)1 << mx[i];
vec = vec | mask;
}
}
}
return vec;
}

//Узнаем вес булевого вектора путем отнимания по одной единицы в числе(разряда) пока вектор не станет 0

int weightOfVector(unsigned long vec) {
int weight = 0;
while (vec) {
weight++;
vec = vec & (vec - 1);
}
return weight;
}

//

void PutValuesToSet(int *Mx, int size, unsigned long vec) {
if (Mx && size > 0 && vec) {
unsigned long mask = 1;
int i = -1;
int value = 0;
while (size && vec) {
if (mask & vec) {
Mx[++i] = value;
vec = vec ^ mask;
}
value++;
mask = mask << 1;
}
}
}
int main(int argc, char** argv) {
unsigned long u, v, r, m;
int setA[32] = { 2,5,7,9,10,4,8,9 };
int setB[32] = { 0,5,7,6,3,4,8,9 };
int size = 8;
int *setI = NULL;
unsigned long valSetA = FillVectorFromArr(setA, size);
unsigned long valSetB = FillVectorFromArr(setB, size);
unsigned long intersection = valSetA & valSetB;
if (intersection) {
printf("Solution is not empty\n");
int weight = weightOfVector(intersection);
if (weight)
{
setI = (int*)malloc(sizeof(int)*weight);
if (setI)
{
PutValuesToSet(setI, weight, intersection);
for (int i = 0; i < weight; i++)
{
printf("%d, ", setI[i]);
}
free(setI);
setI = NULL;
}
else
printf("Exeption: Bad allocation\n");
}
}
else
printf("Solution is empty\n");
return 0;
}
*/