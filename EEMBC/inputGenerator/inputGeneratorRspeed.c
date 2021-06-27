#include <stdlib.h>
#include <stdio.h>
/*==============================================================================
 *$RCSfile: bmark.c,v $
 *
 *   DESC : This file contains the Test Main and other TH support functions
 *
 * AUTHOR : ECL, LLP
 *
 *  EEMBC : 8-16 Bit Subcommittee 
 *
 *    CVS : $Revision: 1.8 $
 *          $Date: 2002/08/07 22:21:44 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/automotive/rspeed01/bmark.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: bmark.c,v $
 * Revision 1.8  2002/08/07 22:21:44  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.7  2002/07/22 16:10:16  rick
 * Fix iteration dependant NI CRC
 *
 * Revision 1.6  2002/05/29 22:25:32  rick
 * Set recommended iterations with make
 *
 * Revision 1.5  2002/04/25 20:10:45  rick
 * sprintf to th_sprintf
 *
 * Revision 1.4  2002/04/19 18:31:38  rick
 * Bug #146: global tablecount uninitialized
 *
 * Revision 1.3  2002/04/10 19:36:59  rick
 * Fixes to reduce Lite vs. Regular variances in timing
 *
 * Revision 1.2  2002/03/12 18:31:04  rick
 * ITERATIONS, CRC_CHECK, NON_INTRUSIVE_CRC_CHECK, add standards headers
 *
 * Revision 1.3  2002/03/12 17:36:36  rick
 * ITERATIONS, CRC_CHECK, NON_INTRUSIVE_CRC_CHECK
 *
 *
 *   5/14/99 pjt     1.0
 *       Initial cleanup
 *   7/4/99  arw     1.0
 *       Added eembc_dt.h datatypes & additional cleanup
 *       "thlib.h" will #include eembc_dt.h for us
 *
 *	7/13/99 arw		1.0
 *		Corrected WriteOut() and 
 *		Changed variable names starting with debugOut* to RAMfile*
 *		Changed various declarations
 *   6/29/01 TC      8/16 Bit Benchmark Suite (V 2.0)
 *       Removed all debug related code to debug.c
 *       Removed all intialization and variable declaration to init.c
 *       Added all extern in algo.h
 *       Removed 'varsize', mostly replaced with proper typedef 
 *       Combined THResult structure and TCDef structure into one	
 *       Added CRC in TCDef structure - Calculates running CRC of some of the
 *       intermediate values.
 *       Remove WriteOut routine, because it was redundant with the DebugOutString
 *       added #if CRC_CHECK, so that number of iterations can be changed
 *       In order to match CRC, you have to use pre-defined number of iterations
 *       Took out all dynamic memory allocations
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

/* Estimate of allocation for NUM_TESTS*( debug test + 2 variables )*/

/* ======================================================================== */
/*         F U N C T I O N   P R O T O T Y P E S                            */
/* ======================================================================== */

/* Define iterations */
typedef short varsize ; 
int NUMBEROFTEST = 1024;

typedef struct{
    varsize in1;
    varsize in2;
    varsize in3;
}inputData;

/*******************************************************************************
    Local Data                                                                  
*******************************************************************************/

/* Source of the test data, in "ROM" */
varsize tonewheelCounter ;   
/* Array of 'tonewheelCounter' test data values */
varsize *inpTonewheelCount ; 
/* Number of teeth on the tonewheel */
varsize tonewheelTeeth =60;     
#define MIN_TOOTH_TIME      100   
/* Maximum inter-pulse period permitted( zero road-speed )*/
#define MAX_TOOTH_TIME      10000
#define MAX_VARIABLE 0x7FFF
#define SPEEDO_SCALE_FACTOR 36000

void writeToInputFile(varsize in1,varsize toothCount1,varsize toothDeltaTime1,varsize toothDeltaTimeLast1,varsize tonewheelCounterLast1,varsize toothTimeAccum1){
    FILE *fp;
    fp = fopen("inputFile.txt", "a");
    if (fp == NULL){
        printf("Problem in a file");
        return;
    }
    fprintf(fp,"r ");
    fprintf(fp,"%ld", in1);

    fprintf(fp," %ld", toothCount1);

    fprintf(fp," %ld", toothDeltaTime1);

    fprintf(fp," %ld", toothDeltaTimeLast1);

    fprintf(fp," %ld", tonewheelCounterLast1);

    fprintf(fp," %ld", toothTimeAccum1);

    fprintf(fp," 0");

    fprintf(fp," 0");

    fprintf(fp," 0");
    
    fprintf(fp," 0");
    fprintf(fp," 0");
    
    fputs("\n",fp);
    fclose(fp);
}

/* >> IMPORTANT NOTE << 
*
* Since benchmarks can be entered( run )multiple times, the benchmark
* MUST NOT depend on global data being initialized.  E.g. it must
* complelty initialize itself EVERY TIME its t_run_test()function
* is called.
* 
*/    

