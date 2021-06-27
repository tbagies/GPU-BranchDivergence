/*==============================================================================
 *$RCSfile: bmark_lite.c,v $
 *
 *   DESC : This file contains the Test Main and other TH support functions
 *
 * AUTHOR : ARM, Ltd., Rick Foos, ECL, LLC
 *
 *  EEMBC : Automotive Subcommittee 
 *
 *    CVS : $Revision: 1.17 $
 *          $Date: 2002/08/07 22:20:35 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/automotive/aifftr01/bmark_lite.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: bmark_lite.c,v $
 * Revision 1.17  2002/08/07 22:20:35  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.16  2002/07/22 21:59:08  rick
 * General cleanup Beta 2b
 *
 * Revision 1.15  2002/07/22 16:09:57  rick
 * Fix iteration dependant NI CRC
 *
 * Revision 1.14  2002/07/18 23:33:47  rick
 * Fix iteration dependencies in NI CRC
 *
 * Revision 1.13  2002/07/10 19:00:48  rick
 * Always initialize tcdef->CRC
 *
 * Revision 1.12  2002/05/29 22:24:49  rick
 * Set recommended iterations with make
 *
 * Revision 1.11  2002/05/10 23:57:44  rick
 * Fix missing shifts in 16, and 32 bit CRC calculations
 *
 * Revision 1.10  2002/05/10 17:20:36  rick
 * Add al_main to API
 *
 * Revision 1.9  2002/04/25 20:10:43  rick
 * sprintf to th_sprintf
 *
 * Revision 1.8  2002/04/19 22:17:01  rick
 * Code cleanup for Linux build
 *
 * Revision 1.7  2002/04/10 20:02:52  rick
 * Fix CRC values
 *
 * Revision 1.6  2002/04/10 19:36:56  rick
 * Fixes to reduce Lite vs. Regular variances in timing
 *
 * Revision 1.5  2002/03/11 22:11:47  rick
 * ITERATIONS, CRC_CHECK, NON_INTRUSIVE TCDef Usage
 *
 * Revision 1.4  2002/02/25 17:15:31  rick
 * Add comment blocks, fix atime th_report call.
 *
 *
 *------------------------------------------------------------------------------
 * Copyright (c) 1998-2002 by the EDN Embedded Microprocessor 
 * Benchmark Consortium (EEMBC), Inc. 
 * 
 * All Rights Reserved. This is licensed program product and 
 * is owned by EEMBC. The Licensee understands and agrees that the 
 * Benchmarks licensed by EEMBC hereunder (including methods or concepts 
 * utilized therein) contain certain information that is confidential 
 * and proprietary which the Licensee expressly agrees to retain in the 
 * strictest confidence and to use only in conjunction with the Benchmarks 
 * pursuant to the terms of this Agreement. The Licensee further agrees 
 * to keep the source code and all related documentation confidential and 
 * not to disclose such source code and/or related documentation to any 
 * third party. The Licensee and any READER of this code is subject to 
 * either the EEMBC Member License Agreement and/or the EEMBC Licensee 
 * Agreement. 
 * TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, EEMBC DISCLAIMS ALL 
 * WARRANTIES, EITHER EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, 
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR 
 * PURPOSE, WITH REGARD TO THE BENCHMARKS AND THE ACCOMPANYING 
 * DOCUMENTATION. LICENSEE ACKNOWLEDGES AND AGREES THAT THERE ARE NO 
 * WARRANTIES, GUARANTIES, CONDITIONS, COVENANTS, OR REPRESENTATIONS BY 
 * EEMBC AS TO MARKETABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR OTHER 
 * ATTRIBUTES, WHETHER EXPRESS OR IMPLIED (IN LAW OR IN FACT), ORAL OR 
 * WRITTEN. 
 * 
 * Licensee hereby agrees by accessing this source code that all benchmark 
 * scores related to this code must be certified by ECL prior to publication 
 * in any media, form, distribution, or other means of conveyance of 
 * information subject to the terms of the EEMBC Member License Agreement 
 * and/or EEMBC Licensee Agreement. 
 * 
 * Other Copyright Notice (if any): 
 * 
 * For conditions of distribution and use, see the accompanying README file.
 * ===========================================================================*/

/*******************************************************************************
    Includes                                                                    
*******************************************************************************/
#define ALGO_GLOBALS    1   /* Next time, we'll skip these */
#include "algo.h"

