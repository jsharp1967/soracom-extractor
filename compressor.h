#ifndef COMPRESSOR_H_
#define COMPRESSOR_H_


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
#include <gzstream.h>


using namespace std;

class Compressor
{
	public:
	static Compressor* Instance();
	bool compressFile(const std::string&,const std::string&);
	bool dcompressFile(const std::string&,const std::string&);

	private:
	Compressor();
	Compressor(Compressor const&){};
	
	static Compressor* m_pInstance;



};
#endif /* COMPRESSOR_H_*/
