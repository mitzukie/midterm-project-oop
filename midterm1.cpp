#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

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
        void display(){
            cout << "Product ID: "<<getProductID()<<endl;
            cout << "Item Name: "<<getName()<<endl;
            cout << "Quantity: "<<getQuantity()<<endl;
            cout << "Price: $"<<getPrice()<<endl;
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
     
    //Remove Item    
};

    void displayMenu(){
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

int main(){

    vector<Item> items;


    int choice;
    int productID, quantity;
    string name;
    double price;

    int condition = 0;

    while(condition == 0){
        displayMenu();
        cin>>choice;

        switch(choice){
            case 1:{
                cin.ignore();
                cout<<"Enter Item Name: ";
                getline(cin, name);
                cout<<"Enter Item Quantity: ";
                cin>>quantity;
                cin.ignore();
                cout<<"Enter Item Price:";
                cin>>price;
                cin.ignore();

                productID = items.size() + 1;

                Item newItem; 
                newItem.addItem(name,quantity,price,productID);

                items.push_back(newItem);

                cout<<"Item added successfully with Product ID: "<<productID<<endl;
            break;
            }
            case 2:{
                cout<<"Input Item ID: ";
                cin>>productID;
                cin.ignore(); // Ignore leftover newline character
                
                //check if id exists
                bool found = false;

                for(size_t i = 0; i < items.size(); i++){
                    if(items[i].getProductID() == productID){
                        found = true;

                        items[i].display();

                        cin.ignore(); // Ignore leftover newline character
                        cout<<"Enter New Item Name: ";
                        getline(cin, name);
                        cout<<"Enter New Item Quantity: ";
                        cin>>quantity;
                        cout<<"Enter New Item Price: $";
                        cin>>price;

                        items[i].update(name,quantity,price);

                        cout<<"Item details updated successfully!"<<endl;

                        break;
                    }

                }

                if (!found){
                    cout<<"Product Id "<<productID <<" not found."<<endl;
                }

                break;
            }
            case 3:{
                cout<<"Input Product ID to remove: ";
                cin>>productID;

                bool found = false;

                for(size_t i = 0; i < items.size(); i++){
                    if(items[i].getProductID() == productID){
                        found = true;

                        items.erase(items.begin() + i);
                        cout<<"Item with Product ID" <<productID<<" removed successfully."<<endl;
                        break;
                    }
                }

                if (!found){
                    cout<<"Product ID "<<productID<<" does not exist."<<endl;
                }
                break;
            }
            case 4:{
                if(items.empty()){
                    cout<<"No items are available to display."<<endl;
                }

                else{
                    cout<<"Displaying all items:"<<endl;
                        for(size_t i = 0; i < items.size(); i++){
                            cout<<"Item "<<i+1<<":"<<endl;
                            items[i].display();
                            cout<<endl;
                        }
                }
                break;
            }
            case 5:{
                cout<<"Enter Product ID to search: ";
                cin>>productID;

                bool found = false;

                for(size_t i = 0; i < items.size(); i++){
                    if(items[i].getProductID() == productID){
                        found = true;

                        cout<<"Item found: "<<endl;
                        items[i].display();
                        
                        break;
                    }
                }

                if(!found){
                    cout<<"Product ID "<<productID<<" does not exist."<<endl;
                }

                break;
            }
            case 6: {
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
                for (size_t i = 0; i < items.size(); i++) {
                    cout << "Item " << i + 1 << ":" << endl;
                    items[i].display();
                    cout << endl;
                }

                break;
            }
            case 7:{
                cout<<"Low Stock Items: "<<endl;

                bool found = false;

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
        }
    }
}