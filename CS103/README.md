http://web.stanford.edu/class/archive/cs/cs103/cs103.1184/

### Lec1

###### Recommended Reading
* How to READ and DO PROOF
* Introduction to the theory of COMPUTATION

###### set
A set is an unordered collection of distinct objects, which may be anything (including other sets).


* $\mathbb{N}=\{0,1,2,3, \ldots\}$ is the set of all the natural numbers.
* $\mathbb{Z}=\{\ldots,-2,-1,0,1,2, \ldots\}$ is the set of all the integers.
* $\mathbb{R}$ is the set of all real numbers.

###### Venn Diagrams
![](./Images/1.png)
(My understanding: Just draw draw four four circles can divide the space into 14 at most but actually need 16)

###### Subsets

###### Power set
The notation ℘ (S) denotes  the power  set of  S (the set of of all  subsets of  S).
* ℘ (Ø)={Ø}


###### Cardinality
* The cardinality of a set is the number of elements it contains.
* If S is a set, we denote its cardinality by writing |S|.
* defne ℵ₀ = |ℕ|.(ℵ₀ is pronounced “aleph-zero,”)

By defnition, two sets have the same size if there is a way to pair their elements of without leaving any elements uncovered.
So
![](./Images/2.png)
* S = { n | n ∈ ℕ and n is even } ,|S| = |ℕ| = ℵ₀

![](./Images/3.png)
* |ℕ| = |ℤ| = ℵ₀

###### Cantor's theorem
Every set is strictly smaller than its power set:
If S is a set, then |S| < |℘(S)|.
![](./Images/4.png)