#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <stdlib.h>
#include <iomanip>

using namespace std;

struct medList
{
  int medID;
  string medName;
  int medCount;
  double price;
};

// struct transactionDetails
// {
//   int id;
//   int oid;
//   string date;
//   string mop;
//   transactionDetails(int _id, int _oid, string _date, string _mop, string _ps) : id(_id), oid(_oid), date(_date), mop(_mop){};
// };

struct OrderDetails
{
  int orderID;
  int mcount;
  string clientName;
  string paymentStatus;
  double amount;
  string date;
  medList meds[10];
  OrderDetails *nextOrder;

  OrderDetails(int id, string nm, string ps, double amt, string dt, medList medss[10], int mcount)
  {
    orderID = id;
    this->mcount = mcount;
    clientName = nm;
    paymentStatus = ps;
    amount = amt;
    date = dt;
    for (int i = 0; i < 10; i++)
    {
      meds[i] = medss[i];
    }
    nextOrder = nullptr;
  }
};

struct InventoryList
{
  medList medicine;
  InventoryList *next;
  InventoryList(medList m) : medicine(m), next(nullptr){};
};

class medManagement
{
  InventoryList *head;
  OrderDetails *orderHead;

public:
  medManagement() : head(nullptr), orderHead(nullptr){};

  void addMedicine()
  {
    system("CLS");

    bool f = false;

    string medN;
    string _mprice;
    string _mc;

    int medID;
    double medPrice;
    int medC;

    while (!f)
    {
      string _mid;
      medList med;
      cout << "ENTER MEDICINE ID: ";
      getline(cin, _mid);
      istringstream isid(_mid);

      if (isid >> medID)
      {
        cout << "ENTER MEDICINE NAME: ";

        getline(cin, medN);
        cout << "ENTER MEDICINE PRICE: ";

        getline(cin, _mprice);
        istringstream isp(_mprice);

        if (isp >> medPrice)
        {
          cout << "ENTER MEDICINE QUANTITY: ";
          getline(cin, _mc);
          istringstream isc(_mc);

          if (isc >> medC)
          {
            med.medName = medN;
            med.medCount = medC;
            med.medID = medID;
            med.price = medPrice;
            if (head == nullptr)
            {
              head = new InventoryList(med);
            }
            else
            {
              InventoryList *temp = head;
              while (temp->next != nullptr)
              {
                temp = temp->next;
              }
              temp->next = new InventoryList(med);
            }
            f = true;
          }
          else
          {
            cout << "INVALID NO. OF MEDS.." << endl;
            system("PAUSE");
            system("CLS");
          }
        }
        else
        {
          cout << "INVALID PRICE.." << endl;
          system("PAUSE");
          system("CLS");
        }
      }
      else
      {
        cout << "INVALID ID..." << endl;
        system("PAUSE");
        system("CLS");
      }
    }
    if (f)
    {
      cout << "MEDICINE ADDED SUCCESSFULLY..!" << endl;
      system("PAUSE");
    }
  }

  int showInventory()
  {
    system("CLS");
    InventoryList *tempp = head;
    if (tempp == nullptr)
    {
      cout << "No Medicines Available." << endl;
      system("PAUSE");
    }
    else
    {
      int i = 0;
      string opt;
      cout << left << setw(80) << "--------------------------------------------------------------------------------" << endl;
      cout << left << setw(80) << "                           MEDICAL MANAGEMENT SYSTEM                            " << endl;
      cout << left << setw(80) << "--------------------------------------------------------------------------------" << endl;
      cout << left << setw(80) << "| NO.  |   MEDICINE ID   |   MEDICINE NAME   |   PRICE (unit)   |   QUANTITY   |" << endl;
      cout << left << setw(80) << "--------------------------------------------------------------------------------" << endl;
      while (tempp != nullptr)
      {
        ++i;
        cout << left << setw(1) <<"|";
        cout << right << setw(6) << i;
        cout << left << setw(1) << "|";
        cout << right << setw(17) << tempp->medicine.medID;
        cout << left << setw(1) << "|";
        cout << right << setw(19) << tempp->medicine.medName;
        cout << left << setw(1) << "|";
        cout << right << setw(18) << tempp->medicine.price;
        cout << left << setw(1) << "|";
        cout << right << setw(14) << tempp->medicine.medCount;
        cout << left << setw(1) << "|"<<endl;

        tempp = tempp->next;
      }
      cout << left << setw(80) << "--------------------------------------------------------------------------------" << endl;
      cout << right << setw(80) << "|                                                                    BACK[9]   |" << endl;
      cout << left << setw(80) << "--------------------------------------------------------------------------------" << endl;

      do
      {
        cout << endl
             << "SELECT (option): ";
        getline(cin, opt);
        istringstream iss(opt);

        if (iss >> i)
        {
          if (i == 9)
          {
            return 0;
          }
        }
        else
        {
          cout << "retry.." << endl;
        }
      } while (true);
    }
    return 0;
  }

