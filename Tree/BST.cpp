#include <iostream>
#include <cstdlib>

using namespace std;

/*
    The Program has Following functions i.e. BST Operations
    1) Insert
    2) Search
    3) Inorder Traversal
    4) Delete
    5) Height
    6) InPre: Which finds Inorder Predecessor
    7) InSuc: Which finds Inorder Successor
*/
struct node
{
    int data;
    node *left, *right;
};

class BST
{
private:
    node *root;

public:
    BST()
    {
        root = NULL;
    }

    void insert(int n)
    {
        node *nn = new node;
        if (!nn)
            return;

        nn->data = n;
        nn->left = nn->right = NULL;

        if (!root)
        {
            root = nn;
            return;
        }

        node *ptr = root;
        while (ptr)
        {
            if (ptr->data == n)
            {
                delete nn;
                return;
            }

            if (ptr->data < n)
            {
                if (!ptr->right)
                {
                    ptr->right = nn;
                    return;
                }
                ptr = ptr->right;
            }

            else
            {
                if (!ptr->left)
                {
                    ptr->left = nn;
                    return;
                }
                ptr = ptr->left;
            }
        }
    }

    void search(int n)
    {
        if (!root)
            return;

        node *ptr = root;
        while (ptr)
        {
            if (ptr->data == n)
            {
                cout << n << " Found.\n";
                return;
            }

            if (ptr->data < n)
                ptr = ptr->right;
            else
                ptr = ptr->left;
        }

        cout << n << " Not Found.\n";
        return;
    }

    int height(node *p)
    {
        int x, y;
        if (!root)
            return -1;
        x = height(p->left);
        y = height(p->right);

        return x > y ? x + 1 : y + 1;
    }

    node *InPre(node *p)
    {
        while (p && p->right != NULL)
            p = p->right;
        return p;
    }

    node *InSuc(node *p)
    {
        while (p && p->left != NULL)
            p = p->left;
        return p;
    }

    node *del(node *p, int n)
    {
        node *q = NULL;

        if (!p)
            return NULL; // empty tree

        if (p->left == NULL & p->right == NULL) // leaf node.
        {
            if (p == root) // if root is the only node.
                root = NULL;
            delete p;
            return NULL;
        }

        // if deleting node is an internal node
        if (p->data < n)
        {
            p->right = del(p->right, n);
        }

        else if (p->data > n)
        {
            p->left = del(p->left, n);
        }

        else
        {
            if (height(p->left) > height(p->right))
            {
                q = InPre(p->left);
                p->data = q->data;
                p->left = del(p->left, q->data);
            }

            else
            {
                q = InSuc(p->right);
                p->data = q->data;
                p->right = del(p->right, q->data);
            }
        }

        return p;
    }

    void del(int n)
    {
        del(root, n);
        return;
    }

    void inorder_rec(node *root)
    {
        if (!root)
            return;

        inorder_rec(root->left);
        cout << root->data << "\t";
        inorder_rec(root->right);
        return;
    }

    void inorder()
    {
        inorder_rec(root);
        return;
    }
};

int main()
{
    BST b1;
    int n = 10;
    while (n--)
    {
        b1.insert(rand() % 100 + 1);
    }

    b1.inorder();
    cout << endl;
    b1.search(50);

    b1.del(50);

    b1.inorder();
    cout << endl;

    b1.search(50);

    return 0;
}