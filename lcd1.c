/*
####################################################
LCD��ʾ
1,	��ʼ�����ã�
	lcden=0;
	lcdrw=0;
	write_com(0x38);
	write_com(0x01);
	write_com(0x0f);
	write_com(0x06);//���ù��״̬Ĭ��0x06,Ϊ��һ���ַ�����1

    write_com(0x80+0x10);//���ó�ʼ������ָ�룬���ڶ�ָ��Ĳ�������е�
	write_com(0x80+0x40+0x10);//���в���,����Ļ���ҷ�����ʾ���Ƶ���Ұ��

2�����ƺ�����
	 //#######��Ļ�����Ƴ�########
	 for(num=0;num<16;num++) //��Ļ������һ����16���ֿ飬����16��
	   {
	   		write_com(0x18);//д�����֣���Ӣ���ĵ�����ܡ�0x18Ϊ���ƣ�0x1cΪ���ơ�
			delay(100);     //�����ƶ������ʣ���ÿ�ƶ�һ���ֿ���ʱ������
	   }    
     //#######��Ļ�����Ƴ�########
	 for(num=0;num<24;num++) //��Ļ������һ����16���ֿ飬����ʱע���ƶ�������������������
	   {
	   		write_com(0x1c);//д�����֣���Ӣ���ĵ�����ܡ�0x18Ϊ���ƣ�0x1cΪ���ơ�
			delay(100);     //�����ƶ������ʣ���ÿ�ƶ�һ���ֿ���ʱ������
	   }
####################################################
*/
	//	 write_com(uchar com)       д�����
	//	 write_date(uchar date)		д���ݺ���
	//   init_lcd()                 ��ʼ������
	//   display()					��ʾ����
	//   move()						�ƶ�����
//##################################################
#include<reg52.h>
#define uchar unsigned char 
#define uint unsigned int

uchar i;

sbit lcdrs=P1^0;
sbit lcdrw=P1^1;
sbit lcden=P1^2;

uchar code t0[]=" douzi && douer ";
uchar code t1[]=" douzi -> douer ";

void delay(uchar z)
{
	uchar x,y;
	for(x=1000;x>1;x--)
		for(y=z;y>1;y--);
}

void write_com(uchar com)
{
	lcdrs=0;
	P2=com;	
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
void write_date(uchar date)
{
	lcdrs=1;
	P2=date;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
void init_lcd()
{
	lcden=0;
	lcdrw=0;
	write_com(0x38);
	write_com(0x01);
	write_com(0x0c);
	write_com(0x06);
}
void display()
{
	//����Ļ�Ҳ���ʾ������
	write_com(0x80+0x10);//���ó�ʼ������ָ��λ��,��������Ļ��δ��ʾ����Ȼ���ƶ�����Ļ������
	for(i=0;i<16;i++)
	{
		write_date(t0[i]);
		delay(5);
	}
	write_com(0x80+0x40+0x10); //���ó�ʼ������ָ��λ��,��������Ļ��δ��ʾ����Ȼ���ƶ�����Ļ������	
	for(i=0;i<16;i++)
	{
		write_date(t1[i]);
		delay(5);		
	}
}
void move()	//�����ƶ�
{
		for(i=0;i<16;i++)
		{
			write_com(0x18);
			delay(100);
		}
}
//#######################
void main()
{
	init_lcd();
	display();
	while(1)
	{
	 	move();		
	}
}


123456
