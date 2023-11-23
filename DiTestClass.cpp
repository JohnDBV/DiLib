#include "DiTestClass.h"
#include <iostream>

void di::test::DiTestClass::say(std::string_view message) const
{
	std::cout << message;
}

template<typename T>
T di::test::DiTestClass::add(T first, T second)
{
	return first + second;
}

std::string_view di::test::DiTestClass::getMemberVariable()
{
	return m_memberVariable;
}

void di::test::DiTestClass::setMemberVariable(std::string_view newValue)
{
	m_memberVariable = newValue;
}