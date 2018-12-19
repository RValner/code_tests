/*
 * This code tests the scope of namespaces.
 * 
 * Lessons learned: dont use "using" directive in .h files or inside
 * namespace declarations, things will get ugly (see line 47)
 * 
 * References: https://stackoverflow.com/a/6175850/8068769
 */

#include <iostream>

namespace component
{
  struct RawData
  {
    RawData(int a, int b)
    : a_(a)
    , b_(b)
    {}

    void printData()
    {
      std::cout << a_ << " " << b_ << std::endl;
    }

    int a_;
    int b_;
  };
}

namespace root
{
using namespace component;    // Bad design

  struct ProcessedData
  {
    ProcessedData(int number)
    : a_(number, number)
    {}

    RawData a_;    
  };
}

int main()
{
  root::ProcessedData pd(5);
  pd.a_.printData();

  root::RawData rd(3, 3);    // Legitimate and confusing
  rd.printData();

  return 0;
}
