#ifndef _KEY_H_
#define _KEY_H_

#include "headfile.h"

//拨码开关状态变量
extern uint8 sw1_status;
extern uint8 sw2_status;

//开关状态变量
extern uint8 key1_status ;
extern uint8 key2_status ;
extern uint8 key3_status ;
extern uint8 key4_status ;

//上一次开关状态变量
extern uint8 key1_last_status;
extern uint8 key2_last_status;
extern uint8 key3_last_status;
extern uint8 key4_last_status;

//开关标志位
extern uint8 key1_flag;
extern uint8 key2_flag;
extern uint8 key3_flag;
extern uint8 key4_flag;



extern int Dispay_Codename;       //显示页面代号
extern int This_Codename;			//本页面编号
extern uint8 KeystrokeLabel;
extern uint8 CursorRow; //光标所在行号
extern uint8 MenuNextFlag;



void Keystroke_Scan(void);

void KeystrokeLabel_Switch(float change_unit, uint8 value_bit);
void Keystroke_Special_Value(int* parameter);

void Cursor(void);
void Keystroke_Menu(void);
void Keystroke_Menu_HOME(void);

void Menu_ONE_Display(uint8 control_line);
void Keystroke_Menu_ONE(void);
void Keystroke_Menu_ONE_One(void);
void Keystroke_Menu_ONE_Two(void); 
void Keystroke_Menu_ONE_Three(void);
void Keystroke_Menu_ONE_Four(void);

void Menu_TWO_Display(uint8 control_line);
void Keystroke_Menu_TWO(void);
void Keystroke_Menu_TWO_One(void);
void Keystroke_Menu_TWO_Two(void);
void Keystroke_Menu_TWO_Three(void);
void Keystroke_Menu_TWO_Four(void);




void Menu_THREE_Display(uint8 control_line);
void Keystroke_Menu_THREE(void);
void Keystroke_Menu_THREE_One(void);
void Keystroke_Menu_THREE_Two(void);
void Keystroke_Menu_THREE_Three(void);
void Keystroke_Menu_THREE_Four(void);

void Keystroke_Menu_FOUR(void);

void Menu_FIVE_Display(uint8 control_line);
void Keystroke_Menu_FIVE(void);
void Keystroke_Menu_FIVE_One(void);
void Keystroke_Menu_FIVE_Two(void);
void Keystroke_Menu_FIVE_Three(void);
void Keystroke_Menu_FIVE_Four(void);

#endif