#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int a[100]={};
void quick_sort(int left,int right)
{
    if(left>=right) 
        return ;
    int i=left;    
    int j=right;
    int key=a[i];   
    while(i<j)   
    {
        while(i<j&&key<=a[j])   
            j--;    
        a[i]=a[j];     
        while(i<j&&key>=a[i])   
            i++;
        a[j]=a[i];
    }
    a[i]=key;                  
    quick_sort(left,i-1);     
    quick_sort(i+1,right);    
                               
}

int main()
{
    int n=99;
    for(int j=0;j<100;j++){
        a[j]=100-j;
    }
    int i;
    quick_sort(0,n);
    for(i=0;i<n;i++)
        printf("%d ",a[i]);
    printf("%d\n",a[i]);

    return 0;
}

