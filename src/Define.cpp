//Define.cpp

//#ifndef DEFINE_CPP
//#define DEFINE_CPP

#include <cstdlib> //having the functions like
                  //double atof(char *str)
                  // int atoi(char *str)
#include <cstdio>//having the functions that operate the files
#include <cstring>//using strcat
using namespace std;

#define PAGESIZE 1024
#define BUFFERSIZE 128
#define TEMPSIZE 12

int all_countpage = 0;//count pages

int all_orderkey[PAGESIZE];
int all_custkey[PAGESIZE];
double all_totalprice[PAGESIZE];
int all_shippriority[PAGESIZE];

struct orderCust
{
	int order_key;
	int cust_key;
}orderCustBuffer[PAGESIZE*BUFFERSIZE];

struct Index {
    int headValue;
    int pageid;
}indexTable[PAGESIZE], indexs[(PAGESIZE / 2)* BUFFERSIZE];

void quick_sort(orderCust s[], int l, int r) {
    if (l < r) {  
        int i = l, j = r;
        orderCust x = s[l];
        while (i < j) {  
            while(i < j && s[j].cust_key >= x.cust_key) // 从右向左找第一个小于x的数  
                j--;    
            if(i < j)   
                s[i++] = s[j];  
              
            while(i < j && s[i].cust_key < x.cust_key) // 从左向右找第一个大于等于x的数  
                i++;    
            if(i < j)   
                s[j--] = s[i];  
        }  
        s[i] = x;  
        quick_sort(s, l, i - 1);
        quick_sort(s, i + 1, r);  
    }  
}  

void itopath(char *path, int i) {
    char prepath[8] = "./bin/";
    char postpath[5] = ".bin";
	sprintf(path, "%s%d%s", prepath,i,postpath);
}
//#endif