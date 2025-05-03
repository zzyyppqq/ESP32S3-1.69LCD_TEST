// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.0 Beta1
// LVGL VERSION: 8.2
// PROJECT: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

void ui_event_Screen1(lv_event_t * e);
extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_Label1;
void ui_event_Image1(lv_event_t * e);
extern lv_obj_t * ui_Image1;
void ui_event_Screen2(lv_event_t * e);
extern lv_obj_t * ui_Screen2;
void ui_event_Image2(lv_event_t * e);
extern lv_obj_t * ui_Image2;


LV_IMG_DECLARE(ui_img_game3_png);    // assets\game3.png
LV_IMG_DECLARE(ui_img_stopwatch2_png);    // assets\stopwatch2.png




void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
