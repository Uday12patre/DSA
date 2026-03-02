#include <iostream>
#include <cstdlib>
using namespace std;

struct node
{
	node *left, *right;
	int data;
	int height;
};

int nodeHeight(node *p)
{
	if (!p)
		return 0;
	int hl = p->left ? p->left->height : 0;
	int hr = p->right ? p->right->height : 0;
	return hl > hr ? hl + 1 : hr + 1;
}

int BalanceFactor(node *p)
{
	if (!p)
		return 0;
	return nodeHeight(p->left) - nodeHeight(p->right);
}

class AVL
{
private:
	node *root;
	// LL Imbalance or Right Rotation
	node *LLRotation(node *p)
	{
		node *pl = p->left;
		p->left = pl->right;
		pl->right = p;

		p->height = nodeHeight(p);
		pl->height = nodeHeight(pl);
		return pl;
	}

	// RR Imbalance or Left Rotation
	node *RRRotation(node *p)
	{
		node *pr = p->right;
		p->right = pr->left;
		pr->left = p;

		p->height = nodeHeight(p);
		pr->height = nodeHeight(pr);
		return pr;
	}

	// Double L-R Rotation
	node *LRRotation(node *p)
	{
		p->left = RRRotation(p->left);
		return LLRotation(p);
	}

	// Double R-L Rotation
	node *RLRotation(node *p)
	{
		p->right = LLRotation(p->right);
		return RRRotation(p);
	}

	// recursive insertion function
	node *insert_rec(node *p, int n)
	{
		if (!p)
		{
			node *nn = new node;
			nn->left = NULL;
			nn->right = NULL;
			nn->data = n;
			nn->height = 1;
			return nn;
		}

		if (n < p->data)
			p->left = insert_rec(p->left, n);
		else if (n > p->data)
			p->right = insert_rec(p->right, n);
		else
			return p; // Duplicate Values not Allowed

		p->height = nodeHeight(p);

		int bf = BalanceFactor(p);

		if (bf == 2 && BalanceFactor(p->left) >= 0)
			return LLRotation(p);
		if (bf == 2 && BalanceFactor(p->left) == -1)
			return LRRotation(p);
		if (bf == -2 && BalanceFactor(p->right) <= 0)
			return RRRotation(p);
		if (bf == -2 && BalanceFactor(p->right) == 1)
			return RLRotation(p);

		return p;
	}

	void inorder_rec(node *p)
	{
		if (!p)
			return;

		inorder_rec(p->left);
		cout << p->data << "\t";
		inorder_rec(p->right);
		return;
	}

public:
	AVL()
	{
		root = NULL;
	}

	void insert(int n)
	{
		root = insert_rec(root, n);
		return;
	}

	void inorder()
	{
		inorder_rec(root);
		cout << endl;
		return;
	}
};

int main()
{
	AVL A1;
	A1.insert(10);
	A1.insert(5);
	A1.insert(2);

	cout << "Inorder Traversal: ";
	A1.inorder();

	return 0;
}