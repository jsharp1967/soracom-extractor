#ifndef UPLOADER_H_
#define UPLOADER_H_


#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "uploader.h"

//#define UPLOAD_FILE_AS  "test.txt"
//#define REMOTE_URL      "FTP://192.168.0.71/" UPLOAD_FILE_AS
//#define RENAME_FILE_TO  "sent.txt"
//#define userpass "pi:raspberry"


using namespace std;

class Uploader
{
	public:
	static Uploader* Instance();
	bool uploadFile(const std::string&,const std::string&);
	CURLcode res;
	CURL	*curl_handle;

	private:
	Uploader();
	Uploader(Uploader const&){};
	//Uploader& operator=(Uploader const&){};
	static Uploader* m_pInstance;



};
#endif /* Uploader_H_*/
