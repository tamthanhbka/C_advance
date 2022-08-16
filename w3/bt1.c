#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio_ext.h>
#define MAX 1000
typedef struct
{
    char name[80];
    long number;
} PhoneEntry;
typedef struct
{
    PhoneEntry entries[MAX];
    int total;
} PhoneBook;
void addPhoneNumber(long number, char *name, PhoneBook *book)
{
    int i, co = 0;
    if (book->total >= MAX)
    {
        printf("Danh sach da day!\n");
    }
    for (int i = 0; i < book->total; i++)
    {
        if (strcmp(book->entries[i].name, name) == 0)
        {
            book->entries[i].number = number;
            co = 1;
        }
    }
    if (co == 0)
    {
        strcpy(book->entries[book->total].name, name);
        book->entries[book->total].number = number;
        book->total++;
    }
}
char *getPhonenumber(long number,  PhoneBook *book)
{
    for (int i = 0; i < book->total; i++)
    {
        if (number == book->entries[i].number)
        {
            return book->entries[i].name;
        }
        else
        {
            return NULL;
        }
    }
}
int main()
{
    PhoneBook Phone;
    Phone.total = 0;
    char name[80];
    long num, key;
    // printf("Tong:%d\n", Phone.total);
    int n;

    printf("Ban muon them bao nhieu nguoi vao danh ba? ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Nhap ten: ");
        __fpurge(stdin);
        fgets(name, 80, stdin);
        name[strlen(name) - 1] = 0;
        printf("Nhap sdt: ");
        scanf("%d", &num);
        addPhoneNumber(num, name, &Phone);
    }
    for (int i = 0; i < Phone.total; i++)
    {
        printf("%s : %d\n", Phone.entries[i].name, Phone.entries[i].number);
    }
    printf("Nhap so dien thoai ban muon tim: ");
    scanf("%d", &key);
    if (getPhonenumber(key, &Phone) == NULL)
    {
        printf("khong tim thay!\n");
    }
    else
    {
        printf("Name:%s\n", getPhonenumber(key, &Phone));
    }

    //printf("")
    return 0;
}