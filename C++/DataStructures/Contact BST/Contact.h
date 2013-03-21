#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>

#ifdef HAVE_STRCASECMP
/* strcasecmp doesn't exist on Windows, so if we're building on
 * unix, just define stricmp to be strcasecmp and define
 * HAVE_STRCASECMP as a compiler flag.
 */
#define stricmp strcasecmp
#endif

class Contact
{
  private:
    std::string m_name;
    std::string m_address;
    std::string m_phoneNumber;

  public:
    Contact() {}
    Contact(const Contact &);
    Contact(std::string name)
      { m_name = name; }

    Contact(std::string name, std::string address, std::string phoneNumber);

    /* Contact address setter and getter */
    void setAddress(std::string address)
      { m_address = address; }
    std::string getAddress()
      { return m_address; }

    /* Contact phone number setter and getter */
    void setPhoneNumber(std::string phoneNumber)
      { m_phoneNumber = phoneNumber; }
    std::string getPhoneNumber()
      { return m_phoneNumber; }

    /* Operator overloads */
    Contact operator=(Contact &);

    bool operator==(std::string &);
    bool operator==(Contact &c) { return *this == c.m_name; }

    bool operator!=(std::string &);
    bool operator!=(Contact &c) { return *this != c.m_name; }

    bool operator>(std::string &);
    bool operator>(Contact &c) { return *this > c.m_name; }

    bool operator<(std::string &);
    bool operator<(Contact &c) { return *this < c.m_name; }

    bool operator>=(std::string &);
    bool operator>=(Contact &c) { return *this >= c.m_name; }

    bool operator<=(std::string &);
    bool operator<=(Contact &c) { return *this <= c.m_name; }

    /* Display properly formatted contact information */
    friend std::ostream &operator<<(std::ostream &, Contact &);
};
#endif
