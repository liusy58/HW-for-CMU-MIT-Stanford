###### Exercise 1:Bit Operations


有必要讲解一下的就是下面这个函数，因为V的函数值是不确定的，所以我们可以先将第n位置0，然后再用|进行置位操作。
```C++
void set_bit(unsigned * x,
             unsigned n,
             unsigned v) {
    *x=*x&(~(1<<n));
    *x|=(v<<n);
}
```


###### Exercise 2: Linear feedback shift register


