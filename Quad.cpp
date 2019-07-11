//
// Created by pooja on 28/06/19.
//

#include <cmath>
#include "Quad.h"

/**
 * default constructor taking four parameters of type long long int
 * creates an object of Quad class
 * uses function standardize()
 * default values assigned are converted from 32-bit int to 64-bit long long int
 * @param x1 first element of array container, default is 0
 * @param x2 second element of array container, default is 1
 * @param x3 third element of array container, default is 0
 * @param x4 fourth element of array container, default is 1
 * */
Quad::Quad(const long long int &x1, const long long int &x2, const long long int &x3, const long long int &x4) {

  //assign the quad numbers
  quadNumbers[0] = x1;
  quadNumbers[1] = x2;
  quadNumbers[2] = x3;
  quadNumbers[3] = x4;
  try{
    if (quadNumbers[1] == 0 || quadNumbers[3] == 0) {
     // quadNumbers[1] = 1;
     throw std::underflow_error ("x2 and x4 cannot be assigned zero");
    }
  }catch(std::underflow_error ue) {
    std::cerr << "underflow_error: " << ue.what() << '\n';
  }
  //the quad must be standardized
  standardize();
}
/**
 * Function to standardize the supplied quad numbers
 * this reuses the functions reduce() and normalize()
 * */
void Quad::standardize() {
  reduce();
  normalize();
}
/**
 * Function to reduce the supplied quad numbers
 * used to reduce the possibility of integer overflow
 * It uses the user-defined function @private gcd()
 * */
void Quad::reduce() {
  auto gcd1 = gcd(quadNumbers[0], quadNumbers[1]);
  auto gcd2 = gcd(quadNumbers[2], quadNumbers[3]);
  quadNumbers[0] = quadNumbers[0] / gcd1;
  quadNumbers[1] = quadNumbers[1] / gcd1;
  quadNumbers[2] = quadNumbers[2] / gcd2;
  quadNumbers[3] = quadNumbers[3] / gcd2;
  normalize();
}
/**
 * recursive function to find Greatest Common Divisor (gcd)
 * such that, divisor d is divisible by a and b
 * any divisor of a and b is also a divisor of d
 * @param a non-zero integer, usually x1 or x3
 * @param b non-zero integer, usually x2 or x4
 * @return a positive integer (let say, d) is returned   */
long long int Quad::gcd(const long long int &a, const long long int &b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}
/**
 * member method to normalize the quad numbers
 * Quad objects are normalized so that the quad numbers remain positive
 * */
void Quad::normalize() {
  if (quadNumbers[1] < 0 && quadNumbers[3] < 0) {// if x4 < 0 AND x2 < 0
    // then [-x1,x2,-x3,x4]
    quadNumbers[0] = -quadNumbers[0];
    quadNumbers[2] = -quadNumbers[2];
  } else if (quadNumbers[1] < 0) {// if x2 < 0
    // then [-x1,-x2,x3,x4]
    quadNumbers[0] = -quadNumbers[0];
    quadNumbers[1] = -quadNumbers[1];
  } else if (quadNumbers[3] < 0) {// if x4 < 0
    // then [x1,x2,-x3,-x4]
    quadNumbers[2] = -quadNumbers[2];
    quadNumbers[3] = -quadNumbers[3];
  }
}
/**
 * isSimilar :  member function returns true  if object X is similar to object Y
 * @param y     supplied object Y to be compared with current object X
 * @return bool     returns result false if current object X is not similar to the supplied object Y
 * */
bool Quad::isSimilar(const Quad &y) const {
  //TRUE if x1y2=y1x2 and x3y4=y3x4
  return (quadNumbers[0] * y.quadNumbers[1] == quadNumbers[1] * y.quadNumbers[0]) &&
         (quadNumbers[2] * y.quadNumbers[3] == quadNumbers[3] * y.quadNumbers[2]);
}
/**
 * isSimilar : member function returns true  if X is similar to Quad(k)
 * isSimilar(const Quad &y)  is used
 * @param k    the supplied int to compare with current object X
 * @return bool  returns result  false if x is not similar to Quad
 * */
bool Quad::isSimilar(const long long int &k) const {
  //Quad q(k);
  return this->isSimilar(Quad(k));
}
/**
 *  inverse() : inverse the Quad object
 *  uses @public standardize to reduce possibility of integer overflow  and normalize to keep x2 and x4 positive
 *  @return Quad : returns object Quad
 * */
