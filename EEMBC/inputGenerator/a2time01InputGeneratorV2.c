/*==============================================================================
 *$RCSfile: bmark.c,v $
 *
 *   DESC : This file contains the Test Main and other TH support functions
 *
 * AUTHOR : ARM, Ltd., ECL, LLP
 *
 *  EEMBC : Automotive Subcommittee 
 *
 *    CVS : $Revision: 1.7 $
 *          $Date: 2002/08/07 22:20:25 $
 *          $Author: rick $
 *          $Source: d:/cvs/eembc2/automotive/a2time01/bmark.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: bmark.c,v $
 * Revision 1.7  2002/08/07 22:20:25  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.6  2002/07/22 16:09:49  rick
 * Fix iteration dependant NI CRC
 *
 * Revision 1.5  2002/05/29 22:24:45  rick
 * Set recommended iterations with make
 *
 * Revision 1.4  2002/04/25 20:10:43  rick
 * sprintf to th_sprintf
 *
 * Revision 1.3  2002/04/19 18:31:37  rick
 * Bug #146: global tablecount uninitialized
 *
 * Revision 1.2  2002/03/08 00:58:51  rick
 * Repair Iterations and CRC ifdef logic
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

#define ALGO_GLOBALS    1   /* Next time, we'll skip these */
#include "algo.h"

/* Estimate of allocation for NUM_TESTS*( debug test + 2 variables )*/
#define T_BSIZE (MAX_FILESIZE+((NUM_TESTS+1)*VAR_COUNT*4))

//int t_run_test( size_t iterations, int argc, const char *argv[] ) ;
//int test_main( struct TCDef **tcdef, int argc, const char *argv[] ) ;

/* Define iterations */
#define ITERATIONS 50000	/* recommended iterations for benchmark */
int NUMBEROFTEST = 1024;

typedef struct{
    varsize in1;
    varsize outengineSpeed1;
    varsize outfiringTime1;
} inputData;
int   tableCount;        /* Number of passes through table */
void WriteOut(varsize value,varsize* output);
void t_run_test( inputData* data ) ;
void writeToInputFile(varsize in1,
                      varsize pulseDeltaTime1,
                varsize angle1,
                 varsize angleCounterLast1,
                 varsize toothCount1,
                 varsize deltaTimeAccum1,
                 varsize deltaTimeAvg1,
                 varsize firingTime1,
                 varsize tdcTime1,
                 unsigned long engineSpeed1,
                 unsigned long rotationTime1);


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

