
/*************************************************************************************************/
/*----------------------------------  �ļ��� �� LCD.c  --------------------------------------*/
/*-----------------------------  ���� �� LCD���� -----------------------------------*/
/*************************************************************************************************/
#include"Include.h"
/*-----------------------------������Ļ��ʾ�ַ�--------------------------*/	
unsigned char num[]="NUM=";
unsigned char s[]="S=";
unsigned char t[]="T=";
unsigned char s1[]="S1=";
unsigned char speedshuzu[]="speed=";
/*-----------------------------д�������--------------------------*/	
//��������ֵvoid
//������� ����ֵunsigned char com
/*------------------------------------------------------------------------*/
void write_com(unsigned char com) 
{
    RS=0;		//RS=0 RW=0 ��ַ����ʱ��sp1=30ns
    delay(20);
    EN=0;
    delay(20);
    PORTB=com;		    //��ַ����ʱ��sp2=10ns
    delay(20);
    EN=1;		//E=1    
    delay(20);
    EN=0;		//��ַ����ʱ��hd1=10ns
    //RS=1;		//RS=1 RW=1
}
/*-----------------------------д���ݳ���--------------------------*/	
//��������ֵvoid
//������� ����ֵunsigned char com
/*------------------------------------------------------------------------*/

void write_data(unsigned char dat)
{
    RS=1;		//RS=1 RW=0 ��ַ����ʱ��sp1=30ns
    delay(20);
    EN=0;
    delay(20);
    PORTB=dat;		    //��ַ����ʱ��sp2=10ns
    delay(20);
    EN=1;		//E=1 
    delay(20);
    EN=0;		//��ַ����ʱ��hd1=10ns
    ///RS=0;		//RS=0 RW=1
}
/*----------------------------��ʾ����Ļ����--------------------------*/	
//��������ֵvoid
//������� ����ֵunsigned char com
/*------------------------------------------------------------------------*/
void LCD_reset(void) 
{
   write_com(0x01);//����
   delay(200);  //��ʱ1.2ms
   write_com(0x06);
   delay(200);
   write_com(0x0f);
   delay(200);
}
/*-----------------------------LCD��ʼ������--------------------------*/	
//��������ֵvoid
//������� ����ֵunsigned char com
/*------------------------------------------------------------------------*/
void LCD_init(void) 
{
  char i;
  for(i=0;i<3;i++) 
  {    
  write_com(0x38);
  longdelay(10);//��ʱ6ms
  }
  write_com(0x38); 
  delay(200);
  LCD_reset();
}

/*-----------------------------д���ݳ���--------------------------*/	
//��������ֵvoid
//������� ����ֵunsigned char com
/*------------------------------------------------------------------------*/
void LCD_number(int lcd1)//������ʾ 
{
  
  int num1;
  unsigned char num2,temp;   //��취��һ������ת�����ַ��������ת����ASCII��
  unsigned char s1[16]={0};
  num2=0;
  if(lcd1==0)
    num2=1;
  else 
  {    
    while(!lcd1==0) 
    {               
      temp=lcd1%10; lcd1=lcd1/10;
      s1[num2]=temp;
      num2++;
    }
  }
  num2--;                            
  for(num1=num2;num1>=0;num1--)
  {
        s1[num1]+=0x30;     
     write_data(s1[num1]);
  }
}
/*-----------------------------MAIN�������ó���--------------------------*/	
//��������ֵvoid
//������� ����ֵint
/*------------------------------------------------------------------------*/
void LCD_running(int shuliang,int lucheng,int shijian,int sudu) //·�̣����� ʱ�䣺��
{
  int minute,second;//�� ��
  minute=shijian/60;
  second=shijian%60;
  write_com(0x80);
  write_data('N');
  write_data('U');
  write_data('M');
  write_data(':');
  LCD_number(shuliang);
  write_data(0x20);//����ո�
  write_data('S');
  write_data(':');
  LCD_number(lucheng);
  write_data('m');
  write_data('m');
  write_com(0x80+0x40);
  write_data('T');
  write_data('I');
  write_data('M');
  write_data('E');
  write_data(':');
  if(minute<10) 
    write_data('0');
  LCD_number(minute);
  write_data(':');
  if(second<10)
    write_data('0');
  LCD_number(second);
  write_data(0x20);//����ո�
  write_data('S');
  write_data('U');
  write_data(':');
  LCD_number(sudu);
}
void LCD_stop(int lucheng,int shijian,int diyi,int dier,int disan,int disi) 
{                                   
 int minute,second;//�� ��
  minute=shijian/60;
  second=shijian%60;
  write_com(0x80);
  write_data('F');
  write_data('I');
  write_data('R');
  write_data('S');
  write_data('T');
  write_data(':');
  LCD_number(diyi);
  write_data('m');
  write_data('m');
  write_com(0x80+0x40);
  write_data('S');
  write_data(':');
  LCD_number(lucheng);
  write_data('m');
  write_data('m');
  longdelay(5000);
  LCD_reset();
  write_com(0x80);
  write_data('S');
  write_data('E');
  write_data('C');
  write_data('O');
  write_data('N');
  write_data('D');
  write_data(':');
  LCD_number(dier);
  write_data('m');
  write_data('m');
  write_com(0x80+0x40);
  write_data('S');
  write_data(':');
  LCD_number(lucheng);
  write_data('m');
  write_data('m');
  longdelay(5000);
  LCD_reset();
    write_com(0x80);
  write_data('T');
  write_data('H');
  write_data('I');
  write_data('O');
  write_data('N');
  write_data('D');
  write_data(':');
  LCD_number(disan);
  write_data('m');
  write_data('m');
  write_com(0x80+0x40);
  write_data('T');
  write_data('I');
  write_data('M');
  write_data('E');
  write_data(':');
  if(minute<10) 
    write_data('0');
  LCD_number(minute);
  write_data(':');
  if(second<10)
    write_data('0');
  LCD_number(second);
  longdelay(5000);
  LCD_reset();
  write_data('F');
  write_data('O');
  write_data('R');
  write_data('T');
  write_data('H');
  write_data(':');
  LCD_number(disi);
  write_data('m');
  write_data('m');
  write_com(0x80+0x40);
  write_data('T');
  write_data('I');
  write_data('M');
  write_data('E');
  write_data(':');
  if(minute<10) 
    write_data('0');
  LCD_number(minute);
  write_data(':');
  if(second<10)
    write_data('0');
  LCD_number(second);
  longdelay(1000);
}