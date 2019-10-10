/*
	Name : Kshitij Agrawal
	Roll.no : 17EC10063	
	Date : 29/01/19
	PC : 28
*/

#include<iostream>
#include<stdlib.h>
#include<iomanip>      // std::setprecision for printing fixed number of digits after decimal

using namespace std;

typedef struct{
	int idx;
	double price;
}arr;

double max(double a,double b)
{
	if(a < b)return b;
	return a;
}
double min(double a,double b)
{
	if(a > b)return b;
	return a;
}

double expo(double a,int b)
{
	double res = 1.0;
	while(b)
	{
		if(b % 2)
			res = res * a;
		a = a*a;
		b/=2;
	}
	return res;
}

void grdsearch1(int n,double *p,double *r)
{
	cout << "+++ Greedy search 1\n";
	int i,j,k;
	bool *visited = (bool *)malloc(n * sizeof(bool));
	
	for(i=0;i<n;i++)
	{
		visited[i] = 0;
	}
	double res = 0.0;
	double curr_max = 0.0;
	int time = 0;
	double exp;
	int idx = 0;
	for(i=0;i<n;i++)
	{
		curr_max = 0.0;
		for(j=0;j<n;j++)
		{
			if(visited[j] == 0)
			{
				exp = expo(r[j],time);
				curr_max = max(curr_max,p[j]*exp);
				if(curr_max == p[j]*exp)
				{
					idx = j;
				}
			}
		}
		visited[idx] = 1;
		cout << "[ " << i << ' ' << idx << "     " << setprecision(6) << curr_max << "]\n";
		res += curr_max;
		time++;
	}
	cout << "--- Total cost = " <<  fixed << setprecision(6) << res << '\n';
	free(visited);
} 

void grdsearch2(int n,double *p,double *r)
{
	cout << "+++ Greedy search 2\n";
	int i,j,k;
	bool *visited = (bool *)malloc(n * sizeof(bool));
	arr *rev_array = (arr *)malloc(n * sizeof(arr));
	for(i=0;i<n;i++)
	{
		visited[i] = 0;
	}
	double res = 0.0;
	double curr_min = 1e15;
	int time = n-1;
	double exp;
	int idx = 0;
	for(i=n-1;i>=0;i--)
	{
		curr_min = 1e15;
		for(j=n-1;j>=0;j--)
		{
			if(visited[j] == 0)
			{
				exp = expo(r[j],time);
				curr_min = min(curr_min,p[j]*exp);
				if(curr_min == p[j]*exp)
				{
					idx = j;
				}
			}
		}
		visited[idx] = 1;
		rev_array[i].idx = idx;
		rev_array[i].price = curr_min;
		res += curr_min;
		time--;
	}
	for(i=0;i<n;i++)
	{
		cout << "[ " << i << ' ' << rev_array[i].idx << "     " << setprecision(6) << rev_array[i].price << "]\n";
	}

	cout << "--- Total cost = " <<  fixed << setprecision(6) << res << '\n';
	free(visited);
	free(rev_array);
} 

void grdsearch3(int n,double *p,double *r)
{
	cout << "+++ Greedy search 3\n";
	int i,j,k;
	bool *visited = (bool *)malloc(n * sizeof(bool));
	
	for(i=0;i<n;i++)
	{
		visited[i] = 0;
	}
	double res = 0.0;
	double curr_max = 0.0;
	double actual_max = 0.0;
	int time = 0;
	double exp;
	int idx = 0;
	for(i=0;i<n;i++)
	{
		curr_max = 0.0;
		for(j=0;j<n;j++)
		{
			if(visited[j] == 0)
			{
				exp = expo(r[j],time + 1) - expo(r[j],time);
				curr_max = max(curr_max,p[j]*exp);
				if(curr_max == p[j]*exp)
				{
					actual_max = p[j]*expo(r[j],time);
					idx = j;
				}
			}
		}
		visited[idx] = 1;
		cout << "[ " << i << ' ' << idx << "     " << setprecision(6) << actual_max << "]\n";
		res += actual_max;
		time++;
	}
	cout << "--- Total cost = " <<  fixed << setprecision(6) << res << '\n';
	free(visited);
} 
//limit checks pruning, if curr_sum > lim return. final array stores the indices of the optimal solution
void genpermutations(int *a,int n,int k,double *p,double *r,double *limit,int *final)
{
	int i,j,t;
	if(k == n)
	{
		int time = 0;
		double curr_max = 0.0;
		double res = 0;
		double exp = 0.0;
		int idx = 0;
		for(i=0;i<n;i++)
		{
			exp = expo(r[a[i]],time);
			res += p[a[i]]*exp;
			time++;
			if(res > *limit)
			{
				return;
			}
		}
		if(*limit > res)
		{	
			*limit = res;
			for(i=0;i<n;i++)
			{
				final[i] = a[i];
			}			
		}
	}
	for(i=k;i<n;i++)
	{
		t = a[i];
		a[i] = a[k];
		a[k] = t;

		genpermutations(a,n,k+1,p,r,limit,final);
		
		t = a[i];
		a[i] = a[k];
		a[k] = t;

	}
}

void exhsearch(int n,double *p,double *r)
{
	cout << "+++ Exhaustive search\n";
	if(n > 12)
	{
		cout << "*** n is too large, skipping exhaustive search\n";
		return;
	}
	int *a = (int *)malloc(n * sizeof(int));
	int *final = (int *)malloc(n * sizeof(int));
	int i,j,k,idx,time = 0;
	double exp,curr_max,res;
	curr_max = res = 0;
	for(i=0;i<n;i++)
	{
		a[i] = i;
		final[i] = 0;
	}
	double limit = 1e15;
	genpermutations(a,n,0,p,r,&limit,final);
	for(i=0;i<n;i++)
	{
		exp = expo(r[final[i]],time);
		res += p[final[i]]*exp;
		time++;
		cout << "[ " << i << ' ' << final[i] << "     " << setprecision(6) << p[final[i]]*exp << "]\n";
	}
	cout << "--- Total cost = " <<  fixed << setprecision(6) << res << '\n';
	free(final);
	free(a);
}
int main()
{
	int n;
	cout << "n = ";
	cin >> n;
	cout << "Initial prices\n";
	double *p = (double *)malloc(n * sizeof(double));
	int i,j,k;
	for(i=0;i<n;i++)
		cin >> p[i];
	cout << "Appreciation rates\n";
	double *r = (double *)malloc(n * sizeof(double));
	for(i=0;i<n;i++)
		cin >> r[i];
	grdsearch1(n,p,r);
	grdsearch2(n,p,r);
	grdsearch3(n,p,r);
	exhsearch(n,p,r);

	free(p);
	free(r);
	return 0;

}
/*
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
*/