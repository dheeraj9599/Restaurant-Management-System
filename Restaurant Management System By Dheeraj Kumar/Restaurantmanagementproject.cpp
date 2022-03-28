                                                                       // A Restaurant Management Project 
                                                                     // Made By - Dheeraj Kumar                                                                
#include <iostream>
#include <string.h>

using namespace std;

struct node
{
    char foodname[40];
    int quantity;
    float price;
    int data;
    struct node *prev;
    struct node *next;
}*head_Cust = NULL,*newnode,*tail_Cust = NULL, *head_adm = NULL, *tail_adm = NULL, *head_sale; //globally accesible pointers

//Some Abbreviation
//Cust is for Customer and adm is for admin, fitem for fooditem
void adminmenu()
{
    cout<<"\n\t\t\t\t\t\t     1. Add new fooditem in the order menu\n";
    cout<<"\t\t\t\t\t\t     2. Delete fooditem from the order menu\n";
    cout<<"\t\t\t\t\t\t     3. Total sales Done Yet \n";
    cout<<"\t\t\t\t\t\t     4. Display the order menu\n";
    cout<<"\t\t\t\t\t\t     5. Back To Main Menu \n\n";
    cout<<"\t\t\t\t\t\t     Please Enter Your Choice(1 to 5) ---> ";
}
void customermenu()
{
    cout<<"\n\t\t\t\t\t\t     1. Place your order\n";
    cout<<"\t\t\t\t\t\t     2. View your ordered items\n";
    cout<<"\t\t\t\t\t\t     3. Delete an item from order\n";
    cout<<"\t\t\t\t\t\t     4. Display final bill\n";
    cout<<"\t\t\t\t\t\t     5. Back To Main Menu \n\n";
    cout<<"\t\t\t\t\t\t     Please Enter Your Choice(1 to 5) ---> ";
}
struct node* Add_new_fitem_from_adm(struct node *head,int data,const char foodname[40], float price)
{
    newnode = new node();
    newnode->data = data;
    newnode->price = price;
    newnode-> quantity = 0;
    strcpy(newnode->foodname,foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head;
    if(temp==NULL)
        head_adm = tail_adm = newnode;
    else
    {
        while(temp->next!=NULL)
            temp=temp->next;

        temp->next=newnode;
        newnode->prev = tail_adm;
        tail_adm = newnode;
    }
    return head_adm;
}

struct node* order_by_customer(struct node *head,int data,int quantity)
{
    newnode = new node();
    struct node *temp1 = head_adm;
    int flag = 0;
    while(temp1!=NULL)
    {
        if(temp1->data==data) //Comparing admin order list with customer order no.
        {
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }
    if(flag==1)
    {
        newnode->data = data;
        newnode->price = quantity*(temp1->price);
        newnode-> quantity = quantity;                     //order creation
        strcpy(newnode->foodname,temp1->foodname);
        newnode->next = NULL;
        newnode->prev = NULL;

        struct node *temp = head;
        if(temp==NULL) 
            head_Cust = tail_Cust = newnode; 
        else
        {       while(temp->next!=NULL)
                temp=temp->next;

            temp->next=newnode;
            newnode->prev = tail_Cust;
            tail_Cust = newnode;
        }
    }
    else
    {
        cout<<"\n\t\t\t\t\t\t\tThis item is not present in the menu!\n";
    }
    return head_Cust;
}

void displayList(struct node *head)
{
    int i=0,j=0;
    struct node *temp1 = head;
        while(temp1!=NULL)
        {       if(temp1->quantity==0){
                if(i==0){
                cout<<"\n\t\t\t\t\t\t   S.no    Food name\t\tPrice\n";}
                cout<<"\t\t\t\t\t\t    "<<temp1->data<<"     "<<temp1->foodname<<"          Rs."<<temp1->price<<"\n";
                i=1;}
            else
            {   if(j==0){
                cout<<"\n\t\t\t\t\t\t   S.no   Food name    Quantity      Price\n";}
                cout<<"\t\t\t\t\t\t    "<<temp1->data<<"     "<<temp1->foodname<<"     "<<temp1->quantity<<"     "<<"     Rs."<<temp1->price<<"\n";
            j=1;            }
            temp1 = temp1->next;
        }
        cout<<"\n";
}

struct node* totalsales(int data,int quantity){
    newnode = new node();
    int flag = 0;
    struct node *temp1 = head_adm;
    while(temp1->data!=data)
    {
        temp1 = temp1->next;
    }
      //making new node for sale list
    newnode->data = data;
    newnode->price = quantity*(temp1->price);
    newnode-> quantity = quantity;
    strcpy(newnode->foodname,temp1->foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head_sale;

    if(temp==NULL)
        head_sale = newnode;  // 1st order details in sales list
    else
    {
        while(temp->next!=NULL)
        {
            if(temp->data==data)
            {
                flag = 1;     //same order in the sale list
                break;
            }
            temp=temp->next;
        }
        if(flag==1)
        {
            temp->quantity += newnode-> quantity; //if same order occur in the sale list just add that fooditem in separate node
            temp->price += newnode->price;
        }
        else
        {
            temp->next=newnode;
        }
    }
    return head_sale;
}

void calculatetotsales()
{
    struct node *temp = head_Cust;
    while(temp!=NULL)
    {   head_sale = totalsales(temp->data, temp->quantity);
        temp=temp->next;
    }
}

struct node* deletion(int data,struct node *head, struct node* tail) //data=num=serialno.
{
    if(head==NULL)
    {
        cout<<"\n\t\t\t\t\t\t\t!Order List is empty!\n";
    }
    else
    {   struct node* temp;
        if(data==head->data)
        {
            temp = head;
            head = head->next;
            if (head != NULL)   
                head->prev = NULL;
            free(temp);
        }
        else if(data==tail->data)
        {
            temp = tail;
            tail = tail->prev; 
            tail->next = NULL;
            free(temp);
        }
        else
        {
            temp = head;
            while(data!=temp->data)
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

int delete_fitem_from_adm()
{
    cout<<"\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted : ";
    int num;
    cin>>num;
    struct node* temp=head_adm;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {   head_adm = deletion(num, head_adm, tail_adm);
            return 1;
        }
        temp=temp->next;
    }
    return 0;
}

int deleteOrder_bycust()
{
    if(head_Cust==NULL){
    cout<<"\n\t\t\t\t\tYou does not placed any order yet \n";
    return 0;
    }
    cout<<"\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ";
    int num;
    cin>>num;
    struct node* temp=head_Cust;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            head_Cust = deletion(num, head_Cust, tail_Cust);
            return 1;
        }
        temp=temp->next;
    }
    return 0;
}

void displaybill()
{
    displayList(head_Cust);
    struct node *temp = head_Cust;
    float total_price = 0;
    while (temp!=NULL)
    {
        total_price +=temp->price;
        temp = temp->next;
    }
    cout<<"\t\t\t\t\t\t\t   |Total price : Rs"<< total_price<<"|"<<endl;

}

void admin()
{
    system("Color 0A");
    cout<<"\n\t\t\t\t\t      ----------------------------------------------\n";
    cout<<"\t\t\t\t\t      |              !ADMIN SECTION!               |  \n";
    cout<<"\t\t\t\t\t      ----------------------------------------------\n";
    while(1)
    {   adminmenu();
        char name[40];
        int opt;
        cin>>opt;
        if(opt==5)
            break;

        switch (opt)
        {
            case 1:
                int num,flag;    
                num=0;
                flag=0;
                float price;
                cout<<"\n\t\t\t\t\t\t\tEnter serial no. of the food item: ";
                cin>>num;  
                struct node *temp ;
                temp = head_adm;
                while(temp!=NULL)
                {
                    if(temp->data==num)
                    {
                        cout<<"\n\t\t\t\t\t\tFood item with given serial number already exists!!\n\n";
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }
                if(flag==1)
                    break;

                else{
                cout<<"\t\t\t\t\t\t\tEnter The food item name : ";
                cin.ignore();
                cin.getline(name,40); 
                cout<<"\t\t\t\t\t\t\tDeclare price : ";
                cin>>price;
                head_adm = Add_new_fitem_from_adm(head_adm, num, name, price);
                cout<<"\n\t\t\t\t\t\t\tNew food item added to the list!!\n\n";
                break;
                }
            case 2:
                if(head_adm==NULL)
                {   cout<<"\n\t\t\t\t\t\t\tNo Food item is available";
                    break;
                }
                if(delete_fitem_from_adm())
                {   cout<<"\n\t\t\t\t\t\tThis Food item is deleted successfully\n";
                    cout<<"\n\t\t\t\t\t\t### Updated list of food items menu ###\n";
                    displayList(head_adm);
                }
                else
                    cout<<"\n\t\t\t\t\t\tFood item with given serial number doesn't exist!\n\n";
                break;
            case 3:
                if(head_sale==NULL){
                    cout<<"\n\t\t\t\t\t\t     No sales done as No Customer ordered yet\n";
                    break;
                }
                displayList(head_sale);
                break;    
            case 4:
                if(head_adm==NULL){
                    cout<<"Food item list is empty\n";
                    break;
                }
                cout<<"\n\t\t\t\t\t\t\t   ### Order menu ###\n";
                displayList(head_adm);
                break;
            default:
                cout<<"\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n";
                break;
        }
    }
}

struct node* deleteList(struct node* head)
{
    if(head==NULL)
    {
        return NULL;
    }
    else
    {   struct node* temp = head;
        while(temp->next!=0)
        {   temp = temp->next;
            free(temp->prev);
        }
        free(temp);
        head = NULL;
    }
    return head;
}

void customer()
{
    int flag=0,j=1;
    char ch;
    system("Color 0B");
    cout<<"\n\t\t\t\t\t      ----------------------------------------------\n";
    cout<<"\t\t\t\t\t      |             !CUSTOMER SECTION!             |\n";
    cout<<"\t\t\t\t\t      ----------------------------------------------\n";
    while(1)
    {   customermenu();
        int opt;
        cin>>opt;
        if(opt==5)
            break;

        switch (opt)
        {
            case 1:
                displayList(head_adm);
                cout<<"\n\t\t\t\t\t\tEnter serial number corresponding to the item you want to order : ";
                int n;
                cin>>n;
                cout<<"\t\t\t\t\t\tEnter quantity : ";
                int quantity;
                cin>>quantity;
                head_Cust = order_by_customer(head_Cust, n, quantity);
                break;
            case 2:
                if(head_Cust==NULL)
                {   cout<<"\n\t\t\t\t\t\t\tOrder List is empty\n";
                    break;
                }
                cout<<"\n\t\t\t\t\t\t     ### List of ordered food items ###\n"; 
                displayList(head_Cust);
                break;
            case 3:
                if(head_Cust==NULL){
                cout<<"\n\t\t\t\t\t\t\tYou did not order anything yet \n";
                break;
                }
                if(deleteOrder_bycust())
                {
                    cout<<"\n\t\t\t\t\t\t     This Food Item is Deleted Successfully\n";
                    if(head_Cust==NULL)
                    {
                        cout<<"\nOrdered food item List Become empty";
                        break;
                    }
                    cout<<"\n\t\t\t\t\t\t### Updated list of your ordered food items ###\n";
                    displayList(head_Cust);
                }
                else
                    cout<<"\n\t\t\t\t\t\tFood item with given serial number doesn't exist!!\n";
                break;
            case 4:
                calculatetotsales();
                if(head_Cust==NULL)
                {
                cout<<"\n\t\t\t\t\t\t\tYou did not order anything yet\n";
                break;
                }
                cout<<"\n\t\t\t\t\t\t\t  ----### Final Bill ###----\n";
                displaybill();
                head_Cust = deleteList(head_Cust);
                cout<<"\n\t\t\t\t\t\tPress any key to return to main menu : ";
                fflush(stdin);
                ch=fgetc(stdin);
                flag=1;
                break;
            default:
                cout<<"\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n";
                break;
        }
        if(flag==1)
            break;
    }
}

void mainnenu()
{
    system("Color 0D");
    cout<<"\n                                 **************************************************************************\n";
    cout<<"                                 |                   !WELCOME TO RESTAURANT MANAGEMENT SYSTEM!            |\n";
    cout<<"                                 **************************************************************************\n\n";
    cout<<"\t\t\t\t\t\t\tPRESS 1 TO ENTER IN ADMIN SECTION \n";
    cout<<"\t\t\t\t\t\t\tPRESS 2 TO ENTER IN CUSTOMER SECTION \n";
    cout<<"\t\t\t\t\t\t\tPRESS 3 TO EXIT FROM THIS MENU \n\n";
    cout<<"\t\t\t\t\t\t\tEnter Your Choice ---> ";
}

int main()
{
    head_adm = Add_new_fitem_from_adm(head_adm,1,"Cholai Chat",250);
    head_adm = Add_new_fitem_from_adm(head_adm,2,"Malai Kofta",200);
    head_adm = Add_new_fitem_from_adm(head_adm,3,"Vegan Curry",250);
    head_adm = Add_new_fitem_from_adm(head_adm,4,"Dal  makhni",100);
    head_adm = Add_new_fitem_from_adm(head_adm,5,"Masala Dosa",150);
    while(1)
    {   mainnenu();
        int choice;
        cin>>choice;
        switch (choice)
        {   case 1:
                admin();
                break;
            case 2:
                customer();
                break;
            case 3:
                cout<<"\n\n\t\t\t\t\t\t\t**********!Thank you For Visiting!**********\n";
                return 0;

            default:
                cout<<"\n\t\t\t\t\t\tWrong Input !! PLease choose a valid option\n";
                break;
}}}