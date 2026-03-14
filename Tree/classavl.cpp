#include <iostream>
using namespace std;

struct node
{
    int data;
    node *left, *right, *parent;
    int bf;
};

int max(int a, int b)
{
    return a > b ? a : b;
}

int ht(node *p)
{
    if (!p)
        return -1;

    return 1 + max(ht(p->left), ht(p->right));
}

node *imbalance(node *n)
{
    while (n)
    {
        if (n->bf == 2 || n->bf == -2)
            return n;
        n = n->parent;
    }
    return n;
}

class AVL
{
private:
    node *root;

public:
    AVL()
    {
        root = NULL;
    }

    void inorder_rec(node *root)
    {
        if (!root)
            return;
        inorder_rec(root->left);
        cout << root->data << "\t" << root->bf << "\n";
        inorder_rec(root->right);

        return;
    }

    void inorder()
    {
        inorder_rec(root);
        cout << endl;
        return;
    }

    void adjust_bf(node *p)
    {
        node *nn = p;
        while (p)
        {
            p->bf = ht(p->left) - ht(p->right);
            p = p->parent;
        }

        // Displaying Type of Rotation required
        node *i = imbalance(nn);

        if (!i)
        {
            // cout << "\nNo Imbalance!\n";
            return;
        }

        if (nn->data < i->data && nn->data < i->left->data)
        {
            cout << "\nLLRotation() to be called.\n";
            LLRotation(i);
            return;
        }

        if (nn->data < i->data && nn->data > i->left->data)
        {
            cout << "\nLRRotation() to be called.\n";
            RRRotation(i->left);
            LLRotation(i);
            return;
        }

        if (nn->data > i->data && nn->data > i->right->data)
        {
            cout << "\nRRRotation() to be called.\n";
            RRRotation(i);
            return;
        }

        if (nn->data > i->data && nn->data < i->right->data)
        {
            cout << "\nRLRotation() to be called.\n";
            LLRotation(i->right);
            RRRotation(i);
            return;
        }
        return;
    }

    void insert(int n)
    {
        node *nn = new node;
        if (!nn)
            return;

        nn->data = n;
        nn->left = nn->right = NULL;
        nn->parent = NULL;
        nn->bf = 0;

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

            if (ptr->data > n)
            {
                if (!ptr->left)
                {
                    nn->parent = ptr;
                    ptr->left = nn;
                    adjust_bf(nn);
                    return;
                }
                ptr = ptr->left;
            }

            else
            {
                if (!ptr->right)
                {
                    nn->parent = ptr;
                    ptr->right = nn;
                    adjust_bf(nn);
                    return;
                }
                ptr = ptr->right;
            }
            adjust_bf(nn);
        }
    }
    void LLRotation(node *p);
    void RRRotation(node *p);
};

void AVL::LLRotation(node *i)
{
    node *iL, *iLR, *ip;
    iL = i->left;
    iLR = iL->right;
    ip = i->parent;

    if (!ip)
    {
        root = iL;
        iL->parent = NULL;
    }

    else
    {
        iL->parent = ip;
        if (i->data > ip->data)
            ip->right = iL;
        else
            ip->left = iL;
    }

    iL->right = i;
    i->parent = iL;
    i->left = iLR;

    if (iLR)
        iLR->parent = i;

    i->bf = ht(i->left) - ht(i->right);
    iL->bf = ht(iL->left) - ht(iL->right);
    return;
}

void AVL::RRRotation(node *i)
{
    node *iR, *iRL, *ip;
    iR = i->right;
    iRL = iR->left;
    ip = i->parent;

    if (!ip)
    {
        root = iR;
        iR->parent = NULL;
    }

    else
    {
        iR->parent = ip;
        if (i->data > ip->data)
            ip->right = iR;
        else
            ip->left = iR;
    }

    iR->left = i;
    i->parent = iR;
    i->right = iRL;

    if (iRL)
        iRL->parent = i;

    i->bf = ht(i->left) - ht(i->right);
    iR->bf = ht(iR->left) - ht(iR->right);
    return;
}

int main()
{
    AVL t_ll, t_rr, t_lr, t_rl;

    cout << "Testing LL Rotation:";
    t_ll.insert(10);
    t_ll.insert(8);
    t_ll.insert(4);
    t_ll.inorder();

    cout << "Testing RR Rotation:";
    t_rr.insert(10);
    t_rr.insert(20);
    t_rr.insert(30);
    t_rr.inorder();

    // Note: You must implement LR/RL rotation functions for these to work!
    cout << "Testing LR Rotation:";
    t_lr.insert(30);
    t_lr.insert(10);
    t_lr.insert(20);
    t_lr.inorder();

    cout << "Testing RL Rotation:";
    t_rl.insert(10);
    t_rl.insert(30);
    t_rl.insert(20);
    t_rl.inorder();

    return 0;
}
