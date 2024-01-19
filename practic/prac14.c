#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ERR_NOT_PTR 1
#define NULL_PTR 2

typedef int error_code_t;

typedef struct nodeS{
        int xx;
        int yy;
        struct nodeS* nx;
    }node;

//Создание списка
error_code_t createListTail(node* _first, int count)
{
    if (NULL == _first && count >= 0)
    {
        return ERR_NOT_PTR;
    }

    node* currentNode = NULL;
    node* newNode = NULL;

    //Создадим новый узел и установим голову на данный узел
    newNode = (node*)malloc(sizeof(node));
    
    if (NULL == newNode)
    {            
        return ERR_NOT_PTR;
    }

    newNode->xx = 0;
    newNode->yy = 0;
    newNode->nx = NULL;

    _first->nx = newNode;
    currentNode = newNode;

    for (int i = 1; i < count; i++)
    {
        newNode = (node*)malloc(sizeof(node));

        if(NULL == newNode)
        {
            return ERR_NOT_PTR;
        }
        
        newNode->xx = i;
        newNode->yy = i;
        newNode->nx = NULL;

        currentNode->nx = newNode;
        currentNode = newNode;
    }

    return 0;
}

error_code_t addBeforeAttribute(
    node** _head, 
    int xx, 
    int yy, 
    int attributeFirst, 
    int attributeSecond
    )
{
    if(NULL == _head)
    {
        return ERR_NOT_PTR;
    }

    //Вставка в голову
    if(
        (*_head)->xx == attributeFirst 
        && (*_head)->yy == attributeSecond
        )
    {
        node* newNode = (node*)malloc(sizeof(node));
        
        if(NULL == newNode)
        {
            return ERR_NOT_PTR;
        }

        newNode->xx = xx;
        newNode->yy = yy;
        newNode->nx = *_head;
        
        *_head = newNode;

        return 0; 
    }

    //Если не голова
    node* current = NULL;
    node* lastNode = NULL;

    for (current = *_head; 
        NULL != current 
        && (current->xx != attributeFirst || current->yy != attributeSecond);
        current = current->nx)
    {
        lastNode = current;
    }

    if (NULL == current)
    {
        return NULL_PTR;
    }

    node* newNode = NULL;
    newNode = (node*)malloc(sizeof(node));
    
    if(NULL == newNode)
    {
        return ERR_NOT_PTR;
    }
    
    newNode->xx = xx;
    newNode->yy = yy;
    newNode->nx = current;

    lastNode->nx = newNode;
    return 0;
}

int main()
{
    node* head = NULL;
    head = (node*)malloc(sizeof(node));
    
    head->xx = -1;
    head->yy = -1;
    head->nx = NULL;

    createListTail(head, 10);

    printf("Before:\n");
    node* current = NULL;
    for (current = head; current != NULL; current = current->nx)
    {
        printf("%d %d %d\n", current->xx, current->yy, current->nx);
    }
    
    addBeforeAttribute(&head, -3, -3, -1, -1);

    printf("After:\n");
    current = NULL;
    for (current = head; current != NULL; current = current->nx)
    {
        printf("%d %d %d\n", current->xx, current->yy, current->nx);
    }
}