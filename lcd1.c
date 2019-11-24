/*
####################################################
LCD显示
1,	初始化设置：
	lcden=0;
	lcdrw=0;
	write_com(0x38);
	write_com(0x01);
	write_com(0x0f);
	write_com(0x06);//设置光标状态默认0x06,为读一个字符光标加1

    write_com(0x80+0x10);//设置初始化数据指针，是在读指令的操作里进行的
	write_com(0x80+0x40+0x10);//换行操作,在屏幕的右方，显示后移到视野内

2，左移和右移
	 //#######字幕向左移出########
	 for(num=0;num<16;num++) //屏幕正方向一共有16个字块，左移16次
	   {
	   		write_com(0x18);//写控制字，在英文文档里介绍。0x18为左移，0x1c为右移。
			delay(100);     //控制移动的速率，即每移动一个字块延时多少秒
	   }    
     //#######字幕向右移出########
	 for(num=0;num<24;num++) //屏幕正方向一共有16个字块，右移时注意移动不足的情况，视情况添加
	   {
	   		write_com(0x1c);//写控制字，在英文文档里介绍。0x18为左移，0x1c为右移。
			delay(100);     //控制移动的速率，即每移动一个字块延时多少秒
	   }
####################################################
*/
	//	 write_com(uchar com)       写命令函数
	//	 write_date(uchar date)		写数据函数
	//   init_lcd()                 初始化函数
	//   display()					显示函数
	//   move()						移动函数
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
	//在屏幕右侧显示出数据
	write_com(0x80+0x10);//设置初始化数据指针位置,设置在屏幕的未显示区，然后移动到屏幕的正方
	for(i=0;i<16;i++)
	{
		write_date(t0[i]);
		delay(5);
	}
	write_com(0x80+0x40+0x10); //设置初始化数据指针位置,设置在屏幕的未显示区，然后移动到屏幕的正方	
	for(i=0;i<16;i++)
	{
		write_date(t1[i]);
		delay(5);		
	}
}
void move()	//进行移动
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
