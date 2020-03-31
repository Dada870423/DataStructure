#include<iostream>
#include<cstring>
#include<string.h>
#include<vector>
using namespace std;

struct node
{
	char Lthread;
	struct node *Lchild;
	int data;
	struct node *Rchild;
	char Rthread;
};

struct node *head = new struct node;
//vector<int> V;
struct node *found = NULL;
void insert();
void show();
void del();
struct node *find(struct node * );
void preorder(struct node *);
void postorder(struct node *);
struct node *Insuc(struct node *);
struct node *Inpre(struct node *);
struct node *find_parent(struct node *);
int main(void)
{
	//announce
	cout<<"command 1 : insert with one number \"insert 1\""<<endl;
	cout<<"command 2 : show"<<endl;
	cout<<"command 3 : find with one number \"find 1\""<<endl;
	cout<<"command 4 : preorder"<<endl;
	cout<<"command 5 : postorder"<<endl;
	cout<<"command 6 : delete with one number \"delete 1\""<<endl;
	cout<<"command 7 : done"<<endl;
	//initial
	head->Lthread = 'T';
	head->Lchild = head;
	head->Rchild = head;
	head->Rthread = 'F';
	//initial done
	int i, j, k;
	//int i_input;
	string s_input;
	while(cin>>s_input)
	{
		if(s_input == "done") break;
		else if(s_input == "insert") insert();
		else if(s_input == "find") find(head);
		else if(s_input == "show") show();
		else if(s_input == "preorder") preorder(head);
		else if(s_input == "postorder") postorder(head);
		else if(s_input == "delete") del();
		else cout<<"wrong input";
		if(s_input != "insert") cout<<endl;
		
	}
	return 0;
}


void insert()
{
	int i, j, k;
	int i_input;
	cin>>i_input;
	//cout<<i_input<<endl;
	struct node *now = new struct node;
	
	//initial
	now->Lthread = 'T';
	now->Lchild = NULL;
	now->data = i_input;
	now->Rchild = NULL;
	now->Rthread = 'T';  //initial done
	
	if(head->Lthread == 'T') //NULL
	{
		//head
		head->Lthread = 'F';
		head->Lchild = now; //head done
		
		//now
		now->Lchild = head;
		now->Rchild = head;  //now done
	}
	else
	{
		struct node *tmp = head->Lchild;
		for(;;)
		{
			if(tmp->data > now->data)
			{
				if(tmp->Lthread == 'F') tmp = tmp->Lchild;
				else
				{
					//step1
					now->Lthread = tmp->Lthread;
					now->Lchild = tmp->Lchild;
					//step2
					now->Rthread = 'T';
					now->Rchild = tmp;
					//step3
					tmp->Lthread = 'F';
					tmp->Lchild = now;  //case 1 done
					//case 2
					if(now->Lthread == 'F')
					{
						struct node *next = Inpre(now);
						next->Rchild = now; 
					}
					return;
				}
			} 
			else  if(tmp->data <= now->data)
			{
				if(tmp->Rthread == 'F') tmp = tmp->Rchild;
				else
				{
					//step1
					now->Rthread = tmp->Rthread;
					now->Rchild = tmp->Rchild;
					//step2
					now->Lthread = 'T';
					now->Lchild = tmp;
					//step3
					tmp->Rthread = 'F';
					tmp->Rchild = now;  //case 1 done
					//case 2
					if(now->Rthread == 'F')
					{
						struct node *next = Insuc(now);
						next->Lchild = now; 
					}
					return;
				}
			} 
		}
		
	}
	

	
}
struct node *Insuc(struct node *x)
{
	struct node *tmp = x->Rchild;
	if(x->Rthread == 'F')
	{
		while(tmp->Lthread != 'T')
		{
			tmp = tmp->Lchild;
		}
	}
	return tmp;
}
struct node *Inpre(struct node *x)
{
	struct node *tmp = x->Lchild;
	if(x->Lthread == 'F')
	{
		while(tmp->Rthread != 'T')
		{
			tmp = tmp->Rchild;
		}
	}
	return tmp;
}

