#ifndef USARTPRINT_H_INCLUDED
#define USARTPRINT_H_INCLUDED

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

void ubegin(const uint16_t baud);

void usart_print_ch(const char ch);
void usart_print_str(const char *str);
void usart_print_dec(const uint16_t num);
void usart_print_bin(const uint16_t num);
void usart_print_hex(const uint16_t num);

inline void uprintf(const char *fmt) {
    usart_print_str(fmt);
}

template <typename First, typename ... Args>
void uprintf(const char *fmt, const First& first, const Args& ... args) {
    // uint8_t len = (sizeof...(args) + 1);
    char ch0, ch1;

    ch0 = pgm_read_byte(fmt);
    fmt++;

    if (ch0 == '%') {
        ch1 = pgm_read_byte(fmt);
        fmt++;

        switch (ch1) {
        case 'd': case 'D':
            usart_print_dec(first);
            break;
        case 'b': case 'B':
            usart_print_bin(first);
            break;
        case 'x': case 'X':
            usart_print_hex(first);
            break;
        default:
            usart_print_ch(ch0);
            usart_print_ch(ch1);
            break;
        }

        uprintf(fmt, args...);
    } else {
        usart_print_ch(ch0);
        uprintf(fmt, first, args...);
    }
}

#endif //USARTPRINT_H_INCLUDED