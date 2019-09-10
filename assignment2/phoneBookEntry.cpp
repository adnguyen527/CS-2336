/*
 * phoneBookEntry.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: 2gree
 */

#include <iostream>
#include <string>
#include <vector>

#include "phoneBookEntry.h"

phoneBookEntry::phoneBookEntry(){
	person="";
	number = "";
	e = "";
}
phoneBookEntry::phoneBookEntry(const std::string &newName, const std::string &newNumber){
	person = newName;
	number = newNumber;
	e = "";
}
phoneBookEntry::phoneBookEntry(const std::string &newName, const std::string &newNumber,  const std::string &newEmail){
	person = newName;
	number = newNumber;
	e = newEmail;
}
phoneBookEntry::phoneBookEntry(const phoneBookEntry &from){
	person = from.name();
	number = from.phoneNumber();
	e = from.email();
}
std::string name() const{
	return person;
}
std::string phoneNumber() const{
	return number;
}
std::string email() const{
	return e;
}
void phoneNumber(const std::string &newNumber){
	number=newNumber;
}
void email(const std::string &newEmail){
	e=newEmail;
}
