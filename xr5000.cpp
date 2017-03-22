#include <iostream>
#include <sstream>

using namespace std;
#include "xr5000.h"


//  libcurl variables for error strings and returned data

static char errorBuffer[CURL_ERROR_SIZE];

//:
//  libcurl write callback function
//

static int writer(char *data, size_t size, size_t nmemb,
                  std::string *writerData)
{
	if (writerData == NULL)
		return 0;

	writerData->append(data, size*nmemb);

	return size * nmemb;
}


XR5000* XR5000::m_pInstance = NULL;

XR5000::XR5000()
{
	// XR5000 Constructor
	//cout<<"XR5000 constructor"<<endl;
	

}
XR5000* XR5000::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new XR5000;
	}
	return m_pInstance;
}
bool XR5000::executeCommand(string url,const std::string &buffer)
{
	cout<<"XR5000::executeCommand():"<<url<<endl;
	
	curl_handle = curl_easy_init();
	if(curl_handle)
	{
		curl_easy_setopt(curl_handle, CURLOPT_ERRORBUFFER, errorBuffer);
		curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
		/* Switch on full protocol/debug output while testing */
		curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
		/* disable progress meter, set to 0L to enable and disable debug output */
		curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
		/* send all data to this function and buffer */
		curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, writer);

		/*Connection timeout*/
		curl_easy_setopt(curl_handle,CURLOPT_CONNECTTIMEOUT,2);
		
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &buffer);
		
		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl_handle);
		
		/* Check for errors */
		if(res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			return false;
		}

		/* always cleanup */
		curl_easy_cleanup(curl_handle);
		return true;
	}
	return false;
	
}

bool XR5000::executeCommand(string url)
{
	cout<<"XR5000::executeCommand()"<<endl;
	curl_handle = curl_easy_init();
	if(curl_handle)
	{
		curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
		
		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl_handle);
		/* Check for errors */
		if(res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			return false;
		}

			/* always cleanup */
		curl_easy_cleanup(curl_handle);
		return true;
	}
	return false;
}

void XR5000::getStatus()
{
	cout<<"XR5000::getStatus()"<<endl;
	curl_handle = curl_easy_init();
	if(curl_handle)
	{
		curl_easy_setopt(curl_handle, CURLOPT_URL, "http://example.com");
		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl_handle);
		/* Check for errors */
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

			/* always cleanup */
		curl_easy_cleanup(curl_handle);
	}
}

void XR5000::parseHtml(const std::string &html)
{
	cout<<"XR5000::parseHTML got:"<<html.size()<<endl;
	
}
void XR5000::postData(string url, const std::string &buffer, const std::string &response_buffer)
{
        cout<<"XR5000::postData():"<<url<<endl;
        cout<<"Data to post is :"<<buffer<<" Size:"<<buffer.length();

        curl_handle = curl_easy_init();
        if(curl_handle)
        {
                curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, buffer.c_str());
                curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, (long)buffer.length());


                curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);

                /* disable progress meter, set to 0L to enable and disable debug output */
                curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

                curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, writer);

                curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &response_buffer);

                /* Perform the request, res will get the return code */
                res = curl_easy_perform(curl_handle);
                /* Check for errors */
                if(res != CURLE_OK)
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                        curl_easy_strerror(res));

                /* always cleanup */
                curl_easy_cleanup(curl_handle);

        }
}

