#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void sort(int arr[], int n)
{
    int i, key, j;
    for(i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while(j >= 0 && arr[j] > key){
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void print(int arr[], int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        printf("%d",arr[i]);
    }

    printf("\n");
}

int main()
{
    int arr[] = {13,19,9,5,12,8,7,4,21,2,6,11};
    int n = sizeof(arr) / sizeof(arr[0]);
    sort(arr,n);
    printf("Sort: \n");
    print(arr,n);
    return 0;
}