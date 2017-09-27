/*
 * FrontEndHardwareBase.h
 *
 *  Created on: Aug 26, 2015
 *      Author: uplegger
 */

#ifndef _ots_FrontEndHardwareBase_h_
#define _ots_FrontEndHardwareBase_h_


#include "otsdaq-core/Macros/CoutHeaderMacros.h"

#include <string>
#include <vector>
#include <stdexcept> /*for std::runtime_error*/

namespace ots
{

class FrontEndHardwareBase
{
public:
	FrontEndHardwareBase();
	virtual ~FrontEndHardwareBase();

	//pure virtual function declarations
	virtual void write              (const std::string&              sendBuffer) throw(std::runtime_error){__SS__; throw std::runtime_error(ss.str() + "Illegal call to undefined base class member function");}
	virtual void write              (const std::vector<std::string>& sendBuffers) throw(std::runtime_error){__SS__; throw std::runtime_error(ss.str() + "Illegal call to undefined base class member function");}
	virtual void writeAndAcknowledge(const std::string&              sendBuffer, int timeoutSeconds = -1) throw(std::runtime_error){__SS__; throw std::runtime_error(ss.str() + "Illegal call to undefined base class member function");}
	virtual void writeAndAcknowledge(const std::vector<std::string>& sendBuffers, int timeoutSeconds = -1) throw(std::runtime_error){__SS__; throw std::runtime_error(ss.str() + "Illegal call to undefined base class member function");}
	virtual void read               (const std::string&              sendBuffer , std::string&              	receiveBuffer, int timeoutSeconds = -1) throw(std::runtime_error){__SS__; throw std::runtime_error(ss.str() + "Illegal call to undefined base class member function");}
	virtual void read               (const std::vector<std::string>& sendBuffers, std::vector<std::string>& 	receiveBuffers, int timeoutSeconds = -1) throw(std::runtime_error){__SS__; throw std::runtime_error(ss.str() + "Illegal call to undefined base class member function");}
};

} // namespace ots

#endif // _ots_FrontEndHardwareBase_h_
