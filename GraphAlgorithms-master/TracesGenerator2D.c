#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int NUMBEROFTEST = 1024;
unsigned long long int visited[1024][42];
unsigned long long int MaxNumber=0;
unsigned long long int counter=0;
unsigned long long int NumberOfBranch =42;
int testID =0;

typedef struct{
    int vertexNum;
    int* adjMatrix;
    int isOriented;
    int hasLoop;
    int vertex;
    int action;
}inputData;

typedef struct{
    int* queue;
    int* wasVisited;
    int* fatherOf;
    double* dist;
}outputData;


void printAdjMatrix(inputData g) {

	int n = g.vertexNum;
	printf("%d\n", n);
	//system(CLEAR_SCREEN);
	for(int i=0; i < n; i++) {
		for(int j=0; j < n; j++)
			printf("%d      ", g.adjMatrix[i*n+j]);
		printf("\n\n");
	}
	//getchar();
} 

 void intializeVector(int* f, int value, int n) {

     for(int i=0; i < n; i++){
         visited[testID][9] = (++counter);
		f[i] = value;
     }
}

void printPairs(int* v, int n) {

	printf("  Node |  Father\n\n");
	for(int i=0; i < n; i++)
		printf("  %2d   |    %2d\n", i, v[i]);

	printf("\n* -1 = root\n* -2 = unreachable\n\n");
}

 void breadthFirstSearch(int vertexNum, int* adjMatrix, int vertex, int *wasVisited, int* queue, int* fatherOf) {

     int add = 0;
     int rem = 0;
     int curr; //Current Vertex

     intializeVector(queue, -2, vertexNum);
     intializeVector(fatherOf, -2, vertexNum);

     fatherOf[vertex] = -1;
     queue[add++] = vertex;
     wasVisited[vertex] = 1;

     while(rem < vertexNum) {
         visited[testID][4] =  (++counter);
         //counter = visited[testID][4];
         curr = queue[rem++];
         if(curr < 0){
             visited[testID][5] =  (++counter);
             //counter = visited[testID][5];
             break;
         }

         for(int j=0; j < vertexNum; j++) {
             //printf("visited[6]  %lu ", visited[6]);
             visited[testID][6] =  (++counter);
             //counter = visited[testID][6];

             if(0 < adjMatrix[curr*vertexNum+j] && adjMatrix[curr*vertexNum+j] < INFINITY){
                 visited[testID][7] =  (++counter);
                 //counter = visited[testID][7];

                 if(!wasVisited[j]) {
                     visited[testID][8] =  (++counter);
                     //counter = visited[testID][8];
                     queue[add++] = j;
                     wasVisited[j] = 1;
                     fatherOf[j] = curr;
                 }
             }
         }
     }


	//printPairs(fatherOf, vertexNum);
}

 int allInPartition(int* partition, int n) {
     for(int i=0; i < n; i++){
         visited[testID][19] =  (++counter);
         //counter = visited[testID][19];
         if(partition[i] == 0){
             visited[testID][20] =  (++counter);
             //counter = visited[testID][20];
             return 0;
         }
     }

     return 1;

 }

 int heapIsEmpty(int* heap, int n) {

     for(int i=0; i < n; i++){
         visited[testID][30] =  (++counter);
         //counter = visited[testID][30];
         if(heap[i] == 1){
             visited[testID][31] =  (++counter);
             //counter = visited[testID][31];
             return 0;
         }
     }

     return 1;
}

 int extractMin(int* heap, double* dist, int n) {
     int minIndex = -1;
     double min = INFINITY;

     for(int i=0; i < n; i++){
         visited[testID][27] =  (++counter);
         //counter = visited[testID][27];
         if(heap[i] == 1){
             visited[testID][28] =  (++counter);
             //counter = visited[testID][28];
             if(dist[i] < min) {
                 visited[testID][29] =  (++counter);
                 //counter = visited[testID][29];
                 min = dist[i];
                 minIndex = i;
             }
         }
     }

     return minIndex;
}

