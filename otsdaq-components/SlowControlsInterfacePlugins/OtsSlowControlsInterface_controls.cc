#include "otsdaq-components/SlowControlsInterfacePlugins/OtsSlowControlsInterface.h"
#include "otsdaq-core/Macros/SlowControlsPluginMacros.h"

using namespace ots;

OtsSlowControlsInterface::OtsSlowControlsInterface(
    const std::string&       interfaceUID,
    const ConfigurationTree& theXDAQContextConfigTree,
    const std::string&       controlsConfigurationPath)
	//TODO -- listen on a socket for data
	//	or read from disk
    //  :Socket            (
    //  theXDAQContextConfigTree.getNode(interfaceConfigurationPath).getNode("HostIPAddress").getValue<std::string>()
    // ,theXDAQContextConfigTree.getNode(interfaceConfigurationPath).getNode("HostPort").getValue<unsigned
    // int>())
    // ,
    : SlowControlsVInterface(
          interfaceUID, theXDAQContextConfigTree, controlsConfigurationPath)
{
}

OtsSlowControlsInterface::~OtsSlowControlsInterface() { destroy(); }

void OtsSlowControlsInterface::initialize() {}

void OtsSlowControlsInterface::destroy() {}

std::string OtsSlowControlsInterface::getList(std::string format)
{
	//__COUT__ <<
	// theXDAQContextConfigTree.getNode(controlsConfigurationPath).getValue <<
	// std::endl;
	return (std::string) "list";
}
void OtsSlowControlsInterface::subscribe(std::string Name) {}

void OtsSlowControlsInterface::subscribeJSON(std::string List) {}

void OtsSlowControlsInterface::unsubscribe(std::string Name) {}

std::array<std::string, 4> OtsSlowControlsInterface::getCurrentValue(std::string Name)
{
	return {"a", "b", "c", "d"};
}

std::array<std::string, 9> OtsSlowControlsInterface::getSettings(std::string Name)
{
	return {"a", "b", "c", "d", "e", "f", "g", "h", "i"};
}

DEFINE_OTS_SLOW_CONTROLS(OtsSlowControlsInterface)
