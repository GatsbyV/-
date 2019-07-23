#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#include"tree.h"
#define MAXITEMS 50 



//***********局部数据类型


typedef struct pair
 {
 	Trnode *parent;
 	Trnode *child;
 	
 } Pair;



//***********局部函数声明 


static Trnode *MakeNode(const Item *pi);
static void AddNote(Trnode *new_node,Trnode *root);
static bool ToLeft(const Item *i1,const Item *i2);
static bool ToRight(const Item *i1,const Item *i2);
static void DeleteNode(Trnode **ptr);
static Pair SeekItem(const Item *pi,const Tree *ptree);
void static InOrder(const Trnode *root,void (*pfun)(Item item));
static void DeleteAllNodes(Trnode *root);


//*********静态局部函数****** 


//******增加节点******** 
static Trnode *MakeNode(const Item *pi)
{
	Trnode *new_node;
	new_node=(Trnode *)malloc(sizeof(Trnode));
	if(new_node != NULL)
	{
		new_node->item=*pi;
		new_node->left=NULL;
		new_node->right=NULL;
	}
		return new_node;

}


//******增肌节点******

static void AddNote(Trnode *new_node,Trnode *root)
{
	if(ToLeft(&new_node->item,&root->item))
	{
		if(root->left==NULL)
		root->left=new_node;
		else 
		AddNote(new_node,root->left);		
	}
	else if(ToRight(&new_node->item,&root->item))
	{
		if(root->right==NULL)
		root->right=new_node;
		else 
		AddNote(new_node,root->right);		
	}
		else
		{
			fprintf(stderr,"locaton error in AddNote()\n");
			exit(1); 
		}
		
}


//*****左右项比较函数*******

static bool ToLeft(const Item *i1,const Item *i2)
{
	int comp1;
	if(i1->y<i2->y)
	return true;
	else
	return false;
}

static bool ToRight(const Item *i1,const Item *i2)
{
	int comp1;
	if(i1->y>i2->y)
	return true;
	else
	return false;
}

//******删除节点******

static void DeleteNode(Trnode **ptr)
{
	Trnode *temp;
	if( (*ptr)->left==NULL)
	{
		temp=*ptr;
		*ptr=(*ptr)->right;
		free(temp);	
	}
	else if((*ptr)->right==NULL)
	{
		temp=*ptr;
		*ptr=(*ptr)->left;
		free(temp);
	}
	else
	{
		for(temp=(*ptr)->left;temp->right!=NULL;temp=temp->right)
		continue;
		temp->right=(*ptr)->right;
		temp=*ptr;
		*ptr=(*ptr)->left;
		free(temp);		
	}
 } 
 
 
// *********寻找项 
 static Pair SeekItem(const Item *pi,const Tree *ptree)
 {
 	Pair look;
 	look.parent=NULL;
 	look.child=ptree->root;
 	if(look.child==NULL)
 	return look;
 	while (look.child!=NULL)
 	{
 		if(ToRight(pi,&(look.child->item)))
 		{
 			look.parent=look.child;
 			look.child=look.child->right;
 			continue;
		 }
		 else if(ToLeft(pi,&(look.child->item)))
		 {
		 	look.parent=look.child;
		 	look.child=(look.child)->left;
		 	continue;
		 }
		 else
		 return look;
		 break;
	}
 }
 
 
// *************遍历节点 
 
 
 void static InOrder(const Trnode *root,void (*pfun)(Item item))
 {	if(root!=NULL)
 {
 	InOrder(root->left,pfun);
 	(*pfun)(root->item);
 	InOrder(root->right,pfun);
 }	
 }


static void DeleteAllNodes(Trnode *root)
{	
	Trnode *pright;
	if(root!=NULL)
	{
		pright=root->right;
		DeleteAllNodes(root->left);
 		free(root);
 		DeleteAllNodes(pright);		
	}
	
}


//******************公共接口函数


//**************初始化树


void InitializeTree(Tree *ptree)
{
	ptree->root=NULL;
	ptree->size=0;
 } 

//***************确认树是否为空


bool TreeIsEmpty(const Tree *ptree)
{
	if(ptree->root==NULL)
	return true;
	else
	return false;
 } 
 
 
//**************寻找项 


bool InTree(const Item *pi,const Tree *ptree) 
{
	return(SeekItem(pi,ptree).child==NULL)?false:true;
}


//*****************确认树是否为满


bool TreeIsFull(const Tree *ptree)
{
	if(ptree->size==MAXITEMS)
	return true;
	else
	return false;
 } 
 
// *********************计数树的节点 


 int TreeItemCount(const Tree *ptree)
 {
 	return ptree->size;
 }
 
 
//**********************增加项


bool AddItem(const  Item *pi,Tree *ptree)
{
	Trnode *new_node;
	if(TreeIsFull(ptree))
	{
		fprintf(stderr,"Tree is full\n");
		return false;
	}
		
	else if(SeekItem(pi,ptree).child!=NULL)
	{
		fprintf(stderr,"tempted to add a duplicate item\n");
		return false;
	}
		else
		new_node=MakeNode(pi);
		if(new_node==NULL)
		{
			fprintf(stderr,"couldn't create a new node");
			return false;
		}
		
		ptree->size++;
	if(ptree->root==NULL)
	ptree->root=new_node;
	else
	AddNote(new_node,ptree->root);
	return true;

 } 
//**************删除项


bool DeleteItem(const Item *pi,Tree *ptree)
{
	Pair look;
	look=SeekItem(pi,ptree);
	if(look.child==NULL)
	return false;
	else if(look.child==ptree->root)
	DeleteNode(&(ptree->root));
	else if(look.child==look.parent->left)
	DeleteNode(&look.parent->left);
	else
	DeleteNode(&look.parent->right);
	ptree->size--;
	return true;
 } 
 
 
// ************遍历项 
 
 
  void Traverse(const Tree *ptree,void (*pfun)(Item item))
 {
 	if(ptree->root!=NULL)
 	InOrder(ptree->root,pfun);
 } 
 
 
//************清空树
 
 
 void DeleteAll(Tree *ptree)
 {
 	if(ptree!=NULL)
 	DeleteAllNodes(ptree->root);
 	ptree->root=NULL;
 	ptree->size=0;
 }



 
