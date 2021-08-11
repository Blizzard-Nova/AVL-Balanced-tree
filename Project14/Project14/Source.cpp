#include <iostream>
using namespace std;
struct node
{
	int data;
	node* right;
	node* left;
	int height;
};
class BST
{

public:
	BST();
	void insert(int val);
	void inorder_print();
	int max_depth();
private:
	node* insert(int val, node* leaf);
	void inorder_print(node* leaf);
	int MaxDepth(node* leaf);
	int getBalance(node* leaf);
	int height(node* leaf);
	node* RightRotate(node* a);
	node* LeftRotate(node* b);
	node* root;
};

BST::BST()
{
	root = NULL;
}
node* BST::insert(int val, node* leaf)
{
	if (leaf == NULL)
	{
		leaf = new node;
		leaf->data = val;
		leaf->left = NULL;
		leaf->right = NULL;
		leaf->height = 1;
	}
	else if (val < leaf->data)
	{
		leaf->left = insert(val, leaf->left);
	}
	else if (val > leaf->data)
	{
		leaf->right = insert(val, leaf->right);
	}
	return leaf;


	leaf->height = MaxDepth(leaf);

	int balance = getBalance(leaf);

	//If nodes become un balanced then there are four cases

	//LEFT LEFT CASE
	if (balance > 1 && val < leaf->left->data)
	{
		return RightRotate(leaf);
	}

	//RIGHT RIGHT CASSE
	if (balance > 1 && val > leaf->right->data)
	{
		return LeftRotate(leaf);
	}

	//LEFT RIGHT CASE
	if (balance > 1 && val > leaf->left->data)
	{
		leaf->left = LeftRotate(leaf->left);
		return RightRotate(leaf);
	}

	//RIGHT LEFT ROTATE
	if (balance > 1 && val < leaf->right->data)
	{
		leaf->right = RightRotate(leaf->right);
		return LeftRotate(leaf);
	}

}

void BST::inorder_print(node* leaf)
{
	if (leaf == NULL)
		return;
	else
	{

		inorder_print(leaf->left);
		cout << leaf->data << " " << endl;
		inorder_print(leaf->right);
	}
}

int BST::MaxDepth(node* leaf)
{
	if (leaf == NULL)
	{
		return 0;
	}
	else
	{
		int LDepth = MaxDepth(leaf->left);
		int RDepth = MaxDepth(leaf->right);
		if (LDepth > RDepth)
		{
			return(LDepth + 1);
		}
		else
		{
			return(RDepth + 1);
		}

	}

}

void BST::insert(int x)
{
	root = insert(x, root);
}

void BST::inorder_print()
{
	inorder_print(root);
}

int BST::max_depth()
{
	return MaxDepth(root);

}

node* BST::RightRotate(node* y)
{
	node* x = y->left;
	node* child = x->right;

	//Now Performing Rotation

	x->right = y;
	y->left = child;

	//Updating heights
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	//Return new root

	return x;
}
node* BST::LeftRotate(node* x)
{
	node* y = x->right;
	node* Child2 = y->left;

	//Perform rotation
	y->left = x;
	y->right = Child2;

	//Updating Heights
	x->height = max(height(x->left), height(x->right) + 1);
	y->height = max(height(y->left), height(x->right) + 1);

	return y;
}

int BST::getBalance(node* leaf)
{
	if (leaf == NULL)
	{
		return 0;
	}
	else
	{
		return height(leaf->left) - height(leaf->right);
	}
}

int BST::height(node* leaf)
{
	if (leaf == NULL)
	{
		return 0;
	}
	else
	{
		return leaf->height;
	}
}
int main()
{
	BST bst;
	bst.insert(20);
	bst.insert(15);
	bst.insert(10);
	bst.insert(25);
	bst.insert(30);
	bst.insert(12);
	bst.insert(22);
	cout << "Inorder arrangement of the balanced tree is \n";
	bst.inorder_print();

	cout << endl;
	cout << endl;

	cout << "Maximum depth of the tree is  "<< bst.max_depth()<<endl;
	

	return 0;
}