  void inventoryMENU()
  {
    int mo;
    do
    {
      system("CLS");
      cout << endl;

      cout << left << setw(50) << "--------------------------------------------------" << endl;
      cout << left << setw(50) << "|            MEDICAL MANAGEMENT SYSTEM           |" << endl;
      cout << left << setw(50) << "--------------------------------------------------" << endl;
      cout << left << setw(50) << "|                                                |" << endl;
      cout << left << setw(50) << "|    SHOW [1]                      UPDATE [2]    |" << endl;
      cout << left << setw(50) << "|                                                |" << endl;
      cout << left << setw(50) << "|    ADD [3]                                     |" << endl;
      cout << left << setw(50) << "|                                                |" << endl;
      cout << left << setw(50) << "--------------------------------------------------" << endl;
      cout << left << setw(50) << "|                                    BACK [9]    |" << endl;
      cout << left << setw(50) << "--------------------------------------------------" << endl;
      cout << endl
           << "SELECT (option): ";
      string opt;
      getline(cin, opt);
      istringstream iss(opt);
      if (iss >> mo)
      {
        switch (mo)
        {
        case 1:
          this->showInventory();
          cin.ignore();
          break;
        case 2:
          this->updateMed();
          cin.ignore();
          break;
        case 3:
          this->addMedicine();
          cin.ignore();
          break;
        default:
          break;
        }
      }
      else
      {
        cout << "Invalid option. Please enter a valid integer." << endl;
      }
    } while (mo != 9);
  }

