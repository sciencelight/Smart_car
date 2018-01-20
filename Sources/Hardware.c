/*************************************************************************************************/
/*--------------------------------  �ļ��� �� HardWare.c  -----------------------------------*/
/*----------------------------------  ���� Ӳ����ʼ�� ----------------------------------------*/
/*************************************************************************************************/
#include "Include.h"
int PWMMOTOTA;              //���ռ�ձ�
extern int LINE_V;
/*----------------------------------  ϵͳʱ�ӳ�ʼ�� ----------------------------------------*/
void CLK_init(void) 
{
  CLKSEL=0x00; //��ʼʱ��û��PLL
  PLLCTL=0xe1; //ʱ�Ӽ��ʹ�ܣ�PLL������VCOCLK��Ƶ2%����ֹ�������ѣ���ֹ�Ը�ʱ�ӣ�αֹͣ�½�ֹʵʱ�жϺͿ��Ź�
  SYNR=2;
  REFDV=1;           //PLLCLK=2*OSCCLK*(SYNR+1/((REFDV+1))=48M;
  asm NOP;asm NOP;asm NOP;//�ȴ����໷�ȶ�
  while(!(CRGFLG&0x08));//���໷�ȶ���־λ
  CLKSEL=0x80;  //ʱ��ѡ��Ĵ�����Bus Clock=PLLCLK/2,ֹͣģʽ��������ϵͳʱ�ӡ����໷���ں�ʱ�ӡ����Ź���������
    
}
/*----------------------------------  ECT��ʼ�� ----------------------------------------*/
void ECT_init(void) 
{
  TIOS=0x0f;   //ͨ��0~4����Ƚϣ�5~7���벶׽
  TSCR2=0x07;  //TOF����λʱ��ֹ�жϣ�ͨ��7����󲻸�λ��f=24/128=0.1875MHz
  TCTL3=0x55;  //ͨ��IC7~4��׽�����أ���TCTL2=0x00,OC�����ŶϿ�)
  PACTL=0x40;  //�����ۼ���Aʹ�ܣ���PT7��⵽�����غ��������1���÷�Ƶ���Ӷ���ʱ�ӣ���ֹ�ۼ�������ж�
  TIE=0x01;    //OCͨ����λ�����жϣ����ɼ�ʱ������������ж�
  PACNT=0x00;
  TCNT=0x00;
  TSCR1=0x80;  //��ʱ��������WAITģʽ����������FREEZEģʽ������������ʱ����־���������
}
/*----------------------------------  IO�ڳ�ʼ�� ----------------------------------------*/
void IO_init(void)
{
  DDRA=0xff;
  PORTA=0xff;
  DDRA=0x00;      //PORTA�������
  //PUCR_PUPAE=1;   //A����������
  DDRB=0xff;      //PORTB��LED��
  PORTB=0x00; 
  //DDRT=0xff;    
  //PTT=0x00;       //��ʼ����
  DDRT=0xff;      //T�����
  PERT=0xff;      //T�ڼ�pull device ����
  PPST=0xff;      //T����������
  PTT_PTT0=0;
  DDRP=0xff;      //PORTP��PWM���
  PTP=0xff;
  DDRM_DDRM0=1;   //PTM0������ڣ�1=���� 0=����
  PTM_PTM0=0;
  DDRJ=0xff;
  PTJ=0xff;     //PTJ0��ʼֵΪ��
  PERJ=0xff;
  DDRJ=0x00;      //PTJ0������ڣ����ܸɻɹ��ж�
  PPSJ=0x00;      //PTJ7��׽�½����ж�
  PIEJ=0X80;      //�ж�ʹ��
  //RDR0AD0=0xff;//AD�ڼ�ʹ������������ʱҲ��ֵ ��Ϊ�ǵ�Ÿ��� ����������
  RDRP=0xff;
  
  //PUCR=0x40;    //BKGD E K A B��������������
  //PUCR �������� ���� RDRIV������� ����
}
/*----------------------------------  PWM��ʼ�� ----------------------------------------*/
void PWM_init(void)
{
  PWME=0x00;        //��ʼ��ֹPWM
  PWMPRCLK=0x44;    //Ԥ��ƵBUSCLOK/16=1.5MHz
  PWMCLK=0x00;     //0��1ʹ��CLOCKA  2��3ʹ��CLOCKB
  PWMCTL=0x30;      //ͨ��01  23����
  PWMPOL=0xff;      //��ʼ�͵�ƽ
  PWMCAE=0x00;      //���������
  PWMPER01=PWMDT;   //�������
  PWMDTY01=CENTRAL; //�������ռ�ձ�
  PWMPER23=PWMMOTOT;//�������
  PWMDTY23=70;//�����ʼ����ռ�ձ�
  PWME=0xff;         //��ʱ֮����������Ͷ��
}
/*----------------------------------  ADģ���ʼ�� ----------------------------------------*/
void AD_init(void)
{
   ATD0CTL0=0x07;     //ADת�����г���Ϊ8
   ATD0CTL1=0x00;     //����ָ��AD�����ⲿ��������ڣ�12λ���������ǰ�������ݲ��ŵ� 1
   ATD0CTL2=0x10;     //��־�Ĵ������������㣬ֹͣģʽ�����У���ֹ�ⲿ��������ֹת������жϺͱȽϳɹ��ж�
   ATD0CTL3=0xc0;     //����Ҷ��룬��FIFOģʽ������ģʽ����ת�� ת������4
   ATD0CTL4=0x44;     //�ڶ��׶β���8��AD���ڣ���һ�׶�2��AD���ڣ���f=fbus/2*(4+1)��4.16msת��һ��
   ATD0CTL5=0x30;     //������ͨ��ת������ͨ��0��ʼ
   ATD0DIEN=0x00;     //�����������뻺��?
}     

/*----------------------------------  ��ȡADת����ʼ���� ----------------------------------------*/
unsigned char GetATD0(unsigned char ch)
{
  int ad=0;
  //while(!ATD0STAT0_SCF);
  switch(ch) 
  { 
    case 0:
    ad=((ATD0DR0H*256)+ATD0DR0L);
    break;
    case 1:
    ad=((ATD0DR1H*256)+ATD0DR1L);
    break;
    case 2:
    ad=((ATD0DR2H*256)+ATD0DR2L);
    break;
    case 3:
    ad=((ATD0DR3H*256)+ATD0DR3L);
    break;
    case 4:
    ad=((ATD0DR4H*256)+ATD0DR4L);
    break;
    case 5:
    ad=((ATD0DR5H*256)+ATD0DR5L);
    break;
    case 6:
    ad=((ATD0DR6H*256)+ATD0DR6L);
    break;
    case 7:
    ad=((ATD0DR7H*256)+ATD0DR7L);
    break;       
  }
  return ad;
}
/*----------------------------------  �ܳ�ʼ��--------------------------------------------*/
void init(void)
{
    CLK_init();
    
    ECT_init();
    IO_init();       
    PWM_init();
    AD_init();    
}