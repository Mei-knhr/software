#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int arr[10000];
int i;

int binary_search (int K, int m, int n)
{
    int i;
    int j;
    int p;
    
    i = m; 
    j = n;
    while(i <= j)
    {
        p = (i+j)/2;
        if (K  < arr[p])j = p-1;
        else if (K > arr[p])i = p+1;
        else if (K == arr[p]) return p;
    }
    return -1;
}

int main()
{
    for (i = 0; i < 1000; i++){
        arr[i] = (i + 1);
    }

    printf("%d\n",arr[binary_search(4,1,1000)]);
}

