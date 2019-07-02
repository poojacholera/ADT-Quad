#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cassert>
#include "Quad.h"
using std::cout;
using std::endl;

auto print(const std::string item, const Quad& q)
{
  cout << std::left << std::setw(20) << item << q << endl;
}
auto main() -> int{

  assert(Quad(2).isSimilar(2));
//  assert(Quad(1, 2) == Quad(10, 20)); // Quad's ctor always standardizes the constructed quad
//  assert(Quad(1, 2) == Quad(1, 2));

  return 0;
}