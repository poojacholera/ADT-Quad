//
// Created by pooja on 28/06/19.
//

#ifndef A3_QUAD_H
#define A3_QUAD_H

#include <iostream>
#include <array>

using namespace std;

class Quad {
private:
    array<long long int, 4> quadNumbers;
public:
    static const int SIZE = 4;

    const long long int &getQuadNumbers(size_t index) const;
    void setQuadNumbers(size_t index, long long int value);

    Quad& operator+(const Quad &rhs);//unary operator +
    Quad& operator-(const Quad &rhs);//unary operator -
    const Quad &operator=(const Quad &rhs);//copy assignment

    void standardize();
    void reduce();
    int gcd(const long long int &a, const long long int &b);
    void normalize();
    bool isSimilar(const long long int & k) const;
    bool isSimilar(const Quad& y) const;


public:
    Quad(const long long int &x1 = (long long int) 0, const long long int &x2 = (long long int) 1,
         const long long int &x3 = (long long int) 0, const long long int &x4 = (long long int) 1);//default constructor
    Quad(const Quad &);//copy constructor
    virtual ~Quad();//destructor
    //compound assignment operator

    friend ostream &operator<<(ostream &out, const Quad &quad); // Overloads operator << as a friend
    friend istream &operator>>(istream &in, Quad &quad); //Overloads operator>> as a friend
};

bool operator==(const Quad &quad1, const Quad &quad2); //free function
bool operator!=(const Quad &, const Quad &); // free function
#endif //A3_QUAD_H
