#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int NUMBEROFTEST = 1024;
#define BILLION 1000000000.0;
typedef struct{
    int length;
    char typeOfSort;
}inputData;

typedef struct{
    int *pArrayToSort;
}outputData;

 void bubbleSort(int * pArray, int howMany);
 void quickSort(int * pArray, int start, int end);
 void mergeSort(int* pArray, int length);
 void mergeSortHelp(int * pArray, int * pTempArray, int start, int end);
 void merge(int * pArray, int * pTempArray, int leftStart, int mid, int rightEnd);
 void swap(int *x, int *y);
 void gnome_sort(int *arr, int n);
 void comb_sort(int *arr, int n);
 void cocktail_sort(int *arr, int n);
 void insertion_sort(int *arr, int n);
 void odd_even_sort(int *arr, int n);
 void shell_sort(int *arr, int n);
 void selection_sort(int *arr, int n);
 void radix_sort(int* arr, int n);
 int find_largest_number(int arr[], int n);
 int pancake_sort(int* arr, int n);
 void flip(int *arr, int i) ;
 int find_max(int *arr, int n);
 void heap_sort(int *a, int n);
 void build_heap(int *a, int n);
 void satisfy_heap(int *a, int i, int heap_size);
//************************************** READING INPUT FROM FILE **************************************** /
void readingInput(inputData *dataCPU, outputData* dataOut){
    int index =0;
    int length;
    char type;
    int ret = fscanf(stdin, "%d %c ",&length,&type);
    while(ret != EOF){
        dataCPU[index].length = length;
        dataCPU[index].typeOfSort = type;
        dataOut[index].pArrayToSort = (int*)malloc(length * sizeof(int));
        int i;
        for(i=0; i<length; i++)
            fscanf(stdin, "%d ",  &dataOut[index].pArrayToSort[i]);
        index++;
        ret = fscanf(stdin, "%d %c ",&length,&type);
    }
    NUMBEROFTEST = index;
}

//************************************* Writing time in a FILE ******************************************
void writeFile(double time, char* fileName){
    FILE *fp1;
    fp1 = fopen("CPUResults.txt", "a");
    if (fp1 == NULL){
        printf("Problem in a file");
        return;
    }
    fprintf(fp1, "%s ", fileName);
    fprintf(fp1, "%f seconds\n", time);
    fclose(fp1);
}
int main (int args, char* argv[])
{
    inputData *dataCPU = (inputData*)malloc(sizeof(inputData)* NUMBEROFTEST);
    outputData *dataOut = (outputData*)malloc(sizeof(outputData)* NUMBEROFTEST);
    readingInput(dataCPU,dataOut);
    struct timespec end, start;
    int index=0,i;
    clock_gettime(CLOCK_REALTIME, &start);
    for(index=0; index<NUMBEROFTEST;index++){
        switch(dataCPU[index].typeOfSort){
            case 'b' :
            printf("Using bubblesort\n");
            bubbleSort(dataOut[index].pArrayToSort, dataCPU[index].length);
            break;
            case 'q' :
            printf("Using quicksort\n");
            quickSort(dataOut[index].pArrayToSort, 0, dataCPU[index].length - 1);
            break;
            case 'm' :
            printf("Using mergesort\n");
            mergeSort(dataOut[index].pArrayToSort, dataCPU[index].length);
            break;
            case 'o' :
            printf("Using odd_even_sort\n");
            odd_even_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
            break;
            case 'c' :
            printf("Using cocktail_sort\n");
            cocktail_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
            break;
            case 't' :
            printf("Using comb_sort\n");
            comb_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
            break;
            case 'g' :
            printf("Using gnome_sort\n");
            gnome_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
            break;
            case 'i' :
            printf("Using insertion_sort\n");
            insertion_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
            break;
            case 'h' :
            printf("Using shell_sort\n");
            shell_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
            break;
            case 's' :
            printf("Using selection_sort\n");
            selection_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
            break;
            case 'r' :
            printf("Using radix_sort\n");
            radix_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
            break;
            case 'p' :
            printf("Using pancake_sort\n");
            pancake_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
            break;
            case 'u' :
            printf("Using heap_sort\n");
            heap_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
            break;
            default:
            printf("No Correct Sort Chosen\n");
            break;
        }
    }
    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - start.tv_sec) +  	(end.tv_nsec - start.tv_nsec) / BILLION;
    writeFile(time_spent,argv[1]);

    for(;index< NUMBEROFTEST; index++) {
        printf("ID# %d ", index, dataCPU[index].length);

        for(i = 0 ; i < dataCPU[index].length ; i++){
            printf("%d ", *(dataOut[index].pArrayToSort + i));
        }
        printf("\n");
    }

    return 0;
}

