/*
	Name : Kshitij Agrawal
	Roll.no : 17EC10063	
	Date : 12/02/19
	PC : 28
	Topic : Stacks, Queues and Trees
*/
#include<iostream>
#include<stdlib.h>
#include "BB5.h"
#include <time.h>

using namespace std;


typedef struct{
	STACK F,B;
} QUEUE;

QUEUE QUINT()
{
	QUEUE Q;
	Q.F = SINIT();
	Q.B = SINIT();
//	cout << ISEMPTY(Q.F) << '\n';
//	cout << ISEMPTY(Q.B) << '\n';
	return Q;
}
void QPRN(QUEUE Q)
{
	/*
	Q.F = PUSH(Q.F,2);
	Q.F = PUSH(Q.F,5);
	Q.F = PUSH(Q.F,3);
	Q.B = PUSH(Q.F,2);
	Q.B = PUSH(Q.F,5);
	*/
	int l = ISEMPTY(Q.F);
	int m = ISEMPTY(Q.B);

	cout << "Q = [";
	if(l == 0)
	{
		SPRNT2B(Q.F);
	}
	if(m == 0)
	{
		SPRNB2T(Q.B);
	}
	cout << "]\n";
}

QUEUE ENQUEUE(QUEUE Q,int x)
{
	Q.B = PUSH(Q.B,x);
	QPRN(Q);
	return Q;
}

QUEUE DEQUEUE(QUEUE Q)
{
	int l = ISEMPTY(Q.F);	// size of Q.F
	int m = ISEMPTY(Q.B);	// size of Q.B
	if(l)	//Q.F Empty ---> switch queues
	{
		if(m)	//Both stacks empty so simply bypass the if-else
		{
			cout << "Q : [ Can't dequeue as Queue is Empty ]\n";
			return Q;
		}
		else
		{
			int v;
			while(!m)	//Transfer all elements from Q.B to Q.F --> !m returns 1 if queue is not empty
			{
				v = TOP(Q.B);
				Q.B = POP(Q.B);
				Q.F = PUSH(Q.F,v);
				m = ISEMPTY(Q.B);
			}
			Q.F = POP(Q.F);	//Actual dequeue from front stack
		}
	}
	else
	{
		Q.F = POP(Q.F);	// Front queue is not empty directly 
	}
	QPRN(Q);
	return Q;

}

int hgt(TREE T)
{
	if(T == NULL)return 0;
	else
	{
		int ll = hgt(T -> L);
		int rr = hgt(T -> R);
		if(ll > rr)
			return 1 + ll;
		return 1 + rr;
	}
}

void print(TREE T,int level){

	if(T == NULL)return;
	if(level == 1){
		cout << T -> key << ' ';
		return;
	}

	else if(level > 1){
		print(T -> L,level - 1);
		print(T -> R,level - 1);
	}
}

void SETN(TREE T)
{
	if(T == NULL)return;

	if(T -> L) T -> N = T -> L;
	else if(T -> R)T -> N = T -> R;
	else{T -> N = NULL;return;}

	TREE p,q;
	p = q = T;
	while(p){
		if(p -> L){
			if(p -> R)p -> L -> N = p -> R;
			else{
				q = q -> N;
				while(q){
					if(q -> L){p -> L -> N = q -> L;break;}
					else if(q -> R){p -> L -> N = q -> R;break;}
					else q = q -> N;
				}
				if(q == NULL){
					p -> L -> N = NULL;
					return;
				}
			}
		}
		if(p == q)q = q -> N;
		if(p -> R){
			while(q){
				if(q -> L){p -> R -> N = q -> L;break;}
				else if(q -> R){p -> R -> N = q -> R;break;}
				else q = q -> N;
			}
			if(q == NULL){
				p -> R -> N = NULL;
				return;
			}
		}
		p = p -> N;
	}
}

void TPRLN(TREE T){
	while(T -> N){
		cout << T -> key << ' ';
		T = T -> N;
	}
	cout << '\n';
}

int main(int argc, char const *argv[])
{
//	srand (time(NULL));
	registerme();
	QUEUE Q;
	Q = QUINT();
	cout << "n = ";
	int n,i,choice;
	cin >> n;
	int enq,deq;
	
	cout << "+++ Part 1\n";
	cout << "\tQINIT(): \tQ = [ ]\n";
	enq = deq = n;
	for(i = 1;i <= 2*n;i++)
	{
		choice = rand() % 2;
		if(choice == 0)
		{
			if(enq)
				enq--;
			else //enqueue operations already n so flip choice
				choice = 1;
		}
		else
		{
			if(deq){
				if(ISEMPTY(Q.F) && ISEMPTY(Q.B))
				{
					choice = 0;
				}	
				else
					deq--;
			}
			else //dequeue operations already n so flip choice
				choice = 0;
		}
		int element = rand() % 1000;
		if(choice == 0)
		{
			cout << "\tENQUEUE(" << element << ") :  ";
			Q = ENQUEUE(Q,element);
		}
		else
		{
			cout << "\tDEQUEUE():\t";
			Q = DEQUEUE(Q);
		}
	}
	
	cout << "+++ Part 2\n";
	cout << "\n--- Generated tree\n";
	TREE T;

	T = TGEN(n);
	TPRN(T);

	cout << "\n--- Level-by-level printing\n";

	SETN(T);
	TPRLN(T);
	return 0;
}