#include <iostream>
#include <list>
using namespace std;

const int TABLE_SIZE = 9;  // Kích thước bảng băm (9 ô nhớ)

// Bảng băm dùng kỹ thuật chaining (dùng danh sách liên kết để xử lý xung đột)
list<int> hashTable[TABLE_SIZE];

// Hàm băm: h(k) = k % TABLE_SIZE
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// a) Thêm số vào bảng băm
void addNumber(int number) {
    int index = hashFunction(number);
    hashTable[index].push_back(number);
    cout << "Đã thêm " << number << " vào vị trí " << index << endl;
}

// b) In bảng băm
void printHashTable() {
    cout << "\nBảng băm hiện tại:\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << i << ": ";
        for (int num : hashTable[i]) {
            cout << num << " -> ";
        }
        cout << "NULL\n";
    }
}

// c) Tìm một số trong bảng băm
void searchNumber(int number) {
    int index = hashFunction(number);
    for (int num : hashTable[index]) {
        if (num == number) {
            cout << "Tìm thấy " << number << " tại vị trí " << index << endl;
            return;
        }
    }
    cout << "Không tìm thấy " << number << " trong bảng băm.\n";
}

// d) Xóa một số khỏi bảng băm
void removeNumber(int number) {
    int index = hashFunction(number);
    for (auto it = hashTable[index].begin(); it != hashTable[index].end(); ++it) {
        if (*it == number) {
            hashTable[index].erase(it);
            cout << "Đã xóa " << number << " khỏi vị trí " << index << endl;
            return;
        }
    }
    cout << "Không tìm thấy " << number << " để xóa.\n";
}

int main() {
    // Thêm một vài số ví dụ
    addNumber(45);
    addNumber(18);
    addNumber(27);
    addNumber(36);
    addNumber(54);
    addNumber(63);
    addNumber(72);
    addNumber(61);

    printHashTable();

    cout << "\nTìm số 36:\n";
    searchNumber(36);

    cout << "\nXóa số 27:\n";
    removeNumber(27);

    printHashTable();

    return 0;
}
