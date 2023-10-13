#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct list {
    struct list *next;
    int data;
};

void search(struct list *p){
    while(p != NULL)
    {
        printf("%d\n" , p -> data);
        p = p -> next;
    }
}

int main(){
    struct list *p, *q;
    struct list *s;
    p = malloc(sizeof(struct list));
    p->data = 1;
    s = p;
    for(int i = 0; i < 99; i++)
    {
        q = malloc(sizeof(struct list));
        p -> next = q;
        q -> data = p -> data + 1;
        p = q;
    }

    q->next = NULL;
    search(s);
    exit(0);
}

