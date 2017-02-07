#ifndef _ots_ROCStream_h_
#define _ots_ROCStream_h_

#include "otsdaq-components/DetectorConfiguration/ROCDACs.h"

#include <string>

namespace ots
{

class ROCStream
{
public:
    ROCStream(void) :
            theDetectorID_   (""),
            theROCType_      (""),
            theROCStatus_    (""),
            theFEWROCAddress_(0),
            theROCMask_      (""),
    		theROCTrimBits_  ("")
    {;}
    virtual ~ROCStream(void){;}

    //Setters
    void  setDetectorID   (const std::string& rocName    ){theDetectorID_    = rocName;}
    void  setROCType      (const std::string& rocType    ){theROCType_       = rocType;}
    void  setROCStatus    (bool               rocStatus  ){theROCStatus_     = rocStatus;}
    void  setFEWROCAddress(unsigned int fecROCAddress    ){theFEWROCAddress_ = fecROCAddress;}
    void  setROCDACs      (const ROCDACs&   rocDACs    	 ){theROCDACs_       = rocDACs;}
    void  addDAC          (std::string name, unsigned int address, unsigned int value){theROCDACs_.setDAC(name,address,value);}
    void  setROCMask      (const std::string& rocMask    ){theROCMask_       = rocMask;}
    void  setROCTrimBits  (const std::string& rocTrimBits){theROCTrimBits_   = rocTrimBits;}

    //Getters
    const std::string&  getDetectorID   (void) const {return theDetectorID_;}
    const std::string&  getROCType      (void) const {return theROCType_;}
    bool                getROCStatus    (void) const {return theROCStatus_;}
    unsigned int        getFEWROCAddress(void) const {return theFEWROCAddress_;}
    const ROCDACs&    	getROCDACs      (void) const {return theROCDACs_;}
    const std::string&  getROCMask      (void) const {return theROCMask_;}
    const std::string&  getROCTrimBits  (void) const {return theROCTrimBits_;}



private:
    std::string  theDetectorID_;
    std::string  theROCType_;
    bool         theROCStatus_;
    unsigned int theFEWROCAddress_;
    ROCDACs    	 theROCDACs_;
    std::string  theROCMask_;
    std::string  theROCTrimBits_;
};

}

#endif //ots_ROCStream_h
