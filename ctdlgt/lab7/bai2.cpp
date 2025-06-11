#include <iostream>
#include <vector>
using namespace std;

// Hàm đổi chỗ 2 phần tử
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Hàm điều chỉnh heap tại vị trí i (heapify xuống)
void heapifyDown(vector<int>& heap, int n, int i) {
    int largest = i;         // Gán nút cha là lớn nhất
    int left = 2 * i + 1;    // Con trái
    int right = 2 * i + 2;   // Con phải

    // Nếu con trái lớn hơn cha
    if (left < n && heap[left] > heap[largest])
        largest = left;

    // Nếu con phải lớn hơn cha
    if (right < n && heap[right] > heap[largest])
        largest = right;

    // Nếu có sự thay đổi, tiếp tục đệ quy
    if (largest != i) {
        swap(heap[i], heap[largest]);
        heapifyDown(heap, n, largest);
    }
}

// Hàm xây dựng max heap từ vector đầu vào
void buildMaxHeap(vector<int>& heap) {
    int n = heap.size();
    // Bắt đầu từ nút cha cuối cùng → gốc
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyDown(heap, n, i);
    }
}

// a) Thêm phần tử vào heap
void insert(vector<int>& heap, int value) {
    heap.push_back(value);
    int i = heap.size() - 1;

    // Duyệt lên để sắp xếp lại heap
    while (i != 0 && heap[(i - 1) / 2] < heap[i]) {
        swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// b) Xóa phần tử đầu tiên (lớn nhất)
void deleteMax(vector<int>& heap) {
    if (heap.empty()) {
        cout << "Heap rỗng.\n";
        return;
    }

    // Đổi phần tử cuối với đầu rồi loại bỏ cuối
    heap[0] = heap.back();
    heap.pop_back();

    // Điều chỉnh lại heap
    heapifyDown(heap, heap.size(), 0);
}

// c) Sắp xếp giảm dần bằng heap sort
vector<int> heapSort(vector<int> heap) {
    vector<int> sorted;
    buildMaxHeap(heap);
    int n = heap.size();
    for (int i = n - 1; i >= 0; i--) {
        swap(heap[0], heap[i]);      // Đưa max về cuối
        sorted.push_back(heap[i]);   // Ghi lại vào mảng kết quả
        heapifyDown(heap, i, 0);     // Xây lại heap
    }
    return sorted;
}

// In heap
void printHeap(const vector<int>& heap) {
    for (int val : heap) {
        cout << val << " ";
    }
    cout << endl;
}

// =======================
// Chương trình chính
// =======================
int main() {
    // Tập đầu vào
    vector<int> heap = {45, 36, 54, 27, 63, 72, 61, 18};
    
    // Xây dựng Max Heap
    buildMaxHeap(heap);

    cout << "Max Heap sau khi xây dựng: ";
    printHeap(heap);

    // a) Thêm phần tử
    cout << "Thêm phần tử 80 vào heap...\n";
    insert(heap, 80);
    printHeap(heap);

    // b) Xóa phần tử lớn nhất
    cout << "Xóa phần tử lớn nhất khỏi heap...\n";
    deleteMax(heap);
    printHeap(heap);

    // c) Sắp xếp giảm dần
    cout << "Danh sách sau khi sắp xếp giảm dần (Heap Sort): ";
    vector<int> sorted = heapSort(heap);
    for (int val : sorted) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
