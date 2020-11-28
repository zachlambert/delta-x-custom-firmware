
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
