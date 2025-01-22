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

// Очистка буфера ввода
void ClearInputBuffer(char delimiter = '\n') {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), delimiter);
}

// Проверка ввода на положительное число
bool ValidateInput(int number) {
    if (number <= 0) {
        cout << "Число должно быть положительным!" << endl;
        return false;
    }
    return true;
}

// Проверка ввода на диапазон
bool ValidateInput(int number, int minValue, int maxValue) {
    if (number < minValue || number > maxValue) {
        cout << "Число должно быть в диапазоне от " << minValue << " до " << maxValue << "!" << endl;
        return false;
    }
    return true;
}

// Приведение символа к нижнему регистру (для русского и английского алфавитов)
char ToLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32; // Преобразование английских букв
    }
    if (c >= 'А' && c <= 'Я') {
        return c + 32; // Преобразование русских букв
    }
    return c;
}

// Обновление счётчика элементов массива
void UpdateCount(int& count, int size) {
    if (count < 0) {
        count = 0;
    }
    else if (count > size) {
        count = size;
    }
}

// Изменение размера массива
void EditSizeArray(int** array, int& size, int& count) {
    cout << "Текущий размер массива: " << size << endl;
    cout << "Хотите сохранить данные из текущего массива? (Да/Нет): ";
    char choice;
    cin >> choice;
    choice = ToLower(choice);

    while (choice != 'д' && choice != 'н') {
        cout << "Введите 'Да' или 'Нет': ";
        cin >> choice;
        choice = ToLower(choice);
    }

    cout << "Введите новый размер массива: ";
    int newSize;
    while (!(cin >> newSize) || !ValidateInput(newSize)) {
        cout << "Ошибка! Введите положительное число: ";
        ClearInputBuffer();
    }

    int* newArray = new int[newSize](); // Инициализация нового массива + заполнение нулями

    if (choice == 'д') {
        int elementsToCopy = (size < newSize) ? size : newSize;
        for (int i = 0; i < elementsToCopy; ++i) {
            newArray[i] = (*array)[i];
        }
        count = elementsToCopy;
        cout << "Данные сохранены. Новый размер массива: " << newSize << endl;
    }
    else {
        count = 0;
        cout << "Массив очищен. Новый размер массива: " << newSize << endl;
    }

    delete[] * array; // Освобождение старой памяти
    *array = newArray; // передаём указателю адрес на новый массив
    size = newSize; // Обновление размера
}

// Вычисление суммы элементов массива
int CalculateSum(const int* array, int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += array[i];
    }
    return sum;
}

// Поиск максимального элемента в массиве
int FindMaxElement(const int* array, int size) {
    int maxElement = array[0];
    for (int i = 1; i < size; ++i) {
        if (array[i] > maxElement) {
            maxElement = array[i];
        }
    }
    return maxElement;
}

// Вывод массива на экран
void PrintArray(const int* array, int size, int count) {
    if (count == 0) {
        cout << "Массив пуст. Заполните его и повторите попытку." << endl;
        return;
    }
    cout << "Элементы массива:" << endl;
    for (int i = 0; i < size; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;
}

// Заполнение массива случайными числами
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

// Ручное заполнение массива
void FillArray(int* array, int size, int& count) {
    cout << "Введите элементы массива:" << endl;
    UpdateCount(count, size);
    for (int i = count; i < size; ++i) {
        cout << "Элемент " << i + 1 << ": ";
        while (!(cin >> array[i])) {
            cout << "Ошибка! Введите число: ";
            ClearInputBuffer();
        }
        count++;
    }
}

// Вывод информации о массиве
void PrintArrayInfo(const int* array, int size, int count) {
    PrintArray(array, size, count);
    if (count > 0) {
        cout << "Максимальный элемент: " << FindMaxElement(array, size) << endl;
        cout << "Сумма элементов: " << CalculateSum(array, size) << endl;
    }
}

int main() {
    int count = 0; // Количество заполненных элементов
    int choice;
    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251);

    cout << "Введите размер массива: ";
    int size;
    while (!(cin >> size) || !ValidateInput(size)) {
        cout << "Ошибка! Введите положительное число: ";
        ClearInputBuffer();
    }

    int* array = new int[size](); // Динамическое выделение памяти для массива + заполнение нулями

    while (true) {
        cout << "----------------------------------------" << endl;
        cout << "Меню:" << endl;
        cout << "1. Заполнить массив вручную" << endl;
        cout << "2. Заполнить массив случайными числами" << endl;
        cout << "3. Вывести массив" << endl;
        cout << "4. Изменить размер массива" << endl;
        cout << "5. Выход" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Выберите действие: ";
        while (!(cin >> choice) || !ValidateInput(choice, 1, 5)) {
            cout << "Ошибка! Введите число от 1 до 5: ";
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
            delete[] array; // Освобождение памяти 
            return 0;
        default:
            cout << "Неизвестная ошибка!" << endl;
            break;
        }
    }
    return 0;
}