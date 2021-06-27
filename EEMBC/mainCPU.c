#define ALGO_GLOBALS    1   /* Next time, we'll skip these */
//#include "algo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define BILLION  1000000000.0;
typedef short varsize; 
/* Estimate of allocation for NUM_TESTS*( debug test + 2 variables )*/
#define T_BSIZE (MAX_FILESIZE+((NUM_TESTS+1)*VAR_COUNT*4))

//int t_run_test( size_t iterations, int argc, const char *argv[] ) ;
//int test_main( struct TCDef **tcdef, int argc, const char *argv[] ) ;

/* Define iterations */
int NUMBEROFTEST = 1024;//7168;
#define NUM_POINTS   512
#define false    0
#define true    !false

/******* a2time **********/

#define CYLINDERS       8       /* We're simulating an eight cylinder engine */
#define TENTH_DEGREES   3600    /* Number of 1/10-degrees in a circle */

/* Cylinder #1 firing angle (*10) */
#define FIRE1_ANGLE (TENTH_DEGREES/CYLINDERS*1)
/* Cylinder #2 firing angle (*10) */
#define FIRE2_ANGLE (TENTH_DEGREES/CYLINDERS*2)
/* Cylinder #3 firing angle (*10) */
#define FIRE3_ANGLE (TENTH_DEGREES/CYLINDERS*3)   
/* Cylinder #4 firing angle (*10) */
#define FIRE4_ANGLE (TENTH_DEGREES/CYLINDERS*4)  
/* Cylinder #5 firing angle (*10) */
#define FIRE5_ANGLE (TENTH_DEGREES/CYLINDERS*5)   
/* Cylinder #6 firing angle (*10) */
#define FIRE6_ANGLE (TENTH_DEGREES/CYLINDERS*6)   
/* Cylinder #7 firing angle (*10) */
#define FIRE7_ANGLE (TENTH_DEGREES/CYLINDERS*7)   
/* Cylinder #8 firing angle (*10) */
#define FIRE8_ANGLE (TENTH_DEGREES/CYLINDERS*8)   

#define CYL1            1       /* Cylinder #1 firing window */
#define CYL2            2       /* Cylinder #2 firing window */
#define CYL3            3       /* Cylinder #3 firing window */
#define CYL4            4       /* Cylinder #4 firing window */
#define CYL5            5       /* Cylinder #5 firing window */
#define CYL6            6       /* Cylinder #6 firing window */
#define CYL7            7       /* Cylinder #7 firing window */
#define CYL8            8       /* Cylinder #8 firing window */

#define TDC_TEETH       2       /* Number of missing teeth (=1) at TDC */
#define TDC_MARGIN      0.9     /* Discrimination window for TDC teeth */
#define NUM_TEETH       60      /* Number of teeth on tonewheel */

/* Arbitrary scale factor for computing internal RPM */
#define RPM_SCALE_FACTOR        3600000 



 varsize tonewheelTeeth =60;
#define MIN_TOOTH_TIME      100   
/* Maximum inter-pulse period permitted( zero road-speed )*/
#define MAX_TOOTH_TIME  10000
#define MAX_VARIABLE 0x7FFF
#define SPEEDO_SCALE_FACTOR 36000

/***** AIFFTR01 *********/
#define STAGE_SCALE_FACTOR      1
#define BUTTERFLY_SCALE_FACTOR  15
#define PI 3.141592654 
#define TRIG_SCALE_FACTOR       32768
#define FFT_LENGTH   9

/***** IDctrn ******/
#define ROWS         8     /* Perform 8x8 block compression */
#define COLS         8

/* Integer table of cosines is scaled from float by this */
#define COS_SCALE_FACTOR    4096.0
/* Scaling expressed as exponent 2**COS_SCALE_FACTOR */
#define COS_SCALE_EXP      12

