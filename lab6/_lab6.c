#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h>
#include <string.h>


#define SIZE_ARRAY 3
#define N_BIT_IN_BYTE 8


typedef int error_code_t;
#define ERR_NOT_PTR 1


typedef unsigned char ubyte;


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
    size_t bits_one,
    size_t bits_second,
    size_t bytes
    )
{
    if((vector_one == NULL) || (vector_second == NULL))
        return NULL;


    if(bits_one >= bits_second)
    {
        if((bits_one/8)+1 > bytes)
        {
            return NULL;
        }

        ubyte* vector_result = (ubyte*)calloc(sizeof(ubyte), bytes);
        if(NULL == vector_result)
            return NULL;


        int i, j;
        for(i = bytes-1, j = bits_second/8; i >= 0 && j >= 0; --i, --j)
        {
            vector_result[i] = vector_one[i] & vector_second[j];
        }


        while (i>=0)
        {
            vector_result[i] = vector_one[i] & vector_result[i];
            --i;
        }
        
        return vector_result;
    }

    else
    {
        if((bits_second/8)+1 > bytes)
        {
            return NULL;
        }

        //int bytes = ((bits_second)/8)+1;
        ubyte* vector_result = (ubyte*)calloc(sizeof(ubyte), bytes);
        if(NULL == vector_result)
            return NULL;


        int i, j;
        for(i = bytes - 1, j = bits_one/8; i >= 0 && j >= 0; --i, --j)
        {
            vector_result[i] = vector_one[j] & vector_second[i];
        }


        while (i>=0)
        {
            vector_result[i] = vector_second[i] & vector_result[i];
            --i;
        }

        return vector_result;
    }
    
    return 0;
}


ubyte* vector_or(
    ubyte* vector_one, 
    ubyte* vector_second, 
    size_t bits_one,
    size_t bits_second,
    size_t bytes
    )
{
    if((vector_one == NULL) || (vector_second == NULL))
        return NULL;


    if(bits_one >= bits_second)
    {
        if((bits_one/8)+1 > bytes)
        {
            return NULL;
        }
     
     
        ubyte* vector_result = (ubyte*)calloc(sizeof(ubyte), bytes);
        if(NULL == vector_result)
            return NULL;


        int i, j;
        for(i = bytes-1, j = bits_second/8; i >= 0 && j >= 0; --i, --j)
        {
            printf("%d %d\n", i, j);
            vector_result[i] = vector_one[i] | vector_second[j];
        }


        while (i>=0)
        {
            vector_result[i] = vector_one[i] | vector_result[i];
            --i;
        }
        

        return vector_result;
    }

    else
    {
        if((bits_second/8)+1 > bytes)
        {
            return NULL;
        }
        //int bytes = ((bits_second)/8)+1;
        ubyte* vector_result = (ubyte*)calloc(sizeof(ubyte), bytes);
        if(NULL == vector_result)
            return NULL;


        int i, j;
        for(i = bytes - 1, j = bits_one/8; i >= 0 && j >= 0; --i, --j)
        {
            vector_result[i] = vector_one[j] | vector_second[i];
        }


        while (i>=0)
        {
            vector_result[i] = vector_second[i] | vector_result[i];
            --i;
        }


        return vector_result;
    }
}


