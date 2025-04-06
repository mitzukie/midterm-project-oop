#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <iomanip>

using namespace std;

int nextProductID = 1; // Global counter for unique product IDs

class Item{
    private:
        int productID;
        string name;
        int quantity;
        double price;

    public:
    //Constructor
        Item() : productID(0), name(""), quantity(0), price(0.0){}

    //Setters
    
        void setProuductID(int productID){
            this->productID = productID;
        }

        void setName(string name){
            this->name = name;
        }

        void setQuantity(int quantity){
            this->quantity = quantity;
        }

        void setPrice(double price){
            this->price = price;
        }

    //Getters
        int getProductID() const {
            return productID;
        }

        string getName() const {
            return name;
        }

        int getQuantity() const {
            return quantity;
        }

        double getPrice() const {
            return price;
        }

    //Display
        void display() const {
            cout << left << setw(12) << productID
                 << setw(20) << name
                 << setw(12) << quantity
                 << fixed << setprecision(2) << setw(12) << price
                 << endl;
        }   
        
    //Add Item
        void addItem(string name, int quantity, double price,int productID){
            setName(name);
            setQuantity(quantity);
            setPrice(price);
            setProuductID(productID);
        }

    //Update Item
        void update(string name, int quantity, double price){
            setName(name);
            setQuantity(quantity);
            setPrice(price);
        }
        
};
    //Validate Input for Integer
        int validatePositiveInteger(const string& prompt) {
            int value;
            while (true) {
                cout << prompt;
                cin >> value;

                // Check if input is valid and positive
                if (cin.fail() || value <= 0) {
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                    cout << "Invalid input. Please input a positive integer." << endl;
                } else {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                    return value; // Return valid input
                }
            }
        }

    //Validate Input for Double   
        double validatePositiveDouble(const string& prompt) {
            double value;
            while (true) {
                cout << prompt;
                cin >> value;

                // Check if input is valid and positive
                if (cin.fail() || value <= 0.0) {
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                    cout << "Invalid input. Please enter a positive number." << endl;
                } else {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                    return value; // Return valid input
                }
            }
        }

    //Menu
        void displayMenu(){
            cout<<endl;
            cout<<"Menu"<<endl;
            cout<<"1 - Add Item"<<endl;
            cout<<"2 - Update Item"<<endl;
            cout<<"3 - Remove Item"<<endl;
            cout<<"4 - Display All Items"<<endl;
            cout<<"5 - Search Item"<<endl;
            cout<<"6 - Sort Items"<<endl;
            cout<<"7 - Display Low Stock Items"<<endl;
            cout<<"8 - Exit"<<endl;
        }

    //Display Table Header
        void displayTableHeader() {
            cout << left << setw(12) << "Product ID"
                 << setw(20) << "Item Name"
                 << setw(12) << "Quantity"
                 << setw(12) << "Price"
                 << endl;
            cout << string(56, '-') << endl; // Print a separator line
        }

    
