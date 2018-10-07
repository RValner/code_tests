#include <boost/any.hpp>
#include <iostream>

void someFunc(boost::any& ba)
{
  int a = 434;
  std::cout << "a = " << a << std::endl;

  boost::any ba_temp;
  ba_temp = boost::any_cast<int>(a);

  ba = ba_temp;

  std::cout << "ba int = " << boost::any_cast<int>(ba) << std::endl;
}

/*
 * Main
 */
int main()
{
  boost::any ba_1;

  someFunc(ba_1);

  std::cout << "ba_1 int = " << boost::any_cast<int>(ba_1) << std::endl;
 
  return 0;
} 