ubyte* vector_xor(
    ubyte* vector_one, 
    ubyte* vector_second, 
    size_t bits_one,
    size_t bits_second,
    size_t bytes
    )
{
    if((vector_one == NULL) || (vector_second == NULL))
        return NULL;


    if(bits_one >= bits_second)
    {
        if((bits_one/8)+1 > bytes)
        {
            return NULL;
        }

        ubyte* vector_result = (ubyte*)calloc(sizeof(ubyte), bytes);
        if(NULL == vector_result)
            return NULL;


        int i, j;
        for(i = bytes-1, j = bits_second/8; i >= 0 && j >= 0; --i, --j)
        {
            printf("%d %d\n", i, j);
            vector_result[i] = vector_one[i] ^ vector_second[j];
        }


        while (i>=0)
        {
            vector_result[i] = vector_one[i] ^ vector_result[i];
            --i;
        }
        

        return vector_result;
    }

    else
    {
        if((bits_second/8)+1 > bytes)
        {
            return NULL;
        }

        //int bytes = ((bits_second)/8)+1;
        ubyte* vector_result = (ubyte*)calloc(sizeof(ubyte), bytes);
        if(NULL == vector_result)
            return NULL;


        
        
        int i, j;
        for(i = bytes - 1, j = bits_one/8; i >= 0 && j >= 0; --i, --j)
        {
            vector_result[i] = vector_one[j] ^ vector_second[i];
        }


        while (i>=0)
        {
            vector_result[i] = vector_second[i] ^ vector_result[i];
            --i;
        }

        return vector_result;
    }
}


ubyte* vector_invert(
    ubyte* vector,
    size_t bits,
    size_t bytes
    )
{
    
    if(vector == NULL)
        return NULL;

 
    if((bits/8)+1 > bytes)
    {
        return NULL;
    }


    ubyte* vector_result = (ubyte*)calloc(sizeof(ubyte), bytes);
    if(NULL == vector_result)
        return NULL;


    int i, j;

    for(i = bytes-1, j = bits/8; i >= 0 && j >= 0; --i, --j)
    {
        vector_result[i] = ~vector[i];
    }


    if((bits+1) % 8 != 0)
    {
        ubyte mask = (255 >> (8-((bits+1)%8)));
        vector_result[i+1] = ~vector[i+1];
        vector_result[i+1] &= mask;
    }
    

    return vector_result;

}


error_code_t vector_shift_left(
    ubyte *vector, 
    size_t size, 
    size_t k
    )
{
    if(NULL == vector)
        return ERR_NOT_PTR;

    
    ubyte before_save = 0;
    ubyte  after_save = 0;
    size_t _bytes = size;
    if (k >= 8)
    {
        size_t full_shift = k / 8;

        while (full_shift)
        {
            before_save = 0;
            after_save = 0;
            
            while (_bytes)
            {
                before_save = vector[_bytes - 1];
                vector[_bytes - 1] <<= 8;

                if (after_save)
                {
                    vector[_bytes - 1] = after_save;
                }

                after_save = before_save;
                _bytes--;
            }

            full_shift--;
            _bytes = size;
        }
        k = k % 8;
    }


    
    _bytes = size - (k/8);
    before_save = 0;
    after_save = 0;

    while (_bytes)
    {
        before_save = vector[_bytes - 1];
        vector[_bytes - 1] <<= k;

        if (after_save)
        {
            vector[_bytes - 1] = vector[_bytes - 1] | (after_save >> (8 - k));
        }

        after_save = before_save;
        _bytes--;
    }
}


error_code_t vector_shift_right(
    ubyte *vector, 
    size_t size, 
    size_t k)
{
    if(NULL == vector)
        return ERR_NOT_PTR;

    
    ubyte before_save = 0;
    ubyte  after_save = 0;
    size_t _bytes = 0;
    if (k >= 8)
    {
        size_t full_shift = k / 8;

        while (full_shift)
        {
            before_save = 0;
            after_save = 0;
            
            while (_bytes < size)
            {
                before_save = vector[_bytes];
                vector[_bytes] >>= 8;

                if (after_save)
                {
                    vector[_bytes] = after_save;
                }

                after_save = before_save;
                _bytes++;
            }

            full_shift--;
            _bytes = 0;
        }
        k = k % 8;
    }


    _bytes = 0;
    before_save = 0;
    after_save = 0;

    while (_bytes < size)
    {
        before_save = vector[_bytes];
        vector[_bytes] >>= k;

        if (after_save)
        {
            vector[_bytes] = vector[_bytes] | (after_save << (8 - k));
        }

        after_save = before_save;
        _bytes++;
    }
}


