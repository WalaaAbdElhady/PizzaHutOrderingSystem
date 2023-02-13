#include "AVLTree.h"

int AVLTree::isEmpty(servedCustomers* root)
{
    return root == NULL;
}

int AVLTree::height(servedCustomers* root)
{
    if (root == NULL) {
        return 0;
    }

    return max(height(root->left), height(root->right)) + 1;
}

int AVLTree::balanceFactor(servedCustomers* root)
{
    if (root == NULL)
    {
        return 0;
    }

    return height(root->left) - height(root->right);
}

servedCustomers* AVLTree::search(servedCustomers* root, string keyName)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->name == keyName)
    {
        return root;
    }
    else if (root->name < keyName)
    {
        return search(root->right, keyName);
    }
    else if (root->name > keyName)
    {
        return search(root->left, keyName);
    }

    return root;
}

servedCustomers* AVLTree::maxservedCustomer(servedCustomers* root)
{
    servedCustomers* p = root;

    servedCustomers* temp = NULL;

    while (p != NULL)
    {
        temp = p;
        p = p->right;
    }

    return temp;
}

servedCustomers* AVLTree::LLRotation(servedCustomers* root)
{
    // saving the new root  
    servedCustomers* y = root->left;

    // saving the lost element in case of rotation
    servedCustomers* temp = y->right;

    // Performing rotation
    y->right = root;
    root->left = temp;

    // updating the root
    root = y;
    // returning the root
    return y;
}

servedCustomers* AVLTree::RRRotation(servedCustomers* root)
{
    // saving the new root  
    servedCustomers* y = root->right;

    // saving the lost element in case of rotation
    servedCustomers* temp = y->left;

    // Performing rotation
    y->left = root;
    root->right = temp;

    // updating the root
    root = y;

    // returning the root
    return y;
}

servedCustomers* AVLTree::LRRotation(servedCustomers* root)
{
    root->left = RRRotation(root->left);
    return LLRotation(root);
}

servedCustomers* AVLTree::RLRotation(servedCustomers* root)
{
    root->right = LLRotation(root->right);
    return RRRotation(root);
}

servedCustomers* AVLTree::insertion(int age, string name, int quantity, string pizzaName, double bill, servedCustomers* root)
{
    servedCustomers* newNode = new servedCustomers(age, name, quantity, pizzaName, bill);

    if (root == NULL)
    {
        root = newNode;
    }
    // sort them by name
    else if (root->name > newNode->name)
    {
        root->left = insertion(age, name, quantity, pizzaName, bill, root->left);
    }
    else if (root->name < newNode->name)
    {
        root->right = insertion(age, name, quantity, pizzaName, bill, root->right);
    }

    else
    {
        cout << "No duplicates Values are Allowed \n";
        return root;
    }

    int bf = balanceFactor(root);

    if (bf == 2)
    {
        // LL
        if (root->left->name > newNode->name)
        {
            return LLRotation(root);
        }

        // LR
        if (root->left->name < newNode->name)
        {
            return LRRotation(root);
        }
    }
    else if (bf == -2)
    {
        // RR
        if (root->right->name < newNode->name)
        {
            return RRRotation(root);
        }

        // RL
        if (root->right->name > newNode->name)
        {
            return RLRotation(root);
        }
    }

    return root; // in case there is no need of rotation
}

servedCustomers* AVLTree::deleteNode(servedCustomers* root, string key)
{
    if (root == NULL) {
        return root;
    }
    else if (key < root->name) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->name) {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        // Case 1:  No child or one child
        if ((root->left == NULL) || (root->right == NULL))
        {
            servedCustomers* temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else {
                *root = *temp;
            }
            delete (temp);
        }
        // case 3: 2 children
        else
        {
            servedCustomers* temp = maxservedCustomer(root->right);
            root->name = temp->name;
            root->right = deleteNode(root->right, temp->name);
        }
    }

    if (root == NULL)
        return root;

    // getting the balance factor
    int balance = balanceFactor(root);
    
    // LL
    if (balance > 1 && key < root->left->name)
    {
        return LLRotation(root);
    }
    // LR
    if (balance > 1 && key > root->left->name)
    {
        root->left = LLRotation(root->left);
        return LRRotation(root);
    }
    // RR
    if (balance < -1 && key > root->right->name)
    {
        return RRRotation(root);
    }

    // RL
    if (balance < -1 && key < root->right->name)
    {
        return RLRotation(root);
    }

    return root;
}


