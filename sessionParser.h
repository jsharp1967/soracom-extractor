#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <libxml++/libxml++.h>
#include <list>
#include "session.h"

using namespace std;

class SessionParser: public xmlpp::SaxParser
{
	public:
	SessionParser();
	~SessionParser() override;
	void parseHtml(const std::string &);
	void setCurrentNode(const::string &);
	const::string& getCurrentNode(){return currentNode;};
	void setCurrentValue(const::string &);
	const::string&  getCurrentValue(){return currentValue;};
	void printCurrentNode();
	string& getNumberOfSessions();
	void addSession(const Session &);
	void listSessions();

	void getSessionNumbers(list<string>&);

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
	string currentNode;
	string currentValue;
	Session currentSession;
	bool foundSession; // TRUE = YES, FALSE = NO
	list<Session> sessionList;

};
#endif /* PARSER_H_*/
