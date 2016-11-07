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


#include <beatflower/BeatFlower.h>


namespace bf {
  BeatFlower::BeatFlower(std::string strTTY, unsigned int unRings, unsigned int unLEDsPerRing)
    : m_strTTY(strTTY), m_unRings(unRings), m_unLEDsPerRing(unLEDsPerRing), m_unMicroSecondsDelay(0) {
  }
  
  BeatFlower::~BeatFlower() {
    this->disconnect();
  }
  
  void BeatFlower::setMicroSecondsDelay(unsigned int unMicroSecondsDelay) {
    m_unMicroSecondsDelay = unMicroSecondsDelay;
  }
  
  bool BeatFlower::connect(std::string strTTY) {
    this->disconnect();
    
    if(strTTY != "") {
      m_strTTY = strTTY;
    }
    
    if(m_strTTY != "") {
      m_nFD = open(m_strTTY.c_str(), O_WRONLY | O_NOCTTY);
      
      if(m_nFD > -1) {
	struct termios tsOptions;
	
	cfsetispeed(&tsOptions, B9600);
	cfsetospeed(&tsOptions, B9600); // Really only needed for output
	
	cfmakeraw(&tsOptions);
	tsOptions.c_cflag |= (CLOCAL);    // Set local mode
	tsOptions.c_cflag &= ~CSTOPB;     // 1 stop bit
	tsOptions.c_cflag &= ~CRTSCTS;    // Disable hardware flow control
	
	tcsetattr(m_nFD, TCSANOW, &tsOptions);
	
	return true;
      }
    }
    
    return false;
  }
  
  bool BeatFlower::disconnect() {
    if(m_nFD > -1) {
      close(m_nFD);
      m_nFD = -1;
      
      return true;
    }
    
    return false;
  }
  
  bool BeatFlower::sendCommand(std::string strCommand) {
    strCommand += "\r";
    
    if(m_unMicroSecondsDelay > 0) {
      for(unsigned int unI = 0; unI < strCommand.length(); ++unI) {
	if(unI > 0) {
	  usleep(m_unMicroSecondsDelay);
	}
	
	if(write(m_nFD, &(strCommand.c_str()[unI]), 1) != 1) {
	  return false;
	}
      }
    } else {
      if(write(m_nFD, strCommand.c_str(), strCommand.length() != strCommand.length())) {
	return false;
      }
    }
    
    return true;
  }
  
  bool BeatFlower::selectRing(unsigned int unIndex) {
    std::stringstream stsCommand;
    stsCommand << "r" << unIndex;
    
    return this->sendCommand(stsCommand.str());
  }
  
  bool BeatFlower::setLEDColor(unsigned int unIndex, unsigned int unR, unsigned int unG, unsigned int unB) {
    std::stringstream stsCommand;
    stsCommand << "l" << unIndex << " " << unR << " " << unG << " " << unB;
    
    return this->sendCommand(stsCommand.str());
  }
  
  bool BeatFlower::commit() {
    return this->sendCommand("c");
  }
}