typedef struct{
    varsize in1;
    varsize pulseDeltaTime1 ;
    varsize angle1 ;
    varsize angleCounterLast1 ;
    varsize toothCount1 ;
    varsize deltaTimeAccum1 ;
    varsize deltaTimeAvg1;
    varsize firingTime1 ;
    unsigned long tdcTime1 ;
    unsigned long engineSpeed1  ;
    unsigned long rotationTime1  ;
    unsigned char inChar[ROWS + COLS];
    varsize commandPos;
    int upDirection1;
    int lastDirection1;
    int incrementA1;
    int incrementB1;
    int endPhaseA1;
    int dirPhaseA1;
    int endPhaseB1;
    int dirPhaseB1;
    varsize internalPos1;
    int pwmCounter1;
    int pwmPhaseA1;
    int pwmPhaseB1;
} inputData;
typedef struct{
    varsize result1[NUM_POINTS];
    varsize result2[NUM_POINTS];
    int outendPhaseA1;
    int outdirPhaseA1;
    int outendPhaseB1;
    int outdirPhaseB1;
    varsize out1;
    varsize out2;
    char choice;
    signed char f_1[ROWS][COLS];
}outputData;

 void WriteOut(varsize value,varsize* output);

 void a2time(varsize in1,varsize pulseDeltaTime1, 
                varsize angle1, 
                varsize angleCounterLast1,
                varsize toothCount1, 
                varsize deltaTimeAccum1,
                varsize deltaTimeAvg1, 
                varsize firingTime1, 
                varsize tdcTime1, 
                unsigned long engineSpeed1,
                unsigned long rotationTime1,
                varsize *outengineSpeed1,
                varsize *outfiringTime1){

    varsize window ;


	varsize angleCounter	= in1;   /* Current 'angleCounter' pulled from  data */
    varsize tonewheelTeeth	= NUM_TEETH; /* Number of teeth on the tonewheel */


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
            //isTopDeadCenter1 = true ;
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
         //   isTopDeadCenter1 = false ;
        }

        WriteOut(engineSpeed1, outengineSpeed1) ;

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
        WriteOut(firingTime1, outfiringTime1 );

}

 void rdspeed(varsize tonewheelCounter1, varsize toothDeltaTime1, varsize toothDeltaTimeLast1, varsize tonewheelCounterLast1, long toothTimeAccum1, varsize toothCount1, varsize *roadSpeed1){
toothDeltaTime1 = (varsize)
            ( tonewheelCounter1 - tonewheelCounterLast1 ) ;
        /* Check for timer overflow */
        if( tonewheelCounterLast1 > tonewheelCounter1 )
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
        tonewheelCounterLast1 = tonewheelCounter1 ;
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
            if( toothTimeAccum1 >  MAX_TOOTH_TIME *tonewheelTeeth / 2 )   
            {    
                /* ...check for zero road speed */
                *roadSpeed1 = 0 ;
            }
            else
            {
                /* ...or compute road speed */
                *roadSpeed1 = (varsize ) ( SPEEDO_SCALE_FACTOR  /
                      ( toothTimeAccum1 / tonewheelTeeth * 2 ) ) ;
 		toothCount1 = 0 ;
                /* ...and clear the accumulator */
                toothTimeAccum1 = 0 ;
            }
        }
}

 void aifftr01(varsize realData_1[NUM_POINTS], varsize imagData_1[NUM_POINTS])    /* Points to imaginary part of data */
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





        for( i_1 = 0 ; i_1 < NUM_POINTS ; i_1++ )
        {        
            realBitRevData_1[i_1] = realData_1[bitRevInd[i_1]] ; 
            imagBitRevData_1[i_1] = imagData_1[bitRevInd[i_1]] ; 
        }

        for( i_1 = 0 ; i_1 < NUM_POINTS ; i_1++ )
        {        
            realData_1[i_1] = realBitRevData_1[i_1] ; 
            imagData_1[i_1] = imagBitRevData_1[i_1] ; 
        }

        for( passCount_1 = 0, k_1 = 1 ; k_1 <= FFT_LENGTH ; k_1++, passCount_1++ )
        {        
            n1_1 = 1 << k_1 ; 
            n2_1 = n1_1 >> 1 ; 
            argIndex_1 = 0 ; 
            deltaIndex_1 = ( NUM_POINTS / 2 ) / n2_1 ; 

            for( j_1 = 0 ; j_1 < n2_1 ; j_1++, passCount_1++ )
            {        
                wReal_1 = cosineV[argIndex_1] ; 
                wImag_1 = sineV[argIndex_1] ; 

                for( i_1 = j_1 ; i_1 < NUM_POINTS ; i_1 += n1_1, passCount_1++ )
                {        
                    l_1 = i_1 + n2_1 ; 
                    realLow_1 = &realData_1[l_1] ; 
                    imagLow_1 = &imagData_1[l_1] ; 
                    realHi_1 = &realData_1[i_1] ; 
                    imagHi_1 = &imagData_1[i_1] ; 

                    *realLow_1 >>= STAGE_SCALE_FACTOR ; 
                    *imagLow_1 >>= STAGE_SCALE_FACTOR ; 
                    *realHi_1 >>= STAGE_SCALE_FACTOR ; 
                    *imagHi_1 >>= STAGE_SCALE_FACTOR ; 

                    tRealData_1 = *realLow_1 * wReal_1 - *imagLow_1 * wImag_1 ; 
                    tImagData_1 = *imagLow_1 * wReal_1 + *realLow_1 * wImag_1 ; 

                    tRealData_1 >>= BUTTERFLY_SCALE_FACTOR ; 
                    tImagData_1 >>= BUTTERFLY_SCALE_FACTOR ; 

                    realData_1[l_1] = *realHi_1 - tRealData_1 ; 
                    imagData_1[l_1] = *imagHi_1 - tImagData_1 ; 
                    realData_1[i_1] += tRealData_1 ; 
                    imagData_1[i_1] += tImagData_1 ; 
                }
                argIndex_1 += deltaIndex_1 ; 
            }

        } 

        for( i_1 = 0 ; i_1 < NUM_POINTS ; i_1++ )
        {        
            realData_1[i_1] *= realData_1[i_1] ;
            realData_1[i_1] += imagData_1[i_1] * imagData_1[i_1] ; 
        }
} 

 void aiifft01( varsize realData_1[NUM_POINTS], varsize imagData_1[NUM_POINTS])
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

 short unPack( unsigned char c )
{        
    /* Only want lower four bit nibble */
    c = c & (unsigned char)0x0F ;  
    
    if( c > 7 ) {
        /* Negative nibble */
        return( ( short )( c - 16 ) ) ;
    }
    else
    {
        /* positive nibble */
        return( ( short )c ) ;       
    }
}

 void idctrno1(unsigned char inChar[ROWS + COLS],signed char f_1[ROWS][COLS])
{
    long cosMatrixA[ROWS][COLS] ;
    long cosMatrixB[ROWS][COLS] ;
    double cosine ;
    double cosMultA ;
    double cosMultB ;
    long F_1[ROWS][COLS] ;
     long G_1[ROWS][COLS] ;
     varsize u_1 ;
     varsize v_1 ;
     varsize i_1 ;
     varsize j_1 ;
     varsize k_1 ;

    /* Build cosine matrix */    
    cosMultA = 2.0 * atan( 1.0 ) / (double)ROWS ; 

    for( u_1 = 0 ; u_1 < ROWS ; u_1++ )
    {        
        cosMultB = u_1 *cosMultA ; 

        for( v_1 = 0 ; v_1 < COLS ; v_1++ )
        {        
            if( u_1 > 0 )
            {
                cosine = (double)( 2.0 * cos( ( 2 * v_1 + 1 ) * cosMultB ) ) ; 
            }
            else
            {
                cosine = (double)( cos( ( 2 * v_1 + 1 ) * cosMultB ) ) ; 
            }
            cosMatrixA[u_1][v_1] = (long)( cosine * COS_SCALE_FACTOR ) ; 
            cosMatrixB[v_1][u_1] = cosMatrixA[u_1][v_1] ; 
        }
    }


        for( i_1 = 0 ; i_1 < ROWS ; i_1++ )
        {        
            for( j_1 = 0 ; j_1 < COLS ; j_1++ )
            {        
                f_1[i_1][j_1] = 0 ; 
            }
        }

        f_1[0][0] = (signed char)inChar[0] ; 
        f_1[0][1] = (signed char)inChar[1] ; 
        f_1[0][2] = 3 * unPack( (unsigned char)( inChar[2] >> 4 ) ) ; 
        f_1[0][3] = 3 * unPack( inChar[2] ) ; 
        f_1[0][4] = 2 * unPack( (unsigned char)( inChar[3] >> 4 ) ) ; 
        f_1[0][5] = 2 * unPack( inChar[3] ) ; 
        f_1[0][6] = (signed char) unPack( (unsigned char)( inChar[4] >> 4 ) ) ; 
        f_1[0][7] = (signed char) unPack( inChar[4] ) ; 

        f_1[1][0] = (signed char)inChar[5] ; 
        f_1[1][1] = (signed char)inChar[6] ; 
        f_1[1][2] = 2 * unPack( (unsigned char)( inChar[7] >> 4 ) ) ; 
        f_1[1][3] = (signed char) unPack( inChar[7] ) ; 
        f_1[1][4] = (signed char) unPack( (unsigned char)( inChar[8] >> 4 ) ) ; 
        f_1[1][5] = (signed char) unPack( inChar[8] ) ; 

        f_1[2][0] = 3 * unPack( (unsigned char)( inChar[9] >> 4 ) ) ; 
        f_1[2][1] = 2 * unPack( inChar[9] ) ; 
        f_1[2][2] = 2 * unPack( (unsigned char)( inChar[10] >> 4 ) ) ; 
        f_1[2][3] = (signed char) unPack( inChar[10] ) ; 

        f_1[3][0] = 3 * unPack( (unsigned char)( inChar[11] >> 4 ) ) ; 
        f_1[3][1] = (signed char) unPack( inChar[11] ) ; 
        f_1[3][2] = (signed char) unPack( (unsigned char)( inChar[12] >> 4 ) ) ; 
        f_1[3][3] = (signed char) unPack( inChar[12] ) ; 

        f_1[4][0] = 2 * unPack( (unsigned char)( inChar[13] >> 4 ) ) ; 
        f_1[4][1] = (signed char) unPack( inChar[13] ) ; 

        f_1[5][0] = 2 * unPack( (unsigned char)( inChar[14] >> 4 ) ) ; 
        f_1[5][1] = (signed char) unPack( inChar[14] ) ; 

        f_1[6][0] = (signed char) unPack( (unsigned char)( inChar[15] >> 4 ) ) ; 

        f_1[7][0] = (signed char) unPack( inChar[15] ) ; 

       for( i_1 = 0 ; i_1 < ROWS ; i_1++ )
        {        
            for( j_1 = 0 ; j_1 < COLS ; j_1++ )
            {        
                F_1[i_1][j_1] = 0 ; 
                G_1[i_1][j_1] = 0 ; 
            }
        }

        for( k_1 = 0 ; k_1 < COLS ; k_1++ )
        {        
            for( i_1 = 0 ; i_1 < ROWS ; i_1++ )
            {        
                for( j_1 = 0 ; j_1 < COLS ; j_1++ )
                {
                    F_1[i_1][j_1] += f_1[i_1][k_1] * cosMatrixA[k_1][j_1] ; 
                }
            }
        }


        for( k_1 = 0 ; k_1 < COLS ; k_1++ )
        {        
            for( i_1 = 0 ; i_1 < ROWS ; i_1++ )
            {        
                for( j_1 = 0 ; j_1 < COLS ; j_1++ )
                {
                    G_1[i_1][j_1] += cosMatrixB[i_1][k_1] * F_1[k_1][j_1] ; 
                }
            }
        }


        for( u_1 = 0 ; u_1 < ROWS ; u_1++ )
        {        
            for( v_1 = 0 ; v_1 < COLS ; v_1++ )
            {        
                G_1[u_1][v_1] += 1 <<( ( COS_SCALE_EXP * 2 ) - 1 ) ; 
	 	f_1[u_1][v_1] = (signed char) (( G_1[u_1][v_1] ) >> COS_SCALE_EXP * 2 ) ; 
            }
        }

} 

