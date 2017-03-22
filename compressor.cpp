#include <iostream>
#include <sstream>

using namespace std;

#include "compressor.h"


Compressor* Compressor::m_pInstance = NULL;

Compressor::Compressor()
{
	// Compressor Constructor
	cout<<"COMPRESSING FILE"<<endl;
	
}
Compressor* Compressor::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new Compressor;
	}
	return m_pInstance;
}

bool Compressor::compressFile(const std::string &fileName,const std::string &cfileName)
{
	cout<<"Compressing file name: "<<fileName<<endl;
	cout<<"Compressed filename: "<<cfileName<<endl;
	
	ogzstream  out(cfileName.c_str());
    if (!out.good()) 
    {
        std::cerr << "ERROR: Opening file `" << cfileName << "' failed.\n";
		return false;
    }
    std::ifstream in(fileName.c_str());
    if (!in.good())
    {
        std::cerr << "ERROR: Opening file `" << fileName << "' failed.\n";
		return false;
    }
    char c;
    while ( in.get(c))
	out << c;
    in.close();
    out.close();
    if (!in.eof())
    {
        std::cerr << "ERROR: Reading file `" << fileName << "' failed.\n";
		return false;
    }
    if (!out.good())
    {
        std::cerr << "ERROR: Writing file `" << cfileName << "' failed.\n";
		return false;
    }	
	return true;
}
bool Compressor::dcompressFile(const std::string &cfileName,const std::string &dfileName)
{
	cout<<"Compressed file name: "<<cfileName<<endl;
	cout<<"DeCompressed filename: "<<dfileName<<endl;

    igzstream in(cfileName.c_str());
    if (!in.good())
    {
		std::cerr << "ERROR: Opening file `" << cfileName << "' failed.\n";
		return false;
		
    }
    std::ofstream  out(dfileName.c_str());
    if (!out.good())
    {
        std::cerr << "ERROR: Opening file `" << dfileName<< "' failed.\n";
		return false;
    }
    char c;
    while ( in.get(c))
	out << c;
    in.close();
    out.close();
    if (!in.eof())
    {
        std::cerr << "ERROR: Reading file `" << cfileName << "' failed.\n";
		return false;
    }
    if ( ! out.good()) {
        std::cerr << "ERROR: Writing file `" << dfileName << "' failed.\n";
		return false;
    }
	return true;
}

