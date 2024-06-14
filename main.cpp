#include <iostream>
#include <fstream>
#include <string>


using namespace std;


bool isValidNumber(const string &s) {
    if(s.empty()) return false;

    for(char c : s) {
        if(!isdigit(c)) {
            return false;
        }
    }
    return s.size() == 1 || (s.size() > 1);
}

bool checkSum(const string &a, const string &b, const string &c) {
    if (!isValidNumber(a) || !isValidNumber(b) || !isValidNumber(c))
        return false;
    string sum = to_string(stoi(a) + stoi(b));
    return sum == c;
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

    if(!isValidNumber(input)) {
        cerr << "Некоректные данные, считывающий файл"
                " должен содержать только цифры";
    }

    int n = input.size();

    for (int i = 1; i < n - 1; ++i) {
        for (int j = 1; j < n - i; ++j) {
            string a = input.substr(0, i);
            string b = input.substr(i, j);
            string c = input.substr(i + j);

            if (checkSum(a, b, c)) {
                outputFile << a << "+" << b << "=" << c << endl;
                outputFile.close();
                return 0;
            }

            string ring = input + input;
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
}