/*
	Name : Kshitij Agrawal
	Roll.no : 17EC10063	
	Date : 12/03/19
	PC : 28
*/
#include<iostream>
#include<stdlib.h>
#include "BB7.h"
using namespace std;

/*Finds preorder traversal of tree*/
void preorder(BST root){

	if(root == NULL)
		return;
	cout << root -> key << ' ';
	preorder(root -> L);	
	preorder(root -> R);
}

/*Finds inorder traversal of tree*/
/*Not needed in code just for debugging*/
void inorder(BST root){

	if(root == NULL)
		return;
	inorder(root -> L);
	cout << root -> key << ' ';
	inorder(root -> R);
}

BST lrotate(BST v){

	if(v -> R == NULL)
		return v;
	BST u = v -> R;
	BST M = u -> L;

	u -> L = v;
	v -> R = M;

	return u;
}

BST rrotate(BST u){
	
	if(u -> L == NULL)
		return u;
	BST v = u -> L;
	BST M = v -> R;

	v -> R = u;
	u -> L = M;

	return v;
}

/*Creates a copy of the given S and T trees with dummy parent pointers to root*/
BST copy(BST a){
	
	if(a == NULL)return a;
	BST node = (BST)malloc(sizeof(BST));
	node -> key = a -> key;
	node -> L = copy(a -> L);
	node -> R = copy(a -> R);
	return node;
}


void rightskew(BST q,BST *H,int *len){

	int i = 0;
	while(q -> R != NULL){	//Marks end of tree

		if(q -> R -> L == NULL){	//As we passed the tree with the dummy ptr we first move to the org root and then go to left
			q = q -> R;
		}
		else{
			H[i++] = q;				//Found NULL left side, hence leftrotate at q. Also the pointer to parent is q (we are moving to q -> R to ge the actual root)
			(*len)++;
			q -> R = rrotate(q -> R);
		}
	}
	return;
}

void findcorr(BST *H_Target,BST S,BST T,int len,BST *H_Source_Prime){

	int i = 0;
	while(i < len){					//Change the pointers correponding to the ones in the source tree for the pointers stored in the Target  History
		if(S -> key == 	H_Target[i] -> key){
			H_Source_Prime[i] = S;
			i++;
		}
		else{
			S = S -> R;
		}
	}
}

void unskew(BST *H_Source_Prime,int len){	//We stored the pointers for the right skewed tree HENCE left rotate the Right pointers

	for(int i = len - 1;i >= 0;i--){
		H_Source_Prime[i] -> R = lrotate(H_Source_Prime[i] -> R);
	}
	return;
}

int main(int argc, char const *argv[])
{
	int n;
	cout << "n = ";
	cin >> n;

	BST S, T;
	registerme(n);
	S = getsourcetree();
	T = gettargettree();

	cout << "+++Initial Trees\n";
	cout << "\tSource : ";
	preorder(S);
	cout << "\n";
	cout << "\tTarget : ";
	preorder(T);
	cout << "\n";

	int inf = -1e6;

	BST src,dest;

	src = (BST)malloc(sizeof(BSTnode));	//temp source tree with dummy root parent
	dest = (BST)malloc(sizeof(BSTnode)); //temp target tree with dummy root parent

	src -> key = dest -> key = inf;
	src -> L  = src -> R = NULL;
	dest -> L  = dest -> R = NULL;

	src -> R = copy(S);
	dest -> R = copy(T);

	BST *H_Source = (BST *)malloc((n + 1)*sizeof(BST));
	BST *H_Target = (BST *)malloc((n + 1)*sizeof(BST));

	cout << "+++ Right-skewing the trees\n";
	
	int len = 0;
	cout << "\tSource : ";
	rightskew(src,H_Source,&len);
	preorder(src -> R);
	cout << "\n";
	cout << "\t\tNumber of rotations = " << len << '\n';

	len = 0;	
	rightskew(dest,H_Target,&len);
	cout << "\tTarget : ";		
	preorder(dest -> R);
	cout << "\n";
	cout << "\t\tNumber of rotations = " << len << '\n';

	BST *H_Source_Prime = (BST *)malloc((len)*sizeof(BST)); //Stores the final pointers of S correponding to the key values in H_Target

	findcorr(H_Target,src,dest,len,H_Source_Prime);

	unskew(H_Source_Prime,len);

	cout << "+++ Finding node correspondence\n\n+++ Reversing the skewing process\n";

	cout << "\tSource : ";
	preorder(src -> R);
	cout << '\n';

	cout << "\tTarget : ";
	preorder(T);
	cout << '\n';


	free(H_Target);
	free(H_Source);
	free(H_Source_Prime);
	free(src);
	free(dest);
	free(T);
	free(S);
	
	return 0;
}
