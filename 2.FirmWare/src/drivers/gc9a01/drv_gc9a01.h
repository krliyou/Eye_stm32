
#ifndef __DRV_OLED_H__
#define __DRV_OLED_H__

#include <rtthread.h>
#include <board.h>

#define OLED_GC9A01_SPI_BUS "spi2"
#define OLED_GC9A01_SPI_DEVICE "spi20"

#define LCD_SCL_PIN GET_PIN(I, 1)
#define LCD_SDA_PIN GET_PIN(I, 3)
#define LCD_RES_PIN GET_PIN(H, 13)
#define LCD_DC_PIN  GET_PIN(H, 15)
#define LCD_CS_PIN  GET_PIN(A, 15)
#define LCD_BLK_PIN GET_PIN(A, 8)

#define LCD_SCLK_Clr() rt_pin_write(LCD_SCL_PIN, PIN_LOW)       // SCL=SCLK
#define LCD_SCLK_Set() rt_pin_write(LCD_SCL_PIN, PIN_HIGH)

#define LCD_MOSI_Clr() rt_pin_write(LCD_SDA_PIN, PIN_LOW)       // SDA=MOSI
#define LCD_MOSI_Set() rt_pin_write(LCD_SDA_PIN, PIN_HIGH)

#define LCD_RES_Clr() rt_pin_write(LCD_RES_PIN, PIN_LOW)        // RES
#define LCD_RES_Set() rt_pin_write(LCD_RES_PIN, PIN_HIGH)

#define LCD_DC_Clr() rt_pin_write(LCD_DC_PIN, PIN_LOW)          // DC
#define LCD_DC_Set() rt_pin_write(LCD_DC_PIN, PIN_HIGH)

#define LCD_CS_Clr() rt_pin_write(LCD_CS_PIN, PIN_LOW)          // CS
#define LCD_CS_Set() rt_pin_write(LCD_CS_PIN, PIN_HIGH)

#define LCD_BLK_Clr() rt_pin_write(LCD_BLK_PIN, PIN_LOW)        // BLK
#define LCD_BLK_Set() rt_pin_write(LCD_BLK_PIN, PIN_HIGH)

#define USE_HORIZONTAL 0                                        // 0或者1为竖屏，2或3为横屏

void lcd_fill_array(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, \
                        rt_uint16_t y_end, rt_uint16_t color);

void lcd_show_picture(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t length, \
                        rt_uint16_t width, const rt_uint8_t pic[]);

void lcd_address_set(rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2);

void lcd_write_data(const rt_uint8_t date);

void lcd_write_data16(rt_uint16_t date);

void lcd_write_cmd(const rt_uint8_t dat);

#endif
