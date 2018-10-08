/*
 * LESSON LEARNED: do not start any threads in the constructor of the object
 * if the thread is accessing its data, and dont start threads right after 
 * construction an object that the thread is about to use
 */


#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>

class DataStruct
{
public:
  DataStruct()
  {
    data_v_.push_back(0);
  }

  void addData(int worker_id)
  {
    std::lock_guard<std::mutex> guard(data_mutex_);

    std::cout << "worker " << worker_id << std::endl;
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));

    int data = data_v_.back();
    data_v_.push_back(++data);
  }

  void print() const
  {
    std::cout << "size of data_v: " << data_v_.size() << std::endl;
    for (auto& data : data_v_)
    {
      std::cout << data << std::endl;     
    }
  }

private:
  std::vector<int> data_v_;
  mutable std::mutex data_mutex_;
};


class Worker
{
public:
  Worker(DataStruct* data, int worker_id)
  : data_(data)
  , worker_id_(worker_id)
  {} 

  void startWorking()
  {
    thread_ = std::thread(&Worker::doSomeWork, this);
  }

  void doSomeWork()
  {
    data_->addData(worker_id_);
  }

  void join()
  {
    thread_.join();
  }
  
private:
  DataStruct* data_;
  int worker_id_;
  std::thread thread_;
};


int main()
{
  DataStruct data_struct;
  std::vector<std::thread> threads;
  std::vector<Worker> workers;
  int nr_of_workers = 100;  
  
  // Create the workers
  std::cout << "constructing " << nr_of_workers << " workers" << std::endl;
 
  for (int i=0; i<nr_of_workers; i++)
  {
    //std::cout << i << std::endl;

    workers.emplace_back(&data_struct, i);
    //std::cout << "d0" << std::endl;
  }

  // Start the threads
  std::cout << "starting the worker threads" << std::endl;

  for (auto& worker : workers)
  {
    worker.startWorking();    
  }
  
  // Join the threads
  std::cout << "joining the worker threads" << std::endl;

  for (auto& worker : workers)
  {
    worker.join();  
  }

  std::cout << "printing out the data" << std::endl;
  data_struct.print();

  return 0;
}
