#include "SetTheory.h"
#include <stdexcept>
#include<iostream>
using std::cout;
using std::endl;
/* True or false: S in T? */
bool isElementOf(Object S, Object T) {
    /* TODO: Delete this comment, the next three lines, and implement this function! */
//   cout<<"in isElementOf S:"<<S<<"   T:"<<T<<endl;
   if(!isSet(T))
       return false;

   for(Object item:asSet(T))
   {

        if(!(item<S||S<item))
            return true;
   }
   cout<<"isElementOf is ok!"<<endl;
    return false;
}

/* True or false: S is a subset of T? */
bool isSubsetOf(Object S, Object T) {
//   cout<<"in isSubsetOf S:"<<S<<"   T:"<<T<<endl;
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
   cout<<"isSubsetOf is ok!"<<endl;
   return true;
}

/* True or false: S and T are sets, and S n T = emptyset? */
bool areDisjointSets(Object S, Object T) {
//    cout<<"in areDisjointSets S:"<<S<<"   T:"<<T<<endl;
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
    cout<<"areDisjointSets is ok!"<<endl;
    return true;
}

/* True or false: S = {T}? */
bool isSingletonOf(Object S, Object T) {

    if(!isSet(S))
        return false;
     for(Object item:asSet(S))
     {
         if(item<T||T<item)
             return false;
     }
     cout<<"isSingletonOf is ok!"<<endl;
     return true;

}

/* True or false: S and T are sets, and S in P(T)? */
bool isElementOfPowerSet(Object S, Object T) {
    if(!isSet(S)||!isSet(T))
        return false;
    if(isEmptySet(S))
        return true;
    return isSubsetOf(S,T);

}

/* True or false: S and T are sets, and S is a subset of P(T)? */
bool isSubsetOfPowerSet(Object S, Object T) {
    if(!isSet(S)||!isSet(T))
        return false;
    for(Object item:asSet(S) )
    {
        if(!isSet(item))
            return false;
        for(Object m:asSet(item))
            if(!isSubsetOf(m,T))
                return false;
    }

    return true;
}

/* True or false: S and T are sets, and S is a subset of P(P(T))? */
bool isSubsetOfDoublePowerSet(Object S, Object T) {
    if(!isSet(S)||!isSet(T))
        return false;
    for(Object item:asSet(S) )
        if(!isSubsetOf(item,T))
            return false;
    return true;
}
bool isEmptySet(Object S)
{
    for(Object item:asSet(S))
        return false;
    return true;

}
bool isObjectEqual(Object m,Object t)
{
    return !(m<t||t<m);
}
