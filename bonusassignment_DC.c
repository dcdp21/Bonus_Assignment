#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void merge(int arr[], int l, int m, int r)
{
    int i, j , k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *left = (int*)malloc(n1 * sizeof(int));
    int *right = (int*)malloc(n2 * sizeof(int));
    extraMemoryAllocated += 2;

    for (i = 0; i < n1; i++)
        left[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        right[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
    free(left);
    free(right);
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void insertionSort(int* arr, int n)
{
    int i, key, j;
    for(i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while(j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void bubbleSort(int* arr, int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int* arr, int n)
{
    int i, j, min_idx, temp;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

int parseData(char *inputFileName, int **pData)
{
    FILE* inFile = fopen(inputFileName,"r");
    int dataSize = 0;
    *pData = NULL;

    if (inFile)
    {
        fscanf(inFile,"%d\n",&dataSize);
        *pData = (int *)malloc(sizeof(int) * dataSize);
        if(*pData){
            for (int i = 0; i < dataSize; ++i)
            {
                fscanf(inFile, "%d\n", &((*pData)[i]));
            }
        }
    }

    return dataSize;
}

void printArray(int arr[], int dataSize)
{
    int i, size = dataSize - 100;
    printf("\tData:\n\t");
    for (i=0; i<100; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n\t");

    for (i=size; i<dataSize; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}

int main(void)
{
    clock_t start, end;
    int i;
    double cpu_time_used;
    char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};

    for (i=0; i<3; ++i)
    {
        int *dataSrc, *dataCopy;
        int dataSize = parseData(fileNames[i], &dataSrc);

        if (dataSize <= 0)
            continue;

        dataCopy = (int *)malloc(sizeof(int)*dataSize);

        printf("---------------------------\n");
        printf("Dataset Size : %d\n", dataSize);
        printf("---------------------------\n");

        printf("Selection Sort:\n");
        memcpy(dataCopy, dataSrc, dataSize*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        selectionSort(dataCopy, dataSize);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
        printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
        printArray(dataCopy, dataSize);

        printf("Insertion Sort:\n");
        memcpy(dataCopy, dataSrc, dataSize*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        insertionSort(dataCopy, dataSize);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
        printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
        printArray(dataCopy, dataSize);

        printf("Bubble Sort:\n");
        memcpy(dataCopy, dataSrc, dataSize*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        bubbleSort(dataCopy, dataSize);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
        printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
        printArray(dataCopy, dataSize);

        printf("Merge Sort:\n");
        memcpy(dataCopy, dataSrc, dataSize*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        mergeSort(dataCopy, 0, dataSize - 1);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
        printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
        printArray(dataCopy, dataSize);

        free(dataCopy);
        free(dataSrc);
    }
}
