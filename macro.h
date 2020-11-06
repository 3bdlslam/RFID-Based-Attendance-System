#ifndef _macro_h
#define _macro_h
#define set_pin(reg,index) reg |=(1<<index)
#define clr_pin(reg,index) reg &=(~(1<<index))
#define get_bit(reg,index) ((reg>>index)& 1)
#endif