// steady_clock example
#include <iostream>
#include <chrono>
#include <ctime>

int main ()
{
  using namespace std::chrono;

  duration<int, std::milli> time_span;
  steady_clock::time_point t1 = steady_clock::now();
  steady_clock::time_point t2 = steady_clock::now();
  int compteur(1);

  while(compteur < 11)
  {
      std::cout << compteur << std::endl;
      t1 = steady_clock::now();
      time_span = duration_cast<duration<int, std::milli>>(t2 - t1);
      while(time_span.count() < 500)
      {
          t2 = steady_clock::now();
          time_span = duration_cast<milliseconds>(t2 - t1);  //milliseconds = typedef duration<int, std::milli> milliseconds;
      }
      compteur++;
  }
  return 0;
}
