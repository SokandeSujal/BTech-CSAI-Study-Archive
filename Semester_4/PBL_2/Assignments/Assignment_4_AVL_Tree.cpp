#include <iostream>
#include <algorithm>
using namespace std;

class AVLTree {
private:
    struct Node {
        int data;
        int height;
        Node* left;
        Node* right;

        Node(int value) {
            data = value;
            height = 1;
            left = NULL;
            right = NULL;
        }
    };

    Node* root;

    int getHeight(Node* node) {
        if(node == NULL) {
            return 0;
        }
        return node->height;
    }

    int getBalance(Node* node) {
        if(node == NULL) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* t2 = x->right;

        x->right = y;
        y->left = t2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* t2 = y->left;

        y->left = x;
        x->right = t2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    Node* insertNode(Node* node, int key) {
        if(node == NULL) {
            return new Node(key);
        }

        if(key < node->data) {
            node->left = insertNode(node->left, key);
        }
        else if(key > node->data) {
            node->right = insertNode(node->right, key);
        }
        else {
            cout << "Duplicate element not allowed\n";
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        if(balance > 1 && key < node->left->data) {
            return rightRotate(node);
        }

        if(balance < -1 && key > node->right->data) {
            return leftRotate(node);
        }

        if(balance > 1 && key > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if(balance < -1 && key < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    bool searchNode(Node* node, int key) {
        if(node == NULL) {
            return false;
        }

        if(node->data == key) {
            return true;
        }

        if(key < node->data) {
            return searchNode(node->left, key);
        }

        return searchNode(node->right, key);
    }

    void inorderNode(Node* node) {
        if(node != NULL) {
            inorderNode(node->left);
            cout << node->data << " ";
            inorderNode(node->right);
        }
    }

    void preorderNode(Node* node) {
        if(node != NULL) {
            cout << node->data << " ";
            preorderNode(node->left);
            preorderNode(node->right);
        }
    }

    void postorderNode(Node* node) {
        if(node != NULL) {
            postorderNode(node->left);
            postorderNode(node->right);
            cout << node->data << " ";
        }
    }

    int countNodes(Node* node) {
        if(node == NULL) {
            return 0;
        }
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    void clearTree(Node* node) {
        if(node != NULL) {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }

public:
    AVLTree() {
        root = NULL;
    }

    ~AVLTree() {
        clearTree(root);
    }

    void insert(int key) {
        root = insertNode(root, key);
    }

    void search(int key) {
        if(searchNode(root, key)) {
            cout << key << " found in AVL tree\n";
        }
        else {
            cout << key << " not found in AVL tree\n";
        }
    }

    void inorder() {
        cout << "Inorder: ";
        inorderNode(root);
        cout << endl;
    }

    void preorder() {
        cout << "Preorder: ";
        preorderNode(root);
        cout << endl;
    }

    void postorder() {
        cout << "Postorder: ";
        postorderNode(root);
        cout << endl;
    }

    void displayAllTraversals() {
        inorder();
        preorder();
        postorder();
    }

    void showTreeInfo() {
        cout << "Total nodes: " << countNodes(root) << endl;
        cout << "Tree height: " << getHeight(root) << endl;
    }
};

int main() {
    AVLTree tree;
    int choice, value;

    do {
        cout << "\n1. Insert\n2. Search\n3. Inorder\n4. Preorder\n5. Postorder\n6. Display All Traversals\n7. Tree Info\n8. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(value);
                break;

            case 2:
                cout << "Enter value to search: ";
                cin >> value;
                tree.search(value);
                break;

            case 3:
                tree.inorder();
                break;

            case 4:
                tree.preorder();
                break;

            case 5:
                tree.postorder();
                break;

            case 6:
                tree.displayAllTraversals();
                break;

            case 7:
                tree.showTreeInfo();
                break;

            case 8:
                break;

            default:
                cout << "Invalid choice\n";
        }
    } while(choice != 8);

    return 0;
}
