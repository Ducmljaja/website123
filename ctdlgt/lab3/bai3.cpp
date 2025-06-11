#include <iostream>
using namespace std;

// ---------------------- CẤU TRÚC QUEUE ------------------------
struct Node {
    int data;
    Node* next;
};

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() {
        front = rear = nullptr;
    }

    void enqueue(int value) {
        Node* newNode = new Node{value, nullptr};
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    int dequeue() {
        if (!front) return -1;
        int val = front->data;
        Node* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        return val;
    }

    int peek() {
        return (front) ? front->data : -1;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    ~Queue() {
        while (!isEmpty()) dequeue();
    }
};

// ------------------ GIẢI BÀI TOÁN JOSEPHUS ----------------------
int josephus(int n, int k) {
    Queue q;

    // Bỏ vào hàng đợi n người (1 đến n)
    for (int i = 1; i <= n; i++) {
        q.enqueue(i);
    }

    while (q.isEmpty() == false && q.peek() != q.dequeue()) {
        // Bỏ qua k - 1 người
        for (int i = 1; i < k; i++) {
            int temp = q.dequeue();
            q.enqueue(temp);
        }
        // Loại người thứ k
        int eliminated = q.dequeue();
        cout << "Nguoi bi loai: " << eliminated << endl;
    }

    // Người còn lại là người thắng
    return q.peek();
}

// -------------------------- MAIN -------------------------------
int main() {
    int n, k;
    cout << "Nhap so nguoi (n): ";
    cin >> n;
    cout << "Nhap buoc dem (k): ";
    cin >> k;

    int winner = josephus(n, k);
    cout << "\nNguoi chien thang la: " << winner << endl;

    return 0;
}
