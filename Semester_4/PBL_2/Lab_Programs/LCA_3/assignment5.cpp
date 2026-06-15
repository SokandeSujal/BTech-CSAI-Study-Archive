#include <iostream>
#include <string>

using namespace std;

class Node
{
public:
    string key, meaning;
    Node *left, *right;
    int height;

    Node(string k, string m)
    {
        key = k;
        meaning = m;
        left = right = NULL;
        height = 1;
    }
};

class AVL
{
    Node *root;

public:
    AVL()
    {
        root = NULL;
    }

    int height(Node *n)
    {
        if (n == NULL)
            return 0;
        return n->height;
    }

    int getBalance(Node *n)
    {
        if (n == NULL)
            return 0;
        return height(n->left) - height(n->right);
    }

    Node *rotateLeft(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node *rotateRight(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node *insert(Node *node, string key, string meaning)
    {
        if (node == NULL)
        {
            return new Node(key, meaning);
        }

        if (key < node->key)
        {
            node->left = insert(node->left, key, meaning);
        }
        else if (key > node->key)
        {
            node->right = insert(node->right, key, meaning);
        }
        else
        {
            cout << "Keyword already exists!\n";
            return node;
        }

        node->height = max(height(node->left), height(node->right)) + 1;
        int balance = getBalance(node);

        // LL
        if (balance > 1 && key < node->left->key)
        {
            return rotateRight(node);
        }

        // RR
        if (balance < -1 && key > node->right->key)
        {
            return rotateLeft(node);
        }

        // LR
        if (balance > 1 && key > node->left->key)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // RL
        if (balance < -1 && key < node->right->key)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void insertKey(string key, string meaning)
    {
        root = insert(root, key, meaning);
    }

    void update(string key, string newMeaning)
    {
        Node *temp = root;
        while (temp != NULL)
        {
            if (key == temp->key)
            {
                temp->meaning = newMeaning;
                cout << "Updated successfully!\n";
                return;
            }
            else if (key < temp->key)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }

        cout << "Keyword Not Found!\n";
    }

    void inorder(Node *root)
    {
        if (root != NULL)
        {
            inorder(root->left);
            cout << root->key << " : " << root->meaning << endl;
            inorder(root->right);
        }
    }

    void display()
    {
        cout << "\nDictionary: \n";
        inorder(root);
    }

    void search(string key)
    {
        Node *temp = root;
        int comparisons = 0;

        while (temp != NULL)
        {
            comparisons++;

            if (key == temp->key)
            {
                cout << "Found! Meaning: " << temp->meaning << endl;
                cout << "Comparisons: " << comparisons << endl;
                return;
            }
            else if (key < temp->key)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }
        cout << "Keyword not found!\n";
        cout << "Comparisons: " << comparisons << endl;
    }
};

int main()
{

    AVL tree;
    int choice;
    string key, meaning;

    do
    {
        cout << "\n1.Insert\n2.Update\n3.Display\n4.Search\n5.Exit\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Keyword: ";
            cin >> key;

            cin.ignore();
            cout << "Enter meaning: ";
            getline(cin, meaning);
            tree.insertKey(key, meaning);
            break;

        case 2:
            cout << "Enter keyword to update: ";
            cin >> key;

            cin.ignore();
            cout << "Enter new meaning: ";
            getline(cin, meaning);
            tree.update(key, meaning);
            break;

        case 3:
            tree.display();
            break;

        case 4:
            cout << "Enter keyword to search: ";
            cin >> key;
            tree.search(key);
            break;
        }
    } while (choice != 5);

    return 0;
}