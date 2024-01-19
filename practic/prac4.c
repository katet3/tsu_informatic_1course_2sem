#include <string.h>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> 
#define ERR_NOT_PTR 1
#define ERR_CALL 2

typedef int error_code_t;

error_code_t freeMatrix(   
    char **Matrix,
    size_t size
    )
{
    if (Matrix)
    {
        for (int ix=0;ix < size;ix++)
        {
            free(Matrix[ix]);
            Matrix[ix] = NULL;
        }
        free(Matrix);
        Matrix = NULL;
        return 0;
    }
    else
        return ERR_NOT_PTR ;

}
error_code_t add_random_words(
    char* array,
    size_t size
    )
{
    if (array)
    {
        for (int ix = 0; ix < size; ix++)
        {
            array[ix] = (rand() % 75) + 48;
        }
        return 0;
    }
    else
    {
        return ERR_NOT_PTR;
    }
}

char** CreateArray_for_Str(
    size_t nRow, 
    size_t nCol
    )
{
    char **ppMtx = NULL;
    ppMtx = (char**)calloc(nRow, sizeof(char*));
    if(ppMtx)
    {
        for (int i = 0; i < nRow; ++i)
        {
            ppMtx[i] = (char*)calloc(nCol, sizeof(char));
            if(ppMtx[i] == NULL)
            {
                free(ppMtx);
                ppMtx = NULL;
                return ppMtx;
            }
        }
        return ppMtx;
    }
    else
    {
        return ppMtx;
    }
}

void PrintMx(
    char** mx,
    size_t nn,
    size_t mm
    )
{
    if (mx)
    {
        for (int ix = 0; ix < nn; ix++)
        {
            //Проверяем, существует ли строка, если существует то выводим ее, в портивном случае выводим занчение NULL
            // Такая проверка является обязательной, в случае разреженной матрицы
            if (mx[ix]) 
            {
                printf("%s", mx[ix]);
                /* вывод для матрици из чисел
                for (int jx = 0; jx < mm; jx++)
                {
                    printf("%d ", mx[ix][jx]);
                }
                printf("\n");
                */
                printf("\n");
            }
            else
                printf("NULL\n\n");
        }
    }
    else
        printf("Matrix is Empty\n");
}
error_code_t Filling_array(
    char** ppMx,
    size_t nRow, 
    size_t nCol
    )
{
    if (ppMx)
    {
        for (int ix = 0; ix < nRow; ix++)
        {
            if(add_random_words(ppMx[ix], nCol))
                return ERR_CALL;
        }
        return 0;
    }
    else
    {
        return ERR_NOT_PTR;
    }
}
error_code_t input_matrix(
    char **CharMatrix,
    size_t nn, 
    size_t mm
    )
{
    if (CharMatrix)
    {
        for (int ix = 0; ix < nn; ix++)
        {
            fgets(CharMatrix[ix],mm,stdin);
        }
        return 0;  
    }
    else
    {
        return ERR_NOT_PTR;
    }
}

error_code_t delete_string(
    char **str, 
    int size
    )
{
    if (str)
    {
        free(*str);
        *str = NULL;
        /*
        for (int i = 0;i < size;i++)
        {
            str[i] = '\0';
        }
        */
        return 0;
    }
    else
        return ERR_NOT_PTR;
}

error_code_t swap(
        char **CharMatrix,
        size_t i,
        size_t j)
{
    if (
        (CharMatrix == NULL) ||
        (CharMatrix[i] == NULL) ||
        (CharMatrix[j] == NULL)
       )
       {
           return ERR_NOT_PTR;
       }

    char* tmp = NULL;
    tmp = CharMatrix[i];
    CharMatrix[i] = CharMatrix[j];
    CharMatrix[j] = tmp;

    return 0;
}

error_code_t sort_matrix_name(
    char **CharMatrix,
    size_t nRow,
    size_t nCol
    )
{
    if (CharMatrix == NULL) {
        return ERR_NOT_PTR;
    }
    int flag = 0;
    for (int ix = 0;ix < nRow-1 ;ix++)
    {
        if (CharMatrix[ix] == NULL) {
            continue;
        }

        for (int jx = ix + 1; jx < nRow; jx++)
        {
            if (CharMatrix[jx] == NULL) {
                continue;
            };

            flag = strcmp(CharMatrix[ix],CharMatrix[jx]);
            
            if (flag > 0)
            {
                swap(CharMatrix, ix, jx);
            };

            if ((flag == 0) && delete_string(&CharMatrix[jx],nCol))
            {
                return ERR_CALL;
            };
        };
    };
    return 0;
};

bool check_programm(
    char **Matrix,
    size_t nRow,
    size_t nCol
    )
{        
    int flag = 0; 

    for (int i = 0, j = 1; i < nRow - j; i = j, j = j+1)
    {
        if(NULL == Matrix[i])
        {
            continue;
        };

        while((i+j < nRow) && NULL == Matrix[i + j])
        {
            j++;
        };

        if (!(i+j < nRow))
        {
            break;
        };
        
        int flag = strcmp(Matrix[i],Matrix[i+j]);
        
        if ((flag > 0) || (flag == 0))
            return false;
    };
    
    return true;
};

bool Input_from_console()
{
    int nRow = 5,nCol = 100;
    char **CharMatrix = CreateArray_for_Str(nRow, nCol); 
    if(CharMatrix == NULL)
    {
        return false;
    }

    printf("Pleas, enter your last name below: \n");

    if (input_matrix(CharMatrix, nRow, nCol))
    {
        return false;
    }

    printf("--------------------------\n");
    printf("Entered from the console  |\n");
    printf("--------------------------\n");
    PrintMx(CharMatrix, nRow, nCol); 

    printf("---------------------\n");
    printf("Before               |\n");
    printf("---------------------\n");

    PrintMx(CharMatrix, nRow, nCol); 

    printf("---------------------\n");
    printf("Sorted               |\n");
    printf("---------------------\n");

    if(sort_matrix_name(CharMatrix,nRow, nCol))
        return false;
    PrintMx(CharMatrix, nRow, nCol); 
/*
    if(check_programm(CharMatrix, nRow, nCol) == false)
    {
        printf("Sort,none \n");
        return false;
    }
*/
    if (freeMatrix(CharMatrix, nRow))
        return false;
    return true;
}

bool Input_random()
{
    //srand() позволяет запускать программу несколько раз с различными последователь­ностями псевдослучайных чисел
    srand((unsigned int) time(NULL));
    int nRow = 5,nCol = 20;
    char **CharMatrix = CreateArray_for_Str(nRow, nCol); 
    if(!CharMatrix)
    {
        return 0;
    }

    if (Filling_array(CharMatrix, nRow, nCol))
        return false;

    PrintMx(CharMatrix, nRow, nCol); 

    printf("---------------------\n");
    printf("Before               |\n");
    printf("---------------------\n");

    PrintMx(CharMatrix, nRow, nCol); 

    printf("---------------------\n");
    printf("Sorted               |\n");
    printf("---------------------\n");

    if(sort_matrix_name(CharMatrix,nRow, nCol))
        return false;

    PrintMx(CharMatrix, nRow, nCol);
    if(check_programm(CharMatrix, nRow, nCol) == false)
    {
        printf("Sort,none \n");
        return false;
    }
    if(freeMatrix(CharMatrix, nRow))
        return false;

    return true;
}

int main()
{ 
    
    if (!Input_from_console())
    {
        return 1;
    };

    /*    
    if (!Input_random())
    {
        return 1;
    } 
    */
    return 0;
}