/*
 * File:   main.c
 * Author: Shri Surya
 * Project - Car Black Box
 * Created on 17 May, 2024, 8:02 PM
 */

#include <xc.h> 
#include "clcd.h"
#include "adc.h"
#include "matrix_keypad.h"

unsigned char *gear[] = {"ON","GR","GN","G1","G2","G3","G4"};
char i = 0;
unsigned char flag = 0 ;
void check_matrix_keypad(void)
{
    unsigned char key;
    key = read_switches(STATE_CHANGE) ;
    if (key == MK_SW2) 
    {
        if (i > 5) {
            i = 5;
        } 
        i++ ;
        if(flag)
        {
            i = 2 ;
            flag = 0;
        }
        clcd_print(gear[i],LINE2(9));
    } 
    else if (key == MK_SW3) {
        i-- ;
        if(flag)
        {
            i = 2 ;
            flag = 0;
        }
       if (i < 1) {
            i = 1;
        }   
        clcd_print(gear[i],LINE2(9));
    } 
    else if (key == MK_SW1) {
        clcd_print("-C", LINE2(9));
        flag = 1;
    } 
    
}


void init_config(void) {
    init_clcd();
    init_adc();
    init_matrix_keypad();
}

void main(void) {
    init_config();
    char time[9] = "00:00:00"; 
    short pot_value;
    clcd_print(gear[0], LINE2(9));
    while (1) {
        clcd_print("TIME   EV  SP", LINE1(2));
        pot_value = ((((read_adc(CHANNEL4)) * ((float)5/1024)) * 1000) / 10);
        clcd_print(time, LINE2(0));  
        clcd_putch((pot_value/10%10) + 48 , LINE2(13));
        clcd_putch((pot_value%10) + 48 , LINE2(14));
     
        check_matrix_keypad();
        

    }
    return;
}
