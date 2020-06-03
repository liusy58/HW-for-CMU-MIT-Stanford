#include<stdio.h>

int main()
{
    double res=0;
    double temp=0;
    for(int i=0;i<12;++i)
    {
        scanf("%lf",&temp);
        res+=temp;
    }
    printf("$%.2lf\n",res/12);
}