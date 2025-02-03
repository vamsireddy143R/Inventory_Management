#include <iostream>
#include <string>
#include <map>
#include <limits>
using namespace std;
struct Product {
string name;
int quantity;
Product* next;
Product* prev;
};
class InventoryManagement {
private:
Product* head;
Product* tail;
int productCount;
multimap<string, Product*> productBrandMap;
public:
InventoryManagement() {
head = nullptr;
tail = nullptr;
productCount = 0;
}
string categorizeProductByBrand(const string& productName) {
string brand = productName.substr(0, productName.find(" "));
return brand;
}
void addProduct(const string& name, const string& brand, int quantity) {
for (Product* current = head; current != nullptr; current = current->next) {
if (current->name == name) {
cout << "Product already present.Update Product instead" << endl;
return;
}
}

13

Product* newProduct = new Product{name, quantity, nullptr, nullptr};
if (!head) {
head = tail = newProduct;
} else {
newProduct->next = head;
head->prev = newProduct;
head = newProduct;
}
productCount++;
string categorizedBrand = categorizeProductByBrand(brand);
productBrandMap.insert(make_pair(categorizedBrand, newProduct));
}
void updateProduct(const string& name, int quantity) {
Product* current = head;
while (current) {
if (current->name == name) {
current->quantity = quantity;
return;
}
current = current->next;
}
cout << "Product not found. Adding it as a new product." << endl;
string brand;
cout << "Enter Brand: ";
cin.ignore(numeric_limits<streamsize>::max(), '\n');
getline(cin, brand);
addProduct(name, brand, quantity);
}
void removeProduct(const string& name) {
Product* current = head;
while (current) {
if (current->name == name) {
string brand = categorizeProductByBrand(current->name);
auto range = productBrandMap.equal_range(brand);
for (auto it = range.first; it != range.second; ++it) {
if (it->second == current) {
productBrandMap.erase(it);
break;
}

14

}
if (current == head && current == tail) {
head = tail = nullptr;
} else if (current == head) {
head = head->next;
if (head) {
head->prev = nullptr;
}
} else if (current == tail) {
tail = tail->prev;
if (tail) {
tail->next = nullptr;
}
} else {
current->prev->next = current->next;
current->next->prev = current->prev;
}
delete current;
productCount--;
return;
}
current = current->next;
}
cout << "Product not found in the inventory." << endl;
}
void displayAllInventory() {
if (productCount == 0) {
cout << "No products found." << endl;
} else {
cout << "Displaying All Inventory:\n";
for (const auto& pair : productBrandMap) {
string brand = pair.first;
Product* product = pair.second;
cout << "Brand: " << brand << ", Product Name: " << product->name << ", Quantity: " << product-
>quantity << endl;
}
}
}
void displayInventoryByBrand(const string& brand) {
cout << "Displaying Inventory for Brand: " << brand << "\n";
auto range = productBrandMap.equal_range(brand);
for (auto it = range.first; it != range.second; ++it) {
Product* product = it->second;

15

cout << "Brand: " << brand << ", Product Name: " << product->name << ", Quantity: " << product-
>quantity << endl;
}
}
int getCount() {
return productCount;
}
};
int main() {
InventoryManagement inventory;
int choice;
string name;
string brand;
int quantity;
string displayBrand;
cout << "1. Add Product\n";
cout << "2. Update Product\n";
cout << "3. Remove Product\n";
cout << "4. Display Inventory\n";
cout << "5. Count Inventory\n";
cout << "6. Exit\n";
do {
cout << "Enter your choice: ";
cin >> choice;
switch (choice) {
case 1:
cout << "Enter Product Name: ";
cin.ignore(numeric_limits<streamsize>::max(), '\n');
getline(cin, name);
cout << "Enter Brand: ";
getline(cin, brand);
cout << "Enter Quantity: ";
cin >> quantity;
inventory.addProduct(name, brand, quantity);
break;
case 2:
cout << "Enter Product Name: ";
cin.ignore(numeric_limits<streamsize>::max(), '\n');
getline(cin, name);
cout << "Enter New Quantity: ";
cin >> quantity;
inventory.updateProduct(name, quantity);

16

break;
case 3:
cout << "Enter Product Name to Remove: ";
cin.ignore(numeric_limits<streamsize>::max(), '\n');
getline(cin, name);
inventory.removeProduct(name);
break;
case 4:
if (inventory.getCount() == 0) {
cout << "No products found." << endl;
} else {
cout << "1. Display All Inventory\n";
cout << "2. Display Inventory by Brand\n";
cout << "Enter your choice: ";
cin >> choice;
switch (choice) {
case 1:
inventory.displayAllInventory();
break;
case 2:
cout << "Enter Brand Name: ";
cin.ignore(numeric_limits<streamsize>::max(), '\n');
getline(cin, displayBrand);
inventory.displayInventoryByBrand(displayBrand);
break;
default:
cout << "Invalid choice. Please try again.\n";
}
}
break;
case 5:
cout << "Total number of products in the inventory: " << inventory.getCount() << endl;
break;
case 6:
cout << "Exiting...\n";
break;
default:
cout << "Invalid choice. Please try again.\n";
}
cout << "------------------------" << endl;
} while (choice != 6);
return 0;
}