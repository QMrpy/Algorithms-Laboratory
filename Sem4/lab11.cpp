/*
*	Name : Kshitij Agrawal
*	Roll.no : 17EC10063	
*	Date : 09/04/19
*	PC : 28 
*	Minimum Spanning Tree
*/

#include<iostream>
#include<stdlib.h>
using namespace std;
#define debug cout << "Caught you !!!\n";
#define edge_lim 101

typedef struct {
	int x,y;
}pp;

typedef struct {
	pp src;
	pp dest;
	int wt;
}graph;

typedef struct c{
	pp **p;
	int **h;
	int **v;
	graph *edge;
	int total_edges;
	int **size;
	int **mark;
}cell;

cell initbhul(int m,int n){

	cell B;

	B.p = (pp **)malloc(m * sizeof(pp *));
	B.size = (int **)malloc(m * sizeof(int *));
	B.mark = (int **)malloc(m * sizeof(int *));
	int i,j;
	for(i = 0;i < m;i++){
		B.p[i] = (pp *)malloc(n * sizeof(pp));
		B.size[i] = (int *)malloc(n * sizeof(int));
		B.mark[i] = (int *)malloc(n * sizeof(int));
	}

	for(i = 0;i < m;i++){
		for(j = 0;j < n;j++){
			B.p[i][j].x = i;
			B.p[i][j].y = j;
			B.size[i][j] = 1;
			B.mark[i][j] = 0;
		}
		// cout << '\n';
	}
	B.h = (int **)malloc((m - 1) * sizeof(int *));
	B.v = (int **)malloc(m * sizeof(int *));

	for(i = 0;i < m;i++){
		B.v[i] = (int *)malloc((n - 1) * sizeof(int));
		if(i != m - 1)
			B.h[i] = (int *)malloc(n * sizeof(int));
	}
	for(i = 0;i < m - 1;i++)
		for(j = 0;j < n;j++)
			B.h[i][j] = 1;

	for(i = 0;i < m;i++)
		for(j = 0;j < n - 1;j++)
			B.v[i][j] = 1;

	B.edge = (graph *)malloc(4*m*n*sizeof(graph));

	pp s,d;

	int k = 0;

	for(i = 0;i < m;i++){
		for(j = 0;j < n;j++){
			s = (pp){i,j};
			if(i + 1 < m){
				d = (pp){i + 1,j};
				int w = rand() % edge_lim;
				B.edge[k].src = s;
				B.edge[k].dest = d;
				B.edge[k].wt = w;
				k++;
			}
			if(j + 1 < n){
				d = (pp){i,j + 1};
				int w = rand() % edge_lim;
				B.edge[k].src = s;
				B.edge[k].dest = d;
				B.edge[k].wt = w;
				k++;
			}
		}
	}
	B.total_edges = k;
	return B;
}

void swap(graph *a, graph *b){
	graph t = *a;
	*a = *b;
	*b = t;
}

int partition(graph *G,int l,int h){

	graph pivot = G[h];
	int i = l - 1,j;
	for(j = l;j < h;j++){
		if(G[j].wt <= pivot.wt){
			i++;
			swap(&G[i],&G[j]);
		}
	}
	swap(&G[i + 1],&G[h]);
	return i + 1;
}

void sort(graph *G,int l,int h){

	if(l < h){
		int pi = partition(G,l,h);

		sort(G,l,pi - 1);
		sort(G,pi + 1,h);
	}
}

cell get_parent(pp key,cell B){

	if(B.p[key.x][key.y].x == key.x && B.p[key.x][key.y].y == key.y)
		return B;
	int r,s;
	r = B.p[key.x][key.y].x;
	s = B.p[key.x][key.y].y;
	cell C = get_parent(B.p[key.x][key.y],B);
	pp z = C.p[r][s];

	B.p[key.x][key.y] = z;

	return B;
}

cell mergesets(pp root_1,pp root_2,cell B){

	int x,y,u,v;
	x = root_1.x;y = root_1.y;
	u = root_2.x;v = root_2.y;

	if(B.size[x][y] > B.size[u][v]){
		B.p[u][v].x = x;
		B.p[u][v].y = y;
		B.size[x][y] += B.size[u][v];
	}
	else{
		B.p[x][y].x = u;
		B.p[x][y].y = v;
		B.size[u][v] += B.size[x][y];
	}
	return B;
}

