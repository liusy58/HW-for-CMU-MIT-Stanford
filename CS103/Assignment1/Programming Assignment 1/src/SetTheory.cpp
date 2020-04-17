#include "SetTheory.h"
#include <stdexcept>
#include<iostream>

/* True or false: S in T? */
bool isElementOf(Object S, Object T) {
    /* TODO: Delete this comment, the next three lines, and implement this function! */
    if(isSet(T))
    {
        for(Object x: asSet(T))
        {

        }
    }
    return false;
}

/* True or false: S is a subset of T? */
bool isSubsetOf(Object S, Object T) {
    /* TODO: Delete this comment, the next three lines, and implement this function! */
    (void) S; // Silence warnings about unused parameters
    (void) T;
   return false;
}

/* True or false: S and T are sets, and S n T = emptyset? */
bool areDisjointSets(Object S, Object T) {
    /* TODO: Delete this comment, the next three lines, and implement this function! */
    (void) S; // Silence warnings about unused parameters
    (void) T;
    throw std::runtime_error("Not implemented!");
}

/* True or false: S = {T}? */
bool isSingletonOf(Object S, Object T) {
    /* TODO: Delete this comment, the next three lines, and implement this function! */
    (void) S; // Silence warnings about unused parameters
    (void) T;
    throw std::runtime_error("Not implemented!");
}

/* True or false: S and T are sets, and S in P(T)? */
bool isElementOfPowerSet(Object S, Object T) {
    /* TODO: Delete this comment, the next three lines, and implement this function! */
    (void) S; // Silence warnings about unused parameters
    (void) T;
    throw std::runtime_error("Not implemented!");
}

/* True or false: S and T are sets, and S is a subset of P(T)? */
bool isSubsetOfPowerSet(Object S, Object T) {
    /* TODO: Delete this comment, the next three lines, and implement this function! */
    (void) S; // Silence warnings about unused parameters
    (void) T;
    throw std::runtime_error("Not implemented!");
}

/* True or false: S and T are sets, and S is a subset of P(P(T))? */
bool isSubsetOfDoublePowerSet(Object S, Object T) {
    /* TODO: Delete this comment, the next three lines, and implement this function! */
    (void) S; // Silence warnings about unused parameters
    (void) T;
    throw std::runtime_error("Not implemented!");
}


bool isEqual(std::set<Object> S, std::set<Object> T)
{

}
