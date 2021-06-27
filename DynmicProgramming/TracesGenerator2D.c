//https://github.com/VAR-solutions/Algorithms

#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
int NUMBEROFTEST = 1024;

unsigned long long int visited[1024][71] ;
unsigned long long int NumberOfBranch =71;
unsigned long long int MaxIteration = 1000000;
unsigned long long int MaxNumber = 0;//9223372036854775807;
unsigned long long int counter =0;
int testID =0;
typedef struct{
    int n;
    int k;
    int* c;
    int* m;
    int* t;
    bool *s;
    char* x;
    char* y;
    char action;
}inputData;

typedef struct{
    int result;
}outputData;

void write(){
    FILE *fp1;
    fp1 = fopen("Traces2D.txt", "a");
    if (fp1 == NULL){
        printf("Problem in a file");
        return;
    }
    int i, j;
    for(i=0; i<NUMBEROFTEST; i++){
        for(j=0;j<NumberOfBranch;j++){
            if(visited[i][j] == -1)
                visited[i][j] = MaxNumber * NumberOfBranch;
            fprintf(fp1, "%lu ", visited[i][j]);
        }
        fputs("\n",fp1);
    }
    fclose(fp1);
}

// ****************************** binomialCoeff *********************************

int min(int a, int b)
{
    if (a < b)  {
        visited[testID][67] = (++counter);
        return a;
    }
    else {
        visited[testID][68] = (++counter);
        return b;
    }
}
int binomialCoeff(int n, int k, int* C)
{
    //int C[n + 1][k + 1];
    int i, j;
    for (i = 0; i <= n; i++)
    {
        visited[testID][11] = (++counter);
        for (j = 0; j <= min(i, k); j++)
        {
            visited[testID][12] = (++counter);
            if (j == 0 || j == i){
                visited[testID][13] = (++counter);
                C[i*(k+1)+j] = 1;
            }

            else{
                visited[testID][14] = (++counter);
                C[i*(k+1)+j] = C[(i - 1)*(k+1)+j - 1] + C[(i - 1)*(k+1)+j];
            }
        }
    }

    return C[n*(k+1)+k];
}


// ****************************** END binomialCoeff *********************************

// Matrix Ai has dimension p[i-1] x p[i] for i = 1..n
int MatrixChainOrder(int *p, int n, int* m)
{

    /* For simplicity of the program, one extra row and one
     extra column are allocated in m[][].  0th row and 0th
     column of m[][] are not used */
    // int m[n][n];
    int i, j, k, L, q;

    /* m[i,j] = Minimum number of scalar multiplications needed
     to compute the matrix A[i]A[i+1]...A[j] = A[i..j] where
     dimension of A[i] is p[i-1] x p[i] */

    // cost is zero when multiplying one matrix.
    for (i=1; i<n; i++) {
        visited[testID][15] = (++counter);
        m[i*n+i] = 0;
    }

    // L is chain length.
    for (L=2; L<n; L++)
    {
        visited[testID][16] = (++counter);
        for (i=1; i<n-L+1; i++)
        {
            visited[testID][17] = (++counter);
            j = i+L-1;
            m[i*n+j] = INT_MAX;
            for (k=i; k<=j-1; k++)
            {
                visited[testID][18] = (++counter);
                // q = cost/scalar multiplications
                q = m[i*n+k] + m[(k+1)*n+j] + p[i-1]*p[k]*p[j];
                if (q < m[i*n+j]) {
                    visited[testID][19] = (++counter);
                    m[i*n+j] = q;
                }
            }
        }
    }
    return m[n+n-1];
}
/******************** END MATRIX MULTPICATION *******************************/

/**************** FIB *****************************************************/
int fib(int n, int* f)
{
    /* Declare an array to store Fibonacci numbers. */
    //  int f[n+2];   // 1 extra to handle case, n = 0
    int i;

    /* 0th and 1st number of the series are 0 and 1*/
    f[0] = 0;
    f[1] = 1;

    for (i = 2; i <= n; i++)
    {
        visited[testID][20] = (++counter);
        /* Add the previous 2 numbers in the series
         and store it */
        f[i] = f[i-1] + f[i-2];
    }

    return f[n];
}
/******************** END FIB ************************************/

