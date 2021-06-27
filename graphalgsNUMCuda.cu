#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

__device__ void intializeVector(int* f, int value, int n) {

	for(int i=0; i < n; i++)
		f[i] = value;
}

void printPairs(int* v, int n) {

	printf("  Node |  Father\n\n");
	for(int i=0; i < n; i++)
		printf("  %2d   |    %2d\n", i, v[i]);

	printf("\n* -1 = root\n* -2 = unreachable\n\n");
}

__device__ void breadthFirstSearch(int vertexNum, int* adjMatrix, int vertex, int *wasVisited, int* queue, int* fatherOf) {

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

__device__ int allInPartition(int* partition, int n) {

	for(int i=0; i < n; i++)
		if(partition[i] == 0)
			return 0;

	return 1;
}

__device__ int heapIsEmpty(int* heap, int n) {

	for(int i=0; i < n; i++)
		if(heap[i] == 1)
			return 0;

	return 1;
}

__device__ int extractMin(int* heap, double* dist, int n) {

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

__device__ void minimumPathDijkstra(int vertexNum, int* adjMatrix, int vertex, int* heap, double *distance, int* fatherOf) {
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

__device__ void minimumPathFloydWarshall(int vertexNum, int* adjMatrix, double* dist) {
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

__device__ void minimumSpanningTree(int vertexNum, int* adjMatrix, int vertex, int* inPartition) {

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

__global__ void myKernel(inputData *dataCPU, outputData* dataOut)
{
    int index = blockIdx.x * blockDim.x + threadIdx.x;
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

    int i =0;
    cudaEvent_t start, stop; // To satart and stop cluck^M
        float time;
     cudaEventCreate(&start);
        cudaEventCreate(&stop);
        cudaEventRecord(start, 0);
    for(; i<NUMBEROFTEST;i++){
        int* d_adjMatrix;
        int* d_wasVisited;
        int* d_queue;
        int* d_fatherOf;
        double* d_dist;
        cudaMalloc((void**)&d_adjMatrix, dataCPU[i].vertexNum * dataCPU[i].vertexNum * sizeof(int));
        cudaMemcpy(d_adjMatrix,dataCPU[i].adjMatrix, dataCPU[i].vertexNum * dataCPU[i].vertexNum * sizeof(int),cudaMemcpyHostToDevice);
	switch (dataCPU[i].action) {
		case 'm':
			cudaMalloc((void**)&d_queue, dataCPU[i].vertexNum * sizeof(int));
                        cudaMemcpy(d_queue, dataOut[i].queue, dataCPU[i].vertexNum * sizeof(int),cudaMemcpyHostToDevice);
			out_data[i].queue = d_queue;
			break;
	        case 'b':
			cudaMalloc((void**)&d_wasVisited, dataCPU[i].vertexNum * sizeof(int));
                        cudaMemcpy(d_wasVisited, dataOut[i].wasVisited, dataCPU[i].vertexNum * sizeof(int),cudaMemcpyHostToDevice);
                        cudaMalloc((void**)&d_queue, dataCPU[i].vertexNum * sizeof(int));
                        cudaMemcpy(d_queue, dataOut[i].queue, dataCPU[i].vertexNum * sizeof(int),cudaMemcpyHostToDevice);
                        cudaMalloc((void**)&d_fatherOf, dataCPU[i].vertexNum * sizeof(int));
                        cudaMemcpy(d_fatherOf, dataOut[i].fatherOf, dataCPU[i].vertexNum * sizeof(int),cudaMemcpyHostToDevice);
                        out_data[i].fatherOf = d_fatherOf;
                        out_data[i].queue = d_queue;
                        out_data[i].wasVisited = d_wasVisited;
			break;
                case 'i':
			cudaMalloc((void**)&d_wasVisited, dataCPU[i].vertexNum * sizeof(int));
       			cudaMemcpy(d_wasVisited, dataOut[i].wasVisited, dataCPU[i].vertexNum * sizeof(int),cudaMemcpyHostToDevice);
        		cudaMalloc((void**)&d_dist, dataCPU[i].vertexNum * sizeof(double));
        		cudaMemcpy(d_dist, dataOut[i].dist, dataCPU[i].vertexNum * sizeof(double),cudaMemcpyHostToDevice);
        		cudaMalloc((void**)&d_fatherOf, dataCPU[i].vertexNum * sizeof(int));
        		cudaMemcpy(d_fatherOf, dataOut[i].fatherOf, dataCPU[i].vertexNum * sizeof(int),cudaMemcpyHostToDevice);
			out_data[i].fatherOf = d_fatherOf;
			out_data[i].dist = d_dist;
        		out_data[i].wasVisited = d_wasVisited;
	                break;
                case 'f':
			cudaMalloc((void**)&d_dist, dataCPU[i].vertexNum * dataCPU[i].vertexNum * sizeof(double));
        		cudaMemcpy(d_dist,dataOut[i].dist, dataCPU[i].vertexNum * dataCPU[i].vertexNum * sizeof(double),cudaMemcpyHostToDevice);
        		out_data[i].dist = d_dist;            
		   	break;
                default:
                        break;
	}
	in_data[i].vertex = dataCPU[i].vertex;
        in_data[i].vertexNum = dataCPU[i].vertexNum;
        in_data[i].adjMatrix = d_adjMatrix;
        in_data[i].action = dataCPU[i].action;
    }
    cudaMalloc ( (void**) &dataGPUIn, input_size);
    cudaMemcpy(dataGPUIn, in_data, input_size, cudaMemcpyHostToDevice );
    cudaMalloc ( (void**) &dataGPUOut, output_size);
    cudaMemcpy(dataGPUOut, out_data, output_size, cudaMemcpyHostToDevice );
    myKernel << <blocksPerGrid, threadsPerBlock >> >(dataGPUIn, dataGPUOut); // excute on kernel
    cudaMemcpy(out_data, dataGPUOut, output_size, cudaMemcpyDeviceToHost);
    i=0;
    for(; i<NUMBEROFTEST;i++){
	 switch (dataCPU[i].action) {
        	case 'b':
			cudaMemcpy(dataOut[i].fatherOf, out_data[i].fatherOf, dataCPU[i].vertexNum * sizeof(int), cudaMemcpyDeviceToHost);
            		break;
        	case 'i':
			cudaMemcpy(dataOut[i].fatherOf, out_data[i].fatherOf, dataCPU[i].vertexNum * sizeof(int), cudaMemcpyDeviceToHost);
			cudaMemcpy(dataOut[i].dist, out_data[i].dist, dataCPU[i].vertexNum * sizeof(double), cudaMemcpyDeviceToHost);
            		break;
       		case 'f':
			cudaMemcpy(dataOut[i].dist, out_data[i].dist, dataCPU[i].vertexNum *  dataCPU[i].vertexNum *sizeof(double), cudaMemcpyDeviceToHost);
            		break;
        	default:
            		break;
    	}
    }
    cudaFree(dataGPUIn);
    cudaFree(dataGPUOut);
    cudaEventRecord(stop, 0);
        cudaEventSynchronize(stop);
        cudaEventElapsedTime(&time, start, stop);
        cudaEventDestroy(start);
        cudaEventDestroy(stop);
    time = time/1000;
    writeFile(time,fileName);
}
int main(int argc, char* argv[]) {
    inputData *dataCPU = (inputData*)malloc(sizeof(inputData)* NUMBEROFTEST);
    outputData *dataOut = (outputData*)malloc(sizeof(outputData)* NUMBEROFTEST);
    readingInput(dataCPU,dataOut);
    launch(dataCPU,dataOut,argv[1]);
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






