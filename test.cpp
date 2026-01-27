#include <Arduino.h>
#include <uprintf.h>

void setup() {
  ubegin(9600);

  uprintf("SSS: %D, %b, %x\n");
  uprintf("SSS: %D, %b, %x\n", 100, 2234, 570);
  uprintf("SSS: %D, %b, %x\n", 100, 2234, 570);
  uprintf("SSS: %D, %b, %x\n", 100, 2234, 570);
  uprintf("SSS: %D, %b, %x\n", 100, 2234, 570);
}

void loop() {}