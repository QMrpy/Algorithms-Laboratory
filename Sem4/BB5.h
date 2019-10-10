typedef struct _stacknode {
   int key;
   struct _stacknode *next;
} stacknode;

typedef stacknode *STACK;

typedef struct _treenode {
   int key;
   struct _treenode *L;
   struct _treenode *R;
   struct _treenode *N;
} treenode;

typedef treenode *TREE;

extern void registerme ();

extern STACK SINIT ();
extern int ISEMPTY ( STACK );
extern int TOP ( STACK );
extern STACK PUSH ( STACK, int );
extern STACK POP ( STACK );
extern void SPRNT2B ( STACK );
extern void SPRNB2T ( STACK );

extern TREE TGEN ( int );
extern void TPRN ( TREE );
