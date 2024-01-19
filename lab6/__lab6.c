#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h>

#define SIZE_ARRAY 3
#define N_BIT_IN_BYTE 8

typedef int error_code_t;
#define ERR_NOT_PTR 1


typedef unsigned char ubyte;

//Function
error_code_t print_bit_byte(ubyte *aByte, size_t size)
{
    if(aByte == NULL)
        return ERR_NOT_PTR;


    for(int i = 0; i < size; i++)
    {
        printf("%c", (0b10000000 & aByte[i]) ? '1' : '0');
        printf("%c", (0b01000000 & aByte[i]) ? '1' : '0');
        printf("%c", (0b00100000 & aByte[i]) ? '1' : '0');
        printf("%c", (0b00010000 & aByte[i]) ? '1' : '0');
        printf("%c", (0b00001000 & aByte[i]) ? '1' : '0');
        printf("%c", (0b00000100 & aByte[i]) ? '1' : '0');
        printf("%c", (0b00000010 & aByte[i]) ? '1' : '0');
        printf("%c", (0b00000001 & aByte[i]) ? '1' : '0');
        printf(" ");
    }

    return 0;
}


ubyte* vector_and(
    ubyte* vector_one, 
    ubyte* vector_second, 
    size_t bits
    )
{
    if((vector_one == NULL) || (vector_second == NULL))
        return NULL;


    if (bits == 0)
    {
        ubyte* vector_result = (ubyte*)calloc(sizeof(ubyte), 1);
        vector_result[0] = vector_one[0] & vector_second[0];

        ubyte mask = (255 >> (8-((bits+1)%8)));
        vector_result[0] &= mask;

        return vector_result;
    }

    //т.к нумерация битов в нуля +1 не нужен
    int bytes = ((bits)/8)+1;

    printf("%d\n", bytes);
    
    ubyte* vector_result = (ubyte*)calloc(sizeof(ubyte), bytes);

    if (vector_result == NULL)
        return NULL;
    
    int i, j;
    for(i = bytes - 1, j = bits/8; i >= 0 && j >= 0; --i, --j)
    {
        //printf("%d %d\n", i, bits);
        vector_result[i] = vector_one[i] & vector_second[i];
    }

    if((bits+1) % 8 != 0)
    {
        //нумерация с 0, поэтому + 1
        ubyte mask = (255 >> (8-((bits+1)%8)));
    //    printf("%d %d %d\n", i, mask, (8-((bits+1)%8)) );
        vector_result[i+1] &= mask;
    }

    return vector_result;

    /*
    for(int i = bits-1, j = bits/8; i >= 0, j > 0; i -= 8, --j)
    {
        vector_result[i/8] = vector_one[i/8] & vector_second[i/8];
        


        //побитовое и байтов двух векторов
        //vector_result[i] = vector_one[i] & vector_second[i];
        
        //print_bit_byte(vector_result, bits/8);
        //printf("\n");
    }
    //ubyte mask = (vector_one[(bits/8)+1] << (bits % 8)) & (vector_second[(bits/8)+1] << (bits % 8));
    vector_result[2] = (vector_one[(bits/8)+1] << (bits % 8)) & (vector_second[(bits/8)+1] << (bits % 8));
    */
    
    return 0;
}


ubyte* vector_or(
    ubyte* vector_one, 
    ubyte* vector_second, 
    size_t bits
    )
{
    if((vector_one == NULL) || (vector_second == NULL))
        return NULL;


    if (bits == 0)
    {
        ubyte* vector_result = (ubyte*)calloc(sizeof(ubyte), 1);
        vector_result[0] = vector_one[0] | vector_second[0];

        ubyte mask = (255 >> (8-((bits+1)%8)));
        vector_result[0] &= mask;

        return vector_result;
    }
    
    //т.к нумерация битов в нуля +1 не нужен
    int bytes = ((bits)/8)+1;
    ubyte* vector_result = (ubyte*)calloc(sizeof(ubyte), bytes);

    if (vector_result == NULL)
        return NULL;
    
    int i, j;
    for(i = bytes - 1, j = bits/8; i >= 0 && j >= 0; --i, --j)
    {
        //printf("%d %d\n", i, j);
        vector_result[i] = vector_one[i] | vector_second[i];
    }

    if((bits+1) % 8 != 0)
    {
        //нумерация с 0, поэтому + 1
        ubyte mask = (255 >> (8-((bits+1)%8)));
    //    printf("%d %d %d\n", i, mask, (8-((bits+1)%8)) );
        vector_result[i+1] &= mask;
    }

    return vector_result;
}


