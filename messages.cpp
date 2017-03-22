#include <iostream>
#include <sstream>

using namespace std;

#include "messages.h"


Messages* Messages::m_pInstance = NULL;

Messages::Messages()
{
	// Messages Constructor
	//cout<<"Messages Constructor"<<endl;
	flipFlop=false;
	
}
Messages* Messages::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new Messages;
	}
	return m_pInstance;
}
void Messages::sendScreenReset()
{
	sendMessage("RE");
}
void Messages::sendSoracomOnline()
{
	sendMessage("SOOnline ");
}
void Messages::sendSoracomOffline()
{
	sendMessage("SOOffline");
}
void Messages::sendXROnline()
{
	sendMessage("XROnline ");
}
void Messages::sendXROffline()
{
	sendMessage("XROffline");
}
void Messages::sendSATOnline()
{
	sendMessage("SAOnline ");
}
void Messages::sendSATOffline()
{
	sendMessage("SAOffline");
}
void Messages::sendIP(const std::string& ip)
{
	string ipaddress = "IP" + ip;
	sendMessage(ipaddress);
}
void Messages::sendDCUName(const std::string& name)
{
	string id = "ID" + name;
	sendMessage(id);
}
void Messages::sendActivityPassive()
{
	sendMessage("PRPassive ");
	sendUpdateMessage("-----------------------");
}
void Messages::sendActivityReady()
{
	//sendMessage("PRReady     ");
	sendMessage("PR01");
}
void Messages::sendActivityReading()
{
	//sendMessage("PRReading   ");
	sendMessage("PR02");
}
void Messages::sendActivityUploading()
{
	//sendMessage("PRUploading  ");
	sendMessage("PR03");
}
void Messages::sendActivityDownload()
{
	//sendMessage("PRDownload   ");
	sendMessage("PR04");
}
void Messages::sendActivityActive()
{
	//sendMessage("PRActive     ");
	sendMessage("PR05");
}
void Messages::sendActivityCompress()
{
	sendMessage("PR06");
}
void Messages::sendUploadInitiated()
{
	sendMessage("PR07");
}
void Messages::sendXRUploadComplete()
{
	sendMessage("RS01");
}
void Messages::sendSessionUploadComplete()
{
	sendMessage("RS02");
}
void Messages::sendReadFailed()
{
	sendMessage("RS11");
}
void Messages::sendUploadFailed()
{
	sendMessage("RS12");
}
void Messages::sendUpdateMessage(const std::string& message)
{
	string sMessage = "ME" + message;
	sendMessage(sMessage);
}
void Messages::sendHeartBeat()
{
	if (flipFlop == false)
	{
		sendMessage("HB60");
		flipFlop = true;
	}
	else
	{
		sendMessage("HB61");
		flipFlop = false;
	}
}
bool Messages::sendMessage(const std::string &message)
{
       	//cout<<"I2C: Connecting"<<endl;
	const char *devName = "/dev/i2c-1";
	int fd;
	
        if ((fd = open(devName, O_RDWR)) < 0)
        {
        	//cout<<"I2C: Failed to access device"<<endl;
               	return (false);
        }

       	//cout<<"I2C: acquiring buss to "<<ADDRESS<<endl;

       	if (ioctl(fd, I2C_SLAVE, ADDRESS) < 0)
       	{
               	//cout<<"I2C: Failed to acquire bus"<<endl;
               	return (false);
       	}
		//usleep(2000000);
        if (!write(fd, message.c_str(), message.length() ))
        {
                //cout<<"Error writing to i2c bus"<<endl;
                return (false);
        }
        close(fd);
        return (true);
}
