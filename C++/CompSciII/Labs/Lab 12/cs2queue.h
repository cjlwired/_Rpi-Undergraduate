
#ifndef queue_h_
#define queue_h_

#include <list>

template <class T>
class queue {
 public:

  queue() : elements(elements){};

  queue( queue<T> const& other )
  {
	for (int i = 0; i < other.size(); i++)
		this.push (other.elements[i]);

  };

  bool empty() const
  {
	  return elements.size() == 0;
  };

  unsigned int size() const
  {
	  return elements.size();
  };

  T& front()
  {
	  return elements.front();
  };

  T const& front() const
  {
	  return elements.front();
  };

  T& back()
  {
	  return elements.back();
  };

  T const& back() const
  {
	  return elements.back();
  };

  void push( T const& value )
  {
	  elements.push_back(value);
  };

  void pop()
  {
	  elements.pop_front();
  };

 private:
  std::list<T> elements;
};

#endif
