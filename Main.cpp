#include <iostream>
#include <cstring>
#include <stdexcept> 
#include <string>
using namespace std;


class Exception {
protected:
    char message[100];
public:
    Exception(const char* m) {
        strcpy_s(message, m);
    }
    virtual const char* GetM() const {
        return message;
    }
};


class ArrayDataException : public Exception {
public:
    ArrayDataException(int row, int col) : Exception("Invalid data at ") {
        cout << "| - " << row + 1 << " --- " << col + 1 << endl; 
    }
};


class ArraySizeException : public Exception {
public:
    ArraySizeException() : Exception("Invalid array size") {}
};


class ArrayValueCalculator {
public:
    int doCalc(const char* arr[4][4], int row, int col) {

        if (row != 4 || col != 4) {
            throw ArraySizeException(); 
        }

        int sum = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                try {

                    sum += stoi(arr[i][j]);
                }
                catch (const invalid_argument&) {
                    throw ArrayDataException(i, j); 
                }
                catch (const out_of_range&) {
                    throw ArrayDataException(i, j);
                }
            }
        }
        return sum;
    }
};

int main() {
    ArrayValueCalculator calculator;

    
    const char* correct[4][4] = {
        {"1", "2", "3", "4"},
        {"5", "6", "7", "8"},
        {"9", "10", "11", "12"},
        {"13", "14", "1", "16"} 
    };

    
    try {
        int result = calculator.doCalc(correct, 4, 4);
        cout << "Sum -> " << result << endl;
    }
    catch (const ArrayDataException& e) {
        cout << "ArrayDataException: " << e.GetM() << endl;
    }
    catch (const ArraySizeException& e) {
        cout << "ArraySizeException: " << e.GetM() << endl;
    }

    return 0;
}