ubyte* vector_xor(
    ubyte* vector_one,
    ubyte* vector_second,  
    size_t bits
    )
{
    if((vector_one == NULL) || (vector_second == NULL))
        return NULL;


    if (bits == 0)
    {
        ubyte* vector_result = (ubyte*)calloc(sizeof(ubyte), 1);
        vector_result[0] = vector_one[0] ^ vector_second[0];

        ubyte mask = (255 >> (8-((bits+1)%8)));
        vector_result[0] &= mask;

        return vector_result;
    }
    

    //т.к нумерация битов в нуля +1 не нужен
    int bytes = ((bits)/8)+1;
    ubyte* vector_result = (ubyte*)calloc(sizeof(ubyte), bytes);

    if (vector_result == NULL)
        return NULL;
    
    int i, j;
    for(i = bytes - 1, j = bits/8; i >= 0 && j >= 0; --i, --j)
    {
        //printf("%d %d\n", i, j);
        vector_result[i] = vector_one[i] ^ vector_second[i];
    }

    if((bits+1) % 8 != 0)
    {
        //нумерация с 0, поэтому + 1
        ubyte mask = (255 >> (8-((bits+1)%8)));
    //    printf("%d %d %d\n", i, mask, (8-((bits+1)%8)) );
        vector_result[i+1] &= mask;
    }

    return vector_result;

    return 0;
}


ubyte* vector_invert(
    ubyte* vector,
    size_t bits
    )
{
    if(vector == NULL)
    {
        return NULL;
    }
    
    if (bits == 0)
    {
        ubyte* vector_result = (ubyte*)calloc(sizeof(ubyte), 1);
        vector_result[0] = ~vector[0];

        ubyte mask = (255 >> (8-((bits+1)%8)));
        vector_result[0] &= mask;

        return vector_result;
    }
    
    //т.к нумерация битов в нуля +1 не нужен
    int bytes = ((bits)/8)+1;
    ubyte* vector_result = (ubyte*)calloc(sizeof(ubyte), bytes);

    if (vector_result == NULL)
        return NULL;

    int i, j;
    for(i = bytes - 1, j = bits/8; i >= 0 && j >= 0; --i, --j)
    {
        //printf("%d %d\n", i, j);
        vector_result[i] = ~vector[i];
    }

    if((bits+1) % 8 != 0)
    {
        //нумерация с 0, поэтому + 1
        ubyte mask = (255 >> (8-((bits+1)%8)));
        //printf("%d %d %d\n", i, mask, (8-((bits+1)%8)) );
        vector_result[i+1] &= mask;
    }

    return vector_result;

    return 0;
}


/*
error_code_t inversion(ubyte* vector, size_t bits)
{   
    if (bits == 0)
        return -1;
    
    //т.к нумерация битов в нуля +1 не нужен
    int bytes = ((bits)/8)+1;

    if (NULL == vector)
        return ERR_NOT_PTR;

    int i, j;
    ubyte buffer = 0;

    for(i = bytes - 1, j = bits/8; i >= 0 && j >= 0; --i, --j)
    {
        //printf("%d %d\n", i, j);
        for(int z = 0; z < 8; ++z)
        {
            ubyte mask = (128>>z)&vector[i];
            buffer |= (mask >> (7 - z)) | buffer;

            print_bit_byte(&buffer, 1);
            printf("%d %d %d\n", buffer, mask ,z);
        }
        vector[i] = buffer;
        buffer = 0;
    }

    if((bits+1) % 8 != 0)
    {
        //нумерация с 0, поэтому + 1
        ubyte mask = (255 >> (8-((bits+1)%8)));
        //printf("%d %d %d\n", i, mask, (8-((bits+1)%8)) );
        vector[i+1] &= mask;
    }
    return 0;

}
*/


