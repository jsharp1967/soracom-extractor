#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "xr5000.h"
#include "extractor.h"
#include "sessionParser.h"
#include "animalParser.h"
#include "uploader.h"
#include "loader.h"
#include "compressor.h"
#include "messages.h"
#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <dirent.h>
#include <list>
#include "functions.h"
#include "compressor.h"

#include <wiringPi.h> // Include WiringPi library!

//const int butUpload = 17;  //Version 1 Active-low button - Broadcom pin 17, P1 pin 11
const int butUpload = 27;  //Active-low button - Broadcom pin 17, P1 pin 11
//const int butDownload = 18; //Version 1 Active-low button - Broadcom pin 18, P1 pin 12
const int butDownload = 22; //Active-low button - Broadcom pin 18, P1 pin 12
//const int butOrange = 27; //Active-low button - Broadcom pin 27, P1 pin 13
//const int butRed = 22;    //Active-low button - Broadcom pin 22, P1 pin 15
const int buzz = 23; // Active-high output to buzzer - Broadcom pin 23 PI pin 16

using namespace std;

string DCUName;
string DCUNamePath;

#define UL_FILE_PATH "/home/pi/data_upload/"
#define DL_FILE_PATH "/home/pi/data_download/"
//#define REMOTE_URL	"FTP://192.168.0.71/data/"
//#define REMOTE_URL	"FTP://104.210.87.9/data_upload/"
//#define REMOTE_URL	"FTP://13.75.190.231/data_upload/"
#define REMOTE_URL	"FTP://cicero5775.cloudapp.net/data_upload/"
#define UPLOAD_COMPLETE_MARKER "ANIMALS_UPLOAD_COMPLETE.TXT"
#define BACKUP_FILE_PATH "/home/pi/data_backup/"

list<string> sessionNumbers;
list<string> fileList;