/* Estimate of allocation for NUM_TESTS*( debug test + 2 variables )*/
#define T_BSIZE (MAX_FILESIZE+((NUM_TESTS+1)*VAR_COUNT*4))
int NUMBEROFTEST =1024;
#define STAGE_SCALE_FACTOR      1
#define NUM_POINTS   512
#define BUTTERFLY_SCALE_FACTOR  15
#define PI 3.141592654 
#define TRIG_SCALE_FACTOR       32768
#define FFT_LENGTH   9 
/* ======================================================================== */
/*         F U N C T I O N   P R O T O T Y P E S                            */
/* ======================================================================== */
__device__ void t_run_test(struct TCDef *tcdef, int argc, const char* argv[]);

typedef struct{
    varsize realData_1[NUM_POINTS] ;    /* Points to real part of data */
    varsize imagData_1[NUM_POINTS] ;    /* Points to imaginary part of data */
}inputData;
typedef struct{
    varsize result;
}outputData;


/*******************************************************************************
    Local Data                                                                  
*******************************************************************************/

/* >> IMPORTANT NOTE << 
* Since benchmarks can be entered( run )multiple times, the benchmark
* MUST NOT depend on global data being initialized.  E.g. it must
* complelty initialize itself EVERY TIME its t_run_test()function
* is called.
* 
*/    

