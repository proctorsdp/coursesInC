//
//  BigInteger.cpp
//  Big Integer Part 1
//
//  Created by Steven Proctor on 2/8/16.
//  Copyright © 2016 Steven Proctor. All rights reserved.
//

#include"BigInteger.h"

BigInteger::BigInteger() {
    digits = NULL;      // Default constructor: storing nothing!
    size = 0;
    nDigits = 0;
}

BigInteger::~BigInteger() {
    if (digits != NULL) delete[] digits;
    digits = NULL;
    size = 0;
    nDigits = 0;
}

void BigInteger::init(int sizeIn) {
    // Task 1. Allocate memory for digits and fill them as zeros
    digits = new char [sizeIn];         //allocates memory for a bigInt of a given size
    for (int i = 0; i < sizeIn; i++) {      //fills the bigInt array with zeros
        digits[i] = 0;
    }
    size = sizeIn;      //resest the size of the array based on the size of the bigInt
}

void BigInteger::copy(const BigInteger &num) {
    size = num.size;            // copy digits array size
    nDigits = num.nDigits;      // copy number of digits
    digits = new char[size];                 // allocate a new digits array with the same size in num
    memcpy(digits, num.digits, size); // copy digits array
}

BigInteger::BigInteger(const BigInteger &num) { // Copy constructor
    copy(num);
}

BigInteger& BigInteger::operator=(const BigInteger &num) {
    if (this != &num) {             // not assign to the same object
        if (digits != NULL) delete[] digits;  // release current digits array
        copy(num);
    }
    return *this;
}


BigInteger::BigInteger(int val) {
    // Task 2a. Construct a BigInteger from an int value
    int tempVal = val;
    int nsize = 0;
    while (tempVal > 0) {
        tempVal = tempVal / 10;
        nsize++;
    }
    
    init(nsize);
    size = nsize;
    
    int i = 0;
    while (val > 0) {
        tempVal = val%10;
        setDigit(i, tempVal);
        val /=10;
        i++;
    }
}


BigInteger::BigInteger(string str) {
    // Task 2b. Construct a BigInteger from a string.
    int nsize = sizeof(str);
    
    init(nsize);
    size = nsize;
    
    for (int i = 0; i < nsize; i++) {    //Fills an array with the given input
        setDigit(i, str[nsize - 1 - i]);
    }
}


char BigInteger::getDigit(int pos) const {
    if (pos >= nDigits)
        return 0;
    else
        return digits[pos];
}

void BigInteger::setDigit(int pos, char digit) {
    if (pos >= size) {       // not enough space
        int newSize = 1;
        while (newSize <= pos) newSize *= 2; // compute newSize as a power of 2 that is bigger than pos
        
        char* temp = digits;    // store link to current digits
        
        digits = new char[newSize]; // allocate a new array
        memset(digits, 0, newSize); // and fill zeros
        
        if (temp != NULL)           // if there are some current digits
            memcpy(digits, temp, nDigits);        // copy them
        size = newSize;
    }
    
    digits[pos] = digit;    // put the given digit at position pos
    
    if (pos >= nDigits)      // update the number of digits!
        nDigits = pos + 1;
}

BigInteger multiply(BigInteger &x, int y) {     //multiply a bigInt by an int
    int pos = 0;
    int nx = x.numberOfDigits();
    BigInteger z;
    int carry = 0;
    for (int i = 0; i < nx; i++) {
        carry += x.getDigit(i) * y;
        z.setDigit(pos++, carry % 10);
        carry /= 10;
    }
    while (carry > 0) {
        z.setDigit(pos++, carry % 10);
        carry /= 10;
    }
    return z;
}

