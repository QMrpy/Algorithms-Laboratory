   /* Name: assgn1-17EC10068
      Creator: Rupayan Sarkar
      Date: January 8, 2019
      Description: Chained Linked List
   */
   #include<iostream>
   #include<stdlib.h>
   using namespace std;
   struct node{
   int data;
   struct node *next1;
   struct node *next2;
   };
    
   struct node* createlist1(int a,int n)
   {
   int d;
   struct node *head1,*p1,*q1;
   head1=(struct node*)malloc(sizeof(struct node));
   d=a;
   head1->data=d;
   head1->next1=NULL;
   head1->next2=NULL;
   p1=head1;
   while(d<=n)
   {
   d+=a;
   q1=(struct node*)malloc(sizeof(struct node));
   q1->data=d;
   q1->next1=NULL;
   q1->next2=NULL;
   p1->next1=q1;
   p1=q1;
   }
   return head1;
   }
   
   struct node* createlist2(int a,int b,int n,struct node *h)
   {
   int m;
   struct node *head2,*p2,*q2,*ptr;
   head2=(struct node*)malloc(sizeof(struct node));
   ptr=h;
   m=b;
   if(m%a!=0)
   {
   head2->data=m;
   head2->next1=NULL;
   head2->next2=NULL;
   }
   else
   {
   while(ptr->data!=m)
   {
   ptr=ptr->next1;
   }
   head2->data=ptr->data;
   head2->next1=ptr->next1;
   head2->next2=NULL;
   }
   p2=head2;
   while(m<=n)
   {
   m+=b;
   q2=(struct node*)malloc(sizeof(struct node));
   q2->data=m;
   q2->next1=NULL;
   q2->next2=NULL;
   if(m%a!=0)
   {
   p2->next2=q2;
   p2=q2;
   }
   else if(m%a==0)
   {
   while(ptr->data!=m)
   {
   ptr=ptr->next1;
   }
   q2->next1=ptr->next1;
   p2->next2=q2;
   p2=q2;
   }
   }
   return head2;
   }
   
   
   void prnlist(struct node *hd,int ind)
   {
   struct node *pr;
   pr=hd;
   if(ind==1)
   {
   while(pr->next1!=NULL)
   {
   cout<<pr->data<<" ";
   pr=pr->next1;
   }
   cout<<"\n";
   }
   if(ind==2)
   {
   while(pr->next2!=NULL)
   {
   cout<<pr->data<<" ";
   pr=pr->next2;
   }
   cout<<"\n";
   }
   }
   
  void prnboth(struct node *hd1,struct node *hd2)
   {
   struct node *ptr1,*ptr2;
   ptr1=hd1;ptr2=hd2;
   while(ptr1->next1!=NULL||ptr2->next2!=NULL)
   {
   if(ptr1->data<ptr2->data)
   {
   cout<<ptr1->data<<" ";
   ptr1=ptr1->next1;
   }
   else if(ptr1->data>ptr2->data)
   {
   cout<<ptr2->data<<" ";
   ptr2=ptr2->next2;
   }
   else
   {
   cout<<ptr1->data<<" ";
   ptr1=ptr1->next1;
   ptr2=ptr2->next2;
   }
   if(ptr1->next1==NULL)
   {
   	cout<<ptr2->data<<" ";
   	ptr2=ptr2->next2;
   }
   else if(ptr2->next2==NULL)
   {
   	cout<<ptr1->data<<" ";
   	ptr1=ptr1->next1;
   }
   }
   }
     
   
   int main()
   {
   int n,a,b;
   cout<<"n = ";
   cin>>n;
   cout<<"a = ";
   cin>>a;
   cout<<"b = ";
   cin>>b;
   struct node *h1=createlist1(a,n);
   prnlist(h1,1);
   struct node *h2=createlist2(a,b,n,h1);
   prnlist(h2,2);
   prnboth(h1,h2);
   return 0;
   }
   


