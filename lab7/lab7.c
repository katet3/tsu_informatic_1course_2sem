#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//структура для каждого элемента списка
struct nodeList
{
	char inf;
	struct nodeList *next;
};

//структура стек, в ней нахоится голова списка и количество элементов
struct StekList
{
	struct nodeList *Top;//Вершина стека(голова на начало списка)
	int size;//количесвто элементов в стеке
};


//определяем новые имена для структур
typedef struct nodeList Node;
typedef struct StekList Stek;


//фунуция для того чтобы добавлять элемент в голову
bool Push(Stek *st, int value) 
{
    Node *el = (Node*)malloc(sizeof(Node));
	//проверка выделилась ли память 
	if (el) {
	    el->inf = value;
		el->next = NULL;
		if (st->Top == NULL) //если голова сейчас пуста, то указатель головы будет указывать на элемент
		{
			st->Top = el;
		}
		else //если же голова не пуста то говорим что новый элемент будет головой
		{
			el->next = st->Top;
			st->Top = el;
		}
		st->size++; //увеличиваем размер стека
		return true;
	}
	return false;
}

//функция взятия элемента из вершины стека
bool Pop(Stek *st, char* elem)
{
	//проверки на существование
	if(!elem) 
        return false;
    if(!(st -> Top))
        return false;

	*elem = st -> Top -> inf; //в elem кладем информаицю с вершины стека
	Node* newTop = st -> Top -> next;//запоминаем новую вершину, т.к. старую освободим после взятия
	free(st -> Top); // освободим старую вершину
	st -> Top = newTop; // передадим новую вершшину (ту которая была после старой)
	st -> size--; // уменьшим размер стека
	return true; 
}

//фунция только для просмотра вершины стека
bool ShowTop( Stek *st, char *value) 
{
	bool answer = false; // флаг, если удалось или не удалось просмотреть вершину
	if (value) { // если сущ value
		if (st->Top) //если сущ st.Top
		{
			*value = st->Top->inf; // кладем информацию из веришны стека
			answer = true; //переводим флаг в true
		}	
	}
	return answer; //возвращаем флаг
}

//проверка на то пуст ли стек 
bool IsEmpty(Stek *st)
{
	if (st->Top == NULL) //если вершина никуда не указывает то пуст
		return true;
	return false;// не пуст
}

//функция очистки стека, использую pop, т.к легче просто использовать готовую функцию
void Clear(Stek *st)
{
	char* empty_tmp = calloc(2,sizeof(char)); //создаю буферную переменную типа char для того чтобы перевдавать его в функицю
	while(st -> size != 0) //пока размер стека не 0 вызывае функцию Pop и таким образом очищаем стек
	{
		Pop(st,empty_tmp); 
	}
	free(empty_tmp); //освобождаем память под буферную переменную 
}

//функция проверки на символ ('a'  - 'z', '0' - '9') с помощью кодов ASCII
bool IsSymbol(char inf)
{
    if (inf > 47 && inf < 58)
		return true;
	if(inf > 96 && inf < 123)
		return true;

    return false;
}

//функция проверки на оператор
bool IsOperator(char inf)
{
	switch (inf)
	{
	case '+':
	case '-': 
	case '*':
	case '/': 
    case ')':
    case '(':
		return true;
	default:
		return false;
	}
}

//функция вывода стека
void PrintStek(Stek *st)
{
	if(IsEmpty(st) || st->size == 0) //проверяем, если стек пуст, то выводим что он пуст
		printf("Stek is empty\n");
	Node *tmp_print = st->Top;//если не пуст то создадим указатель на вершину стека чтобы не потерять саму вершину

	while(tmp_print != NULL) //пока не дошли до конца стека 
	{
		printf("%c\n", tmp_print->inf); //выводим то, что лежит в поле inf 
		tmp_print = tmp_print -> next; //и переходим дальше по стеку
	}
}