error_code_t vector_shift_right(
    ubyte* vector,
    size_t bits,
    size_t k
    )
{
    if (vector == NULL)
        return ERR_NOT_PTR;
        
    size_t n_cel;
    if (k >= bits)
    {
        printf("3131231231\n");
        n_cel = bits / 8;
        while(n_cel)
        {
            vector[n_cel] = 0;
            n_cel--;
        }
        return 0;
    }


    int i,j;
    size_t n_bit;
    size_t current_element;
    size_t current_bit;
    
    for (j = bits-1, i = 0; j > 7; i++, j--) //Идем с конца вектора
    {
        ///*

        if(j-k <= 0)
        {
            //j--;
            //i++;
            
            while(j > 7)
            {
                       // printf("%d %d\n", j, bits);

                current_element = j / 8;
                current_bit = i % 8;
                
                vector[current_element] = vector[current_element] & (~(1 << current_bit));
        
                //print_bit_byte(vector, bits/8);
                //printf("\n");
                j--;
                i++;
                
            }
            
            break;
        }
        //*/
        
        //алгоритм описанный в решении задачи
        n_cel = (j - k) / 8;
        n_bit = (i + k) % 8;
        current_element = j / 8;
        current_bit = i % 8;
        
        if( (vector[n_cel] & (1 << n_bit)) )
        {
            //если бит который должен придти на место текущего бита является единицей
            vector[current_element] = vector[current_element] | ( (1 << current_bit));
            
            //print_bit_byte(vector,bits/8);
            //printf("\n");
            
            continue;
        }
        //иначе 0
        vector[current_element] = vector[current_element] & (~(1 << current_bit));
        
        //print_bit_byte(vector,bits/8);
        //printf("\n");
    }
    //Последний байт сдивигаем обычно, так как для него не найдется заменяемый бит. Будет выход за границы
    current_element = j / 8;
    vector[current_element] = vector[current_element] >> k;

    //print_bit_byte(vector, bits/8);
    //printf("\n");
    
    return 0;
}


error_code_t vector_shift_left(
    ubyte* vector,
    size_t bits,
    size_t k
    )
{
    if (vector == NULL)
        return ERR_NOT_PTR;
    size_t n_cel;
    
    
    printf("%i %i/n", k, bits);
    if (k >= bits)
    {
                printf("3131231231\n");

        n_cel = bits / 8;
        while(n_cel)
        {
            vector[n_cel] = 0;
            n_cel--;
        }
        return 0;
    }
    
    int i,j;
    size_t n_bit;
    size_t current_element;
    size_t current_bit;


    // i ячейки j биты
    for (j = 0, i = bits-1; j < bits-8; i--, j++)//Идем сначала. Т.е текущий бит 
    {
        //выход за границы ?
        if(j+k >= bits)
        {
            while(j < bits-8)
            {
                current_element = j / 8;
                current_bit = i % 8;
                
                vector[current_element] = vector[current_element] & (~(1 << current_bit));
        
                //print_bit_byte(vector, bits/8);
                //printf("\n");
                j++;
                i--;
                
            }
            
            break;
        }
        
        n_cel = (j + k) / 8;
        n_bit = (i - k) % 8;
        current_element = j / 8;
        current_bit = i % 8;
        
        
        if( (vector[n_cel] & (1 << n_bit)) )
        {
            //если бит который должен придти на место текущего бита является единицей
            vector[current_element] = vector[current_element] | ( (1 << current_bit));
            
            //print_bit_byte(vector,bits/8);
            //printf("\n");
            //vector[n_cel] = vector[n_cel] & (~(1 << n_bit));
            continue;
        }
        
        vector[current_element] = vector[current_element] & (~(1 << current_bit));
                    //vector[n_cel] = vector[n_cel] & (~(1 << n_bit));

        //print_bit_byte(vector,bits/8);
        //printf("\n");
    }
    //Последний байт сдивигаем обычно, так как для него не найдется заменяемый бит. Иначе выход за границы
    current_element = j / 8;
    vector[current_element] = vector[current_element] << k;
    
    //print_bit_byte(vector,bits/8);
    //printf("\n");
    return 0;
}


