#include <iostream>
#include <cstdlib>
#include <time.h>

#include <beatflower/BeatFlower.h>

using namespace bf;


int main(int argc, char** argv) {
  int nReturnvalue = EXIT_FAILURE;
  
  BeatFlower bfDemo("/dev/ttyUSB0");
  
  if(bfDemo.connect()) {
    std::cout << "Connected" << std::endl;
    
    bfDemo.setMicroSecondsDelay(1000);
    
    while(true) {
      for(unsigned int unR = 0; unR < 5; ++unR) {
	bfDemo.selectRing(unR);
	
	for(unsigned int unI = 0; unI < 12; ++unI) {
	  bfDemo.setLEDColor(unI, rand() % 25, rand() % 25, rand() % 25);
	  
	  bfDemo.commit();
	  usleep(5000);
	}
      }
    }
    
    std::cout << "Done" << std::endl;
    
    nReturnvalue = EXIT_SUCCESS;
  } else {
    std::cout << "Unable to connect" << std::endl;
  }
  
  return nReturnvalue;
}
