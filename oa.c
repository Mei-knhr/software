#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define SIZE 10000000

struct DataItem /*構造体*/
{
    int data;
    int key;  
};

struct DataItem * arr[SIZE];
struct DataItem * item;

int hash(int key)
{
    return key % SIZE;
}

struct DataItem * search(int key)
{
    int hashIndex = hash(key);
    while (arr[hashIndex] != NULL)
    {
        if (arr[hashIndex] -> key == key)
            return arr[hashIndex];

        hashIndex += 2;
    }

    return NULL;
}

void insert(int key)
{
    struct DataItem *item = (struct DataItem *)malloc(sizeof(struct DataItem));
    item -> key = key;

    int hashIndex = hash(key);

    while(arr[hashIndex] != NULL )
    {
        hashIndex += 2;
    }

    arr[hashIndex] = item;
}

int main()
{
    for (int i = 0; i < 10000000; i++)
    {
        insert(i);
    }
    for(int i = 0; i < 1001; i++){
        item = search(i);
    }
    if(item != NULL)
    {
        printf("found: %d\n", item->key);
    }
    else
    {
        printf("not found\n");
    }
}


