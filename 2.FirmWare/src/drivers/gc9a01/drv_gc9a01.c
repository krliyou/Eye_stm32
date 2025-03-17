
#include <rtdevice.h>
#include <drv_gpio.h>
#include <board.h>
#include <drv_spi.h>
#include "drv_gc9a01.h"

#define LOG_TAG             "drv.lcd"
//#define DBG_LEVEL           DBG_LOG
#include <rtdbg.h>

static struct rt_spi_device *spi_dev_lcd;

void lcd_write_data(const rt_uint8_t date)
{
    rt_uint8_t i;
    rt_size_t len;

    rt_pin_write(LCD_CS_PIN, PIN_LOW);
   
    len = rt_spi_send(spi_dev_lcd, &date, 1);

    if (len != 1)
    {
        LOG_D("drv_gc9a01: _write_data error. %d\r\n", len);
    }
    else
    {
        LOG_D("drv_gc9a01: _write_data done\r\n");
    }

    rt_pin_write(LCD_CS_PIN, PIN_HIGH);
}

void lcd_write_data16(const rt_uint16_t date)
{
    lcd_write_data(date >> 8);
    lcd_write_data(date);
}

void lcd_write_cmd(const rt_uint8_t date)
{
    rt_pin_write(LCD_DC_PIN, PIN_LOW);
    lcd_write_data(date);
    rt_pin_write(LCD_DC_PIN, PIN_HIGH);
}

static int rt_hw_lcd_config(void)
{
    spi_dev_lcd = (struct rt_spi_device *)rt_device_find(OLED_GC9A01_SPI_DEVICE);

    {
        struct rt_spi_configuration cfg = {0};
        cfg.data_width = 8;
        cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_3 | RT_SPI_MSB | RT_SPI_NO_CS;
        cfg.max_hz = 42 * 1000 * 1000; /* 42M,SPI max 42MHz,lcd 4-wire spi */

        rt_spi_configure(spi_dev_lcd, &cfg);
    }

    return RT_EOK;
}

static void lcd_gpio_init(void)
{
    rt_hw_lcd_config();

    rt_pin_mode(LCD_RES_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LCD_DC_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LCD_CS_PIN, PIN_MODE_OUTPUT);

    rt_pin_write(LCD_RES_PIN, PIN_LOW);
    rt_thread_mdelay(RT_TICK_PER_SECOND / 10);
    rt_pin_write(LCD_RES_PIN, PIN_HIGH);
    rt_thread_mdelay(RT_TICK_PER_SECOND / 10);
    rt_pin_write(LCD_BLK_PIN, PIN_HIGH);
    rt_thread_mdelay(RT_TICK_PER_SECOND / 10);
}

/**
 * Set drawing area
 *
 * @param   x1      start of x position
 * @param   y1      start of y position
 * @param   x2      end of x position
 * @param   y2      end of y position
 *
 * @return  void
 */
void lcd_address_set(rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2)
{
    lcd_write_cmd(0x2a); // 列地址设置
    lcd_write_data16(x1);
    lcd_write_data16(x2);

    lcd_write_cmd(0x2b); // 行地址确定
    lcd_write_data16(y1);
    lcd_write_data16(y2);
    
    lcd_write_cmd(0x2c); // 存储器写
}

/**
 * full color array on the lcd.
 *
 * @param   x_start     start of x position
 * @param   y_start     start of y position
 * @param   x_end       end of x position
 * @param   y_end       end of y position
 * @param   color       Fill color array's pointer
 *
 * @return  void
 */
void lcd_fill_array(rt_uint16_t x_start, rt_uint16_t y_start, \
                        rt_uint16_t x_end, rt_uint16_t y_end, rt_uint16_t color)
{
    rt_uint16_t i, j;

    lcd_address_set(x_start, y_start, x_end - 1, y_end - 1);

    for (i = y_start; i < y_end; i++)
    {
        for (j = x_start; j < x_end; j++)
        {
            lcd_write_data16(color);
        }
    }
}

/**
 * display picture
 *
 * @param   x_start     start of x position
 * @param   y_start     start of y position
 * @param   length      picture length
 * @param   width       picture width
 * @param   pic[]       picture arry
 *
 * @return  void
 */
