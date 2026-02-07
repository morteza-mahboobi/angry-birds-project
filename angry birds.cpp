using namespace std;

// for control window and program
#include <windows.h>
// for input & output
#include <iostream>
// for math function
#include <math.h>
// for working with file
#include <fstream>
// for get character without enter
#include <conio.h>
// use system function
#include <cstdlib>

void PrintFile(string);
void ResetProgress(string, string);
void PauseScreen();
void FullScreen();

short TypeOfInputs = 1;
short HowToMoveBullet = 2;
short GameSpeed = 3;
int SleepTimeGame = 200;
short SizeOfMapX = 90;
short SizeOfMapY = 25;
short PlayerPlace = 3;
const char SpecialShotKeyL = 'O';
const char SpecialShotKeyS = 'o';
const char ExitKeyInGameL = 'Q';
const char ExitKeyInGameS = 'q';
#define SleepTimeShowMap 2000

void gotoxy(short, short);
struct Wall
{
    short xPos;
    short yPos;

    void Print()
    {
        gotoxy(xPos, yPos);
        cout << '#';
    }
};
struct Enemy
{
    short xPos;
    short yPos;

    void Print()
    {
        gotoxy(xPos, yPos);
        cout << 'E';
    }
};
struct Launcher
{
    short xPos;
    short yPos;

    void Print()
    {
        gotoxy(xPos, yPos);
        cout << 'P';
    }
};
struct Projectile
{
    short xPos;
    short yPos;

    void Print()
    {
        gotoxy(xPos, yPos);
        cout << '*';
    }

    // for HowToMoveBullet = 2
    void Delete()
    {
        gotoxy(xPos, yPos);
        cout << ' ';
    }

    // for HowToMoveBullet = 1
    short PreviousxPos;
    short PreviousyPos;

    void DeletePrevious()
    {
        gotoxy(PreviousxPos, PreviousyPos);
        cout << ' ';
    }
};
short Map1(short **);
short Map2(short **);
short Map3(short **);
short Map4(short **);
short Map5(short **);
short Map6(short **);
void Border(short **);
Launcher Player();

void NormalShot(short &, short &, short **);
void BombShot(short &, short &, short **);
void DropKickShot(short &, short &, short **);
void DrillShot(short &, short &, short **);
void ClearArea(short, short, short, short);

short PlayGame(short, short, short, short, short);
short CalculatePoint(short, short, short,
                     short, short, short, short,
                     short, short, short, short);
void SaveStar(short, short, string);

int main()
{
    const string AddressOfResetProgress = "basic progress.txt";
    const string AddressOfProgress = "progress.txt";
    const string AddressOfHelp = "how to play.txt";
    FullScreen();

    while (true)
    {
        system("cls");
        // ----------- start menu -----------
        cout << "\n======================================\n";
        cout << "    CONSOLE LAUNCHER (No Gravity)\n";
        cout << "======================================\n\n";
        cout << "1) Start" << endl
             << "2) How To Play" << endl
             << "3) Help & How to play (persian mode)" << endl
             << "4) Reset Progress" << endl
             << "5) Show Map" << endl
             << "6) Setting" << endl
             << "7) About The Developer\n\n"
             << "0) Exit\n\n";

        cout << "Progress :\n";
        PrintFile(AddressOfProgress);
        // ----------- end menu -----------

        cout << "\nyour choice : ";
        short Choice;
        cin >> Choice;
        system("cls");

        if (Choice == 1)
        {
            short StarMap1 = PlayGame(1, 5, 1, 0, 0);
            if (StarMap1 != -1)
            {
                system("cls");
                SaveStar(1, StarMap1, AddressOfProgress);
                short StarMap2 = PlayGame(2, 6, 2, 0, 0);
                if (StarMap2 != -1)
                {
                    system("cls");
                    SaveStar(2, StarMap2, AddressOfProgress);
                    short StarMap3 = PlayGame(3, 7, 1, 1, 1);
                    if (StarMap3 != -1)
                    {
                        system("cls");
                        SaveStar(3, StarMap3, AddressOfProgress);
                        short StarMap4 = PlayGame(4, 8, 2, 2, 1);
                        if (StarMap4 != -1)
                        {
                            system("cls");
                            SaveStar(4, StarMap4, AddressOfProgress);
                            short StarMap5 = PlayGame(5, 10, 2, 2, 2);
                            if (StarMap5 != -1)
                            {
                                system("cls");
                                SaveStar(5, StarMap5, AddressOfProgress);
                                short StarMap6 = PlayGame(6, 12, 3, 3, 3);
                                if (StarMap6 != -1)
                                {
                                    system("cls");
                                    SaveStar(6, StarMap6, AddressOfProgress);
                                }
                            }
                        }
                    }
                }
            }
        }
        else if (Choice == 2)
        {
            cout << "\n--------------------------------------\n";
            cout << "         How To Play & Help\n";
            cout << "--------------------------------------\n\n";

            PrintFile(AddressOfHelp);
            PauseScreen();
        }
        else if (Choice == 3)
        {
            cout << "\n--------------------------------------\n";
            cout << "    How To Play & Help (persian mode)\n";
            cout << "--------------------------------------\n\n";

            cout << "Wait for open file ....";
            system("persian-help.pdf");

            PauseScreen();
        }
        else if (Choice == 4)
        {
            cout << "\n--------------------------------------\n";
            cout << "         Progress Statuse\n";
            cout << "--------------------------------------\n\n";

            ResetProgress(AddressOfProgress, AddressOfResetProgress);
            cout << "Reset Progress Was Successfully ..." << endl;
            PauseScreen();
        }
        else if (Choice == 5)
        {
            short **GridMap = new short *[SizeOfMapX + 1];
            for (int i = 0; i <= SizeOfMapX; i++)
            {
                GridMap[i] = new short[SizeOfMapY + 1];
                for (int j = 0; j <= SizeOfMapY; j++)
                {
                    GridMap[i][j] = 0;
                }
            }

            cout << "\n--------------------------------------\n";
            cout << "             Show Map \n";
            cout << "--------------------------------------\n\n";

            cout << " 1) First Level" << endl
                 << " 2) Second Level" << endl
                 << " 3) Third Level" << endl
                 << " 4) Fourth Level" << endl
                 << " 5) Fifth Level" << endl
                 << " 6) Sixth Level" << endl
                 << " 7) All Map\n\n"
                 << " 0) Go Back \n\n";

            cout << "-> which map do you want to look at : ";
            short ChoiceMap;
            cin >> ChoiceMap;
            system("cls");

            switch (ChoiceMap)
            {
            case 1:
                Map1(GridMap);
                PauseScreen();
                break;

            case 2:
                Map2(GridMap);
                PauseScreen();
                break;

            case 3:
                Map3(GridMap);
                PauseScreen();
                break;

            case 4:
                Map4(GridMap);
                PauseScreen();
                break;

            case 5:
                Map5(GridMap);
                PauseScreen();
                break;

            case 6:
                Map6(GridMap);
                PauseScreen();
                break;

            case 7:
                Map1(GridMap);
                Sleep(SleepTimeShowMap);
                system("cls");

                Map2(GridMap);
                Sleep(SleepTimeShowMap);
                system("cls");

                Map3(GridMap);
                Sleep(SleepTimeShowMap);
                system("cls");

                Map4(GridMap);
                Sleep(SleepTimeShowMap);
                system("cls");

                Map5(GridMap);
                Sleep(SleepTimeShowMap);
                system("cls");

                Map6(GridMap);
                Sleep(SleepTimeShowMap);

                PauseScreen();
                break;

            case 0:
                break;

            default:
                cout << "Not Found !!!";
                PauseScreen();
                break;
            }

            for (int i = 0; i <= SizeOfMapX; i++)
            {
                delete[] GridMap[i];
            }
            delete[] GridMap;
        }
        else if (Choice == 6)
        {
            short *Temp = new short;

            while (true)
            {
                system("cls");
                cout << "\n--------------------------------------\n";
                cout << "               Setting\n";
                cout << "--------------------------------------\n\n";

                cout << " 1) Size Of Map" << endl
                     << " 2) Size Of Luanch Pad" << endl
                     << " 3) Type Of Inputs In Game" << endl
                     << " 4) How To Move Bullet" << endl
                     << " 5) Game Speed (For Automatic Move)\n\n"
                     << " 6) Reset Setting" << endl
                     << " 0) Go Back \n\n";

                cout << "your choice : ";
                short ChoiceSetting;
                cin >> ChoiceSetting;
                short ChangeSetting;
                system("cls");

                if (ChoiceSetting == 1)
                {
                    cout << "\n--------------------------------------\n";
                    cout << "              Size Of Map\n";
                    cout << "--------------------------------------\n\n";

                    cout << "Current Setting : " << SizeOfMapX << " * " << SizeOfMapY;

                    cout << "\n ------------------ \n";
                    cout << "do you want change ? ";
                    cout << "\n 1) Yes \n 2) No \n";
                    cout << "choose : ";
                    cin >> ChangeSetting;

                    system("cls");
                    cout << "\n--------------------------------------\n";
                    cout << "              Size Of Map\n";
                    cout << "--------------------------------------\n\n";

                    switch (ChangeSetting)
                    {
                    case 1:
                        cout << "Width Must Be Between 50 - 160\n";
                        cout << "Height Must Be Between 15 - 35\n";
                        cout << endl;

                        do
                        {
                            cout << "width : ";
                            cin >> *Temp;
                            if (*Temp >= 50 && *Temp <= 160)
                            {
                                SizeOfMapX = *Temp;
                            }
                            else
                            {
                                cout << "This Is Outside The Range !!!\n";
                            }
                            cout << endl;
                        } while (!(*Temp >= 50 && *Temp <= 160));

                        do
                        {
                            cout << "height : ";
                            cin >> *Temp;
                            if (*Temp >= 15 && *Temp <= 45)
                            {
                                SizeOfMapY = *Temp;
                            }
                            else
                            {
                                cout << "This Is Outside The Range !!!\n";
                            }
                            cout << endl;
                        } while (!(*Temp >= 15 && *Temp <= 35));

                        break;

                    case 2:
                        cout << "Setting Don't Change ...";
                        PauseScreen();
                        break;

                    default:
                        cout << "Unknow !!";
                        PauseScreen();
                        break;
                    }
                }
                else if (ChoiceSetting == 2)
                {
                    cout << "\n--------------------------------------\n";
                    cout << "          Size Of Luanch Pad\n";
                    cout << "--------------------------------------\n\n";

                    cout << "Current Setting : " << PlayerPlace;

                    cout << "\n ------------------ \n";
                    cout << "do you want change ? ";
                    cout << "\n 1) Yes \n 2) No \n";
                    cout << "choose : ";
                    cin >> ChangeSetting;

                    system("cls");
                    cout << "\n--------------------------------------\n";
                    cout << "          Size Of Luanch Pad\n";
                    cout << "--------------------------------------\n\n";

                    switch (ChangeSetting)
                    {
                    case 1:
                        cout << "Luanch Pad must be between 2 - 5\n";

                        do
                        {
                            cout << "Size : ";
                            cin >> *Temp;
                            if (*Temp >= 2 && *Temp <= 5)
                            {
                                PlayerPlace = *Temp;
                            }
                            else
                            {
                                cout << "This Is Outside The Range !!!\n";
                            }
                            cout << endl;
                        } while (!(*Temp >= 2 && *Temp <= 5));

                        break;
                    case 2:
                        cout << "Setting Don't Change ...";
                        PauseScreen();
                        break;
                    default:
                        cout << "Unknow !!";
                        PauseScreen();
                        break;
                    }
                }
                else if (ChoiceSetting == 3)
                {
                    cout << "\n--------------------------------------\n";
                    cout << "        Type Of Inputs In Game\n";
                    cout << "--------------------------------------\n\n";

                    cout << "Option : " << endl;
                    cout << " 1) Speed - Angle" << endl;
                    cout << " 2) vx (Speed of x) - vy (Speed of y) - ay (Acceleration of y) " << endl;
                    cout << "\nCurrent Setting : " << TypeOfInputs;

                    cout << "\n ------------------ \n";
                    cout << "do you want change ? ";
                    cout << "\n 1) Yes \n 2) No \n";
                    cout << "choose : ";
                    cin >> ChangeSetting;

                    system("cls");
                    cout << "\n--------------------------------------\n";
                    cout << "        Type Of Inputs In Game\n";
                    cout << "--------------------------------------\n\n";

                    switch (ChangeSetting)
                    {
                    case 1:
                        cout << "Option : " << endl;
                        cout << " 1) Speed - Angle" << endl;
                        cout << " 2) vx (Speed of x) - vy (Speed of y) - ay (Acceleration of y) " << endl;
                        cout << "choose one of the option : ";
                        cin >> *Temp;

                        if (*Temp == 1 || *Temp == 2)
                        {
                            TypeOfInputs = *Temp;
                        }
                        else
                        {
                            cout << "Unknow !!";
                        }

                        break;
                    case 2:
                        cout << "Setting Don't Change ...";
                        PauseScreen();
                        break;
                    default:
                        cout << "Unknow !!";
                        PauseScreen();
                        break;
                    }
                }
                else if (ChoiceSetting == 4)
                {
                    cout << "\n--------------------------------------\n";
                    cout << "          How To Move Bullet\n";
                    cout << "--------------------------------------\n\n";

                    cout << "Option : " << endl;
                    cout << " 1) With Hold Or Press Enter" << endl;
                    cout << " 2) Auto" << endl;
                    cout << "\nCurrent Setting : " << HowToMoveBullet;

                    cout << "\n ------------------ \n";
                    cout << "do you want change ? ";
                    cout << "\n 1) Yes \n 2) No \n";
                    cout << "choose : ";
                    cin >> ChangeSetting;

                    system("cls");
                    cout << "\n--------------------------------------\n";
                    cout << "          How To Move Bullet\n";
                    cout << "--------------------------------------\n\n";

                    switch (ChangeSetting)
                    {
                    case 1:
                        cout << "Option : " << endl;
                        cout << " 1) With Hold Or Press Enter" << endl;
                        cout << " 2) Auto" << endl;
                        cout << "choose one of the option : ";
                        cin >> *Temp;
                        if (*Temp == 1 || *Temp == 2)
                        {
                            HowToMoveBullet = *Temp;
                        }
                        else
                        {
                            cout << "Unknow !!";
                        }

                        break;
                    case 2:
                        cout << "Setting Don't Change ...";
                        PauseScreen();
                        break;
                    default:
                        cout << "Unknow !!";
                        PauseScreen();
                        break;
                    }
                }
                else if (ChoiceSetting == 5)
                {
                    cout << "\n--------------------------------------\n";
                    cout << "              Game Speed\n";
                    cout << "--------------------------------------\n\n";

                    if (HowToMoveBullet == 2)
                    {
                        cout << "Option : " << endl;
                        cout << " 1) Very Slow " << endl;
                        cout << " 2) Slow " << endl;
                        cout << " 3) Normal " << endl;
                        cout << " 4) Fast" << endl;
                        cout << " 5) Very Fast" << endl;
                        cout << "\nCurrent Setting : " << GameSpeed;

                        cout << "\n ------------------ \n";
                        cout << "do you want change ? ";
                        cout << "\n 1) Yes \n 2) No \n";
                        cout << "choose : ";
                        cin >> ChangeSetting;

                        system("cls");
                        cout << "\n--------------------------------------\n";
                        cout << "              Game Speed\n";
                        cout << "--------------------------------------\n\n";

                        switch (ChangeSetting)
                        {
                        case 1:
                            cout << "Option : " << endl;
                            cout << " 1) Very Slow " << endl;
                            cout << " 2) Slow " << endl;
                            cout << " 3) Normal " << endl;
                            cout << " 4) Fast (Warning : Bad For Drop Kick Shot)" << endl;
                            cout << " 5) Very Fast (Warning : Bad For Drop Kick Shot)" << endl;
                            cout << "choose one of the option : ";
                            cin >> *Temp;

                            if (*Temp == 1)
                            {
                                GameSpeed = 1;
                                SleepTimeGame = 350;
                            }
                            else if (*Temp == 2)
                            {
                                GameSpeed = 2;
                                SleepTimeGame = 300;
                            }
                            else if (*Temp == 3)
                            {
                                GameSpeed = 3;
                                SleepTimeGame = 200;
                            }
                            else if (*Temp == 4)
                            {
                                GameSpeed = 4;
                                SleepTimeGame = 100;
                            }
                            else if (*Temp == 5)
                            {
                                GameSpeed = 5;
                                SleepTimeGame = 50;
                            }
                            else
                            {
                                cout << "Unknow !!";
                                PauseScreen();
                            }

                            break;
                        case 2:
                            cout << "Setting Don't Change ...";
                            PauseScreen();
                            break;
                        default:
                            cout << "Unknow !!";
                            PauseScreen();
                            break;
                        }
                    }
                    else
                    {
                        cout << "Pleas First Change Setting . (How To Move Bullet -> Auto)";
                        PauseScreen();
                    }
                }
                else if (ChoiceSetting == 6)
                {
                    cout << "\n--------------------------------------\n";
                    cout << "             Reset Setting\n";
                    cout << "--------------------------------------\n\n";

                    SizeOfMapX = 90;
                    SizeOfMapY = 25;
                    PlayerPlace = 3;
                    TypeOfInputs = 1;
                    HowToMoveBullet = 2;
                    GameSpeed = 3;
                    SleepTimeGame = 200;
                    cout << " 1) Size Of Map = 90 * 25" << endl
                         << " 2) Size Of Luanch Pad = 3" << endl
                         << " 3) Type Of Inputs In Game = Speed & Angle" << endl
                         << " 4) How To Move Bullet = Auto" << endl
                         << " 5) Game Speed = Normal";
                    PauseScreen();
                }
                else if (ChoiceSetting == 0)
                {
                    delete Temp;
                    break;
                }
                else
                {
                    cout << "Not Found !!!";
                    PauseScreen();
                }
            }
        }
        else if (Choice == 7)
        {
            cout << "\n--------------------------------------\n";
            cout << "          About The Developer\n";
            cout << "--------------------------------------\n\n";

            cout << " Create by \" Morteza Mahboobi \" " << endl;
            cout << " github address : https://github.com/morteza-mahboobi/angry-birds-project";

            PauseScreen();
        }
        else if (Choice == 0)
        {
            return 0;
        }
        else
        {
            cout << "Your Choice Is Wrong !!!!";
            PauseScreen();
        }
    }

    PauseScreen();
    return 0;
}

