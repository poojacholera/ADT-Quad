//
// Created by pooja on 28/06/19.
//

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
  if(quadNumbers[1] ==0){
    quadNumbers[1] = 1;
  }
  if(quadNumbers[3] ==0){
    quadNumbers[3] = 1;
  }
  //the quad must be standardized
  standardize();

}
Quad::Quad(const Quad & rhs) {
  cout<<"in copy ctor"<<endl;
  //TODO
}
void Quad::standardize() {
  reduce();
  normalize();
}
void Quad::reduce() {
  auto gcd1=gcd(quadNumbers[0],quadNumbers[1]);
  auto gcd2=gcd(quadNumbers[2],quadNumbers[3]);
//  cout<<gcd1<<'\t'<<gcd2<<endl;

  quadNumbers[0]=quadNumbers[0]/gcd1;
  quadNumbers[1]=quadNumbers[1]/gcd1;
  quadNumbers[2]=quadNumbers[2]/gcd2;
  quadNumbers[3]=quadNumbers[3]/gcd2;
}
/**
 * recursive function to find greatest common divisor (gcd)
 * such that, divisor d is divisible by a and b
 * any divisor of a and b is also a divisor of d
 * @param a non-zero integer, usually x1 or x3
 * @param b non-zero integer, usually x2 or x4
 * @return a positive integer (let say, d) is returned   */
int Quad::gcd(const long long int& a, const long long int& b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}
/**
 * Method to normalize the quad numbers*/
void Quad::normalize() {
  if(quadNumbers[1]<0 && quadNumbers[3]<0 ){// if x4 < 0 AND x2 < 0
    //[-x1,-x2,-x3,-x4]
    quadNumbers[0]=-quadNumbers[0];
    quadNumbers[1]=-quadNumbers[1];
    quadNumbers[2]=-quadNumbers[2];
    quadNumbers[3]=-quadNumbers[3];
  }else if(quadNumbers[1]<0){// if x2 < 0
    //[-x1,-x2,x3,x4]
    quadNumbers[0]=-quadNumbers[0];
    quadNumbers[1]=-quadNumbers[1];
  }else if(quadNumbers[3]<0){// if x4 < 0
    //[x1,x2,-x3,-x4]
    quadNumbers[2]=-quadNumbers[2];
    quadNumbers[3]=-quadNumbers[3];
  }
}
bool Quad::isSimilar(const Quad& y) const {
  //TRUE if x1y2=y1x2 and x3y4=y3x4
  return (quadNumbers[0]*y.quadNumbers[1]==quadNumbers[1]*y.quadNumbers[0])&&(quadNumbers[2]*y.quadNumbers[3]==quadNumbers[3]*y.quadNumbers[2]);
}
bool Quad::isSimilar(const long long int& k) const {
    Quad q(k);
 // cout<<q<<" is similar to: "<< *this;
  return this->isSimilar(q);
}

const Quad& Quad::operator=(const Quad &rhs) {
  cout<<"in copy assignment \n";
  //TODO
  if (this == &rhs) return *this;
  else {
  quadNumbers=rhs.quadNumbers;
  cout<<*this<<endl;
    /*while(!empty()){
      pop_back();
    }
    delete [] this->linePtr;
    this->linePtr=new char[rhs.getCapacity()]{'\0'};
    strcpy(this->linePtr,rhs.linePtr);
    this->capacity=rhs.getCapacity();
    this->lineLength=rhs.length();
  */
  }
  return *this;
}
Quad& Quad::operator-(const Quad& rhs) {
  cout<<"-op called \n";
  quadNumbers[0] = (quadNumbers[0] * rhs.quadNumbers[1] - quadNumbers[1] * rhs.quadNumbers[0]);//x1y2 + x2y1
  quadNumbers[1] = (quadNumbers[1] * rhs.quadNumbers[1]);//x2y2
  quadNumbers[2] = (quadNumbers[2] * rhs.quadNumbers[3] - quadNumbers[3] * rhs.quadNumbers[2]);//x3y4 + x4y3
  quadNumbers[3] = (quadNumbers[3] * rhs.quadNumbers[3]);//x4y4
  cout<<"subtracted"<<*this <<'\n';
  return *this;
}
/**
 * destructor*/
Quad::~Quad() {

 for(int i=0;i<4;i++)
    quadNumbers[i]=0;

  //delete this;

//  delete [] array<long long int,4>;
//  //linePtr= nullptr;
}
//getter for array(container)
const long long int &Quad::getQuadNumbers(size_t index) const {
  return quadNumbers[index];
}
//setter for array(container)
void Quad::setQuadNumbers(size_t index, long long int value) {
  quadNumbers[index] = value;
}

//Quad& Quad::operator+ (const Quad& rhs);
Quad& Quad::operator+(const Quad &rhs) {
  quadNumbers[0] = (quadNumbers[0] * rhs.quadNumbers[1] + quadNumbers[1] * rhs.quadNumbers[0]);//x1y2 + x2y1
  quadNumbers[1] = (quadNumbers[1] * rhs.quadNumbers[1]);//x2y2
  quadNumbers[2] = (quadNumbers[2] * rhs.quadNumbers[3] + quadNumbers[3] * rhs.quadNumbers[2]);//x3y4 + x4y3
  quadNumbers[3] = (quadNumbers[3] * rhs.quadNumbers[3]);//x4y4
  return *this;
}

bool operator==(const Quad &quad1, const Quad &quad2) {
  //x==y iff x1=y1,x2=y2,x3=y3,x4=y4
  //quad1.quadNumbers[0]==quad1.quadNumbers[0];
  cout<<"compare : "<<quad1<<" \t and \t "<<quad2<<'\n';
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
  in >> quad.quadNumbers[0] >> quad.quadNumbers[1] >> quad.quadNumbers[2] >> quad.quadNumbers[3];
  return in;
}
