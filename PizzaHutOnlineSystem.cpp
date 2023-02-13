#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "AVLTree.h"
const int OO = INT_MAX;
using namespace std;
struct Customer
{
    int age;
    string name;
    string pizzaName;
    int quantity;
    double bill;
    string address;
    double deliveryCharges;
    int distanceDelivery;
    Customer* next = NULL;

    Customer(int age, string name, int quantity, string pizzaName, double bill, string address, double deliveryCharges, int distanceDelivery)
    {
        this->age = age;
        this->name = name;
        this->pizzaName = pizzaName;
        this->quantity = quantity;
        this->bill = bill;
        this->address = address;
        this->deliveryCharges = deliveryCharges;
        this->distanceDelivery = distanceDelivery;
        next = NULL;
    }
};

struct PizzaShop
{
    string shopName;
    string* menu = NULL;
    int* price = NULL;
    string address;
    Customer* Customer = NULL;
};

PizzaShop* myPizzaShop = NULL;
Customer* newCustomer = NULL;
AVLTree servedCus;
servedCustomers* root;
double totalOrders, totalServedOrders;

void placeOrder(int age, string name, string pizzaName, int quantity, double bill, string address, int deliveryCharges, int distanceDelivery)
{
    newCustomer = new Customer(age, name, quantity, pizzaName, bill, address, deliveryCharges, distanceDelivery);

    if (myPizzaShop->Customer == NULL)
    {
        myPizzaShop->Customer = newCustomer;
    }
    else
    {
        Customer* temp = myPizzaShop->Customer;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newCustomer;
        newCustomer->next = NULL;
    }
    cout << "\nYour Order has been Placed MR/MRS " << name << " and your order is " << pizzaName << " with " << quantity << " quantity and total bill is " << bill << "\n\n";
}

void serveOrder()
{
    if (myPizzaShop->Customer == NULL)
    {
        cout << "There is No Customers to Serve\n";
    }
    else
    {
        Customer* first = myPizzaShop->Customer;

        if (first->next == NULL)
        {
            myPizzaShop->Customer = NULL;
            cout << "Customer Served : " << first->name << "\n";
            root = servedCus.insertion(first->age, first->name, first->quantity, first->pizzaName, first->bill, root);
            delete (first);
        }
        else {
            Customer* temp = first->next;
            while (temp->next != NULL) {
                first = first->next;
                temp = temp->next;
            }
            first->next = NULL;

            cout << "Customer Served : " << temp->name << "\n";
            root = servedCus.insertion(temp->age, temp->name, temp->quantity, temp->pizzaName, temp->bill, root);
            delete (temp);
        }
    }
}

void serveAllOrders()
{

    while (myPizzaShop->Customer != NULL)
    {
        serveOrder();
    }
    cout << "\n All orders served\n";
}

void displayAllOrders()
{
    if (myPizzaShop->Customer == NULL)
    {
        cout << "There is no Order for  Customer till yet\n";
    }
    else
    {
        Customer* temp = myPizzaShop->Customer;
        while (temp != NULL)
        {

            cout << "-----------------------------------------------------\n";
            cout << "Customer : " << temp->name << endl;
            cout << "Age : " << temp->age << endl;
            cout << "Pizza Name : " << temp->pizzaName << endl;
            cout << "Quantity : " << temp->quantity << endl;
            cout << "Bill : " << temp->bill << " $/_" << endl;
            cout << "-----------------------------------------------------\n";

            temp = temp->next;
        }
    }
}

void totalbillofPendingOrders()
{
    Customer* temp = myPizzaShop->Customer;
    while (temp != NULL)
    {
        totalOrders += temp->bill;
        temp = temp->next;
    }

    cout << "The total bill of pending orders are : " << totalOrders << " $/_\n";
}

double totalEarnings(servedCustomers* root) {

    if (root != NULL) {
        totalEarnings(root->left);
        totalServedOrders += root->bill;
        totalEarnings(root->right);
    }

    return totalServedOrders;
}