void PrintFile(string address)
{
    fstream a;
    string str;
    a.open(address, ios::in);
    while (!a.eof())
    {
        getline(a, str);
        cout << str << endl;
    }
    a.close();
}

void ResetProgress(string Address1, string Address2)
{
    // a & Address1 is for progress
    // b & Address2 is for reset progress
    fstream a, b;
    string str;
    a.open(Address1, ios::out);
    b.open(Address2, ios::in);

    while (!b.eof())
    {
        getline(b, str);
        if (!b.eof())
        {
            a << str << endl;
        }
        else
        {
            a << str;
        }
    }

    a.close();
    b.close();
}

void PauseScreen()
{
    cout << "\n\n";
    system("pause");
}

void FullScreen()
{
    // Down Keys Alt + Enter
    keybd_event(VK_MENU, 0, 0, 0);
    keybd_event(VK_RETURN, 0, 0, 0);

    // Up Keys Alt + Enter
    keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
}

void gotoxy(short x, short y)
{
    static HANDLE h = NULL;
    if (!h)
    {
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}

void Border(short **GridMap)
{
    Wall WL1, WL2, WL3, WL4;

    // Upper Wall
    WL1.yPos = 0;
    for (int i = 0; i <= SizeOfMapX; i++)
    {
        WL1.xPos = i;
        WL1.Print();
        GridMap[WL1.xPos][WL1.yPos] = 2;
    }

    // Right Wall
    WL2.xPos = SizeOfMapX;
    for (int j = 0; j <= SizeOfMapY; j++)
    {
        WL2.yPos = j;
        WL2.Print();
        GridMap[WL2.xPos][WL2.yPos] = 2;
    }

    // Lower Wall
    WL1.yPos = SizeOfMapY;
    for (int i = 0; i <= SizeOfMapX; i++)
    {
        WL1.xPos = i;
        WL1.Print();
        GridMap[WL1.xPos][WL1.yPos] = 2;
    }

    // Left Wall
    WL2.xPos = 0;
    for (int j = 0; j <= SizeOfMapY; j++)
    {
        WL2.yPos = j;
        WL2.Print();
        GridMap[WL2.xPos][WL2.yPos] = 2;
    }
}

Launcher Player()
{
    Wall WL1, WL2;
    Launcher P;

    WL1.xPos = PlayerPlace + 1;
    for (int j = SizeOfMapY; j >= SizeOfMapY - PlayerPlace + 1; j--)
    {
        WL1.yPos = j;
        WL1.Print();
    }

    WL2.yPos = SizeOfMapY - PlayerPlace;
    for (int i = 2; i <= (PlayerPlace) * 2; i++)
    {
        WL2.xPos = i;
        WL2.Print();
    }

    P.xPos = PlayerPlace * 2;
    P.yPos = SizeOfMapY - PlayerPlace - 1;
    P.Print();

    return P;
}

short Map1(short **GridMap1)
{
    Wall WL1, WL2, WL3;
    Enemy E1, E2, E3;

    WL1.xPos = SizeOfMapX * ((float)6 / 7);
    for (int j = SizeOfMapY; j >= SizeOfMapY * ((float)3 / 4); j--)
    {
        WL1.yPos = j;
        WL1.Print();
        GridMap1[WL1.xPos][WL1.yPos] = 1;
    }

    WL2.yPos = SizeOfMapY * ((float)3 / 4);
    for (int i = SizeOfMapX * ((float)6 / 7); i <= SizeOfMapX; i++)
    {
        WL2.xPos = i;
        WL2.Print();
        GridMap1[WL2.xPos][WL2.yPos] = 1;
    }

    WL3.yPos = SizeOfMapY / 4;
    for (int i = SizeOfMapX * ((float)6 / 7); i <= SizeOfMapX; i++)
    {
        WL3.xPos = i;
        WL3.Print();
        GridMap1[WL3.xPos][WL3.yPos] = 1;
    }

    /*
        SizeOfMapX * (6 / 7) + (SizeOfMapX * (1 / 7))/2 = SizeOfMapX * (13 / 14)
    */
    E1.xPos = SizeOfMapX * ((float)13 / 14);
    E1.yPos = (SizeOfMapY * ((float)3 / 4)) - 1;
    E1.Print();
    GridMap1[E1.xPos][E1.yPos] = 3;
    /*
        SizeOfMapX * (6 / 7) + (SizeOfMapX * (1 / 7))/3 = SizeOfMapX * (19 / 21)
    */
    E2.xPos = SizeOfMapX * ((float)19 / 21);
    E2.yPos = (SizeOfMapY * ((float)1 / 4)) - 1;
    E2.Print();
    GridMap1[E2.xPos][E2.yPos] = 3;
    /*
        SizeOfMapX * (6 / 7) + (SizeOfMapX * (1 / 7))*2/3 = SizeOfMapX * (20 / 21)
    */
    E3.xPos = SizeOfMapX * ((float)20 / 21);
    E3.yPos = (SizeOfMapY * ((float)1 / 4)) - 1;
    E3.Print();
    GridMap1[E3.xPos][E3.yPos] = 3;

    Border(GridMap1);
    Player();
    gotoxy(0, SizeOfMapY);
    cout << "\n\n";

    return 3;
}

short Map2(short **GridMap2)
{
    Wall WL1, WL2, WL3, WL4, WL5, WL6;
    Enemy E1, E2, E3;

    WL1.xPos = SizeOfMapX * ((float)3 / 5);
    for (int j = SizeOfMapY; j >= (SizeOfMapY / 1.6); j--)
    {
        WL1.yPos = j;
        WL1.Print();
        GridMap2[WL1.xPos][WL1.yPos] = 1;
    }

    WL2.yPos = SizeOfMapY / 1.6;
    for (int i = SizeOfMapX * ((float)3 / 5); i <= SizeOfMapX; i++)
    {
        WL2.xPos = i;
        WL2.Print();
        GridMap2[WL2.xPos][WL2.yPos] = 1;
    }

    /*
        SizeOfMapX * (3 / 5) + (SizeOfMapX * (2 / 5))/2 = SizeOfMapX * (4 / 5)
    */
    WL3.xPos = (SizeOfMapX * ((float)4 / 5));
    for (int j = SizeOfMapY / 1.6; j >= SizeOfMapY / 2.4; j--)
    {
        WL3.yPos = j;
        WL3.Print();
        GridMap2[WL3.xPos][WL3.yPos] = 1;
    }

    WL4.yPos = SizeOfMapY / 2.4;
    for (int i = (SizeOfMapX * ((float)4 / 5)); i <= SizeOfMapX; i++)
    {
        WL4.xPos = i;
        WL4.Print();
        GridMap2[WL4.xPos][WL4.yPos] = 1;
    }

    /*
        SizeOfMapX * (4 / 5) + (SizeOfMapX * (1 / 5))/2 = SizeOfMapX * (9 / 10)
    */
    WL5.xPos = SizeOfMapX * ((float)9 / 10);
    for (int j = SizeOfMapY / 2.4; j >= SizeOfMapY / 4; j--)
    {
        WL5.yPos = j;
        WL5.Print();
        GridMap2[WL5.xPos][WL5.yPos] = 1;
    }

    WL6.yPos = SizeOfMapY / 4;
    for (int i = SizeOfMapX * ((float)9 / 10); i <= SizeOfMapX; i++)
    {
        WL6.xPos = i;
        WL6.Print();
        GridMap2[WL6.xPos][WL6.yPos] = 1;
    }

    /*
        SizeOfMapX * (3 / 5) + (SizeOfMapX * (2 / 5))/4 = SizeOfMapX * (7 / 10)
    */
    E1.xPos = (SizeOfMapX * ((float)7 / 10));
    E1.yPos = (SizeOfMapY / 1.6) - 1;
    E1.Print();
    GridMap2[E1.xPos][E1.yPos] = 3;
    /*
        SizeOfMapX * (4 / 5) + (SizeOfMapX * (1 / 5))/4 = SizeOfMapX * (17 / 20)
    */
    E2.xPos = (SizeOfMapX * ((float)17 / 20));
    E2.yPos = (SizeOfMapY / 2.4) - 1;
    E2.Print();
    GridMap2[E2.xPos][E2.yPos] = 3;
    /*
        SizeOfMapX * (9 / 10) + (SizeOfMapX * (1 / 10))/2 = SizeOfMapX * (19 / 20)
    */
    E3.xPos = (SizeOfMapX * ((float)19 / 20));
    E3.yPos = (SizeOfMapY / 4) - 1;
    E3.Print();
    GridMap2[E3.xPos][E3.yPos] = 3;

    Border(GridMap2);
    Player();
    gotoxy(0, SizeOfMapY);
    cout << "\n\n";

    return 3;
}

short Map3(short **GridMap3)
{
    Wall WL1, WL2, WL3, WL4, WL5;
    Enemy E1, E2, E3, E4, E5;

    WL1.xPos = SizeOfMapX * ((float)2 / 3);
    for (int j = SizeOfMapY; j >= SizeOfMapY * ((float)5 / 6); j--)
    {
        WL1.yPos = j;
        WL1.Print();
        GridMap3[WL1.xPos][WL1.yPos] = 1;
    }

    /*
        SizeOfMapX * (2 / 3) + SizeOfMapX * (1 / 6) = SizeOfMapX * (5 / 6)
    */
    WL2.xPos = SizeOfMapX * ((float)5 / 6);
    for (int j = SizeOfMapY * ((float)5 / 6); j >= SizeOfMapY * ((float)2 / 6); j--)
    {
        WL2.yPos = j;
        WL2.Print();
        GridMap3[WL2.xPos][WL2.yPos] = 1;
    }

    WL3.yPos = SizeOfMapY * ((float)5 / 6);
    for (int i = SizeOfMapX * ((float)2 / 3); i <= SizeOfMapX * ((float)5 / 6); i++)
    {
        WL3.xPos = i;
        WL3.Print();
        GridMap3[WL3.xPos][WL3.yPos] = 1;
    }

    /*
        SizeOfMapX * (2 / 3) - SizeOfMapX * (1 / 6) = SizeOfMapX * (3 / 6)
    */
    WL4.yPos = SizeOfMapY * ((float)7 / 12);
    for (int i = SizeOfMapX * ((float)5 / 6); i >= SizeOfMapX * ((float)3 / 6); i--)
    {
        WL4.xPos = i;
        WL4.Print();
        GridMap3[WL4.xPos][WL4.yPos] = 1;
    }

    /*
        SizeOfMapX * (2 / 3) - SizeOfMapX * (1 / 12) = SizeOfMapX * (7 / 12)
    */
    WL5.yPos = SizeOfMapY * ((float)2 / 6);
    for (int i = SizeOfMapX * ((float)5 / 6); i >= SizeOfMapX * ((float)7 / 12); i--)
    {
        WL5.xPos = i;
        WL5.Print();
        GridMap3[WL5.xPos][WL5.yPos] = 1;
    }

    /*
        SizeOfMapX * (2 / 3) + SizeOfMapX * (1 / 12) = SizeOfMapX * (9 / 12)
    */
    E1.xPos = (SizeOfMapX * ((float)9 / 12));
    E1.yPos = SizeOfMapY * ((float)5 / 6) - 1;
    E1.Print();
    GridMap3[E1.xPos][E1.yPos] = 3;
    /*
        SizeOfMapX * (2 / 3) - SizeOfMapX * (1 / 12) = SizeOfMapX * (7 / 12)
    */
    E2.xPos = (SizeOfMapX * ((float)7 / 12));
    E2.yPos = SizeOfMapY * ((float)7 / 12) - 1;
    E2.Print();
    GridMap3[E2.xPos][E2.yPos] = 3;
    /*
        SizeOfMapX * (2 / 3) = SizeOfMapX * (8 / 12)
    */
    E3.xPos = (SizeOfMapX * ((float)8 / 12));
    E3.yPos = SizeOfMapY * ((float)7 / 12) - 1;
    E3.Print();
    GridMap3[E3.xPos][E3.yPos] = 3;
    /*
        SizeOfMapX * (2 / 3) + SizeOfMapX * (1 / 12) = SizeOfMapX * (9 / 12)
    */
    E4.xPos = (SizeOfMapX * ((float)9 / 12));
    E4.yPos = SizeOfMapY * ((float)7 / 12) - 1;
    E4.Print();
    GridMap3[E4.xPos][E4.yPos] = 3;
    /*
        SizeOfMapX * (7 / 12) + (SizeOfMapX * (3 / 12))/2 = SizeOfMapX * (17 / 24)
    */
    E5.xPos = (SizeOfMapX * ((float)17 / 24));
    E5.yPos = SizeOfMapY * ((float)2 / 6) - 1;
    E5.Print();
    GridMap3[E5.xPos][E5.yPos] = 3;

    Border(GridMap3);
    Player();
    gotoxy(0, SizeOfMapY);
    cout << "\n\n";

    return 5;
}

short Map4(short **GridMap4)
{
    Wall WL1, WL2, WL3, WL4, WL5, WL6;
    Enemy E1, E2, E3, E4, E5;

    WL1.xPos = SizeOfMapX * ((float)2 / 3);
    for (int j = SizeOfMapY; j >= SizeOfMapY * ((float)6 / 8); j--)
    {
        WL1.yPos = j;
        WL1.Print();
        GridMap4[WL1.xPos][WL1.yPos] = 1;
    }

    WL2.xPos = SizeOfMapX * ((float)5 / 6);
    for (int j = SizeOfMapY; j >= SizeOfMapY * ((float)6 / 8); j--)
    {
        WL2.yPos = j;
        WL2.Print();
        GridMap4[WL2.xPos][WL2.yPos] = 1;
    }

    WL3.yPos = SizeOfMapY * ((float)6 / 8);
    for (int i = SizeOfMapX * ((float)2 / 3); i <= SizeOfMapX * ((float)5 / 6); i++)
    {
        WL3.xPos = i;
        WL3.Print();
        GridMap4[WL3.xPos][WL3.yPos] = 1;
    }

    WL4.yPos = SizeOfMapY * ((float)1 / 8);
    for (int i = SizeOfMapX; i >= SizeOfMapX * ((float)9 / 12); i--)
    {
        WL4.xPos = i;
        WL4.Print();
        GridMap4[WL4.xPos][WL4.yPos] = 1;
    }

    WL5.yPos = SizeOfMapY * ((float)3 / 8);
    for (int i = SizeOfMapX * ((float)9 / 12); i <= SizeOfMapX * ((float)11 / 12); i++)
    {
        WL5.xPos = i;
        WL5.Print();
        GridMap4[WL5.xPos][WL5.yPos] = 1;
    }

    WL6.xPos = SizeOfMapX * ((float)9 / 12);
    for (int j = SizeOfMapY * ((float)1 / 8); j <= SizeOfMapY * ((float)3 / 8); j++)
    {
        WL6.yPos = j;
        WL6.Print();
        GridMap4[WL6.xPos][WL6.yPos] = 1;
    }

    /*
        SizeOfMapX * (2 / 3) + SizeOfMapX * (1 / 18) = SizeOfMapX * (13 / 18)
    */
    E1.xPos = (SizeOfMapX * ((float)13 / 18));
    E1.yPos = SizeOfMapY * ((float)6 / 8) - 1;
    E1.Print();
    GridMap4[E1.xPos][E1.yPos] = 3;
    /*
        SizeOfMapX * (13 / 18) + SizeOfMapX * (1 / 18) = SizeOfMapX * (14 / 18)
    */
    E2.xPos = (SizeOfMapX * ((float)14 / 18));
    E2.yPos = SizeOfMapY * ((float)6 / 8) - 1;
    E2.Print();
    GridMap4[E2.xPos][E2.yPos] = 3;
    /*
        SizeOfMapX * (2 / 3) + SizeOfMapX * (1 / 12) = SizeOfMapX * (9 / 12)
    */
    E3.xPos = (SizeOfMapX * ((float)9 / 12));
    E3.yPos = SizeOfMapY - 1;
    E3.Print();
    GridMap4[E3.xPos][E3.yPos] = 3;
    /*
        SizeOfMapX * (9 / 12) + (SizeOfMapX * (3 / 12))/2 = SizeOfMapX * (7 / 8)
    */
    E4.xPos = (SizeOfMapX * ((float)7 / 8));
    E4.yPos = SizeOfMapY * ((float)1 / 8) - 1;
    E4.Print();
    GridMap4[E4.xPos][E4.yPos] = 3;
    /*
        SizeOfMapX * (9 / 12) + (SizeOfMapX * (2 / 12))/2 = SizeOfMapX * (10 / 12)
    */
    E5.xPos = (SizeOfMapX * ((float)10 / 12));
    E5.yPos = SizeOfMapY * ((float)3 / 8) - 1;
    E5.Print();
    GridMap4[E5.xPos][E5.yPos] = 3;

    Border(GridMap4);
    Player();
    gotoxy(0, SizeOfMapY);
    cout << "\n\n";

    return 5;
}

short Map5(short **GridMap5)
{
    Wall WL1, WL2, WL3, WL4, WL5, WL6, WL7, WL8;
    Enemy E1, E2, E3, E4, E5, E6, E7;

    WL1.xPos = SizeOfMapX * ((float)2 / 5);
    for (int j = SizeOfMapY; j >= SizeOfMapY * ((float)3 / 4); j--)
    {
        WL1.yPos = j;
        WL1.Print();
        GridMap5[WL1.xPos][WL1.yPos] = 1;
    }

    /*
        SizeOfMapX * (2 / 5) + (SizeOfMapX * (3 / 5))*(2 / 5) = SizeOfMapX * (16 / 25)
    */
    WL2.xPos = SizeOfMapX * ((float)16 / 25);
    for (int j = SizeOfMapY; j >= SizeOfMapY * ((float)2 / 4); j--)
    {
        WL2.yPos = j;
        WL2.Print();
        GridMap5[WL2.xPos][WL2.yPos] = 1;
    }

    /*
        SizeOfMapX * (2 / 5) + (SizeOfMapX * (3 / 5))*(3 / 5) = SizeOfMapX * (19 / 25)
    */
    WL3.xPos = SizeOfMapX * ((float)19 / 25);
    for (int j = SizeOfMapY; j >= SizeOfMapY * ((float)2 / 4); j--)
    {
        WL3.yPos = j;
        WL3.Print();
        GridMap5[WL3.xPos][WL3.yPos] = 1;
    }

    WL4.yPos = SizeOfMapY * ((float)3 / 4);
    for (int i = SizeOfMapX * ((float)2 / 5); i <= SizeOfMapX * ((float)16 / 25); i++)
    {
        WL4.xPos = i;
        WL4.Print();
        GridMap5[WL4.xPos][WL4.yPos] = 1;
    }

    WL5.yPos = SizeOfMapY * ((float)2 / 4);
    for (int i = SizeOfMapX * ((float)16 / 25); i <= SizeOfMapX * ((float)19 / 25); i++)
    {
        WL5.xPos = i;
        WL5.Print();
        GridMap5[WL5.xPos][WL5.yPos] = 1;
    }

    WL6.yPos = SizeOfMapY * ((float)3 / 4);
    for (int i = SizeOfMapX * ((float)19 / 25); i <= SizeOfMapX; i++)
    {
        WL6.xPos = i;
        WL6.Print();
        GridMap5[WL6.xPos][WL6.yPos] = 1;
    }

    /*
        SizeOfMapX * (19 / 25) + (SizeOfMapX * (3 / 25))/2 = SizeOfMapX * (41 / 50)
    */
    WL7.xPos = SizeOfMapX * ((float)41 / 50);
    for (int j = 0; j <= SizeOfMapY * ((float)1 / 4); j++)
    {
        WL7.yPos = j;
        WL7.Print();
        GridMap5[WL7.xPos][WL7.yPos] = 1;
    }

    WL8.yPos = SizeOfMapY * ((float)1 / 4);
    for (int i = SizeOfMapX * ((float)41 / 50); i <= SizeOfMapX; i++)
    {
        WL8.xPos = i;
        WL8.Print();
        GridMap5[WL8.xPos][WL8.yPos] = 1;
    }

    /*
        SizeOfMapX * (2 / 5) + SizeOfMapX * (6 / 25)/2 = SizeOfMapX * (13 / 25)
    */
    E1.xPos = (SizeOfMapX * ((float)13 / 25));
    E1.yPos = SizeOfMapY - 1;
    E1.Print();
    GridMap5[E1.xPos][E1.yPos] = 3;

    E2.xPos = (SizeOfMapX * ((float)13 / 25));
    E2.yPos = SizeOfMapY * ((float)3 / 4) - 1;
    E2.Print();
    GridMap5[E2.xPos][E2.yPos] = 3;
    /*
        SizeOfMapX * (16 / 25) + SizeOfMapX * (3 / 25)/2 = SizeOfMapX * (35 / 50)
    */
    E3.xPos = (SizeOfMapX * ((float)35 / 50));
    E3.yPos = SizeOfMapY - 1;
    E3.Print();
    GridMap5[E3.xPos][E3.yPos] = 3;

    E4.xPos = (SizeOfMapX * ((float)35 / 50));
    E4.yPos = SizeOfMapY * ((float)2 / 4) - 1;
    E4.Print();
    GridMap5[E4.xPos][E4.yPos] = 3;
    /*
        SizeOfMapX * (19 / 25) + SizeOfMapX * (6 / 25)/2 = SizeOfMapX * (22 / 25)
    */
    E5.xPos = (SizeOfMapX * ((float)22 / 25));
    E5.yPos = SizeOfMapY - 1;
    E5.Print();
    GridMap5[E5.xPos][E5.yPos] = 3;

    E6.xPos = (SizeOfMapX * ((float)22 / 25));
    E6.yPos = SizeOfMapY * ((float)3 / 4) - 1;
    E6.Print();
    GridMap5[E6.xPos][E6.yPos] = 3;
    /*
        SizeOfMapX * (41 / 50) + SizeOfMapX * (9 / 50)/2 = SizeOfMapX * (91 / 100)
    */
    E7.xPos = (SizeOfMapX * ((float)91 / 100));
    E7.yPos = SizeOfMapY * ((float)1 / 4) - 1;
    E7.Print();
    GridMap5[E7.xPos][E7.yPos] = 3;

    Border(GridMap5);
    Player();
    gotoxy(0, SizeOfMapY);
    cout << "\n\n";

    return 7;
}

short Map6(short **GridMap6)
{
    Wall WL1, WL2, WL3, WL4, WL5, WL6, WL7, WL8, WL9, WL10, WL11, WL12;
    Enemy E1, E2, E3, E4, E5, E6, E7, E8;

    WL1.xPos = SizeOfMapX * ((float)6 / 10);
    for (int j = SizeOfMapY; j >= SizeOfMapY * ((float)8 / 10); j--)
    {
        WL1.yPos = j;
        WL1.Print();
        GridMap6[WL1.xPos][WL1.yPos] = 1;
    }

    WL2.xPos = SizeOfMapX * ((float)8 / 10);
    for (int j = SizeOfMapY; j >= SizeOfMapY * ((float)8 / 10); j--)
    {
        WL2.yPos = j;
        WL2.Print();
        GridMap6[WL2.xPos][WL2.yPos] = 1;
    }

    WL3.xPos = SizeOfMapX * ((float)7 / 10);
    for (int j = SizeOfMapY * ((float)8 / 10); j >= SizeOfMapY * ((float)5 / 10); j--)
    {
        WL3.yPos = j;
        WL3.Print();
        GridMap6[WL3.xPos][WL3.yPos] = 1;
    }

    WL4.xPos = SizeOfMapX * ((float)5 / 10);
    for (int j = SizeOfMapY * ((float)15 / 20); j >= SizeOfMapY * ((float)6 / 10); j--)
    {
        WL4.yPos = j;
        WL4.Print();
        GridMap6[WL4.xPos][WL4.yPos] = 1;
    }

    WL5.xPos = SizeOfMapX * ((float)9 / 10);
    for (int j = SizeOfMapY * ((float)15 / 20); j >= SizeOfMapY * ((float)6 / 10); j--)
    {
        WL5.yPos = j;
        WL5.Print();
        GridMap6[WL5.xPos][WL5.yPos] = 1;
    }

    WL6.xPos = SizeOfMapX * ((float)6 / 10);
    for (int j = SizeOfMapY * ((float)5 / 10); j >= SizeOfMapY * ((float)3 / 10); j--)
    {
        WL6.yPos = j;
        WL6.Print();
        GridMap6[WL6.xPos][WL6.yPos] = 1;
    }

    WL7.xPos = SizeOfMapX * ((float)8 / 10);
    for (int j = SizeOfMapY * ((float)5 / 10); j >= SizeOfMapY * ((float)3 / 10); j--)
    {
        WL7.yPos = j;
        WL7.Print();
        GridMap6[WL7.xPos][WL7.yPos] = 1;
    }

    WL8.yPos = SizeOfMapY * ((float)8 / 10);
    for (int i = SizeOfMapX * ((float)6 / 10); i <= SizeOfMapX * ((float)8 / 10); i++)
    {
        WL8.xPos = i;
        WL8.Print();
        GridMap6[WL8.xPos][WL8.yPos] = 1;
    }

    WL9.yPos = SizeOfMapY * ((float)6 / 10);
    for (int i = SizeOfMapX * ((float)5 / 10); i <= SizeOfMapX * ((float)9 / 10); i++)
    {
        WL9.xPos = i;
        WL9.Print();
        GridMap6[WL9.xPos][WL9.yPos] = 1;
    }

    WL10.yPos = SizeOfMapY * ((float)5 / 10);
    for (int i = SizeOfMapX * ((float)6 / 10); i <= SizeOfMapX * ((float)8 / 10); i++)
    {
        WL10.xPos = i;
        WL10.Print();
        GridMap6[WL10.xPos][WL10.yPos] = 1;
    }

    WL11.yPos = SizeOfMapY * ((float)3 / 10);
    for (int i = SizeOfMapX * ((float)6 / 10); i <= SizeOfMapX * ((float)8 / 10); i++)
    {
        WL11.xPos = i;
        WL11.Print();
        GridMap6[WL11.xPos][WL11.yPos] = 1;
    }

    WL12.yPos = SizeOfMapY * ((float)15 / 20);
    for (int i = SizeOfMapX * ((float)4 / 10); i <= SizeOfMapX * ((float)5 / 10); i++)
    {
        WL12.xPos = i;
        WL12.Print();
        GridMap6[WL12.xPos][WL12.yPos] = 1;
    }

    /*
        SizeOfMapX * (6 / 10) + SizeOfMapX * (1 / 10)/2 = SizeOfMapX * (13 / 20)
    */
    E1.xPos = (SizeOfMapX * ((float)13 / 20));
    E1.yPos = SizeOfMapY * ((float)8 / 10) - 1;
    E1.Print();
    GridMap6[E1.xPos][E1.yPos] = 3;
    /*
        SizeOfMapX * (7 / 10) + SizeOfMapX * (1 / 10)/2 = SizeOfMapX * (15 / 20)
    */
    E2.xPos = (SizeOfMapX * ((float)15 / 20));
    E2.yPos = SizeOfMapY * ((float)8 / 10) - 1;
    E2.Print();
    GridMap6[E2.xPos][E2.yPos] = 3;
    /*
        SizeOfMapX * (4 / 10) + SizeOfMapX * (1 / 10)/3 = SizeOfMapX * (13 / 30)
    */
    E3.xPos = (SizeOfMapX * ((float)13 / 30));
    E3.yPos = SizeOfMapY * ((float)15 / 20) - 1;
    E3.Print();
    GridMap6[E3.xPos][E3.yPos] = 3;
    /*
        SizeOfMapX * (5 / 10) + SizeOfMapX * (2 / 10)/2 = SizeOfMapX * (6 / 10)
    */
    E4.xPos = (SizeOfMapX * ((float)6 / 10)) - 2;
    E4.yPos = SizeOfMapY * ((float)6 / 10) - 1;
    E4.Print();
    GridMap6[E4.xPos][E4.yPos] = 3;
    /*
        SizeOfMapX * (7 / 10) + SizeOfMapX * (2 / 10)/2 = SizeOfMapX * (8 / 10)
    */
    E5.xPos = (SizeOfMapX * ((float)8 / 10)) + 2;
    E5.yPos = SizeOfMapY * ((float)6 / 10) - 1;
    E5.Print();
    GridMap6[E5.xPos][E5.yPos] = 3;
    /*
        SizeOfMapX * (7 / 10)
    */
    E6.xPos = (SizeOfMapX * ((float)7 / 10));
    E6.yPos = SizeOfMapY * ((float)5 / 10) - 1;
    E6.Print();
    GridMap6[E6.xPos][E6.yPos] = 3;
    /*
        SizeOfMapX * (6 / 10) + SizeOfMapX * (1 / 10)/2 = SizeOfMapX * (13 / 20)
    */
    E7.xPos = (SizeOfMapX * ((float)13 / 20)) - 2;
    E7.yPos = SizeOfMapY * ((float)3 / 10) - 1;
    E7.Print();
    GridMap6[E7.xPos][E7.yPos] = 3;
    /*
        SizeOfMapX * (7 / 10) + SizeOfMapX * (1 / 10)/2 = SizeOfMapX * (15 / 20)
    */
    E8.xPos = (SizeOfMapX * ((float)15 / 20)) + 2;
    E8.yPos = SizeOfMapY * ((float)3 / 10) - 1;
    E8.Print();
    GridMap6[E8.xPos][E8.yPos] = 3;

    Border(GridMap6);
    Player();
    gotoxy(0, SizeOfMapY);
    cout << "\n\n";

    return 8;
}

void NormalShot(short &CounterEnemy, short &CounterWall, short **GridMap)
{
    short x1, y1;
    double Angle, Speed;
    double vx, vy, ay;

    ClearArea(10, 100, 0, SizeOfMapY + 1);
    gotoxy(0, SizeOfMapY);
    cout << "\n\n";

    cout << " -> Normal Shot\n\n";

    if (TypeOfInputs == 1)
    {
        cout << "Speed : ";
        cin >> Speed;
        cout << "Angle : ";
        cin >> Angle;
        Angle = Angle * M_PI / 180;

        vx = Speed * cos(Angle);
        vy = Speed * sin(Angle);
        ay = 1;
    }
    else if (TypeOfInputs == 2)
    {
        cout << "Speed x : ";
        cin >> vx;
        cout << "Speed y : ";
        cin >> vy;
        cout << "ay : ";
        cin >> ay;
    }

    Launcher P = Player();
    Projectile Bullet;
    Bullet.xPos = P.xPos;
    Bullet.yPos = P.yPos;
    Bullet.PreviousxPos = Bullet.xPos;
    Bullet.PreviousyPos = Bullet.yPos;
    Projectile TempBullet;
    TempBullet.xPos = Bullet.xPos;
    TempBullet.yPos = Bullet.yPos;
    TempBullet.PreviousxPos = TempBullet.xPos;
    TempBullet.PreviousyPos = TempBullet.yPos;

    // normal shot
    bool IsHit = false;
    if (HowToMoveBullet == 1)
    {
        char PressKey;
        while (true)
        {
            PressKey = getch();
            if (PressKey == 13)
            {
                if (Bullet.xPos > SizeOfMapX || Bullet.yPos > SizeOfMapY)
                {
                    IsHit = true;
                }
                else
                {
                    Bullet.DeletePrevious();
                    Bullet.PreviousxPos = Bullet.xPos;
                    Bullet.PreviousyPos = Bullet.yPos;
                    TempBullet.DeletePrevious();
                    TempBullet.PreviousxPos = TempBullet.xPos;
                    TempBullet.PreviousyPos = TempBullet.yPos;
                    Bullet.Print();
                    if (GridMap[Bullet.xPos][Bullet.yPos] != 0)
                    {
                        IsHit = true;
                        if (GridMap[Bullet.xPos][Bullet.yPos] == 1)
                        {
                            CounterWall++;
                        }
                        else if (GridMap[Bullet.xPos][Bullet.yPos] == 3)
                        {
                            CounterEnemy++;
                        }
                        GridMap[Bullet.xPos][Bullet.yPos] = 0;
                    }
                }

                if (IsHit)
                {
                    Bullet.DeletePrevious();
                    Bullet.PreviousxPos = Bullet.xPos;
                    Bullet.PreviousyPos = Bullet.yPos;
                    TempBullet.DeletePrevious();
                    TempBullet.PreviousxPos = TempBullet.xPos;
                    TempBullet.PreviousyPos = TempBullet.yPos;
                    break;
                }

                /*
                    Line Equation ----> [m = -vy/vx] & [y = m(x-x1) + y1] & [x = (y-y1)/m + x1]
                    Value Of Initial TempBullet & Bullet ----> نقطه عقبی
                    Bullet + (short)v ----> نقطه جلویی
                    Bulletx + (short)vx - 1 ---->  یک نقطه قبل از نقطه جلویی
                    Bullety + (short)vy + 1 ---->  یک نقطه پایین تر از نقطه جلویی (زمانی که رو به بالا حرکت میکنه گلوله)
                    Bullety + (short)vy - 1 ---->  یک نقطه بالا تر از نقطه جلویی (زمانی که رو به پایین حرکت میکنه گلوله)
                    TempBullet ----> نقاط بین نقطه عقبی و جلویی
                    vy > 0 ----> حرکت رو به بالا
                    vy < 0 ----> حرکت رو به پایین
                */

                double m = -vy / vx;
                x1 = TempBullet.xPos;
                y1 = TempBullet.yPos;

                if (abs((short)vx) > abs((short)vy))
                {
                    while (TempBullet.xPos != Bullet.xPos + (short)vx - 1)
                    {
                        PressKey = getch();
                        if (PressKey == 13)
                        {
                            TempBullet.xPos++;
                            TempBullet.yPos = m * (TempBullet.xPos - x1) + y1;

                            if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                            {
                                IsHit = true;
                            }
                            else
                            {
                                Bullet.DeletePrevious();
                                Bullet.PreviousxPos = Bullet.xPos;
                                Bullet.PreviousyPos = Bullet.yPos;
                                TempBullet.DeletePrevious();
                                TempBullet.PreviousxPos = TempBullet.xPos;
                                TempBullet.PreviousyPos = TempBullet.yPos;
                                TempBullet.Print();
                                if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                                {
                                    IsHit = true;
                                    if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                    {
                                        CounterWall++;
                                    }
                                    else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                    {
                                        CounterEnemy++;
                                    }
                                    GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                                }
                            }

                            if (IsHit)
                            {
                                Bullet.DeletePrevious();
                                Bullet.PreviousxPos = Bullet.xPos;
                                Bullet.PreviousyPos = Bullet.yPos;
                                TempBullet.DeletePrevious();
                                TempBullet.PreviousxPos = TempBullet.xPos;
                                TempBullet.PreviousyPos = TempBullet.yPos;
                                break;
                            }
                        }
                        else if ((PressKey == ExitKeyInGameL) || (PressKey == ExitKeyInGameS))
                        {
                            CounterEnemy = -1;
                            return;
                        }
                    }
                }
                else if (abs((short)vx) <= abs((short)vy))
                {
                    if (vy > 0)
                    {
                        while (TempBullet.yPos != Bullet.yPos - (short)vy)
                        {
                            PressKey = getch();
                            if (PressKey == 13)
                            {
                                if ((m < 0.5 && m > -0.5) && (Angle * 180 / M_PI > 75))
                                {
                                    break;
                                }

                                TempBullet.yPos--;
                                TempBullet.xPos = (TempBullet.yPos - y1) / m + x1;

                                if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                                {
                                    IsHit = true;
                                }
                                else
                                {
                                    Bullet.DeletePrevious();
                                    Bullet.PreviousxPos = Bullet.xPos;
                                    Bullet.PreviousyPos = Bullet.yPos;
                                    TempBullet.DeletePrevious();
                                    TempBullet.PreviousxPos = TempBullet.xPos;
                                    TempBullet.PreviousyPos = TempBullet.yPos;
                                    TempBullet.Print();
                                    if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                                    {
                                        IsHit = true;
                                        if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                        {
                                            CounterWall++;
                                        }
                                        else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                        {
                                            CounterEnemy++;
                                        }
                                        GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                                    }
                                }

                                if (IsHit)
                                {
                                    Bullet.DeletePrevious();
                                    Bullet.PreviousxPos = Bullet.xPos;
                                    Bullet.PreviousyPos = Bullet.yPos;
                                    TempBullet.DeletePrevious();
                                    TempBullet.PreviousxPos = TempBullet.xPos;
                                    TempBullet.PreviousyPos = TempBullet.yPos;
                                    break;
                                }
                            }
                            else if ((PressKey == ExitKeyInGameL) || (PressKey == ExitKeyInGameS))
                            {
                                CounterEnemy = -1;
                                return;
                            }
                        }
                    }
                    else if (vy < 0)
                    {
                        while (TempBullet.yPos != Bullet.yPos - (short)vy - 1)
                        {
                            PressKey = getch();
                            if (PressKey == 13)
                            {
                                if ((m < 0.5 && m > -0.5) && (Angle * 180 / M_PI > 75))
                                {
                                    break;
                                }

                                TempBullet.yPos++;
                                TempBullet.xPos = (TempBullet.yPos - y1) / m + x1;

                                if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                                {
                                    IsHit = true;
                                }
                                else
                                {
                                    Bullet.DeletePrevious();
                                    Bullet.PreviousxPos = Bullet.xPos;
                                    Bullet.PreviousyPos = Bullet.yPos;
                                    TempBullet.DeletePrevious();
                                    TempBullet.PreviousxPos = TempBullet.xPos;
                                    TempBullet.PreviousyPos = TempBullet.yPos;
                                    TempBullet.Print();
                                    if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                                    {
                                        IsHit = true;
                                        if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                        {
                                            CounterWall++;
                                        }
                                        else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                        {
                                            CounterEnemy++;
                                        }
                                        GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                                    }
                                }

                                if (IsHit)
                                {
                                    Bullet.DeletePrevious();
                                    Bullet.PreviousxPos = Bullet.xPos;
                                    Bullet.PreviousyPos = Bullet.yPos;
                                    TempBullet.DeletePrevious();
                                    TempBullet.PreviousxPos = TempBullet.xPos;
                                    TempBullet.PreviousyPos = TempBullet.yPos;
                                    break;
                                }
                            }
                            else if ((PressKey == ExitKeyInGameL) || (PressKey == ExitKeyInGameS))
                            {
                                CounterEnemy = -1;
                                return;
                            }
                        }
                    }
                }

                if (IsHit)
                {
                    Bullet.DeletePrevious();
                    Bullet.PreviousxPos = Bullet.xPos;
                    Bullet.PreviousyPos = Bullet.yPos;
                    TempBullet.DeletePrevious();
                    TempBullet.PreviousxPos = TempBullet.xPos;
                    TempBullet.PreviousyPos = TempBullet.yPos;
                    break;
                }

                Bullet.xPos = Bullet.xPos + vx;
                Bullet.yPos = Bullet.yPos - vy;
                vy -= ay;

                TempBullet.xPos = Bullet.xPos;
                TempBullet.yPos = Bullet.yPos;
            }
            else if ((PressKey == ExitKeyInGameL) || (PressKey == ExitKeyInGameS))
            {
                CounterEnemy = -1;
                return;
            }
        }
    }
    else if (HowToMoveBullet == 2)
    {
        while (true)
        {
            if ((GetAsyncKeyState(ExitKeyInGameL) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameL) & 0x0001) ||
                (GetAsyncKeyState(ExitKeyInGameS) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameS) & 0x0001))
            {
                getch();
                CounterEnemy = -1;
                return;
            }
            if (Bullet.xPos > SizeOfMapX || Bullet.yPos > SizeOfMapY)
            {
                IsHit = true;
            }
            else
            {
                Bullet.Print();
                if (GridMap[Bullet.xPos][Bullet.yPos] != 0)
                {

                    IsHit = true;
                    if (GridMap[Bullet.xPos][Bullet.yPos] == 1)
                    {
                        CounterWall++;
                    }
                    else if (GridMap[Bullet.xPos][Bullet.yPos] == 3)
                    {
                        CounterEnemy++;
                    }
                    GridMap[Bullet.xPos][Bullet.yPos] = 0;
                }
            }

            Sleep(SleepTimeGame);

            Bullet.Delete();

            if (IsHit)
            {
                break;
            }

            /*
                Line Equation ----> [m = -vy/vx] & [y = m(x-x1) + y1] & [x = (y-y1)/m + x1]
                Value Of Initial TempBullet & Bullet ----> نقطه عقبی
                Bullet + (short)v ----> نقطه جلویی
                Bulletx + (short)vx - 1 ---->  یک نقطه قبل از نقطه جلویی
                Bullety + (short)vy + 1 ---->  یک نقطه پایین تر از نقطه جلویی (زمانی که رو به بالا حرکت میکنه گلوله)
                Bullety + (short)vy - 1 ---->  یک نقطه بالا تر از نقطه جلویی (زمانی که رو به پایین حرکت میکنه گلوله)
                TempBullet ----> نقاط بین نقطه عقبی و جلویی
                vy > 0 ----> حرکت رو به بالا
                vy < 0 ----> حرکت رو به پایین
            */

            double m = -vy / vx;
            x1 = TempBullet.xPos;
            y1 = TempBullet.yPos;

            if (abs((short)vx) > abs((short)vy))
            {
                while (TempBullet.xPos != Bullet.xPos + (short)vx - 1)
                {
                    if ((GetAsyncKeyState(ExitKeyInGameL) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameL) & 0x0001) ||
                        (GetAsyncKeyState(ExitKeyInGameS) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameS) & 0x0001))
                    {
                        getch();
                        CounterEnemy = -1;
                        return;
                    }
                    TempBullet.xPos++;
                    TempBullet.yPos = m * (TempBullet.xPos - x1) + y1;

                    if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                    {
                        IsHit = true;
                    }
                    else
                    {
                        TempBullet.Print();
                        if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                        {
                            IsHit = true;
                            if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                            {
                                CounterWall++;
                            }
                            else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                            {
                                CounterEnemy++;
                            }
                            GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                        }
                    }
                    Sleep(SleepTimeGame);

                    TempBullet.Delete();

                    if (IsHit)
                    {
                        break;
                    }
                }
            }
            else if (abs((short)vx) <= abs((short)vy))
            {
                if (vy > 0)
                {
                    while (TempBullet.yPos != Bullet.yPos - (short)vy)
                    {
                        if ((GetAsyncKeyState(ExitKeyInGameL) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameL) & 0x0001) ||
                            (GetAsyncKeyState(ExitKeyInGameS) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameS) & 0x0001))
                        {
                            getch();
                            CounterEnemy = -1;
                            return;
                        }
                        if ((m < 0.5 && m > -0.5) && (Angle * 180 / M_PI > 75))
                        {
                            break;
                        }

                        TempBullet.yPos--;
                        TempBullet.xPos = (TempBullet.yPos - y1) / m + x1;

                        if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                        {
                            IsHit = true;
                        }
                        else
                        {
                            TempBullet.Print();
                            if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                            {
                                IsHit = true;
                                if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                {
                                    CounterWall++;
                                }
                                else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                {
                                    CounterEnemy++;
                                }
                                GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                            }
                        }
                        Sleep(SleepTimeGame);

                        TempBullet.Delete();

                        if (IsHit)
                        {
                            break;
                        }
                    }
                }
                else if (vy < 0)
                {
                    while (TempBullet.yPos != Bullet.yPos - (short)vy - 1)
                    {
                        if ((GetAsyncKeyState(ExitKeyInGameL) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameL) & 0x0001) ||
                            (GetAsyncKeyState(ExitKeyInGameS) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameS) & 0x0001))
                        {
                            getch();
                            CounterEnemy = -1;
                            return;
                        }
                        if ((m < 0.5 && m > -0.5) && (Angle * 180 / M_PI > 75))
                        {
                            break;
                        }

                        TempBullet.yPos++;
                        TempBullet.xPos = (TempBullet.yPos - y1) / m + x1;

                        if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                        {
                            IsHit = true;
                        }
                        else
                        {
                            TempBullet.Print();
                            if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                            {
                                IsHit = true;
                                if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                {
                                    CounterWall++;
                                }
                                else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                {
                                    CounterEnemy++;
                                }
                                GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                            }
                        }
                        Sleep(SleepTimeGame);

                        TempBullet.Delete();

                        if (IsHit)
                        {
                            break;
                        }
                    }
                }
            }

            if (IsHit)
            {
                break;
            }

            Bullet.xPos = Bullet.xPos + vx;
            Bullet.yPos = Bullet.yPos - vy;
            vy -= ay;

            TempBullet.xPos = Bullet.xPos;
            TempBullet.yPos = Bullet.yPos;
        }
    }
    Border(GridMap);
}

