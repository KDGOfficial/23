#include <iostream>
#include <fstream>
using namespace std;

struct Product
{
    char name[50];
    double price;
    int quantity;
    bool in_stock;
};

void showProduct(const Product& p)
{
    cout << "Name: " << p.name << " | Price: " << p.price << " | Quantity: " << p.quantity << " | In Stock: " << (p.in_stock ? "Yes" : "No") << endl;
}

int main()
{
    const char* PATH_TO_FILE = "products.bin";
    const int N = 3;
    Product product_list[N] = {
        {"Product1", 19.99, 10, true},
        {"Product2", 29.99, 0, false},
        {"Product3", 39.99, 5, true}
    };

    ofstream outFile(PATH_TO_FILE, ios::binary);
    if (outFile.is_open())
    {
        outFile.write(reinterpret_cast<char*>(product_list), N * sizeof(Product));
        outFile.close();
    }
    else
    {
        cerr << "Unable to open file for writing!" << endl;
        return 1;
    }

    Product new_product_list[N];
    ifstream inFile(PATH_TO_FILE, ios::binary);
    if (inFile.is_open())
    {
        inFile.read(reinterpret_cast<char*>(new_product_list), N * sizeof(Product));
        inFile.close();

        for (int i = 0; i < N; i++)
        {
            showProduct(new_product_list[i]);
        }
    }
    else
    {
        cerr << "Unable to open file for reading!" << endl;
        return 1;
    }

    return 0;
}
