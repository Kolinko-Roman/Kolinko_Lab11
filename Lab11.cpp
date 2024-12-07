#include <iostream>
#include <regex>
#include <string>
using namespace std;
struct Product {
private:
    string name;
    double price;
    string barcode;
public:
    Product(const string& productName, double productPrice, const string& productBarcode)
        : name(productName), price(productPrice), barcode(productBarcode) {}
    string getName() const { return name; }
    double getPrice() const { return price; }
    string getBarcode() const { return barcode; }
    bool isValidBarcode() const {
        regex barcodeRegex(R"(\d{12})");
        return regex_match(barcode, barcodeRegex);
    }
    int calculateCheckDigit() const {
        if (!isValidBarcode()) {
            throw runtime_error("Штрих-код не відповідає формату.");
        }
        int sum = 0;
        for (size_t i = 0; i < barcode.size(); ++i) {
            int digit = barcode[i] - '0'; 
            if (i % 2 == 0) {
                sum += digit; 
            } else {
                sum += digit * 3; 
            }
        }
        int checkDigit = (10 - (sum % 10)) % 10; 
        return checkDigit;
    }
    void printInfo() const {
        cout << "Назва: " << name << "\nЦіна: " << price << "\nШтрих-код: " << barcode << endl;
        if (isValidBarcode()) {
            cout << "Контрольна цифра: " << calculateCheckDigit() << endl;
        } else {
            cout << "Штрих-код некоректний." << endl;
        }
    }
};
int main() {
    try {
        Product product("Молоко", 28.50, "123456789012");
        product.printInfo();
        Product invalidProduct("Хліб", 15.00, "12345");
        invalidProduct.printInfo();
    } catch (const exception& e) {
        cerr << "Помилка: " << e.what() << endl;
    }
    return 0;
}
