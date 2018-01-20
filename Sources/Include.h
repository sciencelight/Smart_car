/*----------------------------  ���� ������������ͷ�ļ����ļ� ------------------------------*/
/*************************************************************************************************/
#ifndef _H_INCLUDE_
	#define _H_INCLUDE_

  #include "Sensor.h"
 // #include "LCD.h"
  #include "Surelocation.h"
  #include "Control.h"
  #include "base.h"
  #include "HardWare.h"
  #include "Hardwaredriver.h"
  #include "MC9S12XS128.h"
  /*---------------------���´�������������------------------------------*/
  #define FRONTNUM 8//ǰ�Ŵ�������4
  #define TESTTIME 5//ÿ�βɼ�ÿ����������ȡ����ֵ��Ŀ
  #define HISTORYNUM 10//��ʷ���ݱ�����
  #define MIDYUZHI 3//�м�����������ʧ��ĺ�
  #define ZHONGJIANYUZHI 35//���������������м��ĳ��������֮��ʱ����ֵ
  #define ZHONGJIAN 210//������⳵���Ƿ����ܵ�����(�������ľ����������İ�����) �м����������������庯������Ϊ���庯�� ��ֵ250
  #define ADYUZHI 10 //AD����У����ֵ  
  #define LOCYUZHI 68 //������ֵ
  #define COE 1
  /*---------------------���µ����������------------------------------*/
  #define PWMMOTOT  150     //���PWM����;//���PWM���� 0.16ms ,���������� ֻ����ռ�ձȡ�//���PWM���� 1.6ms
  #define UOUTMAX 130	//��������ѹ
  #define UOUTMIN 75	//������ѹ
  /*---------------------���¶����������------------------------------*/
  #define PWMDT 30000//���PWM���� 20ms
  #define CENTRAL 2100//���PWM����ռ��1.53ms,ת������duojizhankong=750
  #define MOSTLEFT 2850//��������λ�� 
  #define MOSTRIGHT 1350//������ұ�λ��
  /*---------------------�ٶȿ�����غ궨��------------------------------*/
  #define PIDYushe (450+speedset*7) 
  #define PIDYushe1 (450+speedset*7) //(450+speedset*7) 
  #define PIDYushe2 (550+speedset*10) //(450+speedset*7)
  #define STOPCOUNT 120		//��⵽�ٶ��쳣����С��ͣ��������ۼ���Ŀ
  #define STOPSAFTMIN	30	//������ײ��Ҫ�ﵽ����С�ٶ�ֵ
  #define SPEEDMAX 25//����ٶ�
  #define SPEEDMIN 12//����ٶ� 
  /*---------------------LCD��غ궨��------------------------------*/
 //#define RS PORTA_PA5
 // #define EN PORTA_PA3
#endif