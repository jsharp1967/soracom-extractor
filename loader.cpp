#include <iostream>
#include <sstream>

using namespace std;
#include "loader.h"
#include "xr5000.h"
#include <stdio.h>
#include <stdlib.h>
#include <libxml/xmlreader.h>

Loader::Loader()
{
	//Constructor
	//drive = new Drive();

}
Loader::~Loader()
{
	//Destructor
	//cout<<"Loader::~Loader()"<<endl;

}
bool Loader::checkStatus(const std::string &buffer)
{
	cout<<"Loader::checkStatus"<<endl;
	string command ="http://192.168.8.1:9000/polaris";
	XR5000::Instance()->executeCommand(command,buffer);

	return true;
}
bool Loader::loadAnimalData(const std::string &buffer)
{
	cout<<"Loader::loadData"<<endl;
	string command ="http://192.168.8.1/animals";
	string response;
	XR5000::Instance()->postData(command,buffer,response);
	cout<<"LoadAnimal Data Response:"<<response<<endl;
	return true;
}