void DropKickShot(short &CounterEnemy, short &CounterWall, short **GridMap)
{
    short x1, y1;
    double Angle, Speed;
    double vx, vy, ay;

    ClearArea(10, 100, 0, SizeOfMapY + 1);
    gotoxy(0, SizeOfMapY);
    cout << "\n\n";

    cout << " -> Drop Kick Shot (For Drop , Enter \'O\' )\n\n";

    if (TypeOfInputs == 1)
    {
        cout << "Speed : ";
        cin >> Speed;
        cout << "Angle : ";
        cin >> Angle;
        Angle = Angle * M_PI / 180;

        vx = Speed * cos(Angle);
        vy = Speed * sin(Angle);
        ay = 1;
    }
    else if (TypeOfInputs == 2)
    {
        cout << "Speed x : ";
        cin >> vx;
        cout << "Speed y : ";
        cin >> vy;
        cout << "ay : ";
        cin >> ay;
    }

    Launcher P = Player();
    Projectile Bullet;
    Bullet.xPos = P.xPos;
    Bullet.yPos = P.yPos;
    Bullet.PreviousxPos = Bullet.xPos;
    Bullet.PreviousyPos = Bullet.yPos;
    Projectile TempBullet;
    TempBullet.xPos = Bullet.xPos;
    TempBullet.yPos = Bullet.yPos;
    TempBullet.PreviousxPos = TempBullet.xPos;
    TempBullet.PreviousyPos = TempBullet.yPos;

    // drop kick shot
    bool IsHit = false;
    if (HowToMoveBullet == 1)
    {
        char PressKey;
        while (true)
        {
            PressKey = getch();
            if (PressKey == 13 || (PressKey == SpecialShotKeyL) || (PressKey == SpecialShotKeyS))
            {
                if ((PressKey == SpecialShotKeyL) || (PressKey == SpecialShotKeyS))
                {
                    vx = 0;
                    vy = -1;
                    ay = 0;
                }

                if (Bullet.xPos > SizeOfMapX || Bullet.yPos > SizeOfMapY)
                {
                    IsHit = true;
                }
                else
                {
                    Bullet.DeletePrevious();
                    Bullet.PreviousxPos = Bullet.xPos;
                    Bullet.PreviousyPos = Bullet.yPos;
                    TempBullet.DeletePrevious();
                    TempBullet.PreviousxPos = TempBullet.xPos;
                    TempBullet.PreviousyPos = TempBullet.yPos;
                    Bullet.Print();
                    if (GridMap[Bullet.xPos][Bullet.yPos] != 0)
                    {
                        IsHit = true;
                        if (GridMap[Bullet.xPos][Bullet.yPos] == 1)
                        {
                            CounterWall++;
                        }
                        else if (GridMap[Bullet.xPos][Bullet.yPos] == 3)
                        {
                            CounterEnemy++;
                        }
                        GridMap[Bullet.xPos][Bullet.yPos] = 0;
                    }
                }

                if (IsHit)
                {
                    Bullet.DeletePrevious();
                    Bullet.PreviousxPos = Bullet.xPos;
                    Bullet.PreviousyPos = Bullet.yPos;
                    TempBullet.DeletePrevious();
                    TempBullet.PreviousxPos = TempBullet.xPos;
                    TempBullet.PreviousyPos = TempBullet.yPos;
                    break;
                }

                /*
                    Line Equation ----> [m = -vy/vx] & [y = m(x-x1) + y1] & [x = (y-y1)/m + x1]
                    Value Of Initial TempBullet & Bullet ----> نقطه عقبی
                    Bullet + (short)v ----> نقطه جلویی
                    Bulletx + (short)vx - 1 ---->  یک نقطه قبل از نقطه جلویی
                    Bullety + (short)vy + 1 ---->  یک نقطه پایین تر از نقطه جلویی (زمانی که رو به بالا حرکت میکنه گلوله)
                    Bullety + (short)vy - 1 ---->  یک نقطه بالا تر از نقطه جلویی (زمانی که رو به پایین حرکت میکنه گلوله)
                    TempBullet ----> نقاط بین نقطه عقبی و جلویی
                    vy > 0 ----> حرکت رو به بالا
                    vy < 0 ----> حرکت رو به پایین
                */

                if ((vx != 0) && !((PressKey == SpecialShotKeyL) || (PressKey == SpecialShotKeyS)))
                {
                    double m = -vy / vx;
                    x1 = TempBullet.xPos;
                    y1 = TempBullet.yPos;

                    if (abs((short)vx) > abs((short)vy))
                    {
                        while (TempBullet.xPos != Bullet.xPos + (short)vx - 1)
                        {
                            PressKey = getch();
                            if (PressKey == 13 || (PressKey == SpecialShotKeyL) || (PressKey == SpecialShotKeyS))
                            {
                                if ((PressKey == SpecialShotKeyL) || (PressKey == SpecialShotKeyS))
                                {
                                    vx = 0;
                                    vy = -1;
                                    ay = 0;
                                    Bullet.xPos = TempBullet.xPos;
                                    Bullet.yPos = TempBullet.yPos;
                                    break;
                                }
                                else
                                {

                                    TempBullet.xPos++;
                                    TempBullet.yPos = m * (TempBullet.xPos - x1) + y1;

                                    if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                                    {
                                        IsHit = true;
                                    }
                                    else
                                    {
                                        Bullet.DeletePrevious();
                                        Bullet.PreviousxPos = Bullet.xPos;
                                        Bullet.PreviousyPos = Bullet.yPos;
                                        TempBullet.DeletePrevious();
                                        TempBullet.PreviousxPos = TempBullet.xPos;
                                        TempBullet.PreviousyPos = TempBullet.yPos;
                                        TempBullet.Print();
                                        if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                                        {
                                            IsHit = true;
                                            if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                            {
                                                CounterWall++;
                                            }
                                            else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                            {
                                                CounterEnemy++;
                                            }
                                            GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                                        }
                                    }

                                    if (IsHit)
                                    {
                                        Bullet.DeletePrevious();
                                        Bullet.PreviousxPos = Bullet.xPos;
                                        Bullet.PreviousyPos = Bullet.yPos;
                                        TempBullet.DeletePrevious();
                                        TempBullet.PreviousxPos = TempBullet.xPos;
                                        TempBullet.PreviousyPos = TempBullet.yPos;
                                        break;
                                    }
                                }
                            }
                            else if ((PressKey == ExitKeyInGameL) || (PressKey == ExitKeyInGameS))
                            {
                                CounterEnemy = -1;
                                return;
                            }
                        }
                    }
                    else if (abs((short)vx) <= abs((short)vy))
                    {
                        if (vy > 0)
                        {
                            while (TempBullet.yPos != Bullet.yPos - (short)vy)
                            {
                                PressKey = getch();
                                if (PressKey == 13 || (PressKey == SpecialShotKeyL) || (PressKey == SpecialShotKeyS))
                                {
                                    if ((PressKey == SpecialShotKeyL) || (PressKey == SpecialShotKeyS))
                                    {
                                        vx = 0;
                                        vy = -1;
                                        ay = 0;
                                        Bullet.xPos = TempBullet.xPos;
                                        Bullet.yPos = TempBullet.yPos;
                                        break;
                                    }
                                    else
                                    {
                                        if ((m < 0.5 && m > -0.5) && (Angle * 180 / M_PI > 75))
                                        {
                                            break;
                                        }
                                        TempBullet.yPos--;
                                        TempBullet.xPos = (TempBullet.yPos - y1) / m + x1;

                                        if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                                        {
                                            IsHit = true;
                                        }
                                        else
                                        {
                                            Bullet.DeletePrevious();
                                            Bullet.PreviousxPos = Bullet.xPos;
                                            Bullet.PreviousyPos = Bullet.yPos;
                                            TempBullet.DeletePrevious();
                                            TempBullet.PreviousxPos = TempBullet.xPos;
                                            TempBullet.PreviousyPos = TempBullet.yPos;
                                            TempBullet.Print();
                                            if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                                            {
                                                IsHit = true;
                                                if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                                {
                                                    CounterWall++;
                                                }
                                                else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                                {
                                                    CounterEnemy++;
                                                }
                                                GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                                            }
                                        }

                                        if (IsHit)
                                        {
                                            Bullet.DeletePrevious();
                                            Bullet.PreviousxPos = Bullet.xPos;
                                            Bullet.PreviousyPos = Bullet.yPos;
                                            TempBullet.DeletePrevious();
                                            TempBullet.PreviousxPos = TempBullet.xPos;
                                            TempBullet.PreviousyPos = TempBullet.yPos;
                                            break;
                                        }
                                    }
                                }
                                else if ((PressKey == ExitKeyInGameL) || (PressKey == ExitKeyInGameS))
                                {
                                    CounterEnemy = -1;
                                    return;
                                }
                            }
                        }
                        else if (vy < 0)
                        {
                            while (TempBullet.yPos != Bullet.yPos - (short)vy - 1)
                            {
                                PressKey = getch();
                                if (PressKey == 13 || (PressKey == SpecialShotKeyL) || (PressKey == SpecialShotKeyS))
                                {
                                    if ((PressKey == SpecialShotKeyL) || (PressKey == SpecialShotKeyS))
                                    {
                                        vx = 0;
                                        vy = -1;
                                        ay = 0;
                                        Bullet.xPos = TempBullet.xPos;
                                        Bullet.yPos = TempBullet.yPos;
                                        break;
                                    }
                                    else
                                    {
                                        if ((m < 0.5 && m > -0.5) && (Angle * 180 / M_PI > 75))
                                        {
                                            break;
                                        }
                                        TempBullet.yPos++;
                                        TempBullet.xPos = (TempBullet.yPos - y1) / m + x1;

                                        if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                                        {
                                            IsHit = true;
                                        }
                                        else
                                        {
                                            Bullet.DeletePrevious();
                                            Bullet.PreviousxPos = Bullet.xPos;
                                            Bullet.PreviousyPos = Bullet.yPos;
                                            TempBullet.DeletePrevious();
                                            TempBullet.PreviousxPos = TempBullet.xPos;
                                            TempBullet.PreviousyPos = TempBullet.yPos;
                                            TempBullet.Print();
                                            if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                                            {
                                                IsHit = true;
                                                if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                                {
                                                    CounterWall++;
                                                }
                                                else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                                {
                                                    CounterEnemy++;
                                                }
                                                GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                                            }
                                        }

                                        if (IsHit)
                                        {
                                            Bullet.DeletePrevious();
                                            Bullet.PreviousxPos = Bullet.xPos;
                                            Bullet.PreviousyPos = Bullet.yPos;
                                            TempBullet.DeletePrevious();
                                            TempBullet.PreviousxPos = TempBullet.xPos;
                                            TempBullet.PreviousyPos = TempBullet.yPos;
                                            break;
                                        }
                                    }
                                }
                                else if ((PressKey == ExitKeyInGameL) || (PressKey == ExitKeyInGameS))
                                {
                                    CounterEnemy = -1;
                                    return;
                                }
                            }
                        }
                    }
                }

                if (IsHit)
                {
                    Bullet.DeletePrevious();
                    Bullet.PreviousxPos = Bullet.xPos;
                    Bullet.PreviousyPos = Bullet.yPos;
                    TempBullet.DeletePrevious();
                    TempBullet.PreviousxPos = TempBullet.xPos;
                    TempBullet.PreviousyPos = TempBullet.yPos;
                    break;
                }

                Bullet.xPos = Bullet.xPos + vx;
                Bullet.yPos = Bullet.yPos - vy;
                vy -= ay;

                TempBullet.xPos = Bullet.xPos;
                TempBullet.yPos = Bullet.yPos;
            }
            else if ((PressKey == ExitKeyInGameL) || (PressKey == ExitKeyInGameS))
            {
                CounterEnemy = -1;
                return;
            }
        }
    }
    else if (HowToMoveBullet == 2)
    {
        while (true)
        {
            if ((GetAsyncKeyState(ExitKeyInGameL) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameL) & 0x0001) ||
                (GetAsyncKeyState(ExitKeyInGameS) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameS) & 0x0001))
            {
                getch();
                CounterEnemy = -1;
                return;
            }
            if ((GetAsyncKeyState(SpecialShotKeyL) & 0x8000) || (GetAsyncKeyState(SpecialShotKeyL) & 0x0001) ||
                (GetAsyncKeyState(SpecialShotKeyS) & 0x8000) || (GetAsyncKeyState(SpecialShotKeyS) & 0x0001))
            {
                vx = 0;
                vy = -1;
                ay = 0;
            }

            if (Bullet.xPos > SizeOfMapX || Bullet.yPos > SizeOfMapY)
            {
                IsHit = true;
            }
            else
            {
                Bullet.Print();
                if (GridMap[Bullet.xPos][Bullet.yPos] != 0)
                {

                    IsHit = true;
                    if (GridMap[Bullet.xPos][Bullet.yPos] == 1)
                    {
                        CounterWall++;
                    }
                    else if (GridMap[Bullet.xPos][Bullet.yPos] == 3)
                    {
                        CounterEnemy++;
                    }
                    GridMap[Bullet.xPos][Bullet.yPos] = 0;
                }
            }

            Sleep(SleepTimeGame);

            Bullet.Delete();

            if (IsHit)
            {
                break;
            }

            /*
                Line Equation ----> [m = -vy/vx] & [y = m(x-x1) + y1] & [x = (y-y1)/m + x1]
                Value Of Initial TempBullet & Bullet ----> نقطه عقبی
                Bullet + (short)v ----> نقطه جلویی
                Bulletx + (short)vx - 1 ---->  یک نقطه قبل از نقطه جلویی
                Bullety + (short)vy + 1 ---->  یک نقطه پایین تر از نقطه جلویی (زمانی که رو به بالا حرکت میکنه گلوله)
                Bullety + (short)vy - 1 ---->  یک نقطه بالا تر از نقطه جلویی (زمانی که رو به پایین حرکت میکنه گلوله)
                TempBullet ----> نقاط بین نقطه عقبی و جلویی
                vy > 0 ----> حرکت رو به بالا
                vy < 0 ----> حرکت رو به پایین
            */

            if (vx != 0 && !((GetAsyncKeyState(SpecialShotKeyL) & 0x8000) || (GetAsyncKeyState(SpecialShotKeyL) & 0x0001) ||
                             (GetAsyncKeyState(SpecialShotKeyS) & 0x8000) || (GetAsyncKeyState(SpecialShotKeyS) & 0x0001)))
            {
                double m = -vy / vx;
                x1 = TempBullet.xPos;
                y1 = TempBullet.yPos;

                if (abs((short)vx) > abs((short)vy))
                {
                    while (TempBullet.xPos != Bullet.xPos + (short)vx - 1)
                    {
                        if ((GetAsyncKeyState(ExitKeyInGameL) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameL) & 0x0001) ||
                            (GetAsyncKeyState(ExitKeyInGameS) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameS) & 0x0001))
                        {
                            getch();
                            CounterEnemy = -1;
                            return;
                        }
                        if ((GetAsyncKeyState(SpecialShotKeyL) & 0x8000) || (GetAsyncKeyState(SpecialShotKeyL) & 0x0001) ||
                            (GetAsyncKeyState(SpecialShotKeyS) & 0x8000) || (GetAsyncKeyState(SpecialShotKeyS) & 0x0001))
                        {
                            vx = 0;
                            vy = -1;
                            ay = 0;
                            Bullet.xPos = TempBullet.xPos;
                            Bullet.yPos = TempBullet.yPos;
                            break;
                        }

                        TempBullet.xPos++;
                        TempBullet.yPos = m * (TempBullet.xPos - x1) + y1;

                        if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                        {
                            IsHit = true;
                        }
                        else
                        {
                            TempBullet.Print();
                            if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                            {
                                IsHit = true;
                                if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                {
                                    CounterWall++;
                                }
                                else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                {
                                    CounterEnemy++;
                                }
                                GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                            }
                        }
                        Sleep(SleepTimeGame);

                        TempBullet.Delete();

                        if (IsHit)
                        {
                            break;
                        }
                    }
                }
                else if (abs((short)vx) <= abs((short)vy))
                {
                    if (vy > 0)
                    {
                        while (TempBullet.yPos != Bullet.yPos - (short)vy)
                        {
                            if ((GetAsyncKeyState(ExitKeyInGameL) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameL) & 0x0001) ||
                                (GetAsyncKeyState(ExitKeyInGameS) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameS) & 0x0001))
                            {
                                getch();
                                CounterEnemy = -1;
                                return;
                            }
                            if ((GetAsyncKeyState(SpecialShotKeyL) & 0x8000) || (GetAsyncKeyState(SpecialShotKeyL) & 0x0001) ||
                                (GetAsyncKeyState(SpecialShotKeyS) & 0x8000) || (GetAsyncKeyState(SpecialShotKeyS) & 0x0001))
                            {
                                vx = 0;
                                vy = -1;
                                ay = 0;
                                Bullet.xPos = TempBullet.xPos;
                                Bullet.yPos = TempBullet.yPos;
                                break;
                            }
                            if ((m < 0.5 && m > -0.5) && (Angle * 180 / M_PI > 75))
                            {
                                break;
                            }
                            TempBullet.yPos--;
                            TempBullet.xPos = (TempBullet.yPos - y1) / m + x1;

                            if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                            {
                                IsHit = true;
                            }
                            else
                            {
                                TempBullet.Print();
                                if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                                {
                                    IsHit = true;
                                    if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                    {
                                        CounterWall++;
                                    }
                                    else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                    {
                                        CounterEnemy++;
                                    }
                                    GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                                }
                            }
                            Sleep(SleepTimeGame);

                            TempBullet.Delete();

                            if (IsHit)
                            {
                                break;
                            }
                        }
                    }
                    else if (vy < 0)
                    {
                        while (TempBullet.yPos != Bullet.yPos - (short)vy - 1)
                        {
                            if ((GetAsyncKeyState(ExitKeyInGameL) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameL) & 0x0001) ||
                                (GetAsyncKeyState(ExitKeyInGameS) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameS) & 0x0001))
                            {
                                getch();
                                CounterEnemy = -1;
                                return;
                            }
                            if ((GetAsyncKeyState(SpecialShotKeyL) & 0x8000) || (GetAsyncKeyState(SpecialShotKeyL) & 0x0001) ||
                                (GetAsyncKeyState(SpecialShotKeyS) & 0x8000) || (GetAsyncKeyState(SpecialShotKeyS) & 0x0001))
                            {
                                vx = 0;
                                vy = -1;
                                ay = 0;
                                Bullet.xPos = TempBullet.xPos;
                                Bullet.yPos = TempBullet.yPos;
                                break;
                            }
                            if ((m < 0.5 && m > -0.5) && (Angle * 180 / M_PI > 75))
                            {
                                break;
                            }
                            TempBullet.yPos++;
                            TempBullet.xPos = (TempBullet.yPos - y1) / m + x1;

                            if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                            {
                                IsHit = true;
                            }
                            else
                            {
                                TempBullet.Print();
                                if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                                {
                                    IsHit = true;
                                    if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                    {
                                        CounterWall++;
                                    }
                                    else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                    {
                                        CounterEnemy++;
                                    }
                                    GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                                }
                            }
                            Sleep(SleepTimeGame);

                            TempBullet.Delete();

                            if (IsHit)
                            {
                                break;
                            }
                        }
                    }
                }
            }

            if (IsHit)
            {
                break;
            }

            Bullet.xPos = Bullet.xPos + vx;
            Bullet.yPos = Bullet.yPos - vy;
            vy -= ay;

            TempBullet.xPos = Bullet.xPos;
            TempBullet.yPos = Bullet.yPos;
        }
    }
    Border(GridMap);
}