/************************** KADANE *******************************

 Kadane's algorithm finds the maximum subarray(contigious subsequence) sum.
 let f(i) be the maximum sum of any non-empty subarray ending at i.
 f(i) = {
 max(arr[i], f[i-1] + arr[i])    otherwise
 arr[0]                            when i = 0
 }
 */
//Time Complexity  = O(n)
//Space Complexity = O(n)
//
int max(int a,int b){
    //returns the maximum of two
    if (a>b)
    {
        visited[testID][69] = (++counter);
        return a;
    }
    else {
        visited[testID][70] = (++counter);
        return b;

    }
}
int max_subarray_sum(int* arr, int size,int* f){
    // int f[size];
    int maximum_sum;

    f[0] = arr[0];
    maximum_sum = arr[0];
    for(int i=1; i< size; i++){
        f[i] = max(arr[i], f[i-1]+ arr[i]);
        //keep track of maximum sum ending at ith position found so far.
        maximum_sum = max(f[i],maximum_sum);
        visited[testID][21] = -1;

        ++counter;
    }
    return maximum_sum;
}
/************************** END KADANE *******************************/

/*************************** KNAPSACK ********************************/
int knapSack(int W,int* wt,int* v,int n,int* T){

    //int T[n + 1][W + 1];

    for (int i = 0; i <= n; i++)
    {
        visited[testID][22] = (++counter);
        for (int j = 0; j <= W; j++)
        {
            visited[testID][23] = (++counter);
            if (i == 0 || j == 0){
                visited[testID][24] = (++counter);
                T[i*(W+1)+j] = 0;
            }
            else {
                visited[testID][25] = (++counter);
                if (wt[i - 1] <= j){
                    visited[testID][26] = (++counter);
                    T[i*(W+1)+j] = max(v[i - 1] + T[(i - 1)*(W+1)+j - wt[i - 1]], T[(i - 1)*(W+1)+j]);
                }
                else{
                    visited[testID][27] = (++counter);
                    T[i*W+j] = T[(i - 1)*(W+1)+j];
                }
            }
        }

    }

    return T[n*(W+1)+W];
}
/************************** END KNAPSACK ********************************/

