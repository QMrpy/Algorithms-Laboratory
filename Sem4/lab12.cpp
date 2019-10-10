/*
*	Name : Kshitij Agrawal
*	Roll.no : 17EC10063	
*	Date : 16/04/19
*	PC : 28 
*	Graph Algorithms
*/

#include<iostream>
#include<stdlib.h>
#include<bits/stdc++.h>
using namespace std;
#define debug cout << "Caught you !!!\n";

typedef struct {
	int a,b,c;
}glass;

typedef struct {
	int id;
	glass g;
	glass list[6];
	int len;
}Graph;

typedef struct {
	int i;
	int a[6];
	int len;
}mapping;

int max(int a,int b){
	return (a > b ? a : b);
}

int min(int a,int b){
	return (a < b ? a : b);
}

void print_nodes(glass x){
	cout << "(" << x.a << ' ' << x.b << ' ' << x.c << ") ";
}

bool check(glass a,glass b){
	if(a.a == b.a && a.b == b.b && a.c == b.c)return 0;
	return 1;
}

void gen_graph(mapping m[],Graph G[],glass c,glass g,glass d,int *id,bool vis[101][101][101],int *f){

	// G[*id] = (Graph *)malloc(sizeof(Graph));

	vis[g.a][g.b][g.c] = 1;
	G[*id].id = *id;
	G[*id].g = g;
	glass curr;
	int tx;
	int t = *id;
	int i = 0;
	int r = *id;
	m[t].i = t;
	for(int j = 0;j < 3;j++){

		if(j == 0){
			tx = min(c.b - g.b,g.a);
			// tx = tx - g.b;
			curr.a = g.a - tx;
			curr.b = g.b + tx;
			curr.c = g.c;
			// (*id)++;
			// print_nodes(g);
			// cout << "-->";
			// print_nodes(curr);
			// cout << "\n";
			if(check(curr,d) == 0){
				*f = *id;
			}
			if(check(g,curr)){
				if(vis[curr.a][curr.b][curr.c])
					m[t].a[i] = *id - 1;
				else{
					r++;
					m[t].a[i] = r;
					// r++;
				}
				G[t].list[i] = curr;
				i++;
			}
			if(vis[curr.a][curr.b][curr.c] == 0 && check(g,curr)){
				(*id)++;
				print_nodes(curr);
				gen_graph(m,G,c,curr,d,id,vis,f);
			}

			tx = min(c.c - g.c,g.a);
			// tx = tx - g.c;
			curr.a = g.a - tx;
			curr.b = g.b;
			curr.c = g.c + tx;
			// (*id)++;
			// print_nodes(g);
			// cout << "-->";
			// print_nodes(curr);
			if(check(curr,d) == 0){
				*f = *id;
			}
			// cout << "\n";
			if(check(g,curr)){
				if(vis[curr.a][curr.b][curr.c])
					m[t].a[i] = *id - 1;
				else{
					r++;
					m[t].a[i] = r;
					// r++;
				}
				G[t].list[i] = curr;
				i++;
			}
			if(vis[curr.a][curr.b][curr.c] == 0 && check(g,curr)){
				(*id)++;
				print_nodes(curr);
				gen_graph(m,G,c,curr,d,id,vis,f);
			}

		}
		else if(j == 1){
			tx = min(c.a - g.a, g.b);
			// tx = tx - g.a;
			curr.a = g.a + tx;
			curr.b = g.b - tx;
			curr.c = g.c;
			// (*id)++;
			// print_nodes(g);
			// cout << "-->";
			// print_nodes(curr);
			// cout << "\n";
			if(check(curr,d) == 0){
				*f = *id;
			}
			if(check(g,curr)){
				if(vis[curr.a][curr.b][curr.c])
					m[t].a[i] = *id - 1;
				else
					m[t].a[i] = *id;
				G[t].list[i] = curr;
				i++;
			}
			if(vis[curr.a][curr.b][curr.c] == 0 && check(g,curr)){
				(*id)++;
				print_nodes(curr);
				gen_graph(m,G,c,curr,d,id,vis,f);
			}

			tx = min(c.c - g.c,g.b);
			// tx = tx - g.c;
			curr.a = g.a;
			curr.b = g.b - tx;
			curr.c = g.c + tx;
			// (*id)++;
			// print_nodes(g);
			// cout << "-->";
			// print_nodes(curr);
			if(check(curr,d) == 0){
				*f = *id;
			}
			// cout << "\n";
			if(check(g,curr)){
				if(vis[curr.a][curr.b][curr.c])
					m[t].a[i] = *id - 1;
				else
					m[t].a[i] = *id;
				G[t].list[i] = curr;
				i++;
			}
			if(vis[curr.a][curr.b][curr.c] == 0 && check(g,curr)){
				(*id)++;
				print_nodes(curr);
				gen_graph(m,G,c,curr,d,id,vis,f);
			}

		}
		else{
			tx = min(c.b - g.b,g.c);
			// tx = tx - g.b;
			curr.a = g.a;
			curr.b = g.b + tx;
			curr.c = g.c - tx;
			// (*id)++;
			// print_nodes(g);
			// cout << "-->";
			// print_nodes(curr);
			// cout << "\n";
			if(check(curr,d) == 0){
				*f = *id;
			}
			if(check(g,curr)){
				if(vis[curr.a][curr.b][curr.c])
					m[t].a[i] = *id - 1;
				else
					m[t].a[i] = *id;
				G[t].list[i] = curr;
				i++;
			}
			if(vis[curr.a][curr.b][curr.c] == 0 && check(g,curr)){
				(*id)++;
				print_nodes(curr);
				gen_graph(m,G,c,curr,d,id,vis,f);
			}

			tx = min(c.a - g.a,g.c);
			// tx = tx - g.c;
			curr.a = g.a + tx;
			curr.b = g.b;
			curr.c = g.c - tx;
			// print_nodes(g);
			// cout << "-->";
			// print_nodes(curr);
			// cout << "\n";
			if(check(curr,d) == 0){
				*f = *id;
			}
			if(check(g,curr)){
				if(vis[curr.a][curr.b][curr.c])
					m[t].a[i] = *id - 1;
				else
					m[t].a[i] = *id;
				G[t].list[i] = curr;
				i++;
			}
			if(vis[curr.a][curr.b][curr.c] == 0 && check(g,curr)){
				(*id)++;
				print_nodes(curr);
				gen_graph(m,G,c,curr,d,id,vis,f);
			}
		}

	}
	G[t].len = i;
	m[t].len = i;
	return;
}

