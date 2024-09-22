#include <iostream>
#include <bitset>

using namespace std;

const int MAX_BITS = 32;

bitset<MAX_BITS> decimalToBinary(int num, int bits) {
    bitset<MAX_BITS> binary;
    if (num < 0) {
        num = (1 << bits) + num;
    }
    binary = bitset<MAX_BITS>(num);
    return binary;
}

bitset<MAX_BITS> binarySum(bitset<MAX_BITS> A, bitset<MAX_BITS> B, int bits) {
    bitset<MAX_BITS> result;
    bool acarreo = false;
    for (int i = 0; i < bits; ++i) {
        bool sum = A[i] ^ B[i] ^ acarreo;
        acarreo = (A[i] & B[i]) | (acarreo & (A[i] ^ B[i]));
        result[i] = sum;
    }
    return result;
}

bitset<MAX_BITS> binarySub(bitset<MAX_BITS> A, bitset<MAX_BITS> B, int bits) {
    B.flip();
    B = binarySum(B, bitset<MAX_BITS>(1), bits);
    return binarySum(A, B, bits);
}

void arithmeticShift(bitset<MAX_BITS>& A, bitset<MAX_BITS>& Q, bool& Q_1, int bits) {
    bool msbA = A[bits - 1];
    Q_1 = Q[0];
    Q >>= 1;
    Q[bits - 1] = A[0];
    A >>= 1;
    A[bits - 1] = msbA;
}

void printBits(bitset<MAX_BITS> bits, int n) {
    for (int i = n - 1; i >= 0; --i) {
        cout << bits[i];
    }
}

void boothAlgorithm(int multiplicand, int multiplier, int bits) {
    bitset<MAX_BITS> M = decimalToBinary(multiplicand, bits);
    bitset<MAX_BITS> A;
    bitset<MAX_BITS> Q = decimalToBinary(multiplier, bits);
    bool Q_1 = 0;
    int count = bits;

    cout << "Inicializando:\n";
    cout << "A: "; printBits(A, bits); cout << "\n";
    cout << "Q: "; printBits(Q, bits); cout << "\n";
    cout << "Q-1: " << Q_1 << "\n";

    while (count > 0) {
        int Q0_Q1 = Q[0] * 2 + Q_1;
        if (Q0_Q1 == 2) {
            A = binarySub(A, M, bits);
        } else if (Q0_Q1 == 1) {
            A = binarySum(A, M, bits);
        }

        arithmeticShift(A, Q, Q_1, bits);
        count--;

        cout << "\nPaso con count = " << count << ":\n";
        cout << "A: "; printBits(A, bits); cout << "\n";
        cout << "Q: "; printBits(Q, bits); cout << "\n";
        cout << "Q-1: " << Q_1 << "\n";
    }

    cout << "\nResultado final en binario (A + Q):\n";
    printBits(A, bits);
    printBits(Q, bits);
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
