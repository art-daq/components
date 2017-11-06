#ifndef _ots_FSSRApplicationFirmwareBase_h_
#define _ots_FSSRApplicationFirmwareBase_h_

namespace ots
{


class FSSRApplicationFirmwareBase
{

public:
	//factory method for choosing network protocol
	FSSRApplicationFirmwareBase          (void){;}
    FSSRApplicationFirmwareBase          (unsigned int version){;}
    virtual ~FSSRApplicationFirmwareBase (void){;}
    virtual void init             (void){;}

};

}

#endif