void show()
{
	struct node *tmp = head;
	if(head->Lthread == 'T')
	{
		cout<<"it is a empty tree";
		return;
	}
	for(;;)
	{
		tmp = Insuc(tmp);
		if(tmp != head) cout<<tmp->data<<" ";
		else return;
		
	}
}
void del()
{
	struct node *now = find(head);
	if(now == head) return;
	else
	{
		
		struct node *pre = Inpre(now);
		struct node *next = Insuc(now);
		struct node *parent = find_parent(now);
		struct node *victem = head;
		struct node *victem_parent = head;
		if(1)
		{
			if(now->Lthread == 'T' && now->Rthread == 'T') //leaf
			{
				victem = now;
				victem_parent = parent;
			}
			else if(now->Lthread == 'F' && now->Rthread == 'T') //has left son
			{
				struct node *tmp = now->Lchild;
				for(;;)
				{
					if(tmp->Rthread == 'F') tmp = tmp->Rchild;
					else
					{
						now->data = tmp->data;
						victem = tmp;
						victem_parent = find_parent(victem);
						if(tmp->Lthread != 'T') 
						{
							now = victem;
							tmp = tmp->Lchild;
						}
						else break;
					}
				}
			}
			else if(now->Lthread == 'T' && now->Rthread == 'F') //has right son
			{
				struct node *tmp = now->Rchild;
				for(;;)
				{
					if(tmp->Lthread == 'F') tmp = tmp->Lchild;
					else
					{
						now->data = tmp->data;
						victem = tmp;
						victem_parent = find_parent(victem);
						if(tmp->Rthread != 'T') 
						{
							now = victem;
							tmp = tmp->Rchild;
						}
						else break;
					}
				}
			}
			else if(now->Lthread == 'F' && now->Rthread == 'F')
			{
				struct node *tmp = now->Rchild;
				for(;;)
				{
					if(tmp->Lthread == 'F') tmp = tmp->Lchild;
					else
					{
						now->data = tmp->data;
						victem = tmp;
						victem_parent = find_parent(victem);
						if(tmp->Rthread != 'T') 
						{
							now = victem;
							tmp = tmp->Rchild;
						}
						else break;
					}
				}
			}
			if(victem_parent == head)
			{
				head->Lthread = 'T';
				head->Lchild = head;
				delete victem;
				cout<<"   delete successfully";
				return;
			}
			if(victem_parent->data > victem->data) //victem is the left child of victem_parent
			{
				victem_parent->Lchild = victem->Lchild;
				victem_parent->Lthread = victem->Lthread;
			}
			else //victem is the right of victem_parent
			{
				victem_parent->Rchild = victem->Rchild;
				victem_parent->Rthread = victem->Rthread;
			}
			delete victem;	
			cout<<"   delete successfully";
			return;
		}
	}
}

struct node *find_parent(struct node *now)
{
	struct node *tmp = head;
	for(;;)
	{
		tmp = Insuc(tmp);
		if(tmp->Lchild == now && tmp->Lthread == 'F') return tmp;
		if(tmp->Rchild == now && tmp->Rthread == 'F') return tmp;
		if(tmp == head) return head;
	}
}

struct node *find(struct node *tmp)
{
	//struct node *tmp = head;
	int f_input, index = -1;
	cin>>f_input;
	for(;;)
	{
		index++;
		tmp = Insuc(tmp);
		if(tmp->data == f_input)
		{
			cout<<"found at "<<index;
			return tmp;
		}
		if(tmp == head)
		{
			cout<<"not fount QQ";
			return head; //return head means not found
		}
	}
}
void preorder(struct node *tmp)
{
	if(head->Lthread == 'T')
	{
		cout<<"it is a empty tree";
		return;
	}
	else
	{
		if(tmp != head) cout<<tmp->data<<" ";
		if(tmp->Lthread == 'F') preorder(tmp->Lchild);
		if(tmp->Rthread == 'F') if(tmp->Rchild != head) preorder(tmp->Rchild);
	}
}
void postorder(struct node *tmp)
{
	if(head->Lthread == 'T')
	{
		cout<<"it is a empty tree";
		return;
	}
	else
	{
		
		if(tmp->Lthread == 'F') postorder(tmp->Lchild);
		if(tmp->Rthread == 'F') if(tmp->Rchild != head) postorder(tmp->Rchild);
		if(tmp != head) cout<<tmp->data<<" ";
	}
}











