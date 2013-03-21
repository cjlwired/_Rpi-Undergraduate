#include <iomanip>
#include "Contact.h"

using namespace std;

Contact::Contact(const Contact &c)
{
  m_name = c.m_name;
  m_address = c.m_address;
  m_phoneNumber = c.m_phoneNumber;
}

Contact::Contact(string name, string address, string phoneNumber)
{
  m_name = name;
  m_address = address;
  m_phoneNumber = phoneNumber;
}

Contact Contact::operator=(Contact &right)
{
  this->m_name = right.m_name;
  this->m_address = right.m_address;
  this->m_phoneNumber = right.m_phoneNumber;
  return *this;
}

bool Contact::operator==(string &right)
{
  return (!stricmp(m_name.data(), right.data()) ? true : false);
}

bool Contact::operator!=(string &right)
{
  return (stricmp(m_name.data(), right.data()) ? true : false);
}

bool Contact::operator>(string &right)
{
  return (stricmp(m_name.data(), right.data()) > 0 ? true : false);
}

bool Contact::operator<(string &right)
{
  return (stricmp(m_name.data(), right.data()) < 0 ? true : false);
}

bool Contact::operator>=(string &right)
{
  return (*this > right || *this == right);
}

bool Contact::operator<=(string &right)
{
  return (*this < right || *this == right);
}

ostream &operator<<(ostream &strm, Contact &obj)
{
  strm << setw(25) << left << obj.m_name.data();
  strm << setw(35) << left << obj.m_address.data();
  strm << setw(15) << left << obj.m_phoneNumber.data();
  return strm;
}