#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;

struct medList
{
  int medID;
  char medName[20];
  int medCount;
  double price;
};

struct OrderDetails
{
  int orderID;
  int mcount;
  char clientName[20];
  char paymentStatus[20];
  double amount;
  medList meds[10];
  OrderDetails *nextOrder;

  OrderDetails(int id,char nm[20],char ps[20],double amt,medList medss[10],int mcount){
    orderID = id;
    this->mcount = mcount;
    strcpy(clientName,nm);
    strcpy(paymentStatus,ps);
    amount = amt;
    for (int i = 0; i<10; i++){
      meds[i] = medss[i];
    }
    nextOrder = nullptr;
  }
} *orderHead;

struct InventoryList {
  medList medicine;
  InventoryList *next;

  InventoryList(medList m): medicine(m), next(nullptr){};

};

class Inventory {
  InventoryList *head;
  OrderDetails *orderHead = nullptr;
  public:
  Inventory():head(nullptr){};

  void addMedicine() {
    system("CLS");
    InventoryList *newMed;
    char medN[20];
    int medID;
    double medPrice;
    int medC;


    medList med;
    cout<<"ENTER MED ID: ";
    cin>>medID;
    cout<<"ENTER MED NAME: ";
    cin>>medN;
    cout<<"ENTER MED PRICE: ";
    cin>>medPrice;
    cout<<"ENTER MED QUANTITY: ";
    cin>>medC;

    med.medID = medID;
    strcpy(med.medName,medN);
    med.price = medPrice;
    med.medCount = medC;

    newMed = new InventoryList(med);

    if (head == nullptr) {
      head = newMed;
    }
    else {
      InventoryList *temp = head;
      while (temp->next != nullptr) {
        temp = temp->next;
      }
      temp->next = newMed;
    }
  }

  void showInventory() {
    system("CLS");
    InventoryList *tempp = head;
    if ( tempp == nullptr)
    {
      cout<<"No Medicines Available."<<endl;
      system("PAUSE");
    }
    else{
        cout<<left<<setw(10)<<"ID"<<left<<setw(15)<<"NAME"<<left<<setw(10)<<"QUANTITY"<<left<<setw(10)<<"PRICE(unit)"<<endl;
      while (tempp != nullptr) {

        cout<<left<<setw(10)<<tempp->medicine.medID<<left<<setw(15)<<tempp->medicine.medName<<left<<setw(10)<<tempp->medicine.medCount<<left<<setw(10)<<tempp->medicine.price<<endl;

        tempp = tempp->next;
      }
      system("PAUSE");
    }
  }

  void inventoryMENU() {
    int mo;
    do {
      system("CLS");
      cout<<"1. SHOW INVENTORY"<<endl;
      cout<<"2. UPDATE MED DETAILS"<<endl;
      cout<<"3. ADD MED"<<endl;
      cout<<"SELECT (option): ";
      cin>>mo;

      switch (mo)
      {
      case 1:
        this->showInventory();
        break;
      case 2:
        this->updateMed();
        break;
      case 3:
        this->addMedicine();
        break;
      default:
        break;
      }
    } while (mo != 9);
  }

  void updateMed() {
    system("CLS");
    InventoryList *tempp = head;
    int id;
    cout<<"ENTER THE MED-ID : ";
    cin>>id;
    bool flag = false;
    while (tempp != nullptr) {
      if (tempp->medicine.medID == id) {
        flag = true;
        int opt;
        do {
          system("CLS");
          cout<<"1. Update MedName"<<endl;
          cout<<"2. Update Price"<<endl;
          cout<<"3. Update Quantity"<<endl;
          cout<<endl;
          cout<<"PRESS '9' (BACK)"<<endl;
          cout<<endl;
          cout<<"Enter your choice: ";
          cin>>opt;
          switch (opt) {
            case 1:
              system("CLS");
              char mn[20];
              cout<<"Set Name ("<<tempp->medicine.medName<<")"<<" : ";
              cin>>mn;
              strcpy(tempp->medicine.medName,mn);
              system("CLS");
              cout<<"Updated Successfully"<<endl;
              system("PAUSE");
              break;
            case 2:
              system("CLS");
              double p;
              cout<<"Set Price ("<<tempp->medicine.medName<<")"<<" : ";
              cin>>p;
              tempp->medicine.price = p;
              system("CLS");
              cout<<"Updated Successfully"<<endl;
              system("PAUSE");
              break;
            case 3:
              system("CLS");  
              int q;
              cout<<"Set Quantity ("<<tempp->medicine.medName<<")"<<" : ";
              cin>>q;
              tempp->medicine.medCount = q;
              system("CLS");
              cout<<"Updated Successfully"<<endl;
              system("PAUSE");
              break;
            default:
              break;
          }
        } while(opt != 9);
        break;
      }
      tempp = tempp->next;
    }
    if (flag) {
      system("PAUSE");
    }
    else {
      cout<<"NO MEDICINES FOUND WITH ID ("<<id<<")"<<endl;
      system("PAUSE");
    }
  }
  void orderMENU() {
    int mo;
    do {
      system("CLS");
      cout<<"1. SHOW ORDERS"<<endl;
      cout<<"2. UPDATE ORDER DETAILS"<<endl;
      cout<<"3. NEW ORDER"<<endl;
      cout<<"SELECT (option): ";
      cin>>mo;

      switch (mo)
      {
      case 1:
        this->showOrders();
        break;
      case 2:
        this->deleteOrder();
        break;
      case 3:
        this->newOrder();
        break;
      default:
        break;
      }
    } while (mo != 9);
  }

