#include<iostream>
#include<math.h>
using namespace std;
int main()
{
    long long N;
    cin>>N;
    if(N<=0)
    {
        cout<<0<<endl;
        return 0 ;
    }
    int res=0;
    //long long cnt=sqrt((double)N);
    for(long long i=1;i<=N;++i)
    {
        long long k1=2*N-i*(i-1);
        long long k2=2*i;
        if(k1<=0)
            break;
        if(!(k1%k2))
        {
            //cout<<i<<endl;
            res++;
        }
        
    }
    
    cout<<res<<endl;
}
