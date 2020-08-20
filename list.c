
#define WINDOWS
//#define LINUX

#include <stdio.h>
#include <stdlib.h>

unsigned char setup();
struct NODE *List_Create();
struct NODE *List_Open();

void PLAN(struct NODE *base);


char *SubOrder[6]={
			"Maths",
			"English",
			"Chinese",
			"Physics",
			"Chemistry",
			"Others"
		 };

struct NODE
{
	int time;
	int Subject;
	char detail[50];
	struct NODE *next;
};

int main()
{
	struct NODE *base;
	if(setup()==0x00)
		base = List_Create();
	else if(setup()==0xff)
		base = List_Open();
	else if(setup()==0xaa)
		return 0;
	PLAN(base);
	return 0;
}

void PLAN(struct NODE *base)
{
	struct NODE *temp = base,*del;
	int all=0,num=0,done=0,selection;
	float perdone;
	while(temp!=NULL)
	{
		all+=temp->time;
		temp=temp-> next;
	}
	while(1)
	{
#if defined(LINUX)
		system("clear");
#elif defined(WINDOWS)
		system("cls");
#endif
		int a,blocknum;
		perdone = (float)done/all;
		blocknum = (int)(perdone * 20);
		printf("done:[");
		for(a=0;a<blocknum;a++)
			printf("#");
		for(a=0;a<20-blocknum;a++)
			printf(" ");
		printf("]%.2f all:%dmin\n",perdone,all);
		temp = base;
		while(temp!=NULL)
		{
			printf("%d.%s:%s,%d\n\n",num,SubOrder[temp->Subject],temp->detail,temp->time);
			num++;
			temp=temp->next;
		}
		num = 0;
		temp = base;
		scanf("%d",&selection);
		for(a=0;a<selection;a++)
			temp=temp->next;
		done += temp->time;
		del=temp;
		temp = base;
		if(selection==0)
			base=base->next;
		else
			for(a=0;a<selection-1;a++)
				temp=temp->next;
		temp->next = del->next;
	}
}

struct NODE *List_Create()
{
	int a,b,timetemp;
	char strtemp[50];
	struct NODE *head,*temp,*add;
	head = NULL;
	for(a=0;a<6;a++)
	{
		while(1)
		{
			printf("%d.%s:\n",a,SubOrder[a]);
			scanf("%s",strtemp);
			if(strtemp[0]=='e' && strtemp[1]=='n' && strtemp[2]=='d' && strtemp[3]=='\0')
				break;
			scanf("%d",&timetemp);
			add=(struct NODE *)malloc(sizeof(struct NODE));
			add->time = timetemp;
			add->Subject = a;
			add->next = NULL;
			for(b=0;b<50;b++)
				add->detail[b] = strtemp[b];
			if(head==NULL)
				head=add;
			else
				temp->next = add;
			temp = add;
		}
	}
	return head;
}

struct NODE *List_Open()
{
	printf("open");
	return NULL;
}

unsigned char setup()
{
	int mode;
	printf("LIST\n\n");
	printf("1.Create a new list.\n");
	printf("2.Open the last record.\n\n");
	scanf("%d",&mode);
	switch(mode)
	{
		case 1:
			return 0x00;
			break;
		case 2:
			return 0xff;
			break;
		default:
			printf("Command Not Found!\n");
			return 0xaa;
	}
}
