#include <iostream>
#include <sstream>

using namespace std;
#include "animalParser.h"


AnimalParser::AnimalParser()
{
	// AnimalParser Constructor
	//cout<<"AnimalParser constructor"<<endl;
	
	foundSession = FALSE;

}
AnimalParser::~AnimalParser()
{

}
void AnimalParser::addAnimal(const::Animal &s)
{
	animalList.push_back(s);

}
void AnimalParser::addSession(const::Session &s)
{
	sessionList.push_back(s);

}
void AnimalParser::listAnimals()
{
	list<Animal>::iterator i;
	for (i = animalList.begin(); i != animalList.end(); i++)
    {
		cout<<*i<< " "<<endl;
	}
}
void AnimalParser::listSessions()
{
	list<Session>::iterator i;
	for (i = sessionList.begin(); i != sessionList.end(); i++)
    {
		cout<<*i<< " "<<endl;

	}
}
void AnimalParser::getAnimalNumbers(list<string> &numbers)
{
	list<Animal>::iterator i;
	for (i = animalList.begin(); i != animalList.end(); i++)	
	{
		//cout<<"InternalId is :"<<i->getInternalId()<<endl;
		//numbers.push_back(i->getInternalId());
	}

}
string& AnimalParser::getNumberOfAnimals()
{
	return numberOfAnimals;
}
string& AnimalParser::getNumberOfSessions()
{
	return numberOfSessions;
}
void AnimalParser::setCurrentNode(const::string &current)
{
	currentNode = current;
}
void AnimalParser::setCurrentValue(const::string &current)
{
	currentValue = current;

}
void AnimalParser::printCurrentNode()
{
	cout<<"Current Node:"<<currentNode<<" Value:"<<currentValue<<endl;
}


void AnimalParser::parseHtml(const std::string &html)
{
	cout<<"AnimalParser::parseHTML got:"<<html.size()<<endl;
	
}
void AnimalParser::on_start_document()
{
	cout << "on_start_document()" << std::endl;
}

void AnimalParser::on_end_document()
{
	cout << "on_end_document()" << std::endl;
}

void AnimalParser::on_start_element(const Glib::ustring& name,
                                   const AttributeList& attributes)
{
	cout<<"on_start_element()"<<endl;
	cout << "node name=" << name << std::endl;
	setCurrentNode(name);
	printCurrentNode();
	if (!name.compare("ads:sessions"))
	{
		foundSession = TRUE;
		cout<<"Found sessions"<<endl;

		// Print attributes:
		for(const auto& attr_pair : attributes)
		{
			//cout << "  Attribute " << attr_pair.name << " = " << attr_pair.value << std::endl<<std::endl;
			if (attr_pair.name.compare("count") == 0)
			{
				//cout<<"Found count"<<endl;
				numberOfSessions = attr_pair.value;
			}
		}
	}
	if (!name.compare("ads:session"))
	{
		cout<<"Found new session"<<endl;

		// Print attributes:
		for(const auto& attr_pair : attributes)
		{
			//cout << "  Attribute " << attr_pair.name << " = " << attr_pair.value << std::endl<<std::endl;
			if (attr_pair.name.compare("sessionType") == 0)
			{
					currentSession.type = attr_pair.value;
			}
			
		}
	}
	if (!name.compare("ads:animals"))
	{
		cout<<"Found animals"<<endl;
		for(const auto& attr_pair : attributes)
		{
			//cout << "  Attribute " << attr_pair.name << " = " << attr_pair.value << std::endl<<std::endl;
			if (attr_pair.name.compare("count") == 0)
			{
				//cout<<"Found count"<<endl;
				currentSession.animalCount = attr_pair.value;
			}
		}
		// last value for a session - so add to list
		addSession(currentSession);	
	}
	

}

void AnimalParser::on_end_element(const Glib::ustring& /* name */)
{
	cout<<"on_end_element"<<endl;
}
void AnimalParser::on_characters(const Glib::ustring& text)
{
	std::cout << "on_characters(): " << text << std::endl;
	setCurrentValue(text);
}

void AnimalParser::on_comment(const Glib::ustring& text)
{
	cout << "on_comment(): " << text << std::endl;
}

void AnimalParser::on_warning(const Glib::ustring& text)
{
	cout << "on_warning(): " << text << std::endl;
}

void AnimalParser::on_error(const Glib::ustring& text)
{
	cout << "on_error(): " << text << std::endl;
}

void AnimalParser::on_fatal_error(const Glib::ustring& text)
{
	cout << "on_fatal_error(): " << text << std::endl;
}

_xmlEntity* AnimalParser::on_get_entity(const Glib::ustring& name)
{
	//cout << "on_get_entity(): " << name << std::endl;

	//Call the base class:
	return SaxParser::on_get_entity(name);
}

void AnimalParser::on_entity_declaration(const Glib::ustring& name, xmlpp::XmlEntityType type, const Glib::ustring& publicId, const Glib::ustring& systemId, const Glib::ustring& content)
{
	cout << "on_entity_declaration(): name=" << name << ", publicId=" << publicId << ", systemId=" << systemId << ", content=" << content << std::endl;

	//Call the base class:
	SaxParser::on_entity_declaration(name, type, publicId, systemId, content);
}