Quad Quad::inverse() const {
  Quad temp;
  long long int x1 = quadNumbers[0], x2 = quadNumbers[1], x3 = quadNumbers[2], x4 = quadNumbers[3];
  long long int alpha = (((x1 * x1) * (x4 * x4)) - (2 * (x2 * x2) * (x3 * x3)));
  if (alpha != 0) {
    temp[1] = x1 * x2 * x4 * x4;
    temp[2] = alpha;
    temp[3] = -(x2 * x2 * x3 * x4);
    temp[4] = alpha;
  } else cout << "alpha = " << alpha << endl;
  temp.standardize();
  return temp;
}
/**
 * norm() : function norm returns the double
 * @return double : double value is returned
 * */
double Quad::norm() {
  double norm=0.0;
  long long int x1 = quadNumbers[0], x2 = quadNumbers[1], x3 = quadNumbers[2], x4 = quadNumbers[3];
  double a, b, c, d;
  //a = x1 * x1;
  a = x1 * x1;
  b = x2 * x2;
  c = x3 * x3;
  d = x4 * x4;
  norm = (a / b) + (c / d);
  return norm;
}
/**
 * operator[] : overload function for subscript operator
 * if index is out of bound throws exception
 * @return long long int& : returns reference of quad number at supplied index
 * */
long long int& Quad::operator[](int index) {
  try {
    if (index<1 || index>4 ) throw std::invalid_argument ("index out of bounds");
  }catch (const std::invalid_argument& ia) {
    std::cerr << "Invalid argument: " << ia.what() << '\n';
  }
  return quadNumbers[(index - 1) % SIZE];
}
/**
 * operator[] : overload function for subscript operator for const values
 * It uses the getter for quad number
 * if index is out of bound throws exception
 * @return const long long int& : returns reference of const quad number at supplied index
 * */
const long long int &Quad::operator[](int index) const {
 try{
   if (index<0 || index>3 ) throw std::invalid_argument ("index out of bounds");
  }catch (const std::invalid_argument& ia) {
    std::cerr << "Invalid argument: " << ia.what() << '\n';
  }
  return getQuadNumbers(index % SIZE);
}
/**
 * operator+= : overload function for operator +=
 * uses function reduce() : reduces the possibility of integer overflow
 * @param rhs : a read-only reference of object
 * @return Quad& : modifies the current object returns reference of object
 * */
Quad& Quad::operator+=(const Quad &rhs) {
  quadNumbers[0] = (quadNumbers[0] * rhs.quadNumbers[1] + quadNumbers[1] * rhs.quadNumbers[0]);//x1y2 + x2y1
  quadNumbers[1] = (quadNumbers[1] * rhs.quadNumbers[1]);//x2y2
  quadNumbers[2] = (quadNumbers[2] * rhs.quadNumbers[3] + quadNumbers[3] * rhs.quadNumbers[2]);//x3y4 + x4y3
  quadNumbers[3] = (quadNumbers[3] * rhs.quadNumbers[3]);//x4y4
  reduce();
  return *this;
}
/**
 * operator-= : overload function for operator -=
 * uses function reduce() : reduces the possibility of integer overflow
 * @param rhs : a read-only reference of object
 * @return Quad& : modifies the current object returns reference of object
 * */
Quad& Quad::operator-=(const Quad &rhs) {
  quadNumbers[0] = (quadNumbers[0] * rhs.quadNumbers[1] - quadNumbers[1] * rhs.quadNumbers[0]);//x1y2 + x2y1
  quadNumbers[1] = (quadNumbers[1] * rhs.quadNumbers[1]);//x2y2
  quadNumbers[2] = (quadNumbers[2] * rhs.quadNumbers[3] - quadNumbers[3] * rhs.quadNumbers[2]);//x3y4 + x4y3
  quadNumbers[3] = (quadNumbers[3] * rhs.quadNumbers[3]);//x4y4
  return *this;
}
/**
 * operator*= : overload function for operator *=
 * uses function reduce() : reduces the possibility of integer overflow
 * @param rhs : a read-only reference of object
 * @return Quad& : modifies the current object returns reference of object
 * */
