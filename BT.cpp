#include<iostream>
#include<cstring>
using namespace std;

void ini_cout();
void insert();
void preorder(int );
void inorder(int );
void postorder(int );
int find();
void del(int );
int left(int );
int right(int );

int tree[10000];
bool exist[10000];

int main(void)
{
	int i, j, k;
	string s_input;
	ini_cout();
	
	for(;;)
	{
		cin>>s_input;
		if(s_input == "insert") insert();
		else if(s_input == "done") break;
		else if(s_input == "find") cout<<"found at "<<find()<<endl;
		else if(s_input == "delete") del(find());
		else if(s_input == "preorder") preorder(1);
		else if(s_input == "inorder") inorder(1);
		else if(s_input == "postorder") postorder(1);
		else cout<<"invalid input";

		if(s_input != "insert" && s_input != "delete" && s_input != "find") cout<<endl;
	}
	return 0;
}
void ini_cout()
{
	int i;
	for(i=0;i<10000;i++) exist[i] = false;
	cout<<"command 1 : insert with one number \"insert 1\""<<endl;
	cout<<"command 2 : inorder"<<endl;
	cout<<"command 3 : find with one number \"find 1\""<<endl;
	cout<<"command 4 : preorder"<<endl;
	cout<<"command 5 : postorder"<<endl;
	cout<<"command 6 : delete with one number \"delete 1\""<<endl;
	cout<<"command 7 : done"<<endl;
}

void del(int x)
{
	int victem;
	if(x != -1) cout<<"found at : "<<x<<endl;
	if(x == -1) return;
	for(victem=x;;)
	{
		if(exist[right(victem)] == true)
		{
			for(victem = right(victem);exist[left(victem)];victem = left(victem)) ;
			tree[x] = tree[victem];
			x = victem;
		}
		else if(exist[left(victem)] == true)
		{
			for(victem = left(victem);exist[right(victem)];victem = right(victem)) ;
			tree[x] = tree[victem];
			x = victem;
		}
		else if(exist[left(victem)] == false && exist[right(victem)] == false) break;
	}
	tree[x] = tree[victem];
	exist[victem] = false;
}
int find()
{
	int i_input, now;
	cin>>i_input;
	for(now=1;;)
	{
		if(exist[now] == false) cout<<"not found !!!  "<<endl;
		if(exist[now] == false) return -1;
		else if(tree[now] == i_input) return now;
		else if(i_input > tree[now]) now = right(now);
		else if(i_input <= tree[now]) now = left(now);
	}
}


void insert()
{
	int i_input;
	int now;
	cin>>i_input;
	if(exist[1] == false) 
	{
		tree[1] = i_input;
		exist[1] = true;
		return;
	}
	else
	{
		for(now = 1;;)
		{
			if(i_input > tree[now] && exist[right(now)] == true) now = right(now);
			else if(i_input <= tree[now] && exist[left(now)] == true) now = left(now);
			
			if(i_input > tree[now] && exist[right(now)] == false)
			{
				tree[right(now)] = i_input;
				exist[right(now)] = true;
				return;
			}
			else if(i_input <= tree[now] && exist[left(now)] == false)
			{
				tree[left(now)] = i_input;
				exist[left(now)] = true;
				return;
			}
		}
	}
}

void preorder(int now)
{
	if(exist[1] == false) cout<<"it is an empty tree";
	else if(exist[now] == false) return;
	else
	{
		cout<<tree[now]<<" ";
		if(exist[left(now)] == true) preorder(left(now));
		if(exist[right(now)] == true) preorder(right(now));
	}
}
void inorder(int now)
{
	if(exist[1] == false) cout<<"it is an empty tree";
	else if(exist[now] == false) return;
	else
	{
		if(exist[left(now)] == true) inorder(left(now));
		cout<<tree[now]<<" ";
		if(exist[right(now)] == true) inorder(right(now));
	}
}
void postorder(int now)
{
	if(exist[1] == false) cout<<"it is an empty tree";
	else if(exist[now] == false) return;
	else
	{
		if(exist[left(now)] == true) postorder(left(now));
		if(exist[right(now)] == true) postorder(right(now));
		cout<<tree[now]<<" ";
	}
}


int left(int input)
{
	return (input * 2);
}
int right(int input)
{
	return (input * 2 + 1);
}




