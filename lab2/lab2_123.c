#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*
Функция проверки подвхождения образа в текст
Начиная с самого первого символа
На вход указатель на массив с текстом, указатель на массив с образом
*/

int findSubString(char* _someText, char* _someStr)
{
    if(NULL == _someText || NULL == _someStr)
    {
        return -2;  
    }

    char* text_ptr = _someText;
    char* str_ptr = _someStr;

    while (*text_ptr && *str_ptr)
    {
        printf("%c %c\n", *text_ptr, *str_ptr);
        if(*text_ptr == *str_ptr)
        {
            ++text_ptr;
            ++str_ptr;
        }

        else
        {
            ++text_ptr;
            str_ptr = _someStr;
        }
    }
    
    if(*str_ptr == '\0')
    {
        printf("%d\n",(text_ptr - _someText));
        return (text_ptr - _someText - 1);
    }

    else 
        return -1;
}


int main()
{
    char* someText = NULL;
    char* someStr = NULL;
    size_t size = 100;

    {
        //Динамическое выделение памяти
        someText = (char*)calloc(size, sizeof(char));
        someStr = (char*)calloc(size, sizeof(char));

        if(NULL == someText || NULL == someStr)
        {
            printf("Err not pointer!\n");
            goto next_test;
            //return -1;
        }

        //Инициализация данных
        strcpy(someText, "Hell3o, world!");
        strcpy(someStr, "l");

        int lenPattern = 0;
        char* tmp = someStr;

        while(*tmp)
        {
            lenPattern++;
            tmp++;
        }

        if(!lenPattern)
            lenPattern = 1;

        printf("-------------------------------\n");
        printf("-         findSubString       -\n");
        printf("-------------------------------\n");

        printf("Подстрока присутствует\n");

        printf("Text: %s\n", someText);
        printf("Text: %s\n", someStr);

        /*
        Цикл поиска подвхождения образа в текст, начиная с самого первого символа
        Условия выхода из цикла, либо закончилась строка, либо конец строки
        */
        
        int i = 0;
        printf("%i", lenPattern);
        while((i != -1) && (someText[i] != '\0'))
        {
            i = findSubString(&someText[i]+lenPattern, someStr);
            if (i != -1)
                i += lenPattern;
            
            printf("%d", i);
        }

        free(someText);
        free(someStr);
        
        printf("-------------------------------\n");
    }

    next_test:
    return 0;


}