void printPath(int dest, int* father) {

	if(father[dest] == -1)
		printf("%2d ", dest);
	else if(father[dest] == -2)
		printf("UNREACHABLE");
	else {
		printPath(father[dest], father);
		printf("  ->  %2d", dest);
	}
}

 void minimumPathDijkstra(int vertexNum, int* adjMatrix, int vertex, int* heap, double *distance, int* fatherOf) {
     //    int heap[g->vertexNum];
     //    int fatherOf[g->vertexNum];
     //    double distance[g->vertexNum];
     int curr;

     intializeVector(heap, 1, vertexNum);
     intializeVector(fatherOf, -2, vertexNum);

     for(int i=0; i < vertexNum; i++){
         visited[testID][21] =  (++counter);
         //counter = visited[testID][21];
         distance[i] = INFINITY;
     }
     fatherOf[vertex] = -1;
     distance[vertex] = 0;

     while(!heapIsEmpty(heap, vertexNum)) {
         visited[testID][22] = -1;
         counter++;
         curr = extractMin(heap, distance, vertexNum);

         if(curr < 0) {
             visited[testID][23] =  (++counter);
             //counter = visited[testID][23];
             break;
         }

         heap[curr] = 0;

         for(int j=0; j < vertexNum; j++){
             visited[testID][24] =  (++counter);
             //counter = visited[testID][24];
             if(j != curr && 0 < adjMatrix[curr*vertexNum+j]){
                 visited[testID][25] =  (++counter);
                 //counter = visited[testID][25];
                 if(distance[curr] + adjMatrix[curr*vertexNum+j] < distance[j]) {
                     visited[testID][26] =  (++counter);
                     //counter = visited[testID][26];
                     distance[j] = distance[curr] + adjMatrix[curr*vertexNum+j];
                     fatherOf[j] = curr;
                 }
             }
         }

     }

     /*    for(int i=0; i < vertexNum; i++) {
      printf("d(%2d, %2d) = ", vertex, i);
      printf(" %d = ", distance[i]);
      printPath(i, fatherOf);
      printf("\n");
      }
      */

 }

 void minimumPathFloydWarshall(int vertexNum, int* adjMatrix, double* dist) {
     //    double dist[g->vertexNum][g->vertexNum];

     for(int i=0; i < vertexNum; i++){
         visited[testID][32] =  (++counter);
         //counter = visited[testID][32];
         for(int j=0; j < vertexNum; j++) {
             visited[testID][33] =  (++counter);
             //counter = visited[testID][33];
             if(i == j){
                 visited[testID][34] =  (++counter);
                 //counter = visited[testID][34];
                 dist[i*vertexNum+j] = 0;
             }
             else{
                 visited[testID][35] =  (++counter);
                 //counter = visited[testID][35];
                 if(adjMatrix[i*vertexNum+j] == 0){
                     visited[testID][36] =  (++counter);
                     //counter = visited[testID][36];
                     dist[i*vertexNum+j] = INFINITY;
                 }
                 else{
                     visited[testID][37] =  (++counter);
                     //counter = visited[testID][37];
                     dist[i*vertexNum+j] = adjMatrix[i*vertexNum+j];
                 }
             }
         }
     }
     for(int k=0; k < vertexNum; k++){
         visited[testID][38] =  (++counter);
         //counter = visited[testID][38];
         for(int i=0; i < vertexNum; i++){
             visited[testID][39] =  (++counter);
             //counter = visited[testID][39];
             for(int j=0; j < vertexNum; j++){
                 visited[testID][40] =  (++counter);
                 //counter = visited[testID][40];
                 if(dist[i*vertexNum+k] + dist[k*vertexNum+j] < dist[i*vertexNum+j]){
                     visited[testID][41] =  (++counter);
                     //counter = visited[testID][41];
                     dist[i*vertexNum+j] = dist[i*vertexNum+k] + dist[k*vertexNum+j];
                 }
             }
         }
     }
}

 void minimumSpanningTree(int vertexNum, int* adjMatrix, int vertex, int* inPartition) {

     //    int* inPartition = calloc(g->vertexNum, sizeof(int));
     int minRow, minCol;
     double min;
     int minSize = 0;

     inPartition[vertex] = 1;

     while(!allInPartition(inPartition, vertexNum)) {
         visited[testID][10] =  (++counter);
         //counter = visited[testID][10];
         min = INFINITY;
         minRow = -1;
         minCol = -1;

         for(int i=0; i < vertexNum; i++){
             visited[testID][11] =  (++counter);
             //counter = visited[testID][11];
             if(inPartition[i]){
                 visited[testID][12] =  (++counter);
                 //counter = visited[testID][12];
                 for(int j=0; j < vertexNum; j++){
                     visited[testID][13] =  (++counter);
                     //counter = visited[testID][13];
                     if(!inPartition[j]){
                         visited[testID][14] =  (++counter);
                         //counter = visited[testID][14];
                         if(0 < adjMatrix[i*vertexNum+j] && adjMatrix[i*vertexNum+j] < min) {
                             visited[testID][15] =  (++counter);
                             //counter = visited[testID][15];
                             min = adjMatrix[i*vertexNum+j];
                             minRow = i;
                             minCol = j;
                         }
                     }
                 }
             }
         }

         if(minCol < 0) {
             visited[testID][16] =  (++counter);
             //counter = visited[testID][16];
             printf("The graph has at least one node that is disconnected\n");
             break;
         }else {
             visited[testID][17] =  (++counter);
             //counter = visited[testID][17];
             inPartition[minCol] = 1;
             printf("e(%2d, %2d) = %d\n", minRow, minCol, adjMatrix[minRow*vertexNum+minCol]);
             minSize += adjMatrix[minRow*vertexNum+minCol];

             if(allInPartition(inPartition, vertexNum)){
                 visited[testID][18] = -1;//=  counterFuncCall;
                 counter++;
                 printf("Minimum Spanning Tree value = %d\n", minSize);
             }
         }
     }
}

