// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.0 Beta1
// LVGL VERSION: 8.2
// PROJECT: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void ui_event_Screen1(lv_event_t * e);
lv_obj_t * ui_Screen1;
lv_obj_t * ui_Label1;
void ui_event_Image1(lv_event_t * e);
lv_obj_t * ui_Image1;
void ui_event_Screen2(lv_event_t * e);
lv_obj_t * ui_Screen2;
void ui_event_Image2(lv_event_t * e);
lv_obj_t * ui_Image2;

///////////////////// TEST LVGL SETTINGS ////////////////////
//#if LV_COLOR_DEPTH != 16
//    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
//#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_Screen1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Screen2, LV_SCR_LOAD_ANIM_FADE_ON, 500, 400);
    }
}
void ui_event_Image1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Screen2, LV_SCR_LOAD_ANIM_FADE_ON, 50, 400);
    }
}
void ui_event_Screen2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 500, 400);
    }
}
void ui_event_Image2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 50, 400);
    }
}

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label1 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label1, 157);
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 60
    lv_obj_set_x(ui_Label1, 3);
    lv_obj_set_y(ui_Label1, -104);
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_Label1, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_Label1, "this is a good day,I want  go to exit! ");
    lv_obj_set_scrollbar_mode(ui_Label1, LV_SCROLLBAR_MODE_OFF);

    ui_Image1 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image1, &ui_img_game3_png);
    lv_obj_set_width(ui_Image1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_color(ui_Image1, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Image1, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Image1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Image1, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Image1, ui_event_Image1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Screen1, ui_event_Screen1, LV_EVENT_ALL, NULL);

}
void ui_Screen2_screen_init(void)
{
    ui_Screen2 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image2 = lv_img_create(ui_Screen2);
    lv_img_set_src(ui_Image2, &ui_img_stopwatch2_png);
    lv_obj_set_width(ui_Image2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Image2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_add_event_cb(ui_Image2, ui_event_Image2, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Screen2, ui_event_Screen2, LV_EVENT_ALL, NULL);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    ui_Screen2_screen_init();
    lv_disp_load_scr(ui_Screen1);
}
