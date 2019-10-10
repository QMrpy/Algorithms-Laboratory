typedef struct _node {
   int key;
   struct _node *L;
   struct _node *R;
} BSTnode;

typedef BSTnode *BST;

extern void registerme ( int );
extern BST getsourcetree ( );
extern BST gettargettree ( );