  void updateMed()
  {
    system("CLS");
    InventoryList *tempp = head;
    int id;
    string opt;
    cout << "ENTER THE MED-ID : ";
    getline(cin, opt);
    istringstream iss(opt);
    if (iss >> id)
    {
      bool flag = false;
      while (tempp != nullptr)
      {
        if (tempp->medicine.medID == id)
        {
          flag = true;
          int opt;
          do
          {
            system("CLS");
            cout << endl;

            cout << left << setw(50) << "--------------------------------------------------" << endl;
            cout << left << setw(50) << "|            MEDICAL MANAGEMENT SYSTEM           |" << endl;
            cout << left << setw(50) << "--------------------------------------------------" << endl;
            cout << left << setw(50) << "|                                                |" << endl;
            cout << left << setw(50) << "|    NAME [1]                       PRICE [2]    |" << endl;
            cout << left << setw(50) << "|                                                |" << endl;
            cout << left << setw(50) << "|    QUANTITY [3]                                |" << endl;
            cout << left << setw(50) << "|                                                |" << endl;
            cout << left << setw(50) << "--------------------------------------------------" << endl;
            cout << left << setw(50) << "|                                    BACK [9]    |" << endl;
            cout << left << setw(50) << "--------------------------------------------------" << endl;
            cout << endl
                 << "SELECT (option): ";
            cin >> opt;
            switch (opt)
            {
            case 1:
              system("CLS");
              char mn[20];
              cout << "Set Name (" << tempp->medicine.medName << ")"
                   << " : ";
              cin >> mn;
              tempp->medicine.medName = mn;
              system("CLS");
              cout << "Updated Successfully" << endl;
              system("PAUSE");
              break;
            case 2:
              system("CLS");
              double p;
              cout << "Set Price (" << tempp->medicine.medName << ")"
                   << " : ";
              cin >> p;
              tempp->medicine.price = p;
              system("CLS");
              cout << "Updated Successfully" << endl;
              system("PAUSE");
              break;
            case 3:
              system("CLS");
              int q;
              cout << "Set Quantity (" << tempp->medicine.medName << ")"
                   << " : ";
              cin >> q;
              tempp->medicine.medCount = q;
              system("CLS");
              cout << "Updated Successfully" << endl;
              system("PAUSE");
              break;
            default:
              break;
            }
          } while (opt != 9);
          break;
        }
        tempp = tempp->next;
      }
      if (flag)
      {
        system("PAUSE");
      }
      else
      {
        cout << "NO MEDICINES FOUND WITH ID (" << id << ")" << endl;
        system("PAUSE");
      }
    }
    else
    {
      cout << "INVALID INPUT TYPE.." << endl;
      system("PAUSE");
    }
  }
  void orderMENU()
  {
    int mo;
    do
    {
      system("CLS");
      cout << endl;

      cout << left << setw(50) << "--------------------------------------------------" << endl;
      cout << left << setw(50) << "|            MEDICAL MANAGEMENT SYSTEM           |" << endl;
      cout << left << setw(50) << "--------------------------------------------------" << endl;
      cout << left << setw(50) << "|                                                |" << endl;
      cout << left << setw(50) << "|    SHOW ORDERS [1]         DELETE ORDER [2]    |" << endl;
      cout << left << setw(50) << "|                                                |" << endl;
      cout << left << setw(50) << "|    PLACE ORDER [3]         MAKE PAYMENT [4]    |" << endl;
      cout << left << setw(50) << "|                                                |" << endl;
      cout << left << setw(50) << "--------------------------------------------------" << endl;
      cout << left << setw(50) << "|                                    BACK [9]    |" << endl;
      cout << left << setw(50) << "--------------------------------------------------" << endl;
      cout << endl
           << "SELECT (option): ";
      cin >> mo;

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
      case 4:
        this->orderById();
      default:
        break;
      }
    } while (mo != 9);
  }

  int newOrder()
  {
    system("CLS");
    InventoryList *temp = head;
    int id = 1;
    string nm;
    double amt = 0;
    char date[30];
    medList meds[10];
    int mcount;
    time_t cd = time(nullptr);
    tm *dt = localtime(&cd);
    strftime(date, sizeof(date), "%d/%m/%Y %H:%M:%S", dt);

    cout << "ENTER CLIENT NAME: " << endl;
    cin.ignore();
    getline(cin, nm);
    cout << "NO. OF MEDICINES TO BE ORDERED: ";
    cin >> mcount;

    for (int i = 0; i < mcount; i++)
    {
      int mid;
      int mc;
      cout << "MED ID: ";
      cin >> mid;
      if (temp == nullptr)
      {
        cout << "NO MEDICINES AVAILABLE.." << endl;
        system("PAUSE");
      }
      else
      {
        bool flag = false;
        while (temp != nullptr)
        {
          if (temp->medicine.medID == mid)
          {
            cout << "ENTER QUANTITY (" << temp->medicine.medName << ") : ";
            cin >> mc;
            if (temp->medicine.medCount >= mc)
            {
              amt = amt + (temp->medicine.price * mc);
              meds[i].medCount = mc;
              meds[i].price = temp->medicine.price;
              meds[i].medID = temp->medicine.medID;
              temp->medicine.medCount = temp->medicine.medCount - mc;
              meds[i].medName = temp->medicine.medName;
              flag = true;
            }
            else
            {
              cout << "ORDERED QUANTITY IS ABOVE STOCK AVAILABLE" << endl;
              system("PAUSE");
              return 0;
            }
            break;
          }
          else
          {
            temp = temp->next;
          }
        }
        if (!flag)
        {
          return 0;
        }
      }
    }

    char pss[20];
    strcpy(pss, "PENDING");

    if (orderHead == nullptr)
    {
      orderHead = new OrderDetails(id, nm, pss, amt, date, meds, mcount);
      cout << "Order Received" << endl;
    }
    else
    {
      OrderDetails *otemp = this->orderHead;
      while (otemp->nextOrder != nullptr)
      {
        otemp = otemp->nextOrder;
      }
      id = otemp->orderID + 1;
      otemp->nextOrder = new OrderDetails(id, nm, pss, amt, date, meds, mcount);
      cout << "Order Received" << endl;
    }

    return 0;
  }

  int showOrders()
  {
    system("CLS");
    OrderDetails *otempp = this->orderHead;
    int i = 1;

    if (orderHead == nullptr)
    {
      cout << "No Orders." << endl;
      system("PAUSE");
    }
    else
    {
      cout << left << setw(120) << "------------------------------------------------------------------------------------------------------------------------" << endl;
      cout << left << setw(1) << "|";
      cout << left << setw(9) << "   NO.   ";
      cout << left << setw(1) << "|";

      cout << left << setw(19) << "      ORDER ID     ";
      cout << left << setw(1) << "|";

      cout << left << setw(30) << "          CLIENT NAME         ";
      cout << right << setw(1) << "|";

      cout << left << setw(24) << "          DATE";
      cout << right << setw(1) << "|";

      cout << left << setw(19) << "    ORDER VALUE    ";
      cout << right << setw(1) << "|";

      cout << left << setw(12) << "   STATUS   ";
      cout << right << setw(1) << "|" << endl;
      cout << left << setw(120) << "------------------------------------------------------------------------------------------------------------------------" << endl;

      while (otempp != nullptr)
      {
        cout << left << setw(1) << "|";
        cout << right << setw(9) << i;
        cout << left << setw(1) << "|";

        cout << right << setw(19) << otempp->orderID;
        cout << left << setw(1) << "|";

        cout << right << setw(30) << otempp->clientName;
        cout << right << setw(1) << "|";

        cout << right << setw(24) << otempp->date;
        cout << right << setw(1) << "|";

        cout << right << setw(19) << otempp->amount;
        cout << right << setw(1) << "|";

        cout << right << setw(12) << otempp->paymentStatus;
        cout << right << setw(1) << "|" << endl;

        cout << left << setw(120) << "------------------------------------------------------------------------------------------------------------------------" << endl;

        i = i + 1;

        otempp = otempp->nextOrder;
      }
      system("PAUSE");
    }

    return 0;
  }

  int deleteOrder()
  {
    system("CLS");
    OrderDetails *deltemp = orderHead;
    OrderDetails *prev;
    string _oid;
    int oid;
    cin.ignore();
    cout << "ENTER THE ORDER-ID: ";
    getline(cin, _oid);
    istringstream iss(_oid);

    if (iss >> oid)
    {
      if (deltemp == nullptr)
      {
        cout << "No orders." << endl;
        system("PAUSE");
      }
      else
      {
        while (deltemp != nullptr)
        {
          if (deltemp->orderID == oid)
          {
            break;
          }
          prev = deltemp;
          deltemp = deltemp->nextOrder;
        }
        prev->nextOrder = deltemp->nextOrder;
        cout << "Order deleted successfully .!" << endl;
      }
    }
    else
    {
      cout << "INVALID INPUT TYPE.." << endl;
      system("PAUSE");
    }
    return 0;
  }

  void orderById()
  {
    system("CLS");
    OrderDetails *otempp = this->orderHead;

    int _id;
    cout << "ENTER ORDER-ID: ";
    cin >> _id;

    if (orderHead == nullptr)
    {
      cout << "No Orders." << endl;
      system("PAUSE");
    }
    else
    {
      while (otempp != nullptr)
      {
        if (otempp->orderID == _id)
        {
          double ta = 0;

          cout << right << setw(80) << "--------------------------" << endl;
          cout << right << setw(55) << "|";
          cout << left << setw(11) << " ORDER ID: ";
          cout << left << setw(11) << otempp->orderID;
          cout << right << setw(3) << "|" << endl;
          cout << right << setw(80) << "--------------------------" << endl;

          cout << left << setw(13) << "CLIENT NAME: ";
          cout << left << setw(67) << otempp->clientName << endl;
          cout << left << setw(16) << "PAYMENT STATUS: ";
          cout << left << setw(64) << otempp->paymentStatus << endl;
          cout << endl;

          cout << left << setw(80) << "--------------------------------------------------------------------------------" << endl;

          cout << left << setw(1) << "|";
          cout << left << setw(5) << " NO. ";
          cout << left << setw(1) << "|";

          cout << left << setw(25) << "      MEDICINE NAME      ";
          cout << left << setw(1) << "|";

          cout << left << setw(14) << "   QUANTITY   ";
          cout << right << setw(1) << "|";

          cout << left << setw(16) << "  PRICE (UNIT)  ";
          cout << right << setw(1) << "|";

          cout << left << setw(14) << "     AMT.     ";
          cout << right << setw(1) << "|" << endl;

          cout << left << setw(80) << "--------------------------------------------------------------------------------" << endl;

          for (int i = 0; i < otempp->mcount; i++)
          {

            cout << left << setw(1) << "|";
            cout << right << setw(5) << i + 1;
            cout << left << setw(1) << "|";

            cout << right << setw(25) << otempp->meds[i].medName;
            cout << left << setw(1) << "|";

            cout << right << setw(14) << otempp->meds[i].medCount;
            cout << right << setw(1) << "|";

            cout << right << setw(16) << otempp->meds[i].price;
            cout << right << setw(1) << "|";

            cout << right << setw(14) << otempp->meds[i].price * otempp->meds[i].medCount;
            cout << right << setw(1) << "|" << endl;

            ta = ta + (otempp->meds[i].price * otempp->meds[i].medCount);
          }

          cout << left << setw(80) << "--------------------------------------------------------------------------------" << endl;
          cout << right << setw(64) << "TOTAL PAYABLE: ";
          cout << right << setw(15) << ta;
          cout << right << setw(1) << " " << endl;
          cout << left << setw(80) << "--------------------------------------------------------------------------------" << endl;
          cout << left << setw(80) << " CHANGE STATUS: PAID [7] PENDING [8]                                 BACK [9]   " << endl;
          cout << left << setw(80) << "--------------------------------------------------------------------------------" << endl;

          int o;
          cout << "ENTER [OPTION] :";
          cin >> o;

          if (o == 7)
          {
            otempp->paymentStatus = "PAID";
            cout << "PAID SUCCESSFULLY ..!" << endl;
            system("PAUSE");
          }
          else if (o == 8)
          {
            cout << "PAYMENT UPDATED SUCCESSFULLY ..!" << endl;
            system("PAUSE");
          }
        }

        otempp = otempp->nextOrder;
      }
    }
  }
};