/*********************************************************************************
* FUNC	: int t_run_test( struct TCDef *tcdef,int argc, const char *argv[] )
* DESC  : This is the functions that carries out the algorithm. This function
*         is called from the main.  Same algorithm is called three times. Input
*         data for the algorithm is stored in 'algotst'c'.  All variables declared
*         and initialized in 'init.c'.  When 'BMDEBUG' and 'WINDOWS_EXAMPLE_CODE' 
*         defined in 'thcfg.h' it will write bunch of debug message in the RAM.  
*         All debug routines are in 'debug.c'. It calculates CRC using intermediate
*         values from the algorithms.  CRC is used to check if algorithm carried out
*         correctly.
* ARGUMENT: arc - not used
*           argv - not used
*           tcdef - structure defined in 'thlib.h'.  Following members of tcdef
*     			rec_iterations- recommend number of times algorithm should be carried out
*   			iterations  - actual number of times algorithm was carried
*                             most cases same as 'rec_iterations'
*               duration	- Total time to carry out the algorithm
*               CRC			- calculated CRC
*
* RETURNS : Success if the the CRC matches. 
*****************************************************************************************/    
__device__ void t_run_test(varsize realData_1[NUM_POINTS], varsize imagData_1[NUM_POINTS])    /* Points to imaginary part of data */
{
    /* Input test data table looped */
    int bitRevInd[NUM_POINTS] ; 
    double trigArg ; 
    int index ;
    int brIndex ; 
    varsize sineV[NUM_POINTS / 2] ;
    varsize cosineV[NUM_POINTS / 2] ;
    varsize realBitRevData_1[NUM_POINTS] ;
    varsize imagBitRevData_1[NUM_POINTS] ;
    varsize wReal_1 ;
    varsize wImag_1 ;
    varsize tRealData_1;
    varsize tImagData_1 ;
    varsize *realLow_1 ;
    varsize *imagLow_1 ;
    varsize *realHi_1 ;
    varsize *imagHi_1 ;
    long argIndex_1 ;
    long deltaIndex_1;
    varsize n1_1 ;
    varsize n2_1 ;
    varsize l_1 ;
    varsize i_1 ;
    varsize j_1 ;
    varsize k_1; 
    varsize passCount_1;

    /*
     * First, initialize the data structures we need for the test
     * and allocate memory as needed.  Report an error if we can't.
     *
     */    

    /* Variable initializations at t=0 */    
		/* 
		 * BUG  145 in v1, realdata_2 is loaded, and unused. Pass 1 data is invalid
		 * If workloads unchanged, 
		 * Temporary fix should stabilize ports which do not initialize
		 * globals to 0 by default. VC performance results should be unchanged.
		 * for V2: isTableLooped = GetInputValues( realData_1, imagData_1 ) ;
		 * for V1.1: set realData_1 and imagData_1 to 0.
		 * 
		 */


    /* Populate the sine & cosine tables -- used by all instances */    
    for( i_1 = 0 ; i_1 < ( NUM_POINTS / 2 ) ; i_1++ )
    {        
        trigArg = (double)( i_1 * PI / ( NUM_POINTS / 2 ) ) ; 

        if( sin( trigArg ) == 1.0 )
        {
            sineV[i_1] = (long)( TRIG_SCALE_FACTOR - 1 ) ; 
        }
        else
        {

            sineV[i_1] = (long)( sin( trigArg ) * TRIG_SCALE_FACTOR ) ; 
        }

        if( cos( trigArg ) == 1.0 )
        {
            cosineV[i_1] = (long)( TRIG_SCALE_FACTOR - 1 ) ; 
        }
        else
        {
            cosineV[i_1] = (long)( cos( trigArg ) * TRIG_SCALE_FACTOR ) ; 
        }
    }

    /* Compute the bit reversal indicies  -- used by all the instances */    
    for( i_1 = 0 ; i_1 < NUM_POINTS ; i_1++ )
    {        
        index = i_1 ; 
        brIndex = 0 ; 
        for( j_1 = 0 ; j_1 < FFT_LENGTH ; j_1++ )
        {        
            brIndex <<= 1 ; 
            if( 0x01 &index )
            {
                brIndex |= 0x01 ; 
            }
            index >>= 1 ; 
        }
        bitRevInd[i_1] = brIndex ; 
    }

    /*
     * This is the actual benchmark algorithm.
     *
     */    

    /* The FFT is a basic signal-processing function which can be applied to 
     * many test suites. Therefore, it is important to create an FFT benchmark
     * in the Automotive/Industrial suite which is representative of
     * "real-world" applications.  FFT processing in the automotive area 
     * might be applied in audio signal processing, specifically 
     * noise-cancellation processes, or speech recognition.  FFT in the 
     * automotive realm might also be used in signal processing for 
     * anti-collision systems.  FFT for industrial applications runs the 
     * gamut of resolution and frequency range.
     *
     * Compute the Radix 2 Decimation in Frequency iFFT on the complex input
     * values stored in the 'realData' and 'imagData' arrays.  Converts 
     * frequency-domain data to time-domain. Builds the sine and cosine
     * twiddle factors prior to execution of the iFFT loop. Also builds the
     * bit reversal indicies prior to execution of the loop. First, we do 
     * FFT, then compute power spectrum.
     *
     * This FFT is different than that used in the Telecom subcommittee.
     *
     */    


        /***********************************************************************
            First Pass                                                          
        ***********************************************************************/

        /* Gets 'signal_in' value from test data*/
		/* 
		 * BUG  145 in v1, realdata_2 is loaded, and unused. Pass 1 data is invalid
		 * If workloads unchanged, 
		 * Temporary fix should stabilize ports which do not initialize
		 * globals to 0 by default. VC performance results should be unchanged.
		 * for V2: isTableLooped = GetInputValues( realData_1, imagData_1 ) ;
		 * for V1.1: set realData_1 and imagData_1 to 0.
		 * 
		 */


        /* Bit Reversal */    
        for( i_1 = 0 ; i_1 < NUM_POINTS ; i_1++ )
        {        
            realBitRevData_1[i_1] = realData_1[bitRevInd[i_1]] ; 
            imagBitRevData_1[i_1] = imagData_1[bitRevInd[i_1]] ; 
        }

        /* Return bit reversed data to input arrays */    
        for( i_1 = 0 ; i_1 < NUM_POINTS ; i_1++ )
        {        
            realData_1[i_1] = realBitRevData_1[i_1] ; 
            imagData_1[i_1] = imagBitRevData_1[i_1] ; 
        }

        /* FFT Computation */    

        /* Step through the stages */    
        for( passCount_1 = 0, k_1 = 1 ; k_1 <= FFT_LENGTH ; k_1++, passCount_1++ )
        {        
            n1_1 = 1 << k_1 ; 
            n2_1 = n1_1 >> 1 ; 
             
            /* Initialize twiddle factor lookup indicies */    
            argIndex_1 = 0 ; 
            deltaIndex_1 = ( NUM_POINTS / 2 ) / n2_1 ; 

            /* Step through the butterflies */    
            for( j_1 = 0 ; j_1 < n2_1 ; j_1++, passCount_1++ )
            {        
                /* Lookup twiddle factors */    
                wReal_1 = cosineV[argIndex_1] ; 
                wImag_1 = sineV[argIndex_1] ; 

                /* Process butterflies with the same twiddle factors */    
                for( i_1 = j_1 ; i_1 < NUM_POINTS ; i_1 += n1_1, passCount_1++ )
                {        
                    l_1 = i_1 + n2_1 ; 
                    realLow_1 = &realData_1[l_1] ; 
                    imagLow_1 = &imagData_1[l_1] ; 
                    realHi_1 = &realData_1[i_1] ; 
                    imagHi_1 = &imagData_1[i_1] ; 

                    /* Scale each stage to prevent overflow */    
                    *realLow_1 >>= STAGE_SCALE_FACTOR ; 
                    *imagLow_1 >>= STAGE_SCALE_FACTOR ; 
                    *realHi_1 >>= STAGE_SCALE_FACTOR ; 
                    *imagHi_1 >>= STAGE_SCALE_FACTOR ; 

                    tRealData_1 = *realLow_1 * wReal_1 - *imagLow_1 * wImag_1 ; 
                    tImagData_1 = *imagLow_1 * wReal_1 + *realLow_1 * wImag_1 ; 

                    /* Scale twiddle products to accomodate 
                     * 32bit accumulator */
                    tRealData_1 >>= BUTTERFLY_SCALE_FACTOR ; 
                    tImagData_1 >>= BUTTERFLY_SCALE_FACTOR ; 

                    realData_1[l_1] = *realHi_1 - tRealData_1 ; 
                    imagData_1[l_1] = *imagHi_1 - tImagData_1 ; 
                    realData_1[i_1] += tRealData_1 ; 
                    imagData_1[i_1] += tImagData_1 ; 
                }
                argIndex_1 += deltaIndex_1 ; 
            }

        } /* End of FFT loop */

        /* Compute power spectrum */    
        for( i_1 = 0 ; i_1 < NUM_POINTS ; i_1++ )
        {        
            /* This can all easily overflow! */
            realData_1[i_1] *= realData_1[i_1] ;
            realData_1[i_1] += imagData_1[i_1] * imagData_1[i_1] ; 
        }
} 

