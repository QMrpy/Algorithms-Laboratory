/*
*	Name : Kshitij Agrawal
*	Roll.no : 17EC10063	
*	Date : 02/04/19
*	PC : 28 (EVEN)
*	BFS/DFS
*/

#include<iostream>
#include<stdlib.h>
using namespace std;
#define debug cout << "Ok..\n";

typedef struct c{
	int x,y;
}cell;

cell** initmaze(int **h,int **v,int m,int n){

	cell **p = (cell **)malloc(m * sizeof(cell *));

	int i,j;
	for(i = 0;i < m;i++){
		p[i] = (cell *)malloc(n * sizeof(cell));
	}

	for(i = 0;i < m;i++){
		for(j = 0;j < n;j++){
			p[i][j].x = p[i][j].y = -1;
		}
		// cout << '\n';
	}

	return p;
}

void prnmaze(cell **p,int **h,int **v,int m,int n){

	int i,j;
	for(i = 0; i < n;i++){
		cout << "+---";
	}
	cout << "+\n";

	for(i = 0;i < m; i++){
		cout << "|";
		for(j = 0;j < n;j++){
			cout << "   ";
			if(j < n - 1){
				if(v[i][j])cout << "|";
				else cout << " ";
			}
			if(j == n - 1)
				cout << "|\n";
		}
		for(j = 0;j < n;j++){
			if(i < m - 1){
				if(h[i][j])cout << "+---";
				else cout << "+   ";
			}
		}
		if(i != m - 1)
			cout << "+\n";
		else
			cout << "+";
	}
	for(i = 0; i < n;i++){
		cout << "---+";
	}
	cout << '\n';

}


void dfs(cell **p,int **h,int **v,int m,int n,bool **vis,int i,int j,int dx[],int dy[]){

	if(vis[i][j])return;

	int k = rand() % 4;

	// cout << k << ' ';

	vis[i][j] = 1;

	int possible = 0;

	int x,y,direction;
	for(int r = 0;r < 4;r++){

		x = i + dx[(r + k) % 4];
		y = j + dy[(r + k) % 4];

		if(x >= 0 && x < m && y >= 0 && y < n){
			if(vis[x][y] == 0){
				direction = (r + k) % 4;
	//			cout << direction << " : ";
	//			cout << x << ' ' << y << "\n";
				if(direction == 0){
					p[i][j + 1].x = i;
					p[i][j + 1].y = j;
					v[i][j] = 0;
				}
				else if(direction == 1){
					p[i + 1][j].x = i;
					p[i + 1][j].y = j;
					h[i][j] = 0;
				}
				else if(direction == 3){
					p[i - 1][j].x = i;
					p[i - 1][j].y = j;
					h[i - 1][j] = 0;
				}
				else{
					p[i][j - 1].x = i;
					p[i][j - 1].y = j;
					v[i][j - 1] = 0;
				}
				dfs(p,h,v,m,n,vis,x,y,dx,dy);
			}
		}
	}
}

cell genmaze(cell **p,int **h,int **v,int m,int n,bool **vis){

	int r,s;
	int dx[] = {0, 1, 0 , -1};
	int dy[] = {1, 0, -1 , 0};
	r = s = 0;
	r = rand() % m;
	s = rand() % n;
	// cout << r << ' ' << s << '\n';
	dfs(p,h,v,m,n,vis,r,s,dx,dy);

	cell root;
	root.x = r;
	root.y = s;
	return root;
}
void printpath(cell **p,int **h,int **v,int m,int n,int **res,cell s,cell t){
	int i,j;
	for(i = 0; i < n;i++){
		cout << "+---";
	}
	cout << "+\n";

	for(i = 0;i < m; i++){
		cout << "|";
		for(j = 0;j < n;j++){
			if(res[i][j]){
				if(s.x == i && s.y == j)
					cout << " S ";
				else if(t.x == i && t.y == j)
					cout << " T ";
				else
					cout << " X ";
			}
			else
				cout << "   ";
			if(j < n - 1){
				if(v[i][j])cout << "|";
				else cout << " ";
			}
			if(j == n - 1)
				cout << "|\n";
		}
		for(j = 0;j < n;j++){
			if(i < m - 1){
				if(h[i][j])cout << "+---";
				else cout << "+   ";
			}
		}
		if(i != m - 1)
			cout << "+\n";
		else
			cout << "+";
	}
	for(i = 0; i < n;i++){
		cout << "---+";
	}
	cout << '\n';

}

