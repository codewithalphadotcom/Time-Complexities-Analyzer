#ifndef BST_H
#define BST_H

#include <string>
using namespace std;

// structure for Node containing data and pointers to left and right children in a Binary Search Tree
struct BSTNode
{
    int id;
    string name;
    int age;
    BSTNode *left;
    BSTNode *right;

    BSTNode(int id, string name, int age)
        : id(id), name(name), age(age), left(nullptr), right(nullptr) {}
};

// Binary Search Tree
class BinarySearchTree
{
private:
    BSTNode *root; // root node of the Binary Search Tree

    BSTNode *insert(BSTNode *node, int id, string name, int age)
    {
        // if node is null then create a new node
        if (!node)
        {
            return new BSTNode(id, name, age);
        }
        // if id is less than the id of the node then insert in the left subtree
        if (id < node->id)
        {
            node->left = insert(node->left, id, name, age);
        }
        // if id is greater than the id of the node then insert in the right subtree
        else if (id > node->id)
        {
            node->right = insert(node->right, id, name, age);
        }
        return node;
    }

    BSTNode *search(BSTNode *node, int id)
    {
        // if node is null or id is equal to the id of the node then return the node
        if (!node || node->id == id)
        {
            return node;
        }
        // if id is less than the id of the node then search in the left subtree
        if (id < node->id)
        {
            return search(node->left, id);
        }
        // if id is greater than the id of the node then search in the right subtree
        else
        {
            return search(node->right, id);
        }
    }

    // find the minimum node in the right subtree
    BSTNode *findMin(BSTNode *node)
    {
        // keep traversing to the left until the left child is null
        while (node && node->left)
        {
            node = node->left; // move to the left child
        }
        return node;
    }

    BSTNode *deleteNode(BSTNode *node, int id)
    {
        // if node is null then return null
        if (!node)
        {
            return nullptr;
        }
        // if id is less than the id of the node then delete from the left subtree
        if (id < node->id)
        {
            node->left = deleteNode(node->left, id);
        }
        // if id is greater than the id of the node then delete from the right subtree
        else if (id > node->id)
        {
            node->right = deleteNode(node->right, id);
        }
        else
        {
            // if node has no child or only one child
            if (!node->left)
            {
                BSTNode *temp = node->right; // if node has no left child then make the right child the new node
                delete node;
                return temp;
            }
            else if (!node->right)
            {
                // if node has no right child then make the left child the new node
                BSTNode *temp = node->left;
                delete node;
                return temp;
            }
            // if node has two children
            BSTNode *temp = findMin(node->right); // find the minimum node in the right subtree

            // copy the data of the minimum node to the node
            node->id = temp->id;
            node->name = temp->name;
            node->age = temp->age;

            node->right = deleteNode(node->right, temp->id); // delete the minimum node in the right subtree
        }
        return node; // return the node
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int id, string name, int age)
    {
        // insert the data
        root = insert(root, id, name, age);
    }

    bool search(int id)
    {
        // search for the data
        return search(root, id) != nullptr;
    }

    void remove(int id)
    {
        // delete the data
        root = deleteNode(root, id);
    }
};

#endif
