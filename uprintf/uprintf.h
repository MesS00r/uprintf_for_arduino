#ifndef USARTPRINT_H_INCLUDED
#define USARTPRINT_H_INCLUDED

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

void ubegin(const uint16_t baud);
void _uprintf(const char *fmt, uint8_t len, uint16_t *args);

inline void get_arg(uint16_t arg, uint16_t *copy) {
    *copy = arg;
}

template <typename ... Args>
void uprintf(PGM_P fmt, const Args& ... args) {
    uint8_t len = sizeof...(args), index = 0;
    uint16_t arg_arr[len];

    int dummy[] = {0, (get_arg(args, &arg_arr[index++]), 0)...};
    (void)dummy;

    _uprintf(fmt, len, arg_arr);
}

#endif //USARTPRINT_H_INCLUDED