#ifndef _ots_FSSRPurdueFirmware_h_
#define _ots_FSSRPurdueFirmware_h_

#include <string>
#include "otsdaq-components/DAQHardware/FSSRApplicationFirmwareBase.h"
#include "otsdaq-components/DAQHardware/FirmwareSequence.h"
#include "otsdaq-components/DetectorConfiguration/ROCStream.h"
#include "otsdaq-components/DAQHardware/OtsUDPFirmwareCore.h"

namespace ots
{

class FSSRPurdueFirmware : public FSSRApplicationFirmwareBase//AUG-17-2017 RAR dissociated because function calls are entirely independent from PURDUE firmware calls ///*, public FrontEndFirmwareBase*/
{

public:
    FSSRPurdueFirmware (unsigned int version, std::string type);
    virtual ~FSSRPurdueFirmware(void);
    virtual void init(void);

    /*
    //FEW specific methods
    std::string configureClocks(std::string source, double frequency);
    std::string resetDetector  (int channel=-1);
    std::string enableTrigger  (void);

    void readBurstDestinationIP(std::string& buffer);
    void readBurstDestinationMAC(std::string& buffer);
    void readBurstDestinationPort(std::string& buffer);

    void writeBurstDestinationIP  (std::string& buffer, const uint64_t value);
    void writeBurstDestinationMAC (std::string& buffer, const uint64_t value);
    void writeBurstDestinationPort(std::string& buffer, const uint64_t value);


    void makeDACSequence 				(FirmwareSequence<uint64_t>& sequence, unsigned int channel, const ROCStream& rocStream);
    void makeMaskSequence				(FirmwareSequence<uint64_t>& sequence, unsigned int channel, const ROCStream& rocStream);
    void makeDACSequence 				(FirmwareSequence<uint32_t>& sequence, unsigned int channel, const ROCStream& rocStream);
    void makeDACBuffer   				(std::string& buffer, unsigned int channel, const ROCStream& rocStream);
    void makeDACBuffer   				(std::vector<std::string>& buffer, unsigned int channel, const ROCStream& rocStream);
    void makeMaskSequence				(FirmwareSequence<uint32_t>& sequence, unsigned int channel, const ROCStream& rocStream);
    void makeMaskBuffer  				(std::string& buffer, unsigned int channel, const ROCStream& rocStream);
    void setFrequencyFromClockState		        (std::string& buffer, double frequency);
    bool isClockStateExternal			        (void);

    //FER specific methods
    std::string resetBCO           (void);
    std::string startStream        (bool channel0, bool channel1, bool channel2, bool channel3, bool channel4, bool channel5);
    std::string stopStream         (void);

//protected:
    void makeMaskSequence(FirmwareSequence<uint64_t>& sequence, unsigned int channel, const ROCStream& rocStream, const std::string& registerName);
    void makeMaskSequence(FirmwareSequence<uint32_t>& sequence, unsigned int channel, const ROCStream& rocStream, const std::string& registerName);
    void makeMaskBuffer  (std::string& buffer, unsigned int channel, const ROCStream& rocStream, const std::string& registerName);

    void setCSRRegister						(uint32_t total);
    void writeCSRRegister				    (std::string& buffer);

    uint32_t stripCSRRegisterValue_;
    //Set values for register STRIP_CSR (Strip Control Register)
    void setPacketSizeStripCSR			  (uint32_t size);
    void enableChannelsStripCSR           (bool channel0, bool channel1, bool channel2, bool channel3, bool channel4, bool channel5);
    void setExternalBCOClockSourceStripCSR(std::string clockSource);
    void setHaltStripCSR                  (bool set);
    void enableBCOStripCSR                (bool enable);
	void flushBuffersStripCSR             (void);
	void resetTriggerCounterStripCSR      (std::string& buffer);
	void resetBCOCounterStripCSR          (void);
	void enableTriggerStripCSR            (bool enable);
	void sendTriggerDataStripCSR          (bool send);
	void sendTriggerNumberStripCSR        (bool send);
	void sendBCOStripCSR                  (bool send);
	void enableStreamStripCSR             (bool enable);
	void resetDCMStripCSR                 (bool clear);
	uint32_t waitDCMResetStripCSR         (void);
	std::string readCSRRegister			  (void);

    uint32_t stripResetRegisterValue_;
    //Set values for register STRIP_RESET (Strip Reset)
    void resetStripResetRegisterValue(void)
    {
        stripResetRegisterValue_ = 0;
    }
    void resetDAC                    (void);
    void resetLink                   (bool channel0, bool channel1, bool channel2, bool channel3, bool channel4, bool channel5);
    void clearErrors                 (bool channel0, bool channel1, bool channel2, bool channel3, bool channel4, bool channel5);
    void clearFIFO                   (bool channel0, bool channel1, bool channel2, bool channel3, bool channel4, bool channel5);
    void resetChip                   (bool channel0, bool channel1, bool channel2, bool channel3, bool channel4, bool channel5);

    uint32_t stripBCODCMRegisterValue_;
    void setFrequencyRatio           (std::string& buffer, int numerator, int denominator);

    void configureStripTriggerUnbiased		(std::string& buffer);
    void configureTriggerInputs				(std::string& buffer);

    uint32_t stripTriggerCSRRegisterValue_;
	//Registers setters
	void BCOOffset(uint32_t offset);
	void selectSpyFIFO(uint32_t input);
	void halt(bool halt);


	std::string  resetSlaveBCO(void);
	*/
};

}

#endif