//************************************** READING INPUT FROM FILE **************************************** /
void readingInput(inputData *dataCPU, outputData* dataOut){
    int index =0;
    char action;
    int n, isOriented, vertex, i, j;
    int ret = fscanf(stdin, "%c %d %d %d ",&action,&n, &isOriented, &vertex);
    while(ret != EOF){
        dataCPU[index].action = action;
        dataCPU[index].vertexNum = n;
        dataCPU[index].adjMatrix =  (int*)malloc(n*n*sizeof(int));
        dataCPU[index].isOriented = isOriented;
        dataCPU[index].vertex = 0;// vertex;
        dataOut[index].wasVisited = (int*) malloc(n* sizeof(int));
        dataOut[index].queue = (int*) malloc(n* sizeof(int));
        switch(action){
		case 'i':
			dataOut[index].dist = (double*) malloc(n* sizeof(double));
			break;
		case 'f':
			dataOut[index].dist = (double*) malloc(n*n* sizeof(double));
			break;
	}
        dataOut[index].fatherOf = (int*) malloc(n* sizeof(int));
//	printf("%c %d %d %d \n",action,n, isOriented, vertex);
        for(i=0; i < n; i++){
            for(j = 0; j < n; j++) {
                    fscanf(stdin,"%d ", &dataCPU[index].adjMatrix[i*n+j]);
	//	    printf("%d ", dataCPU[index].adjMatrix[i*n+j]);
            }
	//	printf("\n");
	}
        index++;
        ret = fscanf(stdin, "%c %d %d %d ",&action,&n, &isOriented, &vertex);
    }
    NUMBEROFTEST = index;
}

void myKernel(inputData *dataCPU, outputData* dataOut)
{
    int index=0;
    for(;index< NUMBEROFTEST; index++) {
	testID = index;
	counter = 0;
    switch (dataCPU[index].action) {
        case 'b':
            breadthFirstSearch(dataCPU[index].vertexNum,dataCPU[index].adjMatrix , dataCPU[index].vertex, dataOut[index].wasVisited, dataOut[index].queue, dataOut[index].fatherOf);
            visited[testID][0] = -1;
            counter++;
            break;
        case 'm':
            minimumSpanningTree(dataCPU[index].vertexNum,dataCPU[index].adjMatrix , dataCPU[index].vertex, dataOut[index].queue);
            visited[testID][1] = -1;
            counter++;
            break;
        case 'i':
            minimumPathDijkstra(dataCPU[index].vertexNum,dataCPU[index].adjMatrix , dataCPU[index].vertex, dataOut[index].wasVisited, dataOut[index].dist, dataOut[index].fatherOf);//, dataCPU.wasVisited);
            visited[testID][2] = -1;
            counter++;
            break;
       case 'f':
            minimumPathFloydWarshall(dataCPU[index].vertexNum,dataCPU[index].adjMatrix,dataOut[index].dist);
            visited[testID][3] = -1;
            counter++;
            break;
        default:
            break;
   }
   if(counter>MaxNumber)
	MaxNumber = counter;
}
}
//************************************* Writing time in a FILE ******************************************
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
            if(visited[i][j]==-1)
                visited[i][j] = NumberOfBranch * MaxNumber;
            fprintf(fp1, "%lu ", visited[i][j]);
        }
        fputs("\n",fp1);
    }
    fclose(fp1);
}

int main(int argc, char* argv[]) {
    inputData *dataCPU = (inputData*)malloc(sizeof(inputData)* NUMBEROFTEST);
    outputData *dataOut = (outputData*)malloc(sizeof(outputData)* NUMBEROFTEST);
    readingInput(dataCPU,dataOut);

    myKernel(dataCPU,dataOut);
    write();
    int index=0;
    for(;index< NUMBEROFTEST; index++) {
        printf("\nID# %d ", index);
	switch (dataCPU[index].action) {
        case 'b':
		printPairs(dataOut[index].fatherOf,dataCPU[index].vertexNum);
        	printf("\n");
    //    	printAdjMatrix(dataCPU[index]);
      //  	printf("\n");
            	break;
       case 'm':  
	//	printf("MST \n");
		break;
       case 'i':
        	for(int i=0; i < dataCPU[index].vertexNum; i++) {
			printf("d(%2d, %2d) ", dataCPU[index].vertex, i);
                        printf(" %6.2lf = ", dataOut[index].dist[i]);
                        printPath(i, dataOut[index].fatherOf);
                        printf(" ");
                }
		break;
       case 'f':	
		for(int i=0; i < dataCPU[index].vertexNum; i++) {
   	             	printf("d(%2d, %2d) = ", dataCPU[index].vertex, i);
			printf("%6.2lf ", dataOut[index].dist[dataCPU[index].vertex*dataCPU[index].vertexNum+i]);
        	}
		break;
	}
	printf("\n");
    }
    return 0;
}