void
t_run_test(inputData* data)//int argc, const char *argv[] )
{        
    size_t loop_cnt ; 

    varsize i ;

    static char szDataSize[40] ;
    int isTableLooped = false;    /* Input test data table looped */
    varsize window ;
    static varsize pulseDeltaTime1 =0;
    static varsize angle1 =0;
    static varsize angleCounterLast1 =0;
    static varsize toothCount1 =0;
    static varsize deltaTimeAccum1 =0;
    static varsize deltaTimeAvg1 = 32767;
    static varsize firingTime1 =0;
    static unsigned long tdcTime1 =0;
    static unsigned long engineSpeed1 =0 ;
    static unsigned long rotationTime1 =0 ;
    writeToInputFile(data->in1, pulseDeltaTime1,
                     angle1, 
                     angleCounterLast1,
                     toothCount1, 
                     deltaTimeAccum1, 
                     deltaTimeAvg1, 
                     firingTime1, 
                     tdcTime1,
                     engineSpeed1,
                     rotationTime1);
/* ALGO_GLOBALS */
    tableCount		= 0;
	varsize angleCounter	= data->in1;   /* Current 'angleCounter' pulled from  data */
//	inpAngleCount	= NULL; /* Array of 'angleCounter' test data values */
    varsize tonewheelTeeth	= NUM_TEETH; /* Number of teeth on the tonewheel */
  


    szDataSize[0] = (char)( '0' + DATA_SIZE ) ;
    szDataSize[1] = '\0' ; 

    /* Initialize the test data -- stimuli for the algorithm. */    
    /* Allocate for the test input data table */


    window = TENTH_DEGREES / tonewheelTeeth ; /* Only need to do this once */

    /* This is the actual benchmark algorithm. */    

  //  for( loop_cnt = 0 ; loop_cnt < iterations ; loop_cnt++ ) /* no stopping! */
   // {


        /***********************************************************************
            First Pass                                                          
        ***********************************************************************/

        /* Gets 'angleCounter' value from test data*/
        isTableLooped = true;//data.in1;

        /*
         * Compute 'pulseDeltaTime' -- the difference in counter 
         * readings from the last pulse to the current one.  Note that
         * the realtime counter may roll over, so the elapsed time may
         * need to be corrected when this occurs.
         *
         */    
        if( angleCounterLast1 > angleCounter ) 
        {
            pulseDeltaTime1 = angleCounter + 
                ( (varsize)MAX_VARIABLE - angleCounterLast1 + 1 ) ;
        }
        else
        {
            pulseDeltaTime1 = angleCounter - angleCounterLast1 ; 
        }

        /* Update timer history... */
        angleCounterLast1 = angleCounter ;
        /* ...and elapsed time for a revolution */
        rotationTime1 += pulseDeltaTime1 ;

        /*
         * Must detect TDC reference by noticing that the period between this
         * pulse and the last one is two or three times normal.  We'll set a
         * flag when TDC reference occurs, and clear it on all other pulses.
         * We also keep count of which pulse we're on relative to TDC reference.
         *
         */    

        if( pulseDeltaTime1 > ( TDC_TEETH *deltaTimeAvg1 *TDC_MARGIN ) )
        {
         //   isTopDeadCenter1 = true ;
            pulseDeltaTime1 /= TDC_TEETH ; 
    
            /*
             * Compute engine speed every TDC.  Engine speed will be
             * the inverse of 'tdcTime', which is the period( in CPU
             * time )between TDC's.  Engine speed is also scaled by
             * an arbitrary constant to make it useful elsewhere in
             * the engine controller.
             *
             */    
            tdcTime1 = rotationTime1 ; 
            rotationTime1 = 0 ;
            engineSpeed1 = RPM_SCALE_FACTOR / tdcTime1 ;
            toothCount1 = 0 ; 
        }
        else 
        {
            toothCount1++ ; 
            //isTopDeadCenter1 = false ;
        }

        WriteOut(engineSpeed1, &data->outengineSpeed1) ;

        /*
         * Compute an average delta-T for TDC pulse discrimination.
         * The delta-T will be filtered by averaging over the period
         * of one cylinder( several pulses ).
         *
         */    

        deltaTimeAccum1 += pulseDeltaTime1 ;

        if( ( toothCount1 > 0 ) && 
            ( toothCount1 %( tonewheelTeeth / CYLINDERS ) == 0 ) )
        {        
            deltaTimeAvg1 = deltaTimeAccum1 / ( tonewheelTeeth / CYLINDERS ) ; 
            deltaTimeAccum1 = 0 ; 
        }


        angle1 = ( TENTH_DEGREES * toothCount1 / tonewheelTeeth ) ; 

        /*
         * Now, output a value for the firing angle timer( a one-shot )
         * only if we're on the tooth which precedes the firing
         * angle for one of the cylinders.  We presume that there is
         * always a tooth which precedes each cylinder's firing angle.
         * The value which is output presumably goes to a "capture/compare"
         * timer which generates an interrupt used to fire that cylinder.
         * Note the special treatment for the last cylinder( #4, #6, or #8 ), 
         * we don't subtract the 'angle' because the 360th degree of rotation
         * is the same as the 0th degree of the next rotation.
         *
         */    

        /* CYLINDER 1 */    
        if( ( angle1 >= ( ( CYL1 * TENTH_DEGREES / CYLINDERS ) - window ) ) && 
            ( angle1 < ( CYL1 * TENTH_DEGREES / CYLINDERS ) ) )
        {
            firingTime1 = 
                ( ( FIRE1_ANGLE - angle1 ) * tdcTime1 / TENTH_DEGREES ) +
                angleCounter ; 
        }

        /* CYLINDER 2 */    
        if( ( angle1 >= ( ( CYL2 * TENTH_DEGREES / CYLINDERS ) - window ) ) && 
            ( angle1 < ( CYL2 * TENTH_DEGREES / CYLINDERS ) ) )
        {        
            firingTime1 = 
                ( ( FIRE2_ANGLE - angle1 ) * tdcTime1 / TENTH_DEGREES ) +
                angleCounter ; 
        }

        /* CYLINDER 3 */    
        if( ( angle1 >= ( ( CYL3 * TENTH_DEGREES / CYLINDERS ) - window ) ) && 
            ( angle1 < ( CYL3 * TENTH_DEGREES / CYLINDERS ) ) )
        {        
            firingTime1 = 
                ( ( FIRE3_ANGLE - angle1 ) * tdcTime1 / TENTH_DEGREES ) +
                angleCounter ; 
        }

        /* CYLINDER 4 */    
        if( ( angle1 >= ( ( CYL4 * TENTH_DEGREES / CYLINDERS ) - window ) ) && 
            ( angle1 < ( CYL4 * TENTH_DEGREES / CYLINDERS ) ) )
        {        
            firingTime1 = 
                ( ( FIRE4_ANGLE - angle1 ) * tdcTime1 / TENTH_DEGREES ) +
                angleCounter ; 
        }

#if( CYLINDERS > 4 )

        /* CYLINDER 5 */    
        if( ( angle1 >= ( ( CYL5 * TENTH_DEGREES / CYLINDERS ) - window ) ) &&
            ( angle1 < ( CYL5 * TENTH_DEGREES / CYLINDERS ) ) )
        {        
            firingTime1 = 
                ( ( FIRE5_ANGLE - angle1 ) * tdcTime1 / TENTH_DEGREES ) +
                angleCounter ; 
        }

        /* CYLINDER 6 */    
        if( ( angle1 >= ( ( CYL6 * TENTH_DEGREES / CYLINDERS ) - window ) ) &&
            ( angle1 < ( CYL6 * TENTH_DEGREES / CYLINDERS ) ) )
        {        
            firingTime1 = 
                ( ( FIRE6_ANGLE - angle1 ) * tdcTime1 / TENTH_DEGREES ) + 
                angleCounter ; 
        }

#if( CYLINDERS > 6 )

        /* CYLINDER 7 */    
        if( ( angle1 >= ( ( CYL7 * TENTH_DEGREES / CYLINDERS ) - window ) ) &&
            ( angle1 < ( CYL7 * TENTH_DEGREES / CYLINDERS ) ) )
        {        
            firingTime1 = 
                ( ( FIRE7_ANGLE - angle1 ) * tdcTime1 / TENTH_DEGREES ) +
                angleCounter ; 
        }

        /* CYLINDER 8 */    
        if( ( angle1 >= ( ( CYL8 * TENTH_DEGREES / CYLINDERS ) - window ) ) &&
            ( angle1 < ( CYL8 * TENTH_DEGREES / CYLINDERS ) ) )
        {        
            firingTime1 = 
                ( ( FIRE8_ANGLE - angle1 ) * tdcTime1 / TENTH_DEGREES ) + 
                angleCounter ; 
        }

#endif /* 6 cylinders */
#endif /* 4 cylinders */

        if( firingTime1 > MAX_VARIABLE )
        {
            firingTime1 -= MAX_VARIABLE ; 
        }

        /* Output the 'firingTime result */
        WriteOut(firingTime1, &data->outfiringTime1 ) ;


}