void displayBaseMenuOptions()
{
	cout<<"Command options are:"<<endl;
        cout<<"Execute command:\te"<<endl;
        cout<<"Get Status:\t\ts"<<endl;
        cout<<"Get Sessions:\t\tn"<<endl;
        cout<<"Get  Animals:\t\ta"<<endl;
        cout<<"Get Animals in Session:\tb"<<endl;
        cout<<"Upload Files:\t\tu"<<endl;
        cout<<"Upload Compressed files:v"<<endl;
        cout<<"Compress files:\t\tc"<<endl;
        cout<<"Decompress files:\td"<<endl;
        cout<<"Process Animal files:\tp"<<endl;
	cout<<"Download Animals:\tx"<<endl;
	cout<<"Load download files:\tl"<<endl;
        cout<<"Help:\t\t\th"<<endl;
        cout<<"Quit:\t\t\tq"<<endl;
        cout<<"Help:\t\t\th"<<endl;
        cout<<"Quit:\t\t\tq"<<endl;
}
void commandLineDriver()
{
        displayBaseMenuOptions();
        string input = "";
        while (true)
        {
                cout<<"Enter soracom Command:"<<endl;
                getline(cin,input);

                if (input == "q")
                {
                        cout<<"Quitting...."<<endl;
                        break;
                }
                else if (input == "e")
                {
                        cout<<"Execute Command"<<endl;
                        string com = ".com/";
                        string command = "http://example" + com;
                        //execute_command(command);
                        continue;
                }
                else if (input == "s")
                {
                        cout<<"Getting XR5000 Status"<<endl;
                        get_status();
                        continue;
                }
                else if (input == "n")
                {
                        cout<<"Getting XR5000 Sessions"<<endl;
                        get_sessionsP();
                        continue;
                }

               else if (input == "a")
                {
                        cout<<"Getting XR5000 Animals"<<endl;
                        get_animals();
                        continue;
                }
                else if (input == "b")
                {
                        cout<<"Getting XR5000 Animals"<<endl;
                        get_animalsInSession();
                        continue;
                }
                else if (input =="u")
                {
                        cout<<"Uploading files"<<endl;
                        upload_files();
                        continue;
                }
                else if (input =="v")
                {
			cout<<getTimeNow()<<endl;
                        cout<<"Uploading compressed files"<<endl;
                        upload_compressed_files();
			backup_files();
			cout<<getTimeNow()<<endl;
                        continue;
                }
                else if (input == "c")
                {
                        cout<<"Compressing files"<<endl;
                        compress_files();
                        continue;
                }
                else if (input == "d")
                {
                        cout<<"Decompressing files"<<endl;
                        decompress_files();
                        continue;
                }
               else if (input == "p")
                {
                        cout<<"Processing and Parsing Animal files"<<endl;
                        processAnimalFiles();
                        continue;
                }
		else if (input == "l")
                {
                        cout<<"Getting files for upload to XR 5000"<<endl;
                        findFiles();
                        continue;
                }
                else if (input == "x")
                {
                        cout<<"Uploading animals to XR5000"<<endl;
                        download_animals();
                        continue;
                }

                displayBaseMenuOptions();
        }
}
void startBeep()
{

	digitalWrite(buzz,HIGH);
	delay (50);
	digitalWrite(buzz,LOW);
	delay (50);
	digitalWrite(buzz,HIGH);
	delay (50);
	digitalWrite(buzz,LOW);
	delay (50);
	digitalWrite(buzz,HIGH);
	delay (50);
	digitalWrite(buzz,LOW);
	delay (50);
}
void singleBeep()
{
	digitalWrite(buzz,HIGH);
	delay (500);
	digitalWrite(buzz,LOW);

}
void errorBeeps()
{
	digitalWrite(buzz,HIGH);
	delay (100);
	digitalWrite(buzz,LOW);
	delay (100);
	digitalWrite(buzz,HIGH);
	delay (100);
	digitalWrite(buzz,LOW);
	delay (100);
	digitalWrite(buzz,HIGH);
	delay (100);
	digitalWrite(buzz,LOW);
	delay (100);
	digitalWrite(buzz,HIGH);
	delay (100);
	digitalWrite(buzz,LOW);
	delay (100);
	digitalWrite(buzz,HIGH);
	delay (100);
	digitalWrite(buzz,LOW);
	delay (100);
	digitalWrite(buzz,HIGH);
	delay (100);
	digitalWrite(buzz,LOW);

}
void doubleBeep()
{
	
	digitalWrite(buzz,HIGH);
	delay (800);
	digitalWrite(buzz,LOW);
	delay (100);
	digitalWrite(buzz,HIGH);
	delay (800);
	digitalWrite(buzz,LOW);

}
void buttonDriver()
{
	// Setup stuff:
	wiringPiSetupGpio(); // Initialize wiringPi -- using Broadcom pin numbers

	pinMode(buzz,OUTPUT); // Set buzz as output
	
	pinMode(butUpload, INPUT);            // Set button as INPUT
	pullUpDnControl(butUpload, PUD_OFF);  // Disable internal pull-up resistor

	pinMode(butDownload, INPUT);           // Set button as INPUT
	pullUpDnControl(butDownload, PUD_OFF); // Disable internal pull-up resistor

    	//pinMode(butOrange, INPUT);           // Set button as INPUT
    	//pullUpDnControl(butOrange, PUD_OFF); // Disable internal pull-up resistor
    	//pinMode(butRed, INPUT);              // Set button as INPUT
    	//pullUpDnControl(butRed, PUD_OFF);    // Disable internal pull-up resistor

    	//Message on screen
	DCUName = getDCUName();
	DCUNamePath = DCUName + "/";
	
	cout<<"Data Collection Unit Name is:"<<DCUName<<endl;
	cout<<"Waiting for button inputs! Press CTRL+C to quit."<<endl;
	
	startBeep();
	delay(500);
	Messages::Instance()->sendDCUName(DCUName);
	delay(1000);
	
	//Main Loop
    while(1)
    {
		Messages::Instance()->sendHeartBeat();
		Messages::Instance()->sendActivityReady();
		
        if (digitalRead(butUpload)) // Upload Button is released if this returns 1
        {
            //printf("Upload Button Off\n"); // Print Upload button Off msg
        }
       	else // If butUpload returns 0, button is pressed
		{
			singleBeep();	
			printf ("Upload Button On\n"); // Print Green button On msg
			cout<<"Started upload at:"<<getTimeNow()<<endl;
			Messages::Instance()->sendUploadInitiated();
			// Get the sessions and animals from the XR5000
			if(get_sessionsP())
			{
				// Indicate upload finished
				cout<<"Completed XR Session upload at:"<<getTimeNow()<<endl;
				doubleBeep(); // Upload success
				Messages::Instance()->sendXRUploadComplete();
			}
			else
			{
				errorBeeps();
				Messages::Instance()->sendReadFailed();

			}
			if(upload_compressed_files())
			{

				backup_files();
				cout<<"Completed Session upload at:"<<getTimeNow()<<endl;
				Messages::Instance()->sendSessionUploadComplete();
				doubleBeep(); // Upload success
			}	
			else
			{
				errorBeeps();
				Messages::Instance()->sendUploadFailed();
			}
			Messages::Instance()->sendActivityReady();
        }
        if (digitalRead(butDownload)) // Download Button is released if this returns 1
        {
            //printf("Download Button Off\n"); // Print Download button Off msg
        }
        else // If butDownload returns 0, button is pressed
        {
			printf ("Download Button On\n"); // Print Download button On msg
			singleBeep();	
           	printf ("Upload Button On\n"); // Print Green button On msg
			cout<<"Started download at:"<<getTimeNow()<<endl;
			Messages::Instance()->sendActivityDownload();
			findFiles();
			download_animals();
			Messages::Instance()->sendActivityReady();
            cout<<"Completed upload at:"<<getTimeNow()<<endl;
        }
        delay(500);
    }
}
void upload_data()
{
	// Get the number of sessions
	get_sessions();
	// Get the animals in each session, write to a file and compress each
	
	// Upload each file to remote server and execute db upload
}
void get_status()
{
	Messages::Instance()->sendActivityActive();
	Messages::Instance()->sendXROnline();
	cout<<"Getting XR5000 status"<<endl;
	Extractor *ext  = new Extractor();
	std::string buf;
	ext->checkStatus(buf);
	//cout<<"getStatus::got:"<<buf.size()<<endl;
	cout<<buf<<endl;
	ofstream ofs;
	string filePath = UL_FILE_PATH;
	string fileName = filePath + "status.xml";
	ofs.open(fileName);
	ofs<<buf;
	ofs.close();
	delete ext;
	Messages::Instance()->sendActivityPassive();
}

