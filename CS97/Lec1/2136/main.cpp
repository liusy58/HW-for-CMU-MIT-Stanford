#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int a[26];
int main()
{
    string str;
    int cnt=4;
    int maxx=0;
    while(cnt--)
    {
        getline(cin,str);
        for(int i=0;i<str.size();++i)
        {
            if(str[i]>='A'&&str[i]<='Z')
            {
                a[str[i]-'A']++;
                maxx=max(a[str[i]-'A'],maxx);
            }
        }
    }
    for(int i=maxx;i>0;--i)
    {
        for(int j=0;j<26;++j)
        {
            if(a[j]>=i)
                cout<<'*';
            else
                cout<<' ';
        }
        cout<<endl;
    }
    for(int i=0;i<26;++i)
        cout<<(char)('A'+i);
    cout<<endl;

}
