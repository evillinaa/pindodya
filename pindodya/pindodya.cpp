#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>


class FileManager
{
private:
    std::string product_file;
    std::string quantity_file;
    std::string price_file;

public:
    FileManager() {}

    void setFiles(const std::string& productFile, const std::string& quantityFile, const std::string& priceFile)
    {
        product_file = productFile;
        quantity_file = quantityFile;
        price_file = priceFile;
    }

    bool checkFiles()
    {
        std::ifstream product(product_file);
        std::ifstream quantity(quantity_file);
        std::ifstream price(price_file);

        if (product.good() && quantity.good() && price.good())
        {
            int choice;
            std::cout << "Файлы уже существуют. Перезаписать данные? (1 - да, 2 -н нет): ";
            std::cin >> choice;
            return (choice == '1');
        }
        else
        {
            return true;
        }
    }

    void getData(std::string& product, int& quantity, float& price)
    {
        std::cout << "Введите название товара: ";
        std::cin.ignore();
        getline(std::cin, product);
        std::cout << "Введите количество: ";
        std::cin >> quantity;
        std::cout << "Введите цену: ";
        std::cin >> price;
    }

    void writeData(const std::string& product, int quantity, float price)
    {
        std::ofstream productFile(product_file, std::ios::app);
        std::ofstream quantityFile(quantity_file, std::ios::app);
        std::ofstream priceFile(price_file, std::ios::app);

        productFile << product << "\n";
        quantityFile << quantity << "\n";
        priceFile << price << "\n";
    }

    void readData()
    {
        std::ifstream productFile(product_file);
        std::ifstream quantityFile(quantity_file);
        std::ifstream priceFile(price_file);

        std::string product;
        int quantity;
        float price;
        int id = 1;

        std::cout << "Id \ Название товара \ Кол-во товара \ Цена" << "\n";
        std::cout << "------------------------------" << "\n";

        while (getline(productFile, product))
        {
            quantityFile >> quantity;
            priceFile >> price;
            std::cout << id++ << ") " << product << " " << quantity << " " << price << "\n";
        }
    }
};

int main()
{

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    FileManager fileManager;

    fileManager.setFiles("товары.txt", "количество.txt", "цены.txt");

    if (fileManager.checkFiles())
    {
        for (int i = 0; i < 3; ++i)
        {
            std::string product;
            int quantity;
            float price;
            fileManager.getData(product, quantity, price);
            fileManager.writeData(product, quantity, price);
        }
    }

    fileManager.readData();

    return 0;
}
