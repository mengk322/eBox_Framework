/**
  ******************************************************************************
  * @file    TFT9225.h
  * @author  cat_li
  * @version V1.0
  * @date    2019/06/09
  * @brief
  ******************************************************************************
  * @attention
  *
  * No part of this software may be used for any commercial activities by any form
  * or means, without the prior written consent of shentq. This specification is
  * preliminary and is subject to change at any time without notice. shentq assumes
  * no responsibility for any errors contained herein.
  * <h2><center>&copy; Copyright 2015 shentq. All Rights Reserved.</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_ILI9225_H
#define __LCD_ILI9225_H

#include "ebox_core.h"
#include "font.h"

#define X_MAX_PIXEL	        128
#define Y_MAX_PIXEL	        160

//本程序适用eBox
//              GND   电源地
//              VCC   接5V或3.3v电源
//              SCL   接PA5（SCL）
//              SDA   接PA7（SDA）
//              RES   接PB3 (RST)
//              DC    接PB4 (RS)
//              CS    接PB5
//              BL    接PB6


class Lcd : public Vhmi
{
public:
    uint8_t MADCTL;
    int16_t front_color;
    int16_t back_color;
    TEXT_MODE_TYPE text_mode;
public:
    Lcd(Gpio *cs, Gpio *led, Gpio *rs, Gpio *rst, Spi *spi)
    {
        this->cs = cs;
        this->led = led;
        this->rs = rs;
        this->rst = rst;
        this->spi = spi;
    }
    void begin(void);
    void soft_reset(void);
    void clear(uint16_t Color);
    void on();
    void off();
    void column_order(uint8_t order);
    void row_order(uint8_t order);

    void set_xy(int16_t x, int16_t y);


    virtual void draw_pixel(int16_t x, int16_t y, uint32_t color);
    virtual void draw_h_line(int16_t x0, int16_t y0, int16_t x1, uint32_t color);
    virtual void draw_v_line(int16_t x0, int16_t y0, int16_t y1, uint32_t color);
    virtual void draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color);
    virtual void fill_rect  (int16_t x0, int16_t y0,  int16_t x1, int16_t y1, uint32_t color);
    virtual void fill_rect  (int16_t x0, int16_t y0,  int16_t x1, int16_t y1, uint16_t *bitmap);
    virtual void fill_screen(uint32_t color);
    virtual void draw_circle(int16_t x, int16_t y, int16_t r, uint32_t color);



    int16_t read_point(int16_t x, int16_t y);
    void h_disp_char8x16(int16_t x, int16_t y, uint8_t ch);
    void disp_char8x16(int16_t x, int16_t y, uint8_t ch);
    void printf(int16_t x, int16_t y, const char *fmt, ...);
    void draw_font_gbk16(int16_t x, int16_t y, uint8_t *s);

    void draw_bitmap(const unsigned char *p); //显示40*40 QQ图片


private:
#define TFTLCD_CS  PGout(14)
#define TFTLCD_RST PGout(15) 	
#define TFTLCD_RD  PAout(8)     //rs
#define TFTLCD_WR  PBout(4)		  
#define TFTLCD_RS  PBout(3)	   //rd
    Gpio *cs;
    Gpio *rst;
    Gpio *rd;
    Gpio *rs;
    Gpio *wr;


    Spi::Config_t config;
    uint16_t width, height;
    uint8_t initialized;

    void reset(void);
    void init(void);
    void spi_write_data(uint8_t Data);
    void write_index(uint8_t Index);
    void write_data_8bit(uint8_t Data);
    void write_data_16bit(uint16_t Data);
    uint8_t read_8bit();
    int16_t read_16bit();

    void write_reg(uint8_t Index, uint8_t Data);
    uint8_t   read_reg(uint8_t Index);

    void set_region(int16_t x_start, int16_t y_start, int16_t x_end, int16_t y_end);

};
#endif