/*
bubbleSort
sorts the array using the bubbleSort algorithm
*/
 void bubbleSort(int * pArray, int howMany){
    int i;
    int j;
    for(i = 0 ; i < howMany - 1 ; i++){
        for(j = 0 ; j < howMany - 1 ; j++){
            if(*(pArray + j) > *(pArray + j + 1)){
                swap((pArray + j), (pArray+j+1));
            }
        }
    }
    return;
}

/*
quickSort
sorts algorithm using the quicksort algorithm
*/
 void quickSort(int * pArray, int start, int end){
    if(start < end){
        int pivot = *(pArray + end);
        int swapPos = start-1;
        int i;
        for(i = start; i < end ; i++){
            if(*(pArray + i) < pivot){
                swapPos++;
                swap((pArray + i), (pArray + swapPos));
            } else {
                continue;
            }
        }
        swapPos++;
        swap((pArray + swapPos), (pArray + i));
        if(start < swapPos - 1){
            quickSort(pArray, start, swapPos - 1);
        }
        if(swapPos + 1 < end){
            quickSort(pArray, swapPos + 1, end);
        }
    }

    return;
}

/*
mergeSort
main mergesort functions that creates the temp array and passes
args to the helper
*/
 void mergeSort(int * pArray, int length){

    int * pTempArray;
    pTempArray = (int *) malloc(length * sizeof(int));

    mergeSortHelp(pArray, pTempArray, 0, length-1);
    return;
}

/*
mergeSortHelp
recursively calls itself on its left and right halves and then calls merge
on both of them
*/
 void mergeSortHelp(int * pArray, int * pTempArray, int start, int end){
    if(start < end){
        int mid = (start+end)/2;

        mergeSortHelp(pArray, pTempArray, start, mid);
        mergeSortHelp(pArray, pTempArray, mid + 1, end);

        merge(pArray, pTempArray, start, mid, end);
    }

    return;
}

/*
merge
merges two sorted list into one complete sorted list
*/
 void merge(int * pArray, int * pTempArray, int leftStart, int mid, int rightEnd){
    int size = rightEnd - leftStart + 1;

    int lIndex = leftStart;
    int rIndex = mid + 1;
    int index = leftStart;

    while(lIndex <= mid && rIndex <= rightEnd){
        if(*(pArray + lIndex) <= *(pArray + rIndex)){
            *(pTempArray + index) = *(pArray + lIndex);
            lIndex++;
        } else {
            *(pTempArray + index) = *(pArray + rIndex);
            rIndex++;
        }
        index++;
    }

    while(lIndex <= mid){
        *(pTempArray + index) = *(pArray + lIndex);
        lIndex++;
        index++;
    }

    while(rIndex <= rightEnd){
        *(pTempArray + index) = *(pArray + rIndex);
        rIndex++;
        index++;
    }

    index = leftStart;
    while(index <= rightEnd){
        *(pArray + index) = *(pTempArray + index);
        index++;
    }

    return;

}

 void swap(int *x, int *y){
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
    return;
}

