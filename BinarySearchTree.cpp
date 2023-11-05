//remove functionality not working
//fix it


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
	void print_preorder();
	void preorder(node *);
	void print_postorder();
	void postorder(node *);
	void insert(int);
	void remove(int);
};

//smaller elements go left
//bigger elements go right

void BinarySearchTree::insert(int d)
{
	
	node * t = new node;
	node * parent;
	t -> data = d;
	t -> right = NULL;
	t -> left = NULL;
	parent = NULL;
	
	//if its a new tree root is the new node
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
			else curr = curr -> left;
		}
		//when it reaches to the bottom of the tree 
		//it checks if the new node should go to its parents right or left
		if(t -> data < parent -> data) parent -> left = t;
		else parent -> right = t;
	}
	
}

void BinarySearchTree::remove(int d)
{
	//locate the element
	bool found = false;
	
	if(isEmpty())
	{	
		cout << "Tree is empty! "<<endl;
		return; 
	}
	
	node *curr;
	node *parent;
	curr = root;
	
	while(curr)
	{
		if(curr -> data == d)
		{
			found = true;
			break;
		}		
		else
		{
			parent = curr;
			if(d> curr -> data) curr = curr -> right;
			else curr = curr -> left;
		}	
		
	}
	
	if(!found)
	{
		cout<<"Data not found!"<<endl;
		return;
	}	
	
	
	//if data found there are 3 cases to remove
	//0 - wer are removing the root 
	//1 - we are removing a leaf
	//2 - we are removing a node with 1 child
	//3- we are removing a node with 2 child
	
	
	//node with single child
	if((curr -> left == NULL) && (curr -> right != NULL) 
	||(curr ->left != NULL) && (curr -> right == NULL))
	{
		
		// only right child
		if(curr -> left == NULL && curr -> right != NULL )
		{	
			if(curr = root)
			{
				root = curr -> right;
				delete curr;	
			}
			
			else if(parent -> left == curr)
			{
				
				parent -> left = curr -> right;
				delete curr;
			}
			else
			{
				
				parent -> right = curr -> right;
				delete curr;
			}
			return;
		}	
		
		
		// only left child
		else
		{
			if(curr = root)
			{
				root = curr -> left;
				delete curr;
			}
			
			else if(parent -> left == curr)
			{
				
				parent -> left = curr -> left;
				delete curr;
			}
			else
			{
				
				parent -> right = curr -> left;
				delete curr;
			}
			return;
		
		}	
	}
	
	//leaf node 
	if(curr -> left == NULL && curr -> right == NULL)
	{	
		if(curr = root)
		{
			delete curr;
			root = NULL;
		}
		else if(parent -> left == curr) parent -> left = NULL;
		else parent -> right = NULL;
		delete curr;
		return;
	}
	
	//node with 2 children
	//replace node with smallest value in right subtree
	if(curr -> left != NULL && curr -> right != NULL)
	{
		node * successor = curr -> right;
		node * successorParent = curr;
		if(successor -> left)
		{
			while(successor -> left)
			{
				successorParent = successor;
				successor = successor -> left;
			}	
		}
		
		curr -> data = successor -> data;
		
		if(successor -> right)
		{
			successorParent -> left = successor -> right;
		}
		//if the successorparent is root delete right node 
		//this contition is for the smaller scale trees
		if(successorParent == curr)
		{
			successorParent -> right = NULL;
		}
		else
		{
			successorParent -> left = successor -> right;
		}
		delete successor;
				
		return;
	}
return;	
}
	
	
void BinarySearchTree::print_inorder()
{
	inorder(root);
}

//left value right order
void BinarySearchTree::inorder(node* p)
{
	if(p != NULL)
	{	
		//recursion
		if(p-> left) inorder(p -> left);
		cout << " "<< p ->data<< " ";
		if(p -> right) inorder(p -> right);
	}
	else return;	
}

void BinarySearchTree::print_preorder()
{
	preorder(root);
}

//value left right order
void BinarySearchTree::preorder(node* p)
{
	if(p != NULL)
	{	
		//recursion
		cout << " "<< p ->data<< " ";
		if(p-> left) preorder(p -> left);
		if(p -> right) preorder(p -> right);
	}
	else return;	
}

void BinarySearchTree::print_postorder()
{
	postorder(root);
}

//left right value order
void BinarySearchTree::postorder(node* p)
{
	if(p != NULL)
	{	
		//recursion
		if(p-> left) postorder(p -> left);
		if(p -> right) postorder(p -> right);
		cout << " "<< p ->data<< " ";
	}
	else return;	
}

int main()
{
	BinarySearchTree b;
    int ch,tmp,tmp1;
    while(1)
    {
       cout<<endl<<endl;
       cout<<" Binary Search Tree Operations "<<endl;
       cout<<" ----------------------------- "<<endl;
       cout<<" 1. Insertion/Creation "<<endl;
       cout<<" 2. In-Order Traversal "<<endl;
       cout<<" 3. Pre-Order Traversal "<<endl;
       cout<<" 4. Post-Order Traversal "<<endl;
       cout<<" 5. Removal "<<endl;
       cout<<" 6. Exit "<<endl;
       cout<<" Enter your choice : ";
       cin>>ch;
       switch(ch)
       {
           case 1 : cout<<" Enter Number to be inserted : ";
                    cin>>tmp;
                    b.insert(tmp);
                    break;
           case 2 : cout<<endl;
                    cout<<" In-Order Traversal "<<endl;
                    cout<<" -------------------"<<endl;
                    b.print_inorder();
                    break;
           case 3 : cout<<endl;
                    cout<<" Pre-Order Traversal "<<endl;
                    cout<<" -------------------"<<endl;
                    b.print_preorder();
                    break;
           case 4 : cout<<endl;
                    cout<<" Post-Order Traversal "<<endl;
                    cout<<" --------------------"<<endl;
                    b.print_postorder();
                    break;
           case 5 : cout<<" Enter data to be deleted : ";
                    cin>>tmp1;
                    b.remove(tmp1);
                    break;
           case 6 : system("pause");
                    return 0;
                    break;
       }
    }
}