/********************* SUBSETSUM ********************************/
bool isSubsetSum(int *set, int n, int sum,bool* subset){
    //  bool subset[n+1][sum+1];
    for (int i = 0; i <= n; i++){
        visited[testID][28] = (++counter);
        subset[i*(sum+1)+0] = true;
    }
    for (int i = 1; i <= sum; i++){
        visited[testID][29] = (++counter);
        subset[0*(sum+1)+i] = false;
    }
    for (int i = 1; i <= n; i++){
        visited[testID][30] = (++counter);
        for (int j = 1; j <= sum; j++){
            visited[testID][31] = (++counter);
            if(j<set[i-1]){
                visited[testID][32] = (++counter);
                subset[i*(sum+1)+j] = subset[(i-1)*(sum+1)+j];
            }
            if (j >= set[i-1]){
                visited[testID][33] = (++counter);
                subset[i*(sum+1)+j] = subset[(i-1)*(sum+1)+j] || subset[(i - 1)*(sum+1)+j-set[i-1]];
            }
        }
    }
    return subset[n*(sum+1)+sum];
}
/********************* END SUBSETSUM ********************************/
/************* FROM GITHUB SIMILAR TO  https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/ ******/
int lcs(char* X, char* Y, int m, int n, int* L){
    // int L[m+1][n+1];
    int i, j;

    /* Following steps build L[m+1][n+1] in bottom up fashion. Note
     that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
    for (i=0; i<=m; i++)
    {
        visited[testID][34] = (++counter);
        for (j=0; j<=n; j++)
        {
            visited[testID][35] = (++counter);
            if (i == 0 || j == 0) {
                visited[testID][36] = (++counter);
                L[i*(n+1)+j] = 0;
            }

            else
            {
                visited[testID][37] = (++counter);
                if (X[i-1] == Y[j-1]) {
                    visited[testID][38] = (++counter);
                    L[i*(n+1)+j] = L[(i-1)*(n+1)+j-1] + 1;
                }

                else{
                    visited[testID][39] = (++counter);
                    L[i*(n+1)+j] = max(L[(i-1)*(n+1)+j], L[i*(n+1)+j-1]);
                }
            }
        }
    }

    /* L[m][n] contains length of LCS for X[0..n-1] and Y[0..m-1] */
    return L[m*(n+1)+n];
}
/******************************** END longest-common-subsequence ************/
/*************** https://www.geeksforgeeks.org/edit-distance-dp-5/ **********/
// Utility function to find the minimum of three numbers
int Min(int x, int y, int z)
{
    return min(min(x, y), z);
}
int editDistDP(char* str1, char* str2, int m, int n, int* dp)
{
    // Create a table to store results of subproblems
    //  int dp[m+1][n+1];

    // Fill d[][] in bottom up manner
    for (int i=0; i<=m; i++)
    {
        visited[testID][40] = (++counter);
        for (int j=0; j<=n; j++)
        {
            visited[testID][41] = (++counter);
            // If first string is empty, only option is to
            // insert all characters of second string
            if (i==0) {
                visited[testID][42] = (++counter);
                dp[i*(n+1)+j] = j;  // Min. operations = j
            }

            // If second string is empty, only option is to
            // remove all characters of second string
            else {
                if (j==0){
                    visited[testID][43] = (++counter);
                    dp[i*(n+1)+j] = i; // Min. operations = i
                }

                // If last characters are same, ignore last char
                // and recur for remaining string
                else {
                    visited[testID][44] = (++counter);
                    if (str1[i-1] == str2[j-1]){
                        visited[testID][45] = (++counter);
                        dp[i*(n+1)+j] = dp[(i-1)*(n+1)+j-1];
                    }

                    // If the last character is different, consider all
                    // possibilities and find the minimum
                    else{

                        dp[i*(n+1)+j] = 1 + Min(dp[i*(n+1)+j-1],  // Insert
                                                dp[(i-1)*(n+1)+j],  // Remove
                                                dp[(i-1)*(n+1)+j-1]); // Replace
                        visited[testID][46] = -1;

                        ++counter;
                    }
                }
            }
        }
    }

    return dp[m*(n+1)+n];
}
/***************************** END EDIT DISTANCE ***************/

/****** EGG DROPIING PUZZEL ************************/
int eggDrop(int n, int k, int* eggFloor)
{
    // int eggFloor[n+1][k+1];
    int res;
    int i, j, x;

    for (i = 1; i <= n; i++)
    {
        visited[testID][47] = (++counter);
        eggFloor[i*(k+1)+1] = 1;
        eggFloor[i*(k+1)+0] = 0;
    }

    for (j = 1; j <= k; j++) {
        visited[testID][48] = (++counter);
        eggFloor[1*(k+1)+j] = j;
    }

    for (i = 2; i <= n; i++)
    {
        visited[testID][49] = (++counter);
        for (j = 2; j <= k; j++)
        {
            visited[testID][50] = (++counter);
            eggFloor[i*(k+1)+j] = INT_MAX;
            for (x = 1; x <= j; x++)
            {
                res = 1 + max(eggFloor[(i-1)*(k+1)+x-1], eggFloor[i*(k+1)+j-x]);
                visited[testID][51] = -1 ;

                ++counter;
                if (res < eggFloor[i*(k+1)+j]) {
                    visited[testID][52] = (++counter);
                    eggFloor[i*(k+1)+j] = res;
                }
            }
        }
    }

    return eggFloor[n*(k+1)+k];
}

/********************** END EGG FROPPING PUZZEL ***************************/

