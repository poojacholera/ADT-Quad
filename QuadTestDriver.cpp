#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cassert>
#include "Quad.h"
using std::cout;
using std::endl;

/*
Tests class Quad. Specifically, tests constructors, compound assignment
operator overloads, basic arithmetic operator overloads, unary +, unary -,
pre/post-increment/decrement, subscripts, function objects, 
input/output operators, isSimilar, absValue, and equality relational operators.

@return 0 to indicate success.
*/
auto print(const std::string item, const Quad& q)
{
  cout << std::left << std::setw(20) << item << q << endl;
}
auto main() -> int
{
  //cout << "sizeof(long long int) = " <<  sizeof(long long int) << '\n';
  //cout << "Minimum value for long long int: "
  //<< std::numeric_limits<long long int>::min() << '\n';
  //cout << "Maximum value for long long int: "
  // << std::numeric_limits<long long int>::max() << '\n';
  //Minimum value for 8-byte long long int: -9223372036854775808
  //Maximum value for 8-byte long long int : 9223372036854775807

  Quad zero; // defaluts to the zero quad [0,1,0,1]
  print("Quad zero", zero);
  assert(zero == Quad(0,1,0,1));

  Quad one(1);  //  [1,1,0,1]
  print("Quad identity(1)", one);
  assert(one == Quad(1, 1, 0, 1));

  Quad half(1,2);  //  [1,2,0,1]
  print("Quad half(1,2)", half);
  assert(half == Quad(1, 2, 0, 1));

  Quad q0;
  print("Quad q0", q0);
  assert(q0 == zero);

  Quad q1(2); // defaluts to the zero quad [2,1,0,1]
  print("Quad q1(2)", q1);
  assert(q1 == Quad(2, 1, 0, 1));

  Quad q2(2,3); // defaluts to [2,3,0,1]
  print("Quad q2(2,3)", q2);
  assert(q2 == Quad(2, 3, 0, 1));

  Quad q3(2, 3, 4); // defaluts to [2,3,4,1]
  print("Quad q3(2,3,4)", q3);
  assert(q3 == Quad(2, 3, 4, 1));

  Quad q4(2, 3, 4, 5); //  [2,3,4,5]
  print("Quad q4(2, 3, 4, 5)", q4);
  assert(q4 == Quad(2, 3, 4, 5));

  assert(q0 + one == one);
  assert(q0 * one == zero);
  assert(one * one == one);
  assert(one + one == Quad(2));
  assert(Quad(2) - one == one);
  assert(Quad(1, 2).isSimilar(Quad(10, 20)));
  assert(Quad(1, 2) == Quad(10, 20)); // Quad's ctor always standardizes the constructed quad
  assert(Quad(1, 2) == Quad(1, 2));

  Quad q11(100, -100, -1000, -1000);
  print("q11", q11);
  assert(q11 == Quad(-1, 1, 1, 1));
  q11[1] = 1;
  assert(q11 == Quad(1, 1, 1, 1));
  Quad q23(10, 5, 6, 2);
  assert(q23 == Quad(2,1,3,1));
  Quad q22{ q23 - Quad(0,10,10,10) };
  assert(q22 == Quad(2, 1, 2, 1));
  assert(q22 - q11 == q23 - q22 + one);

  // additions and subtractions
  Quad q01234 = q0 + q1 + q2 + q3 + q4;
  print("q01234", q01234);
  Quad qs01234 = -q0 - q1 - q2 - q3 - q4;
  print("qs01234", qs01234);
  assert(q01234 == -qs01234);
  Quad m01234 = 5LL * q0 + 4LL*q1 + 3LL*q2 + 2LL * q3 + 1LL * q4;
  print("m01234", m01234);
  Quad n01234 = q0 * 5LL + q1 * 4LL + q2 * 3LL +  q3 * 2LL + q4 * 1LL;
  print("n01234", n01234);
  assert(m01234 == n01234);

  // multiplications, division
  Quad qm1234 = q1 * q2 * q3 * q4;
  print("qm1234", qm1234);
  Quad qmr1234 = q4 * q3 * q2 * q1;
  print("qmr1234", qmr1234);
  assert(qm1234 / q4 / q1 == (q3/3LL + q3 / 3LL + q3 / 3LL) * (q2/ 2LL + q2 / 2LL));

  cout << setw(20) << "q4.norm() = " << q4.norm() << endl;
  double  size_of_q4 = q4; // quad to double ( not double to quad! )
  cout << setw(20) << "size of q4 = " <<  size_of_q4 << endl;
  cout << setw(20) << "conjugate of q4 = " <<  q4.conjugate() << endl;

  Quad q5{ qmr1234 }; //
  print("Quad q5{ qmr1234 }", q5);

  // inverse
  Quad q5_inverse{ q5.inverse() };
  print("Quad q5_inverse", q5_inverse);
  assert(q5_inverse * q5 == one);
  assert(q5 == one / q5_inverse);
  assert(q5_inverse == one / q5);

  // operator []
  Quad q6{};
  q6[1] = 10;
  q6[2] = -20;
  q6[3] = 0;
  q6[4] = 40;
  print("q6", q6);
  q6.normalize();
  print("q6 normalized", q6);
  q6.reduce();
  print("q6 reduced", q6);

  //operator ++, --, both versions
  ++q6;
  print("++q6", q6);
  q6 += half;
  print("q6 += half", q6);
  assert(q6 == one);
  q6++;
  print("q6++", q6);
  assert(q6 == one + one);
  q6--;
  print("q6--", q6);
  assert(q6 == one);
  --q6;
  print("--q6", q6);
  assert(q6 == zero);

  // operator ^ to raise a quad to a positive integer power
  Quad q7{ half };
  print("q7", q7);
  q7 = half ^ 1;
  print("q7 = half ^ 1", q7);
  q7 = half ^ 2;
  print("q7 = half ^ 2", q7);
  q7 = half ^ 3;
  print("q7 = half ^ 3", q7);
  q7 = half ^ 4;
  print("q7 = half ^ 4", q7);
  q7 = half ^ 5;
  print("q7 = half ^ 5", q7);

  // operator >>
  Quad input_quad{};
  cin >> input_quad;
  print("input_quad", input_quad);

  // operator ^ to raise a quad to a positive integer power
  Quad q8{};
  print("q8", q8);
  q8 = input_quad ^ 1;
  print("q8 = input_quad ^ 1", q8);
  q8 = input_quad ^ 2;
  print("q8 = input_quad ^ 2", q8);
  q8 = input_quad ^ 3;
  print("q8 = input_quad ^ 3", q8);
  q8 = input_quad ^ 4;
  print("q8 = input_quad ^ 4", q8);
  q8 = input_quad ^ 5;
  print("q8 = input_quad ^ 5", q8);

  // operator ^ to raise a quad to a negative integer power
  Quad q9{};
  print("q9", q9);
  q9 = input_quad ^ (-1);
  print("q9 = input_quad ^ (-1)", q9);
  q9 = input_quad ^ (-2);
  print("q9 = input_quad ^ (-2)", q9);
  q9 = input_quad ^ (-3);
  print("q9 = input_quad ^ (-3)", q9);
  q9 = input_quad ^ (-4);
  print("q9 = input_quad ^ (-4)", q9);
  q9 = input_quad ^ (-5);
  print("q9 = input_quad ^ (-5)", q9);

  assert(q8 * q9 == one);

  cout << "Test completed successfully!" << endl;
  return 0;
}