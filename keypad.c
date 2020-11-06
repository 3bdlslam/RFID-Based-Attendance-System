#include <avr/io.h>
#include "lcd.h"
char keypad(char *i)
{
	char let;
	sw:while (PINB==0b00000000);
	 switch (PINB)
	{
		case 0b00000001:let='a';break;
		case 0b00000010:let='b';break;
		case 0b00000011:let='c';break;
		case 0b00000100:let='d';break;
		case 0b00000101:let='e';break;
		case 0b00000110:let='f';break;
		case 0b00000111:let='g';break;
		case 0b00001000:let='h';break;
		case 0b00001001:let='i';break;
		case 0b00001010:let='j';break;
		case 0b00001011:let='k';break;
		case 0b00001100:let='l';break;
		case 0b00001101:let='m';break;
		case 0b00001110:let='n';break;
		case 0b00001111:let='o';break;
		case 0b00010000:let='p';break;
		case 0b00010001:let='q';break;
		case 0b00010010:let='r';break;
		case 0b00010011:let='s';break;
		case 0b00010100:let='t';break;
		case 0b00010101:let='u';break;
		case 0b00010110:let='v';break;
		case 0b00010111:let='w';break;
		case 0b00011000:let='x';break;
		case 0b00011001:let='y';break;
		case 0b00011010:let='z';break;
		case 0b00011011:let=' ';break;
		case 0b00011100:let='\0';break;
		case 0b00011101:*i-=2;break;
		default:goto sw;
	}
	
	return let;
}