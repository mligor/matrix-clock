#include <Arduino.h>

enum StatusLedMode {
    slmOn,
    slmOff,
    slmBlinkFast,
    slmBlinkMiddle,
    slmBlinkSlow
};

void status_led(int pin, StatusLedMode mode);
