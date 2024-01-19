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
    printf("HEAD %d\n", *(head->size));
    return head;
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
    //newNode->size = (*_last)->size + 1;
    newNode->size = (*_last)->size;

    *(newNode->size) += 1;

    printf("HEAD push %d\n", *(newNode->size));

    *_last = newNode;
}

char pop(node** _node)
{
    if(NULL == _node || NULL == *_node)
    {
        return 0;
    }

    if((*_node)->parent == NULL)
    {
        //char tmp = (*_node)->symbol;
        //(**_node).symbol = 0;
        *((*_node)->size) = 0;


        return 0;
    }

    else
    {
        char tmpChar = (*_node)->symbol;

        node* tmpNode = *_node;
        *_node = (*_node)->parent;
        //printf("1\n");
        free(tmpNode);

        *((*_node)->size) -= 1;
            printf("HEAD pop %d\n", *((*_node)->size));

        return tmpChar;
    }
}

bool try_get_last(node* _last, char* _value) 
{
    if(NULL == _last || NULL == _last->parent)
        return false;

	bool result = false; // флаг, если удалось или не удалось просмотреть вершину
	
    if (_value) { // если сущ value
		//if (_last) //если сущ st.Top
		//{
			*_value = _last->symbol; // кладем информацию из веришны стека
			result = true; //переводим флаг в true
		//}	
	}
	return result; //возвращаем флаг
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

bool IsStekCorrect(node** _last) //функция проверки стека (достаем по 3 элемента, 1ел - символ 2ел- оператор 3ел - символ)иначе ошибка
//стек будет правильным, если мы проверим выражение без скобок и за место этого выражения в стеке останется один элемент
//этот элемент должен быть результатом выражения
{
    //printf("5\n");
    //PrintStek(st);
        char sym1 = 0, oper = 0, sym2 = 0;
        while(1) //
        {
            //printf("this size %i\n", *(_last->size));
            if(*((*_last)->size) >= 3)
            {
                //printf("10\n");
                sym1 = pop(&(*_last));
//printf("%c %d %u\n", _last->symbol, *(_last->size), _last->parent);

                oper = pop(&(*_last));
//printf("%c %d %u\n", _last->symbol, *(_last->size), _last->parent);


                sym2 = pop(&(*_last));
//printf("%c %d %u\n", _last->symbol, *(_last->size), _last->parent);

             //   printf("sym2 %c\n", _last->symbol);


                if(isSymbol(sym1) && isOperation(oper) && isSymbol(sym2))
                {
                  //  printf("%c %d %u\n", _last->symbol, *(_last->size), _last->parent);

                    //sym1 = pop(&_last);
                // try_get_last(_last, &sym1);
                //     //printf("8\n");
                // printf("%c\n", sym1);
                // printf("%d\n", *(_last->size));

                // printf("sym2 %c\n", _last->symbol);
                    //PrintStek(st);
                    
                    push(&(*_last), 'r');
                    //printf("9\n");
                    //PrintStek(st);
                            //printf("222\n");
                    return true;
                }
                else
                    return false;
            }

            
            else
            {
                //try_get_last(&(*_last), &sym1);
                //printf("%c\n", sym1);
                //printf("%d\n", *(_last->size));

                if(*(*_last)->size == 1 && try_get_last((*_last), &sym1) && sym1 == 'r')
                    return true;
                
                
                else
                    return false;
            }
        }
}

int main()
{
    node* tip = createStack();

    char* expression = NULL;
    int size = 100;
    pop(&tip);

//printf("%c %d %u\n", tip->symbol, (tip->size), tip->parent);

    expression = (char*)calloc(size, sizeof(char));
    if (NULL == expression)
        return ERR_NOT_PTR;

    fgets(expression, size, stdin);
    printf("%s", expression); 




    char tmpelem;
    int counter_of_bracers = 0; // счетчик для скобок
    int i = 0; //шаг по выражению

    while(expression[i] && expression[i] != '\n') //пока не конец выражения
    {
            //printf("%d ", *(tip->size)); 

                                printf("%c\n", expression[i]);
//printf("%c %d %u\n", tip->symbol, *(tip->size), tip->parent);

        if(!(isSymbol(expression[i]) || isOperation(expression[i])))//если символ не попадает в диапазон значений то ошибка
        {
            printf("-1\n");
                        //printf("%i\n", expression[i]);

            return false;
        }

        push(&tip, expression[i]);
        if(expression[i] == '(') // если встретили открывающую скобку 
        {
            tmpelem = pop(&tip); //достаем открывающую скобку из стека
            counter_of_bracers++; // увеличиваем счетчик скобок
            
            if(try_get_last(tip, &tmpelem) && isSymbol(tmpelem)) //если перед скобкой стоит символ то выражение не верно
            {
                printf("-2\n");
                //PrintStek(st);
                return false;
            }
        }
        if(expression[i] == ')') //если встретили закрывающую скобку
        {
            tmpelem = pop(&tip); //достаем закрывающую скобку из стека
                                            printf("%c\n", tmpelem);
 
            counter_of_bracers--; //уменьшаем счетчик скобок
            //теперь в стеке должно остаться правильное выражение, проверим стек и если все правльно то в конце проверки 
            //в стек положим результат
            
            if(!(IsStekCorrect(&tip)))
            {
                printf("-3\n");
                //PrintStek(st);
                return false;
            }
            //printf("%c %d %u\n", tip->symbol, *(tip->size), tip->parent);

        } 
        i++;
    }

    if(counter_of_bracers != 0)
    {
        printf("-4\n");
        return false;
    }
    
    printf("ТУТ ПИЗДА...\n");
    
printf("%c %d %u\n", tip->symbol, *(tip->size), tip->parent);
    
    if(IsStekCorrect(&tip))
    {
        printf("+\n");
        //PrintStek(st);
        return true;
    }

    else
    {
        printf("-5\n");
        //PrintStek(st);
        return false;
    }
    
}