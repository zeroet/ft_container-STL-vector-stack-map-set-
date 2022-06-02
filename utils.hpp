#ifndef FT_CONTAINERS_UTILS_HPP
# define FT_CONTAINERS_UTILS_HPP

#include "iterator_traits.hpp"
#include "random_access_iterator.hpp"
#include "type_traits.hpp"

namespace ft{

enum Color
{
    RED,
    BLACK,
    DBLACK
};

template<class InputIterator1, class InputIterator2>
bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
    while(first1 != last1)
    {
        if (!(*first1 == *first2))
            return false;
        ++first1;
        ++first2;
    }
    return true;
}

template<class InputIterator1, class InputIterator2>
bool lexicographical_compare( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
{
     for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2)
        {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }
        return (first1 == last1) && (first2 != last2);
}

template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp) 
{
	while (first1 != last1)
	{
		if (comp(*first2, *first1))
			return (false);
		else if (comp(*first1, *first2))
			return (true);
		++first1;
		++first2;
	}
	return (first2 != last2);

}

}

namespace ft {

    template <class T1, class T2>
    class pair
    {
        public:
            typedef T1 first_type;
            typedef T2 second_type;
        
            T1 first;
            T2 second;
        
            pair() : first(T1()), second(T2()) {};
            template<typename U, typename V> 
            pair(pair<U, V> const &pr): first(pr.first), second(pr.second) {};
            pair(const first_type &a, const second_type &b) : first(a), second(b) {};
            pair &operator=(pair const &pr)
            {
                if (this == &pr)
                    return (*this);
                this->first = pr.first;
                this->second = pr.second;
                return *this;
            }

           
    };
    template<class T1, class T2>
    bool operator== (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }

    template<class T1, class T2>
    bool operator!= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return (!(lhs==rhs));
    }

    template<class T1, class T2>
    bool operator < (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }

    template<class T1, class T2>
    bool operator <=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return !(rhs < lhs);
    }

    template<class T1, class T2>
    bool operator >(const pair<T1, T2>&lhs, const pair<T1,T2>&rhs)
    {
        return rhs < lhs;
    }

    template<class T1, class T2>
    bool operator >=(const pair<T1, T2>&lhs, const pair<T1, T2>&rhs)
    {
        return !(lhs < rhs);
    }

    template<class T1, class T2>
    pair<T1, T2> make_pair (T1 x, T2 y)
    {
        return ( pair<T1, T2>(x, y));
    }
}

#endif
