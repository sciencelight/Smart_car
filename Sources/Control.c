/*************************************************************************************************/
/*----------------------------------  �ļ��� �� Control.c  --------------------------------------*/
/*-----------------------------  ���� �� ȷ������͵������� -----------------------------------*/
/*************************************************************************************************/
#include"Include.h"
extern int Wandaoflag;                            //�������־λ  
extern int Crossflag;                             //��������
extern char startlineflag;                        //�����߼��
int SafeStopEnableFlag;                    //��ײ�����־λ�����ٶȳ���STOPSAFTMINʱ��������
extern int Tingcheflag;
extern int location;
extern int modecount;
extern int forecast[15];
extern int wandaoflag;
/*------------------------------�������-----------------------------*/
int Carlocation=0;                                 //С��λ��
int Piancha;
int duojizhankong;
int directionlost[3]={0,0,0};     //����ƫ��
int duojiPcoe=0;
int duojiIcoe=0;
int duojiDcoe=0;
int duojiLastError=0;
int duojiPrevError=0;
int duojiSumError=0;
int duojiiError_max=0;
int curvecount=0;               //�������
int speedlimitcount=0;
int speedlimit=0;
int curvetostraight=1;
int straignttocurve=2;
/*---------------------------�����������----------------------------*/
int I_Term_max = 10 ; 					//�����޷�ֵ
int I_Term_min = -10 ;					//�����޷�ֵ
int speedset = 50 ;						//�ٶ��趨ֵ��������ĳ�ֵ��ϵ����
int speedlost[3] = {0,0,0} ; 			//�ٶ�ƫ��    
int umotor = 0 ;						//��һ�εĵ����ѹ��
int uout=0;
extern int speed ;							//��ǰ�ٶȣ����Բ���ȫ�ֱ�������Ϊ���Է���
extern int LINE_V;
extern int PWMMOTOTA;
unsigned char lastStrategy = 1 ;		//bang-bangΪ1��pidΪ0,��ʼΪbang-bang
int BANGBANGtoPID = 10 ; 				//Bang-Bang To PID ��ֵ
int PIDtoBANGBANG = 10	; 				//PID To Bang-Bang ��ֵ 
int last_PIDV;                       //���һ��PID����                 
int speedzero ;                    	//����ײ����ͣ��
int WAN_V=100;
int motorPcoe=0;
int motorIcoe=0;
int motorDcoe=0;                                                                            ;
int motorLastError=0;
int motorPrevError=0;
int motorPrevPrevError=0;
int motorSumError=0;
int motoriError_max=0;
int PIDmotor=0;                   //��ǰ���PID����
int modeflag=1;//����ģʽ
/*-----------------------------�������������--------------------------*/	
//��������ֵvoid
//�������void
/*------------------------------------------------------------------------*/
void duojicontrol(void) 
{
  Carlocation=SureLocationTest();                  //С��λ����
	  if(modeflag==1)
	  {  
	  duojiPcoe=60;
    duojiIcoe=0;
    duojiDcoe=0;
	  } 
	  else
	  {  

    duojiPcoe=100;
    duojiIcoe=0;
    duojiDcoe=115;
	  }      
  Piancha=PIDcalc1(duojiPcoe,duojiIcoe,duojiDcoe,Carlocation,duojiLastError,duojiPrevError,duojiSumError,duojiiError_max);
  duojizhankong=CENTRAL-Piancha;   
  if(duojizhankong<MOSTRIGHT)
    duojizhankong=MOSTRIGHT;
  if(duojizhankong>MOSTLEFT)
    duojizhankong=MOSTLEFT;
  PWMDTY01=duojizhankong;//ռ�ձ�=((PWMPER-duojizhankong)/PWMPER)*100%  
}
int speedwanted(void)
{

  int speedtemp;
  if(abs(location)>=2) 
  {
    modeflag=2; 
  } 
  else
    modeflag=1; 
  if((modeflag==1)) 
  {
    speedtemp=LINE_V;
  }
  if(modeflag==2)
    speedtemp=LINE_V+5;  
  return(speedtemp);
}         
void ControlMotor(int uin)
{
 	//if(uin>0 )
 	int temp;
 	temp=uin;
 PWMDTY23 = temp;		//PTM_PTM0 = 1;//�����ת
	/*else if(uin<0 )
	{	PWMDTY23 = uin;	PTM_PTM0 = 0; }//����
	else
	{	PWMDTY23 = 0;	 PTM_PTM0 = 1;	} */
}
void MotorControl(void) 
{
  int bangzhi;
  int P_Term;
  int I_Term;
  int D_Term;
  speedset=20;
  speedlost[2] = speedlost[1] ;
	speedlost[1] = speedlost[0] ;
	speedlost[0] = (speedset-speed) ;
	/*if(lastStrategy)
	  bangzhi=10;
	else
	  bangzhi=PIDtoBANGBANG;                   //������pid֮�����ֵ */
/*	if(speedlost[0]>10) 
	{
	  uout=UOUTMAX;
	  speedlost[2]=0;
	  speedlost[1]=0;
	  lastStrategy=1;
	  last_PIDV=0;
	}
	else if(speedlost[0]<-10) 
	{
	  uout=UOUTMIN;
	  speedlost[2]=0;
	  speedlost[1]=0; 
	  lastStrategy=1;
	  last_PIDV=0;
	}//bangbang�㷨
	else 
	{ */
	  motorPcoe=200;
    motorIcoe=0;
    motorDcoe=0;    
	  /*uout=PIDcalc2(motorPcoe,motorIcoe,motorDcoe,speedset,speed,motorLastError,motorPrevError,motorPrevPrevError,motoriError_max);
	  uout=last_PIDV+uout;
	  uout=PWMMOTOT-uout;
	  lastStrategy=0;*/
	  P_Term = motorPcoe * (speedlost[0] - speedlost[1]);     //��������;
		D_Term = motorDcoe * (speedlost[0] - 2 * speedlost[1] + speedlost[2]);  //΢�ֻ���
  	I_Term = motorIcoe * speedlost[0];   //���ֻ���
		if(I_Term>I_Term_max) 	//���ַ���(�޷�)
			I_Term = I_Term_max;
		else if(I_Term<I_Term_min)	//	���ַ���(�޷�)
			I_Term = I_Term_min;
		PIDmotor = P_Term + I_Term + D_Term;	
		last_PIDV = PIDmotor;
		uout = umotor + P_Term + I_Term + D_Term;		//�����ۼ�
		if(uout > UOUTMAX)		umotor = UOUTMAX;
		else if(uout < UOUTMIN)		umotor = UOUTMIN; 
		lastStrategy = 0;	  
//	}
  if(uout>UOUTMAX)		uout = UOUTMAX;
				else if(uout<UOUTMIN)		uout = UOUTMIN;
	umotor=uout;
  uout=PWMMOTOT-uout;
	ControlMotor(uout);
}



void Control(void)
	{ 
      PWMDTY23=speedwanted(); 	//ȷ���������  \
      
      //MotorControl();
      duojicontrol();
      //PWMDTY23=LINE_V;    		
	}