int main()
{
  medManagement mm;
  int op;

  do
  {
    system("CLS");
    cout << endl
         << endl;
    cout << left << setw(50) << "--------------------------------------------------" << endl;
    cout << left << setw(50) << "|            MEDICAL MANAGEMENT SYSTEM           |" << endl;
    cout << left << setw(50) << "--------------------------------------------------" << endl;
    cout << left << setw(50) << "|                                                |" << endl;
    cout << left << setw(50) << "|                                                |" << endl;
    cout << left << setw(50) << "|    INVENTORY [1]                 ORDERS [2]    |" << endl;
    cout << left << setw(50) << "|                                                |" << endl;
    cout << left << setw(50) << "|                                                |" << endl;
    cout << left << setw(50) << "--------------------------------------------------" << endl;
    cout << left << setw(50) << "|                                    EXIT [9]    |" << endl;
    cout << left << setw(50) << "--------------------------------------------------" << endl;
    cout << endl
         << "SELECT (option): ";

    string opt;
    getline(cin, opt);
    istringstream iss(opt);

    if (iss >> op)
    {
      switch (op)
      {
      case 1:
        mm.inventoryMENU();
        op = 0;
        cin.ignore();
        break;
      case 2:
        mm.orderMENU();
        op = 0;
        cin.ignore();
        break;
      default:
        break;
      }
    }
  } while (op != 9);
  return 0;
}
