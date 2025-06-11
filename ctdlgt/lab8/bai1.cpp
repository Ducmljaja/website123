#include <iostream>
#include <string>
using namespace std;

const int TABLE_SIZE = 10;  // Kích thước bảng băm (hash table)

// Cấu trúc sản phẩm
struct Product {
    int code;           // Mã sản phẩm (5 chữ số)
    string name;        // Tên sản phẩm
    float price;        // Giá sản phẩm
    bool isDeleted;     // Đánh dấu đã bị xóa

    Product() {
        code = -1;
        name = "";
        price = 0;
        isDeleted = false;
    }
};

Product hashTable[TABLE_SIZE];

// Hàm băm: h(k) = k % TABLE_SIZE
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Thêm sản phẩm vào bảng băm
void addProduct(int code, string name, float price) {
    int index = hashFunction(code);
    int originalIndex = index;
    int i = 0;

    while (hashTable[index].code != -1 && !hashTable[index].isDeleted && i < TABLE_SIZE) {
        index = (originalIndex + ++i) % TABLE_SIZE;  // Linear probing
    }

    if (i == TABLE_SIZE) {
        cout << "Bảng băm đầy, không thể thêm!\n";
        return;
    }

    hashTable[index].code = code;
    hashTable[index].name = name;
    hashTable[index].price = price;
    hashTable[index].isDeleted = false;
}

// In danh sách sản phẩm
void printProducts() {
    cout << "Danh sách sản phẩm:\n";
    cout << "Code\tName\t\tPrice\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i].code != -1 && !hashTable[i].isDeleted) {
            cout << hashTable[i].code << "\t" << hashTable[i].name << "\t\t" << hashTable[i].price << endl;
        }
    }
}

// Tìm sản phẩm theo mã
void searchProduct(int code) {
    int index = hashFunction(code);
    int originalIndex = index;
    int i = 0;

    while (i < TABLE_SIZE && hashTable[index].code != -1) {
        if (hashTable[index].code == code && !hashTable[index].isDeleted) {
            cout << "Tìm thấy sản phẩm: " << hashTable[index].name << ", Giá: " << hashTable[index].price << endl;
            return;
        }
        index = (originalIndex + ++i) % TABLE_SIZE;
    }

    cout << "Không tìm thấy sản phẩm với mã: " << code << endl;
}

// Xóa sản phẩm
void removeProduct(int code) {
    int index = hashFunction(code);
    int originalIndex = index;
    int i = 0;

    while (i < TABLE_SIZE && hashTable[index].code != -1) {
        if (hashTable[index].code == code && !hashTable[index].isDeleted) {
            hashTable[index].isDeleted = true;
            cout << "Đã xóa sản phẩm có mã: " << code << endl;
            return;
        }
        index = (originalIndex + ++i) % TABLE_SIZE;
    }

    cout << "Không tìm thấy sản phẩm để xóa.\n";
}

int main() {
    // Thêm sản phẩm ban đầu
    addProduct(10001, "Sugar", 50000);
    addProduct(10002, "Salt", 7500);
    addProduct(10003, "Rice", 15000);
    addProduct(10004, "Fish sauce", 30000);

    printProducts();

    cout << "\nTìm sản phẩm mã 10003:\n";
    searchProduct(10003);

    cout << "\nXóa sản phẩm mã 10002:\n";
    removeProduct(10002);

    cout << "\nDanh sách sau khi xóa:\n";
    printProducts();

    cout << "\nThêm sản phẩm mới mã 10005:\n";
    addProduct(10005, "Pepper", 12000);
    printProducts();

    return 0;
}
