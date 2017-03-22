#include <iostream>
#include <sstream>

using namespace std;

#include "uploader.h"


Uploader* Uploader::m_pInstance = NULL;

static int progress_callback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{
	cout<<"Progress:"<<dltotal<<","<<dlnow<<","<<ultotal<<","<<ulnow<<endl;


}

Uploader::Uploader()
{
	// Uploader Constructor
	cout<<"**TRANSMISSION INITIATED**"<<endl;
	

}
Uploader* Uploader::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new Uploader;
	}
	return m_pInstance;
}

bool Uploader::uploadFile(const std::string &fileName,const std::string &url)
{
	cout<<"Source file path: "<<fileName<<endl;
	cout<<"Target URL: "<<url<<endl;
	
	FILE *hd_src;
	struct stat file_info;
	curl_off_t fsize;

	//struct curl_slist *headerlist=NULL;
	//static const char buf_1 [] = "RNFR " UPLOAD_FILE_AS;
	//static const char buf_2 [] = "RNTO " RENAME_FILE_TO;

	if(stat(fileName.c_str(), &file_info)) 
    	{
		printf("Couldnt open '%s': %s\n", fileName.c_str(), strerror(errno));
			return false;
    	}
	fsize = (curl_off_t)file_info.st_size;

	printf("Local file size: %" CURL_FORMAT_CURL_OFF_T " bytes.\n", fsize);

	hd_src = fopen(fileName.c_str(), "rb");


	curl_global_init(CURL_GLOBAL_ALL);

	
	curl_handle = curl_easy_init();
	if(curl_handle)
	{
		//Test entries
		//curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
		//curl_easy_setopt(curl_handle, CURLOPT_FTP_USE_EPSV, 0L);
		//headerlist = curl_slist_append(headerlist, buf_1);
		//headerlist = curl_slist_append(headerlist, buf_2);

		//const char *userpass = "pi:raspberry";
		
		/* enable uploading */
		curl_easy_setopt(curl_handle, CURLOPT_UPLOAD, 1L);
		// Upload timeout
		curl_easy_setopt(curl_handle, CURLOPT_FTP_RESPONSE_TIMEOUT, 600);

		/* specify target */
		curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());

		/* pass in that last of FTP commands to run after the transfer */
		//curl_easy_setopt(curl_handle, CURLOPT_POSTQUOTE, headerlist);

		/* now specify which file to upload */
		curl_easy_setopt(curl_handle, CURLOPT_READDATA, hd_src);

		curl_easy_setopt(curl_handle, CURLOPT_USERPWD, userpass);


		curl_easy_setopt(curl_handle, CURLOPT_INFILESIZE_LARGE,
                     (curl_off_t)fsize);
		
		curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 0);
		curl_easy_setopt(curl_handle, CURLOPT_PROGRESSFUNCTION, progress_callback);
		
		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl_handle);
		/* Check for errors */
		if(res != CURLE_OK) 
		{
			fprintf(stderr, "Upload failed: %s\n", curl_easy_strerror(res));
			cout << "**Transmission Failed** \n";
			printf("%" CURL_FORMAT_CURL_OFF_T " bytes failed to send.\n", fsize);
			//curl_slist_free_all (headerlist);
			/* always cleanup */
			curl_easy_cleanup(curl_handle);
			fclose(hd_src); /* close the local file */
			curl_global_cleanup();
			return false;
		}
		else
		{
			cout << "**Transmission Complete** \n" ;
			printf("%" CURL_FORMAT_CURL_OFF_T " bytes sent.\n", fsize);
			//curl_slist_free_all (headerlist);
			/* always cleanup */
			curl_easy_cleanup(curl_handle);
		}
		
	}
	else
	{
		fclose(hd_src); /* close the local file */
		curl_global_cleanup();
		return false;
	}	
	fclose(hd_src); /* close the local file */
	curl_global_cleanup();
	return true;
}


