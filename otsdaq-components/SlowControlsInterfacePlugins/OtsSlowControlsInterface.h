#ifndef _ots_OtsSlowControlsInterface_h
#define _ots_OtsSlowControlsInterface_h

#include <array>
#include <string>

#include "otsdaq-core/NetworkUtilities/ReceiverSocket.h"  // Make sure this is always first because <sys/types.h> (defined in Socket.h) must be first
#include "otsdaq-core/SlowControlsCore/SlowControlsVInterface.h"
using namespace ots;
//{

class OtsSlowControlsInterface : public SlowControlsVInterface
{
  public:
	OtsSlowControlsInterface(const std::string&       interfaceUID,
	                         const ConfigurationTree& theXDAQContextConfigTree,
	                         const std::string&       controlsConfigurationPath);
	~OtsSlowControlsInterface();

	void initialize();
	void destroy();

	std::string                getList(std::string format);
	void                       subscribe(std::string Name);
	void                       subscribeJSON(std::string List);
	void                       unsubscribe(std::string Name);
	std::array<std::string, 4> getCurrentValue(std::string Name);
	std::array<std::string, 9> getSettings(std::string Name);
};

//}

#endif
