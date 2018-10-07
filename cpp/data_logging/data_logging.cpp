/*
 * This code tests data logging with buffering, which should
 * reduce the amount of system calls.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>

int main()
{
  std::ofstream log_stream_output("test_data_log.txt", std::ofstream::out);
  std::stringstream log_stream;
  const unsigned int log_buf_size = 10;
  unsigned int event_counter = 0;

  for (int i=0; i<100; i++)
  {
    log_stream << std::to_string(i) << " ";
    log_stream << std::to_string(i*10) << " ";
    log_stream << std::to_string(i*100) << "\n";

    if (event_counter >= log_buf_size)
    {
      log_stream_output << log_stream.str().c_str() << std::flush;
      log_stream.str( std::string() );
      log_stream.clear();
      event_counter = 0;

      std::cout << "logging ... " << i << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    else
    {
      event_counter++;
    }
  }  

  std::cout << "dun." << std::endl;

  log_stream_output.close();

  return 0;
}
