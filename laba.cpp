#include <iostream>
#include <limits>
#define NOMINMAX
#include <Windows.h>
#include <random>
#include <string>
#include <cctype>

using std::cout;
using std::endl;
using std::cin;

// ������� ������ �����
void ClearInputBuffer(char delimiter = '\n') {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), delimiter);
}

// �������� ����� �� ������������� �����
bool ValidateInput(int number) {
    if (number <= 0) {
        cout << "����� ������ ���� �������������!" << endl;
        return false;
    }
    return true;
}

// �������� ����� �� ��������
bool ValidateInput(int number, int minValue, int maxValue) {
    if (number < minValue || number > maxValue) {
        cout << "����� ������ ���� � ��������� �� " << minValue << " �� " << maxValue << "!" << endl;
        return false;
    }
    return true;
}

// ���������� ������� � ������� �������� (��� �������� � ����������� ���������)
char ToLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32; // �������������� ���������� ����
    }
    if (c >= '�' && c <= '�') {
        return c + 32; // �������������� ������� ����
    }
    return c;
}

// ���������� �������� ��������� �������
void UpdateCount(int& count, int size) {
    if (count < 0) {
        count = 0;
    }
    else if (count > size) {
        count = size;
    }
}

// ��������� ������� �������
void EditSizeArray(int** array, int& size, int& count) {
    cout << "������� ������ �������: " << size << endl;
    cout << "������ ��������� ������ �� �������� �������? (��/���): ";
    char choice;
    cin >> choice;
    choice = ToLower(choice);

    while (choice != '�' && choice != '�') {
        cout << "������� '��' ��� '���': ";
        cin >> choice;
        choice = ToLower(choice);
    }

    cout << "������� ����� ������ �������: ";
    int newSize;
    while (!(cin >> newSize) || !ValidateInput(newSize)) {
        cout << "������! ������� ������������� �����: ";
        ClearInputBuffer();
    }

    int* newArray = new int[newSize](); // ������������� ������ ������� + ���������� ������

    if (choice == '�') {
        int elementsToCopy = (size < newSize) ? size : newSize;
        for (int i = 0; i < elementsToCopy; ++i) {
            newArray[i] = (*array)[i];
        }
        count = elementsToCopy;
        cout << "������ ���������. ����� ������ �������: " << newSize << endl;
    }
    else {
        count = 0;
        cout << "������ ������. ����� ������ �������: " << newSize << endl;
    }

    delete[] * array; // ������������ ������ ������
    *array = newArray; // ������� ��������� ����� �� ����� ������
    size = newSize; // ���������� �������
}

// ���������� ����� ��������� �������
int CalculateSum(const int* array, int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += array[i];
    }
    return sum;
}

// ����� ������������� �������� � �������
int FindMaxElement(const int* array, int size) {
    int maxElement = array[0];
    for (int i = 1; i < size; ++i) {
        if (array[i] > maxElement) {
            maxElement = array[i];
        }
    }
    return maxElement;
}

// ����� ������� �� �����
void PrintArray(const int* array, int size, int count) {
    if (count == 0) {
        cout << "������ ����. ��������� ��� � ��������� �������." << endl;
        return;
    }
    cout << "�������� �������:" << endl;
    for (int i = 0; i < size; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;
}

// ���������� ������� ���������� �������
void FillArrayRandom(int* array, int size, int& count) {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_int_distribution<> dist(1, 100);

    UpdateCount(count, size);
    for (int i = count; i < size; ++i) {
        array[i] = dist(mersenne);
        count++;
    }
}

// ������ ���������� �������
void FillArray(int* array, int size, int& count) {
    cout << "������� �������� �������:" << endl;
    UpdateCount(count, size);
    for (int i = count; i < size; ++i) {
        cout << "������� " << i + 1 << ": ";
        while (!(cin >> array[i])) {
            cout << "������! ������� �����: ";
            ClearInputBuffer();
        }
        count++;
    }
}

// ����� ���������� � �������
void PrintArrayInfo(const int* array, int size, int count) {
    PrintArray(array, size, count);
    if (count > 0) {
        cout << "������������ �������: " << FindMaxElement(array, size) << endl;
        cout << "����� ���������: " << CalculateSum(array, size) << endl;
    }
}

int main() {
    int count = 0; // ���������� ����������� ���������
    int choice;
    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251);

    cout << "������� ������ �������: ";
    int size;
    while (!(cin >> size) || !ValidateInput(size)) {
        cout << "������! ������� ������������� �����: ";
        ClearInputBuffer();
    }

    int* array = new int[size](); // ������������ ��������� ������ ��� ������� + ���������� ������

    while (true) {
        cout << "----------------------------------------" << endl;
        cout << "����:" << endl;
        cout << "1. ��������� ������ �������" << endl;
        cout << "2. ��������� ������ ���������� �������" << endl;
        cout << "3. ������� ������" << endl;
        cout << "4. �������� ������ �������" << endl;
        cout << "5. �����" << endl;
        cout << "----------------------------------------" << endl;
        cout << "�������� ��������: ";
        while (!(cin >> choice) || !ValidateInput(choice, 1, 5)) {
            cout << "������! ������� ����� �� 1 �� 5: ";
            ClearInputBuffer();
        }

        switch (choice) {
        case 1:
            FillArray(array, size, count);
            PrintArrayInfo(array, size, count);
            break;
        case 2:
            FillArrayRandom(array, size, count);
            PrintArrayInfo(array, size, count);
            break;
        case 3:
            PrintArray(array, size, count);
            break;
        case 4:
            EditSizeArray(&array, size, count);
            break;
        case 5:
            delete[] array; // ������������ ������ 
            return 0;
        default:
            cout << "����������� ������!" << endl;
            break;
        }
    }
    return 0;
}