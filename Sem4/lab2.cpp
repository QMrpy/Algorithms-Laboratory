/*
	Name : Kshitij Agrawal
	Roll.no : 17EC10063	
	Date : 15/01/19
	Topic : Polynomial vs logarithmic running times
*/

#include<iostream>
#include<stdlib.h>
using namespace std;

extern void registerme ( );
extern void startgame ( int );
extern int valquery ( int );
extern int sgnquery ( int );
extern int delquery ( int );
extern int sumquery ( int );
extern void checksoln ( int, int );

/*Linear search*/
void playgame0()
{
	startgame(0);
	int i = 0,l,r,g,N;
	N = 1e9;
	while(i < N)
	{
		g = valquery(i);
		if(g != i)
		{
			l = i;
			r = g;
			break;
		}
		i++;
	}
	checksoln(l,r);
	return;
}

bool bin_search(int low,int high,int *l,int *r)
{
	if(low <= high)	
	{
		int mid = (low + high)/2;
		int q = valquery(mid);
		if(q != mid){
			*l = mid;
			*r = q;	
			return 1;
		}
		else
		{
			q = bin_search(low,mid-1,l,r);
			if(q == 1)
				return 1;
			else
			{
				q = bin_search(mid+1,high,l,r);
			}
			return q;
		}
	}
	else
		return 0;
}
/* Game 1 Divide and Conquer */
void playgame1()
{
	startgame(1);
	int N = 1e9;
	int l = 0,r = 0;
	bin_search(0,N-1,&l,&r);
	if(l > r)
	{
		int t = l;
		l = r;
		r = t;
	}
	checksoln(l,r);
}
void bin_search_2(int low,int high,int *min_1)
{
	if(low <= high)
	{
		int mid = (low + high)/2;
		int q = sgnquery(mid);
		//cout << "mid = " << mid << " q = " << q << '\n';
		if(q == 1 || q == 0)
		{
			if(mid < *min_1){	
			/* min_1 keeps track of the minimum possible index with sgn() == 0 || sgn() == 1. 
			This index is the location of the mid point*/
				*min_1 = mid;
			}
			bin_search_2(low,mid-1,min_1);
		}
		else
		{
			bin_search_2(mid+1,high,min_1);
		}
	}
	else
		return;
}

void playgame2()
{
	startgame(2);
	int N = 1e9;
	int parity = delquery(0);
	int mn = N,mx = 0,u;
	if(parity & 1)	/*R - L is odd --> R + L is odd --> 0 doesn't exist in the array*/
	{
		bin_search_2(0,N-1,&mn);
		u = 2*mn - 1;	//As mentioned in the question
	}
	else		/*R - L is even --> R + L is even --> 0 exists in the array*/
	{
		bin_search_2(0,N-1,&mn);
		u = 2*mn;	//As mentioned in the question
	}
	//cout << parity << " " << u << '\n';
	//cout << mn << " " << mx << '\n';	
	int l = (parity + u)/2;
	int r = (u - parity)/2;
	if(l > r)
	{
		int t = l;
		l = r;
		r = t;
	}
	checksoln(l,r);
}

void playgame3()
{
	startgame(3);
	int sum = sumquery(0);
	int l = 0;
	int r = 1e9 - 1;
	int m,q,t;
	while(l <= r)
	{
		m = (l + r)/2;
		q = sumquery(m);	
		if(q + sum == 2*m)	/* m is in right of r hence the sum is 2*m - r - l. adding r + l gives the value probed with*/
		{
			r = m;	/*Going in the left side*/
		}
		else if(sum - q == 2*m) /* m is in left of l hence the sum is - 2*m + r + l subtracting from r + l gives the value probed with*/
		{
			l = m;	/*Going in the right side*/
		}
		else
		{
			t = q;	/*Third and the only left region with const sum = r - l found*/
			break;
		}
	}
	//cout << t << ' ' << sum << '\n';
	int ll = (sum - t)/2;
	int rr = (sum + t)/2;
	if(ll > rr)
	{
		int t = ll;
		ll = rr;
		rr = t;
	}
	checksoln(ll,rr);
}
int main()
{
	registerme();
	playgame0();
	playgame1();
	playgame2();
	playgame3();
}