void BombShot(short &CounterEnemy, short &CounterWall, short **GridMap)
{
    short x1, y1;
    double Angle, Speed;
    double vx, vy, ay;

    ClearArea(10, 100, 0, SizeOfMapY + 1);
    gotoxy(0, SizeOfMapY);
    cout << "\n\n";

    cout << " -> Bomb Shot\n\n";

    if (TypeOfInputs == 1)
    {
        cout << "Speed : ";
        cin >> Speed;
        cout << "Angle : ";
        cin >> Angle;
        Angle = Angle * M_PI / 180;

        vx = Speed * cos(Angle);
        vy = Speed * sin(Angle);
        ay = 1;
    }
    else if (TypeOfInputs == 2)
    {
        cout << "Speed x : ";
        cin >> vx;
        cout << "Speed y : ";
        cin >> vy;
        cout << "ay : ";
        cin >> ay;
    }

    Launcher P = Player();
    Projectile Bullet;
    Bullet.xPos = P.xPos;
    Bullet.yPos = P.yPos;
    Bullet.PreviousxPos = Bullet.xPos;
    Bullet.PreviousyPos = Bullet.yPos;
    Projectile TempBullet;
    TempBullet.xPos = Bullet.xPos;
    TempBullet.yPos = Bullet.yPos;
    TempBullet.PreviousxPos = TempBullet.xPos;
    TempBullet.PreviousyPos = TempBullet.yPos;

    // bomb shot
    double Tempx, Tempy;
    bool IsBomb = false;
    if (HowToMoveBullet == 1)
    {
        char PressKey;
        while (true)
        {
            PressKey = getch();
            if (PressKey == 13)
            {
                if (Bullet.xPos > SizeOfMapX || Bullet.yPos > SizeOfMapY)
                {
                    IsBomb = true;
                }
                else
                {
                    Bullet.DeletePrevious();
                    Bullet.PreviousxPos = Bullet.xPos;
                    Bullet.PreviousyPos = Bullet.yPos;
                    TempBullet.DeletePrevious();
                    TempBullet.PreviousxPos = TempBullet.xPos;
                    TempBullet.PreviousyPos = TempBullet.yPos;
                    Bullet.Print();
                    if (GridMap[Bullet.xPos][Bullet.yPos] != 0)
                    {
                        IsBomb = true;
                        Tempx = Bullet.xPos;
                        Tempy = Bullet.yPos;
                        for (short i = Tempx - 1; i <= Tempx + 1; i++)
                        {
                            for (short j = Tempy - 1; j <= Tempy + 1; j++)
                            {
                                if (i < SizeOfMapX && j < SizeOfMapY)
                                {
                                    Bullet.xPos = i;
                                    Bullet.yPos = j;
                                    Bullet.Delete();
                                    if (GridMap[Bullet.xPos][Bullet.yPos] == 1)
                                    {
                                        CounterWall++;
                                    }
                                    else if (GridMap[Bullet.xPos][Bullet.yPos] == 3)
                                    {
                                        CounterEnemy++;
                                    }
                                    GridMap[Bullet.xPos][Bullet.yPos] = 0;
                                }
                            }
                        }
                    }
                }

                if (IsBomb)
                {
                    Bullet.DeletePrevious();
                    Bullet.PreviousxPos = Bullet.xPos;
                    Bullet.PreviousyPos = Bullet.yPos;
                    TempBullet.DeletePrevious();
                    TempBullet.PreviousxPos = TempBullet.xPos;
                    TempBullet.PreviousyPos = TempBullet.yPos;
                    break;
                }

                /*
                    Line Equation ----> [m = -vy/vx] & [y = m(x-x1) + y1] & [x = (y-y1)/m + x1]
                    Value Of Initial TempBullet & Bullet ----> نقطه عقبی
                    Bullet + (short)v ----> نقطه جلویی
                    Bulletx + (short)vx - 1 ---->  یک نقطه قبل از نقطه جلویی
                    Bullety + (short)vy + 1 ---->  یک نقطه پایین تر از نقطه جلویی (زمانی که رو به بالا حرکت میکنه گلوله)
                    Bullety + (short)vy - 1 ---->  یک نقطه بالا تر از نقطه جلویی (زمانی که رو به پایین حرکت میکنه گلوله)
                    TempBullet ----> نقاط بین نقطه عقبی و جلویی
                    vy > 0 ----> حرکت رو به بالا
                    vy < 0 ----> حرکت رو به پایین
                */

                double m = -vy / vx;
                x1 = TempBullet.xPos;
                y1 = TempBullet.yPos;

                if (abs((short)vx) > abs((short)vy))
                {
                    while (TempBullet.xPos != Bullet.xPos + (short)vx - 1)
                    {
                        PressKey = getch();
                        if (PressKey == 13)
                        {
                            TempBullet.xPos++;
                            TempBullet.yPos = m * (TempBullet.xPos - x1) + y1;

                            Tempx = TempBullet.xPos;
                            Tempy = TempBullet.yPos;

                            if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                            {
                                IsBomb = true;
                            }
                            else
                            {
                                Bullet.DeletePrevious();
                                Bullet.PreviousxPos = Bullet.xPos;
                                Bullet.PreviousyPos = Bullet.yPos;
                                TempBullet.DeletePrevious();
                                TempBullet.PreviousxPos = TempBullet.xPos;
                                TempBullet.PreviousyPos = TempBullet.yPos;
                                TempBullet.Print();
                                if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                                {
                                    IsBomb = true;
                                    for (short i = Tempx - 1; i <= Tempx + 1; i++)
                                    {
                                        for (short j = Tempy - 1; j <= Tempy + 1; j++)
                                        {
                                            if (i < SizeOfMapX && j < SizeOfMapY)
                                            {
                                                TempBullet.xPos = i;
                                                TempBullet.yPos = j;
                                                TempBullet.Delete();
                                                if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                                {
                                                    CounterWall++;
                                                }
                                                else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                                {
                                                    CounterEnemy++;
                                                }
                                                GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                                            }
                                        }
                                    }
                                }
                            }

                            if (IsBomb)
                            {
                                Bullet.DeletePrevious();
                                Bullet.PreviousxPos = Bullet.xPos;
                                Bullet.PreviousyPos = Bullet.yPos;
                                TempBullet.DeletePrevious();
                                TempBullet.PreviousxPos = TempBullet.xPos;
                                TempBullet.PreviousyPos = TempBullet.yPos;
                                break;
                            }
                        }
                        else if ((PressKey == ExitKeyInGameL) || (PressKey == ExitKeyInGameS))
                        {
                            CounterEnemy = -1;
                            return;
                        }
                    }
                }
                else if (abs((short)vx) <= abs((short)vy))
                {
                    if (vy > 0)
                    {
                        while (TempBullet.yPos != Bullet.yPos - (short)vy)
                        {
                            PressKey = getch();
                            if (PressKey == 13)
                            {
                                if ((m < 0.5 && m > -0.5) && (Angle * 180 / M_PI > 75))
                                {
                                    break;
                                }
                                TempBullet.yPos--;
                                TempBullet.xPos = (TempBullet.yPos - y1) / m + x1;

                                Tempx = TempBullet.xPos;
                                Tempy = TempBullet.yPos;

                                if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                                {
                                    IsBomb = true;
                                }
                                else
                                {
                                    Bullet.DeletePrevious();
                                    Bullet.PreviousxPos = Bullet.xPos;
                                    Bullet.PreviousyPos = Bullet.yPos;
                                    TempBullet.DeletePrevious();
                                    TempBullet.PreviousxPos = TempBullet.xPos;
                                    TempBullet.PreviousyPos = TempBullet.yPos;
                                    TempBullet.Print();
                                    if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                                    {
                                        IsBomb = true;
                                        for (short i = Tempx - 1; i <= Tempx + 1; i++)
                                        {
                                            for (short j = Tempy - 1; j <= Tempy + 1; j++)
                                            {
                                                if (i < SizeOfMapX && j < SizeOfMapY)
                                                {
                                                    TempBullet.xPos = i;
                                                    TempBullet.yPos = j;
                                                    TempBullet.Delete();
                                                    if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                                    {
                                                        CounterWall++;
                                                    }
                                                    else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                                    {
                                                        CounterEnemy++;
                                                    }
                                                    GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                                                }
                                            }
                                        }
                                    }
                                }

                                if (IsBomb)
                                {
                                    Bullet.DeletePrevious();
                                    Bullet.PreviousxPos = Bullet.xPos;
                                    Bullet.PreviousyPos = Bullet.yPos;
                                    TempBullet.DeletePrevious();
                                    TempBullet.PreviousxPos = TempBullet.xPos;
                                    TempBullet.PreviousyPos = TempBullet.yPos;
                                    break;
                                }
                            }
                            else if ((PressKey == ExitKeyInGameL) || (PressKey == ExitKeyInGameS))
                            {
                                CounterEnemy = -1;
                                return;
                            }
                        }
                    }
                    else if (vy < 0)
                    {
                        while (TempBullet.yPos != Bullet.yPos - (short)vy - 1)
                        {
                            PressKey = getch();
                            if (PressKey == 13)
                            {
                                if ((m < 0.5 && m > -0.5) && (Angle * 180 / M_PI > 75))
                                {
                                    break;
                                }
                                TempBullet.yPos++;
                                TempBullet.xPos = (TempBullet.yPos - y1) / m + x1;

                                Tempx = TempBullet.xPos;
                                Tempy = TempBullet.yPos;

                                if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                                {
                                    IsBomb = true;
                                }
                                else
                                {
                                    Bullet.DeletePrevious();
                                    Bullet.PreviousxPos = Bullet.xPos;
                                    Bullet.PreviousyPos = Bullet.yPos;
                                    TempBullet.DeletePrevious();
                                    TempBullet.PreviousxPos = TempBullet.xPos;
                                    TempBullet.PreviousyPos = TempBullet.yPos;
                                    TempBullet.Print();
                                    if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                                    {
                                        IsBomb = true;
                                        for (short i = Tempx - 1; i <= Tempx + 1; i++)
                                        {
                                            for (short j = Tempy - 1; j <= Tempy + 1; j++)
                                            {
                                                if (i < SizeOfMapX && j < SizeOfMapY)
                                                {
                                                    TempBullet.xPos = i;
                                                    TempBullet.yPos = j;
                                                    TempBullet.Delete();
                                                    if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                                    {
                                                        CounterWall++;
                                                    }
                                                    else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                                    {
                                                        CounterEnemy++;
                                                    }
                                                    GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                                                }
                                            }
                                        }
                                    }
                                }

                                if (IsBomb)
                                {
                                    Bullet.DeletePrevious();
                                    Bullet.PreviousxPos = Bullet.xPos;
                                    Bullet.PreviousyPos = Bullet.yPos;
                                    TempBullet.DeletePrevious();
                                    TempBullet.PreviousxPos = TempBullet.xPos;
                                    TempBullet.PreviousyPos = TempBullet.yPos;
                                    break;
                                }
                            }
                            else if ((PressKey == ExitKeyInGameL) || (PressKey == ExitKeyInGameS))
                            {
                                CounterEnemy = -1;
                                return;
                            }
                        }
                    }
                }

                if (IsBomb)
                {
                    Bullet.DeletePrevious();
                    Bullet.PreviousxPos = Bullet.xPos;
                    Bullet.PreviousyPos = Bullet.yPos;
                    TempBullet.DeletePrevious();
                    TempBullet.PreviousxPos = TempBullet.xPos;
                    TempBullet.PreviousyPos = TempBullet.yPos;
                    break;
                }

                Bullet.xPos = Bullet.xPos + vx;
                Bullet.yPos = Bullet.yPos - vy;
                vy -= ay;

                TempBullet.xPos = Bullet.xPos;
                TempBullet.yPos = Bullet.yPos;
            }
            else if ((PressKey == ExitKeyInGameL) || (PressKey == ExitKeyInGameS))
            {
                CounterEnemy = -1;
                return;
            }
        }
    }
    else if (HowToMoveBullet == 2)
    {
        while (true)
        {
            if ((GetAsyncKeyState(ExitKeyInGameL) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameL) & 0x0001) ||
                (GetAsyncKeyState(ExitKeyInGameS) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameS) & 0x0001))
            {
                getch();
                CounterEnemy = -1;
                return;
            }
            if (Bullet.xPos > SizeOfMapX || Bullet.yPos > SizeOfMapY)
            {
                IsBomb = true;
            }
            else
            {
                Bullet.Print();
                if (GridMap[Bullet.xPos][Bullet.yPos] != 0)
                {

                    IsBomb = true;
                    Tempx = Bullet.xPos;
                    Tempy = Bullet.yPos;
                    for (short i = Tempx - 1; i <= Tempx + 1; i++)
                    {
                        for (short j = Tempy - 1; j <= Tempy + 1; j++)
                        {
                            if (i < SizeOfMapX && j < SizeOfMapY)
                            {
                                Bullet.xPos = i;
                                Bullet.yPos = j;
                                Bullet.Delete();
                                if (GridMap[Bullet.xPos][Bullet.yPos] == 1)
                                {
                                    CounterWall++;
                                }
                                else if (GridMap[Bullet.xPos][Bullet.yPos] == 3)
                                {
                                    CounterEnemy++;
                                }
                                GridMap[Bullet.xPos][Bullet.yPos] = 0;
                            }
                        }
                    }
                }
            }

            Sleep(SleepTimeGame);

            Bullet.Delete();

            if (IsBomb)
            {
                break;
            }

            /*
                Line Equation ----> [m = -vy/vx] & [y = m(x-x1) + y1] & [x = (y-y1)/m + x1]
                Value Of Initial TempBullet & Bullet ----> نقطه عقبی
                Bullet + (short)v ----> نقطه جلویی
                Bulletx + (short)vx - 1 ---->  یک نقطه قبل از نقطه جلویی
                Bullety + (short)vy + 1 ---->  یک نقطه پایین تر از نقطه جلویی (زمانی که رو به بالا حرکت میکنه گلوله)
                Bullety + (short)vy - 1 ---->  یک نقطه بالا تر از نقطه جلویی (زمانی که رو به پایین حرکت میکنه گلوله)
                TempBullet ----> نقاط بین نقطه عقبی و جلویی
                vy > 0 ----> حرکت رو به بالا
                vy < 0 ----> حرکت رو به پایین
            */

            double m = -vy / vx;
            x1 = TempBullet.xPos;
            y1 = TempBullet.yPos;

            if (abs((short)vx) > abs((short)vy))
            {
                while (TempBullet.xPos != Bullet.xPos + (short)vx - 1)
                {
                    if ((GetAsyncKeyState(ExitKeyInGameL) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameL) & 0x0001) ||
                        (GetAsyncKeyState(ExitKeyInGameS) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameS) & 0x0001))
                    {
                        getch();
                        CounterEnemy = -1;
                        return;
                    }
                    TempBullet.xPos++;
                    TempBullet.yPos = m * (TempBullet.xPos - x1) + y1;

                    Tempx = TempBullet.xPos;
                    Tempy = TempBullet.yPos;

                    if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                    {
                        IsBomb = true;
                    }
                    else
                    {
                        TempBullet.Print();
                        if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                        {
                            IsBomb = true;
                            for (short i = Tempx - 1; i <= Tempx + 1; i++)
                            {
                                for (short j = Tempy - 1; j <= Tempy + 1; j++)
                                {
                                    if (i < SizeOfMapX && j < SizeOfMapY)
                                    {
                                        TempBullet.xPos = i;
                                        TempBullet.yPos = j;
                                        TempBullet.Delete();
                                        if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                        {
                                            CounterWall++;
                                        }
                                        else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                        {
                                            CounterEnemy++;
                                        }
                                        GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                                    }
                                }
                            }
                        }
                    }
                    if (IsBomb)
                    {
                        break;
                    }

                    Sleep(SleepTimeGame);

                    TempBullet.Delete();
                }
            }
            else if (abs((short)vx) <= abs((short)vy))
            {
                if (vy > 0)
                {
                    while (TempBullet.yPos != Bullet.yPos - (short)vy)
                    {
                        if ((GetAsyncKeyState(ExitKeyInGameL) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameL) & 0x0001) ||
                            (GetAsyncKeyState(ExitKeyInGameS) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameS) & 0x0001))
                        {
                            getch();
                            CounterEnemy = -1;
                            return;
                        }
                        if ((m < 0.5 && m > -0.5) && (Angle * 180 / M_PI > 75))
                        {
                            break;
                        }
                        TempBullet.yPos--;
                        TempBullet.xPos = (TempBullet.yPos - y1) / m + x1;

                        Tempx = TempBullet.xPos;
                        Tempy = TempBullet.yPos;

                        if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                        {
                            IsBomb = true;
                        }
                        else
                        {
                            TempBullet.Print();
                            if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                            {
                                IsBomb = true;
                                for (short i = Tempx - 1; i <= Tempx + 1; i++)
                                {
                                    for (short j = Tempy - 1; j <= Tempy + 1; j++)
                                    {
                                        if (i < SizeOfMapX && j < SizeOfMapY)
                                        {
                                            TempBullet.xPos = i;
                                            TempBullet.yPos = j;
                                            TempBullet.Delete();
                                            if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                            {
                                                CounterWall++;
                                            }
                                            else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                            {
                                                CounterEnemy++;
                                            }
                                            GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                                        }
                                    }
                                }
                            }
                        }
                        if (IsBomb)
                        {
                            break;
                        }

                        Sleep(SleepTimeGame);

                        TempBullet.Delete();
                    }
                }
                else if (vy < 0)
                {
                    while (TempBullet.yPos != Bullet.yPos - (short)vy - 1)
                    {
                        if ((GetAsyncKeyState(ExitKeyInGameL) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameL) & 0x0001) ||
                            (GetAsyncKeyState(ExitKeyInGameS) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameS) & 0x0001))
                        {
                            getch();
                            CounterEnemy = -1;
                            return;
                        }
                        if ((m < 0.5 && m > -0.5) && (Angle * 180 / M_PI > 75))
                        {
                            break;
                        }
                        TempBullet.yPos++;
                        TempBullet.xPos = (TempBullet.yPos - y1) / m + x1;

                        Tempx = TempBullet.xPos;
                        Tempy = TempBullet.yPos;

                        if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                        {
                            IsBomb = true;
                        }
                        else
                        {
                            TempBullet.Print();
                            if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                            {
                                IsBomb = true;
                                for (short i = Tempx - 1; i <= Tempx + 1; i++)
                                {
                                    for (short j = Tempy - 1; j <= Tempy + 1; j++)
                                    {
                                        if (i < SizeOfMapX && j < SizeOfMapY)
                                        {
                                            TempBullet.xPos = i;
                                            TempBullet.yPos = j;
                                            TempBullet.Delete();
                                            if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                            {
                                                CounterWall++;
                                            }
                                            else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                            {
                                                CounterEnemy++;
                                            }
                                            GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                                        }
                                    }
                                }
                            }
                        }
                        if (IsBomb)
                        {
                            break;
                        }

                        Sleep(SleepTimeGame);

                        TempBullet.Delete();
                    }
                }
            }

            if (IsBomb)
            {
                break;
            }

            Bullet.xPos = Bullet.xPos + vx;
            Bullet.yPos = Bullet.yPos - vy;
            vy -= ay;

            TempBullet.xPos = Bullet.xPos;
            TempBullet.yPos = Bullet.yPos;
        }
    }
    Border(GridMap);
}

