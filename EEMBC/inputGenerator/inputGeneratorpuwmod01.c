

/*******************************************************************************
    Includes                                                                    
*******************************************************************************/

#define ALGO_GLOBALS    1
#include <stdlib.h>
#include <stdio.h>
int NUMBEROFTEST = 1024;

#define false           0
#define true            !false
typedef short varsize ; 
typedef struct{
    varsize in1;
    varsize in2;
    varsize in3;
} inputData;

#define MAX_PHASE       20          /* Maximum duty cycle, per 'pwmCounter' */
#define MAX_COUNT       MAX_PHASE+1 /* Overflow of duty cycle counter */
#define MID_PHASE       MAX_PHASE/2 /* 50% duty cycle */

/* Estimate of allocation for NUM_TESTS*( debug test + 2 variables )*/
#define T_BSIZE (MAX_FILESIZE+((NUM_TESTS+1)*VAR_COUNT*4))

/* ======================================================================== */
/*         F U N C T I O N   P R O T O T Y P E S                            */
/* ======================================================================== */
void writeToInputFile(varsize in1, varsize in2, varsize in3,
                      int upDirection1 ,       /* Initial direction is 'up' */
                      int upDirection2 ,
                      int upDirection3 ,
                      int lastDirection1 ,     /* Memory of direction to detect change */
                      int lastDirection2 ,
                      int lastDirection3 ,
                      int enbPhaseA1 ,         /* Enable for the coil A driver */
                      int enbPhaseA2 ,
                      int enbPhaseA3 ,
                      int dirPhaseA1 ,         /* Dir. control for the coil A driver */
                      int dirPhaseA2 ,
                      int dirPhaseA3 ,
                      int enbPhaseB1 ,         /* Enable for the coil B driver */
                      int enbPhaseB2 ,
                      int enbPhaseB3 ,
                      int dirPhaseB1 ,         /* Dir. control for the coil B driver */
                      int dirPhaseB2 ,
                      int dirPhaseB3 ,
                      int incrementA1 ,        /* Incr./decrement coil A's duty cycle */
                      int incrementA2 ,
                      int incrementA3 ,
                      int incrementB1 ,        /* Incr./decrement coil B's duty cycle */
                      int incrementB2 ,
                      int incrementB3 ,
                      varsize internalPos1 ,   /* Alg.'s internal electrical position */
                      varsize internalPos2 ,
                      varsize internalPos3 ,
                      int pwmCounter1 ,        /* The PWM phase counter */
                      int pwmCounter2 ,
                      int pwmCounter3 ,
                      int pwmPhaseA1 ,         /* The counter-comparator for coil A */
                      int pwmPhaseA2 ,
                      int pwmPhaseA3 ,
                      int pwmPhaseB1 ,         /* The counter-comparator for coil B */
                      int pwmPhaseB2 ,
                      int pwmPhaseB3);


/*******************************************************************************
    Local Data                                                                  
*******************************************************************************/




varsize commandPos ;        /* Commanded position from external world */
varsize *inpCmdPosition ;   /* Array of 'cmdPosition' test data values */

