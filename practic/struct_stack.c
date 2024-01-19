#include<stdio.h>
#include <stdlib.h>

typedef struct NodeS
{
    char data;
    struct NodeS* next;

} node;

node* createStack()
{
    node* head = NULL;

    head = (node*)malloc(sizeof(node));
    if(NULL == head)
        return NULL;

    head->data = 0;
    head->next = NULL;

    return head;
}

int push(node** _last, char _symbol)
{
    node* newNode = NULL;
    newNode = (node*)malloc(sizeof(node));

    if (NULL == newNode)
        return -1;

    newNode->data = _symbol;
    newNode->next = *_last;
    *_last = newNode;

    return 0;
}

char pop(node** _node)
{
    if(NULL == _node && NULL == *_node)
    {
        char tmp = (*_node)->data;
        (**_node).data = 0;

        return tmp;
    }

    else
    {
        char tmpChar = (*_node)->data;

        node* tmpNode = *_node;
        *_node = (*_node)->next;

        free(tmpNode);

        return tmpChar;
    }
}

int main()
{
    node* pick = createStack();




}