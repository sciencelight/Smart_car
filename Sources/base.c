/*************************************************************************************************/
/*-----------------------------------  �ļ��� �� Bace.c  --------------------------------------*/
/*-----------------------------  ���� ���������ܣ���ʱ�����ݴ��� ---------------------------*/
/*************************************************************************************************/

#include "Include.h"		//������ʱ���������������

void delay(int delaytime)
	{//�����ʱ��24M����Ƶ��ʱ��ʱʱ��ԼΪ10us
	     int i;unsigned char j;
	     for (i=0;i<delaytime;i++)
	      for (j=0;j<24;j++)               
	       ; 	
	}
	
void longdelay(int delaytime)
	{//�����ʱ��24M����Ƶ��ʱ��ʱʱ��ԼΪ1ms
		 int i;
	     for (i=0;i<delaytime;i++)
	       delay(100);
	}

/*----------------------------���������м�ֵ����-------------------------------*/	
//��������ֵunsigned char bijiao[n/2];
//�������int bijiao[],unsigned char n
//����ֵ��bijiao[]Ϊԭʼ���ݣ�nΪ������
/*---------------------------------------------------------------------------------*/	
int Midnum(int bijiao[],unsigned char n)
	{
		 int i,j,temp;
		 if(n==1)
		  return bijiao[0];
		 if(n==2)
		  return (bijiao[0] + bijiao[1])/2;
		 for(j=1;j<n;j++)
		   for(i=0;i<n-j;i++)
		   	{	   		 
		     if(bijiao[i]<bijiao[i+1])
		    	{
		    	  temp=bijiao[i];
		    	  bijiao[i]=bijiao[i+1];
		    	  bijiao[i+1]=temp;
		    	}
		   	}
		 if(n%2)
		 	return bijiao[(n-1)/2];
		 else
		 	return (bijiao[n/2] + bijiao[n/2 - 1])/2;
	}
	
/*-----------------------------�����������ֵ����-------------------------------*/	
//��������ֵunsigned char temp
//�������int bijiao[],unsigned char n
//�����ֵ��bijiao[]Ϊԭʼ���ݣ�nΪ������
/*---------------------------------------------------------------------------------*/	
unsigned char Max(int bijiao[],unsigned char n)
	{
      unsigned char i,temp=0;
	  for(i=0;i<n;i++)
	  	{
          if(bijiao[temp]<bijiao[i])
          temp=i;	  	
  	  	}
	  return(temp);
	}
	/*-----------------------------������ƽ��ֵ����-------------------------------*/	
//��������ֵ����ƽ��ֵ
//�������int bijiao[],unsigned char n
//��ƽ��ֵ��bijiao[]Ϊԭʼ���ݣ�nΪ������
/*---------------------------------------------------------------------------------*/
	int Average(int bijiao[],unsigned char n)//������һ��ԭ������ĸ���������Ӧ����ָ��*int
	{
		unsigned char i = 0 ;
		int temp=0;
		for(i=0 ; i< n ; i++)
			{
				temp += bijiao[i] ;
			}
		return (temp/n) ;
	}
	
/*-----------------------------����������Сֵ����-------------------------------*/	
//��������ֵunsigned char temp
//�������int bijiao[],unsigned char n
//����Сֵbijiao[]Ϊԭʼ���ݣ�nΪ������
/*---------------------------------------------------------------------------------*/
unsigned char Min(int bijiao[],unsigned char n)
	{
	  unsigned char i,temp=0;
	  for(i=0;i<n;i++)
	  	{
          if(bijiao[temp]>bijiao[i])
		  temp = i;
        }
	  return(temp);
	} //�õ�����ǰn��Ԫ������Сһ�������±�
	
/*----------------------------------���������±�-------------------------------------*/
//��������ֵvoid
//�������int bijiao[],int flag[],int n
//���� bijiao[] ԭʼ����,flag[]�����ı������,n���鳤��
/*----------------------------------------------------------------------------------------*/
void MaxtoMin(int bijiao[],int flag[],int n) 
	{       
	    int temp[10]={0};
	    int i;
	    if(n > 10)
	    	n = 10;
	    for(i = 0;i < n;i++)
	    	 temp[i] = bijiao[i];
 	    for(i = 0;i < n;i++)
		    {
		       flag[i] = Max(temp,n);
		       temp[flag[i]] = 1;//��һ����С����ֵ
		    }     
	}//������bijiao[]�����ִ�С�������е��±��������flag
/*----------------------------------����ֵ����-------------------------------------*/
//��������ֵint
//�������int
//�����������ֵľ���ֵ
/*----------------------------------------------------------------------------------------*/
int abs(int i) 
{
  int j;
  if(i>=0)
   j=i;
  else
   j=0-i;
  return(j);
}
/*----------------------------------PID���岿��-------------------------------------*/
//��������ֵint
//�������int bijiao[],int flag[],int n
//���� bijiao[] ԭʼ����,flag[]�����ı������,n���鳤��
/*----------------------------------------------------------------------------------------*/

int PIDcalc1(int Pcoe,int Icoe,int Dcoe,int Error,int LastError,int PrevError,int SumError,int iError_max)//λ��pid �����������
{ 
  int  dError,iError,pError;
  PrevError=LastError;
  LastError=Error;
  SumError+=Error;
  dError=Dcoe*(LastError-PrevError);
  iError=Icoe*(SumError);
  pError=Pcoe*Error;
  if(iError>iError_max)
    iError=0;
  return(pError+iError+dError);
}
int PIDcalc2(int PcoeS,int IcoeS,int DcoeS,int SetPoint,int CurrentPoint,int LastErrorS,int PrevErrorS,int PrevPrevErrorS,int Iterm_max)//����ʽPID �����������  currentpoint ��ǰ����ֵ
{
   int Pterm,Iterm,Dterm;
   PrevPrevErrorS=PrevErrorS;
   PrevErrorS=LastErrorS;
   LastErrorS=SetPoint-CurrentPoint;
   Pterm=PcoeS*(LastErrorS-PrevErrorS);
   Iterm=IcoeS*LastErrorS;
   Dterm=IcoeS*(LastErrorS-2*PrevErrorS+PrevPrevErrorS);
   if(Iterm>Iterm_max)
    Iterm=0; 
   return(Pterm+Iterm+Dterm);   
}