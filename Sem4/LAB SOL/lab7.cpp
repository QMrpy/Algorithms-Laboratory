/*
	Name : Kshitij Agrawal
	Roll.no : 17EC10063	
	Date : 05/03/19
	PC : 28
*/
#include<iostream>
#include<stdlib.h>

using namespace std;

typedef struct 
{
	int val;
	int id;
	bool lr;
}ee;

typedef struct 
{
	int id;
	int l;
	int r;

}index;

void merge(ee *E,int l,int r,int m){
	int i,j,k;
	int n1,n2;
	n1 = m - l + 1;
	n2 = r - m;
	ee *a = (ee *)malloc(n1*sizeof(ee));
	ee *b = (ee *)malloc(n2*sizeof(ee));

	for(i = 0;i < n1;i++){
		a[i] = E[l + i];
	}
	for(i = 0;i < n2;i++){
		b[i] = E[m + 1 + i];
	}

	i = j = 0;
	k = l;
	while(i < n1 && j < n2){

		if(a[i].val < b[j].val){
			E[k] = a[i];
			i++;k++;
		}
		else{
			E[k] = b[j];
			j++;k++;
		}
	}
	while(i < n1){
		E[k++] = a[i++];
	}
	while(j < n2){
		E[k++] = b[j++];
	}
	return;
}

void sort(ee *E,int l,int r){

	if(l < r){
		int m = l + (r - l)/2;
		sort(E,l,m);
		sort(E,m + 1,r);
		merge(E,l,r,m);
	}
	return;
}

void insertQ(index *Q,int k,int idl,int x,index *I,ee *E,int *idx){

	idl++;
	Q[idl].l = x;
	Q[idl].r = I[E[k].id].r;
	Q[idl].id = E[k].id;

	int i = idl;	

	while(i >= 0){

		int p = (i - 1)/2;

		if(Q[p].r >= Q[i].r)break;
		else{

			int r;
			r = idx[Q[p].id];
			idx[Q[p].id] = idx[Q[i].id];
			idx[Q[i].id] = r;

			index t = Q[p];
			Q[p] = Q[i];
			Q[i] = t;
			i = p;
		}
	} 

	// for(i = 0;i < idl;i++){
	// 	cout << Q[i].id << ' ' << Q[i].l << "," << Q[i].r << '\n';
	// }
	// cout << "_____________\n";
	return;
}

void heapify(index *Q,int i,int idl,index *I,ee *E,int *idx){

	while(i <= idl){

		int l = 2*i + 1;
		int r = 2*i + 2;
		int m;
		if(l > idl)break;
		if(l == idl)m = l;
		else{
			m = (Q[l].r >= Q[r].r ? l : r);
			if(Q[i].r >= Q[m].r)break;
			else{
				index t = Q[i];
				Q[i] = Q[m];
				Q[m] = t;
				i = m;
				int r = idx[i];
				idx[i] = idx[m];
				idx[m] = r;
			} 
		}
	}
	return;

}

void deleteQ(index *Q,int k,int *idl,int x,index *I,ee *E,int *idx){

	int l = Q[*idl].id;
	l = idx[l];
	{
		index t = Q[*idl];
		Q[l] = t;

		int r;
		r = idx[*idl];	//E[k].id = *idl
		idx[*idl] = idx[l];
		idx[l] = r;

		(*idl)--;
		idx[E[k].id] = -1;
		heapify(Q,l,*idl,I,E,idx);
	}
	// for(int jj = 0;jj < *idl;jj++){
	// 		cout << Q[jj].id << ' ' << Q[jj].l << "," << Q[jj].r << '\n';
	// }

	return;
}


void mincover(index *I,int n){

	ee *E = (ee *)malloc(2*n*sizeof(ee));
	int i,j,k;
	int R,L;
	L = 0;
	R = 0;
	int *idx = (int *)malloc(n*sizeof(int));
	for(i = 0;i < n;i++){
		idx[i] = -1;
	}
	for(i = 0;i < n;i++){

		E[2*i].val = I[i].l;
		E[2*i].id = i;
		E[2*i].lr = 0;

		E[2*i + 1].val = I[i].r;
		E[2*i + 1].id = i + 1;
		E[2*i + 1].lr = 1;

		L = min(L,I[i].l);
		L = min(L,I[i].r);

		R = max(R,I[i].l);
		R = max(R,I[i].r);

	}

	sort(E,0,2*n - 1);	//mergesort
	// for(i = 0;i < 2*n;i++){
	// 	cout << E[i].id << ' ' << E[i].val << ' ' << E[i].lr << '\n';
	// }

	index *Q = (index *)malloc(n*sizeof(index));

	Q[0].l = E[0].val;
	Q[0].r = I[E[0].id].r;
	Q[0].id = E[0].id;
	idx[E[0].id] = 0;
	int x = Q[0].r;
	k = 0;
	j = 1;
	int total = 1;
	cout << "+++ Finding minimum cover\n";
	cout << "Added interval : ";
	cout << Q[0].id << ' ' << '[' << Q[0].l << "," << Q[0].r << "]\n";
	while(x < R){
		k++;
		if(E[k].lr == 0){	//left endpoint
			idx[E[k].id] = j;
			insertQ(Q,k,j,E[k].val,I,E,idx);
			j++;
			//insert
		// cout << "___________\n";
		// for(int jj = 0;jj < j;jj++){
		// 		cout << Q[jj].id << ' ' << Q[jj].l << "," << Q[jj].r << '\n';
		// }

		}
		else{	//right endpoint
			//delete
			// cout << E[k].val << '\n';
			// cout << j << '\n';
			index t = Q[0];

			deleteQ(Q,k,&j,E[k].val,I,E,idx);
			if(E[k].val == x){
				cout << "Added interval : ";
				cout << t.id << ' ' << '[' << t.l << "," << t.r << "]\n";
				x = t.r;
				total++;
			}
		}
	}
	cout << "Total number of intervals = " << total << '\n';
	return;
}


int main()
{
	int n,i,j,k,l,r;
	cout << "n = ";
	cin >> n;
	index *I = (index *)malloc(n*sizeof(index));

	for(i = 0;i < n;i++){
		cin >> l >> r;
		I[i].l = l;
		I[i].r = r;
	}
	mincover(I,n);
	return 0;
}
