#include "otsdaq-components/FEInterfaces/FECommanderInterface.h"
// #include "otsdaq/Macros/CoutMacros.h"
#include "otsdaq/Macros/InterfacePluginMacros.h"

#include <stdio.h>
#include <stdlib.h>
#include <cstring>  //for memcpy
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

using namespace ots;

//========================================================================================================================
ots::FECommanderInterface::FECommanderInterface(
    const std::string&       interfaceUID,
    const ConfigurationTree& theXDAQContextConfigTree,
    const std::string&       interfaceConfigurationPath)
    : Socket(theXDAQContextConfigTree.getNode(interfaceConfigurationPath)
                 .getNode("HostIPAddress")
                 .getValue<std::string>(),
             theXDAQContextConfigTree.getNode(interfaceConfigurationPath)
                 .getNode("HostPort")
                 .getValue<unsigned int>())
    , FEVInterface(interfaceUID, theXDAQContextConfigTree, interfaceConfigurationPath)
    , interfaceSocket_(theXDAQContextConfigTree.getNode(interfaceConfigurationPath)
                           .getNode("InterfaceIPAddress")
                           .getValue<std::string>(),
                       theXDAQContextConfigTree.getNode(interfaceConfigurationPath)
                           .getNode("InterfacePort")
                           .getValue<unsigned int>())
    , stateMachineName_(theXDAQContextConfigTree.getNode(interfaceConfigurationPath)
                            .getNode("StateMachineName")
                            .getValue<std::string>())
    , configurationAlias_(theXDAQContextConfigTree.getNode(interfaceConfigurationPath)
                              .getNode("ConfigurationAlias")
                              .getValue<std::string>())
	, onlyRunTransitions_(false)
	, monitorRemoteAppStatus_(false)
{
	Socket::initialize();
	universalAddressSize_ = 8;
	universalDataSize_    = 8;

	try
	{
		onlyRunTransitions_ = theXDAQContextConfigTree.getNode(interfaceConfigurationPath)
                            .getNode("OnlyRunTransitions")
                            .getValue<bool>();
	}
	catch(...) {;} //ignore missing setting

	try
	{
		monitorRemoteAppStatus_ = theXDAQContextConfigTree.getNode(interfaceConfigurationPath)
                            .getNode("MonitorRemoteAppStatus")
                            .getValue<bool>();
	}
	catch(...) {;} //ignore missing setting

	__COUTV__(onlyRunTransitions_);

	__COUTV__(monitorRemoteAppStatus_);	
	if(monitorRemoteAppStatus_)
	{
		__COUT__ << "Enabling App Status checking..." << __E__;
		std::thread([](FECommanderInterface* s) { FECommanderInterface::AppStatusWorkLoop(s); }, this).detach();
	}
	else
	{
		__COUT__ << "App Status checking is disabled." << __E__;

		// set all app status to "Not Monitored" 
		std::lock_guard<std::mutex> lock(remoteAppStatusMutex_);	
		remoteAppStatus_ = SupervisorInfo::APP_STATUS_NOT_MONITORED;
	}

} //end constructor()

//========================================================================================================================
ots::FECommanderInterface::~FECommanderInterface(void) 
{
	__COUT__ << "Destructor" << __E__;
} //end destructor()

//==============================================================================
// AppStatusWorkLoop
//	child thread
void FECommanderInterface::AppStatusWorkLoop(FECommanderInterface* fePtr)
{
	int i = 0;
	while(1)
	{
		sleep(1);

		std::lock_guard<std::mutex> lock(fePtr->remoteAppStatusMutex_);	
		fePtr->remoteAppStatus_ = "Check" + std::to_string(i++);

		//TODO - UDP request to target GatewaySupervisor for its app status

	}                  // end of infinite status checking loop
}  // end AppStatusWorkLoop()

//==============================================================================
// virtual progress string that can be overridden with more info
//	e.g. steps and substeps
//	however integer 0-100 should be first number, then separated by : colons
//	e.g. 94:FE0:1:2
std::string FECommanderInterface::getStatusProgressDetail(void)
{
	std::lock_guard<std::mutex> lock(remoteAppStatusMutex_);	
	return remoteAppStatus_;
}  // end getStatusProgressString()

//========================================================================================================================
void ots::FECommanderInterface::send(std::string buffer)
{
	try
	{
		bool verbose = false;
		__FE_COUT__ << "Sending: " << buffer << std::endl;
		if(TransceiverSocket::send(interfaceSocket_, buffer, verbose) < 0)
		{
			__FE_SS__ << "Write failed to IP:Port " << interfaceSocket_.getIPAddress() << ":"
			       << interfaceSocket_.getPort() << __E__;
			__FE_SS_THROW__;
		}
	}
	catch(std::runtime_error& e)
	{
		throw;
	}
	catch(...)
	{
		__FE_SS__ << "Unrecognized exception caught!" << std::endl;
		__FE_SS_THROW__;
	}
} //end send()

//========================================================================================================================
void ots::FECommanderInterface::halt(void)
{
	if(onlyRunTransitions_) 
	{
		__FE_COUT__ << "Only executing run transitions - skipping Halt transition." << __E__;
		return;
	}
	// MESSAGE = "PhysicsRuns0,Halt"
	send(stateMachineName_ + ",Halt");
} //end halt()

//========================================================================================================================
void ots::FECommanderInterface::pause(void) { send(stateMachineName_ + ",Pause"); }

//========================================================================================================================
void ots::FECommanderInterface::resume(void) { send(stateMachineName_ + ",Resume"); }
//========================================================================================================================
void ots::FECommanderInterface::start(std::string runNumber)
{
	// MESSAGE = "PhysicsRuns0,Start, %i" % (int(run)) #"PhysicsRuns0,Start"
	send(stateMachineName_ + ",Start," + runNumber);
} //end start()

//========================================================================================================================
void ots::FECommanderInterface::stop(void)
{
	// MESSAGE = "PhysicsRuns0,Stop"
	send(stateMachineName_ + ",Stop");
} //end stop()

//========================================================================================================================
void ots::FECommanderInterface::configure(void)
{

	if(onlyRunTransitions_) 
	{
		__FE_COUT__ << "Only executing run transitions - skipping Configure transition." << __E__;
		return;
	}

	__FE_COUT__ << "Configure" << __E__;
	// MESSAGE = "PhysicsRuns0,Configure,FQNETConfig"
	send(stateMachineName_ + ",Configure," + configurationAlias_);
} //end configure()