#include "animal.h"

Animal::Animal()   // Constructor
{
	internalId = "";
	eid = "";
	sex = "";
	dob = "";
	breed = "";
	sire = "";
	
}

Animal::Animal(const Animal &copyin)   // Copy constructor to handle pass by value.
{                             
	internalId = copyin.internalId;
	eid = copyin.eid;
	sex = copyin.sex;
	dob = copyin.dob;
	breed = copyin.breed;
	sire = copyin.sire;
}

ostream &operator<<(ostream &output, const Animal &aaa)
{
   output << aaa.internalId << ' ' << aaa.eid << ' ' << aaa.sex << ' ' << aaa.dob << ' '
		<<aaa.breed <<' '<< aaa.sire<<endl;
   return output;
}

Animal& Animal::operator=(const Animal &rhs)
{
   this->internalId = rhs.internalId;
   this->eid = rhs.eid;
   this->sex = rhs.sex;
   this->dob = rhs.dob;
   this->breed = rhs.breed;
   this->sire = rhs.sire;
   return *this;
}

int Animal::operator==(const Animal &rhs) const
{
   //if( this->x != rhs.x) return 0;
   //if( this->y != rhs.y) return 0;
   //if( this->z != rhs.z) return 0;
   return 1;
}

// This function is required for built-in STL list functions like sort
int Animal::operator<(const Animal &rhs) const
{
   //if( this->x == rhs.x && this->y == rhs.y && this->z < rhs.z) return 1;
   //if( this->x == rhs.x && this->y < rhs.y) return 1;
   //if( this->x < rhs.x ) return 1;
   return 0;
}

