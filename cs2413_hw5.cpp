#include <iostream>
#include <vector>

using namespace std;

class node {

    public:
        int data;
        node *left, *right;
        node(int);
};

//initializes node with data
node ::node(int data) {
    this->data = data;
    left = right = NULL;
}

class tree {

    node* root;
    public:
        void postOrderEnum(int);
        node* insert(int);
        node* search(int);
        node* delet(int);
        tree(int);
};

//constructor for tree that initializes the root node
tree ::tree(int rootKey) {
    root = new node(rootKey);
}

//insert key into tree
node* tree::insert(int key) {

    node* temp = root;
    while (temp != NULL) {
        //if data is already in the tree, insertion failure
        if (temp->data == key) {
            return NULL;
        }

        //if input is greater than the current node data
        else if (key > temp->data) {
            //if the target child is null, set it to value
            if (temp->right == NULL) {
                temp->right = new node(key);
                return temp->right;
            }
            //else, iterate to the child
            temp = temp->right;
            continue;
        }

        //if input is less than the current node data
        else if (key < temp->data) {
            //if the target child is null, set it to the value
            if (temp->left == NULL) {
                temp->left = new node(key);
                return temp->left;
            }
            //else, iterate to the child
            temp = temp->left;
            continue;
        }
    }

    //failure to insert node
    return NULL;
}

//search tree for a key
node* tree::search(int key) {

    node* temp = root;

    while (temp != NULL) {

        //if the node data is equal to the key, return node
        if (temp->data == key) {
            return temp;
        } 
        //if node data greater than key, iterate to the right
        else if (key > temp->data) {
            temp = temp->right;
        } 
        //if node data less than the key, iterate to the left
        else if (key < temp->data) {
            temp = temp->left;
        }
    }

    //node data was NULL, and thus not found
    return NULL;
}

//delete key into tree
node* tree::delet(int key) {

    node* curr = root;
    node* prev = NULL;

    //check if key is in BST
    while (curr != NULL && curr->data != key) {
        prev = curr;
        if (key < curr->data) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    //key not present, return NULL
    if (curr == NULL) {
        return NULL;
    }

    //if node to be deleted has no children
    if (curr->left == NULL && curr->right == NULL) {
        //new ptr will replace node to be deleted
        node* temp = NULL;

        //if node to be deleted is the root
        if (prev == NULL)
            return root = temp;
        
        //if node to be deleted is
        //the prev left or right child
        if (curr == prev->left) {
            prev->left = temp;
        } else {
            prev->right = temp;
        }

        free(curr);
        return root;
    }

    //if node to be deleted has no more than
    //one child
    if (curr->left == NULL || curr->right == NULL) {
        //new ptr to replace node to be deleted
        node* temp = NULL;

        //if left child is NULL
        if (curr->left == NULL) {
            temp = curr->right;
        } else {
            temp = curr->left;
        }

        //if node to be deleted is the root
        if (prev == NULL)
            return root = temp;
        
        //if node to be deleted is
        //the prev left or right child
        if (curr == prev->left) {
            prev->left = temp;
        } else {
            prev->right = temp;
        }

        free(curr);
        return root;
    } 

    //node to be deleted has two children
    else {
        node* p = NULL;
        node* temp;

        //compute successor by findin min element of right subtree
        temp = curr->right;
        while (temp->left != NULL) {
            p = temp;
            temp = temp->left;
        }

        //check if parent of successor is root
        //if it isnt, make left child of parent
        //equal to successor of right child
        if (p != NULL) {
            p->left = temp->right;
        } else {
            curr->right = temp->right;
        }

        curr->data = temp->data;
        
        free(temp);
        return root;
    }

}

class stack {
    private:
        int size;
        int top;
        node** array;
    public:
        stack(int);
        bool isFull();
        bool isEmpty();
        void push(node* node);
        node* pop();
        node* peek();
};

stack ::stack(int size) {
    this->size = size;
    array = new node*[size];
    top = -1;
}

bool stack ::isFull() {
    return top - 1 == size;
}

bool stack ::isEmpty() {
    return top == -1;
}

void stack::push(node* node) {
    if (isFull()) {
        return;
    }
    array[++top] = node;
}

node* stack::pop() {
    if (isEmpty()) {
        return NULL;
    }
    return array[top--];
}

node* stack::peek() {
    if (isEmpty()) {
        return NULL;
    }
    return array[top];
}

void tree::postOrderEnum(int size) {
    //create stack and temp node for tree traversal
    stack sk(size);
    node* temp = root;
    while (true) {
        //while temp is not null
        while (temp != NULL) {
            //push temp's right child and temp to stack
            if (temp->right != NULL) {
                sk.push(temp->right);
            }
            sk.push(temp);
            //set temp to temp's left child
            temp = temp->left;
        }

        //if stack is empty, return
        if (sk.isEmpty()) {
            return;
        }
        //pop an item from the stack and set it to temp
        temp = sk.pop();

        //if the popped item has a right child and the right
        //child is at the top of the stack
        if(temp->right != NULL && sk.peek() == temp->right) {
            //pop right child, push temp back and set temp to null
            sk.pop();
            sk.push(temp);
            temp = temp->right;
        } else {
            //other wise, print temp's data and set temp to null
            cout << temp->data << ' ';
            temp = NULL;
        }
    }
}

int main() {

    //input bst elements
    vector<int> sequence;
    int input;

    while (cin >> input) {
        sequence.push_back(input);
    }
    cin.clear();
    cin.ignore(1, 's');

    //input task number
    int task;
    cin >> task;

    int key;
    cin >> key;

    //initialize tree
    tree tree(sequence[0]);
    for (int i = 1; i < sequence.size(); i++) {
        tree.insert(sequence[i]);
    }

    switch(task) {
        //search for a key
        case 1: {

            //if the search failed, print -1
            if (tree.search(key) == NULL) {
                cout << -1 << endl;
                break;
            }

            //else, print the list
            tree.postOrderEnum(sequence.size());
            break;
        }

        //insert a key
        case 2: {
            //if insertion failed, output -1
            if (tree.insert(key) == NULL) {
                cout << -1 << endl;
                break;
            } else {
                tree.postOrderEnum(sequence.size());
                break;
            }

        }

        //delete a key
        case 3: {

            node* temp = tree.delet(key);
            if (temp == NULL) {
                cout << -1 << endl;
                break;
            }

            tree.postOrderEnum(sequence.size());
            break;
        }
    }


    return 0;
}