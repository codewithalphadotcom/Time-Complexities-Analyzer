#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <string>
using namespace std;

// B-Tree Node
struct BTreeNode
{
    int *keys;            // Array of keys
    int t;                // Minimum degree
    BTreeNode **children; // Array of child pointers
    int n;                // Current number of keys
    bool leaf;            // Is true if node is a leaf

    BTreeNode(int t, bool leaf)
    {
        this->t = t;
        this->leaf = leaf;

        keys = new int[2 * t - 1];
        children = new BTreeNode *[2 * t];
        n = 0;
    }

    ~BTreeNode()
    {
        delete[] keys;
        delete[] children;
    }

    void traverse()
    {
        for (int i = 0; i < n; i++)
        {
            if (!leaf)
            {
                children[i]->traverse();
            }
            cout << keys[i] << " ";
        }
        if (!leaf)
        {
            children[n]->traverse();
        }
    }

    BTreeNode *search(int key)
    {
        int i = 0;
        while (i < n && key > keys[i])
        {
            i++;
        }

        if (i < n && keys[i] == key)
        {
            return this;
        }

        if (leaf)
        {
            return nullptr;
        }

        return children[i]->search(key);
    }

    void insertNonFull(int key);
    void splitChild(int i, BTreeNode *y);
    void remove(int key);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPredecessor(int idx);
    int getSuccessor(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
};

// B-Tree Class
class BTree
{
private:
    BTreeNode *root;
    int t;

public:
    BTree(int t)
    {
        root = nullptr;
        this->t = t;
    }

    ~BTree()
    {
        delete root;
    }

    void traverse()
    {
        if (root)
        {
            root->traverse();
        }
    }

    BTreeNode *search(int key)
    {
        return root ? root->search(key) : nullptr;
    }

    void insert(int key);
    void remove(int key);
};

// Insert a key into the B-Tree
void BTree::insert(int key)
{
    if (!root)
    {
        root = new BTreeNode(t, true);
        root->keys[0] = key;
        root->n = 1;
    }
    else
    {
        if (root->n == 2 * t - 1)
        {
            BTreeNode *s = new BTreeNode(t, false);
            s->children[0] = root;
            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < key)
            {
                i++;
            }
            s->children[i]->insertNonFull(key);

            root = s;
        }
        else
        {
            root->insertNonFull(key);
        }
    }
}

