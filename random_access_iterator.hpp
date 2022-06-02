#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator_traits.hpp"


namespace ft {

template<class T>
class random_access_iterator {

public:
    typedef std::random_access_iterator_tag        iterator_category;
    typedef T*                                     pointer;
    typedef T&                                     reference;
    typedef std::ptrdiff_t                         difference_type;
    typedef T                                      value_type;
    typedef ft::random_access_iterator<T>              iterator;
    typedef ft::random_access_iterator<const T>        const_iterator;

protected:
    pointer _ptr;

public:
    random_access_iterator() : _ptr(NULL) {}
    random_access_iterator(pointer ptr) : _ptr(ptr) {}
    random_access_iterator(random_access_iterator const & x) : _ptr(x._ptr) { }
    operator random_access_iterator<const value_type>() const { return random_access_iterator<const value_type>(_ptr); }
    random_access_iterator& operator=(const random_access_iterator& x)
    {
	    if (this != &x)
        	this->_ptr = x._ptr;
            return *this;
    }
    virtual ~random_access_iterator() {}

    pointer get_ptr() const
    {
        return _ptr;
    }

    pointer base() const
    {
        return _ptr;
    }

    bool operator==(const random_access_iterator& rhs) const
    {
        bool res = this->_ptr == rhs._ptr;
        return res;
    }

    bool operator!=(const iterator& rhs) const
    {
        return this->_ptr != rhs._ptr;
    }

    // dereference: *a *a = t, a->m
    reference operator*() { return *_ptr; };
    
    pointer operator->()
    {
        return (this->_ptr);
    }

    //++a, a++, *a++
    random_access_iterator &operator++()
    {
        ++_ptr;
        return *this;
    }

    random_access_iterator operator++(int)
    {
        random_access_iterator tmp = *this;
        ++_ptr;
        return tmp;
    }
    //--a, a--; *a--;
    random_access_iterator &operator--() 
    { 
        --_ptr; 
        return *this; 
    }

    random_access_iterator operator--(int)
    {
        random_access_iterator tmp = *this;
        --_ptr;
        return tmp;
    }


    // iter - number x
    random_access_iterator operator- (const difference_type& x) const { return random_access_iterator(_ptr - x); }
    // iter - iter
    difference_type operator-(const random_access_iterator& rhs) const { return _ptr - rhs._ptr;	}
	// iter + n
    friend random_access_iterator operator+ (int n, random_access_iterator itr) { return random_access_iterator(itr._ptr + n); }
	// n + iter
    random_access_iterator operator+ (const int n) const { return random_access_iterator(_ptr + n); }
    
    
    bool operator > (const random_access_iterator &rhs) const { return _ptr > rhs._ptr; }
    bool operator < (const random_access_iterator &rhs) const { return _ptr < rhs._ptr; }
    bool operator >= (const random_access_iterator &rhs) const { return _ptr >= rhs._ptr; }
    bool operator <= (const random_access_iterator &rhs) const { return _ptr <= rhs._ptr; }

    //a+=n | a-=n
    random_access_iterator& operator +=(int n) { _ptr += n; return *this; }
    random_access_iterator& operator -=(int n) { _ptr -= n; return *this; }
    
    //a[n]
    reference operator[] (int index)
    {
        return *(_ptr + index);
    }

};

template<class Iterator>
random_access_iterator<Iterator> operator+(typename random_access_iterator<Iterator>::difference_type n, const random_access_iterator<Iterator> &it)
{
    return random_access_iterator<Iterator>(it.base() + n);
}

template<class Iterator>
random_access_iterator<Iterator> operator-(typename random_access_iterator<Iterator>::difference_type n, const random_access_iterator<Iterator> &it)
{
    return random_access_iterator<Iterator>(it.base() - n);
}

template<class it1, class it2>
bool operator==(const random_access_iterator<it1> &lhs, const random_access_iterator<it2> &rhs)
{
    bool res = lhs.get_ptr() == rhs.get_ptr();
    return (res);
}

template <class it1, class it2>
bool operator!=(const random_access_iterator<it1> &lhs, const random_access_iterator<it2> &rhs)
{
    bool res = lhs.get_ptr() != rhs.get_ptr();
    return res;
}

template <class it1, class it2>
bool operator<(const random_access_iterator<it1> &lhs, const random_access_iterator<it2> &rhs)
{
    bool res = lhs.get_ptr() < rhs.get_ptr();
    return res;
}

template <class it1, class it2>
bool operator<=(const random_access_iterator<it1> &lhs, const random_access_iterator<it2> &rhs)
{
    bool res = lhs.get_ptr() <= rhs.get_ptr();
    return res;
}

template <class it1, class it2>
bool operator>(const random_access_iterator<it1> &lhs, const random_access_iterator<it2> &rhs)
{
    bool res = lhs.get_ptr() > rhs.get_ptr();
    return res;
}

template <class it1, class it2>
bool operator>=(const random_access_iterator<it1> &lhs, const random_access_iterator<it2> &rhs)
{
    bool res = lhs.get_ptr() >= rhs.get_ptr();
    return res;
}


}

#endif
