//Пусть А = {a , b, с } и надо закодировать слово по правилу: букву а заменить на b, b на с и с на а.
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#define SIZE 100

char* NormalMarkovAlgorithm(char* str, size_t size)
{
    //char* str_tmp[SIZE+1] = "*";
    char* str_tmp = (char*)calloc(size, sizeof(char));
    if (!str_tmp)
    {
        return str_tmp;
    }
    *str_tmp = '*';
    int i = 0;
    for (i = 1;(i < size) && (str[i-1] != '\0') ;i++)
    {
        if ((str[i-1] != 'a') && (str[i-1] != 'b') && (str[i-1] != '\0'))
        {
            printf("This text is not suitable for the Normal Markov Algorithm \n[%c] - ??? \n", str[i-1]);
            memset(str_tmp,0,size);
            return str;
        }
        str_tmp[i] = str[i-1];
    }
    //printf("%s",str_tmp);
    for (i = 0;i < size ;)
    {
        if((str_tmp[i] == '*') && (str_tmp[i+1] == 'a'))
        {
            str_tmp[i] = 'b';
            str_tmp[i+1] = '*';
            i = 0;
            continue;
        }
        if((str_tmp[i] == '*') && (str_tmp[i+1] == 'b'))
        {
            str_tmp[i] = 'a';
            str_tmp[i+1] = '*';
            i = 0;
            continue;
        }
        if ((str_tmp[i] == '*') && (str_tmp[i+1] == '\0'))
        {
            str_tmp[i] = '\0';
            break;
        }
        i++;
    }
    //memset(str_tmp,0,SIZE);
    //printf("\n");
    //printf("%s",str);
    //printf("\n");
    return str_tmp;
}


int main()
{
    char str[SIZE] = "aab";
    int size = SIZE;
    char* str_cm = NormalMarkovAlgorithm(str, size);
    if(!str_cm)
    {
        return 0;
    }
    printf("%s\n",str);
    printf("%s\n",str_cm);
    return 1;
}