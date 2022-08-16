#include <stdio.h>
int main()
{
    int h, p;
    float gio;
    printf("Nhap vao gio:");
    scanf("%d", &h);
    printf("Nhap vao phut:");
    scanf("%d", &p);
    gio = h + (float)p / 60;
    // printf("%f\n",gio);
    if (gio < 1)
    {
        printf("Hien dang la gio: Tys\n");
    }
    else if (gio >= 1 && gio < 3)
    {
        printf("Hien dang la gio: Suu\n");
    }
    else if (gio >= 3 && gio < 5)
    {
        printf("Hien dang la gio: Dan\n");
    }
    else if (gio >= 5 && gio < 7)
    {
        printf("Hien dang la gio: Mao\n");
    }
    else if (gio >= 7 && gio < 9)
    {
        printf("Hien dang la gio: Thin\n");
    }
    else if (gio >= 9 && gio < 11)
    {
        printf("Hien dang la gio: Tyj\n");
    }
    else if (gio >= 11 && gio < 13)
    {
        printf("Hien dang la gio: Ngo\n");
    }
    else if (gio >= 13 && gio < 15)
    {
        printf("Hien dang la gio: Mui\n");
    }
    else if (gio >= 15 && gio < 17)
    {
        printf("Hien dang la gio: Than\n");
    }
    else if (gio >= 17 && gio < 19)
    {
        printf("Hien dang la gio: Dau\n");
    }
    else if (gio >= 19 && gio < 21)
    {
        printf("Hien dang la gio: Tuat\n");
    }
    else if (gio >= 21 && gio < 23)
    {
        printf("Hien dang la gio: Hoi\n");
    }
    else if (gio >= 23 && gio < 24)
    {
        printf("Hien dang la gio: Tys\n");
    }
    else
    {
        printf("Gio ban nhap khong hop le!\n");
    }

    return 0;
}