#define MAX_PHASE       20          /* Maximum duty cycle, per 'pwmCounter' */
#define MAX_COUNT       MAX_PHASE+1 /* Overflow of duty cycle counter */
#define MID_PHASE       MAX_PHASE/2 /* 50% duty cycle */

 void puwmod01(varsize commandPos, int upDirection1,
 int lastDirection1,
 int enbPhaseA1,
 int dirPhaseA1,
 int enbPhaseB1,
 int dirPhaseB1,
 int incrementA1,
 int incrementB1,
 varsize internalPos1,
 int pwmCounter1,
 int pwmPhaseA1,
 int pwmPhaseB1, int *outenbPhaseA1,
 int *outdirPhaseA1,
 int *outenbPhaseB1,
 int *outdirPhaseB1)
{

    pwmCounter1++ ;                 /* Bump the PWM phase counter */

    if( pwmCounter1 == MAX_COUNT )  /* Counter overflowed ? */
    {
        pwmCounter1 = 0 ;           /* Yes, reset the counter */
    }


    if( ( pwmCounter1 == pwmPhaseA1 ) &&    /* Reached end of phase A */
    ( pwmPhaseA1 < MAX_PHASE ) )        /*  and not 100% DC ? */
    {
        enbPhaseA1 = 0 ;    /* Yes, turn phase A off now */
    }
    if( ( pwmCounter1 == pwmPhaseB1 ) &&    /* Reached end of phase B */
    ( pwmPhaseB1 < MAX_PHASE ) )        /*  and not 100% DC ? */
    {
        enbPhaseB1 = 0 ;    /* Yes, turn phase B off now */
    }

    if( pwmCounter1 == 0 ) /* Sync with pwm counter rollover */
    {

        /* Are we commanded to move 'up'? */
        if( commandPos > internalPos1 )
        {
        /* Yes, remember that */
        upDirection1 = true ;
        }

        /* Are we commanded to move 'down' ? */
        if( commandPos < internalPos1 )
        {
        /* Yes, remember that */
        upDirection1 = false ;
        }

        if( upDirection1 != lastDirection1 )
        {
        /* Change in direction ? */
        incrementA1 = !incrementA1 ;
        /* ...then, flip the duty-cycle bits */
        incrementB1 = !incrementB1 ;
        }

        /* Remember current direction for next pass */
        lastDirection1 = upDirection1 ;

        /* Are we commanded to move ? */
        if( commandPos != internalPos1 )
        {
        /* Yes, so micro-step per the duty-cycle bits */
        if( incrementA1 )
        {
        pwmPhaseA1++ ;
        }
        else
        {
        pwmPhaseA1-- ;
        }

        if( ( pwmPhaseA1 == MAX_COUNT ) && incrementA1 )
        {
        pwmPhaseA1 = MAX_PHASE - 1 ;
        incrementA1 = false ;
        }

        if( ( pwmPhaseA1 < 0 ) && !incrementA1 )
        {
        pwmPhaseA1 = 1 ;
        incrementA1 = true ;
        }

        if( incrementB1 )
        {
        pwmPhaseB1++ ;
        }
        else
        {
        pwmPhaseB1-- ;
        }

        if( ( pwmPhaseB1 == MAX_COUNT ) && incrementB1 )
        {
        pwmPhaseB1 = MAX_PHASE - 1 ;
        incrementB1 = false ;
        }

        if( ( pwmPhaseB1 < 0 ) && !incrementB1 )
        {
        pwmPhaseB1 = 1 ;
        incrementB1 = true ;
        }

        /* If we reach the mid-point between major motor step
        * positions, then we must flip the coil driver polarity
        *
        */
        if( pwmPhaseA1 == 0 )
        {
            if( dirPhaseA1 == 1 )
            {
                dirPhaseA1 = 0 ;
            }
            else
            {
                dirPhaseA1 = 1 ;
            }
        }

        if( pwmPhaseB1 == 0 )
        {
            if( dirPhaseB1 == 1 )
            {
                dirPhaseB1 = 0 ;
            }
            else
            {
                dirPhaseB1 = 1 ;
            }
        }


        if( upDirection1 )
        {
            internalPos1++ ;
        }
        else
        {
            internalPos1-- ;
        }
        } /* End of 'commandPos != internalPos' */

        if( pwmPhaseA1 > 0 )   /* If >0% DC, turn A on again */
        {
            enbPhaseA1 = 1 ;
        }
        if( pwmPhaseB1 > 0 )   /* And if >0% DC, turn B on again */
        {
            enbPhaseB1 = 1 ;
        }
    }

    *outdirPhaseA1 = dirPhaseA1 ;
    *outenbPhaseA1 = enbPhaseA1;
    *outdirPhaseB1 = dirPhaseB1;
    *outenbPhaseB1 = enbPhaseB1 ;

}
#define NUM_X_ENTRIES   50      /* Number of entries on each axis of the */
#define NUM_Y_ENTRIES   50      /* ...2D table */

 const varsize engLoadROM[] =
{
0, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140,
150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260,
270, 280, 290, 300, 310, 320, 330, 340, 350, 360, 370, 380,
390, 400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 500
} ;

 const varsize engSpeedROM[] =
{
0, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200,
1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200,
2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200,
3300, 3400, 3500, 3600, 3700, 3800, 3900, 4000, 4100, 4200,
4300, 4400, 4500, 4600, 4700, 4800, 4900, 5000
} ;

 const varsize angleTableROM[] =
{
10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 70, 80, 90, 100, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 100, 90, 80, 70, 60, 50, 40, 39, 38, 37, 36, 35, 35, 35, 35, 35, 35, 60,
45, 50, 50, 55, 55, 56, 56, 56, 56, 56, 56, 50, 50, 50, 50, 50, 50, 50, 60, 70, 80, 90, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 103, 90, 80, 72, 66, 60, 52, 44, 38, 32, 28, 27, 35, 35, 35, 35, 35, 60,
30, 40, 40, 50, 54, 54, 54, 54, 54, 54, 54, 40, 40, 40, 40, 40, 40, 40, 50, 60, 70, 86, 90, 91, 92, 91, 90, 89, 89, 90, 92, 94, 94, 91, 74, 64, 63, 62, 54, 46, 40, 34, 29, 28, 35, 35, 35, 35, 35, 60,
15, 30, 30, 40, 50, 51, 51, 51, 51, 51, 51, 30, 30, 40, 50, 60, 70, 76, 80, 86, 90, 94, 98, 99, 100, 99, 98, 97, 97, 98, 100, 102, 102, 92, 82, 72, 70, 64, 56, 48, 42, 36, 30, 29, 35, 35, 35, 35, 35, 60,
10, 20, 20, 30, 40, 50, 50, 50, 50, 50, 50, 56, 62, 68, 74, 80, 84, 88, 92, 96, 100, 104, 108, 109, 110, 109, 108, 107, 107, 108, 110, 112, 112, 102, 92, 82, 72, 67, 59, 51, 47, 43, 41, 39, 37, 37, 37, 37, 37, 60,
10, 20, 20, 30, 40, 50, 50, 50, 50, 50, 50, 56, 62, 68, 74, 80, 86, 92, 98, 102, 106, 110, 114, 115, 116, 115, 114, 113, 113, 114, 116, 118, 118, 108, 98, 88, 80, 70, 62, 54, 49, 45, 43, 41, 39, 39, 39, 39, 39, 100,
12, 20, 20, 30, 40, 50, 50, 50, 50, 50, 50, 56, 62, 68, 74, 80, 86, 92, 98, 104, 108, 112, 116, 117, 118, 117, 116, 115, 115, 116, 118, 120, 120, 110, 100, 90, 80, 72, 64, 56, 52, 48, 46, 44, 42, 42, 42, 42, 42, 100,
15, 20, 20, 30, 40, 50, 50, 50, 50, 50, 50, 56, 62, 68, 74, 80, 86, 92, 98, 104, 108, 112, 116, 117, 118, 117, 116, 115, 115, 116, 118, 120, 120, 110, 100, 90, 78, 75, 67, 59, 54, 49, 47, 45, 43, 43, 43, 43, 43, 100,
20, 20, 20, 30, 40, 50, 50, 50, 50, 50, 50, 56, 62, 68, 74, 80, 86, 92, 98, 103, 107, 111, 115, 116, 117, 116, 115, 114, 114, 115, 117, 119, 119, 109, 99, 88, 78, 75, 67, 59, 54, 49, 47, 45, 43, 43, 43, 43, 43, 100,
22, 22, 22, 32, 42, 52, 52, 52, 52, 52, 52, 58, 64, 70, 76, 84, 90, 96, 102, 102, 106, 110, 114, 115, 116, 115, 114, 113, 113, 114, 116, 118, 118, 108, 98, 88, 78, 75, 70, 59, 54, 49, 47, 45, 43, 43, 43, 43, 43, 100,
24, 24, 24, 34, 44, 54, 54, 54, 54, 54, 54, 60, 66, 72, 78, 84, 90, 96, 102, 104, 108, 112, 116, 117, 118, 117, 116, 115, 115, 116, 118, 120, 120, 110, 100, 86, 86, 78, 75, 67, 59, 54, 49, 47, 44, 44, 44, 44, 44, 100,
30, 30, 30, 40, 50, 60, 60, 60, 60, 60, 60, 66, 72, 78, 84, 90, 96, 102, 108, 112, 116, 120, 124, 125, 126, 125, 124, 123, 123, 124, 124, 122, 120, 118, 108, 88, 88, 78, 75, 67, 59, 54, 49, 47, 44, 44, 44, 44, 44, 100,
30, 30, 30, 40, 50, 60, 60, 60, 60, 60, 60, 66, 72, 78, 84, 90, 96, 102, 116, 120, 124, 128, 132, 133, 134, 133, 132, 131, 131, 132, 130, 127, 124, 121, 116, 92, 92, 76, 68, 60, 56, 52, 50, 48, 46, 46, 46, 46, 46, 100,
30, 30, 30, 40, 50, 60, 60, 60, 60, 60, 60, 66, 72, 78, 84, 90, 96, 104, 118, 122, 126, 130, 134, 135, 136, 135, 134, 133, 133, 133, 131, 128, 107, 106, 104, 92, 92, 76, 68, 60, 56, 52, 50, 48, 46, 46, 46, 46, 46, 100,
31, 31, 31, 41, 51, 61, 61, 61, 61, 61, 61, 67, 73, 79, 85, 91, 97, 103, 120, 124, 128, 132, 136, 137, 138, 137, 136, 135, 134, 134, 132, 129, 107, 106, 104, 92, 92, 76, 68, 60, 56, 52, 50, 48, 46, 46, 46, 46, 46, 100,
33, 33, 33, 43, 53, 63, 63, 63, 63, 63, 63, 69, 75, 81, 87, 93, 99, 105, 122, 126, 130, 134, 138, 139, 140, 139, 138, 137, 135, 135, 133, 130, 108, 107, 104, 94, 94, 77, 72, 66, 60, 72, 75, 70, 66, 66, 66, 66, 66, 100,
35, 35, 35, 45, 55, 65, 65, 65, 65, 65, 65, 71, 77, 83, 88, 96, 100, 107, 124, 128, 132, 136, 140, 141, 142, 141, 140, 139, 136, 136, 134, 131, 108, 107, 105, 94, 94, 77, 76, 72, 70, 92, 100, 105, 86, 86, 86, 86, 86, 100,
35, 35, 35, 45, 55, 65, 65, 65, 65, 65, 65, 67, 69, 71, 77, 83, 89, 95, 126, 130, 134, 138, 142, 143, 144, 143, 142, 141, 137, 137, 135, 132, 109, 108, 107, 106, 105, 105, 104, 108, 112, 116, 120, 120, 106, 106, 106, 106, 106, 100,
35, 35, 35, 45, 55, 65, 65, 65, 65, 65, 65, 65, 65, 65, 71, 81, 91, 101, 127, 131, 135, 139, 143, 144, 145, 144, 144, 142, 138, 138, 136, 133, 131, 127, 125, 122, 120, 125, 130, 135, 140, 145, 140, 108, 116, 116, 116, 116, 116, 100,
38, 38, 38, 48, 58, 68, 68, 68, 68, 68, 68, 68, 68, 68, 74, 84, 94, 104, 128, 132, 136, 140, 143, 145, 146, 145, 145, 143, 139, 139, 137, 134, 130, 126, 124, 126, 130, 135, 140, 145, 150, 155, 150, 140, 120, 120, 120, 120, 120, 100,
41, 41, 41, 51, 61, 71, 71, 71, 71, 71, 71, 71, 71, 71, 77, 87, 97, 107, 129, 133, 137, 141, 143, 146, 147, 146, 146, 144, 140, 140, 138, 135, 129, 125, 123, 122, 124, 129, 134, 139, 144, 149, 139, 138, 122, 122, 122, 122, 122, 100,
44, 44, 44, 54, 64, 74, 74, 74, 74, 74, 74, 74, 74, 74, 80, 90, 100, 110, 130, 134, 138, 142, 144, 147, 148, 147, 147, 145, 141, 141, 139, 134, 128, 124, 122, 122, 122, 127, 132, 137, 142, 147, 137, 136, 124, 124, 124, 124, 124, 100,
47, 47, 47, 57, 67, 77, 77, 77, 77, 77, 77, 77, 77, 77, 87, 97, 107, 117, 131, 135, 139, 143, 144, 148, 149, 148, 148, 146, 142, 143, 140, 133, 127, 123, 121, 120, 121, 126, 131, 136, 141, 146, 136, 134, 126, 126, 126, 126, 126, 100,
45, 45, 45, 55, 65, 75, 75, 75, 75, 75, 75, 75, 78, 88, 98, 108, 118, 128, 138, 142, 144, 144, 144, 149, 150, 149, 149, 145, 143, 145, 141, 132, 126, 122, 120, 119, 120, 125, 130, 135, 140, 145, 135, 132, 130, 130, 130, 130, 130, 100,
43, 43, 43, 53, 63, 73, 73, 73, 73, 73, 73, 76, 79, 89, 109, 108, 118, 128, 138, 142, 144, 144, 144, 149, 150, 149, 149, 145, 143, 153, 142, 131, 125, 121, 120, 119, 118, 117, 116, 115, 114, 144, 139, 134, 136, 136, 136, 136, 136, 100,
42, 42, 42, 52, 62, 72, 72, 72, 72, 72, 72, 75, 78, 88, 98, 108, 118, 128, 138, 142, 144, 144, 144, 142, 142, 138, 148, 143, 144, 142, 142, 130, 124, 124, 125, 125, 124, 123, 123, 123, 128, 143, 133, 128, 142, 142, 142, 142, 142, 100,
41, 41, 41, 51, 61, 71, 71, 71, 71, 71, 71, 74, 77, 87, 97, 107, 117, 127, 137, 141, 143, 143, 143, 141, 141, 137, 146, 142, 133, 141, 141, 129, 123, 125, 130, 129, 128, 127, 127, 132, 137, 142, 132, 126, 148, 148, 148, 148, 148, 100,
40, 40, 40, 50, 60, 70, 70, 70, 70, 70, 70, 73, 76, 86, 96, 106, 116, 126, 136, 140, 142, 142, 142, 140, 140, 136, 142, 141, 136, 140, 140, 139, 137, 135, 133, 131, 130, 129, 128, 132, 137, 142, 131, 125, 142, 142, 142, 142, 142, 100,
46, 46, 46, 56, 66, 76, 76, 76, 76, 76, 76, 84, 92, 100, 108, 116, 124, 132, 140, 144, 146, 146, 146, 144, 144, 140, 140, 140, 140, 144, 140, 139, 137, 135, 133, 131, 130, 129, 128, 127, 126, 141, 131, 124, 136, 136, 136, 136, 136, 100,
50, 50, 50, 60, 70, 80, 80, 80, 80, 80, 80, 88, 96, 104, 112, 120, 128, 136, 144, 148, 150, 150, 150, 148, 148, 144, 138, 139, 144, 148, 144, 143, 141, 139, 137, 135, 134, 133, 132, 131, 130, 141, 130, 123, 130, 130, 130, 130, 130, 100,
54, 54, 54, 64, 74, 84, 84, 84, 84, 84, 84, 92, 100, 108, 116, 124, 132, 140, 148, 152, 154, 154, 154, 152, 152, 148, 136, 140, 148, 152, 148, 147, 145, 143, 141, 139, 138, 137, 136, 135, 134, 140, 130, 122, 126, 126, 126, 126, 126, 100,
58, 58, 58, 68, 78, 88, 88, 88, 88, 88, 88, 96, 104, 112, 120, 128, 136, 144, 152, 156, 158, 158, 158, 156, 156, 152, 136, 144, 152, 156, 152, 151, 149, 147, 145, 143, 142, 141, 140, 139, 138, 134, 130, 121, 124, 124, 124, 124, 124, 100,
62, 62, 62, 72, 82, 92, 92, 92, 92, 92, 92, 100, 108, 116, 124, 132, 140, 148, 156, 160, 162, 162, 162, 160, 160, 156, 140, 148, 156, 160, 156, 155, 153, 151, 149, 147, 146, 145, 144, 143, 142, 133, 129, 120, 122, 122, 122, 122, 122, 100,
62, 62, 62, 72, 82, 92, 92, 92, 92, 92, 92, 100, 108, 116, 124, 132, 140, 148, 156, 160, 162, 162, 162, 160, 160, 156, 140, 148, 156, 160, 156, 155, 153, 151, 149, 147, 146, 145, 144, 143, 142, 132, 129, 128, 120, 120, 120, 120, 120, 100,
62, 62, 62, 72, 82, 92, 92, 92, 92, 92, 92, 100, 108, 116, 124, 132, 140, 148, 156, 160, 162, 162, 162, 160, 160, 156, 140, 148, 156, 160, 156, 155, 153, 151, 149, 147, 146, 145, 144, 143, 142, 131, 130, 129, 123, 123, 123, 123, 123, 100,
62, 62, 62, 72, 82, 92, 92, 92, 92, 92, 92, 100, 108, 116, 124, 132, 140, 148, 156, 160, 162, 162, 162, 160, 160, 156, 140, 148, 156, 160, 156, 155, 153, 151, 149, 147, 146, 145, 144, 143, 142, 130, 132, 131, 126, 126, 126, 126, 126, 100,
62, 62, 62, 72, 82, 92, 92, 92, 92, 92, 92, 100, 108, 116, 124, 132, 140, 148, 156, 160, 162, 162, 162, 160, 160, 156, 140, 148, 156, 160, 156, 155, 153, 151, 149, 147, 146, 145, 144, 143, 142, 141, 134, 133, 130, 130, 130, 130, 130, 100,
62, 62, 62, 72, 82, 92, 92, 92, 92, 92, 92, 100, 108, 116, 124, 132, 140, 148, 156, 160, 162, 162, 162, 160, 160, 156, 140, 148, 156, 160, 156, 155, 153, 151, 149, 147, 146, 145, 144, 143, 142, 141, 136, 135, 130, 130, 130, 130, 130, 100,
62, 62, 62, 72, 82, 92, 92, 92, 92, 92, 92, 100, 108, 116, 124, 132, 140, 148, 156, 160, 162, 162, 162, 160, 160, 156, 140, 148, 156, 160, 156, 155, 153, 151, 149, 147, 146, 145, 144, 143, 142, 141, 138, 137, 130, 130, 130, 130, 130, 100,
62, 62, 62, 72, 82, 92, 92, 92, 92, 92, 92, 100, 108, 116, 124, 132, 140, 148, 156, 160, 162, 162, 162, 160, 160, 156, 140, 148, 156, 160, 156, 155, 153, 151, 149, 147, 146, 145, 144, 143, 142, 141, 140, 139, 130, 130, 130, 130, 130, 100,
62, 62, 62, 72, 82, 92, 92, 92, 92, 92, 92, 100, 108, 116, 124, 132, 140, 148, 156, 160, 162, 162, 162, 160, 160, 156, 140, 148, 156, 160, 156, 155, 153, 151, 149, 147, 146, 145, 144, 143, 142, 141, 140, 139, 130, 130, 130, 130, 130, 100,
62, 62, 62, 72, 82, 92, 92, 92, 92, 92, 92, 100, 108, 116, 124, 132, 140, 148, 156, 160, 162, 162, 162, 160, 160, 156, 140, 148, 156, 160, 156, 155, 153, 151, 149, 147, 146, 145, 144, 143, 142, 141, 140, 139, 130, 130, 130, 130, 130, 100,
62, 62, 62, 72, 82, 92, 92, 92, 92, 92, 92, 100, 108, 116, 124, 132, 140, 148, 156, 160, 162, 162, 162, 160, 160, 156, 140, 148, 156, 160, 156, 155, 153, 151, 149, 147, 146, 145, 144, 143, 142, 141, 140, 139, 130, 130, 130, 130, 130, 100,
62, 62, 62, 72, 82, 92, 92, 92, 92, 92, 92, 100, 108, 116, 124, 132, 140, 148, 156, 160, 162, 162, 162, 160, 160, 156, 140, 148, 156, 160, 156, 155, 153, 151, 149, 147, 146, 145, 144, 143, 142, 141, 140, 139, 130, 130, 130, 130, 130, 100,
62, 62, 62, 72, 82, 92, 92, 92, 92, 92, 92, 100, 108, 116, 124, 132, 140, 148, 156, 160, 162, 162, 162, 160, 160, 156, 140, 148, 156, 160, 156, 155, 153, 151, 149, 147, 146, 145, 144, 143, 142, 141, 140, 139, 130, 130, 130, 130, 130, 100,
62, 62, 62, 72, 82, 92, 92, 92, 92, 92, 92, 100, 108, 116, 124, 132, 140, 148, 156, 160, 162, 162, 162, 160, 160, 156, 140, 148, 156, 160, 156, 155, 153, 151, 149, 147, 146, 145, 144, 143, 142, 141, 140, 139, 130, 130, 130, 130, 130, 100
} ;

 void tblook01(varsize loadValue, varsize speedValue, varsize *outResult )
{

    varsize i1, j1;    /* Local indices and counters */
     varsize outAngleValue1 ;     /* 'Angle' pulled from map */
     float engSpeedDelta1 ;       /* Intermediate ratios from grid */
     float engLoadDelta1 ;

    varsize numXEntries = NUM_X_ENTRIES ;   /* ...specify the num of table entries */
    varsize numYEntries = NUM_Y_ENTRIES ;
    const varsize *engSpeed = engSpeedROM ;        /* Point to the constant linear tables */
    const varsize *engLoad = engLoadROM ;
    const varsize *angleTable = angleTableROM ;    /* ...and to the 3D table */

    for( i1 = 0 ; i1 < ( numXEntries - 1 ) ; i1++ )
    {
        if( ( loadValue < engLoad[i1+1] ) && ( loadValue >= engLoad[i1] ) )
        {
            break ;
        }
    }

    if( i1 == ( numXEntries - 1 ) )
    {
        loadValue = engLoad[i1] ;
    }
    engLoadDelta1 = (float)( loadValue - engLoad[i1] ) /
    (float)( engLoad[i1 + 1] - engLoad[i1] ) ;

    for( j1 = 0 ; j1 < ( numYEntries-1 ) ; j1++ )
    {
        if( ( speedValue < engSpeed[j1+1] ) &&
        ( speedValue >= engSpeed[j1] ) )
        {
            break ;
        }
    }

    if( j1 == ( numYEntries - 1 ) )
    {
        speedValue = engSpeed[j1] ;
    }

    engSpeedDelta1 = (float)( speedValue - engSpeed[j1] ) /
    (float)( engSpeed[j1 + 1] - engSpeed[j1] ) ;


    outAngleValue1 = (varsize)(
    ( ( 1.0 - engLoadDelta1 )*( 1.0 - engSpeedDelta1 ) *
    (float)angleTable[ i1 + ( j1 * numXEntries ) ] ) +
    ( engLoadDelta1 * ( 1.0 - engSpeedDelta1 ) *
    (float)angleTable[ ( i1 + 1 ) + ( j1 * numXEntries ) ] ) +
    ( engLoadDelta1 * engSpeedDelta1 *
    (float)angleTable[ ( i1 + 1 ) + ( numXEntries * ( j1 + 1 ) ) ] ) +
    ( ( 1.0 - engLoadDelta1 )* engSpeedDelta1 *
    (float)angleTable[ i1 + ( numXEntries * ( j1 + 1 ) ) ] ) ) ;


    WriteOut(outAngleValue1, outResult) ;

}
void readFile(inputData* data,outputData* outD){
   // printf("READ FILE");

    int index=0,i=0, x, y;
    char c;
    unsigned char inp;
    int ret = fscanf(stdin, "%c ",&c);
while(ret!=EOF) {
        outD[index].choice = c;
	switch(c){
		case 'a':
		case 'r':
        		ret = fscanf(stdin, "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld\n", &data[index].in1, &data[index].pulseDeltaTime1, &data[index].angle1, &data[index].angleCounterLast1, &data[index].toothCount1, &data[index].deltaTimeAccum1, &data[index].deltaTimeAvg1,&data[index].firingTime1, &data[index].tdcTime1, &data[index].engineSpeed1, &data[index].rotationTime1);  
			break;
		case 'i':
		case 'f':
			for(i=0; i<NUM_POINTS; i++){
				ret = fscanf(stdin, "%d %d ", &x, &y);
            			outD[index].result1[i] = x;
            			outD[index].result2[i] = y;
        		}
			break;
       		case 'd':
        	   	for( i = 0 ; i < ( ROWS + COLS ) ; i++ ){
           			 ret = fscanf(stdin, "%d ", &x);
				 inp = x;
				 data[index].inChar[i] = inp;
           		 }
     	  		 break;
     		case 'p':
            		ret = fscanf(stdin, "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld\n", &data[index].commandPos, &data[index].upDirection1, &data[index].lastDirection1, &data[index].endPhaseA1, &data[index].dirPhaseA1, &data[index].endPhaseB1, &data[index].dirPhaseB1, &data[index].incrementA1, &data[index].incrementB1, &data[index].internalPos1, &data[index].pwmCounter1, &data[index].pwmPhaseA1, &data[index].pwmPhaseB1);
           		 break;
        	case 't':
           		 ret = fscanf(stdin, "%ld %ld\n", &data[index].in1, &data[index].pulseDeltaTime1);
           		 break;
        	}
        index++;
        ret = fscanf(stdin, "%c ",&c);
    }
    NUMBEROFTEST = index;
}

