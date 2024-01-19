#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*
Функция проверки подвхождения образа в текст
Начиная с самого первого символа
На вход указатель на массив с текстом, указатель на массив с образом
*/
bool findSubString(char* _someText, char* _someStr)
{
    if(NULL == _someText || !*_someStr)
    {
        return false;  
    }

    /*
    Пока не дошли до конца текста
    И символы совпадают    
    */
    
    while ((*_someText != '\0') && (*_someStr == *_someText))
    {
        _someStr++;
        _someText++;
    }

    /*
    Если после цикла указатель на образ дошел до конца
    Значит подстрока
    */
    if (*_someStr == '\0')
    {
        return true;
    }

    return false;
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
        strcpy(someText, "Hell3o, world!aa");
        strcpy(someStr, "aa");

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
        while((i < size) && (someText[i] != '\0'))
        {
            printf("%d\n", i);
            if (findSubString(&someText[i], someStr))
            {
                printf("%d\n", i);
                i += lenPattern;
            }

            else
                i++;
        }

        free(someText);
        free(someStr);
        
        printf("-------------------------------\n");
    }

    next_test:
    {
    //Динамическое выделение памяти
    someText = (char*)calloc(size, sizeof(char));
    someStr = (char*)calloc(size, sizeof(char));

    if(NULL == someText || NULL == someStr)
    {
        printf("Err not pointer!\n");
        goto next_test2;
    }

    //Инициализация данных
    strcpy(someText, "Hell3o, world!");
    strcpy(someStr, "");

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

    printf("2)Символа нет:\n");

    printf("Text: %s\n", someText);
    printf("Text: %s\n", someStr);

    /*
    Цикл поиска подвхождения образа в текст, начиная с самого первого символа
    Условия выхода из цикла, либо закончилась строка, либо конец строки
    */
    int i = 0;
    
    while((i < size) && (someText[i] != '\0'))
    {
        if (findSubString(&someText[i], someStr))
        {
            printf("%d\n", i);
            i += lenPattern;
        }

        else
            i++;
    }

    free(someText);
    free(someStr);    
    printf("-------------------------------\n");
    
    }

    next_test2:
    {
    //Динамическое выделение памяти
    someText = (char*)calloc(size, sizeof(char));
    someStr = (char*)calloc(size, sizeof(char));

    if(NULL == someText || NULL == someStr)
    {
        printf("Err not pointer!\n");
        goto next_test3;
    }

    //Инициализация данных
    strcpy(someText, "Hell3o, world!");
    strcpy(someStr, "Hell3o, world!");

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

    printf("3)Подстрока и текст совпадают\n");

    printf("Text: %s\n", someText);
    printf("Text: %s\n", someStr);

    /*
    Цикл поиска подвхождения образа в текст, начиная с самого первого символа
    Условия выхода из цикла, либо закончилась строка, либо конец строки
    */
    
    int i = 0;
    
    while((i < size) && (someText[i] != '\0'))
    {
        if (findSubString(&someText[i], someStr))
        {
            printf("%d\n", i);
            i += lenPattern;
        }

        else
            i++;
    }

    printf("-------------------------------\n");
    }

    next_test3:
    {
    //Динамическое выделение памяти
    someText = NULL;
    someStr = (char*)calloc(size, sizeof(char));

    if(NULL == someText || NULL == someStr)
    {
        free(someStr);
        printf("Err not pointer! In test - 3\n");
        goto next_test4;
    }

    //Инициализация данных
    strcpy(someStr, "Hell3o, world!");

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

    printf("Text: %s\n", someText);
    printf("Text: %s\n", someStr);

    /*
    Цикл поиска подвхождения образа в текст, начиная с самого первого символа
    Условия выхода из цикла, либо закончилась строка, либо конец строки
    */
    int i = 0;
    
    while((i < size) && (someText[i] != '\0'))
    {
        if (findSubString(&someText[i], someStr))
        {
            printf("%d\n", i);
            i += lenPattern;
        }

        else
            i++;
    }
    
    printf("-------------------------------\n");
    }

    next_test4:
    {
    //Динамическое выделение памяти
    someText = (char*)calloc(size, sizeof(char));
    someStr = NULL;

    if(NULL == someText || NULL == someStr)
    {
        free(someStr);
        printf("Err not pointer! In test - 4\n");
        goto next_test5;
    }

    //Инициализация данных
    strcpy(someText, "Hell3o, world!");

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

    printf("Text: %s\n", someText);
    printf("Text: %s\n", someStr);

    /*
    Цикл поиска подвхождения образа в текст, начиная с самого первого символа
    Условия выхода из цикла, либо закончилась строка, либо конец строки
    */
    int i = 0;
    
    while((i < size) && (someText[i] != '\0'))
    {
        if (findSubString(&someText[i], someStr))
        {
            printf("%d\n", i);
            i += lenPattern;
        }

        else
            i++;
    };
    
    printf("-------------------------------\n");
    }

    next_test5:
    printf("END\n");

    return 0;

};