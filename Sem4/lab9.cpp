/*
	Name : Kshitij Agrawal
	Roll.no : 17EC10063	
	Date : 19/03/19
	PC : 28
	Disjoint Set Union
*/
#include<iostream>
#include<stdlib.h>
using namespace std;
#define debug cout << "Ok..\n";



typedef struct cell
{
	int size;
	struct cell *parent;	
}tree;

void initsets(tree **t,int n){
	int i,j;
	for(i = 0;i <= n;i++){
		for(j = 0;j < n;j++){
			t[i][j].size = 1;
			t[i][j].parent = NULL;
		}
	}
}

tree* findsets(tree **t,int i,int j){

	if(t[i][j].parent == NULL){
		return &t[i][j];
	}
	while((t[i][j].parent) -> parent != NULL){

		t[i][j].parent  = (t[i][j].parent) -> parent;
	}
	return t[i][j].parent;
}

void mergesets(tree *p,tree *q){

	if(p -> size > q -> size){
		q -> parent = p;
		p -> size += q -> size;
	}
	else{
		p -> parent = q;
		q -> size += p -> size;
	}
	return;
}

void MergeRegions(int **a,tree **t,int n){

	int i,j;
	tree *p,*q;

	for(i = 1;i < n;i++){	//Merge all cells in the 1st row with (0,0)

		p = findsets(t,0,i);
		q = findsets(t,0,i - 1);
		if(p != q)
			mergesets(p,q);
	}

	for(i = 1; i <= n ;i++){
		for(j = 0;j < n;j++){
			if(a[i][j]){
				if(a[i - 1][j])	//Search in all 4 directions to see if any '1' cell can be merged to any adjacent '1' cell
				{
					p = findsets(t,i,j);
					q = findsets(t,i - 1,j);
					if(p != q)	//If roots of both cells are same they are already in a connected component
						mergesets(p,q);
					if(j){
						if(a[i][j - 1]){
							p = findsets(t,i,j);	
							q = findsets(t,i,j - 1);
							if(p != q)
								mergesets(p,q);
							}
					}
					if(i < n && a[i + 1][j]){
						p = findsets(t,i,j);
						q = findsets(t,i + 1,j);
						if(p != q)
							mergesets(p,q);
					}
					if(j < n - 1 && a[i][j + 1]){
						p = findsets(t,i,j);
						q = findsets(t,i,j + 1);
						if(p != q)
							mergesets(p,q);

					}
				}
			}
		}
	}
}

void printmesh(int **a,tree **t,int n){	//Prints the final reachable cells
	cout << "+++ Reachable cells in the mesh\n";
	tree *p,*q;
	int i,j;
	cout << "\t +";
	for(i = 0;i < n;i++)
		cout << "_";
	cout << "+\n";
	for(i = 0;i <= n;i++){
		cout << "\t | ";
		for(j = 0;j < n;j++){
			if(a[i][j]){
				if(t[i][j].parent != NULL)
					p = findsets(t,i,j);
				else
					p = &t[i][j];
				if(p == &t[0][0]){	//Connected to root
					cout << "-";
				}
				else{	// Cell '1' but not connected
					cout << " ";
				}
			}
			else{	// '0' cell
				cout << 'X';
			}
		}
		cout << " | \n";
	}
	cout << "\t + ";
	for(i = 0;i < n;i++)
		cout << "_";
	cout << " +";
	cout << "\n";

}
void printInput(int **a,int n){		//Printing the input mesh
	cout << "+++Input Mesh\n";
	int i,j;
	cout << "\t +";
	for(i = 0;i < n;i++)
		cout << "_";
	cout << "+\n";
	for(i = 0;i < n;i++)
		cout << " ";
	cout << '\n';
	for(i = 1;i <=n; i++){
		cout << "\t | ";
		for(j = 0;j < n;j++){
			if(a[i][j] == 0)cout << "X";
			else cout << " ";
		}
		cout << " | \n";
	}
	cout << "\t + ";
	for(i = 0;i < n;i++)
		cout << "_";
	cout << " +";
	cout << "\n";

}
bool FindReach(int **a,tree **t,int n){

	int i,j;
	tree *p;
	bool res = 0;
	for(i = 0;i < n;i++){
		if(a[n][i]){
			if(t[n][i].parent != NULL)
				p = findsets(t,n,i);
			else
				p = &t[n][i];
			if(p == &t[0][0]){
				res = 1;
			}
		}
	}
	return res;
}

int main()
{
	int n;
	cout << "n = ";
	cin >> n;
	int **a = (int **)malloc((n + 1) * sizeof(int *));
	tree **t = (tree **)malloc((n + 1) * sizeof(tree *));

	int i,j;
	
	for(i = 0; i <= n;i++){
		a[i] = (int *)malloc(n * sizeof(int));
		t[i] = (tree *)malloc(n * sizeof(tree));

	}

	for(i = 1;i <= n;i++){
		for(j = 0;j < n;j++){
			cin >> a[i][j];
		}
	}
	for(i = 0; i < n;i++){
		a[0][i] = 1;
	}
	printInput(a,n);
	initsets(t,n);
	MergeRegions(a,t,n);
	bool res = FindReach(a,t,n);

	if(res){
		cout << "+++Liquid can seep through the mesh\n\n";
	}
	else{
		cout << "+++Liquid cannot seep through the mesh\n\n";
	}
	printmesh(a,t,n);

	return 0;
}