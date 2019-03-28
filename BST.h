#ifndef BST_H
#define BST_H

#include <stack>
#include <cstdlib>

using namespace std;

    /**
    * @brief Node to hold data and connections to other nodes
    */
template<class T>
struct node {

        /** data of T type */
    T data;

        /** Pointer to left branch of node */
    node *left;

        /** Pointer to right branch of node */
    node *right;
};

    /**
    * @author Kane Nikander
    * @version 4.0
    * @date 19/05/2017
    * @section description
    * @brief The BST class is a template class for a binary search tree.
    */
template<class T>
class BST
{
    typedef node<T> node;

    private:

            /** Root node of the tree */
        node *root;

            /**
            * @brief Searches for node to be removed.
            *
            * @param T data, node *removeNode, node *parentNode
            * @return bool
            */
        void Remove(node* &removeNode);

    public:

            /**
            * @brief A constructor.
            * Construct an empty BST.
            */
        BST();

            /**
            * @brief Adds item into tree.
            *
            * @param T data
            * @return void
            */
        bool Insert(T data);

            /**
            * @brief Searches tree for specific item and removes it.
            *
            * @param T data
            * @return bool
            */
        bool Remove(T data);

            /**
            * @brief Searches tree for specific item and returns whether it was found or not.
            *
            * @param T data
            * @return bool
            */
        bool Search(T data);

            /**
            * @brief Traverse through the contents of tree in order.
            *
            * @return void
            */
        void InOrder(void (*visit) (T&));

            /**
            * @brief Traverse through the contents of tree in pre order.
            *
            * @return void
            */
        void PreOrder(void (*visit) (T&));

            /**
            * @brief Traverse through the contents of tree in post order.
            *
            * @return void
            */
        void PostOrder(void (*visit) (T&));

};

template<class T>
BST<T>::BST() {
    root = NULL;
}

template<class T>
bool BST<T>::Insert(T data) {

    node *current;
    node *trailCurrent;
    node *newNode;

    newNode = new node;
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if(root == NULL) {
        root = newNode;
    } else {
        current = root;
        while(current != NULL) {
            trailCurrent = current;
            if(current->data == data) {
                return false; //duplicate value
            } else if(current->data > data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        if(trailCurrent->data > data) {
            trailCurrent->left = newNode;
        } else {
            trailCurrent->right = newNode;
        }
    }
    return true;

}

template<class T>
bool BST<T>::Remove(T data) {

    node *current;
    node *trailCurrent;
    bool found = false;

    if(root == NULL) {
        //empty tree
    } else {
        current = root;
        trailCurrent = root;

        while(current != NULL && !found) {
            if(current->data == data) {
                found = true;
            } else {
                trailCurrent = current;
                if(current->data > data) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
        }
        if(current == NULL) {
            //item not in tree
        } else if(found) {
            if(current == root) {
                Remove(root);
            } else if(trailCurrent->data > data) {
                Remove(trailCurrent->left);
            } else {
                Remove(trailCurrent->right);
            }
        } else {
            //item not in tree
        }
    }
    return found;

}

template<class T>
void BST<T>::Remove(node* &p) {

    node *current;
    node *trailCurrent;
    node *temp;

    if(p == NULL) {
        //node to be deleted is NULL
    } else if(p->left == NULL && p->right == NULL) {

        temp = p;
        p = NULL;
        delete temp;

    } else if(p->left == NULL) {

        temp = p;
        p = temp->right;
        delete temp;

    } else if(p->right == NULL) {

        temp = p;
        p = temp->left;
        delete temp;

    } else {

        current = p->left;
        trailCurrent = NULL;

        while(current->right != NULL) {
            trailCurrent = current;
            current = current->right;
        }

        p->data = current->data;

        if(trailCurrent == NULL) {
            p->left = current->left;
        } else {
            trailCurrent->right = current->left;
        }

        delete current;

    }

}

template<class T>
bool BST<T>::Search(T data) {

    node *current;
    bool found = false;

    if(root == NULL) {
        //empty tree
    } else {
        current = root;
        while(current != NULL && !found) {
            if(current->data == data) {
                found = true;
            } else if(current->data > data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
    }
    return found;

}

template<class T>
void BST<T>::InOrder(void (*visit) (T& item)) {

    stack<node*> nodeStack;
    node *current;
    current = root;

    while((current != NULL) || (!nodeStack.empty())) {
        if(current != NULL) {
            nodeStack.push(current);
            current = current->left;
        } else {
            current = nodeStack.top();
            nodeStack.pop();
            (*visit) (current->data);
            current = current->right;
        }
    }

}

template<class T>
void BST<T>::PreOrder(void (*visit) (T& item)) {

    stack<node*> nodeStack;
    node *current;
    current = root;

    while((current != NULL) || (!nodeStack.empty())) {
        if(current != NULL) {
            (*visit) (current->data);
            nodeStack.push(current);
            current = current->left;
        } else {
            current = nodeStack.top();
            nodeStack.pop();
            current = current->right;
        }
    }

}

template<class T>
void BST<T>::PostOrder(void (*visit) (T& item)) {

    stack<node*> nodeStack;
    stack<int> intStack;
    node *current;
    current = root;
    int v = 0;

    if(current != NULL) {

        nodeStack.push(current);
        intStack.push(1);
        current = current->left;

        while(!nodeStack.empty()) {
            if(current != NULL && v == 0) {
                nodeStack.push(current);
                intStack.push(1);
                current = current->left;
            } else {
                current = nodeStack.top();
                nodeStack.pop();
                v = intStack.top();
                intStack.pop();
                if(v == 1) {
                    nodeStack.push(current);
                    intStack.push(2);
                    current = current->right;
                    v = 0;
                } else {
                    (*visit) (current->data);
                }
            }
        }

    }

}

#endif // BST_H
