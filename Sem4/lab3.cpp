/*
	Name : Kshitij Agrawal
	Roll.no : 17EC10063	
	Date : 22/01/19
	Topic : 4 pegged Tower of Hanoi
*/

#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;

extern void registerme ( int );
extern void startpart ( int );
extern void endpart ( int );
extern void makemove ( int , int , int );
extern void showpegs ( );

void ToH3(int i,int j,int p,int q,int r)	/*Auxilliary function to evaluate base cases*/
{
	if(i == j){
		makemove(j,p,q);
		return;
	}
	ToH3(i,j-1,p,r,q);
	ToH3(j,j,p,q,r);
	ToH3(i,j-1,r,q,p);
}
void ToH41(int i,int j,int p,int q,int r,int s)	/*k = m/2*/
{
	int m = j - i + 1;
	if(m == 1)	/*Only 1 disc --> move it from p to q*/
	{
		makemove(i,p,q);
		return;
	}
	if(m == 2)  /*Only 2 discs --> move 1st from p to r 2nd from p to q and 1st from r to q*/
	{
		makemove(i,p,r);
		makemove(j,p,q);
		makemove(i,r,q);
		return;
	}
	else if(m == 3)	/*Only 3 discs --> move 1st from p to s 2nd from p to r 3rd from p to q. Now 2nd from r ro q, 1st from s to q*/
	{
		makemove(i,p,r);
		makemove(i+1,p,s);
		makemove(i+2,p,q);
		makemove(i+1,s,q);
		makemove(i,r,q);
		return;
	}
	else
	{
		int k = m/2;
		ToH41(i,i+k,p,s,q,r);	/*Since k == m/2 j - k == i + k within limits of one disc shifted from one recurence to other*/
		ToH3(i+k+1,j,p,q,r);
		ToH41(i,i+k,s,q,p,r);
	}
}
void ToH42(int i,int j,int p,int q,int r,int s,int k)	/*k = sqrt(n) --> fixed*/
{
	if(i > j)return;
	int m = j - i + 1;
	if(m == 1)	/*Only 1 disc --> move it from p to q*/
	{
		makemove(i,p,q);
		return;
	}
	else if(m == 2)	/*Only 2 discs --> move 1st from p to r 2nd from p to q and 1st from r to q*/
	{
		makemove(i,p,r);
		makemove(i+1,p,q);
		makemove(i,r,q);
		return;
	}
	else if(m == 3)	/*Only 3 discs --> move 1st from p to s 2nd from p to r 3rd from p to q. Now 2nd from r ro q, 1st from s to q*/
	{
		makemove(i,p,s);
		makemove(i+1,p,r);
		makemove(i+2,p,q);
		makemove(i+1,r,q);
		makemove(i,s,q);
		return;
	}
	if(m <= k){
		ToH3(i,j,p,q,r);
		return;
	}
	else 
	{
		ToH42(i,j-k,p,s,q,r,k);	/*Similar to n - k, here j ~= n*/
		ToH3(j-k+1,j,p,q,r);
		ToH42(i,j-k,s,q,p,r,k);
		return;
	}
}

void ToH43(int i,int j,int p,int q,int r,int s)	/*k = sqrt(2*m) --> variable*/
{
	int m = j - i + 1;
	if(i > j)return;
	if(m == 1)	/*Only 1 disc --> move it from p to q*/
	{
		makemove(i,p,q);
		return;
	}
	if(m == 2)	/*Only 2 discs --> move 1st from p to r 2nd from p to q and 1st from r to q*/
	{
		makemove(i,p,r);
		makemove(i+1,p,q);
		makemove(i,r,q);
		return;
	}
	else if(m == 3)	/*Only 3 discs --> move 1st from p to s 2nd from p to r 3rd from p to q. Now 2nd from r ro q, 1st from s to q*/
	{
		makemove(i,p,r);
		makemove(i+1,p,s);
		makemove(i+2,p,q);
		makemove(i+1,s,q);
		makemove(i,r,q);
		return;
	}
	else
	{
		int k = sqrt(2*m);
		ToH43(i,j-k,p,s,q,r);	/*Similar to n - k, here j ~= n*/
		ToH3(j-k+1,j,p,q,r);
		ToH43(i,j-k,s,q,p,r);
		return;
	}
}

int main()
{
	int n;
	cout << "n = ";
	cin >> n;
	int k = int(sqrt(n));
	registerme(n);
	
	/*Game 1 : k = (j - i + 1)/2*/
	startpart(1); 
	ToH41(1,n,0,1,2,3); 
	endpart(1);

	/*Game 1 : k = sqrt(n)*/
	startpart(2); 
	ToH42(1,n,0,1,2,3,k); 
	endpart(2);
	
	/*Game 1 : k = sqrt(2*(j - i + 1))*/	
	startpart(3); 
	ToH43(1,n,0,1,2,3); 
	endpart(3);
	return 0;
}