void lcd_show_picture(rt_uint16_t x_start, rt_uint16_t y_start, \
                        rt_uint16_t length, rt_uint16_t width, const rt_uint8_t pic[])
{
    rt_uint16_t i, j;
    rt_uint32_t k = 0;

    lcd_address_set(x_start, y_start, x_start + length - 1, y_start + width - 1);

    for (i = 0; i < length; i++)
    {
        for (j = 0; j < width; j++)
        {
            lcd_write_data(pic[k * 2]);
            lcd_write_data(pic[k * 2 + 1]);
            k++;
        }
    }
}

int rt_hw_lcd_init(void)
{
    static struct rt_spi_device spi_dev_lcd;
    
    rt_spi_bus_attach_device(&spi_dev_lcd, OLED_GC9A01_SPI_DEVICE, OLED_GC9A01_SPI_BUS, NULL);

    lcd_gpio_init();

    lcd_write_cmd(0xEF);
    lcd_write_cmd(0xEB);
    lcd_write_data(0x14);

    lcd_write_cmd(0xFE);
    lcd_write_cmd(0xEF);

    lcd_write_cmd(0xEB);
    lcd_write_data(0x14);

    lcd_write_cmd(0x84);
    lcd_write_data(0x40);

    lcd_write_cmd(0x85);
    lcd_write_data(0xFF);

    lcd_write_cmd(0x86);
    lcd_write_data(0xFF);

    lcd_write_cmd(0x87);
    lcd_write_data(0xFF);

    lcd_write_cmd(0x88);
    lcd_write_data(0x0A);

    lcd_write_cmd(0x89);
    lcd_write_data(0x21);

    lcd_write_cmd(0x8A);
    lcd_write_data(0x00);

    lcd_write_cmd(0x8B);
    lcd_write_data(0x80);

    lcd_write_cmd(0x8C);
    lcd_write_data(0x01);

    lcd_write_cmd(0x8D);
    lcd_write_data(0x01);

    lcd_write_cmd(0x8E);
    lcd_write_data(0xFF);

    lcd_write_cmd(0x8F);
    lcd_write_data(0xFF);

    lcd_write_cmd(0xB6);
    lcd_write_data(0x00);
    lcd_write_data(0x20);

    lcd_write_cmd(0x36);
    if (USE_HORIZONTAL == 0)
    {
        lcd_write_data(0x08);
    }
    else if (USE_HORIZONTAL == 1)
    {
        lcd_write_data(0xC8);
    }
    else if (USE_HORIZONTAL == 2)
    {
        lcd_write_data(0x68);
    }
    else
    {
        lcd_write_data(0xA8);
    }

    lcd_write_cmd(0x3A);
    lcd_write_data(0x05);

    lcd_write_cmd(0x90);
    lcd_write_data(0x08);
    lcd_write_data(0x08);
    lcd_write_data(0x08);
    lcd_write_data(0x08);

    lcd_write_cmd(0xBD);
    lcd_write_data(0x06);

    lcd_write_cmd(0xBC);
    lcd_write_data(0x00);

    lcd_write_cmd(0xFF);
    lcd_write_data(0x60);
    lcd_write_data(0x01);
    lcd_write_data(0x04);

    lcd_write_cmd(0xC3);
    lcd_write_data(0x13);
    lcd_write_cmd(0xC4);
    lcd_write_data(0x13);

    lcd_write_cmd(0xC9);
    lcd_write_data(0x22);

    lcd_write_cmd(0xBE);
    lcd_write_data(0x11);

    lcd_write_cmd(0xE1);
    lcd_write_data(0x10);
    lcd_write_data(0x0E);

    lcd_write_cmd(0xDF);
    lcd_write_data(0x21);
    lcd_write_data(0x0c);
    lcd_write_data(0x02);

    lcd_write_cmd(0xF0);
    lcd_write_data(0x45);
    lcd_write_data(0x09);
    lcd_write_data(0x08);
    lcd_write_data(0x08);
    lcd_write_data(0x26);
    lcd_write_data(0x2A);

    lcd_write_cmd(0xF1);
    lcd_write_data(0x43);
    lcd_write_data(0x70);
    lcd_write_data(0x72);
    lcd_write_data(0x36);
    lcd_write_data(0x37);
    lcd_write_data(0x6F);

    lcd_write_cmd(0xF2);
    lcd_write_data(0x45);
    lcd_write_data(0x09);
    lcd_write_data(0x08);
    lcd_write_data(0x08);
    lcd_write_data(0x26);
    lcd_write_data(0x2A);

    lcd_write_cmd(0xF3);
    lcd_write_data(0x43);
    lcd_write_data(0x70);
    lcd_write_data(0x72);
    lcd_write_data(0x36);
    lcd_write_data(0x37);
    lcd_write_data(0x6F);

    lcd_write_cmd(0xED);
    lcd_write_data(0x1B);
    lcd_write_data(0x0B);

    lcd_write_cmd(0xAE);
    lcd_write_data(0x77);

    lcd_write_cmd(0xCD);
    lcd_write_data(0x63);

    lcd_write_cmd(0x70);
    lcd_write_data(0x07);
    lcd_write_data(0x07);
    lcd_write_data(0x04);
    lcd_write_data(0x0E);
    lcd_write_data(0x0F);
    lcd_write_data(0x09);
    lcd_write_data(0x07);
    lcd_write_data(0x08);
    lcd_write_data(0x03);

    lcd_write_cmd(0xE8);
    lcd_write_data(0x34);

    lcd_write_cmd(0x62);
    lcd_write_data(0x18);
    lcd_write_data(0x0D);
    lcd_write_data(0x71);
    lcd_write_data(0xED);
    lcd_write_data(0x70);
    lcd_write_data(0x70);
    lcd_write_data(0x18);
    lcd_write_data(0x0F);
    lcd_write_data(0x71);
    lcd_write_data(0xEF);
    lcd_write_data(0x70);
    lcd_write_data(0x70);

    lcd_write_cmd(0x63);
    lcd_write_data(0x18);
    lcd_write_data(0x11);
    lcd_write_data(0x71);
    lcd_write_data(0xF1);
    lcd_write_data(0x70);
    lcd_write_data(0x70);
    lcd_write_data(0x18);
    lcd_write_data(0x13);
    lcd_write_data(0x71);
    lcd_write_data(0xF3);
    lcd_write_data(0x70);
    lcd_write_data(0x70);

    lcd_write_cmd(0x64);
    lcd_write_data(0x28);
    lcd_write_data(0x29);
    lcd_write_data(0xF1);
    lcd_write_data(0x01);
    lcd_write_data(0xF1);
    lcd_write_data(0x00);
    lcd_write_data(0x07);

    lcd_write_cmd(0x66);
    lcd_write_data(0x3C);
    lcd_write_data(0x00);
    lcd_write_data(0xCD);
    lcd_write_data(0x67);
    lcd_write_data(0x45);
    lcd_write_data(0x45);
    lcd_write_data(0x10);
    lcd_write_data(0x00);
    lcd_write_data(0x00);
    lcd_write_data(0x00);

    lcd_write_cmd(0x67);
    lcd_write_data(0x00);
    lcd_write_data(0x3C);
    lcd_write_data(0x00);
    lcd_write_data(0x00);
    lcd_write_data(0x00);
    lcd_write_data(0x01);
    lcd_write_data(0x54);
    lcd_write_data(0x10);
    lcd_write_data(0x32);
    lcd_write_data(0x98);

    lcd_write_cmd(0x74);
    lcd_write_data(0x10);
    lcd_write_data(0x85);
    lcd_write_data(0x80);
    lcd_write_data(0x00);
    lcd_write_data(0x00);
    lcd_write_data(0x4E);
    lcd_write_data(0x00);

    lcd_write_cmd(0x98);
    lcd_write_data(0x3e);
    lcd_write_data(0x07);

    lcd_write_cmd(0x35);
    lcd_write_cmd(0x21);

    lcd_write_cmd(0x11);
    rt_thread_mdelay(120);
    lcd_write_cmd(0x29);
    rt_thread_mdelay(20);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_lcd_init);
