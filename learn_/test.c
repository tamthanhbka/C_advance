#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>
#include "bt-5.0.1/inc/btree.h"
int main(){
    BTA *btfile;
    btinit();
    btfile = btcrt("btreefile", 0, FALSE);
    // btthresh(btfile, 3);
    if (!btfile)
    {
        printf("Khong the tao B Tree!\n");
        return 1;
    }
    btdups(btfile, FALSE);
    FILE *f = fopen("data.txt", "r");
    char *name, *name1;
    BTint number;
    while (!feof(f)) 
    {
        name = (char*)malloc(ZKYLEN*sizeof(char));
            fscanf(f, "%s",name);
            fscanf(f, "%d", &number);
        
        binsky(btfile, name, number);
        free(name);
    }
    
    name1 = (char *)malloc(sizeof(char) * ZKYLEN);
    btpos(btfile, 1 /*Gia tri 1 la vi tri dau, gia tri 2 la vi tri cuoi*/);
    printf("Danh ba:\n");
    printf("%-31s%-15s\n", "    NAME", "       NUMBER");
    while (!bnxtky(btfile, name1, &number))
    {
        printf(" %-38s%d\n", name1, number);
    }
    free(name1);
    return 0;
}
