// credits go to https://codereview.stackexchange.com/a/30675

#include <vector>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

const std::vector<std::string> first14 = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen" };
const std::vector<std::string> prefixes = {"twen", "thir", "for", "fif", "six", "seven", "eigh", "nine"};


std::string inttostr( const unsigned int number )
{
    if( number <= 14 )
    {
      return first14.at(number);
    }
    if( number < 20 )
    {
      return prefixes.at(number-12) + "teen";
    }
    if( number < 100 )
    {
      unsigned int remainder = number - (static_cast<int>(number/10)*10);
      return prefixes.at(number/10-2) + (0 != remainder ? "ty " + inttostr(remainder) : "ty");
    }
    if( number < 1000 )
    {
      unsigned int remainder = number - (static_cast<int>(number/100)*100);
      return first14.at(number/100) + (0 != remainder ? " hundred " + inttostr(remainder) : " hundred");
    }
    if( number < 1000000 )
    {
      unsigned int thousands = static_cast<int>(number/1000);
      unsigned int remainder = number - (thousands*1000);
      return inttostr(thousands) + (0 != remainder ? " thousand " + inttostr(remainder) : " thousand");
    }
    if( number < 1000000000 )
    {
      unsigned int millions = static_cast<int>(number/1000000);
      unsigned int remainder = number - (millions*1000000);
      return inttostr(millions) + (0 != remainder ? " million " + inttostr(remainder) : " million");
    }

    throw std::out_of_range("inttostr() value too large");
}

/*
 * Function that generates an str->int map
 */
std::unordered_map<std::string, int> generateStrToNrMap(int max_nr)
{
  std::unordered_map<std::string, int> str_int_map;
  for (int i=0; i<=max_nr; i++)
  {
    str_int_map[inttostr(i)] = i;
  }

  return str_int_map;
}

int main()
{
  auto str_to_nr_map = generateStrToNrMap(999999);

  /*
   * Reverse conversion
   */
  std::string ns_1 = "thirty five";
  std::cout << "The number is: " << str_to_nr_map[ns_1] << std::endl;

  return 0;
}