Quad& Quad::operator*=(const Quad &rhs) {
  long long int x1 = quadNumbers[0], x2 = quadNumbers[1], x3 = quadNumbers[2], x4 = quadNumbers[3];
  long long int y1 = rhs.quadNumbers[0], y2 = rhs.quadNumbers[1], y3 = rhs.quadNumbers[2], y4 = rhs.quadNumbers[3];
  quadNumbers[0] = x1 * y1 * x4 * y4 + (2 * x3 * y3 * x2 * y2);
  quadNumbers[1] = x2 * y2 * x4 * y4;
  quadNumbers[2] = (x1 * y3 * y2 * x4) + (x3 * y1 * x2 * y4);
  quadNumbers[3] = x4 * y4 * x2 * y2;
  reduce();
  return *this;
}
/**
 * operator/= : overload function for operator /=
 * @param rhs : a read-only reference of object
 * @return Quad& : modifies the current object returns reference of object
 * */
Quad& Quad::operator/=(const Quad &rhs) {
  //x/y=x*y
  Quad y = rhs.inverse();
  *this = *this * y;
  return *this;
}
/**
 * Free function : binary plus operator ( x + y )
 * does not modify operands
 * @param lhs a const reference of Quad object as operand one( x )
 * @param rhs a const reference of Quad object which is to be added to lhs ( y )
 * @return  quad object
 * */
const Quad operator+(const Quad &lhs, const Quad &rhs) {
  Quad temp=lhs;
  temp += rhs;
  temp.reduce();
  return temp;
}
/**
 * operator+(x,k) : scalar addition of Quad object to supplied INT
 * does not modify operands
 * @param lhs a const reference of Quad object as operand one
 * @param k a const reference of long long int which is to be added to lhs
 * @return  const quad object
 * */
const Quad operator+(const Quad &lhs, const long long int &k) {
  //x+k
  cout<<"x + k : is called";
  Quad temp{ lhs };
  temp += Quad(k);
  return temp;
}
/**
 * operator+(k,x) :
 * does not modify operands
 * @param k a const reference of long long int which is to be added to rhs
 * @param rhs a const reference of Quad object as operand one
 * @return  const quad object
 * */
const Quad operator+(const long long int &k, const Quad &rhs) {
  //(k+x) = +(x+k)
  cout<<"k + x : is called";
  Quad temp{ rhs };
  temp=temp+k;
  return temp;
}
/**
 * Free function : binary minus operator ( x - y )
 * does not modify operands
 * @param lhs a const reference of Quad object as operand one( x )
 * @param rhs a const reference of Quad object which is to be subtracted from lhs ( y )
 * @return  quad object
 * */
const Quad operator-(const Quad &lhs, const Quad &rhs) {
  Quad temp{lhs};
  temp -= rhs;
  temp.reduce();
  return temp;
}
/**
 * Free function : binary minus operator ( x * y ) : QUAD op QUAD
 * does not modify operands
 * @param lhs a const reference of Quad object as operand one( x )
 * @param rhs a const reference of Quad object which is to be multiplied to lhs ( y )
 * @return  Quad object
 * */
const Quad operator*(const Quad &lhs, const Quad &rhs) {
  Quad temp=lhs;
  temp *= rhs;
  temp.reduce();
  return temp;
}
/**
 * operator*(const Quad &x, long long int k) : scalar binary operator * : QUAD op INT
 * uses operator *= for QUAD op QUAD
 * @param x a const reference of Quad object as operand one( x )
 * @param k long long int k is supplied for scalar multiplication
 * @return  Quad object
 * */
const Quad operator*(const Quad &x, const long long int& k) {
  // x * k
  Quad temp{x};
  //temp[1] = k * temp[1];
  temp[1] *= k;
  temp[3] *= k;
  return temp;
}
/**
 * operator*(long long int k, const Quad &x) : scalar binary operator * : INT op QUAD
 * uses operator * for QUAD op INT  as x * k =k * x
 * @param k long long int k is supplied for scalar multiplication
 * @param x a const reference of Quad object as operand one( x )
 * @return  Quad object
 * */
const Quad operator*(const long long int& k, const Quad &x) {
  // x * k =k * x
  Quad temp=x;
  temp[1] = temp[1] * k;
  temp[3] = temp[3] * k;
  temp.reduce();
  return temp;
}
/**
 * converts the Quad object to double
 * */
Quad::operator double() const {
  Quad temp{*this};
  return temp.absoluteValue();
}
/**
 * operator() : a function object  changes the Quad objects int functions
 * @return double
 * */