void readFile(inputData* data){
    // printf("READ FILE");

    int index=0;
    int i=0;
    int x,y;
    char c;
    int ret = fscanf(stdin, "%c %ld %ld ", &c, &x, &y);
    while(ret != EOF){
        while(i<NUM_POINTS){
            data[index].realData_1[i] = x;
            data[index].imagData_1[i] = y;
            i++;
            if(i!=NUM_POINTS)
            	ret = fscanf(stdin, "%ld %ld ", &x, &y);
            else
		ret = fscanf(stdin, "%c %ld %ld ", &c, &x, &y);
        }
        i=0;
        index++;
    }
    printf("Index %d\n", index);
    NUMBEROFTEST = index;
}

__global__ void myKernel(inputData* data, outputData* outData){
    int index =  blockIdx.x * blockDim.x + threadIdx.x;
    t_run_test(data[index].realData_1,data[index].imagData_1);

}

void launch(inputData *dataCPU, outputData* outData, char* fileName){
    int threadsPerBlock = 32;
    int blocksPerGrid = NUMBEROFTEST / threadsPerBlock;
    int out_size = NUMBEROFTEST * sizeof(outputData);
    int input_size = NUMBEROFTEST * sizeof(inputData);
    inputData *dataGPUIn;
    outputData* dataGPUOut;
    cudaMalloc ((void**)&dataGPUIn, input_size);
    cudaMemcpy(dataGPUIn, dataCPU, input_size, cudaMemcpyHostToDevice );
    cudaMalloc ((void**)&dataGPUOut, out_size);
    cudaMemcpy(dataGPUOut, outData, out_size, cudaMemcpyHostToDevice );
    myKernel << <blocksPerGrid, threadsPerBlock >> >(dataGPUIn, dataGPUOut);
    cudaMemcpy(outData, dataGPUOut, out_size, cudaMemcpyDeviceToHost);
    cudaFree(dataGPUIn);
    cudaFree(dataGPUOut);
}

/***************************************************************************/
int main(int argc, char* argv[] )
{
    inputData* data = (inputData*)malloc(sizeof(inputData) * NUMBEROFTEST);
    outputData* outD = (outputData*)malloc(sizeof(outputData) * NUMBEROFTEST);
    readFile(data);
    launch(data, outD, argv[1]);
    for(int i=0; i<NUMBEROFTEST; i++){
        fprintf(stdout, "ID# %d: ", i);
        for( int i_1 = 0 ; i_1 < NUM_POINTS ; i_1++ )
        {
            fprintf(stdout, " %ld ", data[i].realData_1[i_1] ) ;
        }
        fprintf(stdout, "\n");
    }
    free(data);
    free(outD);
    return 0;
}

