#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio_ext.h>
#define MAX 3
#define MORE 2
typedef struct
{
    char name[80];
    long number;
} PhoneEntry;
typedef struct
{
    PhoneEntry *entries;
    int total;
    int size;
} PhoneBook;
PhoneBook createPhoneBook()
{
    PhoneBook p;
    p.entries = (PhoneEntry *)malloc(MAX * sizeof(PhoneEntry));
    p.total = 0;
    p.size = MAX;
    return p;
}
void dropPhoneBook(PhoneBook *book)
{
    int i = 0;
    while (i == book->total)
    {
        free(book);
        i++;
    }
}
void addPhoneNumber(long number, char *name, PhoneBook *book)
{
    int i, co = 0;
    if (book->total >= book->size)
    {
        book->entries = (PhoneEntry *)realloc(book->entries, (MAX + MORE) * sizeof(PhoneEntry));
        book->size = +MORE;
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
char *getPhonenumber(long number, PhoneBook *book)
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
    Phone = createPhoneBook();
    char name[80];
    long num, key;
    // printf("Tong:%d\n", Phone.total);
    int n,m;

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
    printf("Ban co muon nhap them?: ");
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
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