bool get_sessionsP()
{

	Messages::Instance()->sendActivityReading();
	list<string>::iterator i;
	
	Extractor *ext  = new Extractor();
	std::string buf;
	std::string animalsBuffer;
	if (!ext->getSessions(buf))
	{
		cout<<"Failed to contact XR5000"<<endl;
		return false;
	}
	try
	{
		SessionParser parser;
        	//cout<<"Parsing sessions"<<endl;
		parser.set_substitute_entities(false); //We want to know about the entities, not have them substituted automatically.
		parser.parse_memory(buf);
		//cout<<"Number of sessions found "<<parser.getNumberOfSessions()<<endl;
		//parser.listSessions();
		sessionNumbers.clear();
		fileList.clear();
		parser.getSessionNumbers(sessionNumbers);
        
        	for (i = sessionNumbers.begin(); i != sessionNumbers.end(); i++)
        	{
			animalsBuffer.clear();
			ext->getAnimalsInSession(animalsBuffer,*i);
			string filePath = UL_FILE_PATH;
			string fileName = "animalsinsession-";
			fileName+=*i;
			fileName+=".xml";
			
			string fileNamePath = filePath + fileName;
			if (remove (fileNamePath.c_str()) == 0)
				cout<<"Deleted existing file"<<endl;
			cout<<"Writing to file:"<<fileNamePath<<endl;
			ofstream sessionFile(fileNamePath);
			if (!sessionFile.is_open())
			{
				cout<<"Failed to open session file"<<endl;
				return false;
			}
			sessionFile<<animalsBuffer;
			sessionFile.close();
			fileList.push_back(fileName);
			cout<<"Completed writing to file:"<<fileName<<endl<<endl;
			//cout<<buf2<<endl;
        	}
		compress_files();
	}
	catch(const xmlpp::exception& ex)	
	{
		cerr << "libxml++ exception: " << ex.what() << std::endl;
		return false;
	}
	return true;
}
void processAnimalFiles()
{
	list<string>::iterator i;
	Messages::Instance()->sendActivityActive();
	try
	{
        //for (i = fileList.begin(); i != fileList.end(); i++)
		{
			string buf;
			string line;
			//string fileName = *i; // temp hack to process one file only
			string fileName = "animalsinsession-2.xml";
			string fileNamePath = UL_FILE_PATH + fileName;
			cout<<"processAnimalFiles:"<<fileNamePath<<endl;
			//Messages::Instance()->sendUpdateMessage(fileName);
			ifstream in(fileNamePath);
			if (in.is_open())
			{
				while ( getline (in,line) )
				{
					buf += line + "\n";
					//cout<<line<<endl;
				}
				in.close();
			}
  			else
			{
				cout << "Unable to open file";
				return;
			}

			AnimalParser parser;
			//cout<<buf<<endl;
			parser.set_substitute_entities(false); //We want to know about the entities, not have them substituted automatically.
			parser.parse_memory(buf);
			parser.listSessions();
			in.close();
        	}
		Messages::Instance()->sendActivityPassive();
	}
	catch(const xmlpp::exception& ex)	
	{
		cerr << "libxml++ exception: " << ex.what() << std::endl;
		return;
	}
}
void compress_files()
{
	Messages::Instance()->sendActivityCompress();
	list<string>::iterator i;
	
	for (i = fileList.begin(); i != fileList.end(); i++)
	{
		string compressFilePath = UL_FILE_PATH + *i;
		if (!checkIsZipped(compressFilePath))
		{
			Compressor::Instance()->compressFile(compressFilePath, compressFilePath +".gzip");
			// Remove old file
			remove (compressFilePath.c_str());
		}
		//cout<<*i<<endl;
	}
	//Messages::Instance()->sendActivityReady();
}
void decompress_files()
{
	list<string>::iterator i;	
	for (i = fileList.begin(); i != fileList.end(); i++)
	{
		string uploadFilePath = UL_FILE_PATH + *i;
		//cout<<*i<<endl;
		cout<<uploadFilePath<<endl;
		Uploader::Instance()->uploadFile(uploadFilePath, REMOTE_URL + DCUNamePath + *i);
	}
}
void upload_marker_file()
{
	string uploadFileName = UL_FILE_PATH + string(UPLOAD_COMPLETE_MARKER);
	Uploader::Instance()->uploadFile(uploadFileName, REMOTE_URL + DCUNamePath + string(UPLOAD_COMPLETE_MARKER));

}
void backup_files()
{
	cout<<"Backing up files"<<endl;
	
        list<string>::iterator i;

        for (i = fileList.begin(); i != fileList.end(); i++)
        {
                string uploadFilePath = UL_FILE_PATH + *i;
                //cout<<*i<<endl;
		string backupFilePath = BACKUP_FILE_PATH + *i + "." + getTimeNow();
                cout<<backupFilePath<<endl;
		rename(uploadFilePath.c_str(), backupFilePath.c_str());
		//string fileToDelete = UL_FILE_PATH + *i;
		//if (remove (fileToDelete.c_str()) == 0)
                //               cout<<"Deleted existing file"<<endl;
        }

}
bool upload_compressed_files()
{
	Messages::Instance()->sendActivityUploading();
	findFiles();
	list<string>::iterator i;
	bool uploadSuccess = false;
	
	stringstream ss;
	ss<<fileList.size();
	string totalFiles = ss.str();

	int fileCount = 0;

	for (i = fileList.begin(); i != fileList.end(); i++)
	{
		fileCount++;	
		stringstream ss2;
		ss2<<fileCount;
		string currentFile = ss2.str();

		string uploadFilePath = UL_FILE_PATH + *i;
		string uploadFileMessage = "Upload Session:" + currentFile + " of " + totalFiles;

		Messages::Instance()->sendUpdateMessage(uploadFileMessage);
		//cout<<*i<<endl;
		cout<<"Upload compressed files:"<<uploadFilePath<<endl;
		string dest = REMOTE_URL + DCUNamePath + *i;
		cout<<"Destination:"<<dest<<endl;
		if(Uploader::Instance()->uploadFile(uploadFilePath, REMOTE_URL + DCUNamePath + *i ))
			uploadSuccess = true;
			
	}
	if (uploadSuccess)
	{
		upload_marker_file();
		Messages::Instance()->sendUpdateMessage("-----------------------");
		return true;
	}
	else
	{
		Messages::Instance()->sendUpdateMessage("-----------------------");
		return false;	
	}
	return false;
}
void upload_files()
{
	list<string>::iterator i;
	Messages::Instance()->sendActivityUploading();
	
	for (i = fileList.begin(); i != fileList.end(); i++)
	{
		string uploadFilePath = UL_FILE_PATH + *i;
		//string name = "test1";
		//string rname = "test1";
		//string uploadFilePath = UL_FILE_PATH + name;
		//cout<<*i<<endl;
		cout<<uploadFilePath<<endl;
		//Messages::Instance()->sendUpdateMessage(*i);
		//Uploader::Instance()->uploadFile(uploadFilePath, REMOTE_URL + DCUNamePath + rname);
		Uploader::Instance()->uploadFile(uploadFilePath, REMOTE_URL + DCUNamePath + *i);
	}
	Messages::Instance()->sendActivityPassive();
}
void get_sessions()
{
	cout<<"Getting Sessions"<<endl;
	Extractor *ext  = new Extractor();
	std::string buf;
	int sessionCount = 0;
	sessionCount = ext->getSessions(buf);
	cout<<"getSessions::got:"<<buf.size()<<endl;
	cout<<"get_sessions::number of sessions:"<<sessionCount<<endl;
	cout<<buf<<endl;
	ofstream ofs;
	ofs.open("sessions.xml");
	ofs<<buf;
	ofs.close();
	delete ext;
}
void get_animalsInSession()
{
	cout<<"Getting Animals in Session"<<endl;
	Extractor *ext  = new Extractor();
	std::string buf;
	int sessionCount = 0;
	sessionCount = ext->getAnimalsInSession(buf,"3");
	cout<<"get_animalsInSession::got:"<<buf.size()<<endl;
	cout<<"get_animalsInSession::number of sessions:"<<sessionCount<<endl;
	cout<<buf<<endl;
	ofstream ofs;
	ofs.open("animalsInsession.xml");
	ofs<<buf;
	ofs.close();
	delete ext;
}

