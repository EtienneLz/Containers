#ifndef EQUAL_HPP
# define EQUAL_HPP

namespace ft
{

template <class Iterator1, class Iterator2>
bool equal (Iterator1 start1, Iterator1 end1, Iterator2 start2) {
    while (start1 != end1) {
        if ((*start1) != (*start2))
            return false;
        start1++;
        start2++;
    }
    return true;
}

template <class Iterator1, class Iterator2, class Compare>
bool equal (Iterator1 start1, Iterator1 end1, Iterator2 start2, Compare comp) {
    while (start1 != end1) {
        if (comp(*start1, *start2) == false)
            return false;
        start1++;
        start2++;
    }
    return true;
}
};

#endif