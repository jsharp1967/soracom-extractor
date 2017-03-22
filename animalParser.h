#ifndef ANIMALPARSER_H_
#define ANIMALPARSER_H_

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <libxml++/libxml++.h>
#include <list>
#include "animal.h"
#include "session.h"

using namespace std;

class AnimalParser: public xmlpp::SaxParser
{
	public:
	AnimalParser();
	~AnimalParser() override;
	void parseHtml(const std::string &);
	void setCurrentNode(const::string &);
	const::string& getCurrentNode(){return currentNode;};
	void setCurrentValue(const::string &);
	const::string&  getCurrentValue(){return currentValue;};
	void printCurrentNode();
	string& getNumberOfAnimals();
	string& getNumberOfSessions();
	void addAnimal(const Animal &);
	void addSession(const Session &);
	void listAnimals();
	void listSessions();

	void getAnimalNumbers(list<string>&);

	protected:
  	//overrides:
	void on_start_document() override;
	void on_end_document() override;
	void on_start_element(const Glib::ustring& name,
				const AttributeList& properties) override;
	void on_end_element(const Glib::ustring& name) override;
	void on_characters(const Glib::ustring& characters) override;
	void on_comment(const Glib::ustring& text) override;
	void on_warning(const Glib::ustring& text) override;
	void on_error(const Glib::ustring& text) override;
	void on_fatal_error(const Glib::ustring& text) override;
	_xmlEntity* on_get_entity(const Glib::ustring& name) override;
	void on_entity_declaration(const Glib::ustring& name, xmlpp::XmlEntityType type,
	const Glib::ustring& publicId, const Glib::ustring& systemId, const Glib::ustring& content) override;

	private:
	string numberOfSessions;
	string numberOfAnimals;
	string currentNode;
	string currentValue;
	Session	currentSession;
	Animal currentAnimal;
	bool foundSession; // TRUE = YES, FALSE = NO
	list<Animal> animalList;
	list<Session> sessionList;

};
#endif /* ANIMALPARSER_H_*/
