#include "uprintf.h"

// ****** DIV && REM 10 ******

uint16_t divu10(uint16_t num) {
    uint16_t quot, rem;

    quot = (num >> 1) + (num >> 2);
    quot += (quot >> 4);
    quot += (quot >> 8);
    quot >>= 3;
    rem = num - (((quot << 2) + quot) << 1);

    return quot + (rem > 9);
}

uint16_t remu10(uint16_t num) {
    uint16_t quot, rem;

    quot = (num >> 1) + (num >> 2);
    quot += (quot >> 4);
    quot += (quot >> 8);
    quot >>= 3;
    rem = num - (((quot << 2) + quot) << 1);

    return rem > 9 ? rem - 10 : rem;
}

uint16_t divu10d(uint16_t num, uint8_t deg) {
    deg = deg > 4 ? 4 : deg;

    for (uint8_t i = 0; i < deg; i++) {
        num = divu10(num);
    }
    return num;
}

uint16_t remu10d(uint16_t num, uint8_t deg) {
    uint16_t pow10 = 10, rem = 0;

    deg = deg > 4 ? 4 : deg;

    for (uint8_t i = 0; i < deg; i++) {
        rem *= (pow10 * i);
        rem += remu10(num);
    }
    return rem;
}

// ****** DIV && REM 2 ******

inline uint16_t divu2(uint16_t num) {
    return num >> 1;
}

inline uint16_t remu2(uint16_t num) {
    return num & 0x01;
}

inline uint16_t divu2d(uint16_t num, uint8_t deg) {
    deg = deg > 16 ? 16 : deg;
    return num >> deg;
}

uint16_t remu2d(uint16_t num, uint8_t deg) {
    uint16_t mask = 0x00;

    deg = deg > 16 ? 16 : deg;

    if (deg == 1) mask = 0x01;
    else if (deg <= 4) mask = 0x0f;
    else if (deg <= 8) mask = 0xff;
    else if (deg <= 12) mask = 0x0fff;
    else if (deg <= 16) mask = 0xffff;

    return num & mask;
}

// ****** DIV && REM 16 ******

inline uint16_t divu16(uint16_t num) {
    return num >> 4;
}

inline uint16_t remu16(uint16_t num) {
    return num & 0x0f;
}

inline uint16_t divu16d(uint16_t num, uint8_t deg) {
    deg = deg > 4 ? 4 : deg;
    return num >> (4 * deg);
}

uint16_t remu16d(uint16_t num, uint8_t deg) {
    uint16_t mask = 0x00;

    deg = deg > 4 ? 4 : deg;

    switch (deg) {
    case 1: mask = 0x0f; break;
    case 2: mask = 0xff; break;
    case 3: mask = 0x0fff; break;
    case 4: mask = 0xffff; break;
    }

    return num & mask;
}

// ****** USART INIT ******

void ubegin(const uint16_t baud) {
    uint16_t usart_speed = (uint16_t)(F_CPU / (16UL * baud) - 1UL);
    UBRR0H = (uint8_t)(usart_speed >> 8);
    UBRR0L = (uint8_t)usart_speed;

    UCSR0B = (1 << TXEN0);
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

// ****** USART PRINT STR ******

void usart_print_ch(const char ch) {
    if (ch == '\n') {
        while (!(UCSR0A & (1 << UDRE0)));
        UDR0 = '\r';
    }
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 =  ch;
}

void usart_print_str(PGM_P str) {
    char ch;
    while ((ch = pgm_read_byte(str))) {
        usart_print_ch(ch);
        str++;
    }
}

// ****** USART PRINT DEC ******

void usart_print_dec(const uint16_t num) {
    for (uint8_t deg = 4; deg > 0; deg--) {
        uint16_t divnum = divu10d(num, deg - 1);
        uint16_t rem = remu10(divnum);

        if (divnum == 0 && (deg - 1) != 0) continue;
        else usart_print_ch(('0' + rem));
    }
}

// ****** USART PRINT BIN ******

void usart_print_bin(const uint16_t num) {
    uint8_t deg = num > 0xff ? 16 : 8;

    usart_print_str(PSTR("0b"));
    for (; deg > 0; deg--) {
        uint16_t divnum = divu2d(num, deg - 1);
        uint16_t rem = remu2(divnum);

        usart_print_ch(('0' + rem));
        if (deg == 9) usart_print_ch(' ');
    }
}

// ****** USART PRINT HEX ******

 inline uint16_t hex_mask(const uint8_t num) {
    return num > 9 ? ('A' + (num - 10)) : ('0' + num);
}

void usart_print_hex(const uint16_t num) {
    uint8_t deg = num > 0xff ? 4 : 2;

    usart_print_str(PSTR("0x"));
    for (; deg > 0; deg--) {
        uint16_t divnum = divu16d(num, deg - 1);
        uint16_t rem = remu16(divnum);
        char hex_num = hex_mask(rem);

        usart_print_ch(hex_num);
    }
}

// ****** USART PRINT ******

void uprint_write(PGM_P fmt, uint8_t len, uint16_t *args) {
    uint8_t index = 0;
    char ch0, ch1;

    while ((ch0 = pgm_read_byte(fmt))) {
        fmt++;

        if (ch0 == '%' && index < len) {
            ch1 = pgm_read_byte(fmt);
            fmt++;

            switch (ch1) {
            case 'd': case 'D':
                usart_print_dec(args[index]);
                break;
            case 'b': case 'B':
                usart_print_bin(args[index]);
                break;
            case 'x': case 'X':
                usart_print_hex(args[index]);
                break;
            default:
                usart_print_ch(ch0);
                usart_print_ch(ch1);
                break;
            }

            index++;
        } else usart_print_ch(ch0);
    }
}