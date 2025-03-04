#include <iostream>
#include <vector>
using namespace std;

int location = 0;

int weapon = 0;
int silverkey = 0;
bool forceLocation = false;

enum class equip {
    sword,
    axe,
    hemlet
};

struct player_ 
{

    vector<equip> hero_items = {};
    int count_horse;
    int life;

    void Init()
    {
        count_horse = 1;
        life = 1;

        hero_items.push_back(equip::axe);
        hero_items.push_back(equip::hemlet);

    }

    void dropItem(equip itemID) {
        auto it = find(hero_items.begin(), hero_items.end(), itemID);
        if (it != hero_items.end()) {
            hero_items.erase(it);
            cout << "Item dropped: " << static_cast<int>(itemID) << "\n";
        }
        else {
            cout << "Item not found in inventory.\n";
        }
    }

    void printInventory() const 
    {
        if (hero_items.empty()) {
            cout << "Your inventory is empty.\n";
            return;
        }

        cout << "Your inventory:\n";
        for (const auto& item : hero_items) {
            switch (item) {
            case equip::sword:
                cout << "- Sword\n";
                break;
            case equip::axe:
                cout << "- Axe\n";
                break;
            case equip::hemlet:
                cout << "- Hemlet\n";
                break;
            default:
                cout << "- Unknown item\n";
                break;
            }
        }
    }
};
 
player_ player;


void initGame()
{
    
    location = 0;
    weapon = 0;
    silverkey = 0;
   player.Init();
} 



void startLocation()
{
    cout << "Hello traveler, choose one of 4 doors";
}

void horseLocation()
{
    if (player.count_horse > 0)
    {
        cout << "You lost a horse";
        player.count_horse--;
        cout << "  A horse:" << player.count_horse;
    }
    else
    {
        cout << "You see a dead horse";
    }
}

void robbersLocation()
{
    if (silverkey == 1)
    {
        cout << "You see the dead robbers";
    }
    else
    {
        int chooserobloc;
        cout << "You met robbers";
        if (weapon == 0)
        {
            cout << "1. run away  2. fight ";
            cin >> chooserobloc;
        }
        else
        {
            cout << "1. run away  2. fight 3. get a weapon and fight";
            cin >> chooserobloc;
        }

        switch (chooserobloc)
        {

        case 1:
            forceLocation = true;
            location = 0;
            break;
        case 2:
            cout << "You're dead.";
            initGame();
            forceLocation = true;
            break;
        case 3:
            cout << "You defeat the bandits and get the silver key.";
            silverkey++;
            location = 0;
            forceLocation = true;
            break;

        }
    }
}
void swordLocation() 
{
    if (weapon == 0)
    {
        cout << "You found a sword";
        player.hero_items.push_back(equip::sword);
        weapon++;
    }
    else
    {
        cout << "Do you see an empty room";
    }
}
void villageLife()
{
    if (silverkey == 0)
    {
        cout << "closed";
    }
    else
    {
        cout << "The road has brought you to a village called Life";
        player.printInventory();
    }
}

void(*functptr[])() = {startLocation, horseLocation, robbersLocation, swordLocation, villageLife};

int main()
{
     
     initGame();
    while (player.life > 0)
    {
        (*functptr[location])(); 

        if (!forceLocation)
        {
            int inp;
            cin >> inp;
            if (inp >= 0 && inp <= 4)
            {
                location = inp;
            }
            else
            {
                cout << "Room is out of range 0-3";
                continue;
                
            }
        }
        else
        {
            forceLocation = false;
        }


    }
    cout << "Game over";
}