//#include <Arduino.h>

//#include <SPI.h>
#include <TFT_eSPI.h>       // Hardware-specific library
#include <lvgl.h>
// #include <demos/lv_demos.h>
#include "CST816T.h"
//#include "ui.h"
//#include "demos/benchmark/lv_demo_benchmark.h"
#include <examples/lv_examples.h>


/**
TFT屏幕               ESP32DEVKIT V1
ST7789v:
1->GND ------------------ GND
3->VCC ------------------ 3V3
2->BLC ------------------ D16
7->DC  ----------------- D2
8->CS  ------------------ D5
9->SCK ------------------ D18
10->MOSI -------------- D23
11->RES -------------- D4

CST816T:
13->SCL ------------------ D22
14->SDA ------------------ D21
15->RST ------------------ D12
16->INT ------------------ D13
*/
#define I2C_SDA 21
#define I2C_SCL 22
#define RST_N_PIN 12
#define INT_N_PIN -1

// 触摸
//CST816T cst816t(I2C_SDA, I2C_SCL, RST_N_PIN, INT_N_PIN);
CST816T cst816t(I2C_SDA, I2C_SCL);

// TFT_eSPI默认使用硬件SPI（GPIO18/23/5），而ST7789v_arduino中您定义了
TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

hw_timer_t *tim1 = NULL;
/*Change to your screen resolution*/
static const uint32_t screenWidth = 240;
static const uint32_t screenHeight = 280;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * screenHeight / 2];
// static lv_color_t buf[screenWidth * 10];

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
//    Serial.println("my_disp_flush start");
    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    TouchInfos tp;
    tp = cst816t.GetTouchInfo();
    // bool touched = (tp.touching == 1&&tp.isValid == 1);
    bool touched = tp.touching;

    if (!touched)
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;

        /*Set the coordinates*/
        data->point.x = tp.x;
        data->point.y = tp.y;

        Serial.printf("touchX = %d, touchY = %d\n", tp.x, tp.y);
    }
}

void tim1Interrupt()
{
    lv_tick_inc(1);
}

void lvgl_handler(void *pvParameters)
{
	while(1)
	{
        lv_timer_handler(); /* let the GUI do its work */
        delay(5);
	}
}

void setup()
{
    Serial.begin(115200); /* prepare for possible serial debug */
    Serial.println("Hello Arduino! (V8.0.X)");
    Serial.printf("TFT_CS: %d, TFT_DC: %d, TFT_RST: %d, TFT_BL: %d\n", TFT_CS, TFT_DC, TFT_RST, TFT_BL);
    // 配置引脚10为输出模式并拉低，可能用于控制外设（如复位信号或使能信号）。
    // 注意：pinMode()必须在digitalWrite()前调用
//    pinMode(TFT_BL, OUTPUT);
//    digitalWrite(TFT_BL, LOW);  // 开启背光

    tft.init();

    // 显示屏背光控制（PWM调光）
    // 使用ESP32的LEDC（LED PWM控制器）控制屏幕背光亮度
//    ledcSetup(1, 5000, 10);      // 配置LEDC通道1：频率5kHz，分辨率10位（0-1023）
//    ledcAttachPin(TFT_BL, 1);        // 将GPIO14绑定到LEDC通道1
//    analogReadResolution(10);    // 设置ADC分辨率为10位（可选，可能与背光传感器相关）
//    ledcWrite(1, 200);           // 设置背光PWM占空比为200/1023≈19.5%亮度


    // 复位触摸芯片
//    pinMode(RST_N_PIN, OUTPUT);
//    digitalWrite(RST_N_PIN, LOW);
//    delay(50);
//    digitalWrite(RST_N_PIN, HIGH);
//    Wire.begin(I2C_SDA, I2C_SCL);
    // 触摸
    cst816t.begin();


    // 调用TFT库（如Adafruit_ST7735或TFT_eSPI）的初始化函数，
    // 配置屏幕驱动芯片（如ST7789）
    // 通常包括SPI通信、分辨率设置和颜色模式配置
    tft.fillScreen(TFT_BLUE);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("Hello ESP32", 20, 50, 2);


    lv_init();

    lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * screenHeight / 2);
    // lv_disp_draw_buf_init(&draw_buf, buf1, buf2, screenWidth * 100);

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    // source tick for lvgl
    tim1 = timerBegin(0, 80, true);
    timerAttachInterrupt(tim1, tim1Interrupt, true);
    timerAlarmWrite(tim1, 1000, true);
    timerAlarmEnable(tim1);

#if 0
    Serial.println("ui_init start");
    ui_init();
    /* Create simple label */
//    lv_obj_t *label = lv_label_create( lv_scr_act() );
//    lv_label_set_text( label, "LVGL_Arduino");
//    lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );
    Serial.println("ui_init done");
#else
    /* Try an example from the lv_examples Arduino library
       make sure to include it as written above.
    */
//    lv_example_btn_1();
//    lv_example_btn_2();
//    lv_example_list_1();
//    lv_example_list_2();
//    lv_example_arc_1();
//    lv_example_menu_1();
//    lv_example_anim_1();

    // uncomment one of these demos
//     lv_demo_widgets(); // OK
//    lv_demo_benchmark();          // OK
//     lv_demo_keypad_encoder();     // works, but I haven't an encoder
//     lv_demo_music();              // NOK
//     lv_demo_printer();
//     lv_demo_stress();             // seems to be OK
#endif
    Serial.println("Setup done");

    xTaskCreate(lvgl_handler, "lvgl_handler", 4096, NULL, 2, NULL);
}

void loop()
{
//    if (cst816t.GetTouchInfo().isValid) {
//        Serial.print("X: "); Serial.print(cst816t.GetTouchInfo().x);
//        Serial.print(" Y: "); Serial.println(cst816t.GetTouchInfo().y);
//    }
//    Serial.println("LOOP ");
//    Serial.printf("TFT_CS: %d, TFT_DC: %d, TFT_RST: %d, TFT_BL: %d\n", TFT_CS, TFT_DC, TFT_RST, TFT_BL);
    delay(1);
}