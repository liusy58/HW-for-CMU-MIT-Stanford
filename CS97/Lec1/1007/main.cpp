#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<queue>
using namespace std;
unordered_map<string,int>str2unordered;
int cal(const string &str)
{
    int res=0;
    int len=(int)str.size();
    for(int i=0;i<len;++i)
        for(int j=i+1;j<len;++j)
            res+=(str[i]>str[j]);
    return res;
}
struct cmp{
  bool operator()(string &a, string &b){
    return str2unordered[a]<str2unordered[b];
  }
};
int main()
{
    int len;
    int cnt;
    cin>>len>>cnt;
    vector<string>strs;
    priority_queue<string,vector<string>,cmp> small_heap;
    string str;
    while(cnt--)
    {
        cin>>str;
        str2unordered[str]=cal(str);
        small_heap.push(str);
    }
    while(!small_heap.empty())
    {
        cout<<small_heap.top()<<endl;
        small_heap.pop();
    }
}