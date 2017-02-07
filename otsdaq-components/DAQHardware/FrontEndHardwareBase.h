/*
 * FrontEndHardwareBase.h
 *
 *  Created on: Aug 26, 2015
 *      Author: uplegger
 */

#ifndef _ots_FrontEndHardwareBase_h_
#define _ots_FrontEndHardwareBase_h_

#include <string>
#include <vector>

namespace ots
{

class FrontEndHardwareBase
{
public:
	FrontEndHardwareBase();
	virtual ~FrontEndHardwareBase();

	virtual int write              (const std::string&              writeBuffer) = 0;
	virtual int write              (const std::vector<std::string>& writeBuffer) = 0;
	virtual int writeAndAcknowledge(const std::string&              writeBuffer) = 0;
	virtual int writeAndAcknowledge(const std::vector<std::string>& writeBuffer) = 0;
	virtual int read               (const std::string&              writeBuffer, std::string&              readBuffer) = 0;
	virtual int read               (const std::vector<std::string>& writeBuffer, std::vector<std::string>& readBuffer) = 0;
};

} // namespace ots

#endif // _ots_FrontEndHardwareBase_h_