void readFile(inputData* data){
   // printf("READ FILE");

    int index=0;
    int X;
    int ret = fscanf(stdin, "%d", &X);
    while(ret != EOF && index<1024){
        data[index].in1 = X ;
        index++;
        ret = fscanf(stdin,"%d", &X);
    }
  // printf("END READ FILE");
    NUMBEROFTEST = index;
}

int main(int argc, const char *argv[] )
{
    inputData* data = (inputData*)malloc(sizeof(inputData) * NUMBEROFTEST);
    readFile(data);
    for(int i=0; i<NUMBEROFTEST; i++){
        printf("%ld\n", data[i].in1);
        t_run_test(&data[i]);
   }

    return 1;
}



/*
*    Function :  WriteOut
*
*    Outputs results to the RAM file so that it can be downloaded to host for
*  verification.  Also serves to defeat optimization which would remove the
*  code used to develop the results when not in DEBUG mode.
*
*/    

void WriteOut(varsize value,varsize* output)
{
     /* update the output struct */
    *output = value;
   // printf("VALUE %ld ", value );

} /* End of function 'WriteOut' */


void writeToInputFile(varsize in1,
                      varsize pulseDeltaTime1,
                varsize angle1,
                 varsize angleCounterLast1,
                 varsize toothCount1,
                 varsize deltaTimeAccum1,
                 varsize deltaTimeAvg1,
                 varsize firingTime1,
                 varsize tdcTime1,
                 unsigned long engineSpeed1,
                 unsigned long rotationTime1){
    FILE *fp;
    fp = fopen("inputFile.txt", "a");
    if (fp == NULL){
        printf("Problem in a file");
        return;
    }
    fprintf(fp,"a ");
    fprintf(fp,"%ld", in1);

    fprintf(fp," %ld", pulseDeltaTime1);

    fprintf(fp," %ld", angle1);

    fprintf(fp," %ld", angleCounterLast1);

    fprintf(fp," %ld", toothCount1);

    fprintf(fp," %ld", deltaTimeAccum1);

    fprintf(fp," %ld", deltaTimeAvg1);

    fprintf(fp," %ld", firingTime1);

    fprintf(fp," %ld", tdcTime1);

    fprintf(fp," %ld", engineSpeed1);

    fprintf(fp," %ld", rotationTime1);

    fputs("\n",fp);
    fclose(fp);
}
