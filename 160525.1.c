#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "product.bat"

typedef struct Product
{
    int id;
    char name[20];
    float price;
    int stock;
} Product;

void menu();
void addProducts();
void updateProduct();
void showProducts();
void deleteProduct();

int main(void)
{
    menu();
    return 0;
}

void menu()
{
    int choise;
    while(1)
    {
        printf("\n---URUN YONETIMI---\n");
        printf("1. Urun Ekleme\n");
        printf("2. Stok Guncelleme\n");
        printf("3. Urunleri Goster\n");
        printf("4. Urun Silme\n");
        printf("5. Cikis\n");

        printf("Secim Yapiniz: ");
        scanf("%d", &choise);

        switch (choise)
        {
            case 1:
                addProducts();
                break;
            case 2:
                updateProduct();
                break;
            case 3:
                showProducts();
                break;
            case 4:
                deleteProduct();
                break;
            case 5:
                printf("Cikis yapiliyor...\n");
                exit(0);
                break;
            default:
                printf("Gecersiz secim!\n");
        }
    }
}

void addProducts()
{
    FILE *file = fopen(FILE_NAME, "ab");
    if(!file)
    {
        printf("Dosya acilamadi!\n");
        return;
    }

    Product p;

    printf("Urun ID: ");
    scanf("%d", &p.id);
    printf("Urun Adi: ");
    scanf("%s", p.name);
    printf("Urun Fiyati: ");
    scanf("%2f", &p.price);
    printf("Urun Miktari: ");
    scanf("%d", &p.stock);

    if (fwrite(&p, sizeof(Product), 1, file) == 1)
    {
        printf("Urun dosyaya eklendi.\n");
    }
    else
    {
        printf("Urun dosyaya eklenemedi.\n");
    }

    fclose(file);
}

void updateProduct()
{
    FILE *file = fopen(FILE_NAME, "rb+");
    if (!file)
    {
        printf("Dosya acilamadi!\n");
        return;
    }

    Product p;
    int id, found = 0;

    printf("Guncellenmek istenen Urun ID'sini girin: \n");
    scanf("%d", &id);
    
    while(fread(&p, sizeof(struct Product), 1, file))
    {
        if (p.id == id)
        {
            found = 1;

            printf("Yeni stok miktari: \n");
            scanf("%d", &p.stock); //p.stock

            fseek(file, -sizeof(Product), SEEK_CUR);

            if (fwrite(&p, sizeof(Product), 1, file) == 1)
            {
                printf("Urun guncellendi.\n");
            }
            else
            {
                printf("Urun guncellenemedi.\n");
            }

            break;
        }
    }

    if (!found)
    {
        printf("Urun bulunamadi!\n");
    }
        
    fclose(file);
}

void showProducts()
{
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file)
    {
        printf("Dosya acilamadi!\n");
        return;
    }

    Product p;
    int id, found = 0;

    printf("Urun ID'sini girin (hepsi icin 0): \n");
    scanf("%d", &id);

    if (id == 0)
    {
        while(fread(&p, sizeof(Product), 1, file))
        {
            printf("ID: %d\n", p.id);
            printf("Urun Adi: %s\n", p.name);
            printf("Fiyat: %.2f\n", p.price);
            printf("Stok: %d\n", p.stock);
            printf("-------------------------\n");

            found++;
        }
    }
    else
    {
        while(fread(&p, sizeof(Product), 1, file))
        {
            if (p.id == id)
            {
                found = 1;
                printf("ID: %d\n", p.id);
                printf("Urun Adi: %s\n", p.name);
                printf("Fiyat: %.2f\n", p.price);
                printf("Stok: %d\n", p.stock);
                found = 1;
                printf("-------------------------\n");
                break;
            }
        }
    }
    if (!found)
    {
        printf("Urun bulunamadi!\n");
    }

    fclose(file);
}

void deleteProduct()
{
    FILE *file = fopen(FILE_NAME, "rb");
    FILE *tempFile = fopen("temp.bat", "wb");
    if (!file || !tempFile)
    {
        printf("Dosya acilamadi!\n");
        if(file) fclose(file);
        if(tempFile) fclose(tempFile);
        return;
    }

    Product p;
    int id, found = 0;

    printf("Silinecek Urun ID'sini girin: \n");
    scanf("%d", &id);

    while (fread(&p, sizeof(Product), 1, file))
    {
        if (p.id == id)
        {
            found = 1;
            continue; // bu urunu gec
        }

        fwrite(&p, sizeof(Product), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        remove(FILE_NAME); // eski dosyayi sil
        rename("temp.bat", FILE_NAME); // yeni dosyayi eski dosya ismiyle degistir
        printf("Urun basariyla silindi.\n");
    }
    else
    {
        remove("temp.bat"); // gecici dosyayi sil
        printf("Urun bulunamadi!\n");
    }
}