#include <iostream>
#include <sstream>

using namespace std;
#include "extractor.h"
#include "xr5000.h"
#include <stdio.h>
#include <stdlib.h>
#include <libxml/xmlreader.h>

Extractor::Extractor()
{
	//Constructor
	//drive = new Drive();

}
Extractor::~Extractor()
{
	//Destructor
	//cout<<"Extractor::~Extractor()"<<endl;

}
void Extractor::findNextWayPoint()
{

	
}
bool Extractor::checkStatus(const std::string &buffer)
{
	cout<<"Extractor::checkStatus"<<endl;
	//string command = "http://example.com/";
	string command ="http://192.168.8.1:9000/polaris";
	XR5000::Instance()->executeCommand(command,buffer);

	return true;
}
bool Extractor::getSessions(const std::string &buffer)
{
	//cout<<"Extractor::getSessions"<<endl;
	//string command = "http://example.com/";
	string command = "http://192.168.8.1:9000/sessions";
	if(XR5000::Instance()->executeCommand(command,buffer))
	{
		return true;
	}
	else
	{
		return false;
	}
}
int Extractor::getAnimalsInSession(const std::string &buffer, const std::string &sessionNumber)
{
	//cout<<"Extractor::getAnimalsInSession:"<<sessionNumber<<endl;
	//string command = "http://example.com/";
	string command = "http://192.168.8.1:9000/sessions/" + sessionNumber;
	XR5000::Instance()->executeCommand(command,buffer);
	return 0;
}

int Extractor::getAnimals(const std::string &buffer)
{
	cout<<"Extractor::getAnimals"<<endl;
	//string command = "http://example.com/";
	string command = "http://192.168.8.1:9000/animals";
	XR5000::Instance()->executeCommand(command,buffer);
	return 0;
}




