#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
#include "lcd.h"
#include "eeprom.h"
#include "macro.h"
#include "keypad.h"
#include <string.h>
#define n 10
	static unsigned char names[n][15]={"13006F8C7280","13006F8C7281","13006F8C7282","13006F8C7283","13006F8C7284","13006F8C7285","13006F8C7286"};
	static unsigned char name[n][15]={"Essam","Soliman","Atef","AbdElsalam","Sheref","Hassan","Manar"};
	static unsigned char master[15]={"100064C561D0"};
void clr(){
	LCDWriteStringXY(0,0,"                ");
	LCDWriteStringXY(0,1,"                ");
}
int main(void)
{
	for (char i=0;i<4;i++)
	{
		clr_pin(DDRC,i);
	}		
	for (char i=0;i<8;i++)
	{
		clr_pin(DDRB,i);
	}		
	
	char p[5],checkpass,choose;
	unsigned char i,c,flag,read[12],count,con,cnt,check;
	static char card[n],num[n];
	InitLCD(0);
	uart_init();
	_delay_ms(100);

    while(1)
    {
		check=0;
		for (i=0;i<n;i++){
		if (strlen(names[i])==12)
		check++;	
		}			
        for(c=0;c<n;c++)
		card[c]=0;
		flag=0;
		count=0;
		cnt=0;
		checkpass=0;
	start:if(get_bit(PINC,0)==0 && get_bit(PINC,2)==0 && get_bit(PINC,1)==0 && get_bit(PINC,3)==0)
	{ 
	clr();
	LCDWriteStringXY(0,0,"EECE attendance");
	LCDWriteStringXY(0,1,"Swipe ur card ");


	for(i=0;i<12;i++) // reading RFID tag number
	{
		if(get_bit(PINC,0)==0 && get_bit(PINC,2)==0  && get_bit(PINC,1)==0 && get_bit(PINC,3)==0 )
		{
		   read[i]=rx_data();
		   for (c=0;c<n;c++)
		   {
		   if(names[c][i]==read[i])
		   card[c]++;
		   }
		}
		else goto start;
	}
	for (c=0;c<n;c++)
	{
		if(card[c]==12)
		{
			flag=12;
			break;
		}
	}
	if(flag==12)		// check for authentication
	{
		num[c]++;
		if (num[c]==1)
		{
			clr();
			LCDWriteStringXY(0,0,name[c]);
			LCDWriteStringXY(0,1,"ATTEND          ");
			_delay_ms(500);
		}		
		else
		{
			clr();
			LCDWriteStringXY(0,0,name[c]);
			LCDWriteStringXY(0,1,"card used before ");
			_delay_ms(500);
        }
    }
    else               // unauthorized person
    {
             clr();
			 LCDWriteStringXY(0,0,"card not matched");
			 LCDWriteStringXY(0,1,"Unknown person ");
			 _delay_ms(500);
    }
	}
    else if (get_bit(PINC,0)==1)
    {
        for (c=0;c<n;c++)
        {
			if (strlen(names[c])==12){
            if (num[c]>=1)
            {
				 clr();
			LCDWriteStringXY(0,0,name[c]);
			LCDWriteStringXY(0,1,"checked          ");
			_delay_ms(500);
			count++;
            }
            else 
            {
			 clr();
			LCDWriteStringXY(0,0,name[c]);
			LCDWriteStringXY(0,1,"not checked          ");
			_delay_ms(500);
			}
			}
			else {break;}                   
			}				
		}
		else if (get_bit(PINC,1)==1)
		{
			for (c=0;c<n;c++)
        {
			if (strlen(names[c])==12)
			{
            if (num[c]>=1)
			count++;
			}
			else {break;}                   
			}
			clr();
			LCDWriteStringXY(3,0,"attend");
			LCDWriteIntXY(0,0,count,2);
			LCDWriteStringXY(3,1,"not attend");
			LCDWriteIntXY(0,1,check-count,2);
			_delay_ms(5000);
		}
	else if (get_bit(PINC,2)==1)
	{
	    checkpass=0;
		pas:clr();
		LCDWriteStringXY(0,0,"enter password: ");
		
		for(i=0;i<12;i++)
		{
			p[i]=rx_dat();
		if (p[i]==master[i])
		checkpass++;
		}
		clr();
		LCDWriteStringXY(0,0,"a- insert ");
		LCDWriteStringXY(0,1,"b- delete ");
		
		if (checkpass==12)
		{
			choose=keypad(0);
		if (choose=='a'){
			for (c=0;c<n;c++)
			{
				int len=strlen(names[c]);
				if (len!=12)
				break;
			}
			if (c<=n)
			{
				clr();
				LCDWriteStringXY(0,0,"swipe new card");
				for (i=0;i<12;i++)
				names[c][i]=rx_dat();	
				clr();
				LCDWriteStringXY(0,0,"enter the name");
				i=0;
				while (PINB==0b00000000);
				while (1)
				{
					name[c][i]=keypad(&i);
					LCDWriteStringXY(0,1,name[c]);
					if (name[c][i]=='\0')
					break;
					i++;
					while (PINB!=0b0000000);					
				}
				clr();
				LCDWriteStringXY(0,0,"done");
				_delay_ms(500);
			}
			else 
            {
                clr();
				LCDWriteStringXY(0,0,"no storge");
				_delay_ms(500);
            }
            }
        else if (choose=='b')
        {
                clr();
              LCDWriteStringXY(0,0,"all data will be"); 
              LCDWriteStringXY(0,1,"deleted ,wait"); 
              _delay_ms(5000);
              for (c=0;c<n;c++)
              {
                  free (names[c]);
                  free (name[c]);
              }
            }
		}
	else
			{
			cnt++;
			clr();
			if (cnt<=5)
			{
				LCDWriteStringXY(0,0,"invalid,re enter");
				_delay_ms(800);
				goto pas;
			}
			else
			{
				LCDWriteStringXY(0,0,"5 errors,exit");
				_delay_ms(800);
			}
			}
	}			    
		else if ( get_bit(PINC,3)==1)
		{
			for (i=0;i<n;i++)
			num[i]=0;
		}			
    }
	}