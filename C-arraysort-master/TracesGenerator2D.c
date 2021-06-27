#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int NUMBEROFTEST = 1024;

unsigned long long int counter=0;
unsigned long long int MaxNumber = 0;//9223372036854775807;
unsigned long long int NumberOfBranch = 73;
int testID= 0;
unsigned long long int visited[1024][73];

typedef struct{
    int length;
    char typeOfSort;
}inputData;

typedef struct{
    int *pArrayToSort;
}outputData;

void bubble_sort(int * pArray, int howMany);
void quick_sort(int * pArray, int start, int end);
void merge_sort(int* pArray, int length);
void merge(int* pArray, int* pTempArray, int leftStart, int* mid, int rightEnd);
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



void write(){
    FILE *fp1;
    fp1 = fopen("Traces2D.txt", "a");
    if (fp1 == NULL){
        printf("Problem in a file");
        return;
    }
    int i,j;
    for(i=0; i<NUMBEROFTEST; i++){
        for(j=0; j<NumberOfBranch; j++){
            if(visited[i][j] ==-1)
                visited[i][j] = NumberOfBranch * MaxNumber;
            fprintf(fp1, "%lu ", visited[i][j]);
        }
        fputs("\n",fp1);
    }
    fclose(fp1);
}

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
     //   printf("INDEX %d %c ", index, type);
        ret = fscanf(stdin, "%d %c ",&length,&type);
    }
    NUMBEROFTEST = index;
}

int main (int args, char* argv[])
{
    inputData *dataCPU = (inputData*)malloc(sizeof(inputData)* NUMBEROFTEST);
    outputData *dataOut = (outputData*)malloc(sizeof(outputData)* NUMBEROFTEST);
    readingInput(dataCPU,dataOut);
    int index=0,i,j;
    for(i=0; i<NUMBEROFTEST; i++)
        for(j=0; j<NumberOfBranch; j++)
            visited[i][j]=0;

    for(index=0; index<NUMBEROFTEST;index++){
        testID = index;
        counter =0;
        switch(dataCPU[index].typeOfSort){
            case 'b' :
                printf("Using bubblesort\n");
                bubble_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
                visited[testID][0] = -1;
                counter++;
                break;
            case 'q' :
                printf("Using quicksort\n");
                quick_sort(dataOut[index].pArrayToSort, 0, dataCPU[index].length - 1);
                visited[testID][1] = -1;
                counter++;
                break;
            case 'm' :
                 printf("Using mergesort\n");
                merge_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
                visited[testID][2] = -1;
                counter++;
                break;
            case 'o' :
                 printf("Using odd_even_sort\n");
                odd_even_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
                visited[testID][3] = -1;
                counter++;
                break;
            case 'c' :
                  printf("Using cocktail_sort\n");
                cocktail_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
                visited[testID][4] = -1;
                counter++;
                break;
            case 't' :
                  printf("Using comb_sort\n");
                comb_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
                visited[testID][5] = -1;
                counter++;
                break;
            case 'g' :
                 printf("Using gnome_sort\n");
                gnome_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
                visited[testID][6] = -1;
                counter++;
                break;
            case 'i' :
                 printf("Using insertion_sort\n");
                insertion_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
                visited[testID][7] = -1;
                counter++;
                break;
            case 'h' :
                 printf("Using shell_sort\n");
                shell_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
                visited[testID][8] = -1;
                counter++;
                break;
            case 's' :
                 printf("Using selection_sort\n");
                selection_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
                visited[testID][9] = -1;
                counter++;
                break;
            case 'r' :
                 printf("Using radix_sort\n");
                radix_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
                visited[testID][10] = -1;
                counter++;
                break;
            case 'p' :
                 printf("Using pancake_sort\n");
                pancake_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
                visited[testID][11] = -1;
                counter++;
                break;
            case 'u' :
                 printf("Using heap_sort\n");
                heap_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
                visited[testID][12] = -1;
                counter++;
                break;
            default:
                 printf("No Correct Sort Chosen\n");
                break;
        }
        if(MaxNumber<counter)
            MaxNumber = counter;
    }
    write();

    for(;index< NUMBEROFTEST; index++) {
        printf("ID# %d ", index, dataCPU[index].length);

        for(i = 0 ; i < dataCPU[index].length ; i++){
            printf("%d ", *(dataOut[index].pArrayToSort + i));
        }
        printf("\n");
    }

    return 0;
}