bool bfs(mapping m[],int s,int d,int n,	int parent[]){

	queue<int> q;
	int vis[n] = {0};
	for(int i = 0;i < n;i++){
		parent[i] = -1;
	}
	vis[s] = 1;
	q.push(s);
	while(!q.empty()){
		int t = q.front();
		q.pop();
		cout << t << " : ";
		for(int i = 0; i < m[t].len;i++){
			if(vis[m[t].a[i]] == 0){
				cout << m[t].a[i] << ' ';
				vis[m[t].a[i]] = 1;
				q.push(m[t].a[i]);
				parent[m[t].a[i]] = t;
				if(m[t].a[i] == d)return 1;
			}
		}
	}
	cout << '\n';
	return 0;
}

void shortest_path(int s,int d,mapping m[],int n,Graph g[]){

	int parent[n];

	glass path[n];
	int i = 0;
	if(bfs(m,s,d,n,parent)){
		while(parent[d] != -1){
			path[i++] = g[parent[d]].g;
			d = parent[d];
		}
		for(int j = i - 1;j >= 0;j--){
			print_nodes(path[j]);
			cout << '\n';
		}
	}
	else{
		cout << "Not possible\n";
	}

}

int main(){
	/*
		Glass capacities : 27 28 20
		Initial contents : 15 13 7
		Final contents : 5 10 20
	*/
	freopen("input.txt","r",stdin);
	glass c,init,final;
	cout << "Glass capacities : ";
	cin >> c.a >> c.b >> c.c;

	cout << "Initial capacities : ";
	cin >> init.a >> init.b >> init.c;

	cout << "Final capacities : ";
	cin >> final.a >> final.b >> final.c;

	int id = 0;


	bool vis[101][101][101];
	for(int i = 0;i <= 100;i++)
		for(int j = 0;j <= 100;j++)
			for(int k = 0;k <= 100;k++)
				vis[i][j][k] = 0;	

	Graph g[10000];
	cout << "+++ The vertices are\n";
	mapping m[10000];
	int f;
	gen_graph(m,g,c,init,final,&id,vis,&f);

	cout << id << '\n';
	cout << "\n\n";
	cout << "+++ Graph generated\n";
	for(int i = 0;i < id;i++){
		cout << "\t";
		cout << g[i].id << ' ';
		print_nodes(g[i].g);
		cout << "-->";
		for(int j = 0;j < g[i].len;j++){
			print_nodes(g[i].list[j]);
		}
		cout << '\n';
	}

	// cout << f << '\n';	

	for(int i = 0;i < id;i++){
		cout << m[i].i << " : ";
		for(int j = 0;j < m[i].len;j++){
			cout << m[i].a[j] << ' ';
		}
		cout << '\n';
	}

	shortest_path(0,f ,m,id,g);

	return 0;
}