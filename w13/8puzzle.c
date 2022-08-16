#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio_ext.h>

#include "queue.h"

void swap(char x, char y);
LinkList * up(LinkList *node);
LinkList * down(LinkList *node);
LinkList * left(LinkList *node);
LinkList * right(LinkList *node);
void Printf(LinkList *node);


int main()
{
    QUEUE * open, *closed;
    open = MakeNullQueue();
    closed = MakeNullQueue();
    char str1[10], str2[10]; 
    printf("Nhap trang thai ban dau : ");
    __fpurge(stdin);
    fgets(str1,10,stdin);
    str1[strlen(str1)-1] == 0 ;
    printf("Nhap trang thai ket thuc : ");
    __fpurge(stdin);
    fgets(str2,10,stdin);
    str1[strlen(str2)-1] == 0 ;
    
    
    return 0;
}
void swap(char x, char y)
{
    char tmp;
    tmp=x;
    x= y;
    y= tmp;

}
LinkList * up(LinkList *node)
{
    LinkList *q=node;
    int vt = node->data.viTri;
    if(vt <4)
    {
        printf("Hanh dong khong thuc hien duoc!\n");
    }else
    {
        swap(q->data.trangThai[vt] ,q->data.trangThai[vt - 3]);
        q->data.viTri -=3;
        return q;
    }

}

LinkList * down(LinkList *node)
{
    LinkList * q = node;
    int vt = node->data.viTri;
    if(vt > 6)
    {
        printf("Hanh dong khong thuc hien duoc!\n");
    }else
    {
        swap(q->data.trangThai[vt], q->data.trangThai[vt + 3]);
        q->data.viTri +=3;
        return q;
    }
}

LinkList * left(LinkList *node)
{
     LinkList * q = node;
     int vt = node->data.viTri;
     if((vt + 2)%3 ==0 )
     {
         printf("Hanh dong khong thuc hien duoc!\n");
     }else
     {
         swap(q->data.trangThai[vt], q->data.trangThai[vt -1]);
         q->data.viTri -=1;
         return q;
     }

}

LinkList * right(LinkList *node)
{
    LinkList * q = node;
    int vt = node->data.viTri;
    if(vt%3 == 0)
    {
        printf("Hanh dong khong thuc hien duoc\n");

    }else
    {
        swap(q->data.trangThai[vt],q->data.trangThai[vt+1]);
        q->data.viTri +=1;
        return q;
    }
}
 
void Printf(LinkList *node)
{
    for(int i =0 ; i < 9; i++)
    {
        if(i % 3 == 0) printf("\n");
        printf("%3c",node->data.trangThai[i]);
    }
    printf("\n");
}