void findtarget(cell **p,int **h,int **v,int m,int n,cell s,cell t,cell root){

	int i = s.x;
	int j = s.y;
	// cout << i << ',' << j << '\n';
	cout << "+++ Path from S = (" << i << ',' << j << ") to T = (";

	int **res = (int **)malloc(m * sizeof(int *));
	for(i = 0;i < m; i++){
		res[i] = (int *)malloc(n * sizeof(int));
		for(j = 0;j < n;j++)
			res[i][j] = 0;
	}

	i = s.x;j = s.y;
	int f,g;
	while(i != -1 && j!= -1){
		// cout << "(" << i << ',' << j << ")\n";
		res[i][j] = 1;
		f = p[i][j].x;
		g = p[i][j].y;
		i = f;
		j = g;
	}

	i = t.x;j = t.y;
	cout << i << ',' << j << ")\n";
	cell lca;
	while(i != -1 && j != -1){
		// cout << "(" << i << ',' << j << ")\n";
		
		if(res[i][j]){
			lca.x = i;
			lca.y = j;
			break;
		}
		res[i][j] = 1;
		f = p[i][j].x;
		g = p[i][j].y;
		i = f;
		j = g;
	}

	for(i = 0;i < m;i++){
		for(j = 0;j < n;j++)
			res[i][j] = 0;
	}

	i = s.x;j = s.y;

	res[lca.x][lca.y] = 1;
	// cout << lca.x << ' ' << lca.y << '\n';

	// cout << i << ',' << j << '\n';

	while(i != lca.x || j != lca.y){
		res[i][j] = 1;
		f = p[i][j].x;
		g = p[i][j].y;
		i = f;
		j = g;

	}

	i = t.x;j = t.y;

	while(i != lca.x || j != lca.y){
		res[i][j] = 1;
		f = p[i][j].x;
		g = p[i][j].y;
		i = f;
		j = g;
		
	}

	printpath(p,h,v,m,n,res,s,t);
}



int main(){
	
	srand((unsigned int)time(NULL));	

	int m,n,i,j;
	cout << "m = ";cin >> m;
	cout << "n = ";cin >> n;

	int **h,**v;
	h = (int **)malloc((m - 1) * sizeof(int *));
	v = (int **)malloc(m * sizeof(int *));

	for(i = 0;i < m;i++){
		v[i] = (int *)malloc((n - 1) * sizeof(int));
		if(i != m - 1)
			h[i] = (int *)malloc(n * sizeof(int));
	}
	for(i = 0;i < m - 1;i++)
		for(j = 0;j < n;j++)
			h[i][j] = 1;

	for(i = 0;i < m;i++)
		for(j = 0;j < n - 1;j++)
			v[i][j] = 1;
	
	cell **p = initmaze(h,v,m,n);
	cout << "+++ Initial bhulbhulaiya\n";
	prnmaze(p,h,v,m,n);
	
	bool **vis = (bool **)malloc(m * sizeof(bool *));
	int k,l;
	for(i = 0;i < m;i++){
		vis[i] = (bool *)malloc(n * sizeof(bool));
		for(j = 0;j < n;j++)
			vis[i][j] = 0;
	}

	cell root = genmaze(p,h,v,m,n,vis);

	cout << "+++Random bhulbhulaiya generated\n";

	prnmaze(p,h,v,m,n);

	cell s,t;

	s.x = rand() % m;
	s.y = rand() % n;

	t.x = rand() % m;
	t.y = rand() % n;

	// cout << s.x << ' ' << s.y << '\n';
	// cout << t.x << ' ' << t.y << '\n';

	// for(i = 0;i < m;i++){
	// 	for(j = 0;j < n;j++){
	// 		cout << "(" << p[i][j].x << ',' << p[i][j].y << ") ";
	// 	}
	// 	cout << '\n';
	// }

	findtarget(p,h,v,m,n,s,t,root);

	return 0;
}