bool is_same(pp a,pp b){
	return (a.x == b.x && a.y == b.y);
}

void MSTbhul(cell B,int m,int n){

	sort(B.edge,0,B.total_edges - 1);
	int i,j,k;
	// cout << "Edges sorted\t" << B.total_edges << '\n';
	// for(i = 0;i < B.total_edges;i++){
	// 	cout << "(" << B.edge[i].src.x << ' ' << B.edge[i].src.y << ") --> (" \
	// 		<< B.edge[i].dest.x << ' ' << B.edge[i].dest.y << ") --> " << B.edge[i].wt << '\n';
	// }	
	int reqd = m * n - 1;
	int curr = 0;
	for(i = 0;i < B.total_edges;i++){
		int r,s,u,v;
		r = B.edge[i].src.x;
		s = B.edge[i].src.y;

		// debug
		u = B.edge[i].dest.x;
		v = B.edge[i].dest.y;
		// debug
		B = get_parent(B.edge[i].src,B);
		B = get_parent(B.edge[i].dest,B);
		pp root_1 = B.p[r][s];
		pp root_2 = B.p[u][v];
		if(!is_same(root_1,root_2)){
			curr++;
			B = mergesets(root_1,root_2,B);
			// cout << "(" << r << ',' << s << ")\t";
			// cout << "(" << u << ',' << v << ")\n";
			// cout << i << '\n';
			if(u - r == 1){
				B.h[r][s] = 0;
			}	
			else if(r - u == 1){
				B.h[u][v] = 0;
			}	
			else if(s - v == 1){
				B.v[u][v] = 0;
			}	
			else{
				B.v[r][s] = 0;
			}
		}
		// root_1 = B.p[r][s];
		// root_2 = B.p[u][v];
		// cout << root_1.x << ',' << root_1.y << '\t';
		// cout << root_2.x << ',' << root_2.y << '\n';
		if(curr == reqd)break;
	}
}

// cell reverse_dfs(cell &B,pp s,pp t,int dx[],int dy[], bool **vis,int m,int n){
// 	int x,y;
// 	x = s.x;y = s.y;
// 	vis[x][y] = 1;

// 	if(s.x == t.x && s.y == t.y){
// 		return B;
// 	}

// 	int i,j,k,l;

// 	for(i = 0;i < 4;i++){
// 		int u,v;
// 		u = x + dx[i];
// 		v = y + dy[i];
// 		if(u >= 0 && u < m && v >= 0 && v < n){
// 			if(vis[u][v] == 0){

// 				if(u - x == 1 && !B.h[x][y]){
// 					// cout << u << ',' << v << '\n';
// 					B.mark[u][v] += 1;
// 					return reverse_dfs(B,(pp){u,v},t,dx,dy,vis,m,n);
// 				}
// 				else if(x - u == 1 && !B.h[u][v]){
// 					// cout << u << ',' << v << '\n';
// 					B.mark[u][v] += 1;
// 					return reverse_dfs(B,(pp){u,v},t,dx,dy,vis,m,n);
// 					// cout << f << '\n';
// 				}
// 				else if(v - y == 1 && !B.v[x][y]){
// 					// cout << u << ',' << v << '\n';
// 					B.mark[u][v] += 1;
// 					return reverse_dfs(B,(pp){u,v},t,dx,dy,vis,m,n);
// 					// cout << f << '\n';

// 				}
// 				else if(!B.v[u][v]){
// 					// cout << u << ',' << v << '\n';
// 					B.mark[u][v] += 1;
// 					return reverse_dfs(B,(pp){u,v},t,dx,dy,vis,m,n);
// 					// cout << f << '\n';
// 				}
// 			}
// 		}
// 	}

// }

