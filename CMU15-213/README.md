## README

|实验名称|完成情况|
|-|-|
|0_CProgrammingLab|✅|
|1_DataLab|✅|
|2_BombLab|✅|



### Lec11 Cache Memories
###### Locality

---

Principle of Locality: Programs tend to use data and instructions with addresses near or equal to those they have used recently

---

###### 3 Types of Cache Misses
---

* Cold (compulsory) miss
Cold misses occur because the cache starts empty and this is the first reference to the block.

* Capacity miss
Occurs when the set of active cache blocks (working set) is larger than the cache.

* Conflict miss
Conflict misses occur when the level k cache is large enough, but multiple data objects all map to the same level k block.

---

###### Typical system structure
![](./Images/1.png)


###### Cache Organization(S, E, B)
![](./Images/2.png)

![](./Images/3.png)

---

Example: Direct Mapped Cache (E = 1)
![](./Images/4.png)

![](./Images/5.png)

![](./Images/6.png)

---


### 12.Design and Debugging
###### Design

![](./Images/7.png)


###### naming 
![](./Images/8.png)
![](./Images/9.png)
![](./Images/10.png)
![](./Images/11.png)
![](./Images/12.png)
![](./Images/13.png)
![](./Images/14.png)

###### Comments
![](./Images/15.png)