void DrillShot(short &CounterEnemy, short &CounterWall, short **GridMap)
{
    short x1, y1;
    double Angle, Speed;
    double vx, vy, ay;
    short CountBlock = 0;

    ClearArea(10, 100, 0, SizeOfMapY + 1);
    gotoxy(0, SizeOfMapY);
    cout << "\n\n";

    cout << " -> Drill Shot\n\n";

    if (TypeOfInputs == 1)
    {
        cout << "Speed : ";
        cin >> Speed;
        cout << "Angle : ";
        cin >> Angle;
        Angle = Angle * M_PI / 180;

        vx = Speed * cos(Angle);
        vy = Speed * sin(Angle);
        ay = 1;
    }
    else if (TypeOfInputs == 2)
    {
        cout << "Speed x : ";
        cin >> vx;
        cout << "Speed y : ";
        cin >> vy;
        cout << "ay : ";
        cin >> ay;
    }

    Launcher P = Player();
    Projectile Bullet;
    Bullet.xPos = P.xPos;
    Bullet.yPos = P.yPos;
    Bullet.PreviousxPos = Bullet.xPos;
    Bullet.PreviousyPos = Bullet.yPos;
    Projectile TempBullet;
    TempBullet.xPos = Bullet.xPos;
    TempBullet.yPos = Bullet.yPos;
    TempBullet.PreviousxPos = TempBullet.xPos;
    TempBullet.PreviousyPos = TempBullet.yPos;

    // drill shot
    bool IsHit = false;
    if (HowToMoveBullet == 1)
    {
        char PressKey;
        while (true)
        {
            PressKey = getch();
            if (PressKey == 13)
            {
                if (Bullet.xPos > SizeOfMapX || Bullet.yPos > SizeOfMapY)
                {
                    IsHit = true;
                }
                else
                {
                    Bullet.DeletePrevious();
                    Bullet.PreviousxPos = Bullet.xPos;
                    Bullet.PreviousyPos = Bullet.yPos;
                    TempBullet.DeletePrevious();
                    TempBullet.PreviousxPos = TempBullet.xPos;
                    TempBullet.PreviousyPos = TempBullet.yPos;
                    Bullet.Print();
                    if (GridMap[Bullet.xPos][Bullet.yPos] != 0)
                    {
                        if (GridMap[Bullet.xPos][Bullet.yPos] == 1)
                        {
                            CounterWall++;
                            CountBlock++;
                        }
                        else if (GridMap[Bullet.xPos][Bullet.yPos] == 3)
                        {
                            CounterEnemy++;
                        }
                        if (((GridMap[Bullet.xPos][Bullet.yPos] != 0) && (CountBlock >= 3)) ||
                            (GridMap[Bullet.xPos][Bullet.yPos] == 3 || GridMap[Bullet.xPos][Bullet.yPos] == 2))
                        {
                            IsHit = true;
                        }
                        GridMap[Bullet.xPos][Bullet.yPos] = 0;
                    }
                }

                if (IsHit)
                {
                    Bullet.DeletePrevious();
                    Bullet.PreviousxPos = Bullet.xPos;
                    Bullet.PreviousyPos = Bullet.yPos;
                    TempBullet.DeletePrevious();
                    TempBullet.PreviousxPos = TempBullet.xPos;
                    TempBullet.PreviousyPos = TempBullet.yPos;
                    break;
                }

                /*
                    Line Equation ----> [m = -vy/vx] & [y = m(x-x1) + y1] & [x = (y-y1)/m + x1]
                    Value Of Initial TempBullet & Bullet ----> نقطه عقبی
                    Bullet + (short)v ----> نقطه جلویی
                    Bulletx + (short)vx - 1 ---->  یک نقطه قبل از نقطه جلویی
                    Bullety + (short)vy + 1 ---->  یک نقطه پایین تر از نقطه جلویی (زمانی که رو به بالا حرکت میکنه گلوله)
                    Bullety + (short)vy - 1 ---->  یک نقطه بالا تر از نقطه جلویی (زمانی که رو به پایین حرکت میکنه گلوله)
                    TempBullet ----> نقاط بین نقطه عقبی و جلویی
                    vy > 0 ----> حرکت رو به بالا
                    vy < 0 ----> حرکت رو به پایین
                */

                double m = -vy / vx;
                x1 = TempBullet.xPos;
                y1 = TempBullet.yPos;

                if (abs((short)vx) > abs((short)vy))
                {
                    while (TempBullet.xPos != Bullet.xPos + (short)vx - 1)
                    {
                        PressKey = getch();
                        if (PressKey == 13)
                        {
                            TempBullet.xPos++;
                            TempBullet.yPos = m * (TempBullet.xPos - x1) + y1;

                            if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                            {
                                IsHit = true;
                            }
                            else
                            {
                                Bullet.DeletePrevious();
                                Bullet.PreviousxPos = Bullet.xPos;
                                Bullet.PreviousyPos = Bullet.yPos;
                                TempBullet.DeletePrevious();
                                TempBullet.PreviousxPos = TempBullet.xPos;
                                TempBullet.PreviousyPos = TempBullet.yPos;
                                TempBullet.Print();
                                if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                                {
                                    if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                    {
                                        CounterWall++;
                                        CountBlock++;
                                    }
                                    else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                    {
                                        CounterEnemy++;
                                    }

                                    if (((GridMap[TempBullet.xPos][TempBullet.yPos] != 0) && (CountBlock >= 3)) ||
                                        (GridMap[TempBullet.xPos][TempBullet.yPos] == 3 || GridMap[TempBullet.xPos][TempBullet.yPos] == 2))
                                    {
                                        IsHit = true;
                                    }
                                    GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                                }
                            }

                            if (IsHit)
                            {
                                Bullet.DeletePrevious();
                                Bullet.PreviousxPos = Bullet.xPos;
                                Bullet.PreviousyPos = Bullet.yPos;
                                TempBullet.DeletePrevious();
                                TempBullet.PreviousxPos = TempBullet.xPos;
                                TempBullet.PreviousyPos = TempBullet.yPos;
                                break;
                            }
                        }
                        else if ((PressKey == ExitKeyInGameL) || (PressKey == ExitKeyInGameS))
                        {
                            CounterEnemy = -1;
                            return;
                        }
                    }
                }
                else if (abs((short)vx) <= abs((short)vy))
                {
                    if (vy > 0)
                    {
                        while (TempBullet.yPos != Bullet.yPos - (short)vy)
                        {
                            PressKey = getch();
                            if (PressKey == 13)
                            {
                                if ((m < 0.5 && m > -0.5) && (Angle * 180 / M_PI > 75))
                                {
                                    break;
                                }
                                TempBullet.yPos--;
                                TempBullet.xPos = (TempBullet.yPos - y1) / m + x1;

                                if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                                {
                                    IsHit = true;
                                }
                                else
                                {
                                    Bullet.DeletePrevious();
                                    Bullet.PreviousxPos = Bullet.xPos;
                                    Bullet.PreviousyPos = Bullet.yPos;
                                    TempBullet.DeletePrevious();
                                    TempBullet.PreviousxPos = TempBullet.xPos;
                                    TempBullet.PreviousyPos = TempBullet.yPos;
                                    TempBullet.Print();
                                    if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                                    {
                                        if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                        {
                                            CounterWall++;
                                            CountBlock++;
                                        }
                                        else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                        {
                                            CounterEnemy++;
                                        }

                                        if (((GridMap[TempBullet.xPos][TempBullet.yPos] != 0) && (CountBlock >= 3)) ||
                                            (GridMap[TempBullet.xPos][TempBullet.yPos] == 3 || GridMap[TempBullet.xPos][TempBullet.yPos] == 2))
                                        {
                                            IsHit = true;
                                        }
                                        GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                                    }
                                }

                                if (IsHit)
                                {
                                    Bullet.DeletePrevious();
                                    Bullet.PreviousxPos = Bullet.xPos;
                                    Bullet.PreviousyPos = Bullet.yPos;
                                    TempBullet.DeletePrevious();
                                    TempBullet.PreviousxPos = TempBullet.xPos;
                                    TempBullet.PreviousyPos = TempBullet.yPos;
                                    break;
                                }
                            }
                            else if ((PressKey == ExitKeyInGameL) || (PressKey == ExitKeyInGameS))
                            {
                                CounterEnemy = -1;
                                return;
                            }
                        }
                    }
                    else if (vy < 0)
                    {
                        while (TempBullet.yPos != Bullet.yPos - (short)vy - 1)
                        {
                            PressKey = getch();
                            if (PressKey == 13)
                            {
                                if ((m < 0.5 && m > -0.5) && (Angle * 180 / M_PI > 75))
                                {
                                    break;
                                }
                                TempBullet.yPos++;
                                TempBullet.xPos = (TempBullet.yPos - y1) / m + x1;

                                if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                                {
                                    IsHit = true;
                                }
                                else
                                {
                                    Bullet.DeletePrevious();
                                    Bullet.PreviousxPos = Bullet.xPos;
                                    Bullet.PreviousyPos = Bullet.yPos;
                                    TempBullet.DeletePrevious();
                                    TempBullet.PreviousxPos = TempBullet.xPos;
                                    TempBullet.PreviousyPos = TempBullet.yPos;
                                    TempBullet.Print();
                                    if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                                    {
                                        if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                        {
                                            CounterWall++;
                                            CountBlock++;
                                        }
                                        else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                        {
                                            CounterEnemy++;
                                        }

                                        if (((GridMap[TempBullet.xPos][TempBullet.yPos] != 0) && (CountBlock >= 3)) ||
                                            (GridMap[TempBullet.xPos][TempBullet.yPos] == 3 || GridMap[TempBullet.xPos][TempBullet.yPos] == 2))
                                        {
                                            IsHit = true;
                                        }
                                        GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                                    }
                                }

                                if (IsHit)
                                {
                                    Bullet.DeletePrevious();
                                    Bullet.PreviousxPos = Bullet.xPos;
                                    Bullet.PreviousyPos = Bullet.yPos;
                                    TempBullet.DeletePrevious();
                                    TempBullet.PreviousxPos = TempBullet.xPos;
                                    TempBullet.PreviousyPos = TempBullet.yPos;
                                    break;
                                }
                            }
                            else if ((PressKey == ExitKeyInGameL) || (PressKey == ExitKeyInGameS))
                            {
                                CounterEnemy = -1;
                                return;
                            }
                        }
                    }
                }

                if (IsHit)
                {
                    Bullet.DeletePrevious();
                    Bullet.PreviousxPos = Bullet.xPos;
                    Bullet.PreviousyPos = Bullet.yPos;
                    TempBullet.DeletePrevious();
                    TempBullet.PreviousxPos = TempBullet.xPos;
                    TempBullet.PreviousyPos = TempBullet.yPos;
                    break;
                }

                Bullet.xPos = Bullet.xPos + vx;
                Bullet.yPos = Bullet.yPos - vy;
                vy -= ay;

                TempBullet.xPos = Bullet.xPos;
                TempBullet.yPos = Bullet.yPos;
            }
            else if ((PressKey == ExitKeyInGameL) || (PressKey == ExitKeyInGameS))
            {
                CounterEnemy = -1;
                return;
            }
        }
    }
    else if (HowToMoveBullet == 2)
    {
        while (true)
        {
            if ((GetAsyncKeyState(ExitKeyInGameL) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameL) & 0x0001) ||
                (GetAsyncKeyState(ExitKeyInGameS) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameS) & 0x0001))
            {
                getch();
                CounterEnemy = -1;
                return;
            }
            if (Bullet.xPos > SizeOfMapX || Bullet.yPos > SizeOfMapY)
            {
                IsHit = true;
            }
            else
            {
                Bullet.Print();
                if (GridMap[Bullet.xPos][Bullet.yPos] != 0)
                {

                    if (GridMap[Bullet.xPos][Bullet.yPos] == 1)
                    {
                        CounterWall++;
                        CountBlock++;
                    }
                    else if (GridMap[Bullet.xPos][Bullet.yPos] == 3)
                    {
                        CounterEnemy++;
                    }
                    if (((GridMap[Bullet.xPos][Bullet.yPos] != 0) && (CountBlock >= 3)) ||
                        (GridMap[Bullet.xPos][Bullet.yPos] == 3 || GridMap[Bullet.xPos][Bullet.yPos] == 2))
                    {
                        IsHit = true;
                    }
                    GridMap[Bullet.xPos][Bullet.yPos] = 0;
                }
            }

            Sleep(SleepTimeGame);

            Bullet.Delete();

            if (IsHit)
            {
                break;
            }

            /*
                Line Equation ----> [m = -vy/vx] & [y = m(x-x1) + y1] & [x = (y-y1)/m + x1]
                Value Of Initial TempBullet & Bullet ----> نقطه عقبی
                Bullet + (short)v ----> نقطه جلویی
                Bulletx + (short)vx - 1 ---->  یک نقطه قبل از نقطه جلویی
                Bullety + (short)vy + 1 ---->  یک نقطه پایین تر از نقطه جلویی (زمانی که رو به بالا حرکت میکنه گلوله)
                Bullety + (short)vy - 1 ---->  یک نقطه بالا تر از نقطه جلویی (زمانی که رو به پایین حرکت میکنه گلوله)
                TempBullet ----> نقاط بین نقطه عقبی و جلویی
                vy > 0 ----> حرکت رو به بالا
                vy < 0 ----> حرکت رو به پایین
            */

            double m = -vy / vx;
            x1 = TempBullet.xPos;
            y1 = TempBullet.yPos;

            if (abs((short)vx) > abs((short)vy))
            {
                while (TempBullet.xPos != Bullet.xPos + (short)vx - 1)
                {
                    if ((GetAsyncKeyState(ExitKeyInGameL) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameL) & 0x0001) ||
                        (GetAsyncKeyState(ExitKeyInGameS) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameS) & 0x0001))
                    {
                        getch();
                        CounterEnemy = -1;
                        return;
                    }
                    TempBullet.xPos++;
                    TempBullet.yPos = m * (TempBullet.xPos - x1) + y1;

                    if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                    {
                        IsHit = true;
                    }
                    else
                    {
                        TempBullet.Print();
                        if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                        {
                            if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                            {
                                CounterWall++;
                                CountBlock++;
                            }
                            else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                            {
                                CounterEnemy++;
                            }

                            if (((GridMap[TempBullet.xPos][TempBullet.yPos] != 0) && (CountBlock >= 3)) ||
                                (GridMap[TempBullet.xPos][TempBullet.yPos] == 3 || GridMap[TempBullet.xPos][TempBullet.yPos] == 2))
                            {
                                IsHit = true;
                            }
                            GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                        }
                    }
                    Sleep(SleepTimeGame);

                    TempBullet.Delete();

                    if (IsHit)
                    {
                        break;
                    }
                }
            }
            else if (abs((short)vx) <= abs((short)vy))
            {
                if (vy > 0)
                {
                    while (TempBullet.yPos != Bullet.yPos - (short)vy)
                    {
                        if ((GetAsyncKeyState(ExitKeyInGameL) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameL) & 0x0001) ||
                            (GetAsyncKeyState(ExitKeyInGameS) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameS) & 0x0001))
                        {
                            getch();
                            CounterEnemy = -1;
                            return;
                        }
                        if ((m < 0.5 && m > -0.5) && (Angle * 180 / M_PI > 75))
                        {
                            break;
                        }
                        TempBullet.yPos--;
                        TempBullet.xPos = (TempBullet.yPos - y1) / m + x1;

                        if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                        {
                            IsHit = true;
                        }
                        else
                        {
                            TempBullet.Print();
                            if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                            {
                                if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                {
                                    CounterWall++;
                                    CountBlock++;
                                }
                                else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                {
                                    CounterEnemy++;
                                }

                                if (((GridMap[TempBullet.xPos][TempBullet.yPos] != 0) && (CountBlock >= 3)) ||
                                    (GridMap[TempBullet.xPos][TempBullet.yPos] == 3 || GridMap[TempBullet.xPos][TempBullet.yPos] == 2))
                                {
                                    IsHit = true;
                                }
                                GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                            }
                        }
                        Sleep(SleepTimeGame);

                        TempBullet.Delete();

                        if (IsHit)
                        {
                            break;
                        }
                    }
                }
                else if (vy < 0)
                {
                    while (TempBullet.yPos != Bullet.yPos - (short)vy - 1)
                    {
                        if ((GetAsyncKeyState(ExitKeyInGameL) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameL) & 0x0001) ||
                            (GetAsyncKeyState(ExitKeyInGameS) & 0x8000) || (GetAsyncKeyState(ExitKeyInGameS) & 0x0001))
                        {
                            getch();
                            CounterEnemy = -1;
                            return;
                        }
                        if ((m < 0.5 && m > -0.5) && (Angle * 180 / M_PI > 75))
                        {
                            break;
                        }
                        TempBullet.yPos++;
                        TempBullet.xPos = (TempBullet.yPos - y1) / m + x1;

                        if (TempBullet.xPos > SizeOfMapX || TempBullet.yPos > SizeOfMapY)
                        {
                            IsHit = true;
                        }
                        else
                        {
                            TempBullet.Print();
                            if (GridMap[TempBullet.xPos][TempBullet.yPos] != 0)
                            {
                                if (GridMap[TempBullet.xPos][TempBullet.yPos] == 1)
                                {
                                    CounterWall++;
                                    CountBlock++;
                                }
                                else if (GridMap[TempBullet.xPos][TempBullet.yPos] == 3)
                                {
                                    CounterEnemy++;
                                }

                                if (((GridMap[TempBullet.xPos][TempBullet.yPos] != 0) && (CountBlock >= 3)) ||
                                    (GridMap[TempBullet.xPos][TempBullet.yPos] == 3 || GridMap[TempBullet.xPos][TempBullet.yPos] == 2))
                                {
                                    IsHit = true;
                                }
                                GridMap[TempBullet.xPos][TempBullet.yPos] = 0;
                            }
                        }
                        Sleep(SleepTimeGame);

                        TempBullet.Delete();

                        if (IsHit)
                        {
                            break;
                        }
                    }
                }
            }

            if (IsHit)
            {
                break;
            }

            Bullet.xPos = Bullet.xPos + vx;
            Bullet.yPos = Bullet.yPos - vy;
            vy -= ay;

            TempBullet.xPos = Bullet.xPos;
            TempBullet.yPos = Bullet.yPos;
        }
    }
    Border(GridMap);
}

