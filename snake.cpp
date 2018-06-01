#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<math.h>

//����ڵ�
typedef struct snake
{
	int x;
	int y;
	struct snake *next;
}snake;

//ȫ�ֱ���
int x,y,v=350,guess=0,add=18;
char a='w';
snake *head=NULL,*food=NULL,*p=NULL;

//ǽ���ӡ
void wall();
//������
void pos(int x,int y);
//�������ƶ��ķ���
int control();
//��ʼ����
void createsnake();
//�����ƶ�
void snakemove();
//����ʳ��
void snakefood();
//�ж�ײǽ����ҧ���Լ�
int death();
//������Ϸ
int endgame();
//�ͷ���ָ��

int main()
{
	int a;
loop:
	createsnake();
	wall();
	pos(0,32);
	printf("������%d",guess);
	pos(0,31);
	printf("ʳ���ֵ��%d",add);
	pos(0,30);
	printf("W���ϣ�S���£�A����D���ң�P����ͣ��Z�����٣�X������");
	snakefood();
	snakemove();
lop:
	printf("�Ƿ����¿�ʼ��Ϸ\n1���ǣ�2����\n");
	scanf("%d",&a);
	if(a==1)
	{
		system("cls");
		goto loop;
	}
	else if(a==2)
	return 0;
	else goto lop;
}

//�ͷ���ָ��
void freesnake()
{
	snake *c=head;
	while(c)
	{
		snake *q=c;
		c=c->next;
		free(q);
	}
	//free(head);
	free(c);
}

//������Ϸ
int endgame()
{
	
	if(death()==1)
	{   system("cls");
		printf("��ײ��ǽ�ˣ�\n");
		a='w';v=350;
		guess=0;add=18;
		freesnake();
		printf("������÷�Ϊ��%d",guess);
		return 0;
	}
	if(death()==2)
	{
		system("cls");
		printf("��ҧ���Լ��ˣ�\n");
	    a='w';	v=350;
		guess=0;add=18;
		freesnake();
		printf("������÷�Ϊ��%d",guess);
		return 0;
	}

}

//�ж�ײǽ����ҧ���Լ�
int death()
{
	snake *q=head->next;
	if(head->x==48||head->x==0||head->y==0||head->y==29)//ײǽ
	{
		//free(q);
		return 1;
	}
	while(q)//ҧ���Լ�
	{
		if(q->x==head->x&&q->y==head->y)
		{
			//free(q);
			return 2;
		}
		q=q->next;
	}
}

//�����ƶ�
void snakemove()
{
		snake *nexthead;
		int a=1;
	while(a)
	{
		p=head;
		nexthead=(snake*)malloc(sizeof(snake));
		if(4==control())//������
		{
			nexthead->x=head->x+2;
			nexthead->y=head->y;
			nexthead->next=head;
			head=nexthead;
			pos(head->x,head->y);
			printf("��");
		}
		else if(2==control())//������
		{
			nexthead->x=head->x-2;
			nexthead->y=head->y;
			nexthead->next=head;
			head=nexthead;
			pos(head->x,head->y);
			printf("��");
		}
		else if(3==control())//������
		{
			nexthead->y=head->y+1;
			nexthead->x=head->x;
			nexthead->next=head;
			head=nexthead;
			pos(head->x,head->y);
			printf("��");
		}
		else if(1==control())//������
		{
			nexthead->y=head->y-1;
			nexthead->x=head->x;
			nexthead->next=head;
			head=nexthead;
			pos(head->x,head->y);
			printf("��");
		}
		pos(0,31);
		printf("ʳ���ֵ��%d",add);
		if(!(head->x==food->x&&head->y==food->y))
		{
			while(p->next->next)
				p=p->next;
		    pos(p->next->x,p->next->y);
			printf("  ");
			free(p->next);
			p->next=NULL;
			p=NULL;
		}
		if(head->x==food->x&&head->y==food->y)
		{
			guess+=add;
			pos(0,32);
			printf("������%d",guess);
			free(food);
			snakefood();
		}
		Sleep(v);
		a=endgame();
	}
}

void pos(int x,int y)//������
{
	COORD c={x,y};
	HANDLE a=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(a,c);
}

void wall()//ǽ���ӡ
{
	
	for(x=0;x<50;x+=2)//��ӡ������
	{
		pos(x,0);
		printf("��");
		pos(x,29);
		printf("��");
	}
	
	for(y=1;y<30;y++)//��ӡ������
	{
		pos(0,y);
		printf("��");
		pos(48,y);
		printf("��");
	}
}

int control()//�������ƶ��ķ���
{
	char i;
	if(kbhit())
		i=getch();
	if(i=='w'||i=='a'||i=='s'||i=='d')
		a=i;
	if(i=='z')
	{
		v-=50;
		add+=2;
	}
	if(i=='x')
	{
		v+=50;
		add-=2;
	}
	if(v>=650)
	{
		v=650;
		add=4;
	}
	if(v<=0)
	{
		v=50;
		add=32;
	}
	if(i=='p')
	while(1)
	{
		i='0';
		if(kbhit())
			i=getch();
		if(i=='p')break;
	}
	if(a=='w')return 1;
	else if(a=='a')return 2;
	else if(a=='s')return 3;
	else if(a=='d')return 4;
}

void createsnake()//��
{
	p=(snake*)malloc(sizeof(snake));
	p->x=2;
	p->y=27;
	p->next=NULL;
	for(int i=0;i<4;i++)
	{
		head=(snake*)malloc(sizeof(snake));
		head->x=2;
		head->y=27-i;
		head->next=p;
		p=head;
	}
	while(p)
	{
		pos(p->x,p->y);
		printf("��");
		p=p->next;
	}
	p=NULL;
}
void snakefood()//����ʳ��
{
	int i;
	food=(snake*)malloc(sizeof(snake));
	p=head;
	loop:srand(time(NULL));
	i=rand();
	food->x=(int)(i)*1000*2%46+2;
	srand(time(NULL));
	i=rand();
	food->y=(int)(i)*1000%28+1;
	while(p)
	{
	if(p->x==food->x&&p->y==food->y)goto loop;
	p=p->next;
	}
	pos(food->x,food->y);
	printf("��");
}