#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits>
#include <math.h>
using namespace std;
// Structure representing a pair of countries
struct Countary
{
string fromCountry;
string toCountry;
};
// Abstract class representing a product
class Product
{
public:
Product(const string &name, double price, const Countary &countries) : name(name), price(price), countries(countries)
{
correctPrice();
}
virtual ~Product() {}
virtual double calculateTax() const = 0;
virtual void display() const
{
cout << "Product: " << name << ", Price: $" << price << ", From: " << countries.fromCountry << ", To: " << countries.toCountry;
}
virtual void AddToFile(ofstream &file) const
{
file << name << " " << price << " " << countries.fromCountry << " " << countries.toCountry;
}
// handling the error here
void correctPrice() const
{
if (price < 0)
{
throw invalid_argument("Price cannot be negative.");
}
}
public:
string name;
double price;
Countary countries;
};
int count1 = 0;
int count2 = 0;
// Derived class for imported products
class ImportedProduct : public Product
{
public:
ImportedProduct(const string &name, double price, double importTaxRate, const Countary &countries) : Product(name, price, countries)
{
this->importTaxRate = importTaxRate;
correctPrice();
}
double calculateTax() const override
{
return price * importTaxRate;
}
void display() const override
{
Product::display();
cout << ", Import Tax: $" << calculateTax() << endl;
}
void AddToFile(ofstream &file) const override
{
count1++;
file << "PRODUCT PRICE FROM TO TAX FINAL PRIZE" << endl;
file << count1 << ")";
Product::AddToFile(file);
file << " " << importTaxRate;
file << " " << importTaxRate * price + price;
}
private:
double importTaxRate;
};
// Derived class for exported products
class ExportedProduct : public Product
{
public:
ExportedProduct(const string &name, double price, double exportTaxRate, const Countary &countries) : Product(name, price, countries)
{
this->exportTaxRate = exportTaxRate;
correctPrice();
}
double calculateTax() const override
{
// Exported products have no import tax
return price * exportTaxRate;
}
void display() const override
{
Product::display();
cout << ", Export Tax: $" << calculateTax() << endl;
}
void AddToFile(ofstream &file) const override
{
count2++;
file << "PRODUCT PRICE FROM TO TAX FINAL PRIZE" << endl;
file << count2 << ")";
Product::AddToFile(file);
file << " " << exportTaxRate;
file << " " << exportTaxRate * price + price;
}
private:
double exportTaxRate;
};
// User class for authentication
class User
{
public:
static bool authenticate(const string &username, const string &password)
{
if (username != "abhinav")
{
return false;
}
if (password != "22103003")
{
return false;
}
return !username.empty() && !password.empty();
}
};
// Template class for handling a list of products
template <class T>
class ProductList
{
public:
void addProduct(const T &product)
{
v.push_back(product);
}
void displayAll() const
{
for (const auto &product : v)
{
product.display();
cout << endl;
}
}
void AddToFile(const string &filename) const
{
ofstream file(filename);
if (file.is_open())
{
for (const auto &product : v)
{
product.AddToFile(file);
file << endl;
}
file.close();
cout << "Data saved to file: " << filename << endl;
}
else
{
cerr << "Unable to open file: " << filename << endl;
}
}
bool modifyProduct(const string &productName, double newPrice)
{
for (auto &product : v)
{
if (product.name == productName)
{
product.price = newPrice;
return true;
}
}
return false;
}
double calculateTotalValue() const
{
double totalValue = 0.0;
for (const auto &product : v)
{
totalValue += product.price;
}
return totalValue;
}
double calculateAveragePrice() const
{
if (v.empty())
{
return 0.0;
}
double totalPrices = 0.0;
for (const auto &product : v)
{
totalPrices += product.price;
}
return totalPrices / v.size();
}
private:
vector<T> v;
};
int main()
{
int x;
string name;
double price;
double tax;
string fromCountry;
string toCountry;
cout << "HELLO USER :)" << endl;
cout << "Enter correct detail to continue" << endl
<< endl;
cout << "Enter your username: ";
string username;
cin >> username;
cout << "Enter your password: ";
string password;
cin >> password;
if (!User::authenticate(username, password))
{
cerr << "Authentication failed. Exiting program." << endl;
return 1;
}
while (1)
{
cout << "\nYOU WANT TO ADD EXPORT ITEM OR IMPORT ITEM" << endl;
cout << "1 FOR IMPORT and 2 FOR EXPORT\n";
cout << "3 FOR MODIFY PRODUCT, 4 FOR DISPLAY PRODUCTS, 5 FOR SAVE TO FILE, 6 FOR EXIT\n";
cout << "7 FOR CALCULATE STATISTICS\n";
cin >> x;
try
{
if (x == 1)
{
ProductList<ImportedProduct> importedProducts;
char ch;
ch = 'Y';
while (1)
{
cout << "Enter the name of product: ";
cin >> name;
cout << "Enter the price: ";
cin >> price;
cout << "Enter the import duty: ";
cin >> tax;
cout << "Enter the country from which it is imported: ";
cin >> fromCountry;
cout << "Enter the country to which it is imported: ";
cin >> toCountry;
Countary countries = {fromCountry, toCountry};
importedProducts.addProduct(ImportedProduct(name, price, tax, countries));
cout << "ADD MORE ??(Y OR N)";
cin >> ch;
if (ch == 'N')
{
break;
}
}
cout << "Imported Products:\n";
importedProducts.displayAll();
importedProducts.AddToFile("imported_products.txt");
}
else if (x == 2)
{
ProductList<ExportedProduct> exportedProducts;
char ch;
ch = 'Y';
while (1)
{
cout << "Enter the name of product: ";
cin >> name;
cout << "Enter the price: ";
cin >> price;
cout << "Enter the export duty: ";
cin >> tax;
cout << "Enter the country from which it is exported: ";
cin >> fromCountry;
cout << "Enter the country to which it is exported: ";
cin >> toCountry;
Countary countries = {fromCountry, toCountry};
exportedProducts.addProduct(ExportedProduct(name, price, tax, countries));
cout << "ADD MORE ??(Y OR N)";
cin >> ch;
if (ch == 'N')
{
break;
}
}
cout << "\nExported Products:\n";
exportedProducts.displayAll();
exportedProducts.AddToFile("exported_products.txt");
}
else if (x == 3)
{
cout << "Enter the name of the product to modify: ";
cin >> name;
cout << "Enter the new price: ";
cin >> price;
ProductList<ImportedProduct> importedProducts;
if (importedProducts.modifyProduct(name, price))
{
cout << "Product modified successfully.\n";
importedProducts.displayAll();
}
else
{
cerr << "Product not found.\n";
}
}
else if (x == 4)
{
ProductList<ImportedProduct> importedProducts;
cout << "Imported Products:\n";
importedProducts.displayAll();
ProductList<ExportedProduct> exportedProducts;
cout << "Exported Products:\n";
exportedProducts.displayAll();
}
else if (x == 5)
{
ProductList<ImportedProduct> importedProducts;
importedProducts.AddToFile("imported_products.txt");
ProductList<ExportedProduct> exportedProducts;
exportedProducts.AddToFile("exported_products.txt");
}
else if (x == 6)
{
cout << "Exiting program.\n";
break;
}
else if (x == 7)
{
ProductList<ImportedProduct> importedProducts;
ProductList<ExportedProduct> exportedProducts;
cout << "Statistics:\n";
cout << "Total value of imported products: $" << importedProducts.calculateTotalValue() << endl;
cout << "Average price of imported products: $" << importedProducts.calculateAveragePrice() << endl;
cout << "Total value of exported products: $" << exportedProducts.calculateTotalValue() << endl;
cout << "Average price of exported products: $" << exportedProducts.calculateAveragePrice() << endl;
}
else
{
cerr << "Invalid option. Please enter a valid option.\n";
}
}
catch (const exception &e)
{
cerr << "Error: " << endl;
}
cout << "\nWould you like to perform another operation? (1 for Yes, 0 for No): ";
cin >> x;
if (x == 0)
{
break;
}
}
return 0;
}
