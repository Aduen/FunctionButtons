//
//  FunctionButtons.h
//  TASST_REV4_5V
//
//  Created by Aduen on 5/7/15.
//  Copyright (c) 2015 Aduen. All rights reserved.
//

#ifndef TASST_REV4_5V_FunctionButtons_h
#define TASST_REV4_5V_FunctionButtons_h

#include <Arduino.h>
#include "utility/FastDelegate.h"

using namespace fastdelegate;
typedef FastDelegate2<uint8_t,uint8_t> btncall_delegate;

typedef struct {
    uint8_t btn_pin;
    uint8_t led_pin;
    bool pstate;
    bool fstate;
    
} btn_struct;

class FunctionButtons {
public:
    const uint8_t static BUTTON_UP = 1;
    const uint8_t static BUTTON_DOWN = 2;
    const uint8_t static FUNCTION_ON = 3;
    const uint8_t static FUNCTION_OFF = 4;
    
    FunctionButtons();
    
    uint8_t add_fbutton(uint8_t btn, uint8_t led);
    
    bool func_state(uint8_t btnid);

    void add_btn_listener(btncall_delegate l);
    void add_function_listener(btncall_delegate l);
    void run();
    
private:
    btncall_delegate f_call;
    btncall_delegate b_call;
    btn_struct btns[3];
    uint8_t n_btns;
    
};

#endif