void t_run_test(inputData* data)
{    
    static int upDirection1 ;       /* Initial direction is 'up' */
    static int upDirection2 ; 
    static int upDirection3 ; 
    static int lastDirection1 ;     /* Memory of direction to detect change */
    static int lastDirection2 ; 
    static int lastDirection3 ; 
    static int enbPhaseA1 ;         /* Enable for the coil A driver */
    static int enbPhaseA2 ;     
    static int enbPhaseA3 ; 
    static int dirPhaseA1 ;         /* Dir. control for the coil A driver */
    static int dirPhaseA2 ; 
    static int dirPhaseA3 ; 
    static int enbPhaseB1 ;         /* Enable for the coil B driver */
    static int enbPhaseB2 ; 
    static int enbPhaseB3 ; 
    static int dirPhaseB1 ;         /* Dir. control for the coil B driver */
    static int dirPhaseB2 ; 
    static int dirPhaseB3 ; 
    static int incrementA1 ;        /* Incr./decrement coil A's duty cycle */
    static int incrementA2 ; 
    static int incrementA3 ; 
    static int incrementB1 ;        /* Incr./decrement coil B's duty cycle */
    static int incrementB2 ; 
    static int incrementB3 ; 
    static varsize internalPos1 ;   /* Alg.'s internal electrical position */
    static varsize internalPos2 ; 
    static varsize internalPos3 ; 
    static int pwmCounter1 ;        /* The PWM phase counter */
    static int pwmCounter2 ; 
    static int pwmCounter3 ; 
    static int pwmPhaseA1 ;         /* The counter-comparator for coil A */
    static int pwmPhaseA2 ; 
    static int pwmPhaseA3 ; 
    static int pwmPhaseB1 ;         /* The counter-comparator for coil B */
    static int pwmPhaseB2 ; 
    static int pwmPhaseB3 ; 


    /*
     * First, initialize the data structures we need for the test
     * and allocate memory as needed.  Report an error if we can't.
     *
     */    

    /* Variable initializations at t=0 */    
    pwmCounter1 = 0 ;   /* Initialize the PWM phase counter... */
    pwmCounter2 = 0 ; 
    pwmCounter3 = 0 ; 
    dirPhaseA1 = 0 ;    /* ...and the coil driver bits */
    dirPhaseA2 = 0 ; 
    dirPhaseA3 = 0 ; 
    dirPhaseB1 = 0 ; 
    dirPhaseB2 = 0 ; 
    dirPhaseB3 = 0 ; 
    enbPhaseA1 = 1 ; 
    enbPhaseA2 = 1 ; 
    enbPhaseA3 = 1 ; 
    enbPhaseB1 = 1 ; 
    enbPhaseB2 = 1 ; 
    enbPhaseB3 = 1 ; 
    pwmPhaseA1 = MID_PHASE ;    /* ...and set 50% duty cycle */
    pwmPhaseA2 = MID_PHASE ; 
    pwmPhaseA3 = MID_PHASE ; 
    pwmPhaseB1 = MID_PHASE ; 
    pwmPhaseB2 = MID_PHASE ; 
    pwmPhaseB3 = MID_PHASE ; 
    upDirection1 = true ;       /* ...and presume we'll move 'up' */
    upDirection2 = true ; 
    upDirection3 = true ; 
    lastDirection1 = true ; 
    lastDirection2 = true ; 
    lastDirection3 = true ; 
    incrementA1 = true ;        /* ...which means we increase */
    incrementA2 = true ;        /* coil A duty cycle */
    incrementA3 = true ; 
    incrementB1 = false ;       /* ...and decrease coil B duty cycle */
    incrementB2 = false ; 
    incrementB3 = false ; 

    internalPos1 = 0 ;          /* Start out at zero position */
    internalPos2 = 0 ; 
    internalPos3 = 0 ; 
 //   tableCount = 0 ;    /* Start out at beginning of input test data */
for(int i=0; i<NUMBEROFTEST; i++){
    writeToInputFile(data[i].in1, data[i].in2, data[i].in3, upDirection1, upDirection2 , upDirection3 ,lastDirection1 , lastDirection2 , lastDirection3 , enbPhaseA1 , enbPhaseA2 , enbPhaseA3 , dirPhaseA1 , dirPhaseA2 , dirPhaseA3 , enbPhaseB1 , enbPhaseB2 , enbPhaseB3 , dirPhaseB1 , dirPhaseB2 , dirPhaseB3 , incrementA1 , incrementA2 , incrementA3 , incrementB1 , incrementB2 , incrementB3 , internalPos1 , internalPos2 , internalPos3 , pwmCounter1 , pwmCounter2 , pwmCounter3 , pwmPhaseA1 , pwmPhaseA2 , pwmPhaseA3 , pwmPhaseB1 , pwmPhaseB2 , pwmPhaseB3 );
    /* This is the actual benchmark algorithm. */    

    /*
     * The Pulse-Width Modulation algorithm will take an input variable, 
     * presumed to be a position command for a stepper motor controlled
     * fuel-control valve, and will move the motor to that position using
     * micro-stepping control.  Micro-stepping requires that a proportional
     * current be applied in each motor coil to cause the armature to sit
     * at fractional positions within the fixed step angle of the motor.
     * This requires a PWM signal to be developed for each motor coil.
     *
     * Normally, in a two-phase stepper motor, each coil is energized in
     * either of two polarities of current flow, the four combinations of
     * which causing the stepping action when applied in the correct
     * sequence : 
     *
     * Motor coil :    A    B
     *                +    -        1    \
     *                +    +        2     |__   one cycle, 4 steps
     *                -    +        3     |
     *                -    -        4    /
     *                +    -        5
     *
     * By applying a proportional current in each phase, as well as the
     * major step polarity shown above, we can "micro-step" to positions
     * between steps 1 and 2.  This will be the purpose of the PWM
     * algorithm.  Micro-stepping not only provides more resolution for
     * motor position, but also results in smoother positioning.
     *
     * The following algorithm will presume that each pass through the loop
     * is caused by an interrupt which occurs at a fixed rate, which is
     * substantially higher than the maximum step rate applied to the
     * motor, so that a loop counter can be used to perform the timing
     * for the PWM.  If an 8-bit counter is used, then the algorithm will
     * provide up to 256 micro-step positions within each major motor step.
     *
     * For maximum torque, both motor coils will be energized at
     * 50% duty cycle in each coil applied at the major-step( motor
     * resolution )positions, while 100% duty cycle and 0% duty cycle, 
     * respectively, will be applied to the coils at the middle 
     * micro-step position between two major-step positions.  The PWM duty-
     * cycle will then increase from 0% on the de-energized coil, in the
     * reverse polarity, and decrease proportionally from 100% on the other
     * coil, until 50%/50% is reached again at the next major-step position.
     *
     *
     */    

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
            /* Get 'commandPos' value from test data*/
            commandPos = data[i].in1;
            
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

                /* If we reach the mid-point between major motor step 
                 * positions, then we must flip the coil driver polarity
                 *
                 */
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

                /* Depending on direction, bump the internal position */
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

        /***********************************************************************
            Second Pass                                                         
        ***********************************************************************/

        /* 
         * First, check the PWM phase, and drive the two motor coils depending
         * on their duty-cycle( DC )setpoints.
         */    

        pwmCounter2++ ;                 /* Bump the PWM phase counter */

        if( pwmCounter2 == MAX_COUNT )  /* Counter overflowed ? */
        {
            pwmCounter2 = 0 ;           /* Yes, reset the counter */
        }



        if( ( pwmCounter2 == pwmPhaseA2 ) &&    /* Reached end of phase A */
            ( pwmPhaseA2 < MAX_PHASE ) )        /*  and not 100% DC ? */
        {
            enbPhaseA2 = 0 ;    /* Yes, turn phase A off now */
        }
        if( ( pwmCounter2 == pwmPhaseB2 ) &&    /* Reached end of phase B */
            ( pwmPhaseB2 < MAX_PHASE ) )        /*  and not 100% DC ? */
        {
            enbPhaseB2 = 0 ;    /* Yes, turn phase B off now */
        }

        /* Now, check to see if the counter rolled over, indicating the end 
         * of a PWM cycle, and maybe time to change the motor position. We 
         * change the motor position if the commanded position is different 
         * from the current internal position. If so, we will increment the
         * internal position by one micro-step, which will require a new
         * proportional duty-cycle to be applied to each coil.
         *
         * When one phase is at 0% duty-cycle, and is incremented by one
         * micro-step, then the polarity for that phase must also be switched,
         * per the major-step table. Note that we may need to be decrementing 
         * motor position, depending on the sign of the difference between 
         * commanded and internal position.
         *
         */    

        if( pwmCounter2 == 0 ) /* Sync with pwm counter rollover */
        {
            /* Get 'commandPos' value from test data*/
            commandPos = data[i].in2;
            
            /* Are we commanded to move 'up'? */
            if( commandPos > internalPos2 ) 
            {
                /* Yes, remember that */
                upDirection2 = true ;
            }

            /* Are we commanded to move 'down' ? */
            if( commandPos < internalPos2 ) 
            {
                /* Yes, remember that */
                upDirection2 = false ;
            }

            if( upDirection2 != lastDirection2 )
            {        
                /* Change in direction ? */
                incrementA2 = !incrementA2 ;
                /* ...then, flip the duty-cycle bits */
                incrementB2 = !incrementB2 ;
            }

            /* Remember current direction for next pass */
            lastDirection2 = upDirection2 ;

            /* Are we commanded to move ? */
            if( commandPos != internalPos2 )
            {
                /* Yes, so micro-step per the duty-cycle bits */    
                if( incrementA2 )
                {
                    pwmPhaseA2++ ; 
                }
                else
                {
                    pwmPhaseA2-- ; 
                }

                if( ( pwmPhaseA2 == MAX_COUNT ) && incrementA2 )
                {        
                    pwmPhaseA2 = MAX_PHASE - 1 ; 
                    incrementA2 = false ; 
                }

                if( ( pwmPhaseA2 < 0 ) && !incrementA2 )
                {        
                    pwmPhaseA2 = 1 ; 
                    incrementA2 = true ; 
                }

                if( incrementB2 )
                {
                    pwmPhaseB2++ ; 
                }
                else
                {
                    pwmPhaseB2-- ; 
                }
                
                if( ( pwmPhaseB2 == MAX_COUNT ) && incrementB2 )
                {        
                    pwmPhaseB2 = MAX_PHASE - 1 ; 
                    incrementB2 = false ; 
                }

                if( ( pwmPhaseB2 < 0 ) && !incrementB2 )
                {        
                    pwmPhaseB2 = 1 ; 
                    incrementB2 = true ; 
                }

                /* If we reach the mid-point between major motor step 
                 * positions, then we must flip the coil driver polarity
                 *
                 */
                if( pwmPhaseA2 == 0 )
                {
                    if( dirPhaseA2 == 1 )
                    {
                        dirPhaseA2 = 0 ; 
                    }
                    else
                    {
                        dirPhaseA2 = 1 ; 
                    }
                }

                /* If we reach the mid-point between major motor step 
                 * positions, then we must flip the coil driver polarity
                 *
                 */
                if( pwmPhaseB2 == 0 )
                {
                    if( dirPhaseB2 == 1 )   
                    {
                        dirPhaseB2 = 0 ; 
                    }
                    else
                    {
                        dirPhaseB2 = 1 ; 
                    }
                }

                /* Depending on direction, bump the internal position */
                if( upDirection2 )   
                {
                    internalPos2++ ;
                }
                else
                {
                    internalPos2-- ; 
                }
            } /* End of 'commandPos != internalPos' */

            if( pwmPhaseA2 > 0 )   /* If >0% DC, turn A on again */
            {
                enbPhaseA2 = 1 ; 
            }

            if( pwmPhaseB2 > 0 )   /* And if >0% DC, turn B on again */
            {
                enbPhaseB2 = 1 ; 
            }
        }

        /***********************************************************************
            Third Pass                                                          
        ***********************************************************************/

        /* 
         * First, check the PWM phase, and drive the two motor coils depending
         * on their duty-cycle( DC )setpoints.
         */    

        pwmCounter3++ ;                 /* Bump the PWM phase counter */

        if( pwmCounter3 == MAX_COUNT )  /* Counter overflowed ? */
        {
            pwmCounter3 = 0 ;           /* Yes, reset the counter */
        }

        if( ( pwmCounter3 == pwmPhaseA3 ) &&    /* Reached end of phase A */
            ( pwmPhaseA3 < MAX_PHASE ) )        /*  and not 100% DC ? */
        {
            enbPhaseA3 = 0 ;    /* Yes, turn phase A off now */
        }
        if( ( pwmCounter3 == pwmPhaseB3 ) &&    /* Reached end of phase B */
            ( pwmPhaseB3 < MAX_PHASE ) )        /*  and not 100% DC ? */
        {
            enbPhaseB3 = 0 ;    /* Yes, turn phase B off now */
        }

        /* Now, check to see if the counter rolled over, indicating the end 
         * of a PWM cycle, and maybe time to change the motor position. We 
         * change the motor position if the commanded position is different 
         * from the current internal position. If so, we will increment the
         * internal position by one micro-step, which will require a new
         * proportional duty-cycle to be applied to each coil.
         *
         * When one phase is at 0% duty-cycle, and is incremented by one
         * micro-step, then the polarity for that phase must also be switched,
         * per the major-step table. Note that we may need to be decrementing 
         * motor position, depending on the sign of the difference between 
         * commanded and internal position.
         *
         */    

        if( pwmCounter3 == 0 ) /* Sync with pwm counter rollover */
        {
            commandPos = data[i].in3;
            
            /* Are we commanded to move 'up'? */
            if( commandPos > internalPos3 ) 
            {
                /* Yes, remember that */
                upDirection3 = true ;
            }

            /* Are we commanded to move 'down' ? */
            if( commandPos < internalPos3 ) 
            {
                /* Yes, remember that */
                upDirection3 = false ;
            }

            if( upDirection3 != lastDirection3 )
            {        
                /* Change in direction ? */
                incrementA3 = !incrementA3 ;
                /* ...then, flip the duty-cycle bits */
                incrementB3 = !incrementB3 ;
            }

            /* Remember current direction for next pass */
            lastDirection3 = upDirection3 ;

            /* Are we commanded to move ? */
            if( commandPos != internalPos3 )
            {
                /* Yes, so micro-step per the duty-cycle bits */    
                if( incrementA3 )
                {
                    pwmPhaseA3++ ; 
                }
                else
                {
                    pwmPhaseA3-- ; 
                }

                if( ( pwmPhaseA3 == MAX_COUNT ) && incrementA3 )
                {        
                    pwmPhaseA3 = MAX_PHASE - 1 ; 
                    incrementA3 = false ; 
                }

                if( ( pwmPhaseA3 < 0 ) && !incrementA3 )
                {        
                    pwmPhaseA3 = 1 ; 
                    incrementA3 = true ; 
                }

                if( incrementB3 )
                {
                    pwmPhaseB3++ ; 
                }
                else
                {
                    pwmPhaseB3-- ; 
                }
                
                if( ( pwmPhaseB3 == MAX_COUNT ) && incrementB3 )
                {        
                    pwmPhaseB3 = MAX_PHASE - 1 ; 
                    incrementB3 = false ; 
                }

                if( ( pwmPhaseB3 < 0 ) && !incrementB3 )
                {        
                    pwmPhaseB3 = 1 ; 
                    incrementB3 = true ; 
                }

                /* If we reach the mid-point between major motor step 
                 * positions, then we must flip the coil driver polarity
                 *
                 */
                if( pwmPhaseA3 == 0 )
                {
                    if( dirPhaseA3 == 1 )
                    {
                        dirPhaseA3 = 0 ; 
                    }
                    else
                    {
                        dirPhaseA3 = 1 ; 
                    }
                }

                /* If we reach the mid-point between major motor step 
                 * positions, then we must flip the coil driver polarity
                 *
                 */
                if( pwmPhaseB3 == 0 )
                {
                    if( dirPhaseB3 == 1 )   
                    {
                        dirPhaseB3 = 0 ; 
                    }
                    else
                    {
                        dirPhaseB3 = 1 ; 
                    }
                }

                /* Depending on direction, bump the internal position */
                if( upDirection3 )   
                {
                    internalPos3++ ;
                }
                else
                {
                    internalPos3-- ; 
                }
            } /* End of 'commandPos != internalPos' */

            if( pwmPhaseA3 > 0 )   /* If >0% DC, turn A on again */
            {
                enbPhaseA3 = 1 ; 
            }

            if( pwmPhaseB3 > 0 )   /* And if >0% DC, turn B on again */
            {
                enbPhaseB3 = 1 ; 
            }
        }
}

}
void readFile(inputData* data){
        // printf("READ FILE");

        int index=0;
        int X, Y, Z;
       // int ret = fscanf(stdin, "%d %d %d", &X, &Y,&Z);
         int ret = fscanf(stdin, "%d ", &X);
        while(ret != EOF && index < NUMBEROFTEST){
            data[index].in1 = X ;
         //   data[index].in2 = Y;
          //  data[index].in3 =Z;
            index++;
            ret = fscanf(stdin, "%d ", &X);
        }
        // printf("END READ FILE");
        NUMBEROFTEST = index;
    }

