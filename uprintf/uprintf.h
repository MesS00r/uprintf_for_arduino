#ifndef USARTPRINT_H_INCLUDED
#define USARTPRINT_H_INCLUDED

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

namespace Detail {
    void uprint_write(PGM_P fmt, uint8_t len, uint16_t *args);

    template <typename ... Args>
    void _uprintf(PGM_P fmt, const Args& ... args) {
        static_assert(sizeof...(args) <= 15, "too many arguments for uprintf");
        uint8_t len = sizeof...(args), index = 0;
        uint16_t arg_arr[15];

        int dummy[] = {0, (arg_arr[index++] = args, 0)...};
        (void)dummy;

        uprint_write(fmt, len, arg_arr);
    }
}

void ubegin(const uint16_t baud);
#define uprintf(fmt, ...) Detail::_uprintf(PSTR(fmt), ##__VA_ARGS__);

#endif //USARTPRINT_H_INCLUDED