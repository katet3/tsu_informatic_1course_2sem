#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int delete_simbol(char* someText, char* symbols) 
{
    if(NULL == someText || NULL == symbols)
        return 1;

    bool Tab[256] = {0};
    char *ptrStr = symbols;
    
    while (*ptrStr)
        Tab[*ptrStr++] = true;

    int i = 0, j = 0;

    while (someText[i]) 
    {
        if (!Tab[someText[i]]) {
            someText[j] = someText[i];
            j++;
        }
    
        i++;
    }
    
    someText[j] = '\0';

    return 0;
}

int main()
{
    int size = 100;
    char* someText = NULL;
    char* someStr = NULL;
    someText = (char*)calloc(size, sizeof(char));
    someStr = (char*)calloc(size, sizeof(char));

    if(NULL == someText && NULL == someStr)
        return -1;

    fgets(someText, size, stdin);
    fgets(someStr, size, stdin);

    delete_simbol(someText, someStr);

    for(int i = 0; someText[i] && i < size; ++i)
    {
        printf("%c", someText[i]);
    }

    printf("\n");

    return 0;


}