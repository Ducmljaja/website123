#include <iostream>
#include <fstream>
#include <string>

#include <iomanip>
using namespace std;

// Cấu trúc ngày sinh
struct Date {
    int day, month, year;
};

// Cấu trúc sinh viên
struct Student {
    string name;
    Date dob;
    float math, physic, language;
};

// Cấu trúc nút trong danh sách liên kết đơn
struct Node {
    Student data;
    Node* next;
};

typedef Node* List;

// Hàm tạo node mới
Node* createNode(Student s) {
    Node* newNode = new Node;
    newNode->data = s;
    newNode->next = nullptr;
    return newNode;
}

// Thêm sinh viên vào cuối danh sách
void addLast(List& head, Student s) {
    Node* newNode = createNode(s);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newNode;
    }
}

// Nhập thông tin một sinh viên
Student inputStudent() {
    Student s;
    cout << "Nhập tên (hoặc gõ dấu cách để dừng): ";
    getline(cin, s.name);
    if (s.name == " ") return s;

    cout << "Ngày tháng năm sinh (dd mm yyyy): ";
    cin >> s.dob.day >> s.dob.month >> s.dob.year;
    cout << "Điểm Toán: "; cin >> s.math;
    cout << "Điểm Lý: "; cin >> s.physic;
    cout << "Điểm Ngoại ngữ: "; cin >> s.language;
    cin.ignore(); // Xoá bộ nhớ đệm sau khi nhập số
    return s;
}

// In thông tin một sinh viên
void printStudent(Student s) {
    cout << left << setw(15) << s.name
         << setw(10) << s.dob.day << "/" << s.dob.month << "/" << s.dob.year << "  "
         << setw(6) << s.math
         << setw(6) << s.physic
         << setw(6) << s.language
         << setw(6) << (s.math + s.physic + s.language) / 3 << endl;
}

// In toàn bộ danh sách sinh viên
void printList(List head) {
    cout << left << setw(15) << "Họ tên"
         << setw(14) << "Ngày sinh"
         << setw(6) << "Toán"
         << setw(6) << "Lý"
         << setw(6) << "Ngoại"
         << setw(6) << "TB" << endl;
    Node* temp = head;
    while (temp != nullptr) {
        printStudent(temp->data);
        temp = temp->next;
    }
}

// Đọc danh sách sinh viên từ file
void readFromFile(List& head, const string& filename) {
    ifstream in(filename);
    if (!in) return;
    Student s;
    while (getline(in, s.name)) {
        in >> s.dob.day >> s.dob.month >> s.dob.year;
        in >> s.math >> s.physic >> s.language;
        in.ignore();
        addLast(head, s);
    }
    in.close();
}

// Ghi danh sách sinh viên ra file
void writeToFile(List head, const string& filename) {
    ofstream out(filename);
    Node* temp = head;
    while (temp != nullptr) {
        out << temp->data.name << endl;
        out << temp->data.dob.day << " " << temp->data.dob.month << " " << temp->data.dob.year << endl;
        out << temp->data.math << " " << temp->data.physic << " " << temp->data.language << endl;
        temp = temp->next;
    }
    out.close();
}

// Đếm số sinh viên sinh trong một năm
int countByYear(List head, int year) {
    int count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.dob.year == year)
            count++;
        temp = temp->next;
    }
    return count;
}

// Kiểm tra sinh viên theo tên
bool searchByName(List head, string name) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.name == name)
            return true;
        temp = temp->next;
    }
    return false;
}

// Xoá sinh viên theo tên
void deleteByName(List& head, string name) {
    Node* temp = head, *prev = nullptr;
    while (temp != nullptr && temp->data.name != name) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == nullptr) return;
    if (prev == nullptr) head = temp->next;
    else prev->next = temp->next;
    delete temp;
}

// Tìm và in sinh viên có điểm trung bình cao nhất
void printMaxAverage(List head) {
    float maxAvg = -1;
    Node* temp = head;
    while (temp != nullptr) {
        float avg = (temp->data.math + temp->data.physic + temp->data.language) / 3;
        if (avg > maxAvg) maxAvg = avg;
        temp = temp->next;
    }

    temp = head;
    while (temp != nullptr) {
        float avg = (temp->data.math + temp->data.physic + temp->data.language) / 3;
        if (avg == maxAvg)
            printStudent(temp->data);
        temp = temp->next;
    }
}

// In danh sách sinh viên có điểm Toán dưới 5
void printMathBelowFive(List head) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.math < 5)
            printStudent(temp->data);
        temp = temp->next;
    }
}

// MENU chức năng chính
void menu() {
    List studentList = nullptr;
    readFromFile(studentList, "StudentList.txt"); // Đọc dữ liệu từ file

    int choice;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Nhập danh sách sinh viên\n";
        cout << "2. In danh sách sinh viên\n";
        cout << "3. Thêm sinh viên mới\n";
        cout << "4. Đếm sinh viên theo năm sinh\n";
        cout << "5. Tìm sinh viên theo tên\n";
        cout << "6. Xoá sinh viên theo tên\n";
        cout << "7. Tìm sinh viên có điểm TB cao nhất\n";
        cout << "8. In sinh viên có điểm Toán < 5\n";
        cout << "9. Ghi danh sách ra file\n";
        cout << "0. Thoát\n";
        cout << "Chọn: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                while (true) {
                    Student s = inputStudent();
                    if (s.name == " ") break;
                    addLast(studentList, s);
                }
                break;
            }
            case 2: printList(studentList); break;
            case 3: {
                Student s = inputStudent();
                if (s.name != " ") addLast(studentList, s);
                break;
            }
            case 4: {
                int y;
                cout << "Nhập năm sinh: ";
                cin >> y;
                cout << "Tổng số sinh viên: " << countByYear(studentList, y) << endl;
                break;
            }
            case 5: {
                string name;
                cout << "Nhập tên cần tìm: ";
                getline(cin, name);
                cout << (searchByName(studentList, name) ? "Tìm thấy" : "Không tìm thấy") << endl;
                break;
            }
            case 6: {
                string name;
                cout << "Nhập tên cần xoá: ";
                getline(cin, name);
                deleteByName(studentList, name);
                break;
            }
            case 7: printMaxAverage(studentList); break;
            case 8: printMathBelowFive(studentList); break;
            case 9: writeToFile(studentList, "StudentList.txt"); break;
            case 0: cout << "Thoát chương trình...\n"; break;
            default: cout << "Lựa chọn không hợp lệ!\n"; break;
        }

    } while (choice != 0);
}

int main() {
    menu();
    return 0;
}
