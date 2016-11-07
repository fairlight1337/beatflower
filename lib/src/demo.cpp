/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2016, Jan Winkler.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/** \author Jan Winkler */


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
