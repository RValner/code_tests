#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

struct Error
{
  int subsystem_;
  int code_;
  std::string prefix_;
  std::string message_;
};

typedef std::vector<Error> ErrorStack;

class ErrorHandler
{
public:
  ErrorHandler() = default;

  ErrorHandler(int subsystem, std::string log_group)
    : subsystem_(subsystem)
    , log_group_(log_group)
  {}

  void createAndThrow(int code, std::string prefix, std::string message)
  {
    ErrorStack e_st;
    Error error;

    error.subsystem_ = subsystem_;
    error.code_ = code;
    error.prefix_ = prefix;
    error.message_ = message;

    e_st.push_back(error);
    throw e_st;
  }

  void forwardAndThrow(ErrorStack& e, std::string prefix)
  {
    Error error;

    error.subsystem_ = subsystem_;
    error.code_ = 0;
    error.prefix_ = prefix;
    e.push_back(error);

    throw e;
  }

private:
  int subsystem_;
  std::string log_group_;
};

std::ostream& operator<<(std::ostream& out, const Error& e)
{
  out << std::endl;
  out << "* code: " << e.code_ << std::endl;
  out << "* subsystem: " << e.subsystem_ << std::endl;
  out << "* prefix: " << e.prefix_ << std::endl;
  out << "* message: " << e.message_ << std::endl;

  return out;
}

std::ostream& operator<<(std::ostream& out, const ErrorStack& e_st)
{
  for (auto& e : e_st)
  {
    out << e << std::endl;
  }

  return out;
}



/*
 * Base class
 */
class Base
{
public:
  Base(){}

  Base(Base& b)
    : b_pub_ (b.b_pub_)
    , b_proc_ (b.b_proc_)
    , b_priv_ (b.b_priv_)
    , SUBSYSTEM_ (b.SUBSYSTEM_)
    , log_group_(b.log_group_)
    , ERROR_HANDLER_ (ErrorHandler(b.SUBSYSTEM_, b.log_group_))
  {}

  int b_pub_ = 1;

protected:
  int b_proc_ = 2;
  std::string b_subsys_;
  std::string b_class_;
  int SUBSYSTEM_;
  std::string log_group_;
  ErrorHandler ERROR_HANDLER_;

  void base_initialize(Base* b)
  {
    b_pub_  = b->b_pub_;
    b_proc_ = b->b_proc_;
    b_priv_ = b->b_priv_;
    b_subsys_ = b->b_subsys_;
    SUBSYSTEM_ = b->SUBSYSTEM_;
    log_group_ = b->log_group_;
    ERROR_HANDLER_ = ErrorHandler(SUBSYSTEM_, log_group_);
  }

private:
  int b_priv_ = 3;
};

/*
 * Base2
 */
class Base2 : public Base
{
public:
  std::string b2_pub_str = "ello";

};

/*
 * Derived class 1 (INTERFACE)
 */
class Derived_1 : public Base
{
public:
  Derived_1()
  {
    b_class_ = __func__;
  }

  Derived_1(Base& b) : Base(b)
  {
    b_class_ = __func__;
  }

  void initialize (Base* b)
  {
    base_initialize(b);
    printProc();
  }

  void printProc()
  {
    std::cout << b_subsys_ << "/" << b_class_ << "::" << __func__ << " " << b_proc_ << std::endl;
  }

  void print_deriv_1_proc(Derived_1 &deriv_1_inst)
  {
    std::cout << deriv_1_inst.b_proc_ << std::endl; // Compiles
  }

  void brokenFunction()
  {
    int code = 101;
    std::string prefix = b_class_ + "::" + __func__;
    std::string message = "This is a test";

    ERROR_HANDLER_.createAndThrow(code, prefix, message);
  }

private:

};

/*
 * Derived class 2 (TASK)
 */
class Derived_2 : public Base2
{
public:
  Derived_2(int data, std::string subsys, int subsystem, std::string log_group)
  {
    b_proc_ = data;
    b_subsys_ = subsys;
    b_class_ = __func__;
    SUBSYSTEM_ = subsystem;
    log_group_ = log_group;
    ERROR_HANDLER_ = ErrorHandler(SUBSYSTEM_, log_group_);
  }

  void start()
  {
    d1_.initialize(this);
  }

  void printProc()
  {
    std::cout << b_subsys_ << "/" << b_class_ << "::" << __func__ << " " << b_proc_ << std::endl;
  }

  void brokenFunction()
  {
    try
    {
      d1_.brokenFunction();
    }
    catch(ErrorStack e)
    {
      // print out the error stack
      std::cout << e;
      // ERROR_HANDLER_.forwardAndThrow(e, prefix);
    }
  }

private:
  Derived_1 d1_;
};



/*
 * Main
 */
int main()
{
  Derived_2 d2(22, "subsystem_name", 1, "log_group");
  d2.start();
  d2.printProc();
  d2.brokenFunction();

  char char_array[] = {'t', 'e', 's', 't'};
  char char_array_2[] = "test2";
  char* char_array_3 = char_array;

  int* a = new int;

  char_array_3 = static_cast<char*>(a);

  std::cout << char_array << std::endl;
  std::cout << char_array_2 << std::endl;
  std::cout << char_array_3 << std::endl;
 
  return 0;
} 