error_code_t change_bit(
    ubyte* vector,
    bool bit,
    size_t digit,
    size_t bytes
)

{
    //индексация с нуля
    size_t bits = (bytes*N_BIT_IN_BYTE)-1;
    size_t n_cel = (digit) / 8;
    size_t n_bit = (bits-digit) % 8;
    

    if (vector == NULL)
        return ERR_NOT_PTR;


    if((digit/8)+1 > bytes)
    {
        return -1;
    }
        
    if (bit == false){
        vector[n_cel] = vector[n_cel] & (~(1 << n_bit));
    }
    else
        vector[n_cel] = vector[n_cel] | (1 << n_bit);

    return 0;
}


error_code_t convert_string_2(
    char* string,
    size_t bytes,
    ubyte* vector)
{
    if(vector == NULL || string == NULL)
        return ERR_NOT_PTR;
        
    size_t n_cel;
    size_t n_bit;
    

    size_t bits = (bytes*N_BIT_IN_BYTE  )-1;
    for(int i = 0, j = bits; j >= 0 && string[i]; i++, j--)
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
    
    return 0;
}


error_code_t convert_vector_2(
    ubyte *arr, 
    size_t bits, 
    char *string)
{
    if (NULL == arr || NULL == string)
    {
        return ERR_NOT_PTR;
    }

    size_t n_cel;
    size_t n_bit;
    int i,j;
    
    for(i = 0, j = bits-1; i < bits;i++,j--)
    {
        n_cel = j / 8;
        n_bit = i % 8;
    
        if(arr[n_cel] & (1 << n_bit))
        {
            string[i] = '1';
        }
    
        else
            string[i] = '0';
    }
    
    string[i] = '\0';
    return 0;
}


/*
UNIT TEST
*/
error_code_t case_logic_or()
{
    printf("\n----------------\nlogic or:\n----------------\n");
    {
        char* vec_1 = "1111111111111111111111111111111111111111111111111111";
        char* vec_2 = "1100111";
        
        size_t len_1 = strlen(vec_1)-1;
        size_t len_2 = strlen(vec_2)-1;
        size_t bytes_1 = ((len_1)/8)+1;
        size_t bytes_2 = ((len_2)/8)+1;

        ubyte* vector_result_1 = (ubyte*)calloc(sizeof(ubyte), bytes_1);
        ubyte* vector_result_2 = (ubyte*)calloc(sizeof(ubyte), bytes_2);

        convert_string_2(vec_1, bytes_1, vector_result_1);
        convert_string_2(vec_2, bytes_2, vector_result_2);


        print_bit_byte(vector_result_1, bytes_1);
        printf("\n");        

        print_bit_byte(vector_result_2, bytes_2);
        printf("\nRESULT\n");

        ubyte* vector_result = vector_or(vector_result_1, vector_result_2, len_1, len_2, bytes_1);

        print_bit_byte(vector_result, bytes_1);
        
        free(vector_result);
        free(vector_result_1);
        free(vector_result_2);
    }


    printf("\n----------------\nlogic or:\n----------------\n");
    {
        char* vec_1 = "11001111";
        char* vec_2 = "111111111";

        size_t len_1 = strlen(vec_1)-1;
        size_t len_2 = strlen(vec_2)-1;
        size_t bytes_1 = ((len_1)/8)+1;
        size_t bytes_2 = ((len_2)/8)+1;

        ubyte* vector_result_1 = (ubyte*)calloc(sizeof(ubyte), bytes_1);
        ubyte* vector_result_2 = (ubyte*)calloc(sizeof(ubyte), bytes_2);

        convert_string_2(vec_1, bytes_1, vector_result_1);
        convert_string_2(vec_2, bytes_2, vector_result_2);


        print_bit_byte(vector_result_1, bytes_1);
        printf("\n");        

        print_bit_byte(vector_result_2, bytes_2);
        printf("\nRESULT\n");

        ubyte* vector_result = vector_or(vector_result_1, vector_result_2, len_1, len_2, bytes_2);

        print_bit_byte(vector_result, bytes_2);
        
        free(vector_result);
        free(vector_result_1);
        free(vector_result_2);
    }
}


