#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int NUMBEROFTEST = 1024;

typedef struct{
    int length;
    char typeOfSort;
}inputData;

typedef struct{
    int *pArrayToSort;
}outputData;

__device__ void bubble_sort(int *pArray, int howMany);
__device__ void quick_sort(int * pArray, int start, int end);
__device__ void merge_sort(int* pArray, int length);
__device__ void merge(int * pArray, int * pTempArray, int leftStart, int* mid, int rightEnd);
__device__ void swap(int *x, int *y);
__device__ void gnome_sort(int *arr, int n);
__device__ void comb_sort(int *arr, int n);
__device__ void cocktail_sort(int *arr, int n);
__device__ void insertion_sort(int *arr, int n);
__device__ void odd_even_sort(int *arr, int n);
__device__ void shell_sort(int *arr, int n);
__device__ void selection_sort(int *arr, int n);
__device__ void radix_sort(int* arr, int n);
__device__ int find_largest_number(int arr[], int n);
__device__ int pancake_sort(int* arr, int n);
__device__ void flip(int *arr, int i) ;
__device__ int find_max(int *arr, int n);
__device__ void heap_sort(int *a, int n);
__device__ void build_heap(int *a, int n);
__device__ void satisfy_heap(int *a, int i, int heap_size);

//************************************** READING INPUT FROM FILE **************************************** /
void readingInput(inputData *dataCPU, outputData* dataOut){
    int index =0;
    int length;
    char type;
    int ret = fscanf(stdin, "%d %c",&length,&type);
    while(ret != EOF){
        dataCPU[index].length = length;
        dataCPU[index].typeOfSort = type;
        dataOut[index].pArrayToSort = (int*)malloc(length * sizeof(int));
        int i;
        for(i=0; i<length; i++)
            fscanf(stdin, "%d",  &dataOut[index].pArrayToSort[i]);
        index++;
        ret = fscanf(stdin, "%d %c",&length,&type);
    }
    NUMBEROFTEST = index;
}