void display(servedCustomers* root)
{
    cout << "Name :" << root->name << "\n";
    cout << "Age  :" << root->age << "\n";
    cout << "Pizza :" << root->pizzaName << "\n";
    cout << "Quantity : " << root->quantity << "\n";
    cout << "Bill : " << root->bill << "\n";
}

servedCustomers* displayAllServedOrders(servedCustomers* root)
{
    if (root != NULL) {
        displayAllServedOrders(root->left);
        display(root);
        displayAllServedOrders(root->right);
    }
    return root;
}

void deleteAllServedCustomers(servedCustomers* root)
{

    while (root != NULL)
    {
        root = servedCus.deleteNode(root, root->name);
    }

    cout << "The Served Customer's List is Cleared \n";
}

string deliveryPoints[] = { "6thOctober", "Shobra", "Zamalek", "Dokki", "Giza", "Maadi" };

vector<vector<pair<int, int>>> deliveryMap = {
    // first value in the pair is vertex and second is the distance (weight) in KM
    {{1, 2}, {2, 3}, {3, 5}, {5, 4}}, //  0  6thOctober
    {{0, 2}, {5, 1}},                 //  1  Shobra
    {{0, 3}, {3, 1}},                 //  2  Zamalek
    {{0, 5}, {4, 2}, {5, 2}, {2, 1}}, //  3  Dokki
    {{3, 2}, {5, 2}},                 //  4  Giza
    {{0, 4}, {1, 1},{3,2} ,{4, 2}}    //  5  Maadi
};

vector<int> dijkstra(int sourceNode)
{
    vector<int> distance(6, OO);
    set<pair<int, int>> s;
    distance[sourceNode] = 0;
    s.insert(make_pair(0, sourceNode));

    while (!s.empty())
    {
        auto top = *(s.begin());
        int u = top.first;
        int v = top.second;

        s.erase(s.begin());

        for (auto child : deliveryMap[v])
        {
            int childVertex = child.first;
            int childWeight = child.second;

            if (u + childWeight < distance[childVertex])
            {
                distance[childVertex] = u + childWeight;
                s.insert(make_pair(distance[childVertex], childVertex));
            }
        }
    }
    return distance;
}