error_code_t case_logic_and()
{
    printf("\n----------------\nlogic and:\n----------------\n");
    {
        char* vec_1 = "1111111111111111111111111111111111111111111111111111";
        char* vec_2 = "1100111";
        
        size_t len_1 = strlen(vec_1)-1;
        size_t len_2 = strlen(vec_2)-1;
        size_t bytes_1 = (len_1/8)+1;
        size_t bytes_2 = (len_2/8)+1;

        ubyte* vector_result_1 = (ubyte*)calloc(sizeof(ubyte), bytes_1);
        ubyte* vector_result_2 = (ubyte*)calloc(sizeof(ubyte), (len_2/8)+1);

        convert_string_2(vec_1, bytes_1, vector_result_1);
        convert_string_2(vec_2, (len_2/8)+1, vector_result_2);


        print_bit_byte(vector_result_1, bytes_1);
        printf("\n");        

        print_bit_byte(vector_result_2, (len_2/8)+1);
        printf("\nRESULT\n");

        ubyte* vector_result = vector_and(vector_result_1, vector_result_2, len_1, len_2, bytes_1);

        print_bit_byte(vector_result, bytes_1);
        
        free(vector_result);
        free(vector_result_1);
        free(vector_result_2);
    }


    printf("\n----------------\nlogic and:\n----------------\n");
    {
        char* vec_1 = "11001111";
        char* vec_2 = "1111111111";

        size_t len_1 = strlen(vec_1)-1;
        size_t len_2 = strlen(vec_2)-1;
        size_t bytes_1 = ((len_1)/8)+1;
        size_t bytes_2 = ((len_2)/8)+1;

        ubyte* vector_result_1 = (ubyte*)calloc(sizeof(ubyte), bytes_1);
        ubyte* vector_result_2 = (ubyte*)calloc(sizeof(ubyte), bytes_2);

        convert_string_2(vec_1, bytes_1, vector_result_1);
        convert_string_2(vec_2, bytes_2, vector_result_2);


        print_bit_byte(vector_result_1, bytes_1);
        printf("\n");        

        print_bit_byte(vector_result_2, bytes_2);
        printf("\nRESULT\n");

        ubyte* vector_result = vector_and(vector_result_1, vector_result_2, len_1, len_2, bytes_2);

        print_bit_byte(vector_result, bytes_2);
        
        free(vector_result);
        free(vector_result_1);
        free(vector_result_2);
    }
}


error_code_t case_logic_xor()
{
    printf("\n----------------\nlogic xor:\n----------------\n");
    {
        char* vec_1 = "1111111111111";
        char* vec_2 = "1100111";
        
        size_t len_1 = strlen(vec_1)-1;
        size_t len_2 = strlen(vec_2)-1;
        size_t bytes_1 = (len_1/8)+1;
        size_t bytes_2 = (len_2/8)+1;


        ubyte* vector_result_1 = (ubyte*)calloc(sizeof(ubyte), bytes_1);
        ubyte* vector_result_2 = (ubyte*)calloc(sizeof(ubyte), bytes_1);

        convert_string_2(vec_1, bytes_1, vector_result_1);
        convert_string_2(vec_2, bytes_2, vector_result_2);


        print_bit_byte(vector_result_1, bytes_1);
        printf("\n");        

        print_bit_byte(vector_result_2, bytes_2);
        printf("\nRESULT\n");

        ubyte* vector_result = vector_xor(vector_result_1, vector_result_2, len_1, len_2, bytes_1);

        print_bit_byte(vector_result, bytes_1);
        
        free(vector_result);
        free(vector_result_1);
        free(vector_result_2);
    }


    printf("\n----------------\nlogic xor:\n----------------\n");
    {
        char* vec_1 = "11001111";
        char* vec_2 = "1111111111";
        size_t len_1 = strlen(vec_1)-1;
        size_t len_2 = strlen(vec_2)-1;

        size_t bytes_1 = ((len_1)/8)+1;
        size_t bytes_2 = ((len_2)/8)+1;

        ubyte* vector_result_1 = (ubyte*)calloc(sizeof(ubyte), bytes_1);
        ubyte* vector_result_2 = (ubyte*)calloc(sizeof(ubyte), bytes_2);

        convert_string_2(vec_1, bytes_1, vector_result_1);
        convert_string_2(vec_2, bytes_2, vector_result_2);


        print_bit_byte(vector_result_1, bytes_1);
        printf("\n");        

        print_bit_byte(vector_result_2, bytes_2);
        printf("\nRESULT\n");

        ubyte* vector_result = vector_xor(vector_result_1, vector_result_2, len_1, len_2, bytes_2);

        print_bit_byte(vector_result, bytes_2);
        
        free(vector_result);
        free(vector_result_1);
        free(vector_result_2);
    }
}


