/* Control file for graph */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "DirectedGraph.h"

void printMenu();
int getUserMenuSelection();
int getUserInput(std::string prompt);
void addVertex(DirectedGraph *graph);
void addEdge(DirectedGraph *graph);
void removeEdge(DirectedGraph *graph);
void modifyEdge(DirectedGraph *graph);
void displayVertex(DirectedGraph *graph);
void displayVertices(DirectedGraph *graph);



int main()
{
  int action;
  DirectedGraph* graph = new DirectedGraph();

  do {
    /* Display the actions menu and get a selection from the user */
    printMenu();
    action = getUserMenuSelection();

    switch (action) {
      case 1: addVertex(graph);		break;
      case 2: addEdge(graph);    	break;
      case 3: removeEdge(graph);  	break;
      case 4: modifyEdge(graph);   	break;
      case 5: displayVertex(graph);  	break;
      case 6: displayVertices(graph);	break;
      case 7: break;
      default: std::cout << "Unrecognized option" << std::endl;
    }
  } while (action != 7);

  delete graph;
  return 0;
}


/* Display a list of actions for the user */
void printMenu()
{
  std::cout << std::endl;
  std::cout << "Select from the following:" << std::endl;
  std::cout << "\t1. Add a vertex" << std::endl;
  std::cout << "\t2. Add an edge" << std::endl;
  std::cout << "\t3. Delete an edge" << std::endl;
  std::cout << "\t4. Modify an edge weight" << std::endl;
  std::cout << "\t5. Display vertex information" << std::endl;
  std::cout << "\t6. Display adjacency list" << std::endl;
  std::cout << "\t7. Exit" << std::endl;
}

/* Prompt the user for a menu selection */
int getUserMenuSelection()
{
  int selection;
  std::cout << "Select> ";
  std::cin >> selection;
  std::cin.ignore(); /* Throw away the newline */
  return selection;
}

/* Display a prompt and read input from the user */
int getUserInput(std::string prompt)
{
  int i;
  std::cout << prompt;
  std::cin >> i;
  return i;
}

/* Add a vertex to the directed graph */
void addVertex(DirectedGraph *graph)
{
  int index;
  index = graph->addVertex();
  std::cout << "** Vertex \"" << index << "\" added." << std::endl;
}

/* Add an edge to the directed graph */
void addEdge(DirectedGraph *graph)
{
  int src, dest, weight;
  
  src = getUserInput("Source index: ");
  if (!graph->containsVertex(src)) {
    std::cout << "** Vertex \"" << src << "\" does not exist." << std::endl;
    return;
  }
  dest = getUserInput("Destination index: ");
  if (!graph->containsVertex(dest)) {
    std::cout << "** Vertex \"" << dest << "\" does not exist." << std::endl;
    return;
  }

  /* Check to see if the edge exists already */
  if (graph->containsEdge(src, dest)) {
    std::cout << "** There is already an edge between \"" << src
	    << "\" and \"" << dest << "\"." << std::endl;
    return;
  }
  
  /* Get the edge weight value and convert it into an integer */
  weight = getUserInput("Edge weight value: ");

  graph->addEdge(src, dest, weight);
  std::cout << "** Edge of weight \"" << weight << "\" added from \"" << src
	  << "\" to \"" << dest << "\"." << std::endl;
}

/* Remove an edge from the directed graph */
void removeEdge(DirectedGraph *graph)
{
  int src, dest;
  
  src = getUserInput("Source index: ");
  if (!graph->containsVertex(src)) {
    std::cout << "** Index \"" << src << "\" does not exist." << std::endl;
    return;
  }
  dest = getUserInput("Destination index: ");
  if (!graph->containsVertex(dest)) {
    std::cout << "** Index \"" << dest << "\" does not exist." << std::endl;
    return;
  }

  /* Check to see if the edge exists already */
  if (!graph->containsEdge(src, dest)) {
    std::cout << "** There is no edge between \"" << src
	    << "\" and \"" << dest << "\"." << std::endl;
    return;
  }
  
  graph->removeEdge(src, dest);
  std::cout << "** Edge from \"" << src << "\" to \"" << dest << "\" removed." << std::endl;
}

/* Add an edge to the directed graph */
void modifyEdge(DirectedGraph *graph)
{
  int weight, src, dest;
  
  src = getUserInput("Source index: ");
  if (!graph->containsVertex(src)) {
    std::cout << "** Vertex \"" << src << "\" does not exist." << std::endl;
    return;
  }
  dest = getUserInput("Destination index: ");
  if (!graph->containsVertex(dest)) {
    std::cout << "** Vertex \"" << dest << "\" does not exist." << std::endl;
    return;
  }

  /* Check to see if the edge exists */
  if (!graph->containsEdge(src, dest)) {
    std::cout << "** There is no edge between \"" << src
	    << "\" and \"" << dest << "\"." << std::endl;
    return;
  }
  
  /* Print out the current edge value */
  weight = graph->getEdgeWeight(src, dest);
  std::cout << "Current edge value is \"" << weight << "\"." << std::endl;

  /* Get the new edge value and convert it into an integer */
  weight = getUserInput("New edge weight value: ");

  graph->addEdge(src, dest, weight);
  std::cout << "** Edge from \"" << src << "\" to \"" << dest << "\" changed to \""
	  << weight << "\"." << std::endl;
}

void displayVertex(DirectedGraph *graph)
{
  int index = getUserInput("Vertex index: ");
  if (!graph->containsVertex(index)) {
    std::cout << "** Vertex \"" << index << "\" does not exist." << std::endl;
    return;
  }
  graph->printVertex(index);
  std::cout << std::endl;
}

/* display all the edges of all vertices in an adjacency list */
void displayVertices(DirectedGraph *graph)
{
  graph->printAll();
  std::cout << std::endl;
  std::cout << graph->size() << " vertices total." << std::endl;
}
