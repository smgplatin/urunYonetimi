//linked lists
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int veri;
    struct Node *next;
};

typedef struct Node node;
node *head = NULL;

void yazdir():
void basaEkle(int veri);
void arayaEkle(int veri, int sira);
void sonaEkle(int veri);
void dugumSil(int sira);

int main()
{
    int secim;

    while(1)
    {
        printf("\n------MENU------\n");
        printf("1. Listeyi goruntule\n");
        printf("2. Basa eleman ekle\n");
        printf("3. Araya eleman ekle\n");
        printf("4. Sona eleman ekle\n");
        printf("5. CIikis yap\n");
        scanf("%d", &secim);
        switch (secim)
        {
            case 1:
                yazdir();
                break;
            case 2:
                printf("Basa eklemek istediginiz elemani girin: ");
                int veri;
                scanf("%d", &veri);
                basaEkle(veri);
                break;
            case 3:
                printf("Araya eklemek istediginiz elemani girin: ");
                scanf("%d", &veri);
                printf("Eklemek istediginiz sirayi girin: ");
                int sira;
                scanf("%d", &sira);
                arayaEkle(veri, sira);
                break;
            case 4:
                printf("Sona eklemek istediginiz elemani girin: ");
                scanf("%d", &veri);
                sonaEkle(veri);
                break;
            case 5:
                exit(0);
            default:
                printf("Gecersiz secim!\n");
        }
    }
}

void yazdir()
{
    node *temp = head;

    printf("Liste: \n");
    while (temp != NULL)
    {
        printf("%d ", temp->veri);
        temp = temp->next;
    }
    printf("NULL\n");
}
