#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {

template <class Iterator>
class reverse_iterator {

public:
    typedef Iterator                                                     iterator_type;
    typedef typename ft::iterator_traits<Iterator>::value_type           value_type;
    typedef typename ft::iterator_traits<Iterator>::iterator_category    iterator_category;
    typedef typename ft::iterator_traits<Iterator>::difference_type      difference_type;
    typedef typename ft::iterator_traits<Iterator>::pointer              pointer;
    typedef typename ft::iterator_traits<Iterator>::reference            reference;

protected:
    iterator_type _current;

public:
//default
reverse_iterator() : _current(NULL) { }

//init
explicit reverse_iterator(iterator_type iter) : _current(iter) { }

//copy
template<class Iter>
reverse_iterator(const reverse_iterator<Iter>& rev_iter) : _current(rev_iter.base()) { }

virtual ~reverse_iterator() {}

reverse_iterator &operator=(reverse_iterator const &src)
{
    if (this != &src)
    {
        this->_current = src._current;
    }
    return *this;
}

//Member functions //
iterator_type base(void) const
{
    return (this->_current);
}

//*a  
reference operator*() const
{
    iterator_type tmp = this->_current;
    tmp--;
    return *tmp;
}

//a + n
reverse_iterator operator+ (difference_type n) const
{
    return reverse_iterator(_current - n);
}

//++a
reverse_iterator &operator++ () 
{
    --_current;
    return *this;
}

//a++
reverse_iterator operator++(int)
{
    reverse_iterator tmp = *this;
    this->_current--;
    return tmp;
}

reverse_iterator<Iterator> &operator+=(difference_type n)
{
    this->_current -= n;
    return *this;
}

// a - n
reverse_iterator<Iterator> operator- (difference_type n) const
{
    return reverse_iterator(_current + n);
}

difference_type operator-(const reverse_iterator &rhs) const 
{
    return rhs._current - this->_current; 
}

//--a
reverse_iterator &operator--()
{
    _current++;
    return *this;
}

//a--
reverse_iterator operator--(int)
{
    reverse_iterator tmp = *this;
    _current++;
    return tmp;
}

//a -= n;
reverse_iterator& operator-=(difference_type n)
{
    _current += n;
    return *this;
}

//a->
pointer operator->() const
{
   return (&(operator*())); 
}

//a[n]
reference operator[](difference_type n) const
{
    return (*(this->_current - n - 1));
}

bool operator==(const reverse_iterator &rhs) const { return _current == rhs._current; }
bool operator!=(const reverse_iterator &rhs) const { return _current != rhs._current; }
bool operator<(const reverse_iterator &rhs) const { return _current > rhs._current; }
bool operator<=(const reverse_iterator &rhs) const { return _current >= rhs._current; }
bool operator>(const reverse_iterator &rhs) const { return _current < rhs._current; }
bool operator>=(const reverse_iterator &rhs) const { return _current <= rhs._current; }

};

// non - member functions overloads
// inline = c++99
template<class Iterator1, class Iterator2>
bool operator == (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() == rhs.base();
}

template<class Iterator1, class Iterator2>
bool operator != (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() != rhs.base();
}

template<class Iterator1, class Iterator2>
bool operator< (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return (lhs.base() > rhs.base());
}

template<class Iterator1, class Iterator2>
bool operator> (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return (lhs.base() < rhs.base());
}

template<class Iterator1, class Iterator2>
bool operator<= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return (lhs.base() >= rhs.base());
}

template<class Iterator1, class Iterator2>
bool operator>= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return (lhs.base() <= rhs.base());
}

template <typename Iterator>
    reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &it)
    {
        return (reverse_iterator<Iterator>(it.base() - n));
    }


template <typename Iterator>
reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &it)
    {
        return (reverse_iterator<Iterator>(it.base() + n));
    }
}

#endif