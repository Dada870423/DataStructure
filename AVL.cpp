#include<iostream>
#include<cstring>
using namespace std;

struct node
{
	int data;
	struct node * parent;
	struct node * Lchild;
	struct node * Rchild; 
	int level;
	int height; 
	int key; // left - right
};

struct node *EMPTY = new struct node;

struct node * head = NULL;
void insert();
void preorder(struct node *);
void inorder(struct node *);
void postorder(struct node *);
void get_level(struct node *, int );
struct node * find(struct node *, int );
int cal_key(struct node * );
void balance(struct node * );
void adjust(struct node * , struct node *, struct node *);

int main(void)
{
	int i, j, k;
	string s_input;
	int i_input;
	EMPTY->level = -100;
	EMPTY->data = -98765;
	cout<<"command 1 : insert with one number \"insert 1\""<<endl;
	cout<<"command 2 : inorder"<<endl;
	cout<<"command 3 : find with one number \"find 1\""<<endl;
	cout<<"command 4 : preorder"<<endl;
	cout<<"command 5 : postorder"<<endl;
	cout<<"command 6 : done"<<endl;
	for(;;)
	{
		cin>>s_input;
		if(s_input == "done") break;
		else if(s_input == "insert") insert();
		else if(s_input == "preorder") preorder(head);
		else if(s_input == "inorder") inorder(head);
		else if(s_input == "postorder") postorder(head);
		else if(s_input == "get_level") get_level(head, 0);
		else if(s_input == "find")
		{
			cin>>i_input;
			struct node *ans = find(head, i_input);
			if(ans->level != -100) cout<<"key: "<<ans->key;
			else cout<<"it's not in the tree!!! ";
		}
		else cout<<"error input";
		if(s_input != "insert") cout<<endl;
	}
	return 0;
}
void adjust(struct node * grand, struct node * par, struct node *child)
{
	int L = 0;
	struct node *OG = head;
	if(grand != head)
	{
		OG = grand->parent;
		if(OG->Lchild == grand) L = 1;
		else L = 2;
	} 
	
	
	if(grand->Lchild == par && par->Lchild == child) //LL
	{
		struct node *two_R = par->Rchild;
		if(L == 1) OG->Lchild = par;
		else if(L == 2) OG->Rchild = par;
		else head = par;
		
		grand->Lchild = par->Rchild;
		par->Rchild = grand;
		//parent
		if(L != 0) par->parent = OG;
		else par->parent = head;
		grand->parent = par;
		child->parent = par;
		
		if(grand->Lchild != NULL) grand->Lchild->parent = grand;
		if(grand->Rchild != NULL) grand->Rchild->parent = grand;
		if(child->Lchild != NULL) child->Lchild->parent = child;
		if(child->Rchild != NULL) child->Rchild->parent = child;
		
		
	}
	else if(grand->Lchild == par && par->Rchild == child) //LR
	{
		
		if(L == 1) OG->Lchild = child;
		else if(L == 2) OG->Rchild = child;
		else head = child;
		
		grand->Lchild = child->Rchild;
		par->Rchild = child->Lchild;
		child->Rchild = grand;
		child->Lchild = par;
		//parent
		if(L != 0) child->parent = OG;
		else par->parent = head;
		grand->parent = child;
		par->parent = child;
		
		if(grand->Lchild != NULL) grand->Lchild->parent = grand;
		if(grand->Rchild != NULL) grand->Rchild->parent = grand;
		if(par->Lchild != NULL) par->Lchild->parent = par;
		if(par->Rchild != NULL) par->Rchild->parent = par;
		
	}
	else if(grand->Rchild == par && par->Lchild == child) //RL
	{
		if(L == 1) OG->Lchild = child;
		else if(L == 2) OG->Rchild = child;
		else head = child;
		
		grand->Rchild = child->Lchild;
		par->Lchild = child->Rchild;
		child->Rchild = par;
		child->Lchild = grand;
		//parent
		if(L != 0) child->parent = OG;
		else par->parent = head;
		grand->parent = child;
		par->parent = child;
		
		if(grand->Lchild != NULL) grand->Lchild->parent = grand;
		if(grand->Rchild != NULL) grand->Rchild->parent = grand;
		if(par->Lchild != NULL) par->Lchild->parent = par;
		if(par->Rchild != NULL) par->Rchild->parent = par;
		
	}
	else if(grand->Rchild == par && par->Rchild == child) //RR
	{
		if(L == 1) OG->Lchild = par;
		else if(L == 2) OG->Rchild = par;
		else head = par;
		
		grand->Rchild = par->Lchild;
		par->Lchild = grand;
		//parent
		if(L != 0) par->parent = OG;
		else par->parent = head;
		grand->parent = par;
		child->parent = par;

		if(grand->Lchild != NULL) grand->Lchild->parent = grand;
		if(grand->Rchild != NULL) grand->Rchild->parent = grand;
		if(child->Lchild != NULL) child->Lchild->parent = child;
		if(child->Rchild != NULL) child->Rchild->parent = child;
	}
	return;
}

