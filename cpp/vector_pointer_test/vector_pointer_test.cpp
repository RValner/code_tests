#include <iostream>
#include <vector>
#include <memory>
#include "boost/any.hpp"
#include <algorithm>    // std::find
 
int main()
{
  std::vector<int> v_ints;
  v_ints.push_back(0);
  v_ints.push_back(11);
  v_ints.push_back(22);
  v_ints.push_back(33);

  int* e_2_p = &v_ints[2];
  std::cout << *e_2_p << std::endl;
  v_ints.erase(v_ints.begin() + 2);
  std::cout << *e_2_p << std::endl;

  std::vector<std::shared_ptr<int>> v_shared_ints;
  v_shared_ints.push_back(std::make_shared<int>(44));
  v_shared_ints.push_back(std::make_shared<int>(55));
  v_shared_ints.push_back(std::make_shared<int>(66));
  v_shared_ints.push_back(std::make_shared<int>(77));

//  std::shared_ptr<int> e_2_sp = v_shared_ints[2];
//  std::cout << *e_2_sp << "; count = " << e_2_sp.use_count() << "; size = " << v_shared_ints.size() << std::endl;
//  v_shared_ints.erase(v_shared_ints.begin() + 2);
//  std::cout << *e_2_sp << "; count = " << e_2_sp.use_count() << "; size = " << v_shared_ints.size() << std::endl;

  {
    boost::any e_2_basp = boost::any_cast<std::shared_ptr<int>>(v_shared_ints[2]);
    std::shared_ptr<int> basp_2_e = boost::any_cast<std::shared_ptr<int>>(e_2_basp);

    std::cout << "value basp_2_e = " << *basp_2_e << "; count basp_2_e = " << basp_2_e.use_count() << std::endl;
    std::cout << "value si2 = " << *v_shared_ints[2] << "; count si2 = " << v_shared_ints[2].use_count() << std::endl;

    std::vector<std::shared_ptr<int>>::iterator it = std::find (v_shared_ints.begin(), 
                                                                v_shared_ints.end(), 
                                                                basp_2_e);

    v_shared_ints.erase(it);
    std::cout << "value basp_2_e = " << *basp_2_e << "; count basp_2_e = " << basp_2_e.use_count() << std::endl;
    std::cout << "value si2 = " << *v_shared_ints[2] << "; count si2 = " << v_shared_ints[2].use_count() << std::endl;
  }

  std::cout << "value = " << *v_shared_ints[2] << "; count = " << v_shared_ints[2].use_count() << std::endl;
  
  return 0;
}