error_code_t case_logic_invert()
{
    printf("\n----------------\nlogic invert:\n----------------\n");
    {
        char* vec_1 = "00000000";
        
        size_t len_1 = strlen(vec_1)-1;
        size_t bytes_1 = (len_1/8)+1;

        ubyte* vector_result_1 = (ubyte*)calloc(sizeof(ubyte), bytes_1);

        convert_string_2(vec_1, bytes_1, vector_result_1);

        print_bit_byte(vector_result_1, bytes_1);
        
        printf("\n");        
        printf("\nRESULT\n");

        ubyte* vector_result = vector_invert(vector_result_1, len_1, bytes_1);

        print_bit_byte(vector_result, bytes_1);
        
        free(vector_result);
        free(vector_result_1);
    }
}


error_code_t case_change_bit()
{
    printf("\n----------------\nchange bit 0:\n----------------\n");
    {
        char* vec_1 = "11111111111111111111111111111111111111111111111111111111";
        
        size_t len_1 = strlen(vec_1)-1;
        size_t bytes_1 = (len_1/8)+1;

        printf("\nRESULT\n");

        ubyte* vector_result_1 = (ubyte*)calloc(sizeof(ubyte), bytes_1);  
        convert_string_2(vec_1, bytes_1, vector_result_1);     
        for(int i = 0; i < len_1+1; ++i)
        {

            change_bit(vector_result_1, false, i, bytes_1);

            print_bit_byte(vector_result_1, bytes_1);
            printf("\n");  

        }
        free(vector_result_1);
    }


    printf("\n----------------\nchange bit 1:\n----------------\n");
    {
        char* vec_1 = "00000000000000000000000000000000000000000000000000000000";
        
        size_t len_1 = strlen(vec_1)-1;
        size_t bytes_1 = (len_1/8)+1;

        printf("\nRESULT\n");

        ubyte* vector_result_1 = (ubyte*)calloc(sizeof(ubyte), bytes_1);  
        convert_string_2(vec_1, bytes_1, vector_result_1);     
        for(int i = 0; i < len_1+1; ++i)
        {

            change_bit(vector_result_1, true, i, bytes_1);

            print_bit_byte(vector_result_1, bytes_1);
            printf("\n");  

        }
        free(vector_result_1);
    }
}


/*
error_code_t case_shift_right()
{
    printf("\n----------------\nshift right:\n----------------\n");
    {
        char* vec_1 = "11111111111111111111111111111111111111111111111111111111";
        
        size_t len_1 = strlen(vec_1)-1;
        size_t bytes_1 = (len_1/8)+1;

        printf("\nRESULT\n");

        for(int i = 0; i < len_1+2; ++i)
        {
            ubyte* vector_result_1 = (ubyte*)calloc(sizeof(ubyte), bytes_1);  
            convert_string_2(vec_1, bytes_1, vector_result_1);     

            vector_shift_right(vector_result_1, bytes_1, i);

            print_bit_byte(vector_result_1, bytes_1);
            printf("\n");  

            free(vector_result_1);
        }
    }

}
*/