// Insert a key into a non-full node
void BTreeNode::insertNonFull(int key)
{
    int i = n - 1;

    if (leaf)
    {
        while (i >= 0 && keys[i] > key)
        {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = key;
        n++;
    }
    else
    {
        while (i >= 0 && keys[i] > key)
        {
            i--;
        }
        if (children[i + 1]->n == 2 * t - 1)
        {
            splitChild(i + 1, children[i + 1]);

            if (keys[i + 1] < key)
            {
                i++;
            }
        }
        children[i + 1]->insertNonFull(key);
    }
}

// Split a full child
void BTreeNode::splitChild(int i, BTreeNode *y)
{
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
    {
        z->keys[j] = y->keys[j + t];
    }

    if (!y->leaf)
    {
        for (int j = 0; j < t; j++)
        {
            z->children[j] = y->children[j + t];
        }
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--)
    {
        children[j + 1] = children[j];
    }

    children[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
    {
        keys[j + 1] = keys[j];
    }

    keys[i] = y->keys[t - 1];
    n++;
}

// Remove a key from the B-Tree
void BTree::remove(int key)
{
    if (!root)
    {
        cout << "The tree is empty.\n";
        return;
    }

    root->remove(key);

    if (root->n == 0)
    {
        BTreeNode *temp = root;
        root = root->leaf ? nullptr : root->children[0];
        delete temp;
    }
}

// Remove a key from a node
void BTreeNode::remove(int key)
{
    int idx = 0;
    while (idx < n && keys[idx] < key)
    {
        idx++;
    }

    if (idx < n && keys[idx] == key)
    {
        if (leaf)
        {
            removeFromLeaf(idx);
        }
        else
        {
            removeFromNonLeaf(idx);
        }
    }
    else
    {
        if (leaf)
        {
            cout << "The key " << key << " is not in the tree.\n";
            return;
        }

        bool flag = (idx == n);
        if (children[idx]->n < t)
        {
            fill(idx);
        }

        if (flag && idx > n)
        {
            children[idx - 1]->remove(key);
        }
        else
        {
            children[idx]->remove(key);
        }
    }
}

// Remove from a leaf node
void BTreeNode::removeFromLeaf(int idx)
{
    for (int i = idx + 1; i < n; i++)
    {
        keys[i - 1] = keys[i];
    }
    n--;
}

// Remove from a non-leaf node
void BTreeNode::removeFromNonLeaf(int idx)
{
    int k = keys[idx];

    if (children[idx]->n >= t)
    {
        int pred = getPredecessor(idx);
        keys[idx] = pred;
        children[idx]->remove(pred);
    }
    else if (children[idx + 1]->n >= t)
    {
        int succ = getSuccessor(idx);
        keys[idx] = succ;
        children[idx + 1]->remove(succ);
    }
    else
    {
        merge(idx);
        children[idx]->remove(k);
    }
}

// Get predecessor of a key
int BTreeNode::getPredecessor(int idx)
{
    BTreeNode *cur = children[idx];
    while (!cur->leaf)
    {
        cur = cur->children[cur->n];
    }
    return cur->keys[cur->n - 1];
}

// Get successor of a key
int BTreeNode::getSuccessor(int idx)
{
    BTreeNode *cur = children[idx + 1];
    while (!cur->leaf)
    {
        cur = cur->children[0];
    }
    return cur->keys[0];
}

// Fill a child node
void BTreeNode::fill(int idx)
{
    if (idx != 0 && children[idx - 1]->n >= t)
    {
        borrowFromPrev(idx);
    }
    else if (idx != n && children[idx + 1]->n >= t)
    {
        borrowFromNext(idx);
    }
    else
    {
        if (idx != n)
        {
            merge(idx);
        }
        else
        {
            merge(idx - 1);
        }
    }
}

// Borrow from the previous child
void BTreeNode::borrowFromPrev(int idx)
{
    BTreeNode *child = children[idx];
    BTreeNode *sibling = children[idx - 1];

    for (int i = child->n - 1; i >= 0; i--)
    {
        child->keys[i + 1] = child->keys[i];
    }

    if (!child->leaf)
    {
        for (int i = child->n; i >= 0; i--)
        {
            child->children[i + 1] = child->children[i];
        }
    }

    child->keys[0] = keys[idx - 1];
    if (!leaf)
    {
        child->children[0] = sibling->children[sibling->n];
    }
    keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n++;
    sibling->n--;
}

// Borrow from the next child
void BTreeNode::borrowFromNext(int idx)
{
    BTreeNode *child = children[idx];
    BTreeNode *sibling = children[idx + 1];

    child->keys[child->n] = keys[idx];
    if (!child->leaf)
    {
        child->children[child->n + 1] = sibling->children[0];
    }

    keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; i++)
    {
        sibling->keys[i - 1] = sibling->keys[i];
    }

    if (!sibling->leaf)
    {
        for (int i = 1; i <= sibling->n; i++)
        {
            sibling->children[i - 1] = sibling->children[i];
        }
    }

    child->n++;
    sibling->n--;
}

// Merge two child nodes
void BTreeNode::merge(int idx)
{
    BTreeNode *child = children[idx];
    BTreeNode *sibling = children[idx + 1];

    child->keys[t - 1] = keys[idx];

    for (int i = 0; i < sibling->n; i++)
    {
        child->keys[i + t] = sibling->keys[i];
    }

    if (!child->leaf)
    {
        for (int i = 0; i <= sibling->n; i++)
        {
            child->children[i + t] = sibling->children[i];
        }
    }

    for (int i = idx + 1; i < n; i++)
    {
        keys[i - 1] = keys[i];
    }

    for (int i = idx + 2; i <= n; i++)
    {
        children[i - 1] = children[i];
    }

    child->n += sibling->n + 1;
    n--;

    delete sibling;
}

#endif