double Quad::operator()() const{
  Quad temp{*this};
  /*0.0;*/
  return temp.absoluteValue();
}
/**
 * Basic arithmetic operator /  : works as QUAD op QUAD
 * does not modify the operands
 * @param lhs a const reference of Quad object as operand
 * @param rhs a const reference of Quad object rhs which is to be divided by lhs
 * @return  Quad object
 * */
const Quad operator/(const Quad& lhs, const Quad& rhs) {
  Quad temp{lhs};
  temp /= rhs;
  temp.reduce();
  temp.standardize();
  return temp;
}
/**
 * Basic arithmetic operator /  : works as INT op QUAD ( k / x )
 * does not modify the operands
 * @param k long long int as numerator operand
 * @param x a const reference of Quad object which is denominator
 * @return  Quad object
 * */
const Quad operator/(const long long int& k, const Quad &x) {
  //  k/x = k*x.inverse
  Quad temp = x.inverse();
  temp *= k;
  return temp;
}
/**
 * Basic arithmetic operator /  : works as INT op QUAD ( x / k )
 * does not modify the operands
 * @param x a const reference of Quad object which is numerator
 * @param k long long int as denominator operand
 * @return  Quad object
 * */
const Quad operator/(const Quad &x, const long long int& k) {
  //x/k=k*x.inverse();
  Quad temp{x};
  Quad quadK(1,k);
  temp *= quadK;
  temp.standardize();
  return temp;
}
/**
 * operator-() : unary minus operator
 * @return  copy of current quad object
 * */
Quad Quad::operator-() {
  quadNumbers[0] = -quadNumbers[0];
  quadNumbers[2] = -quadNumbers[2];
  return *this;
}
/**
 * operator+() : unary plus operator
 * @return  copy of current quad object
 * */
Quad Quad::operator+() {
  quadNumbers[0] = +quadNumbers[0];
  quadNumbers[1] = +quadNumbers[1];
  quadNumbers[2] = +quadNumbers[2];
  quadNumbers[3] = +quadNumbers[3];
  reduce();
  return *this;
}
/**
 * getQuadNumbers(size_t index) : getter method for quadNumbers array(container)
 * does not modify members
 * @param index supplied index for the quadNumbers array
 * @return const long long int&  : reference of quadNumbers at supplied index
 * */
const long long int &Quad::getQuadNumbers(size_t index) const {
  return quadNumbers[index];
}
/**
 * setQuadNumbers(size_t index, long long int value) : setter method for quadNumbers array(container)
 * does not modify members
 * sets the supplied value at given index in quadNumbers array.
 * */
void Quad::setQuadNumbers(size_t index, long long int value) {
  quadNumbers[index] = value;
}

/**
 * absoluteValue() : square root of norm of Quad object x
 * uses the function norm()
 * @return double
 * */
double Quad::absoluteValue() {
  return sqrt(this->norm());
}

/**
 *conjugate() : creates a conjugate of current object
 * @return copy of Quad object
 * */
Quad Quad::conjugate() const {
  Quad temp=*this;
  if(temp[2]!=0 && temp[4]!=0){
    temp[3]=-temp[3];
  }
  return temp;
}
/**
 * operator++() : prefix increment
 * @return reference current Quad object
 * */
Quad& Quad::operator++() {
  //++*this;
  *this+=1;
  return *this;
}
/**
 * operator++(int) : postfix increment operator
 * @param int : dummy int parameter
 * @return old copy of current Quad object
 * */
Quad Quad::operator++(int) {
  Quad temp{*this};
  ++(*this);
  return temp;
}
/**
 * operator--() : prefix decrement operator--
 * @return reference current Quad object
 * */
Quad& Quad::operator--() {
  *this-=1;
  return *this;
}
/**
 * operator--(int) : postfix decrement operator
 * @param int : dummy int parameter
 * @return old copy of current Quad object
 * */
Quad Quad::operator--(int) {
  Quad temp{*this};
  --(*this);
  return temp;
}

/**
 * operator==  : compare the supplied two Quad objects
 * x==y iff x1=y1,x2=y2,x3=y3,x4=y4
 * @param quad1 Quad object on lhs
 * @param quad2 Quad object on rhs
 * @return bool
 * */