error_code_t case_shift_right()
{
    printf("\n----------------\nshift right:\n----------------\n");
    {
        //char* vec_1 = "11111111111111111111111111111111111111111111111111111111";
        char* vec_1 = "00000000000000000000000000000000000000000000000000000000";
        
        size_t len_1 = strlen(vec_1)-1;
        size_t bytes_1 = (len_1/8)+1;

        printf("\nRESULT\n");

        ubyte* vector_result_1 = (ubyte*)calloc(sizeof(ubyte), bytes_1);  
        convert_string_2(vec_1, bytes_1, vector_result_1);     
        

        ubyte* vector_result_2 = vector_invert(vector_result_1, 55, bytes_1);
        for(int i = 0; i < len_1; ++i)
        {

            vector_shift_left(vector_result_2, bytes_1, 1);

            print_bit_byte(vector_result_2, bytes_1);
            printf("\n");  

        }
        free(vector_result_1);
    }

}


/*
error_code_t case_shift_left()
{
    printf("\n----------------\nshift left:\n----------------\n");
    {
        char* vec_1 = "11111111111111111111111111111111111111111111111111111111";
        
        size_t len_1 = strlen(vec_1)-1;
        size_t bytes_1 = (len_1/8)+1;

        printf("\nRESULT\n");

        ubyte* vector_result_1 = (ubyte*)calloc(sizeof(ubyte), bytes_1);  
        for(int i = 0; i < len_1+2; ++i)
        {
            convert_string_2(vec_1, bytes_1, vector_result_1);     

            vector_shift_left(vector_result_1, bytes_1, i);

            print_bit_byte(vector_result_1, bytes_1);
            printf("\n");  

        }
        free(vector_result_1);
    }

}
*/


error_code_t case_shift_left()
{
    printf("\n----------------\nshift left:\n----------------\n");
    {
        char* vec_1 = "11111111111111111111111111111111111111111111111111111111";
        
        size_t len_1 = strlen(vec_1)-1;
        size_t bytes_1 = (len_1/8)+1;

        printf("\nRESULT\n");

        ubyte* vector_result_1 = (ubyte*)calloc(sizeof(ubyte), bytes_1);  
        for(int i = 0; i < len_1+2; ++i)
        {
            convert_string_2(vec_1, bytes_1, vector_result_1);     

            vector_shift_left(vector_result_1, bytes_1, i);

            print_bit_byte(vector_result_1, bytes_1);
            printf("\n");  

        }
        free(vector_result_1);
    }

}


error_code_t case_convert_vector()
{
    printf("\n----------------\nconvert vector:\n----------------\n");
    {
        char* vec_1 = "11111111111111111111111111111111111111111111111111111111";
        
        size_t len_1 = strlen(vec_1)-1;
        size_t bytes_1 = (len_1/8)+1;

        ubyte* vector_result_1 = (ubyte*)calloc(sizeof(ubyte), bytes_1);

        convert_string_2(vec_1, bytes_1, vector_result_1);

        print_bit_byte(vector_result_1, bytes_1);
        
        printf("\n");        
        printf("\nRESULT\n");
        char* vec_res = (char*)calloc(sizeof(char), len_1+1);

        convert_vector_2(vector_result_1, len_1+1, vec_res);

        int div = 1;
        for(int i = 0; i < len_1+1;)
        {
            
            printf("%c", vec_res[i]);
            if(div%8==0)
            {
                printf(" ");
                div=1;
                ++i;
                continue;
            }

            ++i;
            ++div;
        }

        free(vector_result_1);
    }
}


int main()
{
    /*
    case_logic_or();
    case_logic_and();
    case_logic_xor();

    case_logic_invert();
    case_change_bit();
    */
    case_change_bit();

    //case_shift_right();
    //case_shift_left();
    
    //case_convert_vector();

    return 0;
}