/**************************************************************************************************/
/*-----------------------------  ��˼����������С������   ʡ���汾---------------------------------*/
/*----------------------------  �����ˣ����� �ſ�� ���� -----------------------------------------*/
/**************************************************************************************************/

/**************************************************************************************************/
/*-----------------------------------  �ļ��� �� main.c  ---------------------------------------*/
/*----------------------------  ���� �������Ͷ�ʱ�����ڣ������ļ� --------------------------*/
/**************************************************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Include.h"


extern int ADdataokflag; //AD������Ч
extern int Crossflag;
extern int Wandaoflag;                                               
extern int duojizhankong; 
extern int modeflag;
int forecast[15];//���ʶ��
int Tingcheflag;  //ͣ����־λ
int LINE_V;
int TC0count; 
unsigned int f1,f2;
int startline=0;
unsigned int speed;
unsigned int modecount;

/*----------------------------------������--------------------------------------*/	
//main.c : Start program  here ...
/*-------------------------------------------------------------------------------*/
void main(void) 
{                                  
  DisableInterrupts;  
  init();  
  //LEDtest(); 
  longdelay(2000);   //2s��ʱ
  PTT_PTT7=1;
	PTM_PTM0=1;
  //TC0=11320; //54ms
  modeflag=0;

  
  EnableInterrupts;//���ߵ��Ե�ʱ���������ֹ����ͻ���Ϊ18���ж϶���ֹ����ִ��
	while(1)
	{
	  MOD_init();
	 /*if(PORTA_PA1==0)//�ɻɹ�ɨ�� 
	 {
	    longdelay(1);//��е���ط���
	    startline++;
      if(startline==3)
        Tingcheflag=1;
	 }
	 if(Tingcheflag) 
  	 {
  	  while(1){
  	    DisableInterrupts;
  	    PWMDTY23=2400;
  	 }���Խ�ֹ*/ 
	 }
}
	
//#pragma CODE_SEG __NEAR_SEG NON_BANKED //��ֹ����ý�����
#pragma CODE_SEG NON_BANKED
void interrupt 8 timer0(void)
{
   DisableInterrupts;
   TFLG1&=0x01 ;
   PACTL_PAEN=0;
   TC0=(TC0+187)%65525;                 //��ʱ1ms ��1125
   f1=PACNT; //�Ȱ�PACNTֵ��������� ����ʵʱ����ʱ��ȡ ����PACNT�ָߵ�λ��ȡ�������
   /*--------------------�˲���������------------------------------------------ */
   speed=f1*4320/1260;  //(f1/200*1*10^(-3))*(40/105)*0.18   �ٶȵ�λ������/�� 
   /*���ܳ�180mm ������105/40
      ����2m/sʱ ����ת��11r/s  ������ת�� 29.17r/s   ������5833/s ��������0.1714ms ÿ��������35��*/                
   PITTF_PTF=1;//���жϱ�־λ 
   PACTL_PAEN=1;
   PACNT=0x00; //����������
   Process();
   Control();
  EnableInterrupts;    
}
//#pragma CODE_SEG __NEAR_SEG NON_BANKED
#pragma CODE_SEG NON_BANKED
void interrupt 24 externinterrupt(void)                       
{
  DisableInterrupts;
  //PIEJ=0x00;
  longdelay(1);                            //�ɻɹ��ǻ�е���� Ҫ���� �Ժ�ĸɻɹ�Ҫ�ӵ��ݷ���
  PIFJ=0x80;
  startline++;
  if(startline==2)
    Tingcheflag=1;
  EnableInterrupts;
  
} 