/************************** STRATGEY GAME *********************************/
// Returns optimal value possible that a player can collect from
// an array of coins of size n. Note than n must be even
int optimalStrategyOfGame(int* arr, int n, int* table)
{
    // Create a table to store solutions of subproblems
    //  int table[n][n];
    int gap, i, j, x, y, z;
    // Fill table using above recursive formula. Note that the table
    // is filled in diagonal fashion (similar to http:// goo.gl/PQqoS),
    // from diagonal elements to table[0][n-1] which is the result.
    for (gap = 0; gap < n; ++gap) {
        visited[testID][53] = (++counter);
        for (i = 0, j = gap; j < n; ++i, ++j) {
            visited[testID][54] = (++counter);
            // Here x is value of F(i+2, j), y is F(i+1, j-1) and
            // z is F(i, j-2) in above recursive formula
            if ((i + 2) <= j) {
                visited[testID][55] = (++counter);
                x = table[(i + 2)*n+j];
            }
            else {
                visited[testID][56] = (++counter);
                x = 0;
            }
            if((i + 1) <= (j - 1)){
                visited[testID][57] = (++counter);
                y = table[(i + 1)* n + j - 1];

            }
            else {
                visited[testID][58] = (++counter);
                y = 0;

            }
            if(i <= (j - 2)){

                visited[testID][59] = (++counter);
                z = table[i*n + j - 2];

            }
            else {
                visited[testID][60] = (++counter);
                z=0;

            }
            table[i*n+j] = max(arr[i] + min(x, y), arr[j] + min(y, z));
        }
    }
    return table[n - 1];
}
/******************** END STRATGEY GAME *********************************/

/************** Longest Increasing Subsequence ********
 * The program finds the length of the Longest subsequence (may not be
 * continuous) such that the subsequence is in increasing order
 ***************/
int findMax(int *arr, int length) {
    int max = 0;
    for (int i = 0; i < length; i++) {
        visited[testID][61] = (++counter);
        if (max < arr[i]) {
            visited[testID][62] = (++counter);
            max = arr[i];
        }
    }
    return max;
}

int findLongestIncSubLength(int *arr,int length, int* dp) {
    //int dp[length];
    int i, j, max = 0;

    // Initialize Longest Increasing Subsequence values
    for (i = 0; i < length; i++) {
        visited[testID][63] = (++counter);
        dp[i] = 1;
    }

    for (i = 1; i < length; i++) {
        visited[testID][64] = (++counter);
        for (j = 0; j < i; j++) {
            visited[testID][65] = (++counter);
            if (arr[i] > arr[j] && dp[i] < dp[j] + 1) {
                visited[testID][66] = (++counter);
                dp[i] = dp[j] + 1;
            }
        }
    }
    max = findMax(dp, length);
    return max;
}
/***************************** END Longest Increasing Subsequence ******************************************/