int main() {

    cout << "\t\t ___                             _   _         _     \n";
    cout << "\t\t(  _`\\  _                       ( ) ( )       ( )_  \n";
    cout << "\t\t| |_) )(_) ____  ____    _ _    | |_| | _   _ | ,_)  \n";
    cout << "\t\t| ,__/'| |(_  ,)(_  ,) /'_` )   |  _  |( ) ( )| |    \n";
    cout << "\t\t| |    | | /'/_  /'/_ ( (_| |   | | | || (_) || |_   \n";
    cout << "\t\t(_)    (_)(____)(____)`\\__,_)   (_) (_)`\\___/'`\\__)) \n";


    myPizzaShop = new PizzaShop;

    myPizzaShop->shopName = "Pizza Hut";

    myPizzaShop->address = "Cairo,6th Of October";

    myPizzaShop->menu = new string[11]{ "",
                                       "chickenTikka", "arabicRanch",
                                       "chickenFajita", "cheeseLover",
                                       "chickenSupreme", "allveggie",
                                       "garlicWest", "BeefBold",
                                       "phantom", "mexicanDelight" };

    myPizzaShop->price = new int[11]{ 0, 2000, 2500, 2400, 2200, 2700, 2000, 2100, 3000, 3000, 2800 };
    int option = -1, choice = -1;
    do {
        cout << "\n\t\t\t\t   " << myPizzaShop->shopName << "\n";
        cout << "\t\t\tLocated at " << myPizzaShop->address << "\n\n\n";
        cout << " 1. Admin                      2.Customer\n";
        cout << " 3. Exit\n\n";
        cout << " Enter your option: ";
        cin >> option;
        if (option == 1) {
            do
            {
                cout << " 1) Serve order\n";

                cout << " 2) Serve All Orders\n";

                cout << " 3) Display all orders\n";

                cout << " 4) Display all served Orders\n";

                cout << " 5) Search Served Orders\n";

                cout << " 6) Clear the Served Orders List\n";

                cout << " 7) Display total bill of Pending Orders\n";

                cout << " 8) Display the total Earnings of Served Orders\n";

                cout << " 0) EXIT \n";

                cout << " Enter your choice: ";

                cin >> choice;
                int age, quantity, pizzaIndex;
                double bill;
                string address;
                string name;

                switch (choice)
                {
                case 1:
                    serveOrder();
                    break;
                case 2:
                    serveAllOrders();
                    break;

                case 3:
                    displayAllOrders();
                    break;

                case 4:
                {
                    servedCustomers* display = displayAllServedOrders(root);
                    if (display == NULL) {
                        cout << "No Served Customer yet \n";
                    }

                }
                break;

                case 5:
                {
                    cout << "Enter the name of the customer you want to search: \n";
                    cin >> name;
                    servedCustomers* searchedCustomer = servedCus.search(root, name);
                    if (searchedCustomer == NULL)
                        cout << "No such Customer was Served \n";
                    else
                        display(searchedCustomer);
                }
                break;

                case 6:
                {
                    deleteAllServedCustomers(root);
                    root = NULL;
                }
                break;

                case 7:
                {
                    totalOrders = 0;
                    totalbillofPendingOrders();
                }
                break;

                case 8:
                {
                    totalServedOrders = 0;
                    double totalx = totalEarnings(root);
                    cout << "The Total Earnings are : " << totalx << "\n";
                }
                break;
                }

            } while (choice != 0);

        }
        else if (option == 2) {
            do
            {

                cout << "\nOur Menu is as follows: \n";
                cout << "***********************\n\n";
                for (int i = 1; i <= 10; i++)
                {
                    cout << i << ". " << myPizzaShop->menu[i] << " - " << myPizzaShop->price[i] << " $\n";
                }
                cout << "\nOur Services is as follows: \n";
                cout << "***********************\n\n";
                cout << "1) Place order\n";
                cout << "0) EXIT \n";

                cout << "Enter your choice: \n";

                cin >> choice;
                int age, quantity, pizzaIndex;
                double bill;
                string address;
                string name;

                switch (choice)
                {
                case 1:
                {
                    vector<int> distanceFromShop = dijkstra(0);
                    int optionDelivery = -1;
                    do
                    {
                        cout << "The delivery is available for following Areas : \n";
                        for (int i = 1; i <= 5; i++)
                        {
                            cout << i << ". " << deliveryPoints[i] << "\n";
                        }

                        cout << "Enter your option :\n";
                        cin >> optionDelivery;

                    } while (!(optionDelivery >= 0 && optionDelivery <= 5));

                    address = deliveryPoints[optionDelivery];

                    cout << "Enter the name of the customer: ";
                    cin >> name;
                    cout << "Enter the age of the customer: ";
                    cin >> age;
                    cout << "Enter the quantity of the pizza: ";
                    cin >> quantity;
                    cout << "Enter the option for the pizza: ";
                    cin >> pizzaIndex;

                    int deliveryChargesPerKM = 50;
                    int deliveryCharges = deliveryChargesPerKM * distanceFromShop[optionDelivery];
                    bill = quantity * myPizzaShop->price[pizzaIndex] + deliveryCharges;

                    int distance = distanceFromShop[optionDelivery];
                    placeOrder(age, name, myPizzaShop->menu[pizzaIndex], quantity, bill, address, distance, deliveryCharges);

                    cout << "\n                                //''---.._         \n";
                    cout << "Thank you for your order!       ||  (_)  _ '-._    \n";
                    cout << "Your Pizzas are on the way!     ||    _ (_)    '-. \n";
                    cout << "                                ||   (_)   __..-'  \n";
                    cout << "                                 \\__..--''        \n";
                }
                }

            } while (choice != 0);

            cout << "Thank you for Using our Services\n";
        }
    } while (option != 3);
    return 0;
}

