#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int NUMBEROFTEST = 1024;


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

	for(int i=0; i < n; i++)
		f[i] = value;
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
       // printf("rem %d\n", rem);
	while(rem < vertexNum) {
		curr = queue[rem++];
	//	printf("queue[add-1] %d\n ", queue[add-1]);
          //      printf("rem %d \n", rem);
            //    printf("curr %d \n", curr);
	   	if(curr < 0){
	//		printf("break");
			break;
}
		for(int j=0; j < vertexNum; j++) {
//			printf("j %d \n", j);
//			printf("adjMatrix[curr*vertexNum+j] %21f ", adjMatrix[curr*vertexNum+j]);
			if(0 < adjMatrix[curr*vertexNum+j] && adjMatrix[curr*vertexNum+j] < INFINITY)
			{//	printf("if condition");
				if(!wasVisited[j]) {
					queue[add++] = j;
					wasVisited[j] = 1;
			//		printf("queue[add-1] %d \n", queue[add-1]);
					fatherOf[j] = curr;
				}}
		}
	}

	//printPairs(fatherOf, vertexNum);
}

 int allInPartition(int* partition, int n) {

	for(int i=0; i < n; i++)
		if(partition[i] == 0)
			return 0;

	return 1;
}

 int heapIsEmpty(int* heap, int n) {

	for(int i=0; i < n; i++)
		if(heap[i] == 1)
			return 0;

	return 1;
}

 int extractMin(int* heap, double* dist, int n) {

	int minIndex = -1;
	double min = INFINITY;

	for(int i=0; i < n; i++)
		if(heap[i] == 1)
			if(dist[i] < min) {
				min = dist[i];
				minIndex = i;			
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
       //printf("minimumPathDijkstra");
//	int heap[g->vertexNum];
//	int fatherOf[g->vertexNum];
//	double distance[g->vertexNum];
	int curr;

	intializeVector(heap, 1, vertexNum);
	intializeVector(fatherOf, -2, vertexNum);

	for(int i=0; i < vertexNum; i++)
		distance[i] = INFINITY;

	fatherOf[vertex] = -1;
	distance[vertex] = 0;

	while(!heapIsEmpty(heap, vertexNum)) {
		curr = extractMin(heap, distance, vertexNum);

		if(curr < 0) break;

		heap[curr] = 0;

		for(int j=0; j < vertexNum; j++){
			if(j != curr && 0 < adjMatrix[curr*vertexNum+j])
				if(distance[curr] + adjMatrix[curr*vertexNum+j] < distance[j]) {
					distance[j] = distance[curr] + adjMatrix[curr*vertexNum+j];
					fatherOf[j] = curr;
			}
			// printf("fatherOf[j] distance[j] %d %lf\n", fatherOf[j],distance[j]);
		}
	
	}
	
	/*	for(int i=0; i < vertexNum; i++) {
			printf("d(%2d, %2d) = ", vertex, i);
			printf(" %d = ", distance[i]);
			printPath(i, fatherOf);
			printf("\n");
		}
*/}

 void minimumPathFloydWarshall(int vertexNum, int* adjMatrix, double* dist) {
//	double dist[g->vertexNum][g->vertexNum];

	for(int i=0; i < vertexNum; i++)
		for(int j=0; j < vertexNum; j++) {
			if(i == j)
				dist[i*vertexNum+j] = 0;
			else if(adjMatrix[i*vertexNum+j] == 0)
				dist[i*vertexNum+j] = INFINITY;
			else
				dist[i*vertexNum+j] = adjMatrix[i*vertexNum+j];
		}

	for(int k=0; k < vertexNum; k++)
		for(int i=0; i < vertexNum; i++)
			for(int j=0; j < vertexNum; j++)
				if(dist[i*vertexNum+k] + dist[k*vertexNum+j] < dist[i*vertexNum+j])
					dist[i*vertexNum+j] = dist[i*vertexNum+k] + dist[k*vertexNum+j];
}

 void minimumSpanningTree(int vertexNum, int* adjMatrix, int vertex, int* inPartition) {

//	int* inPartition = calloc(g->vertexNum, sizeof(int));
	int minRow, minCol;
	double min;
	int minSize = 0;
	
	inPartition[vertex] = 1;

	while(!allInPartition(inPartition, vertexNum)) {
		min = INFINITY;
		minRow = -1;
		minCol = -1;
		
		for(int i=0; i < vertexNum; i++)
			if(inPartition[i])
				for(int j=0; j < vertexNum; j++)
					if(!inPartition[j])
						if(0 < adjMatrix[i*vertexNum+j] && adjMatrix[i*vertexNum+j] < min) {
							min = adjMatrix[i*vertexNum+j];
							minRow = i;
							minCol = j;
						}		

		if(minCol < 0) {
			printf("The graph has at least one node that is disconnected\n");
			break;
		}else {
			inPartition[minCol] = 1;
			printf("e(%2d, %2d) = %d\n", minRow, minCol, adjMatrix[minRow*vertexNum+minCol]);
			minSize += adjMatrix[minRow*vertexNum+minCol];
			if(allInPartition(inPartition, vertexNum))
				printf("Minimum Spanning Tree value = %d\n", minSize);
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
    for(;index< NUMBEROFTEST; index++) //= blockIdx.x * blockDim.x + threadIdx.x;
    switch (dataCPU[index].action) {
        case 'b':
            breadthFirstSearch(dataCPU[index].vertexNum,dataCPU[index].adjMatrix , dataCPU[index].vertex, dataOut[index].wasVisited, dataOut[index].queue, dataOut[index].fatherOf);
            break;
        case 'm':
            minimumSpanningTree(dataCPU[index].vertexNum,dataCPU[index].adjMatrix , dataCPU[index].vertex, dataOut[index].queue);
            break;
        case 'i':
            minimumPathDijkstra(dataCPU[index].vertexNum,dataCPU[index].adjMatrix , dataCPU[index].vertex, dataOut[index].wasVisited, dataOut[index].dist, dataOut[index].fatherOf);//, dataCPU.wasVisited);
            break;
       case 'f':
            minimumPathFloydWarshall(dataCPU[index].vertexNum,dataCPU[index].adjMatrix,dataOut[index].dist);
            break;
        default:
            break;
   }
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
int main(int argc, char* argv[]) {
    inputData *dataCPU = (inputData*)malloc(sizeof(inputData)* NUMBEROFTEST);
    outputData *dataOut = (outputData*)malloc(sizeof(outputData)* NUMBEROFTEST);
    readingInput(dataCPU,dataOut);
    struct timespec now, tmstart;
    clock_gettime(CLOCK_REALTIME, &tmstart);
    myKernel(dataCPU,dataOut);
    clock_gettime(CLOCK_REALTIME, &now);
    double seconds = (double)((now.tv_sec+now.tv_nsec*1e-9) - (double)(tmstart.tv_sec+tmstart.tv_nsec*1e-9));

    writeFile(seconds,argv[1]);
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