error_code_t change_bit(
    ubyte* vector,
    bool bit,
    size_t digit
)

{
    size_t n_cel = digit / 8;
    size_t n_bit = digit % 8;
    
    if (vector == NULL)
        return ERR_NOT_PTR;
        
    if (bit == false)
    {
        vector[n_cel] = vector[n_cel] & (~(1 << n_bit));
    }
    else
        vector[n_cel] = vector[n_cel] | (1 << n_bit);

    return 0;
}

/*
//Первый тип заполнения
error_code_t convert_string_1(
    char* string,
    size_t bits,
    ubyte* vector)
{
    if(vector == NULL)
        return ERR_NOT_PTR;
        
    size_t n_cel;
    size_t n_bit;
    
    for(int i = 0; i < bits && string[i]; i++)
    {
        n_cel = i / 8;
        n_bit = i % 8;
        
        if (string[i] != '0')
        {
            vector[n_cel] = vector[n_cel] | (1 << (n_bit % 8));
        }
        else 
            vector[n_cel] = vector[n_cel] & (~(1 << (n_bit % 8)));
    }
    
    return 0;
}
*/

// 2 тип заполнения (Взаимно однозначное соответствие)
error_code_t convert_string_2(
    char* string,
    size_t bits,
    ubyte* vector)
{
    if(vector == NULL)
        return ERR_NOT_PTR;
        
    size_t n_cel;
    size_t n_bit;
    
    for(int i = 0, j = bits - 1; i < bits && string[i]; i++, j--)
    {
        n_cel = j / 8;
        n_bit = i % 8;
        
        if (string[i] != '0')
        {
            vector[n_cel] = vector[n_cel] | (1 << (n_bit % 8));
        }
        else
        { 
            vector[n_cel] = vector[n_cel] & (~(1 << (n_bit % 8)));
        }
    }
    
    printf("\n");
    return 0;
}

/*
error_code_t convert_vector_1(ubyte *arr,size_t bits,char *string)
{
    if (NULL == arr || NULL == string)
    {
        return ERR_NOT_PTR;
    }
    size_t n_cel;
    size_t n_bit;
    int i;
    
    for(i = 0;i < bits-1;i++)
    {
        n_cel = i / 8;
        n_bit = i % 8;
        if(arr[n_cel] & (1 << n_bit))
        {
            //1
            string[i] = '1';
        }
        else
            string[i] = '0';
    }
    
    string[i] = '\0';
    return 0;
}
*/

error_code_t convert_vector_2(ubyte *arr, size_t bits, char *string)
{
    if (NULL == arr || NULL == string)
    {
        return ERR_NOT_PTR;
    }

    size_t n_cel;
    size_t n_bit;
    int i,j;
    
    for(i = 0, j = bits-1; i < bits-1;i++,j--)
    {
        n_cel = j / 8;
        n_bit = i % 8;
    
        if(arr[n_cel] & (1 << n_bit))
        {
            //1
            string[i] = '1';
        }
    
        else
            string[i] = '0';
    }
    
    string[i] = '\0';
    return 0;
}

error_code_t work_on_byte();

int main()
{
    if (work_on_byte())
    {
        printf("Failed to get memory!");
        return 1;
    }
    return 0;
}


