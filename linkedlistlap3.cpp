#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct node
{
   int id;
   char name[45];
   double price;
   struct node *next;
} product;

/* function prototypes */
product *initnode(char *, int);
void printnode(product *);
void printlist(product *);
void add(product *);
product *searchname(product *, char *);
void deletenode(product *);
void insertnode(product *);
void deletelist(product *);

product *head = NULL;
product *end = NULL;

product *initnode(int id, char *name, double price)
{
   product *ptr = new product;
   ptr->id = id;
   strcpy(ptr->name, name);
   ptr->price = price;
   return (ptr);
}

void printnode(product *ptr)
{
   printf("ID: %d\tName: %s\tPrice: %.2f\n", ptr->id, ptr->name, ptr->price);
}

void printlist(product *ptr)
{
   if (ptr == NULL)
      return;
   while (ptr != NULL)
   {
      printnode(ptr);
      ptr = ptr->next;
   }
}

int compare(const void *a, const void *b)
{
   const product *productA = *(const product **)a;
   const product *productB = *(const product **)b;
   return productA->id - productB->id;
}

void printlistid(product *ptr)
{
   if (ptr == NULL)
      return;

   // นับจำนวนโหนดทั้งหมดในรายการ
   int count = 0;
   product *currentNode = ptr;
   while (currentNode != NULL)
   {
      count++;
      currentNode = currentNode->next;
   }

   // สร้างอาร์เรย์เก็บตัวแปร pointer ไปยังโหนดในรายการ
   product **nodeArray = (product **)malloc(count * sizeof(product *));
   currentNode = ptr;
   for (int i = 0; i < count; i++)
   {
      nodeArray[i] = currentNode;
      currentNode = currentNode->next;
   }

   // เรียงลำดับอาร์เรย์ของโหนดตาม id
   qsort(nodeArray, count, sizeof(product *), compare);

   // พิมพ์โหนดตามลำดับที่เรียงแล้ว
   for (int i = 0; i < count; i++)
   {
      printnode(nodeArray[i]);
   }

   free(nodeArray);
}

void add(product *newptr)
{
   if (head == NULL)
   {
      head = newptr;
   }
   else
   {
      end->next = newptr;
   }
   end = newptr;
}

product *searchname(product *ptr, char *name)
{
   while (strcmp(name, ptr->name) != 0)
   {
      ptr = ptr->next;
      if (ptr == NULL)
         break;
   }
   return (ptr);
}

/*product *searchid(product *ptr, int id) {
   while (ptr != NULL && ptr->id != id) {
      ptr = ptr->next;
   }
   return ptr;
}*/

void deletenode(product *ptr)
{
   product *tmp, *prv;
   tmp = ptr;
   prv = head;
   if (tmp == prv)
   {
      head = head->next;
      if (end == tmp)
      {
         end = end->next;
         delete (tmp);
      }
   }
   else
   { // กรณีโหนดที่จะลบไม่ใช่โหนดแรก
      while (prv->next != tmp)
      {
         prv = prv->next;
      }
      prv->next = tmp->next;
      if (end == tmp)
         end = prv;
      delete (tmp);
   }
}

void insertnode(product *newptr)
{
   product *tmp, *prv;
   if (head == NULL)
   {
      head = newptr;
      end = newptr;
      return;
   }
   tmp = head;
   while (strcmp(tmp->name, newptr->name) < 0)
   {
      tmp = tmp->next;
      if (tmp == NULL)
         break;
   }
   if (tmp == head)
   {
      newptr->next = head;
      head = newptr;
   }
   else
   {
      prv = head;
      while (prv->next != tmp)
      {
         prv = prv->next;
      }
      prv->next = newptr;
      newptr->next = tmp;
      if (end == prv)
         end = newptr;
   }
}

void deletelist(product *ptr)
{
   product *temp;
   if (ptr == NULL)
      return;

   while (ptr != NULL)
   {
      temp = ptr->next;
      delete (ptr);
      ptr = temp;
   }
}
product *searchid(product *ptr, int id)
{
   while (ptr != NULL)
   {
      if (ptr->id == id)
         return ptr;
      ptr = ptr->next;
   }
   return NULL;
}
void id(product *ptr)
{
   printf("Product IDs:\n");
   while (ptr != NULL)
   {
      printf("ID: %d\n", ptr->id);
      ptr = ptr->next;
   }
} /*stop funtionsearch id */

int main()
{
   int id;
   char name[20];
   double price;
   int ch = 9;
   product *ptr;

   while (ch != 0)
   {
      system("cls");
      printf("1 add a name \n");
      printf("2 delete a name \n");
      printf("3 list all names \n");
      printf("4 search for name \n");
      printf("5 insert a name \n");
      printf("6 search for id\n");
      printf("7 list all id\n");
      printf("0 quit\n");
      printf("Please select menu: ");
      scanf("%d", &ch);

      switch (ch)
      {
      case 1:
         printf("Enter in id : ");
         scanf("%d", &id);
         printf("Enter in name : ");
         scanf("%s", name);
         printf("Enter in price : ");
         scanf("%lf", &price);
         ptr = initnode(id, name, price);
         add(ptr);
         break;
      case 2:
         printf("Enter Product Name: ");
         scanf("%s", name);
         ptr = searchname(head, name);
         if (ptr == NULL)
         {
            printf("Name %s not found\n", name);
            getch();
         }
         else
         {
            deletenode(ptr);
         }
         break;

      case 3:
         printlist(head);
         getch();
         break;

      case 4:
         printf("Enter Product Name: ");
         scanf("%s", name);
         ptr = searchname(head, name);
         if (ptr == NULL)
         {
            printf("Name %s not found\n", name);
         }
         else
         {
            printnode(ptr);
         }
         getch();
         break;
      case 5:
         printf("Enter in id : ");
         scanf("%d", &id);
         printf("Enter in name : ");
         scanf("%s", name);
         printf("Enter in price : ");
         scanf("%lf", &price);
         ptr = initnode(id, name, price);
         insertnode(ptr);
         getch();
         break;
      case 6:
         printf("Enter SearchProduct ID: ");
         scanf("%d", &id);
         ptr = searchid(head, id);
         if (ptr == NULL)
         {
            printf("Product ID %d not found\n", id);
         }
         else
         {
            printnode(ptr);
         }
         getch();
         break; /*stop end case 6 funtion search ID*/
      case 7:
         printlistid(head);
         getch();
         break;
      }
   }
   deletelist(head);
}