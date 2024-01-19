#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool simbol_replacement(char* _someText, char* _someStr, size_t N)
{
    char* strA = _someText;
    char* strB = _someStr;
    if(N > 0 && _someStr && _someText)
        while (N > 0 && _someText && (*strA++ = *strB++))
            N--;
}

int main()
{
    size_t size = 100;
    char* someText = NULL;
    char* someStr = NULL;
    someText = (char*)calloc(100, sizeof(char));
    someStr = (char*)calloc(100, sizeof(char));

    if(NULL == someText && NULL == someStr)
        return -1;

    fgets(someText, size, stdin);
    fgets(someStr, size, stdin);
    
    simbol_replacement(someText, someStr, 3);

    for(int i = 0; someStr[i] && i < size; ++i)
    {
        printf("%c", someText[i]);
    }

    for(int i = 0; someStr[i] && i < size; ++i)
    {
        printf("%c", someStr[i]);
    }

    return 0;
}