/********* https://github.com/eddyerburgh/c-sorting-algorithms******/
 void odd_even_sort(int *arr, int n) {
    bool sorted = false;  // Initially array is unsorted
    int temp;

    while (!sorted) {
        sorted = true;
	int i;
        // Perform Bubble sort on odd indexed element
        for (i = 1; i <= n - 2; i += 2) {
            if (arr[i] > arr[i + 1]) {
                temp = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = temp;
                sorted = false;
            }
        }

        // Perform Bubble sort on even indexed element
        for (i = 0; i <= n - 2; i += 2) {
            if (arr[i] > arr[i + 1]) {
                temp = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = temp;
                sorted = false;
            }
        }
    }
}
 void cocktail_sort(int *arr, int n) {
    bool swapped = true;
    int i = 0;
    int j = n - 1;

    while (i < j && swapped) {
        swapped = false;
        int k;
        for (k = i; k < j; k++) {
            if (arr[k] > arr[k + 1]) {
                int temp = arr[k];
                arr[k] = arr[k + 1];
                arr[k + 1] = temp;
                swapped = true;
            }
        }
        j--;
        if (swapped) {
            swapped = false;
            int k;
            for (k = j; k > i; k--) {
                if (arr[k] < arr[k - 1]) {
                    int temp = arr[k];
                    arr[k] = arr[k - 1];
                    arr[k - 1] = temp;
                    swapped = true;
                }
            }
        }
        i++;
    }
}

 void comb_sort(int *arr, int n) {
    int temp;
    int i;
    int j;
    int gap = n;
    int shrink = 3;
    bool swapped;

    while (gap != 1 || swapped == true) {
        gap = (gap / shrink);
        if (gap < 1) {
            gap = 1;
        }
        swapped = false;
        int i;
        for (i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                temp = arr[i + gap];
                arr[i + gap] = arr[i];
                arr[i] = temp;
                swapped = true;
            }
        }
    }
}

 void gnome_sort(int *arr, int n) {
    int i = 0;
    int temp;

    while (i < n) {
        if (i == 0 || arr[i] >= arr[i - 1]) {
            i++;
        } else {
            temp = arr[i];
            arr[i] = arr[i - 1];
            arr[i - 1] = temp;
            i--;
        }
    }
}
 void insertion_sort(int *arr, int n) {
    int i;
    for (i = 0; i < n; i++) {
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j]) {
            int temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
            j--;
        }
    }
}

 void shell_sort(int *arr, int n) {
    int j;
    int gap;
    for (gap = n / 2; gap > 0; gap /= 2) {
        int i;
        for (i = gap; i < n; ++i) {
            int temp = arr[i];
            for (j = i; j >= gap && temp < arr[j - gap]; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

 void selection_sort(int *arr, int n) {
    int i, j;

    for (j = 0; j < n - 1; j++) {
        int iMin = j;

        for (i = j + 1; i < n; i++) {
            if (arr[i] < arr[iMin]) {
                iMin = i;
            }
        }

        if (iMin != j) {
            int temp = arr[j];
            arr[j] = arr[iMin];
            arr[iMin] = temp;
        }
    }
}

 int find_largest_number(int *arr, int n) {

    int i;
    int largest_number = -1;

    for (i = 0; i < n; i++) {
        if (arr[i] > largest_number) largest_number = arr[i];
    }

    return largest_number;
}

 void radix_sort(int* arr, int n) {

    // Base 10 is used
    int i;
    int *semi_sorted = (int*)malloc(n*sizeof(int));
    int significant_digit = 1;
    int largest_number = find_largest_number(arr, n);

    // Loop until we reach the largest significant digit
    while (largest_number / significant_digit > 0) {


        int bucket[10] = {0};

        // Counts the number of "keys" or digits that will go into each bucket
        for (i = 0; i < n; i++) bucket[(arr[i] / significant_digit) % 10]++;

        /**
         * Add the count of the previous buckets,
         * Acquires the indexes after the end of each bucket location in the arr
         * Works similar to the count sort algorithm
         **/
        for (i = 1; i < 10; i++) bucket[i] += bucket[i - 1];

        // Use the bucket to fill a "semi_sorted" arr
        for (i = n - 1; i >= 0; i--)
        semi_sorted[--bucket[(arr[i] / significant_digit) % 10]] = arr[i];


        for (i = 0; i < n; i++) arr[i] = semi_sorted[i];

        // Move to next significant digit
        significant_digit *= 10;
    }
}

 void flip(int *arr, int i) {
    int temp, start = 0;
    while (start < i) {
        temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
        start++;
        i--;
    }
}

 int find_max(int *arr, int n) {
    int mi, i;
    for (mi = 0, i = 0; i < n; ++i)
    if (arr[i] > arr[mi]) mi = i;
    return mi;
}


 int pancake_sort(int* arr, int n) {
    int curr_size;
    for (curr_size = n; curr_size > 1; --curr_size) {
        int mi = find_max(arr, curr_size);
        if (mi != curr_size - 1) {
            flip(arr, mi);

            flip(arr, curr_size - 1);
        }
    }
}
 void heap_sort(int a[], int n) {
    build_heap(a, n);
    int heap_size, i, temp;
    heap_size = n - 1;
    for (i = heap_size; i >= 0; i--) {
        temp = a[0];
        a[0] = a[heap_size];
        a[heap_size] = temp;
        heap_size--;
        satisfy_heap(a, 0, heap_size);
    }
}

 void build_heap(int a[], int n) {
    int i, heap_size;
    heap_size = n - 1;
    for (i = (n / 2); i >= 0; i--) {
        satisfy_heap(a, i, heap_size);
    }
}

 void satisfy_heap(int a[], int i, int heap_size) {
    int l, r, largest, temp;
    l = 2 * i;
    r = 2 * i + 1;
    if (l <= heap_size && a[l] > a[i]) {
        largest = l;
    } else {
        largest = i;
    }
    if (r <= heap_size && a[r] > a[largest]) {
        largest = r;
    }
    if (largest != i) {
        temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        satisfy_heap(a, largest, heap_size);
    }
}
