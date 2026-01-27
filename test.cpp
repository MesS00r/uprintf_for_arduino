// #include <Arduino.h>
// #include <avr/io.h>
#include <uprintf.h>

// void setup() {
//   ubegin(9600);

//   uprintf("SSS: %d\n", 100);
// }

// void loop() {

// }

int main(void) {
  ubegin(9600);

  // uint16_t nums[] = {0, 2234, 570};
  // _uprintf("SSS: %D, %b, %x\n", sizeof(nums) / sizeof(uint16_t), nums);

  uprintf(PSTR("SSS: %D, %b, %x\n"), 100, 2234, 570);
  uprintf(PSTR("SSS: %D, %b, %x\n"), 100, 2234, 570);
  uprintf(PSTR("SSS: %D, %b, %x\n"), 100, 2234, 570);
  uprintf(PSTR("SSS: %D, %b, %x\n"), 100, 2234, 570);

  return 0;
}