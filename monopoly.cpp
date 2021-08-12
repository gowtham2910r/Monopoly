#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include<conio.h>
#include<windows.h>
#include<stdio.h>
using namespace std;
double screenwidth = GetSystemMetrics(SM_CXSCREEN);
double screenheight = GetSystemMetrics(SM_CYSCREEN);
double sw,sh;
void bg(){
    setcolor(GREEN);
    setfillstyle(SOLID_FILL,GREEN);
    rectangle(0,0,screenwidth*(60.0/100.0),screenheight);
    floodfill(1,1,GREEN);
    setcolor(YELLOW);
    sw = ((screenwidth*60.0/100.0) - 650.0)/2.0;
    sh = (screenheight - 650.0)/2.0;
    rectangle(sw,sh,sw+100,sh+100);
    rectangle(sw + 550,sh,sw+650,sh+100);
    rectangle(sw,sh+550,sw+100,sh+650);
    rectangle(sw+550,sh+550,sw+650,sh+650);
    for(int i=0;i<450;i += 50){
        rectangle(sw + 100 + i,sh,sw + 150 + i,sh+100);
        rectangle(sw,sh + 100 + i,sw+100,sh+150+i);
        rectangle(sw+550,sh + 100 + i,sw+650,sh + 150 + i);
        rectangle(sw + 100+i,sh + 550,sw + 150 + i,sh + 650);
    }
    line(sw+100,sh+200,sw+200,sh+100);
    line(sw+200,sh+100,sw+300,sh+200);
    line(sw+200,sh+300,sw+300,sh+200);
    line(sw+100,sh+200,sw+200,sh+300);
    line(sw+450,sh+550,sw+550,sh+450);
    line(sw+450,sh+350,sw+550,sh+450);
    line(sw+350,sh+450,sw+450,sh+350);
    line(sw+450,sh+550,sw+350,sh+450);
    int a[2];
    a[0] = 4;
    a[1] = 1;
    setcolor(a[0]);
    setfillstyle(SOLID_FILL,a[0]);
    circle(sw+590,sh+563,8);
    floodfill(sw+590,sh+563,a[0]);
    setcolor(BLUE);
    setfillstyle(SOLID_FILL,BLUE);
    circle(sw+610,sh+563,8);
    floodfill(sw+610,sh+563,BLUE);
    setbkcolor(2);
    setcolor(YELLOW);
    settextstyle(0,0,3);
    moveto(sw+250,sh-30);
    outtext("MONOPOLY");
    settextstyle(0,0,2);
    moveto(sw+410,sh+440);
    outtext("Choice");
    moveto(sw+160,sh+190);
    outtext("Choice");
}
class Location{
      protected:
      int card_val;
      int type;
      int owner;
      string name;
      public:
      Location(int l){
            card_val = l;
            type=0;
            name="";
            owner = 0;
      }
      Location(Location& l){
            card_val = l.card_val;
            type = l.type;
            name = l.name;
            owner = l.owner;
      }
      virtual void addBuilding(){};
      virtual int getRent(){};
      virtual int getRent(int){};
      virtual int getRent(int,int,int){};
      virtual void read(){};
      virtual void setMortStatus(bool){};
      virtual int getBuildings(){};
      virtual bool getMortStatus(){};
      int getOwner(){
            return owner;
      }
      string getName(){
            return name;
      }
      virtual int getAmount(){};
      virtual int getMortgage(){};
      void setOwner(int o){
            owner = o;
      }
      int getValue(){
            return card_val;
      }
      int getType(){
            return type;
      }

};
class City:public Location{
      protected:
            int amount,mortgage_val, r0, r1, r2, r3, r4, rh, nb;
            bool mort;
      public:
            City(int l):Location(l){
                  type = 1;
                  amount=0;
                  mortgage_val=0;
                  r0=0;
                  r1=0;
                  r2=0;
                  r3=0;
                  r4=0;
                  rh=0;
                  nb=0;
                  mort=false;
            }
            int getBuildings(){
                  return nb;
            }
            void addBuilding(){
                  nb++;
            }
            void read();
            int getRent();
            int getAmount(){
                  return amount;
            }
            int getMortgage(){
                  return mortgage_val;
            }
            void setMortStatus(bool status){
                  mort=status;
            }
            bool getMortStatus(){
                  return mort;
            }
};
class Railway:public Location{
      protected:
      int amount,mortgage_val;
      bool mort;
      public:
      Railway(int l):Location(l){
            type = 3;
            amount = 200;
            mortgage_val = 100;
            mort=false;
      }
      void storeRailway();
      int getRent(int nr){
            return 50*nr;
      }
      void read();
      int getAmount(){
            return amount;
      }
      void setMortStatus(bool status){
            mort=status;
      }
      bool getMortStatus(){
            return mort;
      }
      int getMortgage(){
            return mortgage_val;
      }
};
class Utility:public Location{
      protected:
      int amount,mortgage_val;
      bool mort;
      public:
      Utility(int l):Location(l){
            type=2;
            amount = 150;
            mortgage_val = 75;
      }
      int getAmount(){
            return amount;
      }
      void setMortStatus(bool status){
            mort=status;
      }
      bool getMortStatus(){
            return mort;
      }
      int getRent(int n1,int n2, int nu){
            return (n1+n2)*50*nu;
      }
      void storeUtility();
      void read();
};
void Utility::read(){
      static int count = 0;
      string arr[] = {"Electric Company","Water Works"};
      name = arr[count];
      count++;
}
void Railway::read(){
      static int count = 0;
      string arr[] = {"Kingscross Statation","Marylebone Station","Liverpool Station","Frenchurch Street Station"};
      name = arr[count];
      count++;
}
void City::read(){
      static int count = 0;

      string arr[] = {"Old Kent Road","Whitechapel Road","The Angel Islington","Euston Road","Pentoville Road","Pall Mall","Whitehall",
      "Northumberland Avenue","Bow Street","Marlborough Street","Vine Street","Strand","Fleet Street","Trafalgar Square","Leicester Street","Coventry Street",
      "Picadilly","Regent Street","Oxford Street","Bond Street","Park Lane","Mayfair"};

      string col[] = {"Brown","Brown","Light Blue","Light Blue","Light Blue","Pink","Pink","Pink","Orange","Orange","Orange","Red","Red","Red","Yellow","Yellow"
      ,"Yellow","Green","Green","Green","Dark Blue","Dark Blue"};

      int amt[] = {60,60,100,100,120,140,140,160,180,180,200,220,220,240,260,260,280,300,300,320,350,400};
      int rent[] = {2,4,6,6,8,10,10,12,14,14,16,18,18,20,22,22,24,26,26,28,35,50};
      int rent1[] = {10,20,30,30,40,50,50,60,70,70,80,90,90,100,110,110,120,130,130,150,175,200};
      int rent2[] = {30,60,90,90,100,150,150,180,200,200,220,250,250,300,330,330,360,390,390,450,500,600};
      int rent3[] = {90,180,270,270,300,450,450,500,550,550,600,700,700,750,800,800,850,900,900,1000,1100,1400};
      int rent4[] = {160,320,400,400,450,625,625,700,750,750,800,875,875,925,975,975,1025,1100,1100,1200,1300,1700};
      int renth[] = {250,450,550,550,600,750,750,900,950,950,1000,1050,1050,1100,1150,1150,1200,1275,1275,1400,1500,2000};
      int mv[] = {30,30,50,50,60,70,70,80,90,90,100,110,110,120,130,130,140,150,150,160,175,200};

      name = arr[count];
      amount = amt[count];
      r0 = rent[count];
      r1 = rent1[count];
      r2 = rent2[count];
      r3 = rent3[count];
      r4 = rent4[count];
      rh = renth[count];
      mortgage_val = mv[count];
      count++;

}
int City::getRent(){
      if(nb==0)
            return r0;
      else if(nb==1)
            return r1;
      else if(nb==2)
            return r2;
      else if(nb==3)
            return r3;
      else if(nb==4)
            return r4;
      else
            return rh;
}
int getHouseRent(int val){
      if(val<10)
            return 50;
      else if(val<20)
            return 100;
      else if(val<30)
            return 150;
      else
            return 200;
}
int check_pos(int pos){
      if(pos%10==0)
            return 1;
      else if(pos==2 || pos==7 || pos==17 || pos==22 || pos==33 || pos==36)
            return 2;
      else if(pos == 4 || pos==38)
            return 3;
      else if(pos==12 || pos==28)
            return 4;
      else if(pos%5==0)
            return 5;
      else
            return 6;
}
class Player{
      protected:
            double balance;
            Location** locations_owned;
            int cur_pos , jail_status;
            int num_loc , num_rail , num_util;
      public:
            Player(){
                  balance = 2000;
                  locations_owned=NULL;
                  cur_pos=0;
                  num_loc=0;
                  jail_status=0;
                  locations_owned = new Location*[30];
                  num_rail=0;
                  num_util=0;
            }
            double getBalance(){
                  return balance;
            }
            void operator+(int amount){
                  balance+=amount;
            }
            void operator-(int amount){
                  balance-=amount;
            }
            int getPosition(){
                  return cur_pos;
            }
            void setPosition(int pos){
                  cur_pos=pos;
            }
            void addLocation(Location* l){
                  locations_owned[num_loc] = l;
                  num_loc++;
                  if(l->getType()==3){
                        num_rail++;
                  }
                  if(l->getType()==2){
                        num_util++;
                  }
            }
            void getLocations(){
                  cout<<"The locations you own now are:\n";
                  for(int i=0;i<num_loc;i++){
                        cout<<(i+1)<<" - "<<locations_owned[i]->getName()<<"\n";
                  }
            }
            void getMortgages(){
                  for(int i=0;i<num_loc;i++){
                        if(!locations_owned[i]->getMortStatus())
                              cout<<(i+1)<<locations_owned[i]->getName()<<" - "<<locations_owned[i]->getMortgage()<<"\n";
                  }
            }
            void mortgage(int i){
                  locations_owned[i]->setMortStatus(true);
            }
            int sell(int i){
                  locations_owned[i]->setOwner(0);
                  int b,hr;
                  int val = locations_owned[i]->getValue();
                  if(check_pos(val)==6){
                        b = locations_owned[i]->getBuildings();
                        hr = getHouseRent(i);
                  }
                  int amt = locations_owned[i]->getAmount();
                  amt += hr*b;
                  if(locations_owned[i]->getMortStatus()){
                        amt-=locations_owned[i]->getMortgage();
                        locations_owned[i]->setMortStatus(false);
                        cout<<"Since the property was mortgaged, you have paid "<<locations_owned[i]->getMortgage()<<" to unmortgage.\n";
                  }
                  for(int j=i;i<num_loc-1;i++){
                        locations_owned[i]=locations_owned[i+1];
                  }
                  locations_owned[i]=NULL;
                  num_loc--;
                  return amt;
            }
            int getNumLoc(){
                  return num_loc;
            }
            int getNumRail(){
                  return num_rail;
            }
            int getNumUtil(){
                  return num_util;
            }
            int getJailStatus(){
                  return jail_status;
            }
            void setJailStatus(int j){
                  jail_status=j;
            }
};
int roll(){
      int  n = (rand()%6)+1;
      return n;
}
int storeCardData(Location** arr){
      for(int i=0;i<40;i++){
            if(i%10==0)
                  continue;
            if(i%5==0){
                  Railway* rail = new Railway(i);
                  arr[i]=rail;
            }
            else if(i==4 || i==38){
                  continue;
            }
            else if(i==2 || i==7 || i==17 || i==22 || i==33 || i==36){
                  continue;
            }
            else if(i==12 || i==28){
                 Utility* utility = new Utility(i);
                 arr[i]=utility;
            }
            else{
                  City* city = new City(i);
                  arr[i]=city;
            }
            arr[i]->read();
      }
}
bool moneyShort(Player* player){
      cout<<"Not enough money\n";
      cout<<"Would you like to do one of the following\n";
      cout<<"1 - Mortgage\n";
      cout<<"2 - Sell Building\n";
      cout<<"3 - Sell Location(if any buildings, also sold)\n";
      cout<<"4 - Cancel\n";
      int temp;
      cin>>temp;
      switch(temp){
            case 1:
            {
                  player->getMortgages();
                  int m;
                  cin>>m;
                  player->mortgage(m-1);
                  cout<<"Property successfully mortgaged\n";
                  break;
            }
            case 2:
            {

            }
            case 3:
            {
                  player->getLocations();
                  int s;
                  cin>>s;
                  int amt = player->sell(s-1);
                  player+amt;
                  cout<<"Property sold successfully\n You earned "<<amt<<endl;
                  break;
            }
            case 4:return false;
      }
      return true;
}
bool checkGameStatus(Player* player){
      if(player->getNumLoc()==0){
            return true;
      }
      else{
            return false;
      }
}
void goToJail(Player* player, int& new_position, int co){
      cout<<"Go to Jail\n1 - Pay fifty to stay here\n2 - Skip three turns in Jail(no rent)\n";
                        int opt;
                        cin>>opt;
                        if(opt==1){
                              l6:
                              if(player->getBalance()<50){
                                    bool check = moneyShort(player);
                                    if(!check){
                                          cout<<"Jail escape cancelled. Go to Jail\n";
                                          player->setPosition(10);
                                          new_position=10;
                                    }
                                    else{
                                          goto l6;
                                    }
                              }
                              else{
                                    player-50;
                                    cout<<"You spent 50 and you are out of jail\nYour position hasn't changed\n";
                              }
                        }
                        else if(opt==2){
                              int i = 0,color = 4;
                              if(co == 2){
                                    i = 20;
                                    color = 1;
                              }
                              if(new_position == 30){
                                  setcolor(2);
                                  setfillstyle(SOLID_FILL,2);
                                  circle(sw+590 +i,sh+13,8);
                                  floodfill(sw+590 + i,sh+13,2);
                              }
                              else if(new_position == 33){
                                    setcolor(2);
                                    setfillstyle(SOLID_FILL,2);
                                    circle(sw+590 + i,sh+563-7*50,8);
                                    floodfill(sw+590 +i,sh+563-7*50,2);
                              }
                              player->setPosition(10);
                              new_position=10;
                              setcolor(color);
                              setfillstyle(SOLID_FILL,color);
                              circle(sw+40+i,sh+563,8);
                              floodfill(sw+40+i,sh+563,color);
                              cout<<"You are in jail\n";
                              player->setJailStatus(1);

                        }

                        else{
                              cout<<"Invalid Option\n";
                              goto l6;
                        }
}
int main(){
      srand(time(0));
      Player player1,player2;
      Location** board= new Location*[40];
      for(int i=0;i<40;i++){
            Location* c = new Location(i);
            board[i]= c;
      }
      storeCardData(board);
      int current_player=1;
      int game_status = 1;
      Player* player;
      Player* opponent;
      initwindow(screenwidth/100.0*60.0,screenheight,"");
      bg();

      while(game_status==1){
            int n1 = roll();
            int n2 = roll();
            int steps = n1+n2;
            if(current_player==1){
                   player = &player1;
                   opponent = &player2;
                   if(player->getPosition() == 0){
                            setcolor(2);
                            setfillstyle(SOLID_FILL,2);
                            circle(sw+590,sh+563,8);
                            floodfill(sw+590,sh+563,2);
                   }
                   else{
                            int cur = 9-player->getPosition();
                            setcolor(2);
                            setfillstyle(SOLID_FILL,2);
                            circle(sw+110+cur*50,sh+563,8);
                            floodfill(sw+110+cur*50,sh+563,2);
                   }
                   if((player->getPosition()+steps)%40 >= 0 && (player->getPosition()+steps)%40 <= 9){
                        if((player->getPosition()+steps)%40 == 0){
                            setcolor(4);
                            setfillstyle(SOLID_FILL,4);
                            circle(sw+590,sh+563,8);
                            floodfill(sw+590,sh+563,4);
                        }
                        else{
                            int cur = 9 - (player->getPosition() + steps)%40;
                            setcolor(4);
                            setfillstyle(SOLID_FILL,4);
                            circle(sw+110+cur*50,sh+563,8);
                            floodfill(sw+110+cur*50,sh+563,4);
                        }
                   }
                   if(player->getPosition()+steps >= 10 && player->getPosition()+steps <= 19){
                        if(player->getPosition()+steps == 10){
                            setcolor(4);
                            setfillstyle(SOLID_FILL,4);
                            circle(sw+40,sh+563,8);
                            floodfill(sw+40,sh+563,4);
                        }
                        else{
                            int cur =  player->getPosition() + steps - 10;
                            setcolor(4);
                            setfillstyle(SOLID_FILL,4);
                            circle(sw+40,sh+563-cur*50,8);
                            floodfill(sw+40,sh+563-cur*50,4);
                        }
                   }
                   if(player->getPosition() >= 10 && player->getPosition() <= 19){
                        if(player->getPosition() == 10){
                            setcolor(2);
                            setfillstyle(SOLID_FILL,2);
                            circle(sw+40,sh+563,8);
                            floodfill(sw+40,sh+563,2);
                        }
                        else{
                            int cur =  player->getPosition() - 10;
                            setcolor(2);
                            setfillstyle(SOLID_FILL,2);
                            circle(sw+40,sh+563-cur*50,8);
                            floodfill(sw+40,sh+563-cur*50,2);
                        }
                   }
                   if(player->getPosition() >= 20 && player->getPosition() <= 29){
                        if(player->getPosition() == 20){
                            setcolor(2);
                            setfillstyle(SOLID_FILL,2);
                            circle(sw+40,sh+13,8);
                            floodfill(sw+40,sh+13,2);
                        }
                        else{
                            int cur = player->getPosition() - 21;
                            setcolor(2);
                            setfillstyle(SOLID_FILL,2);
                            circle(sw+110+cur*50,sh+13,8);
                            floodfill(sw+110+cur*50,sh+13,2);
                        }
                   }
                   if(player->getPosition()+ steps >= 20 && player->getPosition()+steps <= 29){
                        if(player->getPosition()+steps == 20){
                            setcolor(4);
                            setfillstyle(SOLID_FILL,4);
                            circle(sw+40,sh+13,8);
                            floodfill(sw+40,sh+13,4);
                        }
                        else{
                            int cur = player->getPosition() + steps - 21;
                            setcolor(4);
                            setfillstyle(SOLID_FILL,4);
                            circle(sw+110+cur*50,sh+13,8);
                            floodfill(sw+110+cur*50,sh+13,4);
                        }
                   }
                   if(player->getPosition()+steps >= 30 && player->getPosition()+steps <= 39){
                        if(player->getPosition()+steps == 30){
                            setcolor(4);
                            setfillstyle(SOLID_FILL,4);
                            circle(sw+590,sh+13,8);
                            floodfill(sw+590,sh+13,4);
                        }
                        else{
                            int cur =  40 - player->getPosition() - steps ;
                            setcolor(4);
                            setfillstyle(SOLID_FILL,4);
                            circle(sw+590,sh+563-cur*50,8);
                            floodfill(sw+590,sh+563-cur*50,4);
                        }
                   }
                   if(player->getPosition() >= 30 && player->getPosition() <= 39){
                        if(player->getPosition() == 30){
                            setcolor(2);
                            setfillstyle(SOLID_FILL,2);
                            circle(sw+590,sh+13,8);
                            floodfill(sw+590,sh+13,2);
                        }
                        else{
                            int cur =  40 - player->getPosition();
                            setcolor(2);
                            setfillstyle(SOLID_FILL,2);
                            circle(sw+590,sh+563-cur*50,8);
                            floodfill(sw+590,sh+563-cur*50,2);
                        }
                   }
            }


            else{
                  player = &player2;
                  opponent = &player1;
                  if(player->getPosition() >= 0 && player->getPosition() <= 9){
                        if(player->getPosition() == 0){
                            setcolor(2);
                            setfillstyle(SOLID_FILL,2);
                            circle(sw+610,sh+563,8);
                            floodfill(sw+610,sh+563,2);
                        }
                        else{
                            int cur = 9-player->getPosition();
                            setcolor(2);
                            setfillstyle(SOLID_FILL,2);
                            circle(sw+130+cur*50,sh+563,8);
                            floodfill(sw+130+cur*50,sh+563,2);
                        }
                   }
                   if((player->getPosition()+steps)%40 >= 0 && (player->getPosition()+steps)%40 <= 9){
                        if((player->getPosition()+steps)%40 == 0){
                            setcolor(1);
                            setfillstyle(SOLID_FILL,1);
                            circle(sw+610,sh+563,8);
                            floodfill(sw+610,sh+563,1);
                        }
                        else{
                            int cur = 9 - (player->getPosition() + steps)%40;
                            setcolor(1);
                            setfillstyle(SOLID_FILL,1);
                            circle(sw+130+cur*50,sh+563,8);
                            floodfill(sw+130+cur*50,sh+563,1);
                        }
                   }
                   if(player->getPosition()+steps >= 10 && player->getPosition()+steps <= 19){
                        if(player->getPosition()+steps == 10){
                            setcolor(1);
                            setfillstyle(SOLID_FILL,1);
                            circle(sw+60,sh+563,8);
                            floodfill(sw+60,sh+563,1);
                        }
                        else{
                            int cur =  player->getPosition() + steps - 10;
                            setcolor(1);
                            setfillstyle(SOLID_FILL,1);
                            circle(sw+60,sh+563-cur*50,8);
                            floodfill(sw+60,sh+563-cur*50,1);
                        }
                   }
                   if(player->getPosition() >= 10 && player->getPosition() <= 19){
                        if(player->getPosition() == 10){
                            setcolor(2);
                            setfillstyle(SOLID_FILL,2);
                            circle(sw+60,sh+563,8);
                            floodfill(sw+60,sh+563,2);
                        }
                        else{
                            int cur =  player->getPosition() - 10;
                            setcolor(2);
                            setfillstyle(SOLID_FILL,2);
                            circle(sw+60,sh+563-cur*50,8);
                            floodfill(sw+60,sh+563-cur*50,2);
                        }
                   }
                   if(player->getPosition()+ steps >= 20 && player->getPosition()+steps <= 29){
                        if(player->getPosition()+steps == 20){
                            setcolor(1);
                            setfillstyle(SOLID_FILL,1);
                            circle(sw+60,sh+13,8);
                            floodfill(sw+60,sh+13,1);
                        }
                        else{
                            int cur = player->getPosition() + steps - 21;
                            setcolor(1);
                            setfillstyle(SOLID_FILL,1);
                            circle(sw+130+cur*50,sh+13,8);
                            floodfill(sw+130+cur*50,sh+13,1);
                        }
                   }
                   if(player->getPosition() >= 20 && player->getPosition() <= 29){
                        if(player->getPosition() == 20){
                            setcolor(2);
                            setfillstyle(SOLID_FILL,2);
                            circle(sw+60,sh+13,8);
                            floodfill(sw+60,sh+13,2);
                        }
                        else{
                            int cur = player->getPosition() - 21;
                            setcolor(2);
                            setfillstyle(SOLID_FILL,2);
                            circle(sw+130+cur*50,sh+13,8);
                            floodfill(sw+130+cur*50,sh+13,2);
                        }
                   }
                   if(player->getPosition()+steps >= 30 && player->getPosition()+steps <= 39){
                        if(player->getPosition()+steps == 30){
                            setcolor(1);
                            setfillstyle(SOLID_FILL,1);
                            circle(sw+610,sh+13,8);
                            floodfill(sw+610,sh+13,1);
                        }
                        else{
                            int cur =  40 - player->getPosition() - steps ;
                            setcolor(1);
                            setfillstyle(SOLID_FILL,1);
                            circle(sw+610,sh+563-cur*50,8);
                            floodfill(sw+610,sh+563-cur*50,1);
                        }
                   }
                   if(player->getPosition() >= 30 && player->getPosition() <= 39){
                        if(player->getPosition() == 30){
                            setcolor(2);
                            setfillstyle(SOLID_FILL,2);
                            circle(sw+610,sh+13,8);
                            floodfill(sw+610,sh+13,2);
                        }
                        else{
                            int cur =  40 - player->getPosition();
                            setcolor(2);
                            setfillstyle(SOLID_FILL,2);
                            circle(sw+610,sh+563-cur*50,8);
                            floodfill(sw+610,sh+563-cur*50,2);
                        }
                   }
            }

            int old_position = player->getPosition();
            int new_position = (old_position+steps)%40;
            player->setPosition(new_position);
            cout<<"Dice 1: "<<n1<<"\nDice 2: "<<n2<<endl<<endl;
            int pos_type = check_pos(new_position);
            cout<<"Player "<<current_player<<":\n\n";
            if(old_position>new_position && player->getJailStatus()==0){
                  cout<<"You passed GO, you earned 200\n";
                  player+200;
            }
            if(pos_type >=4){//card is location card
                  Location* cur_card = board[new_position];
                  string cur_name = cur_card->getName();
                  int cur_amount = cur_card->getAmount();
                  cout<<"Name: "<<cur_name<<"\nAmount: "<<cur_amount<<endl;
                  int current_owner = cur_card->getOwner();
                  if(current_owner == 0){//unowned
                        cout<<"Would you like to buy this property (y/n)?\n";
                        char choice;
                        cin>>choice;
                        if(choice=='y'){
                              label:
                              double cur_bal = player->getBalance();
                              if(cur_bal>=cur_amount){
                                    *player-cur_amount;
                                    cout<<"You bought "<<cur_name<<endl;
                                    cur_card->setOwner(current_player);
                                    player->addLocation(cur_card);
                              }
                              else{
                                    bool check = moneyShort(player);
                                    if(check){
                                         goto label;
                                    }

                              }
                        }
                  }
                  else if(current_owner==current_player){
                        cout<<"You already own this property\n";
                        if(cur_card->getMortStatus() && player->getBalance()>cur_card->getMortgage()){
                              cout<<"You have eneough money to unmortgage this property\n";
                              cout<<"Automatic Unmortgage\n";
                              *player+(cur_card->getMortgage());
                              cur_card->setMortStatus(false);
                        }
                        else if(cur_card->getMortStatus()){
                              cout<<"This property is mortgaged by you\n";
                              cout<<"You don't have enough money to unmortgage\n";
                        }
                        else if(pos_type == 6){
                              if(cur_card->getBuildings()<5){
                                    cout<<"Would you like to build houses/hotel? (y/n)\n";
                                    int value = cur_card->getValue();
                                    double house_rent = getHouseRent(value);
                                    cout<<"The rent per building is "<<house_rent<<endl;
                                    char choice;
                                    cin>>choice;
                                    if(choice=='y'){
                                          if(house_rent>player->getBalance()){
                                                cout<<"You do not have enough money to build buildings here.\n";
                                                cout<<"For builings, you do not have options to get money from bank.\n";
                                          }
                                          else{
                                                cur_card->addBuilding();
                                                cout<<"You have successfully built building.\n";
                                          }
                                    }
                                    else{
                                          cout<<"You didn't build any building here\n";
                                    }
                              }
                              else{
                                    cout<<"There is already a hotel here\n";
                              }
                        }
                        else{
                              cout<<"This location can't have buildings\n";
                        }


                  }
                  else{
                        cout<<"This property is owned by your oponent\n";
                        int rent;
                        if(pos_type==4){
                              rent = cur_card->getRent(n1,n2,player->getNumUtil());
                        }
                        else if(pos_type==5){
                              rent = cur_card->getRent(player->getNumRail());
                        }
                        else if(pos_type==6){
                              rent = cur_card->getRent();
                        }

                        if(!cur_card->getMortStatus() && player->getJailStatus()==0){
                              cout<<"You have to pay a rent of "<<rent<<endl;
                              l2:
                              if(player->getBalance() < rent){
                                    bool status = checkGameStatus(player);
                                    if(status){
                                          cout<<"Player "<<current_player<<" you don't have enough money and you don't own any properties.\nYou Lose\n";
                                          game_status=0;
                                    }
                                    else{
                                          bool check = moneyShort(player);
                                          if(check){
                                                goto l2;
                                          }
                                          else{
                                                cout<<"Invalid Option\n";
                                                goto l2;
                                          }
                                    }

                              }
                              *player-rent;
                              *opponent+rent;
                              cout<<"Opponent earned "<<rent<<endl;
                        }
                        else{
                              cout<<"Property is mortgaged or Player is in Jail\n";
                              cout<<"You do not have to pay any money\n";
                        }

                  }
            }
            else if(check_pos(new_position)==2){
                  cout<<"You have landed on Chance or Community Chest\n";
                  if(new_position==33){
                        goToJail(player,new_position, current_player);
                  }
                  else if(new_position==22){
                        cout<<"You have advanced to GO\n";
                        if(current_player == 2){
                              setcolor(2);
                              setfillstyle(SOLID_FILL,2);
                              circle(sw+130+50,sh+13,8);
                              floodfill(sw+130+50,sh+13,2);
                              setcolor(1);
                              setfillstyle(SOLID_FILL,1);
                              circle(sw+610,sh+563,8);
                              floodfill(sw+610,sh+563,1);
                        }
                        else if(current_player == 1){
                            setcolor(2);
                            setfillstyle(SOLID_FILL,2);
                            circle(sw+110+50,sh+13,8);
                            floodfill(sw+110+50,sh+13,2);
                            setcolor(4);
                            setfillstyle(SOLID_FILL,4);
                            circle(sw+590,sh+563,8);
                            floodfill(sw+590,sh+563,4);
                        }
                        player->setPosition(0);
                        new_position=0;
                  }
                  else if(new_position%2==0){
                        *player+(steps*2);
                        cout<<"You earned "<<(steps*2)<<endl;
                  }
                  else{
                        *player-steps;
                        cout<<"You lost "<<steps<<endl;
                  }
            }
            else if(check_pos(new_position)==3){
                  int tax;
                  if(new_position==4){
                        tax=200;
                  }
                  else{
                        tax=150;
                  }
                        cout<<"You have landed on tax\nYou have to pay "<<tax<<endl;
                        l3:
                        if(player->getBalance()<tax){
                              bool status = checkGameStatus(player);
                              if(status){
                                    cout<<current_player<<" you don't have enough money and you don't own any properties.\nYou Lose\n";
                                    game_status=0;
                              }
                              bool check = moneyShort(player);
                              if(check){
                                    goto l3;
                              }
                              else{
                                    cout<<"Invalid Option\n";
                                    goto l3;
                              }
                        }
                        else{
                              *player-tax;
                              cout<<"You have payed a tax of "<<tax<<endl;
                        }

            }
            else{
                  if(new_position==0){
                        cout<<"You are on GO\n";
                  }
                  else if(new_position==10){
                        cout<<"You are on just visiting\n";
                  }
                  else if(new_position==20){
                        cout<<"You are on free parking\n";
                  }
                  else{
                        goToJail(player,new_position,current_player);
                  }
            }
            for(int i=0;i<=39;i++){
                  int clr;
                  Location* card = board[i];
                  if(card->getOwner() == 0)
                    clr = 2;
                  else if(card->getOwner() == 1)
                    clr = 4;
                  else if(card->getOwner() == 2)
                    clr = 1;
                    setcolor(clr);
                    settextstyle(0,0,2);
                    setbkcolor(2);
                  if(i>0 && i <=9){
                    int ps = 9 - i;
                    char c[10];
                    rectangle(sw+103 + ps*50,sh+553,sw+147 + ps*50,sh+647);
                    if(card->getBuildings() > 0 && card->getBuildings()<5){
                        moveto(sw+120 + ps*50,sh+595);
                        if(card->getBuildings() == 0){
                              setcolor(2);
                              rectangle(sw+120+ps*50,sh+595,sw+145+ps*50,sh+640);
                              setfillstyle(SOLID_FILL,2);
                              floodfill(sw+120+ps*50,sh+595,2);
                        }
                  }}
                  if(i>10 && i <=19){
                    int ps = 19 - i;
                    char c[50];
                    rectangle(sw+3,sh+103+ps*50,sw+97,sh+147+ps*50);
                    if(card->getBuildings() >= 1 && card->getBuildings()<=5){
                        moveto(sw+47,sh+123+ps*50);
                        if(card->getBuildings() == 0){
                              setcolor(2);
                              rectangle(sw+47,sh+123+ps*50,sw+67,sh+143+ps*50);
                              setfillstyle(SOLID_FILL,2);
                              floodfill(sw+47,sh+123+ps*50,2);
                        }
                  }}
                  if(i>20 && i <=29){
                    int ps = i - 21;
                    char c[10];
                    rectangle(sw+103 + ps*50,sh+3,sw+147 + ps*50,sh+97);
                    if(card->getBuildings() > 0 && card->getBuildings()<=5){
                        moveto(sw+120 + ps*50,sh+45);
                        if(card->getBuildings() == 0){
                              setcolor(2);
                              rectangle(sw+120+ps*50,sh+45,sw+140+ps*50,sh+45);
                              setfillstyle(SOLID_FILL,2);
                              floodfill(sw+120+ps*50,sh+45,2);
                        }

                  }}
                  if(i>30 && i <=39){
                    int ps = i - 31;
                    char c[10];
                    rectangle(sw+553,sh+103 + ps*50,sw+ 647,sh+147 + ps*50);
                    if(card->getBuildings() > 0 && card->getBuildings()<=5){
                        moveto(sw+590,sh+122 + ps*50);
                        if(card->getBuildings() == 0){
                              setcolor(2);
                              rectangle(sw+590,sh+122+ps*50,sw+610,sh+143+ps*50);
                              setfillstyle(SOLID_FILL,2);
                              floodfill(sw+590,sh+123+ps*50,2);
                        }
                  }}
                  setcolor(clr);
                  if(card->getBuildings() == 1)
                    outtext("1");
                  else if(card->getBuildings() == 2)
                    outtext("2");
                  else if(card->getBuildings() == 3)
                    outtext("3");
                  else if(card->getBuildings() ==4)
                    outtext("4");
                   else if(card->getBuildings() == 5)
                     outtext("H");
            }
            if(n1==n2 && player->getJailStatus()==0){
                  cout<<"Next turn is for same player as you have rolled doubles\n";
            }
            else if(opponent->getJailStatus()!=0){
                  cout<<"Next turn is for same player as oponent is in jail\n";
                  int js = opponent->getJailStatus();
                  if(js<3){
                        opponent->setJailStatus(js+1);
                  }
                  else{
                        opponent->setJailStatus(0);
                  }
            }
            else if(current_player==1)
                  current_player=2;
            else
                  current_player=1;
            cout<<"\n";
            player->getLocations();
            cout<<player->getBalance()<<" is your current balance\n";
            delay(5000);
            system("cls");
     }
     return 0;

}



