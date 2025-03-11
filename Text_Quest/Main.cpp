#include <iostream>
#include <vector>
using namespace std;

int currentLocation;
int silverkey;
string inp = {};

enum class equip {
    sword,
    axe,
    helmet
};

string getIDString(equip itemID)
{
    switch (itemID) {
    case equip::sword:
        return "sword";
        break;
    case equip::axe:
        return "axe";
        break;
    case equip::helmet:
        return "helmet";
        break;
    default:
        return "Unknown item\n";
        break;
    }
    return NULL;
}

struct Location_
{
    vector<equip> location_items = {};
    void printInventory()
    {
        if (location_items.empty()) {
            cout << "Location inventory is empty.\n";
            return;
        }

        cout << "Location inventory:\n";

        for (int i = 0; i < location_items.size(); i++) {
            auto s = getIDString(location_items[i]);
            cout << "- " << s.c_str() << "\n";
        }
    }

};

Location_ location[5];

struct player_ 
{

    vector<equip> hero_items = {};
    int count_horse;
    int life;

    void Init()
    {
        count_horse = 1;
        life = 1;
    }

    void dropItem(equip itemID) {
        auto it = find(hero_items.begin(), hero_items.end(), itemID);
        if (it != hero_items.end()) {
            location[currentLocation].location_items.push_back(*it);
            hero_items.erase(it);
            cout << "Item dropped: " << getIDString(itemID) << "\n";
        }
        else {
            cout << "Item not found in inventory.\n";
        }
    }
    void pickItem(equip itemID)
    {
        auto it = find(location[currentLocation].location_items.begin(), location[currentLocation].location_items.end(), itemID);
        if (it != location[currentLocation].location_items.end()) {
            hero_items.push_back(itemID);
            location[currentLocation].location_items.erase(it);
            cout << "Item picked: " << getIDString(itemID) << "\n";
        }
        else {
            cout << "Item not found in location.\n";
        }
    }

    void printInventory()  
    {
        if (hero_items.empty()) {
            cout << "Your inventory is empty.\n";
            return;
        }

        cout << "Your inventory:\n";

        for (int i = 0; i < hero_items.size(); i++) {
            auto s = getIDString(hero_items[i]);
            cout << "- " << s.c_str() << "\n";
        }
    }
};

player_ player;

void playerinput()
{
    cin >> inp;
    for (auto item : location[currentLocation].location_items) {
        if (inp == getIDString(item)) {
            player.pickItem(item);
            return;
        }
    }

   

    if (inp == "i")
    {
        player.printInventory();
    }
    else if (inp == "2")
    {
        currentLocation++;
    }
    else if (inp == "1")
    {
        currentLocation--;
    }
    else
    {
        cout << "Input wrong, try again\n";
    }
}


void initGame()
{
    currentLocation = 0;
    silverkey = 0;
    location[0].location_items.push_back(equip::helmet);
    location[3].location_items.push_back(equip::sword);
   player.Init();
} 



void startLocation()  //location 0
{
    cout << "You are in the starting location. Select an action\n";
    cout << "2.Go forward\n";
    cout << "i.Inventory\n";
    cout << "Write down the name of the item to pick it up\n";
    location[currentLocation].printInventory();
    playerinput();
}

void horseLocation()   //location 1
{
    if (player.count_horse > 0)
    {
        cout << "You lost a horse\n";
        player.count_horse--;
        cout << "  A horse:" << player.count_horse << "\n";
        cout << "1.Go back\n";
        cout << "2.Go forward\n";
        cout << "i.Inventory\n";
        cout << "Write down the name of the item to pick it up\n";
        location[currentLocation].printInventory();
        playerinput();
    }
    else
    {
        cout << "You see a dead horse\n";
        cout << "1.Go back\n";
        cout << "2.Go forward\n";
        cout << "i.Inventory\n";
        cout << "Write down the name of the item to pick it up\n";
        location[currentLocation].printInventory();
        playerinput();
    }
}

void robbersLocation() //location 2
{
    cout << "You met robbers. Select an action\n";
    cout << "1.Go back\n";
    cout << "2.Go forward\n";
    cout << "i.Inventory\n";
    cout << "Write down the name of the item to pick it up\n";
    for (auto item : player.hero_items)
    {
        if (getIDString(item) == "sword")
        {
            cout << "You defeat the bandits and get the silver key. You can take the axe from their leader.\n";
            location[currentLocation].location_items.push_back(equip::axe);
            silverkey++;
            location[currentLocation].printInventory();
            playerinput();
        }
    }
    location[currentLocation].printInventory();
    playerinput();
}
void swordLocation() //location 3
{
    cout << "Bandits have clearly been here, you can see a broken wagon, and in the distance you can see a huge fence and a door. Select an action\n";
    cout << "1.Go back\n";
    cout << "2.Go forward\n";
    cout << "i.Inventory\n";
    cout << "Write down the name of the item to pick it up\n";
    if (silverkey == 1)
    {
        cout << "You managed to open the door with a key.\n";
    }
    location[currentLocation].printInventory();
    playerinput();
    
}
void villageLife() //location 4
{
    if (silverkey == 0)
    {
        cout << "closed\n";
        currentLocation--;
    }
    else
    {
        cout << "The road has brought you to a village called Life\n";
        location[currentLocation].printInventory();
        playerinput();
    }
}

void(*functptr[])() = {startLocation, horseLocation, robbersLocation, swordLocation, villageLife};

int main()
{
     
     initGame();
         
     
     while (player.life > 0)
     {
         if (currentLocation >= 0)
         {
             (*functptr[currentLocation])();
         }
         else
         {
             currentLocation = 0;
             continue;
         }
     }

    cout << "Game over\n";
}