#ifndef MESSAGES_H_
#define MESSAGES_H_
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
using namespace std;

// The Arduino I2C Address
#define ADDRESS 0x04

class Messages
{
	public:
	static Messages* Instance();
	void sendSoracomOnline();
	void sendSoracomOffline();
	void sendXROnline();
	void sendXROffline();
	void sendSATOnline();
	void sendSATOffline();
	void sendIP(const std::string&);
	void sendActivityReady();
	void sendActivityReading();
	void sendActivityPassive();
	void sendActivityUploading();
	void sendUploadInitiated();
	void sendReadFailed();
	void sendUploadFailed();
	void sendXRUploadComplete();
	void sendSessionUploadComplete();
	void sendActivityDownload();
	void sendActivityActive();
	void sendActivityCompress();
	void sendUpdateMessage(const std::string&);
	void sendScreenReset();
	void sendDCUName(const std::string&);
	void sendHeartBeat();

	private:
	Messages();
	Messages(Messages const&){};
	static Messages* m_pInstance;
	bool sendMessage(const std::string&);
	bool flipFlop;

};
#endif /* MESSAGES_H_*/