/***************************************************************************/
int main(int argc, char* argv[] )
{

    inputData* data = (inputData*)malloc(sizeof(inputData) * NUMBEROFTEST);
    readFile(data);
    t_run_test(data);
} 

    void writeToInputFile(varsize in1, varsize in2, varsize in3,
                          int upDirection1 ,       /* Initial direction is 'up' */
                          int upDirection2 ,
                          int upDirection3 ,
                          int lastDirection1 ,     /* Memory of direction to detect change */
                          int lastDirection2 ,
                          int lastDirection3 ,
                          int enbPhaseA1 ,         /* Enable for the coil A driver */
                          int enbPhaseA2 ,
                          int enbPhaseA3 ,
                          int dirPhaseA1 ,         /* Dir. control for the coil A driver */
                          int dirPhaseA2 ,
                          int dirPhaseA3 ,
                          int enbPhaseB1 ,         /* Enable for the coil B driver */
                          int enbPhaseB2 ,
                          int enbPhaseB3 ,
                          int dirPhaseB1 ,         /* Dir. control for the coil B driver */
                          int dirPhaseB2 ,
                          int dirPhaseB3 ,
                          int incrementA1 ,        /* Incr./decrement coil A's duty cycle */
                          int incrementA2 ,
                          int incrementA3 ,
                          int incrementB1 ,        /* Incr./decrement coil B's duty cycle */
                          int incrementB2 ,
                          int incrementB3 ,
                          varsize internalPos1 ,   /* Alg.'s internal electrical position */
                          varsize internalPos2 ,
                          varsize internalPos3 ,
                          int pwmCounter1 ,        /* The PWM phase counter */
                          int pwmCounter2 ,
                          int pwmCounter3 ,
                          int pwmPhaseA1 ,         /* The counter-comparator for coil A */
                          int pwmPhaseA2 ,
                          int pwmPhaseA3 ,
                          int pwmPhaseB1 ,         /* The counter-comparator for coil B */
                          int pwmPhaseB2 ,
                          int pwmPhaseB3 ){
        FILE *fp;
        fp = fopen("puwmod01InputFile.txt", "a");
        if (fp == NULL){
            printf("Problem in a file");
            return;
        }
        fprintf(fp,"p %ld", in1);
      //  fprintf(fp," %ld", in2);
       // fprintf(fp," %ld", in3);

        fprintf(fp," %ld", upDirection1);
       // fprintf(fp," %ld", upDirection2);
       // fprintf(fp," %ld", upDirection3);

        fprintf(fp," %ld", lastDirection1);
     /*   fprintf(fp," %ld", lastDirection2);
        fprintf(fp," %ld", lastDirection3);
*/
        fprintf(fp," %ld", enbPhaseA1);
  /*      fprintf(fp," %ld", enbPhaseA2);
        fprintf(fp," %ld", enbPhaseA3);
*/
        fprintf(fp," %ld", dirPhaseA1);
  /*      fprintf(fp," %ld", dirPhaseA2);
        fprintf(fp," %ld", dirPhaseA3);
*/
        fprintf(fp," %ld", enbPhaseB1);
  /*      fprintf(fp," %ld", enbPhaseB2);
        fprintf(fp," %ld", enbPhaseB3);
*/
        fprintf(fp," %ld", dirPhaseB1);
  /*      fprintf(fp," %ld", dirPhaseB2);
        fprintf(fp," %ld", dirPhaseB3);
*/
        fprintf(fp," %ld", incrementA1);
  /*      fprintf(fp," %ld", incrementA2);
        fprintf(fp," %ld", incrementA3);
*/
        fprintf(fp," %ld", incrementB1);
 /*       fprintf(fp," %ld", incrementB2);
        fprintf(fp," %ld", incrementB3);

  */      fprintf(fp," %ld", internalPos1);
   /*     fprintf(fp," %ld", internalPos2);
        fprintf(fp," %ld", internalPos3);
*/
        fprintf(fp," %ld", pwmCounter1);
  //      fprintf(fp," %ld", pwmCounter2);
    //    fprintf(fp," %ld", pwmCounter3);

        fprintf(fp," %ld", pwmPhaseA1);
      //  fprintf(fp," %ld", pwmPhaseA2);
       // fprintf(fp," %ld", pwmPhaseA3);

        fprintf(fp," %ld", pwmPhaseB1);
 //       fprintf(fp," %ld", pwmPhaseB2);
  //      fprintf(fp," %ld", pwmPhaseB3);

        fputs("\n",fp);
        fclose(fp);
    }

