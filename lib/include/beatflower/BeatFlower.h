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
