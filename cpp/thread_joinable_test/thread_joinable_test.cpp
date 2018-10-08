#include <iostream>
#include <future>


template<typename T>
bool future_is_ready(std::future<T>& t)
{
  return t.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
}

void task_1(int sec)
{
  for(int i=0; i<sec; i++)
  {
    std::cout << "sleep: " << i << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

int main()
{
  std::future<void> foo = std::async(std::launch::async, task_1, 2);  
 
  while(true)
  {
    if(future_is_ready(foo))
    {
      std::cout << "the thread has finished" << std::endl;    
    }
    else
    {
      std::cout << "the thread has not finished" << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }


//  std::thread task_thread(task_1);
//  
//  while(true)
//  {
//    if(task_thread.joinable())
//    {
//      std::cout << "the thread is joinable" << std::endl;
//      task_thread.join();    
//    }
//    else
//    {
//      std::cout << "the thread is not joinable" << std::endl;
//    }

//    std::this_thread::sleep_for(std::chrono::milliseconds(500));
//  }
  
}