void readingInput(inputData *dataCPU, outputData* dataOut){
    int index =0;
    char action;
    int n, k, i;
    int ret = fscanf(stdin, "%c ",&action);
    while(ret != EOF){
        switch(action){
            case 'c':
                ret = fscanf(stdin, "%d %d ",&n, &k);
                dataCPU[index].action = action;
                dataCPU[index].n = n;
                dataCPU[index].k = k;
                dataCPU[index].c = (int*)malloc(sizeof(int)*(n+1)*(k+1));
                break;
            case 'm':
                ret = fscanf(stdin, "%d ",&n);
                dataCPU[index].action = action;
                dataCPU[index].n = n;
                dataCPU[index].c = (int*)malloc(sizeof(int)*n);
                for(i=0;i<n;i++)
                    ret = fscanf(stdin, "%d ",&dataCPU[index].c[i]);
                dataCPU[index].m = (int*)malloc(sizeof(int)*n * n);
                break;
            case 'f':
                ret = fscanf(stdin, "%d ",&n);
                dataCPU[index].action = action;
                dataCPU[index].n = n;
                dataCPU[index].c = (int*)malloc(sizeof(int)*(n+2));
                break;
            case 'k':
                ret = fscanf(stdin, "%d ",&n);
                dataCPU[index].action = action;
                dataCPU[index].n = n;
                dataCPU[index].c = (int*)malloc(sizeof(int)*n);
                for(i=0;i<n;i++)
                    ret = fscanf(stdin, "%d ",&dataCPU[index].c[i]);
                dataCPU[index].m = (int*)malloc(sizeof(int)*n);
                break;
            case 'n':
                ret = fscanf(stdin, "%d %d ",&n, &k);
                dataCPU[index].action = action;
                dataCPU[index].n = n;
                dataCPU[index].k=k;
                dataCPU[index].c = (int*)malloc(sizeof(int)*n);
                for(i=0;i<n;i++)
                    ret = fscanf(stdin, "%d ",&dataCPU[index].c[i]);
                dataCPU[index].m = (int*)malloc(sizeof(int)*n);
                for(i=0;i<n;i++)
                    ret = fscanf(stdin, "%d ",&dataCPU[index].m[i]);
                dataCPU[index].t = (int*)malloc(sizeof(int)*(n+1)*(k+1));
                break;
            case 's':
                ret = fscanf(stdin, "%d %d ",&n, &k);
                dataCPU[index].action = action;
                dataCPU[index].n = n;
                dataCPU[index].k=k;
                dataCPU[index].c = (int*)malloc(sizeof(int)*n);
                for(i=0;i<n;i++)
                    ret = fscanf(stdin, "%d ",&dataCPU[index].c[i]);
                dataCPU[index].s = (bool*)malloc(sizeof(bool)*(n+1)*(k+1));
                break;
            case 'l':
                ret = fscanf(stdin, "%d %d ",&n, &k);
                dataCPU[index].action = action;
                dataCPU[index].n = n;
                dataCPU[index].k=k;
                dataCPU[index].x = (char*)malloc(sizeof(char)*n);
                for(i=0;i<n;i++){
                    ret = fscanf(stdin, "%c ",&dataCPU[index].x[i]);//dataCPU[index].x[i]);
                }
                dataCPU[index].y = (char*)malloc(sizeof(char)*k);
                for(i=0;i<k;i++)
                    ret = fscanf(stdin, "%c ",&dataCPU[index].y[i]);
                dataCPU[index].m = (int*)malloc(sizeof(int)*(n+1)*(k+1));

                break;
            case 'e':
                ret = fscanf(stdin, "%d %d ",&n, &k);
                dataCPU[index].action = action;
                dataCPU[index].n = n;
                dataCPU[index].k=k;
                dataCPU[index].x = (char*)malloc(sizeof(char)*n);
                for(i=0;i<n;i++)
                    ret = fscanf(stdin, "%c ",&dataCPU[index].x[i]);
                dataCPU[index].y = (char*)malloc(sizeof(char)*k);
                for(i=0;i<k;i++)
                    ret = fscanf(stdin, "%c ",&dataCPU[index].y[i]);
                dataCPU[index].m = (int*)malloc(sizeof(int)*(n+1)*(k+1));
                break;
            case 'g':
                ret = fscanf(stdin, "%d %d ",&n, &k);
                dataCPU[index].action = action;
                dataCPU[index].n = n;
                dataCPU[index].k=k;
                dataCPU[index].c = (int*)malloc(sizeof(int)*(n+1)*(k+1));
                break;
            case 'o':
                ret = fscanf(stdin, "%d ",&n);
                dataCPU[index].action = action;
                dataCPU[index].n = n;
                dataCPU[index].c = (int*)malloc(sizeof(int)*n);
                for(i=0;i<n;i++)
                    ret = fscanf(stdin, "%d ",&dataCPU[index].c[i]);
                dataCPU[index].m = (int*)malloc(sizeof(int)*n*n);
                break;
            case 'i':
                ret = fscanf(stdin, "%d ",&n);
                dataCPU[index].action = action;
                dataCPU[index].n = n;
                dataCPU[index].c = (int*)malloc(sizeof(int)*n);
                for(i=0;i<n;i++)
                    ret = fscanf(stdin, "%d ",&dataCPU[index].c[i]);
                dataCPU[index].m = (int*)malloc(sizeof(int)*n);
                break;
            default:
                printf("DEFAULT ID %d\n", index);
                break;
        }
        index++;
        ret = fscanf(stdin, "\n%c ",&action);
    }
    NUMBEROFTEST = index;
}

