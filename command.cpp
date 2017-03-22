#include "command.h"

Command::Command()
{
        //Constructor



}
void Command::displayBaseMenuOptions()
{

        cout<<"Command options are:"<<endl;
        cout<<"Execute command:\tx"<<endl;
        cout<<"Get Status:\t\ts"<<endl;
        cout<<"Get Sessions:\t\tn"<<endl;
        cout<<"Get  Animals:\t\ta"<<endl;
        cout<<"Get Animals in Session:\t\tb"<<endl;
        cout<<"Upload files:\t\tu"<<endl;
        cout<<"Upload Compressed files:\tv"<<endl;
        cout<<"Compress files:\t\tc"<<endl;
        cout<<"Decompress files:\t\td"<<endl;
        cout<<"Help:\t\t\th"<<endl;
        cout<<"Quit:\t\t\tq"<<endl;

}
void Command::processInput(string input)
{

        cout<<"Command::processInput:"<<input<<endl;
        stringstream myStream(input);

}
Command::~Command()
{
        //Destructor

}

