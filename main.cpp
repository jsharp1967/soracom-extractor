#include <iostream>
#include <sstream>
using namespace std;

#include "xr5000.h"
#include "functions.h"
#include "messages.h"

#include <wiringPi.h> // Include WiringPi library!
const int butUp = 17;  //Active-low button - Broadcom pin 17, P1 pin 11
const int butYellow = 18; //Active-low button - Broadcom pin 18, P1 pin 12
const int butOrange = 27; //Active-low button - Broadcom pin 27, P1 pin 13
const int butRed = 22;    //Active-low button - Broadcom pin 22, P1 pin 15



int main(int argc, char *argv[])
{
	if (argc >= 2)
	{
		cout<<"Commands are "<<string(argv[1])<<endl;
	}
	else
	{
		cout<<"Command is either c for Command Line Mode or b for Front Panel Mode"<<endl;
		exit(0);
	}

	if (string(argv[1]) == "c")
	{
		cout<<"Welcome to soracom command programme"<<endl;
		cout<<"Command Line Mode"<<endl;
		Messages::Instance()->sendScreenReset();
		Messages::Instance()->sendActivityReady();
		//Messages::Instance()->sendIP("192.168.0.222");
		commandLineDriver();
	}	
	else if (string(argv[1]) == "b")
	{
		cout<<"Welcome to soracom command programme"<<endl;
		cout<<"Front Panel Mode"<<endl;
		Messages::Instance()->sendScreenReset();
		//Messages::Instance()->sendActivityReady();
		//Messages::Instance()->sendIP("192.168.0.222");
		buttonDriver();
	}
	else
	{
		cout<<"Error unrecognised command"<<endl;
		Messages::Instance()->sendSoracomOffline();
		exit(0);

	}

	Messages::Instance()->sendSoracomOffline();
    	return 0;
}
