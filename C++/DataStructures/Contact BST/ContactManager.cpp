#include <iostream>
#include <iomanip>
#include <string>

#include "BinarySearchTree.h"
#include "Contact.h"

using namespace std;

/* Display a list of actions for the user */
void printMenu()
{
  cout << endl;
  cout << "Select from the following:" << endl;
  cout << "\t1. Add a contact" << endl;
  cout << "\t2. Delete a contact" << endl;
  cout << "\t3. Find a contact" << endl;
  cout << "\t4. Update a contact" << endl;
  cout << "\t5. List all contacts" << endl;
  cout << "\t6. Exit" << endl;
}

/* Display the header at the top of a list of contact information */
void printContactHeader()
{
  cout << setw(25) << left << "Name";
  cout << setw(35) << left << "Address";
  cout << setw(15) << left << "Phone No." << endl;
  cout << setw(25) << left << "------------";
  cout << setw(35) << left << "------------";
  cout << setw(15) << left << "------------" << endl;
}

/* Prompt the user for a menu selection */
int getUserMenuSelection()
{
  int selection;
  cout << "Select> ";
  cin >> selection;
  cin.ignore(); /* Throw away the newline */
  return selection;
}

/* Display a prompt and read input from the user */
string getUserInput(string prompt)
{
  string line;
  cout << prompt;
  getline(cin, line);
  return line;
}

/* Add a contact to the binary search tree */
void addContact(BinarySearchTree *contacts)
{
  /* Get a non-empty name from the user */
  string name = getUserInput("Contact Name: ");
  if (name == "") {
    cout << "** Contact name cannot be blank." << endl;
  } else {
    /* Get the rest of the contact information */
    string address = getUserInput("Address: ");
    string phoneNum = getUserInput("Phone Number: ");

    /* Create a contact and add it to the binary tree */
    Contact contact(name, address, phoneNum);
    contacts->insert(contact);
    cout << "** Contact \"" << name << "\" added." << endl;
  }
}

/* Remove a contact from the binary search tree */
void deleteContact(BinarySearchTree *contacts)
{
  string name = getUserInput("Contact Name: ");
  if (!contacts->contains(name)) {
    cout << "** Contact \"" << name << "\" does not exist." << endl;
  } else {
    contacts->remove(name);
    cout << "** Contact \"" << name << "\" removed." << endl;
  }
}

/* Find a specific contact's name in the list of contacts */
void findContact(BinarySearchTree *contacts)
{
  string name = getUserInput("Contact Name: ");
  if (!contacts->contains(name)) {
    cout << "** Contact \"" << name << "\" not found." << endl;
  } else {
    Contact c = contacts->get(name);
    printContactHeader();
    cout << c << endl;
  }
}

/* Updates a specific contact's address or phone number */
void updateContact(BinarySearchTree *contacts)
{
  Contact c;
  string address, phoneNumber, prompt;
  string name = getUserInput("Contact Name: ");

  if (!contacts->contains(name)) {
    cout << "** Contact \"" << name << "\" does not exist." << endl;
  } else {
    Contact c = contacts->get(name);
    cout << "Updating contact information for: " << name << endl;

    /* Get the updated address, or use current if none entered */
    prompt = "Address [" + c.getAddress() + "]: ";
    address = getUserInput(prompt);
    if (address != "") c.setAddress(address);

    /* Get the updated phone number, or use current if none entered */
    prompt = "Phone Number [" + c.getPhoneNumber() + "]: ";
    phoneNumber = getUserInput(prompt);
    if (phoneNumber != "") c.setPhoneNumber(phoneNumber);

    /* Replace the old contact node with the modified one */
    contacts->insert(c);
    cout << "** Contact information updated!" << endl;
  }
}

/* Lists all contact names, addresses, and phone numbers */
void listContacts(BinarySearchTree *contacts)
{
  printContactHeader();
  contacts->printInOrder();
  cout << endl;
  cout << contacts->size() << " contacts total." << endl;
}


int main()
{
  int action;
  BinarySearchTree *contacts = new BinarySearchTree();

  do {
    /* Display the actions menu and get a selection from the user */
    printMenu();
    action = getUserMenuSelection();

    switch (action) {
      case 1: addContact(contacts);     break;
      case 2: deleteContact(contacts);  break;
      case 3: findContact(contacts);    break;
      case 4: updateContact(contacts);  break;
      case 5: listContacts(contacts);   break;
      case 6: break;
      default: cout << "Unrecognized option" << endl;
    }
  } while (action != 6);

  delete contacts;
  return 0;
}
