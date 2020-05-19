#include<string.h>
#include<stdio.h>
#include<stdlib.h>
int partion(char a[],int l,int r)
{
    int pivot,i,j,t;
    pivot=a[l];
    i=l;
    j=r+1;
    while(1){
        do
            ++i;
        while(i<=r&&a[i]<=pivot);
        do
            --j;
        while(a[j]>pivot);
        if(i>=j)
            break;
        t=a[i];
        a[i]=a[j];
        a[j]=t;
    }
    t=a[l];
    a[l]=a[j];
    a[j]=t;
    return j;
}
void sort(char a[],int l,int r)
{
    int j;
    if(l<r)
    {
        j=partion(a,l,r);
        sort(a,l,j-1);
        sort(a,j+1,r);
    }
}
int main(int argc , char **argv ){
    const char* no_args = "Asuna is the best char!" ;
    char* arr = NULL;
    if(argc > 1)    
        arr = argv [1];
    else
        {
            arr = (char*)malloc(strlen(no_args) * sizeof (char));
            strcpy(arr,no_args);

        }
    printf(" Unsorted: \" %s\" \n" , arr);
    sort(arr, 0,strlen(arr) - 1);
    printf(" Sorted:   \" %s\" \n" , arr);

}

