/*
 TimeStampOBJ.h
 CREATED on WEDNESDAY 17 APRIL 2019
 by CHANSIGAUD YANN

TimeStampOBJ available on https://github.com/YannChansigaud/TimeStampOBJ
TimeStampOBJ use TimeOBJ available on : https://github.com/YannChansigaud/TimeOBJ

TimeStampOBJ is designed to define a time mark. All internal calculation are using microsecond with micros()

WARNING : all values sended to TimeStampOBJ with overloaded comparison operator ( >, <, >=, <= ) are evaluated as millisecond in view to correspond to millis()
          define TimeStampOBJ_defaultFormat to "MICRO" if you want to pass microseconds values

PAY ATTENTION : this class has to be called with compute() at least 1 time per hours
                maximum delay between two calls : 1h 11min 34s 967ms 295us (H/M/S/ms/us equivalent for the maximum of uint32_t length return by micros() )

- This class didn't reset micros().
- micros() rollback to zero by itself when uint32_t maximum reached

This class use 2 TimeOBJ objects
- TimeOBJ now : Time object to store total execution time since the begining 
- TimeOBJ pass : Time object to store elapsed time since last call
                 This object is use to store temporary values used by comparison operator

- TNOW, TPREV, TPASS : uint32_t variables used for calculation with micros()

*/
#ifndef TimeStampOBJ_h
#define TimeStampOBJ_h
#include <inttypes.h>
#include "TimeOBJ.h"

#define MAX_UINT32_T   4294967295

//#define TimeStampOBJ_defaultFormat   MICRO
#define TimeStampOBJ_defaultFormat   MILLI

class TimeStampOBJ{                                         // 
  public :                                                  // 
    TimeStampOBJ();                                         // 
    // ==================================================== //       Values get back methods
    TimeOBJ &getTimeFromLastCheck();                        // since last call
    TimeOBJ &getTimeFromBeginning();                        // since the begenning
    // ==================================================== //
    TimeOBJ operator=( TimeStampOBJ &obj );
    // ==================================================== //       Overloaded comparison operator with values
    bool operator>=( uint32_t val );                        // >=
    bool operator<=( uint32_t val );                        // <=
    bool operator>(  uint32_t val );                        // >
    bool operator<(  uint32_t val );                        // <
    // ==================================================== //       Overloaded comparison operator with TimeOBJ objects
    bool operator>=( const TimeOBJ &TimeToCompare );        // >=
    bool operator<=( const TimeOBJ &TimeToCompare );        // <=
    bool operator>(  const TimeOBJ &TimeToCompare );        // >
    bool operator<(  const TimeOBJ &TimeToCompare );        // <
    // ==================================================== //       
    uint8_t getNbLoop();                                    // Accessor to nbLoop of micros() counted
    void compute();                                         // Method called at least 1 time per hour
    TimeOBJ &get();                                         // 
    // ==================================================== // 
  private :                                                 // 
    TimeOBJ now     = TimeOBJ();                            // 
    TimeOBJ past    = TimeOBJ();                            // 
    uint32_t TPREV  = 0;                                    // 
    uint32_t TNOW   = 0;                                    // 
    uint32_t TPASS  = 0;                                    // 
    uint8_t  nbLoop = 0;                                    // 
    bool has_loop   = false;                                // 
};                                                          // 

#endif
