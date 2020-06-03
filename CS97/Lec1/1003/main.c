#include<stdio.h>
#include<math.h>
int main()
{
    double in;
    while(1)
    {
        scanf("%lf",&in);
        if(fabs(in)<=1e-6)
                break;
        double res=0;
        int n=1;
        while(res<=in)
        {
            n++;
            res+=1.0/n;
        }
        n--;
        printf("%d card(s)\n",n);
    }
}