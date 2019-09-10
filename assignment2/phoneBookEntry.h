/*
 * phoneBookEntry.h
 *
 *  Created on: Oct 10, 2018
 *      Author: 2gree
 */

#ifndef PHONEBOOKENTRY_H_
#define PHONEBOOKENTRY_H_

#include <string>
class phoneBookEntry
{
private:
	std::string person;
	std::string number;
	std::string e;
public:
	phoneBookEntry();
	phoneBookEntry(const std::string &name, const std::string &number);
	phoneBookEntry(const std::string &name, const std::string &number,  const std::string &email);
	phoneBookEntry(const phoneBookEntry &from);
	std::string name() const;
	std::string phoneNumber() const;
	std::string email() const;
	void phoneNumber(const std::string &newNumber);
	void email(const std::string &newEmail);
};


#endif /* PHONEBOOKENTRY_H_ */