bool operator==(const Quad &quad1, const Quad &quad2) {
  //x==y iff x1=y1,x2=y2,x3=y3,x4=y4
//  cout << "compare : " << quad1 << " \t and \t " << quad2 << '\n';
  return ((quad1.getQuadNumbers(0) == quad2.getQuadNumbers(0)) &&
          (quad1.getQuadNumbers(1) == quad2.getQuadNumbers(1)) &&
          (quad1.getQuadNumbers(2) == quad2.getQuadNumbers(2)) &&
          (quad1.getQuadNumbers(3) == quad2.getQuadNumbers(3)));
}
/**
 * operator==  : compare the supplied int and Quad object
 * k==x
 * uses operator== (Quad, Quad)
 * @param k  const reference of supplied long long int
 * @param rhs Quad object on rhs
 * @return bool
 * */
bool operator==(const long long int &k, const Quad &rhs) {
  return Quad(k)==rhs;
}
/**
 * operator==  : compare the supplied Quad object and int
 * x==k
 * uses operator== (long long int, Quad)
 * @param lhs Quad object on lhs
 * @param k  const reference of supplied long long int
 * @return bool
 * */
bool operator==(const Quad &lhs, const long long int &k) {
  return k==lhs;
}
/**
 * operator!=  : compare the supplied two Quad objects
 * uses operator== (Quad, Quad)
 * @param quad1 Quad object on lhs
 * @param quad2 Quad object on rhs
 * @return bool
 * */
bool operator!=(const Quad &quad1, const Quad &quad2) {
  return !(quad1 == quad2);
}
/**
 * operator!=  : compare the supplied two Quad objects
 * uses operator!= (Quad, Quad)
 * @param k  const reference of supplied long long int
 * @param rhs Quad object on rhs
 * @return bool
 * */
bool operator!=(const long long int &k, const Quad& rhs) {
  return Quad(k)!=rhs;
}
/**
 * operator!=  : compare the supplied two Quad objects
 * uses operator!= (long long int, Quad)
 * @param lhs Quad object on lhs
 * @param k  const reference of supplied long long int
 * @return bool
 * */
bool operator!=(const Quad & lhs, const long long int &k) {
  return k!=lhs;
}
/**
 * overloads out-stream operator <<
 * it prints the object of Quad class
 * @param out out-stream object reference
 * @param quad const object reference of Quad class
 * @return out-stream object reference
 * */
ostream &operator<<(ostream &out, const Quad &quad) {
  out << "[" << quad.quadNumbers[0] << ", " << quad.quadNumbers[1] << ", " << quad.quadNumbers[2] << ", "
      << quad.quadNumbers[3] << "]";
  return out;
}
/**
 * overloads in-stream operator >> (friend function)
 * accepts the user input into the object of Quad class
 * @param in in-stream object reference
 * @param quad Quad class object reference
 * @return in-stream object reference
 * */
istream &operator>>(istream &in, Quad &quad) {
  do{
    try {
      cout << "About to create the Quad [a, b, c ,d]\nEnter four numbers a, b, c, d in that order:\n";
      in >> quad.quadNumbers[0] >> quad.quadNumbers[1] >> quad.quadNumbers[2] >> quad.quadNumbers[3];
      if (quad.quadNumbers[1] == 0 || quad.quadNumbers[3] == 0) {
        throw std::underflow_error ("x2 and x4 cannot be assigned zero");
      }
    }catch(std::underflow_error ue){
      std::cerr << "underflow_error: " << ue.what() << '\n';
      in.clear();
    }
  }while (quad.quadNumbers[1] == 0 || quad.quadNumbers[3] == 0);
  return in;
}
/**
 * operator<(Quad, Quad) : checks if the lhs Quad object is less than rhs
 * @param lhs   supplied Quad object to be compared
 * @param rhs   supplied Quad object to be compared
 * @return bool returns true if lhs is less than rhs
 * */
bool operator<(const Quad &lhs, const Quad& rhs) {
  Quad x{lhs}, y{rhs};
  return (x.norm() < y.norm());
}
/**
 * operator<(int, Quad) : checks if the k is less than Quad object rhs
 * uses operator<(Quad, Quad)
 * @param k     supplied long long int into be compared
 * @param rhs   supplied Quad object to be compared
 * @return bool returns true if k is less than rhs
 * */
bool operator<(const long long int &k, const Quad &rhs) {
  return (Quad(k) < rhs);
}
/**
 * operator<(Quad, int) : checks if the lhs Quad object is less than k
 * * uses operator<(Quad, Quad)
 * @param lhs   supplied Quad object to be compared
 * @param k     supplied long long int into be compared
 * @return bool returns true if lhs is less than k
 * */
