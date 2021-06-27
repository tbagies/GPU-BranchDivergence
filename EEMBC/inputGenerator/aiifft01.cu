/*==============================================================================
 *$RCSfile: bmark_lite.c,v $
 *
 *   DESC : This file contains the Test Main and other TH support functions
 *
 * AUTHOR : ARM, Ltd., Rick Foos, ECL, LLC
 *
 *  EEMBC : Automotive Subcommittee 
 *
 *    CVS : $Revision: 1.15 $
 *          $Date: 2002/08/07 22:20:41 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/automotive/aiifft01/bmark_lite.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: bmark_lite.c,v $
 * Revision 1.15  2002/08/07 22:20:41  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.14  2002/07/22 21:59:12  rick
 * General cleanup Beta 2b
 *
 * Revision 1.13  2002/07/22 16:10:04  rick
 * Fix iteration dependant NI CRC
 *
 * Revision 1.12  2002/07/18 23:33:49  rick
 * Fix iteration dependencies in NI CRC
 *
 * Revision 1.11  2002/07/10 19:00:50  rick
 * Always initialize tcdef->CRC
 *
 * Revision 1.10  2002/05/29 22:24:53  rick
 * Set recommended iterations with make
 *
 * Revision 1.9  2002/05/10 23:57:45  rick
 * Fix missing shifts in 16, and 32 bit CRC calculations
 *
 * Revision 1.8  2002/05/10 17:20:36  rick
 * Add al_main to API
 *
 * Revision 1.7  2002/04/25 20:10:43  rick
 * sprintf to th_sprintf
 *
 * Revision 1.6  2002/04/10 19:53:19  rick
 * Fix CRC error
 *
 * Revision 1.5  2002/04/10 19:36:58  rick
 * Fixes to reduce Lite vs. Regular variances in timing
 *
 * Revision 1.4  2002/03/11 22:11:47  rick
 * ITERATIONS, CRC_CHECK, NON_INTRUSIVE TCDef Usage
 *
 * Revision 1.3  2002/02/25 17:15:32  rick
 * Add comment blocks, fix atime th_report call.
 *
 *   5/14/99 pjt     1.0
 *       Initial cleanup
 *   7/4/99  arw     1.0
 *       Added eembc_dt.h datatypes & additional cleanup
 *       "thlib.h" will #include eembc_dt.h for us
 *	7/13/99 arw		1.0
 *		Corrected WriteOut() and 
 *		Changed variable names starting with debugOut* to RAMfile*
 *		Changed various declarations
 *   5/29/01 TC 
 *       Removed all debug related code to debug.c
 *       Removed all intializatio and variable declaration to init.c
 *       Added all extern in algo.h
 *       Removed 'varsize', mostly replaced with n_int 
 *       Combined THResult structure and TCDef structure into one	
 *       Added CRC in TCDef structure - Calculates running CRC of all the
 *       intermediate value
 *       added #if CRC_CHECK, so that number of iterations can be changed
 *       In order to match CRC, you have to use pre-defined number of iterations
 *       Removed all dynamic memory allocation
 *   7/24/01 TC/arw  8/16 Bit Benchmark Suite (V 2.0)
 *       Added optional compile define for all CRC operation with CRC_CHECK.
 *       turn on CRC operation by setting #define CRC_CHECK	TRUE
 *       turn off CRC operation by setting #define CRC_CHECK FALSE 
 *       define for CRC_CHECK is in th\al\thcfg.h file
 *       Please use recommended # of iterations when CRC_CHECK is enabled
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

#define NUM_POINTS    512   /* Number of points in FFT */
#define FFT_LENGTH    9     /* length = log2( NUM_POINTS )*/

#ifdef PI
#undef PI
#endif
#define PI    3.141592654

/* TRIG_SCALE_FACTOR is used for greatest twiddle factor precision */
#define TRIG_SCALE_FACTOR           32768

/* BUTTERFLY_SCALE_FACTOR = log2( TRIG_SCALE_FACTOR )is used to
accomodate accumulator size limit of 32 bits */
#define BUTTERFLY_SCALE_FACTOR      15

/* STAGE_SCALE_FACTOR is used to prevent overflow from
accumulation at each processing stage */
#define STAGE_SCALE_FACTOR          1

int NUMBEROFTEST =1024;

typedef struct{
    varsize realData_1[NUM_POINTS] ;    /* Points to real part of data */
    varsize imagData_1[NUM_POINTS] ;    /* Points to imaginary part of data */
}inputData;

typedef struct{

}outputData;

/* ======================================================================== */
/*         F U N C T I O N   P R O T O T Y P E S                            */
/* ======================================================================== */
__device__ void aiifft01( varsize realData_1[NUM_POINTS], varsize imagData_1[NUM_POINTS]);


__device__ void aiifft01( varsize realData_1[NUM_POINTS], varsize imagData_1[NUM_POINTS])
{
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
     varsize tRealData_1 ;
     varsize tImagData_1 ;
     varsize *realLow_1 ;
     varsize *imagLow_1 ;
     varsize *realHi_1 ;
     varsize *imagHi_1 ;
     long argIndex_1 ;
     long deltaIndex_1 ;
     varsize n1_1 ;
     varsize n2_1 ;
     varsize l_1 ;
     varsize i_1 ;
     varsize j_1 ;
     varsize k_1 ;
     varsize passCount_1 ;
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

    /*
     * Inverse FFT processing in the automotive area might be applied in audio
     * signal processing, specifically noise-cancellation processes.
     *
     * Compute the Radix 2 Decimation in Frequency iFFT on the complex input
     * values stored in the 'realData' and 'imagData' arrays.  Converts
     * frequency-domain data to time-domain.  Builds the sine and cosine
     * twiddle factors prior to execution of the iFFT loop.  Also builds 
     * the bit reversal indicies prior to execution of the loop.
     *
     */

        /***********************************************************************
            First Pass                                                          
        ***********************************************************************/

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

        /* iFFT Computation */    

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
                /* Note iFFT reversal of sign */
                wImag_1 = -sineV[argIndex_1] ;

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

                    /* Scale twiddle products to accomodate 32-bit accu. */
                    tRealData_1 >>= BUTTERFLY_SCALE_FACTOR ; 
                    tImagData_1 >>= BUTTERFLY_SCALE_FACTOR ; 

                    realData_1[l_1] = *realHi_1 - tRealData_1 ; 
                    imagData_1[l_1] = *imagHi_1 - tImagData_1 ; 
                    realData_1[i_1] += tRealData_1 ; 
                    imagData_1[i_1] += tImagData_1 ; 
                }
                argIndex_1 += deltaIndex_1 ; 
            }
        } /* End of iFFT loop */
}

void readFile(inputData* data){
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
    aiifft01(data[index].realData_1,data[index].imagData_1);

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

