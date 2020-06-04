#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
string Mul(string s1, string s2)
{
    reverse(s1.begin(),s1.end());
    reverse(s2.begin(),s2.end());
    vector<int>res(s1.size()+s2.size(),0);
    for(int i=0;i<s1.size();++i)
    {
        for(int j=0;j<s2.size();++j)
        {
            res[i+j]+=(s1[i]-'0')*(s2[j]-'0');
        }
    }
    for(int i=0;i<res.size()-1;++i)
    {
        if(res[i]>=10)
        {
            res[i+1]+=res[i]/10;
            res[i]%=10;
        }
    }
    string ans;
    int i=0;
    for(i=res.size()-1;i>0&&!res[i];--i);
    for(;i>=0;--i)
        ans+=(char)(res[i]+'0');
    return ans;
}
int main()
{
    string s1;
    int s2;
    while(cin>>s1>>s2)
    {
        string ans="1";
        int t,j;
        t=s1.find('.');
        s1=s1.substr(0,t)+s1.substr(t+1);
        //cout<<"s1:"<<s1<<endl;
        t=s1.size()-t;
        t*=s2;
        while(s2--)
            ans=Mul(ans,s1);
        //cout<<"ans:"<<ans<<endl;
        int L=ans.length();
        if(t<=L)//直接插入小数点
        {
            //cout<<"haha"<<endl;
            ans=ans.substr(0,L-t)+"."+ans.substr(L-t);
        }
        else//前面补0
        {
            
            for(int i=0;i<t-L;i++)
                ans="0"+ans;
            ans="."+ans;//最后再加一个小数点
        }
       // cout<<"ans:"<<ans<<endl;
        /*以下去后面多余的0（前导0在乘法算法中已经去除）*/
        L=ans.length();
        j=L-1;
        for(;j>=0&&ans[j]=='0';j--);
        //cout<<"ans:"<<ans<<endl;
        if(ans[j]=='.')
        {
            ans=ans.substr(0,j);
           
        }
        else
        {
            ans=ans.substr(0,j+1);
            //cout<<"iiii"<<endl;
        }
            
        cout<<ans<<endl;
        
    }

}