bool operator<(const Quad &lhs, const long long int &k) {
  return (lhs < Quad(k));
  //return !(k >= x);
}
/**
 * operator>(Quad, Quad) : checks if the lhs Quad object is greater than rhs
 * uses operator<=(Quad, Quad)
 * @param lhs   supplied Quad object to be compared
 * @param rhs   supplied Quad object to be compared
 * @return bool returns true if lhs is greater than rhs
 * */
bool operator>(const Quad &lhs, const Quad& rhs) {
  return !(lhs<=rhs);
}
/**
 * operator>(int, Quad) : checks if the k is greater than Quad object rhs
 * uses operator>(Quad, Quad)
 * @param k     supplied long long int into be compared
 * @param rhs   supplied Quad object to be compared
 * @return bool returns true if k is greater than rhs
 * */
bool operator>(const long long int &k, const Quad &rhs) {
  return (Quad(k) > rhs);
  //return !(k<=rhs);
}
/**
 * operator>(Quad, int) : checks if the lhs Quad object is greater than k
 * uses operator>(Quad, Quad)
 * @param lhs   supplied Quad object to be compared
 * @param k     supplied long long int into be compared
 * @return bool returns true if lhs is greater than k
 * */
bool operator>(const Quad &lhs, const long long int &k) {
  return (lhs>Quad(k));
  //return !(lhs<=k);
}
/**
 * operator>=(Quad, Quad) : checks if the lhs Quad object is greater than or equal to rhs
 * uses operator>(Quad, Quad)  and  operator==(Quad, Quad)
 * @param lhs   supplied Quad object to be compared
 * @param rhs   supplied Quad object to be compared
 * @return bool returns true if lhs is greater than or equal to rhs
 * */
bool operator>=(const Quad &lhs, const Quad &rhs) {
  Quad x{lhs}, y{rhs};
  return (x>y || x==y);
}
/**
 * operator>=(Quad, int) : checks if the lhs Quad object is greater than or equal to k
 * uses operator>=(Quad, Quad)
 * @param lhs   supplied Quad object to be compared
 * @param k     supplied long long int into be compared
 * @return bool returns true if lhs is greater than or equal to  k
 * */
bool operator>=(const Quad &lhs, const long long int &k) {
  return (lhs >= Quad(k));
}
/**
 * operator>=(int, Quad) : checks if the k Quad object is greater than or equal to rhs
 * uses operator<(int, Quad)
 * @param k     supplied long long int into be compared
 * @param rhs   supplied Quad object to be compared
 * @return bool returns true if k is greater than or equal to  rhs
 * */
bool operator>=(const long long int &k, const Quad &rhs) {
  return !(k<rhs);
}
/**
 * operator<=(Quad, Quad) : checks if the lhs Quad object is less than or equal to rhs
 * uses operator>(Quad, Quad)
 * @param lhs   supplied Quad object to be compared
 * @param rhs   supplied Quad object to be compared
 * @return bool returns true if lhs is less than or equal to rhs
 * */
bool operator<=(const Quad &lhs, const Quad &rhs) {
  return !(lhs>rhs);
}
/**
 * operator<=(int, Quad) : checks if the k is less than or equal to Quad object rhs
 * uses operator>(int, Quad)
 * @param k     supplied long long int into be compared
 * @param rhs   supplied Quad object to be compared
 * @return bool returns true if k is less than or equal to  rhs
 * */
bool operator<=(const long long int &k, const Quad &rhs) {
  return !(k>rhs);
}
/**
 * operator<=(Quad, int) : checks if the lhs Quad object is less than or equal to k
 * uses operator>(Quad, int)
 * @param lhs   supplied Quad object to be compared
 * @param k     supplied long long int into be compared
 * @return bool returns true if lhs is less than or equal to  k
 * */
bool operator<=(const Quad &lhs, const long long int &k) {
  return !(lhs>k);
}
/**
 * operator^ : used here as power of
 * does not modify operands
 * x^k
 * @param lhs   supplied Quad object to be compared
 * @param k     supplied int as power to the Quad object
 * @retun the quad resulting from raising x to the power k(an int)
 * */
const Quad operator^(const Quad &lhs, const int &k) {
  Quad temp{lhs};
  if (k > 1){
    for(size_t i=2;i<=k;i++){
      temp*=lhs;
      temp.standardize();
    }
  } else if(k<0){
    for(signed int i=0;i>=k;i--){
      temp/=lhs;
      temp.standardize();
    }
  }
  temp.standardize();
  return temp;
}


