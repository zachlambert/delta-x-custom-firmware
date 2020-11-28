
// Before separate header:
// Without inline:
//   Program: 672
//   Data: 4
// With inline:
//   Program: 494
//   Data: 0
//
// After separate header:
// Without inline:
//   Program: 672
//   Data: 4
// With inline:
//   Program: 494
//   Data: 0
//
//   ** Still can't guarantee that pgmspace stuff works though, need to test **
//
// BUT, need a config.h to provide pin definitions.
// Without inline:
//   Program: 644
//   Data: 4
// With inline:
//   Program: 930
//   Data: 4
//
// What if you just remove PinImpl and create static Pin data?
// With inline functions, gives:
//   Program: 494
//   Data: 0
// This is good.
// (Removing inline -> Program: 614, Data: 4)
// 
// Now that I think about it, there isn't much point using pointers to pins
// when the Pin itself is only 1 byte.
// Also, if the pin is treated as static data, the compiler can treat it
// as constant and do appropriate optimisations, I think.

#include <util/delay.h>
#include "pin.h"
#include "config.h"

int main(void)
{
    init_output(led);
    init_output(led2);
    init_output(led3);
    while (1) {
        set(led);
        set(led2);
        set(led3);
        _delay_ms(500);
        clear(led);
        clear(led2);
        clear(led3);
        _delay_ms(500);
    }
    return 0;
}