void myKernel(inputData* data, outputData* outData){
     for(int index =0; index< NUMBEROFTEST; index++)//  blockIdx.x * blockDim.x + threadIdx.x;
    //printf("%c ", outData[index].choice);
    {
	 switch(outData[index].choice){
	case 'a':
     		a2time(data[index].in1, data[index].pulseDeltaTime1, data[index].angle1, data[index].angleCounterLast1, data[index].toothCount1, data[index].deltaTimeAccum1, data[index].deltaTimeAvg1, data[index].firingTime1, data[index].tdcTime1, data[index].engineSpeed1, data[index].rotationTime1, &outData[index].out1, &outData[index].out2);	break;
	case 'r':
		rdspeed(data[index].in1,data[index].pulseDeltaTime1, data[index].angle1, data[index].angleCounterLast1,data[index].toothCount1, data[index].deltaTimeAccum1,&outData[index].out1);	
	break;
        case 'i':
		aifftr01(outData[index].result1,outData[index].result2);
		break;
	case 'f':
		aiifft01(outData[index].result1,outData[index].result2);
		break;
    case 'd':
        idctrno1(data[index].inChar,outData[index].f_1);
        break;
    case 'p':
puwmod01(data[index].commandPos,data[index].upDirection1,data[index].lastDirection1,data[index].endPhaseA1,data[index].dirPhaseA1,data[index].endPhaseB1,data[index].dirPhaseB1,data[index].incrementA1,data[index].incrementB1,data[index].internalPos1,data[index].pwmCounter1,data[index].pwmPhaseA1, data[index].pwmPhaseB1, &outData[index].outendPhaseA1, &outData[index].outdirPhaseA1, &outData[index].outendPhaseB1, &outData[index].outdirPhaseB1 );        break; 
   case 't': 
       tblook01(data[index].in1, data[index].pulseDeltaTime1, &outData[index].out1);
        break;
	}
   }
}

