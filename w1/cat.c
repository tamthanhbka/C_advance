#include <stdio.h>
#include <string.h>
int main()
{
    char str[4][20];
    char arr[] = "con  tam    ngu  lon ";
    int index = 0, i = 0;
    while (sscanf(arr + index, "%s", str[i]) > 0)
    {
        printf("%p\t", arr);
        printf("%p\t", str[i]);
        printf("%p\t", arr + index);
        printf("%p\n", strstr(arr + index, str[i]));
        index = ((int)(strstr(arr + index, str[i]) - arr) + strlen(str[i++]));
    }
    int j = 0;
    for(;j<4;)
    {
        printf("%s\t", str[j++]);
    }
    return 0;
}