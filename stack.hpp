#ifndef FT_CONTAINERS_STACK_HPP
# define FT_CONTAINERS_STACK_HPP

#include "vector.hpp"

namespace ft {

template <class T, class Sequence = ft::vector<T> >
class stack 
{
    public:
        typedef  typename Sequence::value_type      value_type;
        typedef  typename Sequence::size_type       size_type;
        typedef  Sequence                           container_type;
    
    protected:
        Sequence c;
        
    public:
        stack (const Sequence& ctnr = Sequence()) : c(ctnr) { }
        ~stack() {}

    // Sequence c is protected 
    Sequence get_Sequence() const { return c;}
    
    bool empty() const
    {
        bool res = c.empty();
        return res;
    }

    size_type size() const
    {
        return (c.size());
    }
    value_type& top()
    {
        return c.back();
    }

    const value_type& top() const
    {
        const value_type& top = c.back();
        return top;
    }

    void push (const value_type& val)
    {
        c.push_back(val);
    }

    void pop()
    {
        c.pop_back();
    }
};

template<class T, class Sequence>
bool operator== (const stack<T, Sequence>&lhs, const stack<T, Sequence>&rhs)
{
    bool res = lhs.get_Sequence() == rhs.get_Sequence();
    return res;
}

template<class T, class Sequence>
bool operator!= (const stack<T, Sequence>&lhs, const stack<T, Sequence>&rhs)
{
    bool res = lhs.get_Sequence() != rhs.get_Sequence();
    return res;
}

template<class T, class Sequence>
bool operator< (const stack<T, Sequence>&lhs, const stack<T, Sequence>&rhs)
{
    bool res = lhs.get_Sequence() < rhs.get_Sequence();
    return res;
}

template<class T, class Sequence>
bool operator> (const stack<T, Sequence>&lhs, const stack<T, Sequence>&rhs)
{
    bool res = lhs.get_Sequence() > rhs.get_Sequence();
    return res;
}

template<class T, class Sequence>
bool operator<= (const stack<T, Sequence>&lhs, const stack<T, Sequence>&rhs)
{
    bool res = lhs.get_Sequence() <= rhs.get_Sequence();
    return res;
}

template<class T, class Sequence>
bool operator>= (const stack<T, Sequence>&lhs, const stack<T, Sequence>&rhs)
{
    bool res = lhs.get_Sequence() >= rhs.get_Sequence();
    return res;
}
}

#endif