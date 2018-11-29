#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZEBUF 80
typedef struct list
	{
	float num;
	int drob;
	struct list *adress;//obyavlenie structury
	}list;
list *head=NULL;
void errors(int kod)//errors determinate
	{
	switch (kod)
		{
		case 1:
			perror("form of argument <prog> <filename>\n");
		case 2:
			perror("cannot open file\n");                     
		case 3:
			perror("no memory for word\n");
		case 4:
			perror("no memory for struct\n");
		}
	exit(1);
	}//errdet
int delimword(char sym)//check delims
	{
	if (isspace(sym)==0)
			return 0;
	else 
			return 1;
	}//chdel
void sdvig(char *buf,int n)
	{
	int i;
	for (i=0;i<n-1;i++)
		buf[i]=buf[i+1];
	buf[n-1]='\0';
	}
int testnum (char *buf,int n)//check digit
	{
	int j;
	int k=0,m;
	if (buf[0]=='-')
		{
		sdvig(buf,n);
		n--;
		}
	for (j=0;j<n-1 && k<1;j++)	
		{
		if ((buf[j]=='.'))
			k++;
		}
	m=j;
	if (k==0)
		{
		for (j=0;j<n;j++)
				if ((isdigit(buf[j])==0))
					return -1;
		return 0;
		}
	else
		{
		for (j=0;j<m-1;j++)
				if ((isdigit(buf[j])==0))
					return -1;
		for (j=m;j<n;j++)
				if ((isdigit(buf[j])==0))
					return -1;
		return n-m;
		}		
	}//chdig
void insertfirst(list **head,list *new,float copy,int x)//insert first word
	{
		new->adress=*head;
		new->num=copy;
		new->drob=x;
		*head=new;
	}
void insertafter(list *work,list *new,float copy,int x)//insert after choosed word
	{
		new->adress=work->adress;
		new->num=copy;
		new->drob=x;
		work->adress=new;
	}//
void insertbefore(list *last,list *new,list *work,float copy,int x)//insert before choosed word
	{
		last->adress=new;
		new->adress=work;
		new->num=copy;
		new->drob=x;
	}//
void insertlocal (list **head,list *new,float copy,list *work,list *p,int x)//choose the kind of insert
	{
		if (work!=*head)
			if (copy<work->num)
					insertafter(work,new,copy,x);
			else
				insertbefore(p,new,work,copy,x);	
		else
			if (copy>work->num)
					insertfirst(head,new,copy,x);
			else
					insertafter(work,new,copy,x);
	}
void make(FILE *file)
	{
	char buf[SIZEBUF];
	float copy;
	register int i=0;
	char c;
	int x,znak=1;
	list *new,*work,*last;
	while ((c=fgetc(file))!=EOF)
		{
		if (delimword(c)==0)					
				buf[i++]=c;
		else
			{
			if (i!=0)
				{
				buf[i]='\0';
				if (buf[0]=='-')
					znak=-1;
				if ((x=testnum(buf,i))!=-1)
					{
						if((new=(list*)malloc(sizeof(list)))==NULL)
							 errors(4);
						copy=znak*atof(buf);
						if (head==NULL)
							insertfirst(&head,new,copy,x); 
						else
							{
							work=head;
							while((work->adress!=NULL) && (copy<work->num))
										{ 
										last=work;
										work=work->adress;
										}
							insertlocal(&head,new,copy,work,last,x);//enter local element
							}
		
					}
				i=0;
				znak=1;	
				}
			}	
		}	
	}
void out(list **head)
	{
	list *work;
	work=*head;
	for (work=*head;work!=NULL;work=work->adress)
		printf("%.*f  ",work->drob,work->num);
	printf("\n");
	}
void memory(list **head)
	{
	list *work;
	work=*head;
	for (work=*head;work!=NULL;work=work->adress)
		free(work);
	}
void main(int argc,char *argv[]) {
	FILE *file;
	if (argc!=2)//error of enter
		errors(1);
	if ((file=fopen(argv[1],"r"))==NULL)// error of open file
		errors(2);
	make(file);
	out(&head);
	fclose(file);
	printf("enter new words:\n");
	make(stdin);
	out(&head);
	memory(&head);
}