/********* https://github.com/eddyerburgh/c-sorting-algorithms******/
void bubble_sort(int arr[], int n) {
    int temp;
    int i;
    int j;

    i = 0;
    while (i < n) {
        visited[testID][13] = (++counter);
        j = 0;
        while (j < i) {
            visited[testID][14] = (++counter);
            if (arr[j] > arr[i]) {
                visited[testID][15] = (++counter);
                temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
            j++;
        }
        i++;
    }
}

void quick_sort(int arr[], int first_index, int last_index) {
    int pivotIndex, temp, index_a, index_b;

    if (first_index < last_index) {
        pivotIndex = first_index;
        index_a = first_index;
        index_b = last_index;
        while (index_a < index_b) {
            visited[testID][17] = (++counter);
            while (arr[index_a] <= arr[pivotIndex] && index_a < last_index) {
                visited[testID][18] = (++counter);
                index_a++;
            }
            while (arr[index_b] > arr[pivotIndex]) {
                visited[testID][19] = (++counter);
                index_b--;
            }

            if (index_a < index_b) {
                visited[testID][20] = (++counter);
                temp = arr[index_a];
                arr[index_a] = arr[index_b];
                arr[index_b] = temp;
            }
        }
        temp = arr[pivotIndex];
        arr[pivotIndex] = arr[index_b];
        arr[index_b] = temp;
        quick_sort(arr, first_index, index_b - 1);
        quick_sort(arr, index_b + 1, last_index);
        visited[testID][16] = -1;
        counter++;

    }
}

void merge(int* arr, int* left_arr, int left_count, int* right_arr, int right_count) {
    int i, j, k;

    i = 0;
    j = 0;
    k = 0;

    while (i < left_count && j < right_count) {
        visited[testID][21] = (++counter);
        if (left_arr[i] < right_arr[j]){
            visited[testID][22] = (++counter);
            arr[k++] = left_arr[i++];
        }
        else{
            visited[testID][23] = (++counter);
            arr[k++] = right_arr[j++];
        }
    }
    while (i < left_count) {
        visited[testID][24] = (++counter);
        arr[k++] = left_arr[i++];
    }
    while (j < right_count) {
        visited[testID][25] = (++counter);
        arr[k++] = right_arr[j++];
    }
}

void merge_sort(int arr[], int n) {
    int mid, i, *L, *right_arr;
    if (n < 2) {
        visited[testID][26] = (++counter);
        return;
    }
    mid = n / 2;

    L = (int*)malloc(mid * sizeof(int));
    right_arr = (int*)malloc((n - mid) * sizeof(int));

    for (i = 0; i < mid; i++) {
        visited[testID][27] = (++counter);
        L[i] = arr[i];
    }
    for (i = mid; i < n; i++) {
        right_arr[i - mid] = arr[i];
        visited[testID][28] = (++counter);
    }

    merge_sort(L, mid);
    merge_sort(right_arr, n - mid);
    merge(arr, L, mid, right_arr, n - mid);
    free(L);
    free(right_arr);
}

void odd_even_sort(int *arr, int n) {
    bool sorted = false;  // Initially array is unsorted
    int temp;

    while (!sorted) {
        visited[testID][29] = (++counter);
        sorted = true;
        int i;
        // Perform Bubble sort on odd indexed element
        for (i = 1; i <= n - 2; i += 2) {
            visited[testID][30] = (++counter);
            if (arr[i] > arr[i + 1]) {
                visited[testID][31] = (++counter);
                temp = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = temp;
                sorted = false;
            }
        }

        // Perform Bubble sort on even indexed element
        for (i = 0; i <= n - 2; i += 2) {
            visited[testID][32] = (++counter);
            if (arr[i] > arr[i + 1]) {
                visited[testID][33] = (++counter);
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
        visited[testID][34] = (++counter);
        swapped = false;
        int k;
        for (k = i; k < j; k++) {
            visited[testID][35] = (++counter);
            if (arr[k] > arr[k + 1]) {
                visited[testID][36] = (++counter);
                int temp = arr[k];
                arr[k] = arr[k + 1];
                arr[k + 1] = temp;
                swapped = true;
            }
        }
        j--;
        if (swapped) {
            visited[testID][37] = (++counter);
            swapped = false;
            int k;
            for (k = j; k > i; k--) {
                visited[testID][38] = (++counter);
                if (arr[k] < arr[k - 1]) {
                    visited[testID][39] = (++counter);
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
        visited[testID][40] = (++counter);
        gap = (gap / shrink);
        if (gap < 1) {
            visited[testID][41] = (++counter);
            gap = 1;
        }
        swapped = false;
        int i;
        for (i = 0; i < n - gap; i++) {
            visited[testID][42] = (++counter);
            if (arr[i] > arr[i + gap]) {
                visited[testID][43] = (++counter);
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
        visited[testID][44] = (++counter);
        if (i == 0 || arr[i] >= arr[i - 1]) {
            visited[testID][45] = (++counter);
            i++;
        } else {
            visited[testID][46] = (++counter);
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
        visited[testID][47] = (++counter);
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j]) {
            visited[testID][48] = (++counter);
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
        visited[testID][49] = (++counter);
        int i;
        for (i = gap; i < n; ++i) {
            visited[testID][50] = (++counter);
            int temp = arr[i];
            for (j = i; j >= gap && temp < arr[j - gap]; j -= gap) {
                visited[testID][51] = (++counter);
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void selection_sort(int *arr, int n) {
    int i, j;

    for (j = 0; j < n - 1; j++) {
        visited[testID][52] = (++counter);
        int iMin = j;

        for (i = j + 1; i < n; i++) {
            visited[testID][53] = (++counter);
            if (arr[i] < arr[iMin]) {
                visited[testID][54] = (++counter);
                iMin = i;
            }
        }

        if (iMin != j) {
            visited[testID][55] = (++counter);
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
        visited[testID][56] = (++counter);
        if (arr[i] > largest_number){
            visited[testID][57] = (++counter);
            largest_number = arr[i];
        }
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

        visited[testID][58] = (++counter);
        int bucket[10] = {0};

        // Counts the number of "keys" or digits that will go into each bucket
        for (i = 0; i < n; i++) {
            visited[testID][59] = (++counter);
            bucket[(arr[i] / significant_digit) % 10]++;
        }

        /**
         * Add the count of the previous buckets,
         * Acquires the indexes after the end of each bucket location in the arr
         * Works similar to the count sort algorithm
         **/
        for (i = 1; i < 10; i++) {
            visited[testID][60] = (++counter);
            bucket[i] += bucket[i - 1];
        }

        // Use the bucket to fill a "semi_sorted" arr
        for (i = n - 1; i >= 0; i--){
            visited[testID][61] = (++counter);
            semi_sorted[--bucket[(arr[i] / significant_digit) % 10]] = arr[i];
        }


        for (i = 0; i < n; i++) {
            visited[testID][62] = (++counter);
            arr[i] = semi_sorted[i];
        }

        // Move to next significant digit
        significant_digit *= 10;
    }
}

void flip(int *arr, int i) {
    int temp, start = 0;
    while (start < i) {
        visited[testID][63] = (++counter);
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
        if (arr[i] > arr[mi]){
            visited[testID][64] = (++counter);
            mi = i;
        }
    return mi;
}


int pancake_sort(int* arr, int n) {
    int curr_size;
    for (curr_size = n; curr_size > 1; --curr_size) {
        visited[testID][65] = (++counter);
        int mi = find_max(arr, curr_size);
        if (mi != curr_size - 1) {
            flip(arr, mi);

            flip(arr, curr_size - 1);
            visited[testID][66] = -1;
            (++counter);
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
        visited[testID][67] = -1;
        ++counter;
    }
}

void build_heap(int a[], int n) {
    int i, heap_size;
    heap_size = n - 1;
    for (i = (n / 2); i >= 0; i--) {
        satisfy_heap(a, i, heap_size);
        visited[testID][68] = -1;
        ++counter;
    }
}

void satisfy_heap(int a[], int i, int heap_size) {
    int l, r, largest, temp;
    l = 2 * i;
    r = 2 * i + 1;
    if (l <= heap_size && a[l] > a[i]) {
        visited[testID][69] = (++counter);
        largest = l;
    } else {
        visited[testID][70] = (++counter);
        largest = i;
    }
    if (r <= heap_size && a[r] > a[largest]) {
        visited[testID][71] = (++counter);
        largest = r;
    }
    if (largest != i) {
        temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        satisfy_heap(a, largest, heap_size);
        visited[testID][72] = -1;
        ++counter;
    }
}
