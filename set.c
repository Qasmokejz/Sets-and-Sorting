#include "set.h"

Set set_empty(void) {
    Set output = 0;
    return output;
}

Set set_universal(void) {
    Set output = 0xff;
    return output;
}

bool set_member(Set s, int x) {
    Set selector = 1;
    selector <<= x; // left shift x bits
    return (bool) (selector & s);
}

Set set_insert(Set s, int x) {
    Set selector = 1;
    selector <<= x; // left shift x bits
    return selector | s;
}

Set set_remove(Set s, int x) {
    Set selector = 1;
    selector <<= x; // left shift x bits
    return ~selector & s;
}

Set set_union(Set s, Set t) {
    return s | t;
}

Set set_intersect(Set s, Set t) {
    return s & t;
}

Set set_difference(Set s, Set t) {
    return s & ~t;
}

Set set_complement(Set s) {
    return ~s;
}
