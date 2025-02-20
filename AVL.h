#ifndef AVL_H
#define AVL_H

#include <string>
using namespace std;

// structure for Node containing data and pointers to left and right children in an AVL Tree
struct AVLNode
{
    int id;
    string name;
    int age;
    int height;
    AVLNode *left;
    AVLNode *right;

    AVLNode(int id, string name, int age)
        : id(id), name(name), age(age), height(1), left(nullptr), right(nullptr) {}
};

// AVL Tree
class AVL
{
private:
    AVLNode *root; // root node of the AVL Tree

    int getHeight(AVLNode *node)
    {
        return node ? node->height : 0; // if node is not null then return the height of the node otherwise return 0
    }

    int getBalanceFactor(AVLNode *node)
    {
        return node ? getHeight(node->left) - getHeight(node->right) : 0; // if node is not null then return the difference of height of left and right children of the node otherwise return 0
    }

    AVLNode *rotateRight(AVLNode *y)
    {
        AVLNode *x = y->left;     // x is the left child of y
        AVLNode *temp = x->right; // temp is the right child of x

        x->right = y;   // make y the right child of x
        y->left = temp; // make temp the left child of y

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1; // update the height of y
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1; // update the height of x

        return x; // return the new root
    }

    AVLNode *rotateLeft(AVLNode *x)
    {
        AVLNode *y = x->right;   // y is the right child of x
        AVLNode *temp = y->left; // temp is the left child of y

        y->left = x;     // make x the left child of y
        x->right = temp; // make temp the right child of x

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1; // update the height of x
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1; // update the height of x and y

        return y; // return the new root
    }

    AVLNode *insert(AVLNode *node, int id, string name, int age)
    {
        if (!node)
        {
            return new AVLNode(id, name, age); // if node is null then create a new node
        }
        if (id < node->id)
        {
            node->left = insert(node->left, id, name, age); // if id is less than the id of the node then insert in the left subtree
        }
        else if (id > node->id)
        {
            node->right = insert(node->right, id, name, age); // if id is greater than the id of the node then insert in the right subtree
        }
        else
            return node; // Duplicate IDs not allowed

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1; // update the height of the node

        int balance = getBalanceFactor(node); // get the balance factor of the node

        // Four cases of rotation

        // Left-Left case
        if (balance > 1 && id < node->left->id) // if balance is greater than 1 and id is less than the id of the left child of the node
        {
            return rotateRight(node); // perform right rotation
        }
        // Right-Right case
        if (balance < -1 && id > node->right->id) // if balance is less than -1 and id is greater than the id of the right child of the node
        {
            return rotateLeft(node); // perform left rotation
        }
        // Left-Right case
        if (balance > 1 && id > node->left->id) // if balance is greater than 1 and id is greater than the id of the left child of the node
        {
            node->left = rotateLeft(node->left); // perform left rotation on the left child of the node
            return rotateRight(node);            // perform right rotation on the node
        }

        // Right-Left case
        if (balance < -1 && id < node->right->id) // if balance is less than -1 and id is less than the id of the right child of the node
        {
            node->right = rotateRight(node->right); // perform right rotation on the right child of the node
            return rotateLeft(node);                // perform left rotation on the node
        }

        return node; // return the node
    }

    AVLNode *minValueNode(AVLNode *node)
    {
        AVLNode *current = node; // current is the node
        while (current->left)
        {
            current = current->left; // traverse to the leftmost node
        }
        return current; // return the leftmost node
    }

    AVLNode *deleteNode(AVLNode *root, int id)
    {
        if (!root)
        {
            return root; // if root is null then return root
        }
        if (id < root->id)
        {
            root->left = deleteNode(root->left, id); // if id is less than the id of the root then delete from the left subtree
        }
        else if (id > root->id)
        {
            root->right = deleteNode(root->right, id); // if id is greater than the id of the root then delete from the right subtree
        }
        else
        {
            // Node with only one child or no child
            if (!root->left || !root->right) // if root has no child or only one child
            {
                AVLNode *temp = root->left ? root->left : root->right;

                // if root has no child
                if (!temp)
                {
                    temp = root;    // make temp the root
                    root = nullptr; // make root null
                }
                else
                    // if root has only one child
                    *root = *temp; // copy the data of temp to root

                delete temp;
            }
            else
            {
                AVLNode *temp = minValueNode(root->right); // find the inorder successor of the root

                // Copy the inorder successor's data to this node
                root->id = temp->id;
                root->name = temp->name;
                root->age = temp->age;

                root->right = deleteNode(root->right, temp->id); // delete the inorder successor
            }
        }

        if (!root)
        {
            return root; // if root is null then return root
        }
        root->height = max(getHeight(root->left), getHeight(root->right)) + 1; // update the height of the root

        int balance = getBalanceFactor(root); // get the balance factor of the root

        // Left-Left case
        if (balance > 1 && getBalanceFactor(root->left) >= 0)
            return rotateRight(root);

        // Left-Right case
        if (balance > 1 && getBalanceFactor(root->left) < 0)
        {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // Right-Right case
        if (balance < -1 && getBalanceFactor(root->right) <= 0)
            return rotateLeft(root);

        // Right-Left case
        if (balance < -1 && getBalanceFactor(root->right) > 0)
        {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    AVLNode *search(AVLNode *node, int id)
    {
        if (!node || node->id == id)
        {
            // if node is null or id is equal to the id of the node then return the node
            return node;
        }
        if (id < node->id)
        {
            // if id is less than the id of the node then search in the left subtree
            return search(node->left, id);
        }
        // if id is greater than the id of the node then search in the right subtree
        return search(node->right, id);
    }

public:
    AVL() : root(nullptr) {}

    void insert(int id, string name, int age)
    {
        // insert the data
        root = insert(root, id, name, age);
    }

    void remove(int id)
    {
        // delete the data
        root = deleteNode(root, id);
    }

    bool search(int id)
    {
        // search for the data
        return search(root, id) != nullptr;
    }
};

#endif
