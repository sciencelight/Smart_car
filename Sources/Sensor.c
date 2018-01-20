/*************************************************************************************************/
/*------------------------------�ļ�����Sensor.c-------------------------------------------------*/
/*---------------------------���ܣ���ȡ������������---------------------------------------------*/
/*************************************************************************************************/
#include "Include.h"

extern int Tingcheflag;
int Crossflag=0;
/*------------------------------���´�������ز���------------------------------*/
int ADdataorigenal[FRONTNUM][TESTTIME];//���������ݳ�ֵ
int ADdatacur[FRONTNUM];//������������Чֵ
int ADdatahis[HISTORYNUM][FRONTNUM];//��������ʷ��ֵ��0ΪĿǰֵ,Ϊ��ֵ��֮���ֵ
int ADdataflag[FRONTNUM];//��������ֵ��֮���С����
int ADdata[FRONTNUM];//��������������ֵ
int ADdataOkflag;

/*-----------------------------ԭʼ���ݲɼ�����-----------------------------*/	
//��������ֵvoid
//�������void 
//[ȷ����Ѳ���Ƶ�ʺ�ÿ�βɼ�������ȡ��������ԭʼ����]
/*-----------------------------------------------------------------------------*/

void GetADdata(int testevetime) 
{
  unsigned char i,j,k;
  for(i=0;i<=FRONTNUM;i++)
    for(j=0;j<=testevetime;j++) 
    {
      ADdataorigenal[i][j]=GetATD0(i);    //��i��������ȡ��j��
    }
  for(k=0;k<=FRONTNUM;k++)
  {
    ADdatacur[k]=Average(ADdataorigenal[k],testevetime);//Average(ADdataorigenal[i],TESTTIME);    //�Զ��ȡ��ֵȥ��ֵ����ƽ��ֵ��Ϊ��Чֵ
  }
  ATD0STAT0_SCF=1;                                    //AD��������                   
}
/*--------------------------------���ݹ�һ��-----------------------------------*/	
//��������ֵvoid
//�������void 
//�洢��ʷ����
/*-----------------------------------------------------------------------------*/

void Getordinarydata()
{
    char i,j,temp,temp1;
    for(i=HISTORYNUM;i>1;i--) 
      for(j=FRONTNUM;j>=0;j--)
        ADdatahis[i-1][j]=ADdatahis[i-2][j];//��ʷ����ǰ��һλ
    for(j=0;j<FRONTNUM;j++)
       ADdatahis[0][j]=ADdatacur[j]*COE;
    /*temp=ADdatahis[1][0]-ADdatahis[0][0];
    temp1=abs(temp);
    if(temp1>10) 
    {
      ADdatahis[0][0]=ADdatahis[1][0];
    }   */
}
/*----------------------------������Ч��У��----------------------------*/	
//��������ֵvoid
//��ڲ���void ����ֵADdataokflag
//ȷ��AD�����Ƿ���Ч
/*-----------------------------------------------------------------------------*/
void ADdataOk(void) 
{

    int flag,temp;
    temp=Max(ADdatahis[0],10);
    if(ADdatahis[0][temp]<=3)
      ADdataOkflag=0;              //������Ч
    else ADdataOkflag=1;      
    /*
      if(abs((duojiLastError-Carlocation))>6)
        ADdataOkflag=0;
    */
}
/*-------------------------��ȡ����ʱ��һ���������-----------------------*/	
//��������ֵvoid
//�������void
//���ã�����һ��������ݴ���ADdata
/*-----------------------------------------------------------------------------*/
void Process() 
{
  unsigned char i;     
    GetADdata(TESTTIME);
    Getordinarydata();
    ADdataOk();
    if(ADdataOkflag) 
    {      
     for(i=0;i<FRONTNUM;i++)
        ADdata[i]=ADdatahis[0][i];       //���������Ч��ADֵ������
        //ADdata[7]=(ADdata[7]*28)/43;
    }
}