void ClearArea(short Row, short Cols, short StartLocationx, short StartLocationy)
{
    gotoxy(StartLocationx, StartLocationy);
    for (int i = 0; i < Row; i++)
    {
        for (int j = 0; j < Cols; j++)
        {
            cout << " ";
        }
        cout << endl;
    }
}

short PlayGame(short WhichMap, short NumberOfNormalShot, short NumberOfDropkickShot, short NumberOfBombShot, short NumberOfDrillShot)
{
    short CounterEnemy = 0, CounterWall = 0;
    short UseNormalShot = 0, UseDropkickShot = 0, UseBombShot = 0, UseDrillShot = 0;
    short AllNumberOfNormalShot = NumberOfNormalShot;
    short AllNumberOfDropkickShot = NumberOfDropkickShot;
    short AllNumberOfBombShot = NumberOfBombShot;
    short AllNumberOfDrillShot = NumberOfDrillShot;
    short NumberOfEnemy;
    short Star;

    short **GridMap = new short *[SizeOfMapX + 1];
    for (int i = 0; i <= SizeOfMapX; i++)
    {
        GridMap[i] = new short[SizeOfMapY + 1];
        for (int j = 0; j <= SizeOfMapY; j++)
        {
            GridMap[i][j] = 0;
        }
    }

    switch (WhichMap)
    {
    case 1:
        NumberOfEnemy = Map1(GridMap);
        break;

    case 2:
        NumberOfEnemy = Map2(GridMap);
        break;

    case 3:
        NumberOfEnemy = Map3(GridMap);
        break;

    case 4:
        NumberOfEnemy = Map4(GridMap);
        break;

    case 5:
        NumberOfEnemy = Map5(GridMap);
        break;

    case 6:
        NumberOfEnemy = Map6(GridMap);
        break;
    }

    Border(GridMap);

    char ChoiceShot;
    while ((NumberOfNormalShot != 0) || (NumberOfDropkickShot != 0) || (NumberOfBombShot != 0) || (NumberOfDrillShot != 0))
    {
        ClearArea(10, 100, 0, SizeOfMapY + 1);
        gotoxy(0, SizeOfMapY);
        cout << "\n\n";
        cout << "1) Normal Shot (" << NumberOfNormalShot << ")" << endl
             << "2) Drop Kick Shot (" << NumberOfDropkickShot << ")" << endl
             << "3) Bomb Shot (" << NumberOfBombShot << ")" << endl
             << "4) Drill Shot (" << NumberOfDrillShot << ")\n\n";
        cout << "Which shot do you want (enter one key in keyboard without press enter)";
        ChoiceShot = getch();

        if (NumberOfNormalShot > 0 && ChoiceShot == '1')
        {
            NormalShot(CounterEnemy, CounterWall, GridMap);
            if (CounterEnemy == -1)
            {
                return -1;
            }
            UseNormalShot++;
            NumberOfNormalShot--;
            ClearArea(10, 100, 0, SizeOfMapY + 1);
            gotoxy(0, SizeOfMapY);
            cout << "\n\n";
            cout << "Enemy : " << CounterEnemy << endl;
            cout << "Wall : " << CounterWall << endl;
            cout << "Number Of Normal Shot : " << NumberOfNormalShot << endl;
            cout << "Number Of Drop Kick Shot : " << NumberOfDropkickShot << endl;
            cout << "Number Of Bomb Shot : " << NumberOfBombShot << endl;
            cout << "Number Of Drill Shot : " << NumberOfDrillShot;
            PauseScreen();
            if (CounterEnemy == NumberOfEnemy)
            {
                break;
            }
        }
        else if (NumberOfNormalShot == 0 && ChoiceShot == '1')
        {
            ClearArea(10, 100, 0, SizeOfMapY + 1);
            gotoxy(0, SizeOfMapY);
            cout << "\n\n";
            cout << "this shot is end ...\n";
            cout << "Please choose another one";
            PauseScreen();
        }

        if (NumberOfDropkickShot > 0 && ChoiceShot == '2')
        {
            DropKickShot(CounterEnemy, CounterWall, GridMap);
            if (CounterEnemy == -1)
            {
                return -1;
            }
            UseDropkickShot++;
            NumberOfDropkickShot--;
            ClearArea(10, 100, 0, SizeOfMapY + 1);
            gotoxy(0, SizeOfMapY);
            cout << "\n\n";
            cout << "Enemy : " << CounterEnemy << endl;
            cout << "Wall : " << CounterWall << endl;
            cout << "Number Of Normal Shot : " << NumberOfNormalShot << endl;
            cout << "Number Of Drop Kick Shot : " << NumberOfDropkickShot << endl;
            cout << "Number Of Bomb Shot : " << NumberOfBombShot << endl;
            cout << "Number Of Drill Shot : " << NumberOfDrillShot;
            PauseScreen();
            if (CounterEnemy == NumberOfEnemy)
            {
                break;
            }
        }
        else if (NumberOfDropkickShot == 0 && ChoiceShot == '2')
        {
            ClearArea(10, 100, 0, SizeOfMapY + 1);
            gotoxy(0, SizeOfMapY);
            cout << "\n\n";
            cout << "this shot is end ...\n";
            cout << "Please choose another one";
            PauseScreen();
        }

        if (NumberOfBombShot > 0 && ChoiceShot == '3')
        {
            BombShot(CounterEnemy, CounterWall, GridMap);
            if (CounterEnemy == -1)
            {
                return -1;
            }
            UseBombShot++;
            NumberOfBombShot--;
            ClearArea(10, 100, 0, SizeOfMapY + 1);
            gotoxy(0, SizeOfMapY);
            cout << "\n\n";
            cout << "Enemy : " << CounterEnemy << endl;
            cout << "Wall : " << CounterWall << endl;
            cout << "Number Of Normal Shot : " << NumberOfNormalShot << endl;
            cout << "Number Of Drop Kick Shot : " << NumberOfDropkickShot << endl;
            cout << "Number Of Bomb Shot : " << NumberOfBombShot << endl;
            cout << "Number Of Drill Shot : " << NumberOfDrillShot;
            PauseScreen();
            if (CounterEnemy == NumberOfEnemy)
            {
                break;
            }
        }
        else if (NumberOfBombShot == 0 && ChoiceShot == '3')
        {
            ClearArea(10, 100, 0, SizeOfMapY + 1);
            gotoxy(0, SizeOfMapY);
            cout << "\n\n";
            cout << "this shot is end ...\n";
            cout << "Please choose another one";
            PauseScreen();
        }

        if (NumberOfDrillShot > 0 && ChoiceShot == '4')
        {
            DrillShot(CounterEnemy, CounterWall, GridMap);
            if (CounterEnemy == -1)
            {
                return -1;
            }
            UseDrillShot++;
            NumberOfDrillShot--;
            ClearArea(10, 100, 0, SizeOfMapY + 1);
            gotoxy(0, SizeOfMapY);
            cout << "\n\n";
            cout << "Enemy : " << CounterEnemy << endl;
            cout << "Wall : " << CounterWall << endl;
            cout << "Number Of Normal Shot : " << NumberOfNormalShot << endl;
            cout << "Number Of Drop Kick Shot : " << NumberOfDropkickShot << endl;
            cout << "Number Of Bomb Shot : " << NumberOfBombShot << endl;
            cout << "Number Of Drill Shot : " << NumberOfDrillShot;
            PauseScreen();
            if (CounterEnemy == NumberOfEnemy)
            {
                break;
            }
        }
        else if (NumberOfBombShot == 0 && ChoiceShot == '4')
        {
            ClearArea(10, 100, 0, SizeOfMapY + 1);
            gotoxy(0, SizeOfMapY);
            cout << "\n\n";
            cout << "this shot is end ...\n";
            cout << "Please choose another one";
            PauseScreen();
        }
    }

    for (int i = 0; i <= SizeOfMapX; i++)
    {
        delete[] GridMap[i];
    }
    delete[] GridMap;

    Star = CalculatePoint(NumberOfEnemy, CounterEnemy, CounterWall,
                          UseNormalShot, UseDropkickShot, UseBombShot, UseDrillShot,
                          AllNumberOfNormalShot, AllNumberOfDropkickShot, AllNumberOfBombShot, AllNumberOfDrillShot);

    return Star;
}

