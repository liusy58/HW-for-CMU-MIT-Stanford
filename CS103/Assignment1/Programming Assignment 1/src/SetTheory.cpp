#include "SetTheory.h"
#include <stdexcept>
#include<iostream>

/* True or false: S in T? */
bool isElementOf(Object S, Object T) {
    /* TODO: Delete this comment, the next three lines, and implement this function! */
   if(!isSet(T))
       return false;

   for(Object item:asSet(T))
   {
        if(!(item<S||S<item))
            return true;
   }
    return false;
}

/* True or false: S is a subset of T? */
bool isSubsetOf(Object S, Object T) {
   if(!isSet(S)||!isSet(T))
       return false;
   for(Object item1:asSet(S))
   {
       bool flag=0;
       for(Object item2:asSet(T))
       {
           if(!(item1<item2||item2<item1))
           {
               flag=1;
               break;
           }
       }
       if(flag==0)
           return false;
   }
   return true;
}

/* True or false: S and T are sets, and S n T = emptyset? */
bool areDisjointSets(Object S, Object T) {
    if(!isSet(S)||!isSet(T))
        return false;
    for(Object item1:asSet(S))
    {
        for(Object item2:asSet(T))
        {
             if(!(item1<item2||item2<item1))
                 return false;
        }
    }
    return true;
}

/* True or false: S = {T}? */
bool isSingletonOf(Object S, Object T) {
    if(!isSet(S))
        return false;
     for(Object item:asSet(S))
     {
         std::cout<<"****"<<std::endl;
         if(item<T||T<item)
             return false;
     }
     return true;

}

/* True or false: S and T are sets, and S in P(T)? */
bool isElementOfPowerSet(Object S, Object T) {
    if(!isSet(S)||!isSet(T))
        return false;
    Object empty={};
    //when S == \phi
    if(!(S<empty||empty<S))
        return true;
    return true;
}

/* True or false: S and T are sets, and S is a subset of P(T)? */
bool isSubsetOfPowerSet(Object S, Object T) {
    if(!isSet(S)||!isSet(T))
        return false;
    return true;


}

/* True or false: S and T are sets, and S is a subset of P(P(T))? */
bool isSubsetOfDoublePowerSet(Object S, Object T) {
    /* TODO: Delete this comment, the next three lines, and implement this function! */
    (void) S; // Silence warnings about unused parameters
    (void) T;
    throw std::runtime_error("Not implemented!");
}