__global__ void myKernel(inputData *dataCPU, outputData* dataOut)
{
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    switch(dataCPU[index].typeOfSort){
        case 'b' :
            printf("Using bubblesort\n");
            bubble_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
            break;
        case 'q' :
            printf("Using quicksort\n");
            quick_sort(dataOut[index].pArrayToSort, 0, dataCPU[index].length - 1);
            break;
        case 'm' :
            printf("Using mergesort\n");
            merge_sort(dataOut[index].pArrayToSort, dataCPU[index].length);
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
//************************************* Writing time in a FILE ******************************************
void writeFile(double time, char* fileName){
    FILE *fp1;
    fp1 = fopen("NUMCudaResults.txt", "a");
    if (fp1 == NULL){
        printf("Problem in a file");
        return;
    }
    fprintf(fp1, "%s ", fileName);
    fprintf(fp1, "%f seconds\n", time);
    fclose(fp1);
}
void launch(inputData *dataCPU, outputData* dataOut, char* fileName){

    int threadsPerBlock = 32;
    int blocksPerGrid = (NUMBEROFTEST) / threadsPerBlock;
    int output_size = (NUMBEROFTEST) * sizeof(outputData);
    int input_size = (NUMBEROFTEST) * sizeof(inputData);
    inputData *dataGPUIn, *in_data = (inputData*)malloc(sizeof(inputData)* NUMBEROFTEST);
    outputData *dataGPUOut, *out_data = (outputData*)malloc(sizeof(outputData)* NUMBEROFTEST);
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    int i =0;
    cudaEventRecord(start);
    for(; i<NUMBEROFTEST;i++){
        int* d_array;
        cudaMalloc((void**)&d_array, dataCPU[i].length*sizeof(int));
        cudaMemcpy(d_array,dataOut[i].pArrayToSort, dataCPU[i].length*sizeof(int),cudaMemcpyHostToDevice);
        in_data[i].length = dataCPU[i].length;
        in_data[i].typeOfSort = dataCPU[i].typeOfSort;
        out_data[i].pArrayToSort = d_array;
    }
    cudaMalloc ( (void**) &dataGPUIn, input_size);
    cudaMemcpy(dataGPUIn, in_data, input_size, cudaMemcpyHostToDevice );
    cudaMalloc ( (void**) &dataGPUOut, output_size);
    cudaMemcpy(dataGPUOut, out_data, output_size, cudaMemcpyHostToDevice );
    myKernel << <blocksPerGrid, threadsPerBlock >> >(dataGPUIn, dataGPUOut); // excute on kernel
    cudaMemcpy(out_data, dataGPUOut, output_size, cudaMemcpyDeviceToHost);
    i=0;
    for(; i<NUMBEROFTEST;i++){
        cudaMemcpy(dataOut[i].pArrayToSort, out_data[i].pArrayToSort, dataCPU[i].length*sizeof(int), cudaMemcpyDeviceToHost);
    }
    cudaFree(dataGPUIn);
    cudaFree(dataGPUOut);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);
    writeFile((milliseconds/1000),fileName);
}
int main (int args, char* argv[])
{
    inputData *dataCPU = (inputData*)malloc(sizeof(inputData)* NUMBEROFTEST);
    outputData *dataOut = (outputData*)malloc(sizeof(outputData)* NUMBEROFTEST);
    readingInput(dataCPU,dataOut);
    launch(dataCPU,dataOut,argv[1]);
    int index=0,i;
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

__device__ void quick_sort(int arr[], int first_index, int last_index) {
  // declaring index variables
  int pivotIndex, temp, index_a, index_b;

  if (first_index < last_index) {
    // assigning first element index as pivot element
    pivotIndex = first_index;
    index_a = first_index;
    index_b = last_index;

    // Sorting in Ascending order with quick sort
    while (index_a < index_b) {
      while (arr[index_a] <= arr[pivotIndex] && index_a < last_index) {
        index_a++;
      }
      while (arr[index_b] > arr[pivotIndex]) {
        index_b--;
      }

      if (index_a < index_b) {
        // Swapping operation
        temp = arr[index_a];
        arr[index_a] = arr[index_b];
        arr[index_b] = temp;
      }
    }

    // At the end of first iteration, swap pivot element with index_b element
    temp = arr[pivotIndex];
    arr[pivotIndex] = arr[index_b];
    arr[index_b] = temp;

    // Recursive call for quick sort, with partitioning
    quick_sort(arr, first_index, index_b - 1);
    quick_sort(arr, index_b + 1, last_index);
  }
}

__device__ void merge(
    int* arr, int* left_arr, int left_count, int* right_arr, int right_count) {
  int i, j, k;

  i = 0;
  j = 0;
  k = 0;

  while (i < left_count && j < right_count) {
    if (left_arr[i] < right_arr[j])
      arr[k++] = left_arr[i++];
    else
      arr[k++] = right_arr[j++];
  }
  while (i < left_count) arr[k++] = left_arr[i++];
  while (j < right_count) arr[k++] = right_arr[j++];
}

__device__ void merge_sort(int arr[], int n) {
  int mid, i, *L, *right_arr;
  if (n < 2) return;
  mid = n / 2;

  L = (int*)malloc(mid * sizeof(int));
  right_arr = (int*)malloc((n - mid) * sizeof(int));

  for (i = 0; i < mid; i++) L[i] = arr[i];
  for (i = mid; i < n; i++) right_arr[i - mid] = arr[i];

  merge_sort(L, mid);
  merge_sort(right_arr, n - mid);
  merge(arr, L, mid, right_arr, n - mid);
  free(L);
  free(right_arr);
}
__device__ void bubble_sort(int arr[], int n) {
  int temp;
  int i;
  int j;
  
  i = 0;
  while (i < n) {
    j = 0;
    while (j < i) {
      if (arr[j] > arr[i]) {
        temp = arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
      }
      j++;
    }
    i++;
  }
}
__device__ void odd_even_sort(int *arr, int n) {
  bool sorted = false;  // Initially array is unsorted
  int temp;

  while (!sorted) {
    sorted = true;

    // Perform Bubble sort on odd indexed element
    for (int i = 1; i <= n - 2; i += 2) {
      if (arr[i] > arr[i + 1]) {
        temp = arr[i + 1];
        arr[i + 1] = arr[i];
        arr[i] = temp;
        sorted = false;
      }
    }

    // Perform Bubble sort on even indexed element
    for (int i = 0; i <= n - 2; i += 2) {
      if (arr[i] > arr[i + 1]) {
        temp = arr[i + 1];
        arr[i + 1] = arr[i];
        arr[i] = temp;
        sorted = false;
      }
    }
  }
}
__device__ void cocktail_sort(int *arr, int n) {
    bool swapped = true;
    int i = 0;
    int j = n - 1;

    while (i < j && swapped) {
        swapped = false;
        for (int k = i; k < j; k++) {
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
            for (int k = j; k > i; k--) {
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

__device__ void comb_sort(int *arr, int n) {
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
        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
            temp = arr[i + gap];
            arr[i + gap] = arr[i];
            arr[i] = temp;
            swapped = true;
            }
        }
    }
}

__device__ void gnome_sort(int *arr, int n) {
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
__device__ void insertion_sort(int *arr, int n) {
  for (int i = 0; i < n; i++) {
    int j = i;
    while (j > 0 && arr[j - 1] > arr[j]) {
      int temp = arr[j];
      arr[j] = arr[j - 1];
      arr[j - 1] = temp;
      j--;
    }
  }
}

__device__ void shell_sort(int *arr, int n) {
  int j;

  for (int gap = n / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < n; ++i) {
      int temp = arr[i];
      for (j = i; j >= gap && temp < arr[j - gap]; j -= gap) {
        arr[j] = arr[j - gap];
      }
      arr[j] = temp;
    }
  }
}

__device__ void selection_sort(int *arr, int n) {
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

__device__ int find_largest_number(int *arr, int n) {

  int i;
  int largest_number = -1;

  for (i = 0; i < n; i++) {
    if (arr[i] > largest_number) largest_number = arr[i];
  }

  return largest_number;
}

__device__ void radix_sort(int* arr, int n) {

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

__device__ void flip(int *arr, int i) {
  int temp, start = 0;
  while (start < i) {
    temp = arr[start];
    arr[start] = arr[i];
    arr[i] = temp;
    start++;
    i--;
  }
}

__device__ int find_max(int *arr, int n) {
  int mi, i;
  for (mi = 0, i = 0; i < n; ++i)
    if (arr[i] > arr[mi]) mi = i;
  return mi;
}


__device__ int pancake_sort(int* arr, int n) {
  for (int curr_size = n; curr_size > 1; --curr_size) {
    int mi = find_max(arr, curr_size);
    if (mi != curr_size - 1) {
      flip(arr, mi);

      flip(arr, curr_size - 1);
    }
  }
}
__device__ void heap_sort(int a[], int n) {
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

__device__ void build_heap(int a[], int n) {
  int i, heap_size;
  heap_size = n - 1;
  for (i = (n / 2); i >= 0; i--) {
    satisfy_heap(a, i, heap_size);
  }
}

__device__ void satisfy_heap(int a[], int i, int heap_size) {
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