error_code_t work_on_byte()
{
    //int size = SIZE_ARRAY,i;

    //3 bites
    {
        printf("\n--------------\n3 BYTES\n---------\n");

        {

            ubyte vector_test_1[SIZE_ARRAY] = {255, 255, 255};
            ubyte vector_test_2[SIZE_ARRAY] = {83, 255, 255};
            printf("logic and:\n");
            print_bit_byte(vector_test_1, 3);
            printf("\n");        
            print_bit_byte(vector_test_2, 3);
            printf("\nRESULT\n");


            for(int i = 16; i < 24; ++i){

                ubyte* vector_result = vector_and(vector_test_1, vector_test_2, i);

                print_bit_byte(vector_result, 3);
                free(vector_result);
                printf("\n");
            }

        }


        {
            ubyte vector_test_1[SIZE_ARRAY] = {255, 255, 255};
            ubyte vector_test_2[SIZE_ARRAY] = {83, 255, 255};
            printf("logic or:\n");
            print_bit_byte(vector_test_1, 3);
            printf("\n");
            print_bit_byte(vector_test_2, 3);
            printf("\nRESULT\n");


            for(int i = 16; i < 24; ++i){

                ubyte* vector_result = vector_or(vector_test_1, vector_test_2, i);

                print_bit_byte(vector_result, 3);
                free(vector_result);
                printf("\n");
            }


        }


        {

            ubyte vector_test_1[SIZE_ARRAY] = {255, 255, 255};
            ubyte vector_test_2[SIZE_ARRAY] = {83, 255, 255};
            printf("logic xor:\n");
            print_bit_byte(vector_test_1, 3);
            printf("\n");
            print_bit_byte(vector_test_2, 3);
            printf("\n");


            for(int i = 16; i < 24; ++i){

                ubyte* vector_result = vector_xor(vector_test_1, vector_test_2, i);

                print_bit_byte(vector_result, 3);
                free(vector_result);
                printf("\n");
            }


        }

        printf("invert:\n");
        for(int i = 16; i < 24; ++i){
            ubyte vector_test[SIZE_ARRAY] = {1, 100, 128};
            print_bit_byte(vector_test, 3); 
            printf("\n");

            ubyte* vector_result = vector_invert(vector_test, i);

            print_bit_byte(vector_result, 3);
            printf("\n");
        }


        printf("shift right:\n");
        for(int i = 0; i < 24; ++i){
            ubyte vector_test[SIZE_ARRAY] = {255,255,255};

            vector_shift_right(vector_test, 24, i);
            print_bit_byte(vector_test, 3);
            printf("\n");

        }


        printf("shift left:\n");
        for(int i = 0; i < 24; ++i){
            ubyte vector_test[SIZE_ARRAY] = {255,255,255};
            
            printf("%i\n", i);
            vector_shift_left(vector_test, 24, i);
            print_bit_byte(vector_test, 3);
            printf("\n");

        }


        {
            printf("Convert str to vector\n");
            //convert

            char* str = "11111";
            printf("str - %s", str);

            ubyte* result = (ubyte*)calloc(sizeof(ubyte), 1);
            convert_string_2(str, 4, result);
            
            printf("vector - ");
            print_bit_byte(result, 1);
            printf("\n");
        }


        {
            printf("Convert str to vector\n");


            //convert
            char* str = (char*)calloc(sizeof(char),1);

            ubyte vector_test = 120;
            printf("vector - ");
            print_bit_byte(&vector_test, 1);
            printf("\n");


            convert_vector_2(&vector_test, 8, str);
            printf("str - %s\n",str);
        }

    }


    //1 bytes
    {
        printf("\n--------------\n1 BYTES\n---------\n");
        {

            ubyte vector_test_1[SIZE_ARRAY] = {255};
            ubyte vector_test_2[SIZE_ARRAY] = {83};

            printf("logic and:\n");
            print_bit_byte(vector_test_1, 1);
            printf("\n");        
            print_bit_byte(vector_test_2, 1);
            printf("\nRESULT\n");


            for(int i = 0; i < 8; ++i){

                ubyte* vector_result = vector_and(vector_test_1, vector_test_2, i);
        
                print_bit_byte(vector_result, 1);
                free(vector_result);
                printf("\n");
            }

        }


        {
            ubyte vector_test_1[SIZE_ARRAY] = {255};
            ubyte vector_test_2[SIZE_ARRAY] = {0};

            printf("logic or:\n");
            print_bit_byte(vector_test_1, 1);
            printf("\n");
            print_bit_byte(vector_test_2, 1);
            printf("\nRESULT\n");


            for(int i = 0; i < 8; ++i){

                ubyte* vector_result = vector_or(vector_test_1, vector_test_2, i);

                print_bit_byte(vector_result, 1);
                free(vector_result);
                printf("\n");
            }


        }


        {

            ubyte vector_test_1[SIZE_ARRAY] = {255};
            ubyte vector_test_2[SIZE_ARRAY] = {83};

            printf("logic xor:\n");
            print_bit_byte(vector_test_1, 1);
            printf("\n");
            print_bit_byte(vector_test_2, 1);
            printf("\n");


            for(int i = 0; i < 8; ++i){

                ubyte* vector_result = vector_xor(vector_test_1, vector_test_2, i);

                print_bit_byte(vector_result, 1);
                free(vector_result);
                printf("\n");
            }


        }

        printf("invert:\n");
        for(int i = 0; i < 8; ++i){
            ubyte vector_test[SIZE_ARRAY] = {255};
            print_bit_byte(vector_test, 1); 
            printf("\n");

            ubyte* vector_result = vector_invert(vector_test, i);

            print_bit_byte(vector_result, 1);
            printf("\n");
        }

        printf("shift right:\n");
        for(int i = 0; i < 8; ++i){
            ubyte vector_test[SIZE_ARRAY] = {255};
            
            vector_shift_right(vector_test, 8, i);
            print_bit_byte(vector_test, 1);
            printf("\n");

        }

        printf("shift left:\n");
        for(int i = 0; i < 8; ++i){
            ubyte vector_test[SIZE_ARRAY] = {255};
            
            vector_shift_left(vector_test, 8, i);
            print_bit_byte(vector_test, 3);
            printf("\n");

        }
        return 0;
        {
            //convert
            char* str = "11111";
            ubyte* result = (ubyte*)calloc(sizeof(ubyte), 1);
            convert_string_2(str, 4, result);
            print_bit_byte(result, 1);
            printf("\n");
        }

        {
            //convert
            char* str = (char*)calloc(sizeof(char),1);

            ubyte vector_test = 120;

            convert_vector_2(&vector_test, 8, str);
            printf("%s\n",str);
        }

        {

            for(int i = 0; i < 24; ++i){
            ubyte vector_test[SIZE_ARRAY] = {255,255,255};
            
            vector_shift_left(vector_test, 24, i);
            print_bit_byte(vector_test, 3);
            printf("\n");

            }
        }




    }


    return 0;
    /*
    //AND
    printf("First vector:  ");
    
    print_bit_byte(vector_one,size);
    
    printf("\n");
    printf("Second vector: ");
    
    print_bit_byte(vector_second,size);
    
    printf("\n");
    printf("&\n");
    
    bit_AND(vector_one,vector_second,vector_result,size);
    
    printf("Result vector:");
    
    print_bit_byte(vector_result,size);
    
    printf("\n--------------------------------------\n");
    
    //OR
    printf("First vector:  ");
    
    print_bit_byte(vector_one,size);
    
    printf("\n");
    printf("Second vector: ");
    
    print_bit_byte(vector_second,size);
    
    printf("\n");
    printf("|\n ");
    
    bit_OR(vector_one,vector_second,vector_result,size);
    
    printf("Result vector:");
    
    print_bit_byte(vector_result,size);
    
    printf("\n--------------------------------------\n");
    
    //XOR
    vector_result[0] = 0;
    vector_result[1] = 0;
    vector_result[2] = 0;
    
    printf("Vector: ");
    
    print_bit_byte(vector_one,size);
    
    printf("\n");
    printf("Vector: ");
    
    print_bit_byte(vector_second,size);
    
    printf("\n");
    printf("XOR\n");
    
    vector_XOR(vector_one,vector_second, vector_result,size);
    
    printf("Vector:");
    
    print_bit_byte(vector_result,size);
    
    printf("\n--------------------------------------\n");
    
    //Invert
    vector_result[0] = 0;
    vector_result[1] = 0;
    vector_result[2] = 0;
    
    printf("Vector: ");
    
    print_bit_byte(vector_one,size);
    
    printf("\n");
    printf("Invert\n ");
    
    vector_INVERT(vector_one,vector_result,size);
    
    printf("Vector:");
    
    print_bit_byte(vector_result,size);
    
    printf("\n--------------------------------------\n");
    
    //Convet_1
    char array[30] = "dada0dsa0das0sd0";
    size = 30;
    int memory_vector = ((size)/8)+1;
    ubyte *vector_convert = (ubyte*)calloc(sizeof(char),memory_vector);
    
    if (NULL == vector_convert)
    {
        return ERR_NOT_PTR;
    }
    
    printf("String:\n%s ",array);
    printf("\n");
    
    int bits = 30;
    convert_string_1(array,bits,vector_convert);
    
    printf("Vector: ");
    
    print_bit_byte(vector_convert,memory_vector);
    free(vector_convert);
    
    printf("\n--------------------------------------\n");
    
    //Convert_2
    vector_convert = (ubyte*)calloc(sizeof(char),memory_vector);
    
    if (NULL == vector_convert)
    {
        return ERR_NOT_PTR;
    }
    
    printf("String:\n%s ",array);
    printf("\n");
    
    bits = 30;
    convert_string_2(array,bits,vector_convert);
    
    printf("Vector: ");
    
    print_bit_byte(vector_convert,memory_vector);
    
    free(vector_convert);
    printf("\n--------------------------------------\n");
    
    //Shift_right
    vector_one[0] = 255;
    vector_one[1] = 255;
    vector_one[2] = 255;
    int N_byte = 3;
    int N_shift = 16;
    
    printf("Vector: ");
    
    print_bit_byte(vector_one,SIZE_ARRAY);
    
    printf("\n");
    printf("Shift right\n");
    
    vector_shift_right(vector_one, N_BIT_IN_BYTE*N_byte, N_shift);
    
    printf("Vector: ");
    
    print_bit_byte(vector_one,SIZE_ARRAY);
    
    printf("\n--------------------------------------\n");
    //Shift_left
    vector_one[0] = 255;
    vector_one[1] = 255;
    vector_one[2] = 255;
    N_byte = 3;
    N_shift = 16;
    
    printf("Vector: ");
    
    print_bit_byte(vector_one,SIZE_ARRAY);
    
    printf("\n");
    printf("Shift left\n");
    
    vector_shift_left(vector_one, N_BIT_IN_BYTE*N_byte, N_shift);
    
    printf("Vector: ");
    
    print_bit_byte(vector_one,SIZE_ARRAY);
    
    printf("\n--------------------------------------\n");
    //convert_vector_1
    
    size = 3;
    char *convert_array = (char*)calloc(sizeof(char),size * N_BIT_IN_BYTE);
    
    if (NULL == convert_array)
    {
        return ERR_NOT_PTR;
    }
    
    printf("Vector: ");
    
    print_bit_byte(vector_second,size);
    
    printf("\n");
    printf("Convet");
    printf("\n");
    
    convert_vector_1(vector_second,size * N_BIT_IN_BYTE, convert_array);
    
    printf("String: %s",convert_array);
    free(convert_array);
    printf("\n--------------------------------------\n");
    //convert_vector_2
    
    size = 3;
    convert_array = (char*)calloc(sizeof(char),size * N_BIT_IN_BYTE);
    
    if (NULL == convert_array)
    {
        return ERR_NOT_PTR;
    }
    
    printf("Vector: ");
    
    print_bit_byte(vector_second,size);
    
    printf("\n");
    printf("Convet");
    printf("\n");
    
    convert_vector_2(vector_second,size * N_BIT_IN_BYTE, convert_array);
    
    printf("String: %s",convert_array);
    free(convert_array);
    printf("\n--------------------------------------\n");
    return 0;
    */
}
