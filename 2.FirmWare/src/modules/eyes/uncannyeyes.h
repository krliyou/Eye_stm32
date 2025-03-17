
#ifndef __UNCANNY_EYES_H
#define __UNCANNY_EYES_H

#include <rtdevice.h>
#include "drv_gc9a01.h"

#define HW_SCREEN_WIDTH 240
#define HW_SCREEN_HEIGHT 240

#define HIGH 0x1
#define LOW  0x0

void loop();
void setup(void);

#define SYMMETRICAL_EYELID

#endif