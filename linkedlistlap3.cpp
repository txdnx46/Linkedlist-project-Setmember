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
/* ประเภทเเละฟังก์ชั่นทั้งหมด */

/*ปรับให้ส่วนนำหัวเเละท้ายว่างเปล่า*/
product *head = NULL;
product *end = NULL;

/*สร้างโหนด ที่ชื่อ initnode มา เก็บ ไอดี เเละ ชื่อ ราคา ของ สินค้า*/
product *initnode(int id, char *name, double price)
{
   product *ptr = new product;
   ptr->id = id;
   strcpy(ptr->name, name);
   ptr->price = price;
   return (ptr);
}

/*ฟังก์ชั่นเเรก อยู๋ใน node initnode ฟังก์ชั่น printnode ทำงานด้วยการ นำ ไอดี ชื่อ เเละ ราคา มาโชว์ */
void printnode(product *ptr)
{
   printf("ID: %d\tName: %s\tPrice: %.2f\n", ptr->id, ptr->name, ptr->price);
}
/*ฟังกืชั่น 2 อยู่ใน node initnode ชื่อ printlist ทำงานโดย ใช้ ลิงก์ ตัว ptr ไล่ค้นหา สิ่งที่อยู๋ใน product มา ทีละอย่างจนหมด เเล้วเอาออกมาโชว์ */
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
/*ฟังก์ชั่น compare เป็นฟังก์ชั่นเเยกออกมา จาก node อื่นๆ ซึ่งทำงาน เช็คค่าใน product  เเปรง product ให้เป็นพารามิเตอร์ a เเละ b ซึ่งนำมาหักลบกัน เพื่อจะดูว่าเหมือนกันหรือไม่  */
int compare(const void *a, const void *b)
{
   const product *productA = *(const product **)a;
   const product *productB = *(const product **)b;
   return productA->id - productB->id;
}

/*ฟังก์ชั่น printlistid ทำงานโดยไล่เช็ค id ใน product ทั้งหมดทีละตัว*/
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

/*ฟังก์ชั่น add ข้อมูลเข้า product ทำงานโดยใช้ ptr ทำเงื่อนไข ถ้า head = ว่างเปล่า ก็เเส้ง ptr เลย  
ถ้าเกิด  head มีค่าอยู่  ให้ทำเงื่อนไขสุดท้ายคือ  end -> next คือ ค่าต่อไปของค่าสุดท้าย ให้เอา ptr มาใส่เป็นตัวสุดท้ายเลบ */
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

/*node searchname  ทำงานโดย ใช่ ptr ไล่เช็คชื่อ สินค้า เมื่อ สินค้าเข้ามา จนกว่า จะถึงสินค้าตัวสุดท้าย*/
product *searchname(product *ptr, char *name)
{
   while (strcmp(name, ptr->name) != 0)
   {
      if (ptr == NULL)
      ptr = ptr->next;
         break;
   }
   return (ptr);
}

/*ฟังก์ชั่น ลบ โหนด โดยขอพื้นที่ให้ ตัวแปล tmp คือค่าที่รับมา , prv ให้เช็คระหว่างโหนดแรกกับโหนดหลัง
โดยกำหนด ให้ tmp = ptr เเละ prv = head  ต่อไปเข้าเงื่อนไข  ถ้าเมื่อไหร่ที่ tmp หรือ ptr เท่ากับ prv หรือ head 
ต่อไป นำค่า next ของ head มาเก็บไว้ใน head เเละนำเข้าเงื่อนไข ถ้า end เท่ากับ ptr เเล้ว ให้ end เก็บค่า end = end->next เเละ ลบ ptr */
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
   { // กรณีโหนดที่จะลบไม่ใช่โหนดแรก เเละสุดท้าย
   /*ให้ใช้  prv->next ไม่เท่ากับ ptr หรือ tmp 
   ให้เก็บค่า prv->next ไว้ใน prv
   เเลัวนำ ค่า prv->next เก็บ ค่าของ tmp หรือ ptr->next
   เเล้วนำเข้าเงื่อนไข end ถ้าตัวสุดท้ายมีค่าเท่ากับ tmp หรือ ptr ให้นำค่า prv มาเก็บใน end เเละ ลบ tmp หรือ ค่า ptr  */
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

/*ฟังก์ชั่น เพิ่มข้อมูลเข้า product  
ตัวแปล  newptr เข้าเงื่อนไข ถ้า head มีค่าว่างเปล่า ให้ ptr เข้าเเทนได่เลย เเล้วเป็นทั้งตัวเเรกเเลัะสุดท้าย*/
void insertnode(product *newptr)
{
   product *tmp, *prv;
   if (head == NULL)
   {
      head = newptr;
      end = newptr;
      return;
   } /*เเล้วมากำหนด ให้ tmp = head 
   ใช้เงื่อนไข ถ้า ชื่อที่อยู่ในตัวแปล newptr amd tmp มากกว่า 0 
   ให้ทำ tmp next
   เเละเข้าเงื่อนไข ถ้า tmp มีค่าว่าง ให้จบการทำงาน 
   เเล้วถ้า tmp = head ให้ newptr -> nenxt = head 
   เเล้วนำคา newptr มาเก็บไว้ใน  head*/
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
   }/*กรณีไม่เข้าเงื่อนไข ทั้งหมดด้านบนเลย ให้มาทำ เงื่อนไขสุดท้าย 
   คือ กำหนด ให่ prv = head เเละ ใช้ การวนลูป เมื่อ prv-> != tmp : ถ้าข้อมูลเเรกไม่เท่ากับ tmp
   ให้ next->prv เเล้วกำหนดค่า prv->next = newptr เเละนำค่า newptr->next เก็บค่า tmp เเล้วเข้าเงื่อนไข ถ้า ตัวสุดท้าย = prv ให้ end เป็นค่า tmp*/
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
      printf("MENU Appication\t\n"); printf("\n");
      printf("\t1 add a name \n");
      printf("\t2 delete a name \n");
      printf("\t3 list all names \n");
      printf("\t4 search for name \n");
      printf("\t5 insert a name \n");
      printf("\t6 search for id\n");
      printf("\t7 list all id\n");
      printf("\t0 quitAppication\n");printf("\n");
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