int main(){

    vector<Item> items;


    int choice;
    int productID, quantity;
    string name;
    double price;

    int condition = 0;

    while(condition == 0){
        displayMenu();
        choice = validatePositiveInteger("Enter Menu Choice: ");

        switch(choice){
            case 1: {
                cin.ignore();
                cout << "Enter Item Name: ";
                getline(cin, name);

                // Validate quantity and price
                quantity = validatePositiveInteger("Enter Item Quantity: ");
                price = validatePositiveDouble("Enter Item Price: ");

                productID = nextProductID++;

                Item newItem;
                newItem.addItem(name, quantity, price, productID);

                items.push_back(newItem);

                cout << "Item added successfully with Product ID: " << productID << endl;
                break;
            }
            case 2: {
                if (items.empty()) {
                    cout << "There are no items yet." << endl;
                }

                cout << "Input Item ID: ";
                cin >> productID;
                cin.ignore(); 

                //check if id exists
                bool found = false;

                for (size_t i = 0; i < items.size(); i++) {
                    if (items[i].getProductID() == productID) {
                        found = true;

                        items[i].display();

                        cin.ignore();
                        cout << "Enter New Item Name: ";
                        getline(cin, name);

                        // Validate quantity and price
                        quantity = validatePositiveInteger("Enter New Item Quantity: ");
                        price = validatePositiveDouble("Enter New Item Price: ");

                        items[i].update(name, quantity, price);

                        cout << "Item details updated successfully!" << endl;

                        break;
                    }
                }

                if (!found) {
                    cout << "Item not found!" << endl;
                }

                break;
            }
            case 3:{
                if (items.empty()) {
                    cout << "There are no items yet." << endl;
                }

                cout<<"Input Product ID to remove: ";
                cin>>productID;

                bool found = false;

                for(size_t i = 0; i < items.size(); i++){
                    if(items[i].getProductID() == productID){
                        found = true;

                        items.erase(items.begin() + i);
                        cout<<"Item "<<name<<" has been removed from the inventory."<<endl;
                        break;
                    }
                }

                if (!found){
                    cout<<"Item not found!"<<endl;
                }
                break;
            }
            case 4: {
                if (items.empty()) {
                    cout << "No items are available to display." << endl;
                } 
                else {
                    displayTableHeader(); // Print the table header
                    for (size_t i = 0; i < items.size(); i++) {
                        items[i].display(); // Print each item as a table row
                    }
                }
                break;
            }
            case 5:{
                if (items.empty()) {
                    cout << "There are no items yet." << endl;
                }

                cout<<"Enter Product ID to search: ";
                cin>>productID;

                bool found = false;

                for(size_t i = 0; i < items.size(); i++){
                    if(items[i].getProductID() == productID){
                        found = true;

                        cout<<"Item found: "<<endl;
                        displayTableHeader();
                        items[i].display();
                        
                        break;
                    }
                }

                if(!found){
                    cout<<"Item not found!"<<endl;
                }

                break;
            }
            case 6: {
                if (items.empty()) {
                    cout << "There are no items yet." << endl;
                }

                int sortChoice, orderChoice;

                // Ask for sorting criteria
                cout << "Sort by:\n";
                cout << "1 - Quantity\n";
                cout << "2 - Price\n";
                cout << "Enter your choice: ";
                cin >> sortChoice;

                // Validate sorting criteria
                if (sortChoice != 1 && sortChoice != 2) {
                    cout << "Invalid sorting criteria! Please enter 1 or 2." << endl;
                    break;
                }

                // Ask for sorting order
                cout << "Order:\n";
                cout << "1 - Ascending\n";
                cout << "2 - Descending\n";
                cout << "Enter your choice: ";
                cin >> orderChoice;

                // Validate sorting order
                if (orderChoice != 1 && orderChoice != 2) {
                    cout << "Invalid order choice! Please enter 1 or 2." << endl;
                    break;
                }

                // Perform sorting based on user input
                if (sortChoice == 1) { // Sort by Quantity
                    sort(items.begin(), items.end(), [orderChoice](const Item& a, const Item& b) {
                        return (orderChoice == 1) ? (a.getQuantity() < b.getQuantity()) : (a.getQuantity() > b.getQuantity());
                    });
                } else if (sortChoice == 2) { // Sort by Price
                    sort(items.begin(), items.end(), [orderChoice](const Item& a, const Item& b) {
                        return (orderChoice == 1) ? (a.getPrice() < b.getPrice()) : (a.getPrice() > b.getPrice());
                    });
                }

                cout << "Items sorted successfully!" << endl;

                // Display sorted items
                cout << "Sorted items:" << endl;
                displayTableHeader();
                for (size_t i = 0; i < items.size(); i++) {
                    items[i].display();
                    cout << endl;
                }

                break;
            }
            case 7:{
                if (items.empty()) {
                    cout << "There are no items yet." << endl;
                }

                cout<<"Low Stock Items: "<<endl;

                bool found = false;

                displayTableHeader();
                for(size_t i = 0; i < items.size(); i++){
                    if(items[i].getQuantity() <= 5){
                        found = true;
                        items[i].display();
                        cout<<endl;
                    }
                }

                if(!found){
                    cout<<"No low stock items found."<<endl;
                }
                break;
            }
            case 8:{
                cout<<"Exiting Program.."<<endl;
                condition = 1;
                break;
            }
            default:{
                cout<<"Invalid choice. Please select a valid option from the given menu."<<endl;
            }
        }
    }
}