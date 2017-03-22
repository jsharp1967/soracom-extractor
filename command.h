#include <iostream>
#include <sstream>
using namespace std;
#include "functions.h"

class Command
{

        public:
        Command();
        void displayBaseMenuOptions();
        void processInput(string input);
        ~Command();
};
