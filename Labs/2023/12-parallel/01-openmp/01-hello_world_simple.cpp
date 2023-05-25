#include <omp.h>

#include <iostream>

int
main(int argc, char **argv)
{
  std::cout << "Hello World!" << std::endl;

  int n;
  int id;

#pragma omp parallel shared(n) private(id)
  {
    //computed by each thread
    id = omp_get_thread_num();

    //declared before
#pragma omp master //the next line is run only by one thread (which one is decided by openMP -> first available)
    n = omp_get_num_threads();

    // #pragma omp single amd #pragma openmp master are very similar, 
    // the only difference is that the theread that is preforming the op. is the master thread 

/*
#pragma omp critical //we're practical making our code serial. The following line is executed just by one thread at the time
    std::cout << "Hello World from " << id << " out of " << n << std::endl;
*/
#pragma omp barrier

//scheduling: 
//dynamic each iteration is assigned to the first available thread 
//static: work assigned to every thread before the loop

//we may want to specifiy the chunk size
#pragma omp for schedule(dynamic) 
    for(int i=0; i < n; i++){
#pragma omp critical
      std::cout << "Iteration " << i << " by thread " << id << std::endl;
    }

  }




  return 0;
}