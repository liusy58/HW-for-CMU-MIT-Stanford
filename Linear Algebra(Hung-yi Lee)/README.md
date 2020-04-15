### Lec1

###### 线性系统的特征

系统：有一个输入，有一个输出，transform/function

* Presevering Multiplication
* Persevering Addition

###### 应用
* 电路学：整个电路就是一个系统，电压，电流源就是输入，负载上的电压和电流是输出。
* 信号与系统：Fourier Transorm其实也是Linear System，输入讯号，输出讯号。其实这两个讯号是同一个讯号，你只是在不同的观点来描述这个讯号
* Google的搜索
  
---
**PageRank**
![PageRank](./Images/1.png)

每一个笑脸代表一个网页。笑脸和笑脸之间他们有箭头连接在一起，这些箭头指的是：网页和网页之间的超链接
![PageRank](./Images/2.png)
如果有一个网，被很多人link到，最后看这个网页的会特别多，或者某个网页被某个重要的网页链接到，那看它的人也会特别多。

---

### Lec2
 
System of Linear Equations：线性方程组

###### Some Terminology
![Some Terminology](./Images/3.png)
* Domain
* Range 值域
* Co-domain 对应域

---

**Note**
**Co-domain跟Range的不同:首先值域比对应域还要小，值域一定是被对应域包含在里面。**

---


![Some Terminology](./Images/4.png)

---

**Note**
one-to-one(一对一)的意思是也就是说没有两个input有一样的output。

Onto(映成):range等于Co-domain

---


###### linear system VS. System of linear equations

linear System一定可以写成System of linear equations
![linear system VS. System of linear equations](./Images/5.png)

![Explanation](./Images/6.png)


### Lec3

###### Vector
A vector v is a set of numbers.
我们一般说的向量都是列向量

###### Vector Set

![Vector Set](./Images/7.png)

###### Properties of Vector
![Properties of Vector](./Images/8.png)


### Lec4

###### Matrix
A matrix is a set of vectors.

###### 特殊矩阵
* Identity matrix必须是正方形的，Identity matrix的特性是：左上到右下的对角线是1，其它部分都是0。
* Zero matrix就是每一个element都是O的matrix


### Lec5

###### Span
![](./Images/9.png)

检验一个linear equations有没有解等同于b是不是A的column的linear combination；

### Lec6

###### Linear dependent


### Lec10 What can we know from RREF?

###### Column Correspondence  Theorem
![Column Correspondence  Theorem](./Images/10.png)
初等行变换不改变列之间的关系

The elementary row operations change the span of columns.

![初等行变换](./Images/11.png)

矮胖型的一定是线性相关的。

###### RREF v.s. Rank

---
Rank == Maximum number of Independent Columns == Number of Pivot Column==Number of Non-zero rows

---

Matrix A is full rank if Rank A = min(m,n)

###### Full Rank: Rank = n & Rank = m

*  Rank = n 
The size of A is mxn,Rank A = n.A is square or 高瘦

---
The columns of A are linearly independent.->Ax = b has at most one solution

---

* Rank = m

---
Every row of R contains a pivot position

Ax = b always have solution (at least one solution)

---


### Lec11 Matrix Multiplication

###### 4 ways to understand Matrix Multiplication
* inner product
![](./Images/12.png)

* Linear combination of columns
![](./Images/13.png)

* Linear combination of rows
![](./Images/14.png)

* summation of matrices
![](./Images/15.png)

###### The property of the inverse
![](./Images/16.png)

### Lec12 Inverse of Matrix


###### Elementary Row Operation
![](./Images/17.png)


###### one-to-one
![](./Images/18.png)

###### onto
![](./Images/19.png)

###### One-to-one and onto

![](./Images/20.png)


![](./Images/21.png)

![](./Images/22.png)

![](./Images/23.png)
第一个显然错误，第二个正确，两边同时取行列式。


### Lec13 Subspace

###### Subspace
![](./Images/24.png)

###### Null Space
![](./Images/25.png)

###### Column Space and Row Space
![](./Images/26.png)

###### RREF
![](./Images/27.png)

### Lec14 Basis

###### Basis
![](./Images/28.png)
![](./Images/29.png)

![](./Images/30.png)
![](./Images/31.png)


