/*************************************************************************************************/
/*-----------------------------------  �ļ��� �� Bace.h  --------------------------------------*/
/*-------------------------------  ���� ��Base.c ��Ӧͷ�ļ� ---------------------------------*/
/*************************************************************************************************/
                             //�ṹ�嶨����ͷ�ļ���
void delay(int delaytime);				//��ʱ��Լ3us
void longdelay(int delaytime);		//����ʱ��Լ3ms,û��ϸ�㣬��Ӧ���ö�ʱ���ģ�O(��_��)O����~
unsigned char Max(int bijiao[],unsigned char n); //���ֵ�����������±�
unsigned char Min(int bijiao[],unsigned char n); //��Сֵ�����������±�
int Midnum(int bijiao[],unsigned char n);//��ֵ�������м����±�
void MaxtoMin(int bijiao[],char  flag[],int n);
int Average(int bijiao[],unsigned char n);//���м�ֵ
int abs(int i);
int PIDcalc1(int Pcoe,int Icoe,int Dcoe,int Error,int LastError,int PrevError,int SumError,int iError_max);//λ��pid �����������;//λ��ʽPID ����������� 
int PIDcalc2(int PcoeS,int IcoeS,int DcoeS,int SetPoint,int CurrentPoint,int LastErrorS,int PrevErrorS,int PrevPrevErrorS,int Iterm_max);//����ʽPID �����������  currentpoint ��ǰ����ֵ