#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char s[] = "A2 : A1-3";
    char v[3],u[3];
    sscanf(s,"%s%s",v,u);
    printf("%s - %s\n",v,u);
    return 0;
}

































// nt dem(char str[])
// {
//     int dem = 0;
//     for (int i = 0; i < strlen(str); i++)
//     {
//         if (str[i] == ' ')
//         {
//             dem++;
//         }
//     }
//     return dem;
// }
// void idlancan(char str[], int arr[])
// {
//     char *token;
//     token = strtok(str, " ");
//     int i = 0;
//     while (token != NULL)
//     {
//         arr[i] = atoi(token);
//         i++;i
//         token = strtok(NULL, " ");
//     }
// }
// int main()
// {
//     char string[] = "1000 3012 1562 1212";
//     printf("%s\n", string);
//     char name[50], id[50];
//     int n, arr[4];
//     n = dem(string);
//     printf("%d\n", n);

//     idlancan(string, arr);

//     for (int i = 0; i <= n; i++)
//     {
//         printf("%d\n", arr[i]);
//     }
//     return 0;
// }