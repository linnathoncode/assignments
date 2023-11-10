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
	
	// 3 cases when removing
	// 1 - we are removing a node with 1 child
	// 2 - we are removing a leaf node 
	// 3 we are removeing a node with 2 children
	// root cases can be specified inside of these cases
	
	// node with 1 child
	if((curr -> left == NULL) && (curr -> right != NULL) 
	||(curr ->left != NULL) && (curr -> right == NULL))
	{
		
		// only right child
		if(curr -> left == NULL && curr -> right != NULL )
		{	
			// if the curr node is the root new root will be the right subtree's first node
			if(curr == root)
			{
				root = curr -> right;
				delete curr;	
			}

			// if the curr node is the left node of its parent, parent's new left node will be curr's right node 
			// if there isnt a right node of the curr its gonna be NULL
			else if(parent -> left == curr)
			{
				
				parent -> left = curr -> right;
				delete curr;
			}
			// curr is right node of its parent, new right node will be curr's right node	
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
			// if the curr node is the root new root will be the left subtree's first node
			if(curr == root)
			{
				root = curr -> left;
				delete curr;
			}
				
			// if the curr node is the left node of its parent, parent's new left node will be curr's left node 
			// if there isnt a left node of the curr its gonna be NULL
			else if(parent -> left == curr)
			{
				
				parent -> left = curr -> left;
				delete curr;
			}
			
			// curr is right node of its parent, new right node will be curr's left node	
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
		// if the curr node is the root 
		// delete curr set root to NULL
		if(curr = root)
		{
			delete curr;
			root = NULL;
			return;
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

		//locate the leftmost node of the right subtree
		if(successor -> left)
		{
			while(successor -> left)
			{
				successorParent = successor;
				successor = successor -> left;
			}	
		}
		
		curr -> data = successor -> data;

		// if successor (the node thats gonna replace the curr) has a right node 
		// that right node is gonna be the new left node of the successor node's parent
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
	if(isEmpty())
	{	
		cout << "Tree is empty! "<<endl;
		return; 
	}
	else inorder(root);
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
	if(isEmpty())
	{	
		cout << "Tree is empty! "<<endl;
		return; 
	}
	else preorder(root);
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
	if(isEmpty())
	{	
		cout << "Tree is empty! "<<endl;
		return; 
	}
	else postorder(root);
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
