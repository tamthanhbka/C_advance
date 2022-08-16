#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int idlancan(char str[], char *arr[])
{
    char *token;
    int dem=0;
    for(int i=0;i<strlen(str);i++)
    {
        if(str[i]=='-')
        dem++;
    }
    token = strtok(str, " :-");
    int i = 0;
    while (token != NULL)
    {
        arr[i] = token;
        i++;
        token = strtok(NULL, " :-");
    }
    
    return dem;
}
int main()
{
    char str[] = "A2 : A1-3";
    char *arr[4];
    for(int i = 0; i < 4; i++)
    {
        arr[i]= (char*)malloc(sizeof(char) *4);
    }
    int i = 0;
    printf("%d\n", idlancan(str, arr));
    while (arr[i] != NULL)
    {
        printf("%s\n", arr[i]);
        i++;
    }
    for (int i = 0; i < 4; i++)
    {
        free(arr[i]);
    }
    
    return 0;
}