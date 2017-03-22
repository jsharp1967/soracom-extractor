#ifndef XR5000_H_
#define XR5000_H_


#include <iostream>
#include <sstream>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <curl/curl.h>

using namespace std;

class XR5000
{
	public:
	static XR5000* Instance();
	void getStatus();
	bool executeCommand(string,const std::string &);
	bool executeCommand(string);
	void postData(string, const std::string &, const std::string &);
	void parseHtml(const std::string &);
	CURLcode res;
	CURL	*curl_handle;

	private:
	XR5000();
	XR5000(XR5000 const&){};
	//XR5000& operator=(XR5000 const&){};
	static XR5000* m_pInstance;



};
#endif /* XR5000_H_*/
