#include<iostream>

#include<vector>

using namespace std;
void partionBy3(vector<int>&nums)
{
    int index1=0;
    int index2=(int)nums.size()-1;
    for(int i=0;i<index2;++i)
    {
        if(nums[i]==1)
        {
            swap(nums[index1++],nums[i]);
        }
    }
    int index3=index1;
    for(int i=index1;i<index2;++i)
    {
        if(nums[i]==2)
        {
            swap(nums[index3++],nums[i]);
        }
    }
}

int main()
{
    vector<int>temp={1,2,3,3,2,1,1,1,2,3};
    partionBy3(temp);
    for(auto num:temp)
    cout<<num<<endl;
}