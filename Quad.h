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
//public:
    static const int SIZE = 4;

    long long int gcd(const long long int &a, const long long int &b);
public:
    //virtual Quad()= default;
    Quad(const long long int &x1 = (long long int) 0, const long long int &x2 = (long long int) 1,
         const long long int &x3 = (long long int) 0, const long long int &x4 = (long long int) 1);//default constructor
    Quad(const Quad &)= default;//Default copy constructor
    virtual ~Quad() = default;// Defaulted destructor
    Quad& operator=(const Quad &rhs)= default;// defaulted copy assignment

    const long long int &getQuadNumbers(size_t index) const;
    void setQuadNumbers(size_t index, long long int value);

    Quad operator+();//unary operator +
    Quad operator-();//unary operator -
    Quad& operator--();//unary operator prefix --
    Quad operator--(int);//unary operator postfix --
    Quad& operator++();//unary operator prefix --
    Quad operator++(int);//unary operator postfix ++

    //compound assignment operator
    long long int& operator[](int index); //overload function for subscript operator
    const long long int& operator[](int index) const; //overload function for subscript operator for const values

    Quad& operator+=(const Quad& rhs);//compound operator +=
    Quad& operator-=(const Quad& rhs);//compound operator -=
    Quad& operator*=(const Quad& rhs);//compound operator *=
    Quad& operator/=(const Quad& rhs);//compound operator /=

    Quad& operator+(const long long int& k)const;//binary operator + for scalar addition//TODO check if ever used?
    Quad operator/(const long long int& k);//  scalar binary operator / : as QUAD op INT

    bool isSimilar(const long long int& k) const;
    void normalize();
    void standardize();
    void reduce();
    bool isSimilar(const Quad& y) const;
    Quad inverse() const;
    Quad conjugate() const;
    double norm();
    double operator()() const;
    double absoluteValue();

    friend ostream &operator<<(ostream &out, const Quad &quad); // Overloads operator << as a friend
    friend istream &operator>>(istream &in, Quad &quad); //Overloads operator>> as a friend
};
Quad operator+(const Quad& lhs, const Quad& rhs);//binary operator +
Quad operator-(const Quad& lhs, const Quad& rhs);//binary operator -
Quad operator*(const Quad& lhs, const Quad& rhs);//binary operator * : QUAD op QUAD
Quad operator*(long long int k,const Quad& x) ;// scalar binary operator *
Quad operator/(const Quad& lhs, const Quad& rhs);//binary operator / : as QUAD op QUAD
Quad operator/(long long int k, const Quad& x);// scalar binary operator / : as INT op QUAD
bool operator==(const Quad &quad1, const Quad &quad2); //free function
bool operator!=(const Quad &, const Quad &); // free function
bool operator<(const Quad& lhs,const Quad& rhs);
bool operator<=(const Quad& lhs,const Quad& rhs);
bool operator>(const Quad& lhs,const Quad& rhs);
bool operator>=(const Quad& lhs,const Quad& rhs);
Quad operator^(const Quad& lhs,const int & k);
#endif //A3_QUAD_H
