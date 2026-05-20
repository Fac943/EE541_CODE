#include "NUCLEO.h"

void BUTTON_CONFIG(void){ //sets PC13 to input with pull-up
    BUTTON_PORT->MODER &= ~(GPIO_MODER_MODE13);
    BUTTON_PORT->PUPDR &= ~(GPIO_PUPDR_PUPD13);  
}
void WAIT_FOR_BUTTON_PRESS(void){//infinite loop that only breaks when button is pressed
    while(BUTTON_PRESS){
        ;        
    }
    while(!BUTTON_PRESS){       //wait for release to continue
        ;
    }
}