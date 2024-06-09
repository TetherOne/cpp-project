#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

// Функция проверяет, является ли строка числом
bool isValidNumber(const string &s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Функция проверяет, равна ли сумма первых двух чисел третьему
bool checkSum(const string &a, const string &b, const string &c) {
    if (!isValidNumber(a) || !isValidNumber(b) || !isValidNumber(c))
        return false;

    try {
        long long int_a = stoll(a); // Преобразуем строку в число
        long long int_b = stoll(b);
        long long int_c = stoll(c);
        return (int_a + int_b == int_c); // Возвращаем true, если сумма равна, иначе false
    } catch (out_of_range &e) {
        // Если число выходит за пределы long long,
        // то функция возвращает false
        return false;
    }
}

int main() {
    ifstream inputFile("/Users/pasha/ClionProjects/untitled/input.txt");
    ofstream outputFile("/Users/pasha/ClionProjects/untitled/output.txt");

    if (!inputFile.is_open()) {
        cerr << "Ошибка при открытии input.txt";
        return 1;
    }

    if (!outputFile.is_open()) {
        cerr << "Ошибка при открытии output.txt";
        inputFile.close();
        return 1;
    }

    string input;
    inputFile >> input;
    inputFile.close();

    if (!isValidNumber(input)) {
        cerr << "Некорректные данные, считывающий файл должен"
                " содержать только цифры";
        outputFile << "Некорректные данные";
        outputFile.close();
        return 1;
    }

    int n = input.size();

    // Перебираем все возможные разбиения строки на три части
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < n - i; ++j) {
            string a = input.substr(0, i);
            string b = input.substr(i, j);
            string c = input.substr(i + j);

            if (checkSum(a, b, c)) {
                outputFile << a << "+" << b << "=" << c;
                outputFile.close();
                return 0;
            }

            string ring = input + input;
            // Перебираем все возможные разбиения кольцевой строки на три части
            for (int k = 0; k < n; ++k) {
                a = ring.substr(k, i);
                b = ring.substr(k + i, j);
                c = ring.substr(k + i + j, n - (i + j));

                if (checkSum(a, b, c)) {
                    outputFile << a << "+" << b << "=" << c;
                    outputFile.close();
                    return 0;
                }
            }
        }
    }

    outputFile << "No";
    outputFile.close();
    return 0;
}
