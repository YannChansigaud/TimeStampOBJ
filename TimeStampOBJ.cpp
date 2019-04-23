/*
 * TimeStampOBJ.cpp
 * CREATED on WEDNESDAY 17 APRIL 2019
 * by CHANSIGAUD YANN
 */


#if (ARDUINO <  100)
#include <WProgram.h>
#else
#include <Arduino.h>
#endif
#include <inttypes.h>

#include "TimeOBJ.h"
#include "TimeStampOBJ.h"
// ====================================================================================================== // 
TimeStampOBJ::TimeStampOBJ(){}                                                                            // CONSTRUCTOR
TimeOBJ &TimeStampOBJ::getTimeFromLastCheck(){    compute();  return( past );    }                        // compute and return past value
TimeOBJ &TimeStampOBJ::getTimeFromBeginning(){    compute();  return( now  );    }                        // compute and return now value
// ====================================================================================================== // 
uint8_t TimeStampOBJ::getNbLoop(){    return( nbLoop );    }                                              // 
void TimeStampOBJ::compute(){                                                                             // MAIN CALCULATION METHOD
    TNOW = micros();                                                                                      // calling back values from micros()
    if( TNOW < TPREV ){                                                                                   // If last call was greater than this call 
        has_loop = true;                                                                                  //   it means that micros has rolling back to zero
        nbLoop++;                                                                                         //   nbLoop increased
    }                                                                                                     // 
    else{                                                                                                 // Else
        has_loop = false;                                                                                 //   
    }                                                                                                     // 
    if( has_loop ){    TPASS = TNOW - 0 + ( MAX_UINT32_T - TPREV );    }                                  // If rolling back, count from last one to the end plus from the begining to now
    else{              TPASS = TNOW - TPREV;                           }                                  // If not, just count from last to now
    now.add( TPASS, MICRO );                                                                              // Adding elapsed time to TimeOBJ now
    past = 0;                                                                                             // Setting TimeOBJ past to zero
    past.add( TPASS, MICRO );                                                                             // Store elapsed time value to TimeOBJ past
    TPREV = TNOW;                                                                                         // record this time point to TPREV
}                                                                                                         // 
// ====================================================================================================== // 
TimeOBJ &TimeStampOBJ::get(){                                     return( now );                     }    // Return now object
// ====================================================================================================== // 
bool TimeStampOBJ::operator>=( uint32_t val ){                    return( !(*this<val) );            }    // To compare >= return the opposite <
bool TimeStampOBJ::operator<=( uint32_t val ){                    return( !(*this>val) );            }    // 
bool TimeStampOBJ::operator>=( const TimeOBJ &TimeToCompare ){    return( !(*this<TimeToCompare) );  }    // 
bool TimeStampOBJ::operator<=( const TimeOBJ &TimeToCompare ){    return( !(*this>TimeToCompare) );  }    // 
bool TimeStampOBJ::operator>(  uint32_t val ){                                                            // compare a uint32_t value ( like millis() ) to TimeStampOBJ
    compute();                                                                                            // compute values
    past = 0;                                                                                             // reset temporary TimeOBJ object
    past.add( val, TimeStampOBJ_defaultFormat );                                                          // adding parsed value 
    return( now>past );                                                                                   // return result
}                                                                                                         // 
bool TimeStampOBJ::operator<(  uint32_t val ){                                                            // compare a uint32_t value ( like millis() ) to TimeStampOBJ
    compute();                                                                                            // compute values
    past = 0;                                                                                             // reset temporary TimeOBJ object
    past.add( val, TimeStampOBJ_defaultFormat );                                                          // adding parsed value
    return( now<past );                                                                                   // return result
}                                                                                                         // 
bool TimeStampOBJ::operator>(  const TimeOBJ &TimeToCompare ){    return( now>TimeToCompare );      }     // 
bool TimeStampOBJ::operator<(  const TimeOBJ &TimeToCompare ){    return( now<TimeToCompare );      }     // 
