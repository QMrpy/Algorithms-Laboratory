/*
	Name : Kshitij Agrawal
	Roll.no : 17EC10063	
	Date : 08/01/19
	Description : Chained Linked List
*/

#include<iostream>
#include<stdlib.h>
using namespace std;
#define dbg cout << "Hold right there sparky...\n";
#define dbg2 cout << "First time\n";
#define dbg3 cout << "Not so first time\n";


typedef struct node{
	int data;
	struct node* first;
	struct node* second;
}list;

int gcd(int a,int b)
{
	if(b == 0)return a;
	return gcd(b,a%b);
}
int lcm(int a,int b)
{
	return a*(b/gcd(a,b));
}
void prnlist(list *head,int type)
{
	list *p;
	p = head;
	if(type == 1)
	{
		while(p != NULL)
		{
			cout << p->data << ' ';
			p = p->first;
		}
		cout << '\n';
	}
	else
	{
		while(p != NULL)
		{
			cout << p->data << ' ';
			p = p->second;
		}
		cout << '\n';
	}

}
list *createlist1(int a,int n)
{
	list *head = (list*)malloc(sizeof(list));
	head = NULL;	
	list *p;
	int i;
	for(i=a;i<=n;i+=a)
	{
//		dbg
		list *node = (list*)malloc(sizeof(list));
		node->data = i;
		node->first = NULL;
		node->second = NULL;			
		if(head == NULL)
		{
			head = node;
			p = head;	//prev pointer in order to achive O(n)
		}
		else
		{
			p->first = node;
			p = p->first;
		}
	}
	return head;

}
list *createlist2(int b,int n,int a,list *n1)
{
	list *head = (list*)malloc(sizeof(list));
	head = NULL;	
	list *p,*q = NULL;
	int i;
	int common = lcm(a,b);
	int j = common;
	int is_first = 0;
	p = n1;
	for(i=b;i<=n;i+=b) //O(len1 + len2) ~ O(n)
	{
	//	cout << i << ' ' << j << '\n';
		if(i == j)	//Intersection found
		{
	//		dbg
			if(is_first == 0)
			{
	//			dbg2
				while(p->data != j)
				{
					p = p->first;
				}
				is_first  = 1;
			}
			else
			{
	//			dbg3;
				while(p->data != j)
				{
					p = p->first;
				}

			}
	//		if(q != NULL)
	//			 cout << q->data << '\n';
			if(head == NULL)
			{
				head = p;
				if(q == NULL)
				{
					q = head;	
				}
				else
				{
					q->second = head;
					q = q->second;
				}
			}
			else
			{
				q->second = p;
				q = p;
			}
			j += common;
		}
		else
		{
		//	dbg
			list *node = (list*)malloc(sizeof(list));
			node->data = i;
			node->first = NULL;
			node->second = NULL;			
			if(head == NULL)
			{
				head = node;
				q = head;
			}
			else
			{
				q->second = node;
				q = q->second;

			}
		}
	}
	return head;
}
void print_both(list *n1,list *n2)
{
	while(n1 != NULL && n2 != NULL)
	{
		if(n1->data < n2->data)
		{
			cout << n1->data << ' ';
			n1 = n1->first;
		}
		else if(n1->data > n2->data)
		{
			cout << n2->data << ' ';
			n2 = n2->second;
		}
		else
		{
			cout << n2->data << ' ';
			n1 = n1->first;		
			n2 = n2->second;	
		}
	}
	while(n1 != NULL)
	{
		cout << n1->data << ' ';
		n1 = n1->first;		
	}
	while(n2 != NULL)
	{
		cout << n2->data << ' ';
		n2 = n2->second;		
	}
	cout << '\n';
}
int main()
{
	int n,a,b;
	cout << "n = ";
	cin >> n;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	list *n1,*n2;
	n1 = createlist1(a,n);
	n2 = createlist2(b,n,a,n1);
	prnlist(n1,1);
	prnlist(n2,2);
	print_both(n1,n2);
}


