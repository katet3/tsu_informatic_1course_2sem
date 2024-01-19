#include <stdio.h> 
#include <stdlib.h> 
 
int find_sub_string(char* text, char* string) 
{ 
    if(NULL == text || NULL == string)
        return -2;

    char* text_ptr = text; 
    char* str_ptr = string; 
    for(int i = 0; *text_ptr != '\0'; ++i, ++text_ptr) 
    { 
        str_ptr = string; 
        text_ptr = &text[i]; 

        while(*str_ptr != '\0' && *text_ptr == *str_ptr) 
        { 
            text_ptr++; 
            str_ptr++; 
        } 

        if(*str_ptr == '\0') 
        { 
            return i; 
        } 
    } 

    return -1;   
} 
 
int main() 
{ 
    //Hell0_world!!!
    char* text = "abababababababababababab"; //основная строка //aaaaaaaaaaaaaaaaaaa 
    char* sub_string = "abab"; //подстрока 

/*
    int lenPattern = 0;
    char* tmp = sub_string;


    while(*tmp)
    {
        lenPattern++;
        tmp++;
    }

    if(!lenPattern)
        return 0;
*/

    int result = 0;
    int i = 0;
    
    while(text[i])
    {
        
        result = find_sub_string(&text[i], sub_string);// text+i

        if(result == -1)
        {
            break;
        }
        
        printf("%i\n", i + result);
        i += result;    
/*
        if(result == 0 || i == 0)
        {
            ++i;
            continue;
        }
*/       
        ++i;
    }

    return 0; 
}