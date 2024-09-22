#include <iostream>
#include <vector>

using namespace std;

vector<int> decimalToBinary(int num, int bits) {
    vector<int> binary(bits, 0);
    if (num < 0) {
        num = (1 << bits) + num;
    }
    for (int i = bits - 1; i >= 0; --i) {
        binary[i] = num & 1;
        num >>= 1;
    }
    return binary;
}

vector<int> binarySum(vector<int> A, vector<int> B, int bits) {
    vector<int> result(bits, 0);
    int carry = 0;
    for (int i = bits - 1; i >= 0; --i) {
        int sum = A[i] + B[i] + carry;
        result[i] = sum % 2;
        carry = sum / 2;
    }
    return result;
}

vector<int> binarySub(vector<int> A, vector<int> B, int bits) {
    for (int i = 0; i < bits; ++i) {
        B[i] = B[i] == 0 ? 1 : 0;
    }
    B = binarySum(B, decimalToBinary(1, bits), bits);
    return binarySum(A, B, bits);
}

void arithmeticShift(vector<int>& A, vector<int>& Q, int& Q_1, int bits) {
    int msbA = A[0];
    Q_1 = Q[bits - 1];
    for (int i = bits - 1; i > 0; --i) {
        Q[i] = Q[i - 1];
    }
    Q[0] = A[bits - 1];
    for (int i = bits - 1; i > 0; --i) {
        A[i] = A[i - 1];
    }
    A[0] = msbA;
}

void boothAlgorithm(int multiplicand, int multiplier, int bits) {
    vector<int> M = decimalToBinary(multiplicand, bits);
    vector<int> A(bits, 0);
    vector<int> Q = decimalToBinary(multiplier, bits);
    int Q_1 = 0;
    int count = bits;

    cout << "Inicializando:\n";
    cout << "A: ";
    for (int i : A) cout << i;
    cout << "\nQ: ";
    for (int i : Q) cout << i;
    cout << "\nQ-1: " << Q_1 << "\n";

    while (count > 0) {
        int Q0_Q1 = Q[bits - 1] * 2 + Q_1;
        if (Q0_Q1 == 10) {
            A = binarySub(A, M, bits);
        } else if (Q0_Q1 == 1) {
            A = binarySum(A, M, bits);
        }

        arithmeticShift(A, Q, Q_1, bits);
        count--;

        cout << "\nPaso con count = " << count << ":\n";
        cout << "A: ";
        for (int i : A) cout << i;
        cout << "\nQ: ";
        for (int i : Q) cout << i;
        cout << "\nQ-1: " << Q_1 << "\n";
    }

    cout << "\nResultado final en binario (A + Q):\n";
    for (int i : A) cout << i;
    for (int i : Q) cout << i;
    cout << endl;
}

int main() {
    int multiplicand, multiplier, bits;

    cout << "Introduce el multiplicando: ";
    cin >> multiplicand;
    cout << "Introduce el multiplicador: ";
    cin >> multiplier;
    cout << "Introduce el número de bits: ";
    cin >> bits;

    boothAlgorithm(multiplicand, multiplier, bits);

    return 0;
}