short CalculatePoint(short NumberOfEnemy, short CounterEnemy, short CounterWall,
                     short UseNormalShot, short UseDropkickShot, short UseBombShot, short UseDrillShot,
                     short NumberOfNormalShot, short NumberOfDropkickShot, short NumberOfBombShot, short NumberOfDrillShot)
{
    short Star = 0;

    int SumPointAllShot = NumberOfNormalShot * 10 + NumberOfDropkickShot * 20 + NumberOfBombShot * 30 + NumberOfDrillShot * 40;
    int SumPointRemainderShot = SumPointAllShot - (UseNormalShot * 10 + UseDropkickShot * 20 + UseBombShot * 30 + UseDrillShot * 40);
    int SumPointWall = CounterWall * 5;

    if (CounterEnemy >= floor(NumberOfEnemy / 3))
    {
        Star++;
    }

    if (CounterEnemy >= floor(NumberOfEnemy * 2 / 3))
    {
        Star++;
    }

    if (CounterEnemy == NumberOfEnemy)
    {
        Star++;
    }

    // for fourth star
    if ((SumPointRemainderShot > SumPointAllShot / 2) || (SumPointWall > 30))
    {
        Star++;
    }

    return Star;
}

void SaveStar(short Level, short Star, string AddressOfProgress)
{
    // convert file to string
    string AllTextInFile;
    string Line;
    fstream File;
    File.open(AddressOfProgress, ios::in);
    while (!File.eof())
    {
        getline(File, Line);
        if (!File.eof())
        {
            AllTextInFile += Line + "\n";
        }
        else
        {
            AllTextInFile += Line;
        }
    }
    File.close();

    // edit progress
    string KeySearch;
    KeySearch = "level " + to_string(Level) + " | stars : ";
    if (AllTextInFile.find(KeySearch, 0) != string::npos)
    {
        int Pos = AllTextInFile.find(KeySearch, 0) + KeySearch.length();
        if ((AllTextInFile[Pos] - '0') <= Star)
        {
            AllTextInFile.replace(Pos, 1, to_string(Star));
        }
    }
    else
    {
        return;
    }

    // convert string to file
    File.open(AddressOfProgress, ios::out);
    File << AllTextInFile;
    File.close();
}