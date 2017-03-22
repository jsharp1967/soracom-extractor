#ifndef SESSION_H_
#define SESSION_H_
#include <iostream>
#include <list>
using namespace std;

// The List STL template requires overloading operators =, == and <.

class Session
{
	friend ostream &operator<<(ostream &, const Session &);

	public:
	string type;
	string internalId;
	string sessionId;
	string name;
	string startDate;
	string endDate;
	string animalCount;
	string getType();
	string getInternalId();

      Session();
      Session(const Session &);
      ~Session(){};
      Session &operator=(const Session &rhs);
      int operator==(const Session &rhs) const;
      int operator<(const Session &rhs) const;
};
#endif