BigInteger operator*(BigInteger &x, BigInteger &y) {        //multiply a bigInt by a BigInt
    int pos = 0;
    int nx, ny, nz;
    nx = x.numberOfDigits();
    ny = y.numberOfDigits();
    BigInteger z;
    int carry = 0;
    for (int j = 0; j < ny; j++) {
        pos = j;
        for (int i = 0; i < nx; i++) {
            carry += x.getDigit(i) * y.getDigit(j);
            if (carry > 9) {
                int tempPos = pos;
                while (carry > 0) {
                    z.setDigit(tempPos, (z.getDigit(tempPos) + (carry % 10)));
                    carry /= 10;
                    tempPos++;
                }
            }
            else {
                z.setDigit(pos, (z.getDigit(pos) + (carry % 10)));
            }
            nz = z.numberOfDigits();
            for (int i = 0; i < nz; i++) {
                if (z.getDigit(i) > 9) {
                    int temp = z.getDigit(i);
                    z.setDigit(i, (temp % 10));
                    temp /= 10;
                    z.setDigit(i+1, (z.getDigit(i+1) + temp));
                }
            }
            carry /= 10;
            pos++;
        }
    }
    while (carry > 0) {
        z.setDigit(pos++, carry % 10);
        carry /= 10;
    }
    return z;
}

BigInteger operator+(BigInteger &x, BigInteger &y) {        //adds two BigInts together
    int pos = 0;
    int nx;
    if (x.numberOfDigits() > y.numberOfDigits()) {
        nx = x.numberOfDigits();
    }
    else{
        nx = y.numberOfDigits();
    }
    BigInteger z;
    int carry = 0;
    for (int i = 0; i < nx; i++) {
        carry += x.getDigit(i) + y.getDigit(i);
        z.setDigit(pos++, carry % 10);
        carry /= 10;
    }
    while (carry > 0) {
        z.setDigit(pos++, carry % 10);
        carry /= 10;
    }
    return z;
}

bool operator==(BigInteger &x, BigInteger &y) {     //Is BigInt 'a' equal to BigInt 'b'?
    bool check = false;
    int nx;
    if (x.numberOfDigits() == y.numberOfDigits()) {
        nx = x.numberOfDigits();
        check = true;
        for (int i = nx - 1; i > -1; i--) {
            if (x.getDigit(i) != y.getDigit(i)){
                check = false;
                break;
            }
        }
    }
    return check;
}

bool operator!=(BigInteger &x, BigInteger &y) {     //Is BigInt 'a' not equal BigInt 'b'?
    bool check = false;
    int nx;
    if (x.numberOfDigits() > y.numberOfDigits()) {
        check = true;
    }
    else if (y.numberOfDigits() > x.numberOfDigits()){
        check = true;
    }
    else {
        nx = x.numberOfDigits();
        for (int i = nx - 1; i > -1; i--) {
            if (x.getDigit(i) != y.getDigit(i)){
                check = true;
                break;
            }
        }
    }
    return check;
}

bool operator<(BigInteger &x, BigInteger &y) {      //Is BigInt 'a' smaller than BigInt 'b'?
    bool check = false;
    int nx = x.numberOfDigits();
    if (x.numberOfDigits() < y.numberOfDigits()) {
        check = true;
    }
    else {
        for (int i = nx - 1; i > -1; i--) {
            if (x.getDigit(i) < y.getDigit(i)) {
                check = true;
                break;
            }
        }
    }
    return check;
}

bool operator>(BigInteger &x, BigInteger &y) {      //Is BigInt 'a' bigger than BigInt 'b'?
    bool check = false;
    int nx = x.numberOfDigits();
    if (x.numberOfDigits() > y.numberOfDigits()) {
        check = true;
    }
    else {
        for (int i = nx - 1; i >= 0; i--) {
            if (x.getDigit(i) > y.getDigit(i)){
                check = true;
                break;
            }
        }
    }
    return check;
}

void BigInteger::print(bool debug) {        //prints a BigInt
    if (digits == NULL)
        cout << '0';
    else
        for (int i = nDigits; --i >= 0;)
            cout << (int) digits[i];
    if (debug)
        printf(" [digits = %s, size = %d, nDigits = %d] ", digits, size, nDigits);
}

ostream& operator<<(ostream& out, BigInteger num) {
    //Task 3. Overload operattor << to write a BigInteger object to screen
    num.print(false);
    
    return out;
}
