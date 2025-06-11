#include <iostream>
#include <cstring>
using namespace std;

struct Student
{
    char id[12];       // Mã sinh viên, tối đa 11 ký tự + 1 ký tự kết thúc '\0'
    char name[30];     // Tên sinh viên, tối đa 29 ký tự + '\0'
    char className[10]; // Lớp học, tối đa 9 ký tự + '\0'
    float mMath;       // Điểm môn Toán
    float mPhysical;   // Điểm môn Vật lý
};

// Hàm nhập thông tin một sinh viên
void inputStudent(Student &s)
{
    cout << "Nhập mã sinh viên: ";
    cin.ignore(); // Xóa bộ đệm trước khi nhập chuỗi
    cin.getline(s.id, 12);

    cout << "Nhập tên sinh viên: ";
    cin.getline(s.name, 30);

    cout << "Nhập lớp: ";
    cin.getline(s.className, 10);

    cout << "Nhập điểm Toán: ";
    cin >> s.mMath;

    cout << "Nhập điểm Vật lý: ";
    cin >> s.mPhysical;
}

// Hàm xuất thông tin một sinh viên
void outputStudent(const Student &s)
{
    cout << s.id << "\t" << s.name << "\t" << s.className << "\t"
         << s.mMath << "\t" << s.mPhysical << "\t"
         << (s.mMath + s.mPhysical) / 2 << endl; // In thêm điểm trung bình
}

// Hàm nhập danh sách sinh viên
void inputList(Student a[], int &n)
{
    cout << "Nhập số lượng sinh viên: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Nhập thông tin sinh viên thứ " << i + 1 << ":\n";
        inputStudent(a[i]);
    }
}

// Hàm xuất danh sách sinh viên
void outputList(Student a[], int n)
{
    cout << "ID\tTên\tLớp\tToán\tVật lý\tTrung bình\n";
    for (int i = 0; i < n; i++)
    {
        outputStudent(a[i]);
    }
}

// Hàm tìm sinh viên theo mã
int searchStudentById(Student a[], int n, const char id[])
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(a[i].id, id) == 0)
        {
            return i; // Trả về vị trí tìm thấy
        }
    }
    return -1; // Không tìm thấy trả về -1
}

// Hàm sắp xếp danh sách sinh viên theo điểm trung bình giảm dần
void sortByAvgDescending(Student a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            float avg_i = (a[i].mMath + a[i].mPhysical) / 2;
            float avg_j = (a[j].mMath + a[j].mPhysical) / 2;
            if (avg_i < avg_j)
            {
                // Đổi chỗ 2 sinh viên
                Student temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

int main()
{
    Student students[100]; // Mảng lưu tối đa 100 sinh viên
    int n;                // Số lượng sinh viên hiện có

    // Nhập danh sách sinh viên
    inputList(students, n);

    cout << "\nDanh sách sinh viên vừa nhập:\n";
    outputList(students, n);

    // Tìm sinh viên theo mã
    char searchId[12];
    cout << "\nNhập mã sinh viên cần tìm: ";
    cin.ignore();
    cin.getline(searchId, 12);
    int pos = searchStudentById(students, n, searchId);
    if (pos != -1)
    {
        cout << "Thông tin sinh viên tìm thấy:\n";
        outputStudent(students[pos]);
    }
    else
    {
        cout << "Không tìm thấy sinh viên với mã " << searchId << endl;
    }

    // Sắp xếp danh sách sinh viên theo điểm trung bình giảm dần
    sortByAvgDescending(students, n);

    cout << "\nDanh sách sinh viên sau khi sắp xếp theo điểm trung bình giảm dần:\n";
    outputList(students, n);

    return 0;
}