void get_animals()
{
	cout<<"Getting Animals"<<endl;
	Extractor *ext  = new Extractor();
	std::string buf;
	int sessionCount = 0;
	sessionCount = ext->getAnimals(buf);
	cout<<"getAnimals::got:"<<buf.size()<<endl;
	cout<<"get_animals::number of animals:"<<sessionCount<<endl;
	cout<<buf<<endl;
	ofstream ofs;
	ofs.open("animals.xml");
	ofs<<buf;
	ofs.close();
	delete ext;
}
string getIP()
{
	int fd;
	struct ifreq ifr;
	char iface[] = "eth0";

	fd = socket(AF_INET, SOCK_DGRAM, 0);

	//Type of address to retrieve - IPv4 IP address
	ifr.ifr_addr.sa_family = AF_INET;

	//Copy the interface name in the ifreq structure
	strncpy(ifr.ifr_name , iface , IFNAMSIZ-1);
	ioctl(fd, SIOCGIFADDR, &ifr);
	close(fd);
	string str(inet_ntoa( ((struct sockaddr_in *)&ifr.ifr_addr )->sin_addr));
	return(str);
}
bool  findFiles()
{
        DIR *dir;
        struct dirent *ent;
        string fileName;
        fileList.clear();
        if ((dir = opendir(UL_FILE_PATH)) != NULL)
        {
                // Found dir - listing files

                while ((ent = readdir(dir)) != NULL)
                {
                        //cout<<ent->d_name<<endl;
                        fileName = ent->d_name;
                        // Remove . and ..
                        if ((*ent->d_name !='.'))
                        {
				if (checkIsZipped(fileName))
                                	fileList.push_back(fileName);
                        }
                }
                closedir(dir);
        }
        else
        {

                perror("");
                return false;

        }
	if (fileList.empty())
	{
		cout<<"No files to transfer"<<endl;
		return false;
	}
	else
	{
		cout<<"Files to transfer"<<endl;
        	displayFileList();
		return true;
	}	
}
void displayFileList()
{

        list<string>::iterator i;
        for (i = fileList.begin(); i != fileList.end(); i++)
        {
                cout<<"File in list:"<<*i<<endl;
        }
}
bool checkIsXML(string fileName)
{

        size_t pos = 0;
        pos = fileName.find(".xml");
        if ( pos !=std::string::npos)
                return true;
        else
                return false;

}
bool checkIsZipped(string fileName)
{
        size_t pos = 0;
        pos = fileName.find(".gzip");
        if ( pos !=std::string::npos)
                return true;
        else
                return false;
}
void removeSuffixFromString(string &str)
{
        size_t pos = str.find(".gzip");
        str = str.substr(0,pos);
}
void download_animals()
{
        Messages::Instance()->sendXROnline();
        cout<<"Downloading to XR5000"<<endl;
        Messages::Instance()->sendActivityUploading();
        list<string>::iterator i;

        for (i = fileList.begin(); i != fileList.end(); i++)
        {

                string downloadFilePath = DL_FILE_PATH + *i;
                std::ifstream in(downloadFilePath);
                std::string buf;
                if (!in.good())
                {
                        std::cerr << "ERROR: Opening file `" << downloadFilePath << "' failed.\n";
                        return;
                }
                char c;
                while ( in.get(c))
                {
                        buf += c;
                }
                in.close();

                Loader *ldr  = new Loader();
                ldr->loadAnimalData(buf);
                delete ldr;
        }
        //Messages::Instance()->sendXROffline();
        Messages::Instance()->sendActivityPassive();
}
string getTimeNow()
{
        time_t now = time(0);
        struct tm tstruct;
        tstruct = *localtime(&now);
        char buf[80];
        strftime(buf,sizeof(buf), "%Y-%m-%d.%X", &tstruct);

        return buf;
}
string getDCUName()
{

	string buf;
	string line;
	string configFileName = "/home/pi/DCU_CONFIG.TXT";
	ifstream in(configFileName);
	if (in.is_open())
	{
		while ( getline (in,line) )
		{
			buf += line;
		}
		in.close();
	}
	else
	{
		cout << "Unable to open file";
		return "NOTFOUND";
	}
	return buf;
}
