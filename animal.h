#ifndef ANIMAL_H_
#define ANIMAL_H_

#include <iostream>
#include <list>
using namespace std;

// The List STL template requires overloading operators =, == and <.

class Animal
{
	friend ostream &operator<<(ostream &, const Animal &);

	public:
	string internalId;
	string eid;
	string sex;
	string dob;
	string breed;
	string sire;

      Animal();
      Animal(const Animal &);
      ~Animal(){};
      Animal &operator=(const Animal &rhs);
      int operator==(const Animal &rhs) const;
      int operator<(const Animal &rhs) const;
};

#endif
