#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#include"tree.h"


void printitem(Item item);
void ShowNums(const Tree *nm);
void FindNums(const Tree *nm);
void DropNums(Tree *nm);
void AddNums(Tree *nm);
char menu(void);


int main(void)
{
	Tree nums;
	char choice;
	InitializeTree(&nums);
	while((choice=menu())!='q')
	{
		switch(choice)
		{
			case'a':AddNums(&nums);
			break;
			case's':ShowNums(&nums); 
			break;
			case'f':FindNums(&nums);
			case'n':printf("%d numbers in us\n",TreeItemCount(&nums));
			break;
			case'd':DropNums(&nums);
			break;
			default:puts("√ª’‚∏ˆ√¸¡Ó£¨…µ±∆"); 
		}
	}
	DeleteAll(&nums);
	puts("Bye.");
	return 0;
} 


char menu(void)
{
	int ch;
	puts("Bianry Tree ASC system");
	puts("Enter the letter corresponding to your choice:");
	puts("a)add a number           s)show list of numbers");
	puts("n)number of numbers      f)find numbers");
	puts("d)delete a number        q)quit");
	while((ch=getchar())!=EOF)
	{
		while(getchar()!='\n')
		continue;
		if(strchr("asrfndq",ch)==NULL)
		puts("Please enter an a.s.f.n.d.or q,asshole£∫");
		else 
		break;
	}
	if(ch==EOF)
	ch='q';
	return ch;
}


void AddNums(Tree *nm)
{
	Item temp;
	if(TreeIsFull(nm))
	puts("No numbers");
	else
	{
		int i,Max;
		puts("please enter the Max_number:");
		scanf("%d",&temp.x);
		puts("please enter the number:");
		for(i=1;i<=temp.x;i++)	
		{
			scanf("%d",&temp.y);
			AddItem(&temp,nm);
		}
	}
}


void ShowNums(const Tree *nm)
{
	if(TreeIsEmpty(nm))
	puts("No entries!");
	else
	Traverse(nm,printitem);
}


void printitem(Item item)
{   int i;	
	printf("%d",item.y);
}
void FindNums(const Tree *nm)
{
	Item temp;
	if(TreeIsEmpty(nm))
	{
		puts("No entries!");
		return;	
	}
	else
	puts("Please enter number you wish to find:");
	scanf("%d",&temp.y);
	printf("%d",temp.y);
	if(InTree(&temp,nm))
	printf("is one of us" );
	else
	printf("is not one of us");
	
}


void DropNums(Tree *nm)
{
	Item temp;
	if(TreeIsEmpty(nm))
	{
		puts("No entries!");
		return;	
	}	
	else
	puts("Please enter number you wish to drop:");
	scanf("%d",&temp.y);
	printf("%d",temp.y);
	if(DeleteItem(&temp,nm))
		printf("is already dropped from us");
	else
		printf("is not one of us.\n");	
}


