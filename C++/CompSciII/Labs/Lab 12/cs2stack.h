
#ifndef stack_h_
#define stack_h_

#include <vector>

template <class T>
class stack {
 public:

  stack() : values(values){};

  stack( stack<T> const& other )
  {
	  for (int i = 0; i < other.size(); i++)
		this.push (other.values[i]);
  };

  bool empty() const
  {
	  return values.size() == 0;
  };

  unsigned int size() const
  {
	  return values.size();
  };

  T& top()
  {
	  return values.back();
  };

  T const& top() const
  {
	return values.back();
  };

  void push( T const& value )
  {
	  values.push_back(value);
  };

  void pop()
  {
	  values.pop_back();
  };
  
 private:
  std::vector<T> values;
};

#endif
