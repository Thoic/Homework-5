#include <iostream>
#include <vector>

using namespace std;

class node {

    public:
        int data;
        node *left, *right;
        node(int);
};

node ::node(int data) {
    this->data = data;
    left = right = NULL;
}

class tree {

    node* root;
    public:
        void print(node* node);
        int insert(int value);
        int search(int key);
        node* getRoot();
        tree(int);
};

tree ::tree(int value) {
    root = new node(value);
}

node* tree::getRoot() {
    return root;
}

//util function prints tree inorder
void tree::print(node* node) {
    if (node != NULL) {
        print(node->left);
        cout << node->data << ' ';
        print(node->right);
    }
}

int tree::insert(int value) {

    node* temp = root;
    while (temp != NULL) {
        //if data is already in the tree, insertion failure
        if (temp->data == value) {
            return -1;
        }
        else if (value > temp->data) {
            //if the target child is null, set it to value
            if (temp->right == NULL) {
                temp->right = new node(value);
                return 0;
            }
            //else, iterate to the child
            temp = temp->right;
            continue;
        }
        else if (value < temp->data) {
            //if the target child is null, set it to the value
            if (temp->left == NULL) {
                temp->left = new node(value);
                return 0;
            }
            //else, iterate to the child
            temp = temp->left;
            continue;
        }
    }

    //failure to insert node
    return -1;
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

    switch(task) {
        case 1: {
            tree tree(sequence[0]);
            for (int i = 1; i < sequence.size(); i++) {
                tree.insert(sequence[i]);
            }

            tree.print(tree.getRoot());
        }
        case 2: {

        }
        case 3: {

        }
    }


    return 0;
}