void writeFile(double time, char* fileName){
    FILE *fp;
    fp = fopen("CPUResults.txt", "a");
    if (fp == NULL){
        printf("Problem in a file");
        return;
    }
    fprintf(fp, "%s ", fileName);
    fprintf(fp, "%21f seconds\n", time);
    fclose(fp);
}
int main(int argc, char *argv[] )
{
    inputData* data = (inputData*)malloc(sizeof(inputData) * NUMBEROFTEST);
    outputData* outD = (outputData*)malloc(sizeof(outputData) * NUMBEROFTEST);
    readFile(data,outD);
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    myKernel(data, outD);
    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / BILLION;
    writeFile(time_spent,argv[1]);
    for(int i=0; i<NUMBEROFTEST; i++){
	fprintf(stdout, "ID# %d %c: ", i, outD[i].choice);
	 switch(outD[i].choice){
        	case 'a':
                	fprintf(stdout, " - %ld %ld\n", outD[i].out1, outD[i].out2);
                	break;
		case 'r':
        	case 't':
        		fprintf(stdout, " - %ld %ld\n", outD[i].out1);
		    	break;
		case 'i':
		case 'f':
			for( int i_1 = 0 ; i_1 < NUM_POINTS ; i_1++ )
        		{
            			fprintf(stdout, " %ld ", outD[i].result1[i_1] ) ;
        		}
				fprintf(stdout, "\n");
			break;
        	case 'p':
            		fprintf(stdout, " - %ld %ld %ld %ld\n", outD[i].outendPhaseA1, outD[i].outdirPhaseA1, outD[i].outendPhaseB1, outD[i].outdirPhaseB1);
            		break;
    		}
    }
    free(data);
    free(outD);
    return 0;
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

