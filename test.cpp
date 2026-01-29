#include <Arduino.h>
#include <uprintf.h>

// void setup() {
//   Terminal::ubegin(9600);

//   // uint16_t nums[] = {100, 2234, 570};
//   // uint8_t len = sizeof(nums) / sizeof(uint16_t);
//   // uprint_write(PSTR("SSS: %D, %b, %x\n"), len, nums);

//   // uprintf("SSS: %D, %b, %x\n");

//   Terminal::uprintf("SSS: %D, %b, %x\n", 100, 2234, 570);
//   // uprintf("SSS: %D, %b, %x\n", 100, 2234, 570);
//   // uprintf("SSS: %D, %b, %x\n", 100, 2234, 570);
//   // uprintf("SSS: %D, %b, %x\n", 100, 2234, 570);

//   // uprintf("SSS: %D, %b, %x\n", 100, 2234, 570);
//   // uprintf("SSS: %D, %b, %x\n", 100, 2234, 570);
//   // uprintf("SSS: %D, %b, %x\n", 100, 2234, 570);
//   // uprintf("SSS: %D, %b, %x\n", 100, 2234, 570);

//   // uprintf("SSS: %D, %b, %x\n", 100, 2234, 570);
//   // uprintf("SSS: %D, %b, %x\n", 100, 2234, 570);
//   // uprintf("SSS: %D, %b, %x\n", 100, 2234, 570);
//   // uprintf("SSS: %D, %b, %x\n", 100, 2234, 570);
// }

// void loop() {}

int main(void) {
  ubegin(9600);
  uprintf("SSS: %D, %b, %x\n", 100, 2234, 570);

  return 0;
}