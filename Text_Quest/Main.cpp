#include <iostream>
using namespace std;

int main()
{
    again:
    int location = 0;
    int count_horse = 1;
    int weapon = 0;
    int silverkey = 0;
    while (true)
    {
        switch (location)
        {
        case 0:
            startloc:
            cout << "Hello traveler, choose one of 4 doors";
            break;
        case 1:              

            if (count_horse > 0)
            {
                cout << "You lost a horse";
                count_horse--;
                cout << "  A horse:" << count_horse;
            }
            else
            {
                cout << "You see a dead horse";
            }
            break;
        case 2:
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
                if (chooserobloc == 1)
                {
                    goto startloc;
                }
                if (chooserobloc == 2)
                {
                    cout << "You're dead.";
                    goto again;
                }
                if (chooserobloc == 3)
                {
                    cout << "You defeat the bandits and get the silver key.";
                    silverkey++;
                    goto startloc;
                }
            }
            break;
        case 3:
            if (weapon == 0)
            {
                cout << "You found a sword";
                weapon++;
            }
            else
            {
                cout << "Do you see an empty room";
            }
            break;
        case 4:
        {
            if (silverkey == 0)
            {
                cout << "closed";
            }
            else
            {
                cout << "The road has brought you to a village called Life";
            }
        }
        }
        int inp;
        cin >> inp;
        if (inp >= 0 && inp <= 4)
        {
            location = inp;
        }
        else
        {
            cout << "Room is out of range 0-3";
        }
    }
}