void myKernel(inputData *dataCPU, outputData* dataOut)
{
    int index = 0;// blockIdx.x * blockDim.x + threadIdx.x;
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for(;index<NUMBEROFTEST; index++){
        testID = index;
        counter =0;
        switch (dataCPU[index].action) {
            case 'c':
                dataOut[index].result=binomialCoeff(dataCPU[index].n,dataCPU[index].k, dataCPU[index].c);
                visited[testID][0]= -1;
                ++counter;
                break;
            case 'm':
                dataOut[index].result= MatrixChainOrder(dataCPU[index].c,dataCPU[index].n,dataCPU[index].m);
                visited[testID][1] = -1;
                ++counter;
                break;
            case 'f':
                dataOut[index].result=fib(dataCPU[index].n,dataCPU[index].c);
                visited[testID][2] = -1;

                ++counter;
                break;
            case 'k':
                dataOut[index].result=max_subarray_sum(dataCPU[index].c,dataCPU[index].n,dataCPU[index].m);
                visited[testID][3] = -1 ;

                ++counter;
                break;
            case 'n':
                dataOut[index].result=knapSack(dataCPU[index].k,dataCPU[index].m,dataCPU[index].c,dataCPU[index].n,dataCPU[index].t);
                visited[testID][4] = -1;
                ++counter;
                break;
            case 's':
                dataOut[index].result=isSubsetSum(dataCPU[index].c, dataCPU[index].n, dataCPU[index].k,dataCPU[index].s);
                visited[testID][5] = -1;
                ++counter;
                break;
            case 'l':
                dataOut[index].result = lcs( dataCPU[index].x, dataCPU[index].y, dataCPU[index].n, dataCPU[index].k,dataCPU[index].m);
                visited[testID][6] = -1;
                ++counter;
                break;
            case 'e':
                dataOut[index].result = editDistDP( dataCPU[index].x, dataCPU[index].y, dataCPU[index].n, dataCPU[index].k,dataCPU[index].m);
                visited[testID][7] = -1;
                ++counter;
                break;
            case 'g':
                dataOut[index].result = eggDrop(dataCPU[index].n,dataCPU[index].k, dataCPU[index].c);
                visited[testID][8] = -1;
                ++counter;
                break;
            case 'o':
                dataOut[index].result = optimalStrategyOfGame(dataCPU[index].c, dataCPU[index].n, dataCPU[index].m);
                visited[testID][9] = -1;
                ++counter;
                break;
            case 'i':
                dataOut[index].result = findLongestIncSubLength(dataCPU[index].c, dataCPU[index].n, dataCPU[index].m);
                visited[testID][10] = -1;
                ++counter;
                break;
            default:
                break;
        }
        if(MaxNumber<counter)
            MaxNumber = counter;
    }

}
int main(int argc, char* argv[]) {
    inputData *dataCPU = (inputData*)malloc(sizeof(inputData)* NUMBEROFTEST);
    outputData *dataOut = (outputData*)malloc(sizeof(outputData)* NUMBEROFTEST);
    readingInput(dataCPU,dataOut);
    for(int i=0; i<NUMBEROFTEST; i++)
        for(int j=0; j<NumberOfBranch; j++)
            visited[i][j]=0;
    myKernel(dataCPU,dataOut);
    write();
    int index=0;
    for(;index< NUMBEROFTEST; index++) {
        printf("ID# %d ", index);
        switch (dataCPU[index].action) {
            case 'c':
                printf("Value of C(%d, %d) is %d ", dataCPU[index].n, dataCPU[index].k, dataOut[index].result);
                break;
            case 'm':
                printf("Minimum number of multiplications is %d ",dataOut[index].result);
                break;
            case 'f':
                printf("fibonacci %d",dataOut[index].result);
                break;
            case 'k':
                printf("Kane %d",dataOut[index].result);
                break;
            case 'n':
                printf("Max value %d",dataOut[index].result);
                break;
            case 's':
                if (dataOut[index].result == 1)
                    printf("Found a subset with sum");
                else
                    printf("No subset found with given sum");
                break;
            case 'l':
                printf("Length of LCS is %d",dataOut[index].result);
                break;
            case 'e':
                printf("Edit Distance is %d",dataOut[index].result);
                break;
            case 'g':
                printf ("Minimum number of trials in worst case is %d",dataOut[index].result);
                break;
            case 'o':
                printf("Optimal Game Stratgey %d",dataOut[index].result);
                break;
            case 'i':
                printf("Longest Increasing Subsequence Length is %d",dataOut[index].result);
                break;
            default:
                break;
        }
        printf("\n");
    }
    return 0;
}
