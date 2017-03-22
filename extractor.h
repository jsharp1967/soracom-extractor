#ifndef EXTRACTOR_H_
#define EXTRACTOR_H_

#include <iostream>
#include <sstream>
using namespace std;
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
//#include "drive.h"

class Extractor
{
	public:
	Extractor();
	~Extractor();
	bool checkStatus(const std::string &response); // TRUE = OK, FALSE = NO RESPONSE
	bool getSessions(const std::string &response); // Returns number of sessions
	int getAnimals(const std::string &response); // Returns number of sessions
	int getAnimalsInSession(const std::string &response, const std::string &sessionNumber); // Returns number of sessions
	void findNextWayPoint();
	private:
	//Drive *drive;

};
#endif /* EXTRACTOR_H_ */
