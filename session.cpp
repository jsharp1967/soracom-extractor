#include "session.h"

Session::Session()   // Constructor
{
	type = "";
	internalId = "";
	sessionId = "";
	name = "";
	startDate = "";
	endDate = "";
	animalCount = "";
	
}

Session::Session(const Session &copyin)   // Copy constructor to handle pass by value.
{                             
	type = copyin.type;
	internalId = copyin.internalId;
	sessionId = copyin.sessionId;
	name = copyin.name;
	startDate = copyin.startDate;
	endDate = copyin.endDate;
	animalCount = copyin.animalCount;
}


ostream &operator<<(ostream &output, const Session &aaa)
{
   output <<aaa.type<<' '<<aaa.internalId << ' ' << aaa.sessionId << ' ' << aaa.name << ' ' << aaa.startDate << ' '
		<<aaa.endDate <<' '<< aaa.animalCount<<endl;
   return output;
}

Session& Session::operator=(const Session &rhs)
{
	this->type = rhs.type;
	this->internalId = rhs.internalId;
	this->sessionId = rhs.sessionId;
	this->name = rhs.name;
	this->startDate = rhs.startDate;
	this->endDate = rhs.endDate;
	this->animalCount = rhs.animalCount;
	return *this;
}
string Session::getType()
{
	return this->type;
}
string Session::getInternalId()
{
	return this->internalId;
}

int Session::operator==(const Session &rhs) const
{
   //if( this->x != rhs.x) return 0;
   //if( this->y != rhs.y) return 0;
   //if( this->z != rhs.z) return 0;
   return 1;
}

// This function is required for built-in STL list functions like sort
int Session::operator<(const Session &rhs) const
{
   //if( this->x == rhs.x && this->y == rhs.y && this->z < rhs.z) return 1;
   //if( this->x == rhs.x && this->y < rhs.y) return 1;
   //if( this->x < rhs.x ) return 1;
   return 0;
}