void balance(struct node * now)
{
	struct node *par = NULL;
	struct node *grand = NULL;
	if(now->parent != NULL) 
	{
		par = now->parent;
		if(par->parent != NULL)
		{
			grand = par->parent;
		}
		else return;
	}
	else return;
	//have grand
	struct node *child = now;
	for(;grand != head;)
	{
		if(grand->key > 1 || grand->key < -1)
		{
			adjust(grand, par, child);
			return;
		} 
		child = par;
		par = grand;
		grand = grand->parent;
	}
	if(head->key > 1 || head->key < -1) adjust(grand, par, child);
}

struct node * find(struct node *now, int i_input)
{
	if(head == NULL)
	{
		cout<<"it is a empty tree and ";
		return EMPTY;
	}
	for(;;)
	{
		if(now->data == i_input) return now;
		else if(now->Lchild != NULL && now->data > i_input) now = now->Lchild;
		else if(now->Rchild != NULL && now->data <= i_input) now = now->Rchild;
		else return EMPTY;
	}	
}

int cal_key(struct node *now)
{
	int i, j, k;
	int L = 0, R = 0;
	int ans = 0;
	
	if(now->Lchild != NULL) cal_key(now->Lchild);
	if(now->Rchild != NULL) cal_key(now->Rchild);
	
	if(now->Lchild != NULL) L = now->Lchild->height;
	if(now->Rchild != NULL) R = now->Rchild->height;

	now->key = L - R;

	return 0;	
	
}

int get_height(struct node *now)
{
	int i, j, k;
	int L = 0, R = 0;
	
	if(now->Lchild != NULL) L = get_height(now->Lchild);
	if(now->Rchild != NULL) R = get_height(now->Rchild);
	if(L > R)
	{
		now->height = (L+1);
		return (L+1);	
	} 
	now->height = (R+1);
	return (R+1);	
	
}



void get_level(struct node *now, int level)
{
	int i, j, k;

	now->level = level;
	level++;
	if(now->Lchild != NULL) get_level(now->Lchild, level);
	if(now->Rchild != NULL) get_level(now->Rchild, level);
}



void insert()
{
	int i, j, k;
	int i_input;
	cin>>i_input;
	//new a node
	struct node *now = new struct node;
	now->data = i_input;
	now->Lchild = NULL;
	now->Rchild = NULL; 
	now->parent = NULL;
	now->level = 0;//done
	
	if(head == NULL) //empty tree
	{
		head = now;
		now->parent = now;
	}
	else
	{
		struct node *par = head;
		for(;;)
		{
			if(par->Lchild != NULL && par->data > i_input) par = par->Lchild;
			else if(par->Rchild != NULL && par->data <= i_input) par = par->Rchild;
			else break;
		}
		if(par->data > i_input) 
		{
			par->Lchild = now;
			now->parent = par;
		}
		else
		{
			par->Rchild = now;
			now->parent = par;
		}
	}
	get_level(head, 0);
	get_height(head);
	cal_key(head);
	balance(now);
	get_level(head, 0);
	get_height(head);
	cal_key(head);
}

void preorder(struct node *tmp)
{
	if(head == NULL)
	{
		cout<<"it is a empty tree";
		return;
	}
	else
	{
		cout<<tmp->data<<" ";
		if(tmp->Lchild != NULL) preorder(tmp->Lchild);
		if(tmp->Rchild != NULL) preorder(tmp->Rchild);
	}
}
void inorder(struct node *tmp)
{
	if(head == NULL)
	{
		cout<<"it is a empty tree";
		return;
	}
	else
	{
		if(tmp->Lchild != NULL) inorder(tmp->Lchild);
		cout<<tmp->data<<" ";
		if(tmp->Rchild != NULL) inorder(tmp->Rchild);
	}
}
void postorder(struct node *tmp)
{
	if(head == NULL)
	{
		cout<<"it is a empty tree";
		return;
	}
	else
	{
		if(tmp->Lchild != NULL) postorder(tmp->Lchild);
		if(tmp->Rchild != NULL) postorder(tmp->Rchild);
		cout<<tmp->data<<" ";
	}
}



