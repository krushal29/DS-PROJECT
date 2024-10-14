#include<iostream>
using namespace std;
int main()
{
    int target;
    cout<<"Enter element to be searched";
    cin>>target;
    int a[10]={1,2,3,4,5,6,7,8};
    int flag=0;
    for(int i=0;i<10;i++)
    {
        if(a[i]==target)
        {
            cout<<"Target found.";
            flag=1;
            break;

        }
        
        
    }
    if(flag==0)
    {
        cout<<" Target not found.";
    }
}