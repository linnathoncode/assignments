#include <iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))

using namespace std;

struct avl_node
{
	int data;
	struct avl_node * left;
	struct avl_node * right;
}*root;

class avl_tree
{
	public:
		bool isEmpty() const {return root == NULL;}
		int height(avl_node *);
		int diff(avl_node *);
		avl_node * rrRotation(avl_node *);
		avl_node * llRotation(avl_node *);
		avl_node * lrRotation(avl_node *);
		avl_node * rlRotation(avl_node *);
		avl_node * balance(avl_node *);
		avl_node * insert(avl_node *, int);
		void remove(int);
		void display(avl_node *, int);
		void inorder(avl_node*);
		void preorder(avl_node*);
		void postorder(avl_node*);
		
		avl_tree()
		{
			root = NULL;
		}
		
};

// finds the height of the given avl tree
int avl_tree::height(avl_node * temp)
{
	int h = 0;
	
	// uses recursion to find the max height of the avl tree
	if(temp != NULL)
	{
		int l_height = height(temp -> left);
		int r_height = height(temp -> right);
		int max_height = max(l_height, r_height);
		h = max_height + 1;
	}
	return h;
}

// height difference
int avl_tree::diff(avl_node * temp)
{
	int l_height = height(temp -> left);
	int r_height = height(temp -> right);
	int b_factor = l_height - r_height;
	return b_factor;
}

// left rotation - right heavy unbalance
avl_node * avl_tree::llRotation(avl_node * parent)
{	
	avl_node *temp;
	temp = parent -> right;
	parent -> right = temp -> left;
	temp -> left = parent;
	return temp;

}

// right rotation - left heavy unbalance
avl_node * avl_tree::rrRotation(avl_node * parent)
{	
	avl_node *temp;
	temp = parent -> left;
	parent -> left = temp -> right;
	temp -> right = parent;
	return temp;

}

// left right rotation - left's right subtree heavy
avl_node * avl_tree::lrRotation(avl_node * parent)
{	
	avl_node *temp;
	temp = parent -> left;
	parent -> left = llRotation(temp);
	return rrRotation(parent);

}

// right left ratation - right's left subtree heavy
avl_node * avl_tree::rlRotation(avl_node * parent)
{	
	avl_node *temp;
	temp = parent -> right;
	parent -> right =rrRotation(temp);
	return llRotation(parent);

}


// balances the avl tree by using rotation appropriate to the case
avl_node *avl_tree::balance(avl_node * temp)
{
	int bal_factor = diff(temp);
	if(bal_factor > 1)
	{
		if(diff(temp -> left) > 0) temp = rrRotation(temp);
		else temp = lrRotation(temp);
	}
	else if(bal_factor < - 1)
	{
		if(diff(temp -> right) > 0) temp = rlRotation(temp);
		else temp = llRotation(temp);
	}
	return temp;
}


//insert element into the tree
avl_node *avl_tree::insert(avl_node *root, int value)
{
	if(root == NULL)
	{
		root = new avl_node;
		root -> data = value;
		root -> left = NULL;
		root -> right = NULL;
		return root;
	}
	// recursion to find a suitable spot for the new node
	else if(value < root -> data)
	{
		root -> left = insert(root -> left, value);
		root = balance(root);
	}
	else if(value >= root -> data)
	{
		root -> right = insert(root -> right, value);
		root = balance(root);
	}
	return root;
}

// display avl tree

void avl_tree::display(avl_node* ptr, int level)
{
	int i;
	if(ptr != NULL)
	{
		display(ptr -> right, level +1);
		cout << "\n";
		if(ptr == root) cout<<"Root -> ";
		for(i = 0; i < level && ptr != root; i++) cout<< "       ";
		cout<< ptr -> data;
		display(ptr->left, level +1);
	}
}


// left - value - right order
void avl_tree::inorder(avl_node * tree)
{
	if(tree == NULL) return;
	inorder(tree -> left);
	cout << tree -> data<< " ";
	inorder(tree -> right);
}

// value - left - right order
void avl_tree::preorder(avl_node * tree)
{
	if(tree == NULL) return;
	cout << tree -> data<< " ";
	preorder(tree -> left);
	preorder(tree -> right);
}

// left - right - value order
void avl_tree::postorder(avl_node * tree)
{
	if(tree == NULL) return;
	postorder(tree -> left);
	postorder(tree -> right);
	cout << tree -> data<< " ";
}


void avl_tree::remove(int d)
{
	//locate the element
	bool found = false;
	
	if(isEmpty())
	{	
		cout << "Tree is empty! "<<endl;
		return; 
	}
	
	avl_node *curr;
	avl_node *parent;
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
			if(d > curr -> data) curr = curr -> right;
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
			root = balance(root);
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
			root = balance(root);
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
		root = balance(root);
		return;
	}
	
	//node with 2 children
	//replace node with smallest value in right subtree
	if(curr -> left != NULL && curr -> right != NULL)
	{
		avl_node * successor = curr -> right;
		avl_node * successorParent = curr;

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
		root = balance(root);
		return;
	}
return;	
}





int main()
{	
	int choice, item;
    avl_tree avl;
    while (1)
    {
        cout<<"\n---------------------"<<endl;
        cout<<"AVL Tree Implementation"<<endl;
        cout<<"\n---------------------"<<endl;
        cout<<"1.Insert Element into the tree"<<endl;
        cout<<"2.Display Balanced AVL Tree"<<endl;
        cout<<"3.InOrder traversal"<<endl;
        cout<<"4.PreOrder traversal"<<endl;
        cout<<"5.PostOrder traversal"<<endl;
        cout<<"6.Exit"<<endl;
        cout<<"7.Delete"<<endl;
        cout<<"Enter your Choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter value to be inserted: ";
            cin>>item;
            root = avl.insert(root, item);
            break;
        case 2:
            if (root == NULL)
            {
                cout<<"Tree is Empty"<<endl;
                continue;
            }
            cout<<"Balanced AVL Tree:"<<endl;
            avl.display(root, 1);
            break;
        case 3:
        	cout<<"Enter value to be deleted:";
        	cin>>item;
        	avl.remove(item);
        	cout<<"Balanced AVL Tree:"<<endl;
            avl.display(root, 1);
			break;
		case 4:
            cout<<"Inorder Traversal:"<<endl;
            avl.inorder(root);
            cout<<endl;
            break;
        case 5:
            cout<<"Preorder Traversal:"<<endl;
            avl.preorder(root);
            cout<<endl;
            break;
        case 6:
            cout<<"Postorder Traversal:"<<endl;
            avl.postorder(root);    
            cout<<endl;
            break;
        case 7:
            exit(1);    
            break;
        default:
            cout<<"Wrong Choice"<<endl;
        }
    }
    return 0;
}
	


