//
// Created by pooja on 28/06/19.
//

#ifndef A3_QUAD_H
#define A3_QUAD_H

#include <iostream>
#include <array>
#include <stdexcept>      // std::invalid_argument

using namespace std;


class Quad {
private:
    array<long long int, 4> quadNumbers;
    static const int SIZE = 4;

    long long int gcd(const long long int &a, const long long int &b);

public:
    Quad(const long long int &x1 = (long long int) 0, const long long int &x2 = (long long int) 1,
         const long long int &x3 = (long long int) 0, const long long int &x4 = (long long int) 1);//default constructor
    Quad(const Quad &) = default;//Default copy constructor
    virtual ~Quad() = default;// Defaulted destructor
    Quad &operator=(const Quad &rhs) = default;// defaulted copy assignment

    const long long int &getQuadNumbers(size_t index) const;

    void setQuadNumbers(size_t index, long long int value);

    Quad operator+();// unary operator +
    Quad operator-();// unary operator -
    Quad &operator--();// unary operator prefix --
    Quad operator--(int);// unary operator postfix --
    Quad &operator++();// unary operator prefix --
    Quad operator++(int);// unary operator postfix ++

    //compound assignment operator
    long long int &operator[](int index); // overload function for subscript operator
    const long long int &operator[](int index) const; // overload function for subscript operator for const values

    Quad &operator+=(const Quad &rhs);// compound operator +=
    Quad &operator-=(const Quad &rhs);// compound operator -=
    Quad &operator*=(const Quad &rhs);// compound operator *=
    Quad &operator/=(const Quad &rhs);// compound operator /=

    bool isSimilar(const long long int &k) const;//
    bool isSimilar(const Quad &y) const;

    void normalize();

    void standardize();

    void reduce();

    Quad inverse() const;

    Quad conjugate() const;

    double norm();

    operator double() const;
    double operator()() const;

    double absoluteValue();

    friend ostream &operator<<(ostream &out, const Quad &quad); // Overloads operator << as a friend
    friend istream &operator>>(istream &in, Quad &quad); //Overloads operator>> as a friend
};
// free functions (non-member functions)
//basic arithmetic operators
const Quad operator+(const Quad &lhs, const Quad &rhs);//binary operator + : QUAD op QUAD addition
const Quad operator+(const Quad &lhs, const long long int &k);// binary operator + for scalar addition : QUAD op INT
const Quad operator+(const long long int &k, const Quad &lhs);// binary operator + for scalar addition : INT op QUAD

const Quad operator-(const Quad &lhs, const Quad &rhs);//binary operator - for QUAD subtraction
const Quad operator-(const Quad &lhs, const long long int &k);//binary operator - for scalar subtraction : QUAD op INT
const Quad operator-(const long long int &k, const Quad &rhs);//binary operator - for scalar subtraction : INT op QUAD

const Quad operator*(const Quad &lhs, const Quad &rhs);//binary operator * for multiplication : QUAD op QUAD
const Quad operator*(const Quad &x, const long long int& k);// scalar binary operator * : QUAD op INT multiplication
const Quad operator*(const long long int &k, const Quad &x);//binary operator * for INT op QUAD multiplication

const Quad operator/(const Quad &lhs, const Quad &rhs);//binary operator / : QUAD op QUAD Division
const Quad operator/(const Quad &x, const long long int& k);// scalar binary operator / : as QUAD op INT  Scalar Division
const Quad operator/(const long long int& k, const Quad &x);// scalar binary operator / : as INT op QUAD Scalar Division

// Relational operators
bool operator==(const Quad &quad1, const Quad &quad2); // Quad comparison
bool operator==(const Quad &quad1, const long long int& k); //Quad comparison
bool operator==(const long long int& k, const Quad &quad2); //Quad comparison

bool operator!=(const Quad &, const Quad &);
bool operator!=(const Quad &, const long long int& k);
bool operator!=(const long long int& k, const Quad &);

bool operator<(const Quad &lhs, const Quad &rhs);
bool operator<(const Quad &lhs, const long long int& k);
bool operator<(const long long int& k, const Quad &rhs);

bool operator>(const Quad &lhs, const Quad &rhs);
bool operator>(const Quad &lhs, const long long int& k);
bool operator>(const long long int& k, const Quad &rhs);

bool operator>=(const Quad &lhs, const Quad &rhs);
bool operator>=(const Quad &lhs, const long long int& k);
bool operator>=(const long long int& k, const Quad &rhs);

bool operator<=(const Quad &lhs, const Quad &rhs);
bool operator<=(const Quad &lhs, const long long int& k);
bool operator<=(const long long int& k, const Quad &rhs);
//XOR operator
const Quad operator^(const Quad &lhs, const int &k);// used here as power-of operator
#endif //A3_QUAD_H
