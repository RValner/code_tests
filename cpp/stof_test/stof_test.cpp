#include <iostream>
#include <string>

/*
 * Main
 */
int main()
{
  std::string n1 = "three";
  std::string n2 = "3";

  try
  {
    float n1_f = std::stof(n1);
    std::cout << "n1_f = " << n1_f << std::endl;
  }
  catch(std::exception e)
  {
    std::cout << "Stuff went bad from n1:" << e.what() << std::endl;
  }

  try
  {
    float n2_f = std::stof(n2);
    std::cout << "n2_f = " << n2_f << std::endl;
  }
  catch(std::exception e)
  {
    std::cout << "Stuff went bad from n2: " << e.what() << std::endl;
  }

  return 0;
}
