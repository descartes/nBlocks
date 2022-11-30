
// Sample Ping-Pong for nRF24L01 radio

// Some version tracking info
#define VER_NUM "v1.2"
#define VER_DATE "2022-11-29"
#define VERSION "nBlocks " VER_NUM " " VER_DATE

// Required includes
#include "mbed.h"
#include "nBlocks.h"

#define WAIT_TIME_MS 500

DigitalOut led0(RC0);
AnalogIn TMP36(RA2);
DigitalIn SendBtn(RD0, PullDown);

int main() {
  // Show firmware version & when it was created
  printf("\n\n########################################\n\n");
  printf(VERSION "\n\n");
  printf("Compiled " __DATE__ " " __TIME__);
  printf("Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
  printf("\n\n########################################\n\n");


  // Each STM32 has a unique 96 bit number
  uint32_t *uid = (uint32_t *)0x1FFFF7E8;
  printf("Unique Id    : 0x%X 0x%X 0x%X\n", uid[0], uid[1], uid[2]);
  // This is a useful way of identifying different radio nodes

  uint8_t SendBtnWasPressed = 0;

  // The super loop ...
  while (true) {

    printf("\n\nTop of loop ...\n"); // Say we are doing it

    led0 = !led0;
    thread_sleep_for(WAIT_TIME_MS);

    // If button is now pressed and wasn't previously pressed
    if ((SendBtn == 1) & (SendBtnWasPressed == 0)) {
      SendBtnWasPressed = 1; // Set the flag to say the button was pressed

      printf("Sending ...\n"); // Say we are doing it

      uint16_t rawTemperature = TMP36;

      //   txData[0] = (uint8_t)((rawTemperature >> 8) & 0xFF);
      //   txData[1] = (uint8_t)(rawTemperature & 0xFF);

      printf("Sending: ");

      // If button is pressed and was previously pressed
    } else if ((SendBtn == 1) & (SendBtnWasPressed == 1)) {
      // Don't send
      printf("Don't send\n");

      // If button is not pressed and was previously pressed
    } else if ((SendBtn == 0) & (SendBtnWasPressed == 1)) {
      SendBtnWasPressed = 0; // Reset the flag
      printf("Reset\n");

      // If button is not pressed and was not previously pressed
    } else if ((SendBtn == 0) & (SendBtnWasPressed == 0)) {
      // Nothing to do
      printf("Nowt\n");

    } // SendBtn & SendBtnWasPressed??

  } // while forever / true

} // main
