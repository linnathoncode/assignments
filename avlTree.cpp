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
		int height(avl_node *);
		int diff(avl_node *);
		avl_node * rrRotation(avl_node *);
		avl_node * llRotation(avl_node *);
		avl_node * lrRotation(avl_node *);
		avl_node * rlRotation(avl_node *);
		avl_node * balance(avl_node *);
		avl_node * insert(avl_node *, int);
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
		for(i = 0; i < level && ptr != root; i++) cout<< "               ";
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
            cout<<"Inorder Traversal:"<<endl;
            avl.inorder(root);
            cout<<endl;
            break;
        case 4:
            cout<<"Preorder Traversal:"<<endl;
            avl.preorder(root);
            cout<<endl;
            break;
        case 5:
            cout<<"Postorder Traversal:"<<endl;
            avl.postorder(root);    
            cout<<endl;
            break;
        case 6:
            exit(1);    
            break;
        default:
            cout<<"Wrong Choice"<<endl;
        }
    }
    return 0;
}
	