  int newOrder(){
    system("CLS");
    InventoryList *temp = head;
    int id;char nm[20];char ps[20];double amt = 0;medList meds[10];int mcount;

    cout<<"ENTER CLIENT NAME: ";
    cin>>nm;
    cout<<"NO. OF MEDICINES TO BE ORDERED: ";
    cin>>mcount;

    for (int i = 0; i< mcount; i++) {
      int mid;
      int mc;
      cout<<"MED ID: ";
      cin>>mid;
      if (temp == nullptr) {
        cout<<"NO MEDICINES AVAILABLE.."<<endl;
        system("PAUSE");
      }
      else {
        bool flag = false;
        while (temp != nullptr) {
          if (temp->medicine.medID == mid) {
            cout<<"ENTER QUANTITY ("<<temp->medicine.medName<<") : ";
            cin>>mc;
            if (temp->medicine.medCount >= mc) {
              amt = amt + (temp->medicine.price * mc);
              meds[i].medCount = mc;
              meds[i].price = temp->medicine.price;
              meds[i].medID = temp->medicine.medID;
              temp->medicine.medCount = temp->medicine.medCount - mc;
              strcpy(meds[i].medName, temp->medicine.medName);
              flag = true;
            }
            else {
              cout<<"ORDERED QUANTITY IS ABOVE STOCK AVAILABLE"<<endl;
              system("PAUSE");
              return 0;
            }
            break;
          }
          else {
            temp = temp->next;
          }
        }
        if (!flag) {
          return 0;
        }
      }
    }

    OrderDetails *new_order;
    char nmm[20];
    char pss[20];
    strcpy(nmm,nm);
    strcpy(pss,"PENDING");

    if (orderHead == nullptr) {
      id = 1;
      new_order = new OrderDetails(id,nmm,pss,amt,meds,mcount);
      orderHead = new_order;
      cout<<"Order Received"<<endl;
    }
    else {   
      OrderDetails *otemp = this->orderHead;
      int prevID;
      while (otemp->nextOrder != nullptr) {
        otemp = otemp->nextOrder;
        prevID = otemp->orderID;
      }
      id = prevID;
      new_order = new OrderDetails(id,nmm,pss,amt,meds,mcount);
      otemp->nextOrder = new_order;
      cout<<"Order Received"<<endl;
    }

    return 0;
  }

  int showOrders() {
    system("CLS");
    OrderDetails *otempp = this->orderHead;

    if (orderHead == nullptr) {
      cout<<"No Orders."<<endl;
      system("PAUSE");
    }
    else{
      while (otempp != nullptr) { 
        cout<<"ORDER ID: "<<otempp->orderID<<endl;
        cout<<"CLIENT NAME: "<<otempp->clientName<<endl;
        cout<<"PAYMENT STATUS: "<<otempp->paymentStatus<<endl;
        cout<<left<<setw(15)<<"MED NAME"<<left<<setw(10)<<"QUANTITY"<<left<<setw(10)<<"PRICE"<<endl;
        for (int i = 0; i < otempp->mcount; i++){
          cout<<left<<setw(15)<<otempp->meds[i].medName<<left<<setw(10)<<otempp->meds[i].medCount<<left<<setw(10)<<otempp->meds[i].price<<endl;
        }
        cout<<"___________________________________________"<<endl;
        cout<<right<<setw(40)<<"TOTAL PAYABLE: "<<otempp->amount<<endl;
        otempp = otempp->nextOrder;
      }
      system("PAUSE");
    }

    return 0;
  }

  int deleteOrder() {
    system("CLS");
    OrderDetails *deltemp = orderHead;
    OrderDetails *prev;
    int oid;

    cout<<"ENTER THE ORDER-ID: ";
    cin>>oid;

    if (deltemp == nullptr) {
      cout<<"No orders."<<endl;
    }
    else {
      while (deltemp != nullptr) {
        if (deltemp->orderID == oid) {
          break;
        }
        prev = deltemp;
        deltemp = deltemp->nextOrder;
      }
      prev->nextOrder = deltemp->nextOrder;
    }
    return 0;
  }
};

int main()
{
  Inventory inv;
  int op;

  do {
    system("CLS");
    cout<<"1. INVENTORY"<<endl;
    cout<<"2. ORDERS"<<endl;
    cout<<"3. LOGOUT"<<endl;

    cout<<"SELECT (option): ";
    cin>>op;

    switch (op)
    {
    case 1:
      inv.inventoryMENU();
      break;
    case 2:
      inv.orderMENU();
      break;
    case 3:
      op = 9;
      break;
    default:
      break;
    }
  } while(op != 9);
  return 0;
}



