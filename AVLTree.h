#include <string>
#include <iostream>
using namespace std;
struct servedCustomers
{
    int age;
    string name;
    int quantity;
    string pizzaName;
    double bill;
    servedCustomers* left;
    servedCustomers* right;

    servedCustomers(int age, string name, int quantity, string pizzaName, double bill)
    {

        this->age = age;
        this->name = name;
        this->quantity = quantity;
        this->pizzaName = pizzaName;
        this->bill = bill;
        this->left = NULL;
        this->right = NULL;
    }
};

class AVLTree
{
private:
    servedCustomers* root = NULL;
public:
    AVLTree() {

    }

    int isEmpty(servedCustomers* root);
   
    int height(servedCustomers* root);

    int balanceFactor(servedCustomers* root);
   
    servedCustomers* search(servedCustomers* root, string keyName);

    servedCustomers* maxservedCustomer(servedCustomers* root);

    servedCustomers* LLRotation(servedCustomers* root);

    servedCustomers* RRRotation(servedCustomers* root);

    servedCustomers* LRRotation(servedCustomers* root);

    servedCustomers* RLRotation(servedCustomers* root);

    servedCustomers* insertion(int age, string name, int quantity, string pizzaName, double bill, servedCustomers* root);

    servedCustomers* deleteNode(servedCustomers* root, string key);
 

};

