//#include<stdio.h>
//#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;

struct node
{
    char foodname[50];
    int quantity;
    float price;
    int data;
    struct node *prev;
    struct node *next;
};

struct node *headc = NULL,*newnode,*tailc = NULL;
struct node *heada = NULL, *taila = NULL;
struct node *head_s;

void adminmenu()
{
    cout<<"\n\t\t1. View total sales\n";
    cout<<"\t\t2. Add new items in the order menu\n";
    cout<<"\t\t3.Delete items from the order menu\n";
    cout<<"\t\t4. Display order menu\n";
    cout<<"\t\t5. Back To Main Menu \n\n";
    cout<<"\t\t   Enter Your Choice --->";
}

void customermenu()
{
    cout<<"\n\t\t1. Place your order\n";
    cout<<"\t\t2. View your ordered items\n";
    cout<<"\t\t3. Delete an item from order\n";
    cout<<"\t\t4. Display final bill\n";
    cout<<"\t\t5. Back To Main Menu \n\n";
    cout<<"\t\t   Enter Your Choice --->";
}
                             //       5                6         rice                20
struct node* createadmin(struct node *head,int data, const char foodname[25], float price)
{
    newnode = (struct node*)malloc(sizeof(struct node));

    newnode->data = data;//6
    newnode->price = price;//20
    newnode-> quantity = 0;
    strcpy(newnode->foodname,foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head;//

    if(temp==NULL)
        heada = taila = newnode;
    else
    {                          //               t
        while(temp->next!=NULL)//1   2  3   4   5   6
            temp=temp->next;  // 10  20 30  40  500  600

        temp->next=newnode;//
        newnode->prev = taila;
        taila = newnode;
    }

    return heada;
}
                                     //     null       1          1      //  temp1
struct node* createcustomer(struct node *head,int data,int quantity)//  1->next 200    3 ->next  NULL
                                                                    //  100              200
{
   newnode = (struct node*)malloc(sizeof(struct node));
     //newnode=new node;
    struct node *temp1 = heada;
    int flag = 0;
    while(temp1!=NULL)
    {                         //   t  n
        if(temp1->data==data)//1   2  3  4  5
        {
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }

    if(flag==1)
    {
        newnode->data = data;
        newnode->price = quantity*(temp1->price);//2*50=100
        newnode-> quantity = quantity;//2
        strcpy(newnode->foodname,temp1->foodname);
        newnode->next = NULL;
        newnode->prev = NULL;

        struct node *temp = head;//head of cust

        if(temp==NULL)
            headc = tailc = newnode;//1
        else
        {
            while(temp->next!=NULL)//1  2   3   4   5
                temp=temp->next;

            temp->next=newnode;
            newnode->prev = tailc;
            tailc = newnode;
        }


    }
    else
    {
        cout<<"\n\t\tThis item is not present in the menu!\n";
    }
    return headc;
}
                                        //  t
void displayList(struct node *head)//heada  1 2  3  4 5 6
{
    struct node *temp1 = head;
    if(temp1==NULL)
    {
        cout<<"\n\t\tList is empty!!\n\n";
    }
    else
    {
        cout<<"\n";
        while(temp1!=NULL)
        {
            if(temp1->quantity==0)//
                cout<<"\t\t"<<temp1->data<<"\t"<<temp1->foodname<<"\t"<<temp1->price<<endl;
            else
            {
                cout<<"\t\t"<<temp1->data<<"\t"<<temp1->foodname<<"\t"<<temp1->quantity<<"\t"<<temp1->price<<endl;
            }

            temp1 = temp1->next;
        }
        cout<<"\n";
    }

}

struct node* totalsales(int data,int quantity)//2   2
{
    newnode = (struct node*)malloc(sizeof(struct node));
    int flag = 0;
                            //      t
    struct node *temp1 = heada;//1  2  3  4  5
    while(temp1->data!=data)//
    {
        temp1 = temp1->next;
    }

    newnode->data = data;
    newnode->price = quantity*(temp1->price);//300
    newnode-> quantity = quantity;//2
    strcpy(newnode->foodname,temp1->foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head_s;

    if(temp==NULL)
        head_s = newnode;
    else
    {
        while(temp->next!=NULL)
        {
            if(temp->data==data)
            {
                flag = 1;
                break;
            }
            temp=temp->next;
        }

        if(flag==1)
        {
            temp->quantity += newnode-> quantity;
            temp->price += newnode->price;
        }
        else
        {
            temp->next=newnode;
        }
    }

    return head_s;
}

void calculatetotsales()
{
    struct node *temp = headc;
    while(temp!=NULL)
    {
        head_s = totalsales(temp->data, temp->quantity);
        temp=temp->next;
    }
}

struct node* del(int data,struct node* head, struct node* tail)
{
    if(head==NULL)
    {
        cout<<"\n\t\tList is empty\n";
    }
    else
    {
        struct node* temp;//  head           tail
        if(data==head->data)//1  2  3  4  5  6
        {              //   head
            temp = head;//  2  3  4  5  6
            head = head->next;//
            if (head != NULL)
                head->prev = NULL;
            free(temp);
        }
        else if(data==tail->data)//
        {        //                  tail
            temp = tail;//1  2  3  4  5
            tail = tail->prev;
            tail->next = NULL;
            free(temp);
        }
        else
        {               //   t  k  d  l
            temp = head;//1  2  3  4  5  6
            while(data!=temp->data)//2!=4
            {
                temp = temp->next;
            }
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            free(temp);
        }
    }
    return head;
}

int deleteadmin()
{
    cout<<"\n\t\tEnter serial no. of the food item which is to be deleted: ";
    int num;
    cin>>num ;//2
    //scanf("%d",&num);

    struct node* temp=heada;
    while(temp!=NULL)
    {        //  2         2
        if (temp->data == num)//1  2   3  4  5  6
        {
            heada = del(num, heada, taila);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}

int deletecustomer()
{
    cout<<"\n\t\tEnter serial no. of the food item which is to be deleted: ";
    int num;//3
    cin>>num ;
    //scanf("%d",&num);

    struct node* temp=headc;
    while(temp!=NULL)
    {
        if (temp->data == num)//2 3
        {
            headc = del(num, headc, tailc);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}

void displaybill()
{
    displayList(headc);
    struct node *temp = headc;
    float total_price = 0;
    while (temp!=NULL)
    {
        total_price +=temp->price;//total=total+price
        temp = temp->next;
    }

    cout<<"\t\tTotal price:"<< total_price<<endl;

}

struct node* deleteList(struct node* head)
{
    if(head==NULL)
    {
        return NULL;
    }
    else
    {
        struct node* temp = head;
        while(temp->next!=0)
        {
            temp = temp->next;
            free(temp->prev);
        }
        free(temp);
        head = NULL;
    }

    return head;
}

void admin()
{
    cout<<"\n\t\t   ----------------------------------------------\n";
    cout<<"\t\t\t  ADMIN SECTION\n";
    cout<<"\t\t  ----------------------------------------------\n";
    while(1)
    {
        adminmenu();

        int num ,flag = 0;
        char name[50];
        float price;
        struct node* temp = NULL ;

        int opt;
        scanf("%d",&opt);
    /*cout<<"\n\t\t1. View total sales\n";
    cout<<"\t\t2. Add new items in the order menu\n";
    cout<<"\t\t3.Delete items from the order menu\n";
    cout<<"\t\t4. Display order menu\n";
    cout<<"\t\t5. Back To Main Menu \n\n";
     */
        if(opt==5)
            break;

        switch (opt)
        {
            case 1:
                displayList(head_s);
                break;
            case 2:

                cout<<"\n\t\tEnter serial no. of the food item: ";
                //int num,flag = 0;
                //char name[50];
                //float price;
                scanf("%d",&num);

                //struct node *temp = heada;
                temp = heada ;
  /*heada = createadmin(heada,1,"Hot and Sour Soup",100);
    heada = createadmin(heada,2,"Manchow Soup",200);
    heada = createadmin(heada,3,"Manchurian Noodles",150);
    heada = createadmin(heada,4,"Fried Rice",180);
    heada = createadmin(heada,5,"Hakka Noodles",80);
    heada = createadmin(heada,6,"rice",20);
     */

                                                  // t-next=NULL
                while(temp!=NULL)//1   2    3   4  5
                {
                    if(temp->data==num)//5==4
                    {
                        cout<<"\n\t\tFood item with given serial number already exists!!\n\n";
                        flag = 1;
                        break;
                    }
                    temp = temp->next;//2
                }

                if(flag==1)
                    break;

                cout<<"\t\tEnter food item name: ";
                cin>>name ;//white rice
                //scanf("%s",name);
                cout<<"\t\tEnter price: ";
                cin>>price ;//20
                //scanf("%f",&price);
                heada = createadmin(heada, num, name, price);
                cout<<"\n\t\tNew food item added to the list!!\n\n";
                break;
            case 3:
                if(deleteadmin())
                {
                    cout<<"\n\t\t### Updated list of food items menu ###\n";
                    displayList(heada);
                }
                else
                    cout<<"\n\t\tFood item with given serial number doesn't exist!\n\n";

                break;
            case 4:
                cout<<"\n\t\t   ### Order menu ###\n";
                displayList(heada);
                break;

            default:
                cout<<"\n\t\tWrong Input !! PLease choose valid option\n";
                break;
        }
    }
}

void customer()
{
    int flag=0,j=1;
    char ch;
    cout<<"\n\t\t  ----------------------------------------------\n";
    cout<<"\t\t    CUSTOMER SECTION\n";
    cout<<"\t\t   ----------------------------------------------\n";
    while(1)
    {
        customermenu();
      /*  cout<<"\n\t\t1. Place your order\n";
    cout<<"\t\t2. View your ordered items\n";
    cout<<"\t\t3. Delete an item from order\n";
    cout<<"\t\t4. Display final bill\n";
    cout<<"\t\t5. Back To Main Menu \n\n";
    cout<<"\t\t   Enter Your Choice --->";*/
        int n , quantity ;
        int opt;
        cin>>opt ;
        //scanf("%d",&opt);

        if(opt==5)
            break;

        switch (opt)
        {
            case 1:
                displayList(heada);
                cout<<"\n\t\tEnter number corresponding to the item you want to order: ";
                //int n;
                cin>>n ;
                //scanf("%d",&n);
                cout<<"\t\tEnter quantity: ";
                //int quantity;
                cin>>quantity ;
                //scanf("%d",&quantity);
                headc = createcustomer(headc, n, quantity);
                break;
            case 2:
                cout<<"\n\t\t  ### List of ordered items ###\n";
                displayList(headc);
                break;
            case 3:
                if(deletecustomer())
                {
                    cout<<"\n\t\t### Updated list of your ordered food items ###\n";
                    displayList(headc);
                }
                else
                {
                    cout<<"\n\t\tFood item with given serial number doesn't exist!!\n";
                break;
                }
            case 4:
                calculatetotsales();
                cout<<"\n\t\t  ### Final Bill ###\n";
                displaybill();
                headc = deleteList(headc);
                cout<<"\n\t\tPress any key to return to main menu:\n\t\t\t\t\t\t";
                fflush(stdin);
                ch=fgetc(stdin);
                flag=1;
                break;

            default:
                cout<<"\n\t\tWrong Input !! PLease choose valid option\n";
                break;
        }
        if(flag==1)
        {
            break;
        }
    }
}

void mainnenu()
{
    cout<<"\n                                 **********\n";
    cout<<"                           WELCOME TO RESTAURANT MANAGEMENT SYSTEM\n";
    cout<<"                                 **********\n\n\n";
    cout<<"\t\t1. ADMIN SECTION--> \n";
    cout<<"\t\t2. CUSTOMER SECTION--> \n";
    cout<<"\t\t3. Exit--> \n\n";
    cout<<"\t\tEnter Your Choice --->";
}

int main()
{
    heada = createadmin(heada,1,"Hot and Sour Soup",100);
    heada = createadmin(heada,2,"Manchow Soup",200);
    heada = createadmin(heada,3,"Manchurian Noodles",150);
    heada = createadmin(heada,4,"Fried Rice",180);
    heada = createadmin(heada,5,"Hakka Noodles",80);

    while(1)
    {
        mainnenu();
        int choice;
        cin>>choice ;
        //scanf("%d",&choice);

        if(choice==3)
        {
            cout<<"\n\n\t\t**Thank you!!**\n";
            break;
        }

        switch (choice)
        {
            case 1:
            {   admin();
                break;
            }
            case 2:
            {
                customer();
                break;
            }
            case 3:
            {
                break;
            }

            default:
            {
                cout<<"\n\t\tWrong Input !! PLease choose valid option\n";
            }   break;
        }
    }
}
