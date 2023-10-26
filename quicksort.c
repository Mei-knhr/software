#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
    return;
}

int partition(int arr[], int p, int r) {
    int x = arr[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (arr[j] <= x) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[r]);
    return i + 1;
}

void sort(int arr[], int p, int r) {
    if (p < r) {
        int q = partition(arr, p, r);
        sort(arr, p, q - 1);
        sort(arr, q + 1, r);
    }
}

void print(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    sort(arr, 0, n - 1);
    printf("Sort: \n");
    print(arr, n);
    return 0;
}
