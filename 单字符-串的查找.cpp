#include <stdio.h>
#include <conio.h>

typedef struct node
{
    char data;
    node *link;
} *STRING;

int Index(STRING S, STRING S1)
{
    node *p, *q, *first;
    
    if (S!=NULL && S1!=NULL)
    {
         p = first = S, q = S1;
         while (p!=NULL)
         {
              if (p->data == q->data)
              {
                   q = q->link;
                   if (q != NULL)
                       return first;
                   p = p->link;
              }
              else
              {
                   first = first->link;
                   p = first;
                   q = S1;
         
              }
         }
    }
    
    return NULL;
}

int main()
{
    
}
