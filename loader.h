#ifndef LOADER_H_
#define LOADER_H_

#include <iostream>
#include <sstream>
using namespace std;
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

class Loader
{
	public:
	Loader();
	~Loader();
	bool checkStatus(const std::string &response); // TRUE = OK, FALSE = NO RESPONSE
	bool loadAnimalData(const std::string &buffer);
	private:
	//Drive *drive;

};
#endif /* LOADER_H_ */