bool Fgets_my(char *str, int size)//функция чтобы при вводе с клавиатуры УБИРАТЬ \n(Enter)
{
    char *fgets_result = fgets(str, size, stdin);//считываем строку с клавиатуры и после нажатия enter ставиться в конец \0
    //fgets возвращает указатель на строку (str)
    if (fgets_result != str)//сверяем что указатели равны, если нет то ошибка
        return false;

    int len = strlen(str);//strlen возвращает число символов до \0 => число символов + 1 перенос строки (\n Enter) его будем убирать

    if ( len > 0 && str[len-1] == '\n')//заменяем \n на \0 проверив правда ли с клавиатуры сичталось \n(Enter)
        str[len-1] = '\0';

    return true;
}
bool IsStekCorrect(Stek *st) //функция проверки стека (достаем по 3 элемента, 1ел - символ 2ел- оператор 3ел - символ)иначе ошибка
//стек будет правильным, если мы проверим выражение без скобок и за место этого выражения в стеке останется один элемент
//этот элемент должен быть результатом выражения
{
    //printf("5\n");
    //PrintStek(st);
        char sym1, oper, sym2;
        while(1) //
        {
            if(st->size >= 3)
            {
                //printf("10\n");
                Pop(st, &sym1);
                Pop(st, &oper);
                Pop(st, &sym2);
                if(IsSymbol(sym1) && IsOperator(oper) && IsSymbol(sym2))
                {
                    //printf("8\n");
                    //PrintStek(st);
                    Push(st, 'r');
                    //printf("9\n");
                    //PrintStek(st);
                }
                else
                    return false;
            }
            else
            {
                if(st->size == 1 && ShowTop(st, &sym1) && sym1 == 'r')
                    return true;
                else
                    return false;
            }
        }
}


bool IsExpressionCorrect(char *expression)
{
    if (!expression)    //проверяем, что строка expression не является пустой.
        return false;

    Stek* st = (Stek*)malloc(sizeof(Stek));   //создается стек stack
    if (!st)
        return false;

    st->size = 0;    //стек инициализируется пустым
    st->Top = NULL;  

    char tmpelem;
    int counter_of_bracers = 0; // счетчик для скобок
    int i = 0; //шаг по выражению

    while(expression[i]) //пока не конец выражения
    {
        if(!(IsSymbol(expression[i]) || IsOperator(expression[i])))//если символ не попадает в диапазон значений то ошибка
        {
            //printf("6\n");
            return false;
        }

        Push(st, expression[i]);
        if(expression[i] == '(') // если встретили открывающую скобку 
        {
            Pop(st, &tmpelem); //достаем открывающую скобку из стека
            counter_of_bracers++; // увеличиваем счетчик скобок
            if(ShowTop(st, &tmpelem) && IsSymbol(tmpelem)) //если перед скобкой стоит символ то выражение не верно
            {
                //printf("1\n");
                //PrintStek(st);
                return false;
            }
        }
        if(expression[i] == ')') //если встретили закрывающую скобку
        {
            Pop(st, &tmpelem); //достаем закрывающую скобку из стека 
            counter_of_bracers--; //уменьшаем счетчик скобок
            //теперь в стеке должно остаться правильное выражение, проверим стек и если все правльно то в конце проверки 
            //в стек положим результат
            if(!(IsStekCorrect(st)))
            {
                //printf("2\n");
                //PrintStek(st);
                return false;
            }
        } 
        i++;
    }
    if(counter_of_bracers != 0)
        return false;
    if(IsStekCorrect(st))
    {
        //printf("3\n");
        //PrintStek(st);
        return true;
    }
    else
    {
        //printf("4\n");
        //PrintStek(st);
        return false;
    }
}

int main()
{
    char expression[100];
    printf("Enter string: ");  
    if(!Fgets_my(expression, 100))
    {
        printf("Error! Failed to write string.\n");
    }

    if(IsExpressionCorrect(expression))
        printf("correct");
    else
        printf("incorrect");
    
    return 0;
}