void dfs(cell *B,pp s,pp t,int dx[],int dy[], bool **vis,int m,int n){

	int x,y;
	x = s.x;y = s.y;
	vis[x][y] = 1;
	// cout << x << ' ' << y << '\n';
	if(s.x == t.x && s.y == t.y){
		return;
	}

	int i,j,k,l;

	for(i = 0;i < 4;i++){
		int u,v;
		u = x + dx[i];
		v = y + dy[i];
		if(u >= 0 && u < m && v >= 0 && v < n){
			if(vis[u][v] == 0){
				vis[u][v] = 1;
				if(dx[i] == 1 && !(*B).h[x][y]){
					cout << u << ',' << v << '\n';
					(*B).mark[u][v] += 1;
					dfs(B,(pp){u,v},t,dx,dy,vis,m,n);
				}
				else if(dx[i] == -1 && !(*B).h[u][v]){
					cout << u << ',' << v << '\n';
					(*B).mark[u][v] += 1;
					dfs(B,(pp){u,v},t,dx,dy,vis,m,n);
					// cout << f << '\n';

				}
				else if(dy[i] == 1 && !(*B).v[x][y]){
					cout << u << ',' << v << '\n';
					(*B).mark[u][v] += 1;
					dfs(B,(pp){u,v},t,dx,dy,vis,m,n);
					// cout << f << '\n';

				}
				else if(!(*B).v[u][v]){
					cout << u << ',' << v << '\n';
					(*B).mark[u][v] += 1;
					dfs(B,(pp){u,v},t,dx,dy,vis,m,n);
					// cout << f << '\n';
				}
			}
		}
	}
	return;
}
void prnbhul(cell B,int m,int n);
cell findrani(cell B,int m,int n,pp s,pp t){

	int dx[] = {1,-1,0,0};
	int dy[] = {0,0,1,-1};
	bool **vis = (bool **)malloc(m * sizeof(bool *));
	int i,j;
	for(i = 0;i < m;i++){
		vis[i] = (bool *)malloc(n * sizeof(bool));
		for(j = 0;j < n;j++)
			vis[i][j] = 0;
	}
	dfs(&B,s,t,dx,dy,vis,m,n);
	for(i = 0;i < m;i++){
		for(j = 0;j < n;j++){
			cout << B.mark[i][j] << ' ';
		}
		cout << '\n';
	}
	for(int i = 0;i < m;i++)
		for(int j = 0;j < n;j++)
			vis[i][j] = 0;
	prnbhul(B,m,n);
	dfs(&B,t,s,dx,dy,vis,m,n);
	for(i = 0;i < m;i++){
		for(j = 0;j < n;j++){
			cout << B.mark[i][j] << ' ';
		}
		cout << '\n';
	}
	return B;
}

void prnbhul(cell B,int m,int n){

	int i,j;
	for(i = 0; i < n;i++){
		cout << "+---";
	}
	cout << "+\n";

	for(i = 0;i < m; i++){
		cout << "|";
		for(j = 0;j < n;j++){
			if(B.mark[i][j] != 2)
				cout << "   ";
			else
				cout << " X ";
			if(j < n - 1){
				if(B.v[i][j])cout << "|";
				else cout << " ";
			}
			if(j == n - 1)
				cout << "|\n";
		}
		for(j = 0;j < n;j++){
			if(i < m - 1){
				if(B.h[i][j])cout << "+---";
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

	// for(i = 0;i < B.total_edges;i++){
	// 	cout << "(" << B.edge[i].src.x << ' ' << B.edge[i].src.y << ") --> (" \
	// 		<< B.edge[i].dest.x << ' ' << B.edge[i].dest.y << ") --> " << B.edge[i].wt << '\n';
	// }

}

int main(){
	
	srand((unsigned int)time(NULL));	

	int m,n,i,j;
	cout << "m = ";cin >> m;
	cout << "n = ";cin >> n;

	cell p = initbhul(m,n);

	cout << "+++ Initial bhulbhulaiya\n";
	prnbhul(p,m,n);

	MSTbhul(p,m,n);

	cout << "+++ Random bhulbhulaiya generated\n";
	prnbhul(p,m,n);

	pp s,t;

	s.x = rand() % m;
	s.y = rand() % n;

	t.x = rand() % m;
	t.y = rand() % n;
	cout << "+++ Path from S = (" << s.x << ',' << s.y; \
	cout << ") to T = (" << t.x << ',' << t.y << ")\n";

	// p.mark[s.x][s.y] = p.mark[t.x][t.y] = 2;

	p = findrani(p,m,n,s,t);
	// p.mark[s.x][s.y] = p.mark[t.x][t.y] = 2;

	prnbhul(p,m,n);
	return 0;
}