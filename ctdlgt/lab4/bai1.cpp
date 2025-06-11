#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;

const int SIZE = 1000;
int arr[SIZE];

// --------- a) Sinh và in mảng ngẫu nhiên ---------
void generateRandomArray() {
    srand(time(0));
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 10000 + 1; // Từ 1 đến 10000
    }
}

void printArray(int a[], int size) {
    for (int i = 0; i < size; i++) {
        cout << a[i] << " ";
        if ((i + 1) % 20 == 0) cout << endl;
    }
}

// --------- b) Các thuật toán sắp xếp ---------
void bubbleSort(int a[], int size) {
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
}

void selectionSort(int a[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < size; j++)
            if (a[j] < a[minIdx])
                minIdx = j;
        swap(a[i], a[minIdx]);
    }
}

void insertionSort(int a[], int size) {
    for (int i = 1; i < size; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

// --------- c) So sánh thời gian và ghi file ---------
void compareSortTimes(int a[]) {
    ofstream fout("SortingTime.txt");

    auto testSort = [&](void (*sortFunc)(int[], int), const string& name) {
        int temp[SIZE];
        copy(a, a + SIZE, temp);

        auto start = high_resolution_clock::now();
        sortFunc(temp, SIZE);
        auto end = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(end - start).count();
        cout << name << " took " << duration << " ms" << endl;
        fout << name << " took " << duration << " ms\n";
    };

    testSort(bubbleSort, "Bubble Sort");
    testSort(selectionSort, "Selection Sort");
    testSort(insertionSort, "Insertion Sort");
    testSort([](int a[], int size) { sort(a, a + size); }, "STL sort");

    fout.close();
    cout << "=> Ket qua da duoc luu vao file SortingTime.txt\n";
}

// --------- d) Tìm tuyến tính ---------
int linearSearch(int a[], int size, int x) {
    for (int i = 0; i < size; i++)
        if (a[i] == x) return i;
    return -1;
}

// --------- e) Tìm nhị phân (cần sắp xếp trước) ---------
int binarySearch(int a[], int size, int x) {
    int l = 0, r = size - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (a[mid] == x) return mid;
        else if (a[mid] < x) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

// --------- MENU CHÍNH ---------
int main() {
    generateRandomArray();
    int choice, x;
    int sorted[SIZE];

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. In mang\n";
        cout << "2. So sanh thoi gian sap xep\n";
        cout << "3. Tim kiem tuyen tinh\n";
        cout << "4. Tim kiem nhi phan\n";
        cout << "0. Thoat\n";
        cout << "Lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
        case 1:
            printArray(arr, SIZE);
            break;
        case 2:
            compareSortTimes(arr);
            break;
        case 3:
            cout << "Nhap gia tri can tim: ";
            cin >> x;
            {
                int pos = linearSearch(arr, SIZE, x);
                if (pos != -1) cout << "Tim thay tai vi tri " << pos << endl;
                else cout << "Khong tim thay.\n";
            }
            break;
        case 4:
            copy(arr, arr + SIZE, sorted);
            sort(sorted, sorted + SIZE);
            cout << "Nhap gia tri can tim: ";
            cin >> x;
            {
                int pos = binarySearch(sorted, SIZE, x);
                if (pos != -1) cout << "Tim thay tai vi tri (sau sap xep) " << pos << endl;
                else cout << "Khong tim thay.\n";
            }
            break;
        case 0:
            cout << "Tam biet!\n";
            break;
        default:
            cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);

    return 0;
}
