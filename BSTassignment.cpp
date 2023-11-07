#include <iostream>

using namespace std;

class node
{
	
	public:
		node * left;
		node * right;
		int data;
};

class BinarySearchTree
{
	
	private:
		node * leaf;
		node *root;
		
	public:
		BinarySearchTree()
		{
			root = NULL;
		}
	bool isEmpty() const {return root == NULL;}
	void print_inorder();
	void inorder(node *);
	void insert(char);
	void insertString(char []);
};

//smaller elements go left
//bigger elements go right
void BinarySearchTree::insert(char d)
{
	
	node * t = new node;
	node * parent;
	t -> data = d;
	t -> right = NULL;
	t -> left = NULL;
	parent = NULL;
	
	//if it is a new tree 
	//new node will be the root
	if(isEmpty()) root = t; 
	else
	{
		
		//curr pointer to keep track of the nodes
		
		node * curr;
		curr = root;
		
		while(curr)
		{
			parent = curr;
			if(t -> data > curr -> data) curr = curr -> right;	
			else if (t -> data < curr -> data)curr = curr -> left;
			//if the new node is the same as its parent it doesnt add that node to the tree
			else return;
		}
		//when it reaches to the bottom of the tree 
		//it checks if the new node should go to its parents right or left
		
			if(t -> data < parent -> data) parent -> left = t;
			else parent -> right = t;	
		
	}
	
}	
	
void BinarySearchTree::print_inorder()
{	
	if(isEmpty())
	{	
		cout << "Tree is empty! "<<endl;
		return; 
	}
	else inorder(root);
}

//left - value - right order
void BinarySearchTree::inorder(node* p)
{
	if(p != NULL)
	{	
		//recursion
		if(p-> left) inorder(p -> left);
		cout << " "<< char(p ->data)<< " ";
		if(p -> right) inorder(p -> right);
	}
	else return;	
}


void BinarySearchTree::insertString(char text[])
{
	int i = 0;
	while(text[i])
	{
		if(text[i] != ' ')
		{
			insert(text[i]);		
		}	
		i++;
	}
	print_inorder();
}



int main()
{
	BinarySearchTree b;
    char text[100];
    
	cout<< "Enter a text"<<endl;
    cin.get(text, sizeof(text));
    b.insertString(text);
    
 	return 0;   
}
