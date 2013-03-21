
//  File:    cs2list.h
//  Author:  Chuck Stewart
//  Purpose: A simplified implementation of a generic list container
//    class, including the iterator, but not the const_iterators.
//
//  Overview:  Three separate classes are defined:  a Node class, an
//    iterator class, and the actual list class.  The underlying list
//    is doubly-linked, but there is no dummy head node and the list
//    is not circular.


#ifndef cs2list_h_
#define cs2list_h_

///////////////////////////////////////////////////////////////////
///////////////         Node class        /////////////////////////
///////////////////////////////////////////////////////////////////

template <class T>
class Node {
public:
  Node( ) : next_(0), prev_(0) {}
  Node( const T& v ) : value_(v), next_(0), prev_(0) {}
  T value_;
  Node<T>* next_;
  Node<T>* prev_;
};


//  This is what's called a "forward declaration" of the templated
//  cs2list class so that the iterator class allows it to be named as
//  a friend.

template <class T> class cs2list;

///////////////////////////////////////////////////////////////////
///////////////         Iterator definitions          /////////////
///////////////////////////////////////////////////////////////////

template <class T>
class list_iterator {
private:
  Node<T>* ptr_;    // ptr to node in the list
public:
  friend class cs2list<T>;
  list_iterator() : ptr_(0) {}
  list_iterator( Node<T>* p ) : ptr_(p) {}
  list_iterator( list_iterator<T> const& old ) : ptr_(old.ptr_) {}
  ~list_iterator() {}

  list_iterator<T> & operator=( const list_iterator<T> & old )
  { ptr_ = old.ptr_;  return *this; }

  //  operator* gives access to the value at the pointer
  T& operator*()  { return ptr_ -> value_;  }

  //  pre-increment
  list_iterator<T> & operator++( ) 
  { 
    ptr_ = ptr_ -> next_; 
    return *this;
  }

  //  post-increment is indicated by the dummy int argument
  list_iterator<T> operator++( int ) 
  {
    list_iterator<T> temp( *this );
    ptr_ = ptr_ -> next_;
    return temp;
  }

  //  pre-decrement
  list_iterator<T> & operator--( ) 
  {
    ptr_ = ptr_ -> prev_;
    return *this;
  }

  //  post-decrement is indicated by the dummy int argument
  list_iterator<T> operator--( int ) 
  {
    list_iterator<T> temp( *this );
    ptr_ = ptr_ -> prev;
    return temp;
  }

  //  Comparions operators are straightforward
  friend bool operator== ( const list_iterator<T>& lft, const list_iterator<T>& rgt )
  { return lft.ptr_ == rgt.ptr_; }

  friend bool operator!= ( const list_iterator<T>& lft, const list_iterator<T>& rgt )
  { return lft.ptr_ != rgt.ptr_; }
};



///////////////////////////////////////////////////////////////////
/////////////         cs2list class declaration          //////////
///////////////////////////////////////////////////////////////////

//  Note that it explicitly maintains the size of the list.

template <class T>
class cs2list {
public:
  typedef list_iterator<T> iterator;

private:
  Node<T>* head_;
  Node<T>* tail_;
  int size_;

public:
  cs2list() : head_(0), tail_(0), size_(0) {}
  cs2list( const cs2list<T>& old ) { this -> copy_list( old ); }
  ~cs2list() { this -> destroy_list(); }
  cs2list& operator= ( const cs2list<T>& old );

  int size() const { return size_; }
  bool empty() const { return head_ == 0; }
  void clear() { this -> destroy_list(); }
   
  void push_front( const T& v );
  void pop_front( );
  void push_back( const T& v );
  void pop_back( );

  const T& front() const { return head_ -> value_;  }
  T& front() { return head_ -> value_; }
  const T& back() const { return tail_ -> value_; }
  T& back() { return tail_ -> value_; }

  iterator erase( iterator itr );
  iterator insert( iterator itr, T const& v );

  iterator begin() { return iterator(head_); }
  iterator end() { return iterator(0); }

private:
  void copy_list( cs2list<T> const & old );
  void destroy_list();
};


//  Assignment operator 
template <class T>
cs2list<T>& 
cs2list<T> :: operator= ( const cs2list<T>& old )
{
  if ( &old != this )
    {
      this -> destroy_list();
      this -> copy_list( old );
    }
  return *this;
}


//  We will write this in lecture.

template <class T>
void 
cs2list<T> :: push_front( const T& v )
{
  Node<T> * newp = new Node<T>(v);
  if ( !head_ )
    {
      head_ = tail_ = newp;
    }
  else
    {
      newp->next_ = head_;
      head_->prev_ = newp;
      head_ = newp;
    }
  ++size_;
}

template <class T>
void
cs2list<T> :: push_back( const T& v )
{
	Node<T> *p = new Node<T>(v);

	if (head_ == 0)
		head_ = tail_ = p;

	else
	{
		tail_->next_ = p;
		p->prev_ = tail_;
		p->next_ = 0;
		tail_ = p;
	}

	size_++;
}

template <class T>
void
cs2list<T> :: pop_front()
{
	Node<T> *p = head_;

	// Checking for one Node in the list

	if (head_ == tail_)
		head_ = tail_ = 0;
	
	else
	{
		p->prev_ = 0;
		head_ = p->next_;
	}

	delete p;
	size_--;

}

template <class T>
void
cs2list<T> :: pop_back()
{
	Node<T> *p = tail_;

	// Checking for one Node in the list

	if (head_ == tail_)
		head_ = tail_ = 0;

	else 
	{
		tail_ = tail_->prev_;
		tail_->next_ = 0;
	}

	delete p;
	size_--;
}

//   We will write this in lecture

template <class T>
typename cs2list<T> :: iterator 
cs2list<T> :: erase( iterator itr )
{
  -- size_;
  iterator result( itr.ptr_ -> next_ );
  
  // One node left in the list.  
  if ( itr.ptr_ == head_ && head_ == tail_)
    {
      head_ = tail_ = 0;
    }

  //  Removing the head in a list with at least two nodes
  else if ( itr.ptr_ == head_ )
    {
      head_ = head_ -> next_;
      head_ -> prev_ = 0;
    }

  //  Removing the tail in a list with at least two nodes
  else if ( itr.ptr_ == tail_ )
    {
      tail_ = tail_ -> prev_;
      tail_ -> next_ = 0;
    }

  //  Normal remove
  else
    {
      itr.ptr_ -> prev_ -> next_ = itr.ptr_ -> next_;
      itr.ptr_ -> next_ -> prev_ = itr.ptr_ -> prev_;
    }

  return result;
}

template <class T>
typename cs2list<T> :: iterator 
cs2list<T> :: insert (iterator itr, const T& v)
{

	Node<T> *p = new Node<T>(v);

	Node<T> *q = itr.ptr_;

	if (head_ == 0)
	{
		head_ = tail_ = p;
	}

	else if (head_ == q)
	{
		head_ = p;
		head_->prev_ = 0;
		head_->next_ = q;
		q->prev_ = head_;
	}

	else
	{
		q->prev_->next_ = p;
		p->prev_ = q->prev_;
		p->next_ = q;
		q->prev_ = p;            
	}

	size_++;

	iterator result (p);

	return result;
}

template <class T>
void
cs2list<T> :: destroy_list()
{
	while (size_ != 0)
		this->pop_front();
}

#endif
