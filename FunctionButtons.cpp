//
//  FunctionButtons.cpp
//  
//
//  Created by Aduen on 5/7/15.
//  Copyright (c) 2015 Aduen. All rights reserved.
//

#include "FunctionButtons.h"

FunctionButtons::FunctionButtons(){
    n_btns = 0;
}

void FunctionButtons::run(){
    for (uint8_t i = 0; i < n_btns; ++i) {
        bool bs = digitalRead(btns[i].btn_pin);
        
        if(bs != btns[i].pstate){
            btns[i].pstate = bs;
            
            if(bs && b_call) b_call(i,BUTTON_UP);
            else b_call(i,BUTTON_DOWN);
            
            if(f_call && bs){
                btns[i].fstate = !btns[i].fstate;
                digitalWrite(btns[i].led_pin, btns[i].fstate);
                
                if(btns[i].fstate) f_call(i,FUNCTION_ON);
                else f_call(i,FUNCTION_OFF);
            }
        }
    }
}

bool FunctionButtons::func_state(uint8_t btnid){
    return btns[btnid].fstate;
}

void FunctionButtons::reset_fbutton(uint8_t btnid)
{
	btns[btnid].fstate = false;
	btns[btnid].pstate = true;
	digitalWrite(btns[btnid].led_pin, LOW);
}

uint8_t FunctionButtons::add_fbutton(uint8_t btn, uint8_t led){
    btns[n_btns].btn_pin = btn;
    btns[n_btns].led_pin = led;
    btns[n_btns].fstate = false;
    btns[n_btns].pstate = true;
    
    pinMode(btn, INPUT_PULLUP);
    pinMode(led, OUTPUT);
    digitalWrite(led, LOW);
    
    n_btns++;
    
    return n_btns-1;
}

void FunctionButtons::add_btn_listener(btncall_delegate l){
    b_call = l;
}

void FunctionButtons::add_function_listener(btncall_delegate l){
    f_call = l;
}
