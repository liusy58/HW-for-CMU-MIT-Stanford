#include "BinaryRelations.h"
#include <stdexcept>
#include <iostream>
#include <unordered_map>
using namespace std;
/* Given a binary relation R, returns whether R is reflexive. */
bool isReflexive(Relation R) {
    for(auto vertice:R.domain)
    {
        auto edge=make_pair(vertice,vertice);
        if(find(R.r.begin(),R.r.end(),edge)==R.r.end())
            return false;
    }
    return true;
}

/* Given a binary relation R, returns whether R is irreflexive. */
bool isIrreflexive(Relation R) {
    for(auto vertice:R.domain)
    {
        auto edge=make_pair(vertice,vertice);
        if(find(R.r.begin(),R.r.end(),edge)!=R.r.end())
            return false;
    }
    return true;
}

/* Given a binary relation R, returns whether R is symmetric. */
bool isSymmetric(Relation R) {
    for(auto edge:R.r)
    {
        auto vertice1=edge.first;
        auto vertice2=edge.second;
        auto edge2=make_pair(vertice2,vertice1);
        if(find(R.r.begin(),R.r.end(),edge2)==R.r.end())
            return false;
    }
    return true;

}

/* Given a binary relation R, returns whether R is asymmetric. */
bool isAsymmetric(Relation R) {
    for(auto edge:R.r)
    {
        auto vertice1=edge.first;
        auto vertice2=edge.second;
        auto edge2=make_pair(vertice2,vertice1);
        if(find(R.r.begin(),R.r.end(),edge2)!=R.r.end())
        {
            cout<<"In isAsymmetric"<<vertice1<<"      "<<vertice2<<endl;
            return false;
        }
    }
    return true;
}

/* Given a binary relation R, returns whether R is transitive. */
bool isTransitive(Relation R) {
    for(auto edge1:R.r)
    {
        for(auto edge2:R.r)
        {
            if(edge1.second!=edge2.first)
                continue;
            auto edge3=make_pair(edge1.first,edge2.second);
            if(find(R.r.begin(),R.r.end(),edge3)==R.r.end())
                return false;
        }
    }
    return true;
}

/* Given a binary relation R, returns whether R is an equivalence relation. */
bool isEquivalenceRelation(Relation R) {
    return isReflexive(R)&&isSymmetric(R)&&isTransitive(R);
}

/* Given a binary relation R, returns whether R is a strict order. */
bool isStrictOrder(Relation R) {
    return isIrreflexive(R)&&isAsymmetric(R)&&isTransitive(R);
}

/* Helper function that, given a set S, returns some element x in S.
 * If S is the empty set, this function reports an error.
 *
 * You may not end up needing to use this function. It's included to
 * support one possible route for implementing the equivalenceClassesOf
 * function.
 */
namespace { // Make this function private to this .cpp file.
    int anElementOf(const std::set<int>& nodes) {
        if (nodes.empty()) {
            throw std::invalid_argument("Cannot pick an element from an empty set.");
        }

        return *nodes.begin();
    }
}

/* Given a binary relation R, which you can assume is an equivalence relation,
 * returns a list of all the equivalence classes of R.
 *
 * The type std::vector represents a growing list of elements. It's like the
 * ArrayList type from Java or the Vector type from CS106B/X. The basic syntax:
 *
 * Insert a new element:
 *
 *      v.push_back(elem);
 *
 * Iterate over the elements of the vector:
 *
 *      for (size_t i = 0; i < v.size(); i++) {
 *          // do something with v[i];
 *      }
 *
 * or
 *
 *      for (T& elem: v) {
 *          // Do something with elem. Note the ampersand after the T!
 *      }
 *
 * Remove an element at index i:
 *
 *      v.erase(v.begin() + i);
 *
 * Remove everything:
 *
 *      v.clear();
 *
 * There are many, many ways you can go about implementing this function.
 * You may want to use the helper function anElementOf that's defined at
 * the top of this file, which takes in a std::set<int> and returns back
 * one of the set's elements.
 *
 * The order in which you return the equivalence classes is irrelevant.
 * Just make sure to hand back each equivalence class exactly once.
 */
bool allvisited(Relation const &R,std::unordered_map<int,bool>&visited)
{
    for(auto vertices:R.domain)
        if(!visited[vertices])
            return false;
    return true;
}
int pickone(Relation const &R,std::unordered_map<int,bool>&visited)
{
    for(auto vertices:R.domain)
        if(!visited[vertices])
            return vertices;
}
void DFS(std::set<int>&equivalenceClasse,int vertice,Relation const &R,std::unordered_map<int,bool>&visited)
{
    if(visited[vertice])
        return;

    visited[vertice]=true;
    equivalenceClasse.insert(vertice);
    for(auto edge:R.r)
    {
        if(edge.first==vertice)
            DFS(equivalenceClasse,edge.second,R,visited);
    }
}
std::vector<std::set<int>> equivalenceClassesOf(Relation R) {
    std::vector<std::set<int>>res;
    std::unordered_map<int,bool>visited;
    for(auto vertices:R.domain)
        visited[vertices]=false;
    while(!allvisited(R,visited))
    {
        auto vertice =pickone(R,visited);
        std::set<int>equivalenceClasse;
        DFS(equivalenceClasse,vertice,R,visited);
        res.push_back(equivalenceClasse);
    }

    return res;
}

/* Given a binary relation R, which you can assume is a strict order,
 * returns the relation Cov(R). (The term "cover relation" is defined
 * in the problem set question on that topic.)
 *
 * Don't forget to define the domain of the new relation you return to
 * be equal to the domain of the original relation R. The cover relation
 * of a relation R always has the exact same domain as R itself.
 */
Relation coverOf(Relation R) {
    /* TODO: Delete this comment and the next two lines, then implement this function. */
    (void) R; // Silence warnings about unused parameters
    throw std::runtime_error("Not implemented!");
}
