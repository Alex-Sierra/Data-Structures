#include <bits/stdc++.h>
 
using namespace std;

// avl
struct avl
{
    int key;
    int height;
    avl *left;
    avl *right;

    avl(int k) {
        key = k;
        height = 1;
        left = NULL;
        right = NULL;
    }

    int getBalance() {
        int leftHeight = 0;
        int rightHeight = 0;

        if (left != NULL)
            leftHeight = left->height;

        if (right != NULL)
            rightHeight = right->height;

        return leftHeight - rightHeight;
    }

    void updateHeight() {
        int leftHeight = 0;
        int rightHeight = 0;

        if (left != NULL)
            leftHeight = left->height;

        if (right != NULL)
            rightHeight = right->height;

        height = max(leftHeight, rightHeight) + 1;
    }

    avl *rotateLeft() {
        avl *newRoot = right;
        right = newRoot->left;
        newRoot->left = this;
        updateHeight();
        newRoot->updateHeight();
        return newRoot;
    }

    avl *rotateRight() {
        avl *newRoot = left;
        left = newRoot->right;
        newRoot->right = this;
        updateHeight();
        newRoot->updateHeight();
        return newRoot;
    }

    avl *balance() {
        updateHeight();
        int balance = getBalance();

        if (balance == 2) {
            if (left->getBalance() < 0)
                left = left->rotateLeft();
            return rotateRight();
        }

        if (balance == -2) {
            if (right->getBalance() > 0)
                right = right->rotateRight();
            return rotateLeft();
        }

        return this;
    }

    avl *insert(int k) {
        if (k < key) {
            if (left == NULL)
                left = new avl(k);
            else
                left = left->insert(k);
        }
        else {
            if (right == NULL)
                right = new avl(k);
            else
                right = right->insert(k);
        }

        return balance();
    }

    avl *findMin() {
        if (left == NULL)
            return this;
        else
            return left->findMin();
    }

    avl *removeMin() {
        if (left == NULL)
            return right;
        left = left->removeMin();
        return balance();
    }

    avl *remove(int k) {
        if (k < key)
            left = left->remove(k);
        else if (k > key)
            right = right->remove(k);
        else {
            avl *leftChild = left;
            avl *rightChild = right;

            delete this;

            if (rightChild == NULL)
                return leftChild;

            avl *min = rightChild->findMin();
            min->right = rightChild->removeMin();
            min->left = leftChild;
            return min->balance();
        }

        return balance();
    }

    ~avl()
    {
        if (left != NULL)
            delete left;

        if (right != NULL)
            delete right;
    }
};