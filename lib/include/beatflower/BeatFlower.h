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


#ifndef __BEATFLOWER_H__
#define __BEATFLOWER_H__


#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <termios.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>


namespace bf {
  class BeatFlower {
  public:
    typedef std::shared_ptr<BeatFlower> Ptr;
    
  private:
    std::string m_strTTY;
    int m_nFD;
    unsigned int m_unRings;
    unsigned int m_unLEDsPerRing;
    unsigned int m_unMicroSecondsDelay;
    
  protected:
  public:
    BeatFlower(std::string strTTY, unsigned int nRings = 5, unsigned int nLEDsPerRing = 12);
    ~BeatFlower();
    
    void setMicroSecondsDelay(unsigned int unMicroSecondsDelay);
    
    bool connect(std::string strTTY = "");
    bool disconnect();
    
    bool sendCommand(std::string strCommand);
    
    bool selectRing(unsigned int unIndex);
    bool setLEDColor(unsigned int unIndex, unsigned int unR, unsigned int unG, unsigned int unB);
    bool commit();
    
    template<class ... Args>
      static BeatFlower::Ptr create(Args ... args) {
      return std::make_shared<BeatFlower>(std::forward<Args>(args)...);
    }
  };
}


#endif /* __BEATFLOWER_H__ */
