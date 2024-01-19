/*
  [0-9][-, +, *, /][0-9] +
  [(][0-9][-, +, *, /][0-9][)] +

  [(][0-9][-, +, *, /][0-9] -
  [0-9][-, +, *, /][0-9][)] -

  ![0-9][-, +, *, /][0-9] -
  [0-9][-, +, *, /]![0-9] -
  [0-9]![-, +, *, /][0-9] -
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#define ERR_NOT_PTR 400
typedef int error_code_t;


typedef struct nodeS
{
        char symbol;
        struct nodeS* parent;
        size_t* size;
}node;


node* createStack()
{
    node* head = NULL;

    head = (node*)malloc(sizeof(node));
    if(NULL == head)
        return NULL;

    head->symbol = 0;
    head->parent = NULL;
    head->size = (size_t*)calloc(sizeof(size_t), 1);
    
    if(head->size == NULL)
    {    
        free(head);
        return NULL;
    }

    *(head->size) = 0;
    return head;
}


error_code_t clear_stack(node** _last)
{
    if(_last == NULL || *_last == NULL)
    {
        return ERR_NOT_PTR;
    }


    for(node* current_node = *_last; (*_last)->parent != NULL; current_node = *_last)
    {
        *_last = (*_last)->parent;
        free(current_node);
    }

    free(*_last);
    *_last = NULL;
    return 0;

}


error_code_t push(node** _last, char _symbol)
{
    if(_last == NULL || *_last == NULL)
    {
        return ERR_NOT_PTR;
    }

    node* newNode = NULL;
    newNode = (node*)malloc(sizeof(node));

    if (NULL == newNode)
        return ERR_NOT_PTR;

    newNode->symbol = _symbol;
    newNode->parent = *_last;
    newNode->size = (*_last)->size;

    *(newNode->size) += 1;

    *_last = newNode;
    return 0;
}


char pop(node** _node)
{
    if(NULL == _node || NULL == *_node)
    {
        return 0;
    }

    if((*_node)->parent == NULL)
    {
        *((*_node)->size) = 0;
        return 0;
    }

    else
    {
        char tmpChar = (*_node)->symbol;

        node* tmpNode = *_node;
        *_node = (*_node)->parent;
        free(tmpNode);

        *((*_node)->size) -= 1;
        return tmpChar;
    }
}


bool try_get_last(node* _last, char* _value) 
{
    if(NULL == _last || NULL == _last->parent)
        return false;

	bool result = false;
	
    if (_value) 
    {
        *_value = _last->symbol;
        result = true;
    }
	return result;
}

bool isSymbol(char _symbol)
{
    if (((47 < _symbol) && (_symbol < 58)) || ((96 < _symbol) && (_symbol < 123)))
    {
        return true;
    }

    return false;
}

bool isOperation(char _symbol)
{
    if (
        (_symbol == '+')||
        (_symbol == '-')||
        (_symbol == '*')||
        (_symbol == '/')||
        (_symbol == '(')||
        (_symbol ==')')
        )
    {
        return true;
    }

    return false;
}

error_code_t IsStekCorrect(node** _last)
{
    if(_last == NULL || *_last == NULL)
    {
        return ERR_NOT_PTR;
    }


    char sym1 = 0, oper = 0, sym2 = 0;
    while(1)
    {
        if(*((*_last)->size) >= 3)
        {
            sym1 = pop(&(*_last));
            oper = pop(&(*_last));
            sym2 = pop(&(*_last));

            if(isSymbol(sym1) && isOperation(oper) && isSymbol(sym2))
            {   
                push(&(*_last), 'f');
                return 0;
            }

            else
                return -1;
        }

        
        else
        {
            if(*(*_last)->size == 1 && try_get_last((*_last), &sym1) && sym1 == 'f')
                return 0;
            
            
            else
                return -1;
        }
    }
}


int main()
{
    node* tip = createStack();

    char* expression = NULL;
    int size = 100;
    pop(&tip);

    expression = (char*)calloc(size, sizeof(char));
    if (NULL == expression)
        return ERR_NOT_PTR;

    fgets(expression, size, stdin);
    printf("%s", expression); 




    char tmpelem;
    int counter_of_bracers = 0;
    int i = 0;

    while(expression[i] && expression[i] != '\n')
    {
        if(!(isSymbol(expression[i]) || isOperation(expression[i])))
        {
            printf("-1\n");
            return false;
        }

        push(&tip, expression[i]);
        if(expression[i] == '(')
        {
            tmpelem = pop(&tip);
            counter_of_bracers++;
            
            if(try_get_last(tip, &tmpelem) && isSymbol(tmpelem))
            {
                printf("-2\n");
                return false;
            }
        }
        if(expression[i] == ')')
        {
            tmpelem = pop(&tip);
            counter_of_bracers--;
            
            if(IsStekCorrect(&tip))
            {
                printf("-3\n");
                return false;
            }
        } 
        i++;
    }

    if(counter_of_bracers != 0)
    {
        printf("-4\n");
        return false;
    }
    

    if(!IsStekCorrect(&tip))
    {
        printf("+\n");
        return true;
    }

    else
    {
        printf("-5\n");
        return false;
    }
    
}