/*
* FUNC   : t_run_test
*
* DESC   : called to run the test
*
*          This function is called to start the test.  It does not return
*          until after the test is completed( finished ).  Note, th_finished()
*          and th_report_results()MUST be called before this function
*          returns if results are to be report.  If these are not called
*          then no results will be reported for the test.
*         
* NOTE   : after this function returns, no other functions in the test
*          will be called.  EG, returning from this function is equivelent
*          to returning from a main()or calling th_exit()
*
* RETURNS : Success if the test ran fine.  If th_finished()and
*          th_report_results()were not called, then the test finished
*          successfully, but there were no results and the host will
*          not be able to measure the test's duration.
*/
/* Input test data table looped */
/* Output variable 'roadSpeed' is calculated */
static varsize roadSpeed1 ;
/*  from inter-pulse period, 'toothDeltaTime' */
static varsize toothDeltaTime1 ;
/* History of 'toothDeltaTime' */
static varsize toothDeltaTimeLast1 ;
/* History of the pulse timer/counter */
static varsize tonewheelCounterLast1 ;
/* Accumulator for filtering pulse time */
static long toothTimeAccum1 ;
/* Counter for filtering pulse time */
static varsize toothCount1 ;

void t_run_test( inputData* data)
{
    /* 
     * First, initialize the data structures we need for the test
     * and allocate memory as needed.  Report an error if we can't.
     *
     */    

    /* Variable initializations at t=0 */


    writeToInputFile(data->in1, toothCount1, toothDeltaTime1,toothDeltaTimeLast1,tonewheelCounterLast1,toothTimeAccum1);
        /***********************************************************************
            First Pass                                                          
        ***********************************************************************/

        tonewheelCounter = data->in1;

        /*
         * Compute 'toothDeltaTime' -- the difference in counter 
         * readings from the last pulse to the current one.  Note that
         * the realtime counter may roll over, so the elapsed time may
         * need to be corrected when this occurs.
         *
         * The 'roadSpeed' calculation will be performed twice for each
         * revolution of the tonewheel, so some filtering of pulse-period
         * is performed.
         *
         * If the period between pulses goes out to some maximum, then
         * road speed will be forced to zero.  Also, if the period between
         * pulses gets unrealistically small, we'll ignore it, presuming
         * that we're just picking up noise.
         *
         * We also watch out for strange excursions in the pulse period, to
         * filter out errors :  if the period suddenly jumps to several times
         * the last period measured, then it is ignored.
         *
         */    

        /* Compute period between pulses */    
        toothDeltaTime1 = (varsize)
            ( tonewheelCounter - tonewheelCounterLast1 ) ; 

        /* Check for timer overflow */
        if( tonewheelCounterLast1 > tonewheelCounter )
        {
            /* ...and correct for it */
            toothDeltaTime1 += ( varsize )( MAX_VARIABLE + 1 ) ;
        }

        /* Watch out for erroneously short */
        if( toothDeltaTime1 < MIN_TOOTH_TIME )   
        {
            /* ...pulse period */
            toothDeltaTime1 = toothDeltaTimeLast1 ;    
        }
        
        /* Watch out for erroneously long */
        if( toothDeltaTime1 > 4 * toothDeltaTimeLast1 )
        {
            /* ...pulse period */
            toothDeltaTime1 = toothDeltaTimeLast1 ;
        }

        /* Update timer history */
        tonewheelCounterLast1 = tonewheelCounter ;
        /* ...and accumulate pulses for filtering */
        toothTimeAccum1 += toothDeltaTime1 ;
        /* ...counting the pulses being filtered */
        toothCount1++ ;
        /* Remember this pulse's period */
        toothDeltaTimeLast1 = toothDeltaTime1 ;

        /* Time to update ? */
        if( toothCount1 >= tonewheelTeeth / 2 )
        {            
            /* Yes, */
            if( toothTimeAccum1 > MAX_TOOTH_TIME *tonewheelTeeth / 2 )   
            {    
                /* ...check for zero road speed */
                roadSpeed1 = 0 ;    
            }
            else
            {
                /* ...or compute road speed */
                roadSpeed1 = (varsize ) ( SPEEDO_SCALE_FACTOR  / 
                      ( toothTimeAccum1 / tonewheelTeeth * 2 ) ) ; 
                /* ...then reset the filter counter */
                toothCount1 = 0 ;
                /* ...and clear the accumulator */
                toothTimeAccum1 = 0 ;
            }
        }
} /* End of function 't_run_test' */

/*
* FUNC   : test_main
*
* DESC   : the test( or bench mark )main entry point
*
* RETURNS : Any error value defined in th_error.h
*/    
void readFile(inputData* data){

    int index=0;
    int X, Y, Z;

    int ret = fscanf(stdin, "%d", &X);
    while(ret != EOF && index<1024){
        data[index].in1 = X ;

        /* ...and pulse filter */

        index++;
        ret = fscanf(stdin,"%d", &X);
    }
    //NUMBEROFTEST = index;
}

int main(int argc, const char *argv[] )
{
    inputData* data = (inputData*)malloc(sizeof(inputData) * NUMBEROFTEST);
    readFile(data);
    toothCount1 = 0 ;
    /* ...and haven't accumulated for filter */
    toothTimeAccum1 = 0 ;
    /* ...Road speed starts at '0' */
    roadSpeed1 = 0 ;
    /* ...and no pulse history yet */
    tonewheelCounterLast1 = 0 ;
    toothDeltaTimeLast1 = MAX_TOOTH_TIME ;

    int i;
    for( i=0; i<NUMBEROFTEST; i++){
        //printf("%ld %ld %ld\n", data[i].in1, data[i].in2, data[i].in3);
        t_run_test(&data[i]);
    }

    return 1;
}
