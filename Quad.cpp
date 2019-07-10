//
// Created by pooja on 28/06/19.
//

#include <cmath>
#include "Quad.h"

/**
 * default constructor taking four parameters of type long long int
 * creates an object of Quad class
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

  //TODO check x2 != 0 and x4 != 0
  if (quadNumbers[1] == 0) {
    quadNumbers[1] = 1;
  }
  if (quadNumbers[3] == 0) {
    quadNumbers[3] = 1;
  }
  //the quad must be standardized
  standardize();

}

/**
 * Function to standardize the supplied quad numbers
 * */
void Quad::standardize() {
  reduce();
  normalize();
}

/**
 * Function to reduce the supplied quad numbers
 * It uses the user defined gcd method
 * */
void Quad::reduce() {
  auto gcd1 = gcd(quadNumbers[0], quadNumbers[1]);
  auto gcd2 = gcd(quadNumbers[2], quadNumbers[3]);
//  cout<<gcd1<<'\t'<<gcd2<<endl;

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
 * Method to normalize the quad numbers     */
void Quad::normalize() {
  if (quadNumbers[1] < 0 && quadNumbers[3] < 0) {// if x4 < 0 AND x2 < 0
    //[-x1,-x2,-x3,-x4]
    /*   -quadNumbers[0];
       -quadNumbers[2];*/
    quadNumbers[0] = -quadNumbers[0];
    //quadNumbers[1] = -quadNumbers[1];
    quadNumbers[2] = -quadNumbers[2];
    //quadNumbers[3] = -quadNumbers[3];
  } else if (quadNumbers[1] < 0) {// if x2 < 0
    //[-x1,-x2,x3,x4]
    quadNumbers[0] = -quadNumbers[0];
    quadNumbers[1] = -quadNumbers[1];
  } else if (quadNumbers[3] < 0) {// if x4 < 0
    //[x1,x2,-x3,-x4]
    quadNumbers[2] = -quadNumbers[2];
    quadNumbers[3] = -quadNumbers[3];
  }
}

bool Quad::isSimilar(const Quad &y) const {
  //TRUE if x1y2=y1x2 and x3y4=y3x4
  return (quadNumbers[0] * y.quadNumbers[1] == quadNumbers[1] * y.quadNumbers[0]) &&
         (quadNumbers[2] * y.quadNumbers[3] == quadNumbers[3] * y.quadNumbers[2]);
}

bool Quad::isSimilar(const long long int &k) const {
  Quad q(k);
  return this->isSimilar(q);
}


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
 * function norm returns the floating point number
 * */

double Quad::norm() {
  double norm=0.0;
  long long int x1 = quadNumbers[0], x2 = quadNumbers[1], x3 = quadNumbers[2], x4 = quadNumbers[3];
  double a, b, c, d;
  a = x1 * x1;
  b = x2 * x2;
  c = x3 * x3;
  d = x4 * x4;
  norm = (a / b) + (c / d);
//  cout << "x1" << endl;
  return norm;
}

/**
 * overload function for subscript operator
 * */
long long int &Quad::operator[](int index) {


  if (index<1 || index>4 ) throw std::invalid_argument ("index out of bounds");
  return quadNumbers[(index - 1) % SIZE];
}

/**
 * overload function for subscript operator for const values
 * It uses the getter for quad number
 * */
const long long int &Quad::operator[](int index) const {
  if (index<0 || index>3 ) throw std::invalid_argument ("index out of bounds");
  return getQuadNumbers(index % SIZE);
}

Quad &Quad::operator+=(const Quad &rhs) {
//TODO yet to check implementation
  quadNumbers[0] = (quadNumbers[0] * rhs.quadNumbers[1] + quadNumbers[1] * rhs.quadNumbers[0]);//x1y2 + x2y1
  quadNumbers[1] = (quadNumbers[1] * rhs.quadNumbers[1]);//x2y2
  quadNumbers[2] = (quadNumbers[2] * rhs.quadNumbers[3] + quadNumbers[3] * rhs.quadNumbers[2]);//x3y4 + x4y3
  quadNumbers[3] = (quadNumbers[3] * rhs.quadNumbers[3]);//x4y4
  reduce();
  return *this;
}

Quad &Quad::operator-=(const Quad &rhs) {
  quadNumbers[0] = (quadNumbers[0] * rhs.quadNumbers[1] - quadNumbers[1] * rhs.quadNumbers[0]);//x1y2 + x2y1
  quadNumbers[1] = (quadNumbers[1] * rhs.quadNumbers[1]);//x2y2
  quadNumbers[2] = (quadNumbers[2] * rhs.quadNumbers[3] - quadNumbers[3] * rhs.quadNumbers[2]);//x3y4 + x4y3
  quadNumbers[3] = (quadNumbers[3] * rhs.quadNumbers[3]);//x4y4
  return *this;
}

Quad &Quad::operator*=(const Quad &rhs) {
  /*cout<<*this<<" *= called"<<endl;
  cout<<"my quad is :"<<rhs.quadNumbers[0]<<" "<<rhs.quadNumbers[1] <<" "<<rhs.quadNumbers[2]<<" "<<rhs.quadNumbers[3]<<endl;*/
  long long int x1 = quadNumbers[0], x2 = quadNumbers[1], x3 = quadNumbers[2], x4 = quadNumbers[3];
  long long int y1 = rhs.quadNumbers[0], y2 = rhs.quadNumbers[1], y3 = rhs.quadNumbers[2], y4 = rhs.quadNumbers[3];
  quadNumbers[0] = x1 * y1 * x4 * y4 + (2 * x3 * y3 * x2 * y2);
  quadNumbers[1] = x2 * y2 * x4 * y4;
  quadNumbers[2] = (x1 * y3 * y2 * x4) + (x3 * y1 * x2 * y4);
  quadNumbers[3] = x4 * y4 * x2 * y2;
  return *this;
}
/*
Quad &Quad::operator*=(const long long int &k) {
  cout<<"Scalr *= called"<<endl;
  long long int x1 = quadNumbers[0], x2 = quadNumbers[1], x3 = quadNumbers[2], x4 = quadNumbers[3];
  quadNumbers[0] = x1 * k;
  quadNumbers[1] = x2 ;
  quadNumbers[2] = x3 * k;
  quadNumbers[3] = x4;
  return *this;
}
*/


Quad &Quad::operator/=(const Quad &rhs) {
  //x/y=x*y
 // Quad temp = rhs;
  Quad y = rhs.inverse();
  *this = *this * y;
  return *this;
}

/**
 * Free function : binary plus operator ( x + y )
 * @param lhs a const reference of Quad object as operand one( x )
 * @param rhs a const reference of Quad object which is to be added to lhs ( y )
 * @return  current quad object reference
 * */
Quad operator+(const Quad &lhs, const Quad &rhs) {
  Quad temp=lhs;
  temp += rhs;
//  cout<<lhs<<" + "<<rhs <<" = "<<temp<<endl;
  /*temp[0]=(temp[0] * rhs[1] + temp[1] * rhs[0]);//x1y2 + x2y1
  temp[1] = (temp[1] * rhs[1]);//x2y2
  temp[2] = (temp[2] * rhs[3] + temp[3] * rhs[2]);//x3y4 + x4y3
  temp[3] = (temp[3] * rhs[3]);//x4y4*/
  //cout<<"binary + called \t"<< temp;

  temp.reduce();
  return temp;
}

/**
 * Free function : binary minus operator ( x - y )
 * @param lhs a const reference of Quad object as operand one( x )
 * @param rhs a const reference of Quad object which is to be subtracted from lhs ( y )
 * @return  current quad object reference
 * */
Quad operator-(const Quad &lhs, const Quad &rhs) {
  // cout << "binary -op called \n";
  Quad temp{lhs};
  temp -= rhs;
  temp.reduce();
  return temp;
}

Quad operator*(const Quad &lhs, const Quad &rhs) {
  Quad temp=lhs;
  temp *= rhs;
  temp.reduce();
  return temp;
}

/*Quad Quad::operator*(const long long int& k) const {
  // x * k =k * x
  Quad temp=*this;
  //cout<<"my temp :"<<temp[1]<<" "<<temp[2] <<" "<<temp[3]<<" "<<temp[4]<<endl;
 // cout<<temp<<" when k= "<<k<<endl;
  temp[1] = temp[1] * k;
  temp[3] = temp[3] * k;
  //cout<<temp<<" after multiplying *= "<<k<<endl;
 // temp.reduce();
  return temp;
}*/

/**
 * Basic arithmetic operator /  : works as QUAD op QUAD
 * does not modify the operands
 * @return return reference of quad  object to allow chaining
 * */
Quad operator/(const Quad& lhs, const Quad& rhs) {
  Quad temp{lhs};
  temp /= rhs;
  temp.reduce();
  temp.standardize();
  return temp;
}

/**
 * Basic arithmetic operator /  : works as INT op QUAD
 * does not modify the operands*/
Quad operator/(long long int k, const Quad &x) {
  //  k/x = k*x.inverse
  Quad temp = x.inverse();
  //cout<<"inverse x is ="<<temp <<" to be multiplied with "<<k<< endl;
  temp *=k;
  //cout<<"output"<<temp<<endl;
  return temp;
}
/**
 * Basic arithmetic operator /  : works as QUAD op INT
 * does not modify the operands*/
Quad Quad::operator/(const long long int &k) {
  Quad temp=*this;
  Quad quadK(1,k);
  //quadK[0]=1; quadK[1]=k; quadK[2]=0; quadK[3]=1;

  temp = temp * quadK;
 // cout<<"temp ="<<*this <<" * "<<quadK<< endl;
  temp.standardize();
//  cout<<"'temp ="<<temp << endl;
  return temp;
}
/**
 * unary minus operator
 * @return  current quad object
 * */
Quad Quad::operator-() {
  quadNumbers[0] = -quadNumbers[0];
  quadNumbers[2] = -quadNumbers[2];
  return *this;
}

/**
 * unary plus operator
 * @return  current quad object
 * */
Quad Quad::operator+() {
  quadNumbers[0] = +quadNumbers[0];
  quadNumbers[1] = +quadNumbers[1];
  quadNumbers[2] = +quadNumbers[2];
  quadNumbers[3] = +quadNumbers[3];
  reduce();
  return *this;
}

//getter for quadNumber array(container)
const long long int &Quad::getQuadNumbers(size_t index) const {
  return quadNumbers[index];
}

//setter for quadNumber array(container)
void Quad::setQuadNumbers(size_t index, long long int value) {
  quadNumbers[index] = value;
}

bool operator==(const Quad &quad1, const Quad &quad2) {
  //x==y iff x1=y1,x2=y2,x3=y3,x4=y4
//  cout << "compare : " << quad1 << " \t and \t " << quad2 << '\n';
  return ((quad1.getQuadNumbers(0) == quad2.getQuadNumbers(0)) &&
          (quad1.getQuadNumbers(1) == quad2.getQuadNumbers(1)) &&
          (quad1.getQuadNumbers(2) == quad2.getQuadNumbers(2)) &&
          (quad1.getQuadNumbers(3) == quad2.getQuadNumbers(3)));
}

bool operator!=(const Quad &quad1, const Quad &quad2) {
  return !(quad1 == quad2);
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
 * overloads in-stream operator >>
 * accepts the user input into the object of Quad class
 * @param in in-stream object reference
 * @param quad Quad class object reference
 * @return in-stream object reference
 * */
istream &operator>>(istream &in, Quad &quad) {
  //delete [] line.linePtr;//empty the previous object
  cout<<"About to create the Qua [a, b, c ,d]\nEnter Four numbers a, b, c, d in that order:\n";
  in >> quad.quadNumbers[0] >> quad.quadNumbers[1] >> quad.quadNumbers[2] >> quad.quadNumbers[3];
  return in;
}

Quad operator*(long long int k, const Quad &x) {
  // x * k =k * x
  Quad temp=x;
  //cout<<"my temp :"<<temp[1]<<" "<<temp[2] <<" "<<temp[3]<<" "<<temp[4]<<endl;
  // cout<<temp<<" when k= "<<k<<endl;
  temp[1] = temp[1] * k;
  temp[3] = temp[3] * k;
  //cout<<temp<<" after multiplying *= "<<k<<endl;
   temp.reduce();
  return temp;
}

Quad operator^(const Quad &lhs, const int &k) {
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

bool operator<(const Quad &lhs, const Quad& rhs) {
  Quad x{lhs}, y{rhs};
  return (x.norm() < y.norm());
}

bool operator>(const Quad &lhs, const Quad& rhs) {
  Quad x{lhs}, y{rhs};
  return !(x<y);
}

bool operator>=(const Quad &lhs, const Quad &rhs) {
  Quad x{lhs}, y{rhs};
  return (x>y || x==y);
}

bool operator<=(const Quad &lhs, const Quad &rhs) {
  Quad x{lhs}, y{rhs};
  return (x<y || x==y);
}

Quad& Quad::operator+(const long long int &k) const {
  Quad temp{*this};
  temp+=Quad{k};
  cout<<"my scalar additon temp"<<temp <<endl;
  return temp;
}

double Quad::absoluteValue() {
  return sqrt(this->norm());
}

double Quad::operator()() const {
  Quad temp{*this};
  return temp.absoluteValue();
}

Quad Quad::conjugate() const {
  Quad temp=*this;
  if(temp[2]!=0 && temp[4]!=0){
    temp[3]=-temp[3];
  }
  return temp;
}

Quad& Quad::operator++() {
  //++*this;
  *this+=1;
  return *this;
}

Quad Quad::operator++(int) {
  Quad temp{*this};
  ++(*this);
  return temp;
}

Quad &Quad::operator--() {
  *this-=1;
  return *this;
}

Quad Quad::operator--(int) {
  Quad temp{*this};
  --(*this);
  return temp;
}
/*
Quad::operator double() const{
  Quad temp{*this};
  return temp.norm();
}*/




