#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string>

using namespace std;

char a[40][40]; //khai bao mang 2 chieu
char key; // bien ky tu nhap vao tu ban phim

short diemX = 0, diemO = 0; // ty so
short diemX15 = 0, diemO15 = 0; 

short x, y, i, m, n, m1, n1, LuaChon; //m1 n1 xac dinh X hoac O win

void GanDL() // Lap day mang 2 chieu bang cac ky tu space
{
    for (int i = 1; i <= 34; i++)
        for (int j = 1; j <= 23; j++)
            a[i][j]=' ';
}

void fixConsoleWindow()
{
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX)& ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void SetWindow(int Width, int Height)
{
    _COORD coord;
    coord.X = Width;
    coord.Y = Height;

    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle
    SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size
    SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size
}


void MoDau(short); //mo dau tro choi
void Choi2Nguoi(); // 2p mode
void Thoat(); // exit
void HuongDan(short); // tutorial
void VeKhung(short);
void VeKhung15(short); // ve ban co
void ChoiLai();
void ChoiLai15(); // replay
void Choi2Nguoi15(); // 15 cell mode
void ThongTin();
void restore();
void SaveGame();

void Goto(int x, int y)//lam viec voi toa do trong console
{
    COORD co = {x,y}; // coordinate 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , co);
}

void TextColor(int x) //Xac dinh mau cua chu
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , x);
}

void restore()
{   
    system("cls");
    short mode;
    string name;

    cout << "Ban muon khoi phuc che do choi nao?\n1. 15x15\n2. 20x20\nLua chon: ";
    do {
        cin >> mode;
        if (mode != 1 && mode != 2);
        cout << "Xin loi, chung toi khong co che do nay, vui long nhap lai: ";
    } while (mode != 1 && mode != 2);

    switch(mode)
    {
        case 1: 
        {       
            system("cls");
            ifstream in("data15.txt", ios::in);
            in >> name >> diemX15 >> diemO15;

            cout << "\n Xin chao " << name << " ! Welcome back!";
            in.close();
            getch();
            system("cls");
            MoDau(0);  break;
        }
        default:
        {
            system("cls");
            ifstream in("data.txt", ios::in);
            in >> name >> diemX >> diemO;
            cout << "\n Xin chao " << name << " ! Welcome back!";
            in.close();
            getch();
            system("cls");
            MoDau(0);  break;
        }

    }

}

void SaveGame()
{
    string name;
    if (LuaChon == '1')
    {
        ofstream out("data15.txt", ios::out); 
        system("cls"); cout << "Ten cua ban la (viet lien khong dau): ";
        cin >> name;
        out << name << " " << diemX15 << " " << diemO15; 
    }
    else
    {
        ofstream out("data.txt", ios::out); 
        system("cls"); cout << "Ten cua ban la (viet lien khong dau): ";
        cin >> name;
        out << name << " " << diemX << " " << diemO; 
    }
    cout << "Cam on " << name << ". Chuc ban 1 ngay tot lanh.";
    getch();
    system("cls");
    MoDau(0); 

}

void CRGXO()
{
    Goto(6,26); TextColor(10); cout <<" _______  _______  _______  _______  _______  _______  _______  _______ ";
    Goto(6,27); TextColor(10); cout <<"(  ____ \\(  ___  )(  ____ )(  ___  )(  ____ \\(  ___  )(       )(  ____ \\";
    Goto(6,28); TextColor(10); cout <<"| (    \\/| (   ) || (    )|| (   ) || (    \\/| (   ) || () () || (    \\/";
    Goto(6,29); TextColor(10); cout <<"| |      | (___) || (____)|| |   | || |      | (___) || || || || (__    ";
    Goto(6,30); TextColor(10); cout <<"| |      |  ___  ||     __)| |   | || | ____ |  ___  || |(_)| ||  __)   ";
    Goto(6,31); TextColor(10); cout <<"| |      | (   ) || (\\ (   | |   | || | \\_  )| (   ) || |   | || (      ";
    Goto(6,32); TextColor(10); cout <<"| (____/\\| )   ( || ) \\ \\__| (___) || (___) || )   ( || )   ( || (____/\\";
    Goto(6,33); TextColor(10); cout <<"(_______/|/     \\||/   \\__/(_______)(_______)|/     \\||/     \\|(_______/";

    Goto(20,35); TextColor(4); cout <<"ooooooo  ooooo                 .oooooo.  ";
    Goto(20,36); TextColor(4); cout <<" `8888    d8'                 d8P'  `Y8b ";
    Goto(20,37); TextColor(4); cout <<"   Y888..8P                  888      888";
    Goto(20,38); TextColor(4); cout <<"    `8888'                   888      888";
    Goto(20,39); TextColor(4); cout <<"   .8PY888.       8888888    888      888";
    Goto(20,40); TextColor(4); cout <<"  d8'  `888b                 `88b    d88'";
    Goto(20,41); TextColor(4); cout <<"o888o  o88888o                `Y8bood8P' ";
}
//game start
short Chan(short i) // ho tro trong viec chia luot
{ 
    if (i % 2 == 0) return 1;
    else return 0;
}

char OX(short i) // Bao hieu luot cua ai danh
{
    if (Chan(i) == 1) return 'O';
    else return 'X';
}

void VeOX(short x, short y) //Ve O, X theo luot
{
    if (a[x][y] != 'X' && a[x][y] != 'O')
    {
        if (Chan(i) == 1) TextColor(11); 
        else TextColor(12);
            a[x][y] = OX(i);
        cout << a[x][y];
        i += 1;
    }
    else a[n][m];
    TextColor(7);
}

void AnSangTrai()
{
    x -= 1;
    if (x < 13) x = 13;
}

void AnSangPhai()
{
    x+=1;
    if (x >= 32) x = 32;
}

void AnLenTren()
{
    y -= 1;
    if (y < 3) y = 3;
}

void AnXuongDuoi()
{
    y += 1;
    if (y >= 22) y = 22;
}

void ConTro(short x, short y) 
{  
    Goto(x,y);
    n=x;m=y;
}

void AnSangTrai15()
{
    x -= 1;
    if (x < 18) x = 18;
}

void AnXuongDuoi15()
{
    y += 1;
    if (y >= 17) y = 17;
}

void ThongTinTranDau()
{
    TextColor(7);

    //infor

    Goto(36,2); cout << "Toa Do: " << x - 12 << "-" << y - 2 << "    Q: Quit.\n";
    Goto(36,3); cout << "Turn: " << i << "   Hello // Nhan L de save game";
    Goto(36,4); cout << "-----------------------------------------";
    
    //decor 
    
     
    Goto(36,5); TextColor(11); cout << "Player 1 dung A,D,W,S va E de danh" << endl << endl; 
    Goto(36,6); TextColor(12); cout << "Player 2 dung phim mui ten va M de danh" << endl << endl;
    Goto(36,7); TextColor(15); cout << "-----------------------------------------" << endl << endl;
    
    Goto(36,9); TextColor(15); cout << "------------";

    Goto(36,10); TextColor(15); cout << "B: Back to menu" ; Goto(57,10); TextColor(14); cout << "TY SO";
    Goto(36,11); TextColor(15); cout << "R: Choi lai\n"; Goto(53,11); TextColor(12); cout << "X = " << diemX; TextColor(15); cout << " : "; TextColor(11); cout << "O = " << diemO;

    Goto(36,12); TextColor(15); cout << "------------";

    Goto(36,13); TextColor(10); cout << "Luot cua " << OX(i); TextColor(3); cout << "    Kich co ban co: 20x20";


    CRGXO();
}

void ThongTinTranDau15()
{
    TextColor(7);

    //infor

    Goto(36,2); cout << "Toa Do: " << x - 17 << "-" << y - 2 << "    Q: Quit.\n";
    Goto(36,3); cout << "Turn: " << i << "   Hello // Nhan L de save game";
    Goto(36,4); cout << "-----------------------------------------";
    
    //decor 
    
    Goto(36,5); TextColor(11); cout << "Player 1 dung A,D,W,S va E de danh" << endl << endl; 
    Goto(36,6); TextColor(12); cout << "Player 2 dung phim mui ten va M de danh" << endl << endl;
    Goto(36,7); TextColor(15); cout << "-----------------------------------------" << endl << endl;
    
    Goto(36,9); TextColor(15); cout << "------------";

    Goto(36,10); TextColor(15); cout << "B: Back to menu" ; Goto(57,10); TextColor(14); cout << "TY SO";
    Goto(36,11); TextColor(15); cout << "R: Choi lai\n"; Goto(53,11); TextColor(12); cout << "X = " << diemX15; TextColor(15); cout << " : "; TextColor(11); cout << "O = " << diemO15;

    Goto(36,12); TextColor(15); cout << "------------";

    Goto(36,13); TextColor(10); cout << "Luot cua " <<OX(i); TextColor(3); cout << "    Kich co ban co: 15x15";

    CRGXO();
}

short DKOChienThang()
{   
    //O win

    m1 = m; n1 = n;
    while (a[n1][m] == 'O')
        n1++;
    n1--;

    //dua con tro ve dau hang

    if ((a[n1][m] == 'O') && (a[n1+1][m] == 'O') && (a[n1+2][m] == 'O') && (a[n1+3][m] == 'O') && (a[n1+4][m] == 'O') && ((a[n1+5][m] != 'X') || (a[n1-1][m] != 'X')) ) return 1; else
    if ((a[n1][m] == 'O') && (a[n1-1][m] == 'O') && (a[n1-2][m] == 'O') && (a[n1-3][m] == 'O') && (a[n1-4][m] == 'O') && ((a[n1-5][m] != 'X') || (a[n1+1][m] != 'X')) ) return 1; else
    if ((a[n1][m] == 'O') && (a[n1+1][m] == 'O') && (a[n1+2][m] == 'O') && (a[n1+3][m] == 'O') && (a[n1+4][m] == 'O') && ((a[n1+5][m] == 'X') && (a[n1-1][m] == 'X')) ) return 2; else
    if ((a[n1][m] == 'O') && (a[n1-1][m] == 'O') && (a[n1-2][m] == 'O') && (a[n1-3][m] == 'O') && (a[n1-4][m] == 'O') && ((a[n1-5][m] == 'X') && (a[n1+1][m] == 'X')) ) return 2;
    
    
    //Theo hang doc
    m1 = m; n1 = n;
    while (a[n][m1] == 'O')
        m1++;
    m1--;
    
    //Theo duong cheo chinh
    if ((a[n][m1] == 'O') && (a[n][m1+1] == 'O') && (a[n][m1+2] == 'O') && (a[n][m1+3] == 'O') && (a[n][m1+4] == 'O') && ((a[n][m1+5] != 'X') || (a[n][m1-1] != 'X')) ) return 1; else
    if ((a[n][m1] == 'O') && (a[n][m1-1] == 'O') && (a[n][m1-2] == 'O') && (a[n][m1-3] == 'O') && (a[n][m1-4] == 'O') && ((a[n][m1-5] != 'X') || (a[n][m1+1] != 'X')) ) return 1; else
    if ((a[n][m1] == 'O') && (a[n][m1+1] == 'O') && (a[n][m1+2] == 'O') && (a[n][m1+3] == 'O') && (a[n][m1+4] == 'O') && ((a[n][m1+5] == 'X') && (a[n][m1-1] == 'X')) ) return 2; else
    if ((a[n][m1] == 'O') && (a[n][m1-1] == 'O') && (a[n][m1-2] == 'O') && (a[n][m1-3] == 'O') && (a[n][m1-4] == 'O') && ((a[n][m1-5] == 'X') && (a[n][m1+1] == 'X')) ) return 2;

    
    //Theo duong cheo phu
    m1 = m; n1 = n;
    while (a[n1][m1] == 'O')
    {
        m1++; 
        n1++;
    }
    m1--; n1--;

    if ((a[n1][m1] == 'O') && (a[n1+1][m1+1] == 'O') && (a[n1+2][m1+2] == 'O') && (a[n1+3][m1+3] == 'O') && (a[n1+4][m1+4] == 'O') && ((a[n1+5][m1+5] != 'X') || (a[n1-1][m1-1] != 'X')) ) return 1; else
    if ((a[n1][m1] == 'O') && (a[n1-1][m1-1] == 'O') && (a[n1-2][m1-2] == 'O') && (a[n1-3][m1-3] == 'O') && (a[n1-4][m1-4] == 'O') && ((a[n1-5][m1-5] != 'X') || (a[n1+1][m1+1] != 'X')) ) return 1; else
    if ((a[n1][m1] == 'O') && (a[n1+1][m1+1] == 'O') && (a[n1+2][m1+2] == 'O') && (a[n1+3][m1+3] == 'O') && (a[n1+4][m1+4] == 'O') && ((a[n1+5][m1+5] == 'X') && (a[n1-1][m1-1] == 'X')) ) return 2; else
    if ((a[n1][m1] == 'O') && (a[n1-1][m1-1] == 'O') && (a[n1-2][m1-2] == 'O') && (a[n1-3][m1-3] == 'O') && (a[n1-4][m1-4] == 'O') && ((a[n1-5][m1-5] == 'X') && (a[n1+1][m1+1] == 'X')) ) return 2;


    m1 = m; n1 = n;
    while (a[n1][m1] == 'O')
    {
        n1++; m1--;
    }
    n1--; m1++;
    if ((a[n1][m1]) == 'O' && (a[n1+1][m1-1]) == 'O' && (a[n1+2][m1-2]) == 'O' && (a[n1+3][m1-3]) == 'O' && (a[n1+4][m1-4] == 'O' ) && ((a[n1+5][m1-5] != 'X') || (a[n1-1][m1+1] != 'X')) ) return 1; else
    if ((a[n1][m1]) == 'O' && (a[n1-1][m1+1]) == 'O' && (a[n1-2][m1+2]) == 'O' && (a[n1-3][m1+3]) == 'O' && (a[n1-4][m1+4] == 'O' ) && ((a[n1-5][m1+5] != 'X') || (a[n1+1][m1-1] != 'X')) ) return 1; else
    if ((a[n1][m1]) == 'O' && (a[n1+1][m1-1]) == 'O' && (a[n1+2][m1-2]) == 'O' && (a[n1+3][m1-3]) == 'O' && (a[n1+4][m1-4] == 'O' ) && ((a[n1+5][m1-5] == 'X') && (a[n1-1][m1+1] == 'X')) ) return 2; else
    if ((a[n1][m1]) == 'O' && (a[n1-1][m1+1]) == 'O' && (a[n1-2][m1+2]) == 'O' && (a[n1-3][m1+3]) == 'O' && (a[n1-4][m1+4] == 'O' ) && ((a[n1-5][m1+5] == 'X') && (a[n1+1][m1-1] == 'X')) ) return 2;

    return 0;
}

short DKXChienThang()
{ 
    //X win
    //THeo hang ngang
    m1 = m; n1 = n;
    while (a[n1][m] == 'X') {
        n1++;
    }
    n1--;
    
    if ((a[n1][m] == 'X') && (a[n1+1][m] == 'X') && (a[n1+2][m] == 'X') && (a[n1+3][m]=='X') && (a[n1+4][m] == 'X') && ((a[n1+5][m] != 'O') || (a[n1-1][m] != 'O')) ) return 1; else 
    if ((a[n1][m] == 'X') && (a[n1-1][m] == 'X') && (a[n1-2][m] == 'X') && (a[n1-3][m] == 'X') && (a[n1-4][m] == 'X') && ((a[n1-5][m] != 'O') || (a[n1+1][m] != 'O')) ) return 1; else
    if ((a[n1][m] == 'X') && (a[n1+1][m] == 'X') && (a[n1+2][m] == 'X') && (a[n1+3][m]=='X') && (a[n1+4][m] == 'X') && ((a[n1+5][m] == 'O') && (a[n1-1][m] == 'O')) ) return 2; else 
    if ((a[n1][m] == 'X') && (a[n1-1][m] == 'X') && (a[n1-2][m] == 'X') && (a[n1-3][m] == 'X') && (a[n1-4][m] == 'X') && ((a[n1-5][m] == 'O') && (a[n1+1][m] == 'O')) ) return 2;


    m1 = m; n1 = n;
    while (a[n][m1] == 'X') 
    {
        m1++;
    }
    m1--;

    if ((a[n][m1] == 'X') && (a[n][m1+1] == 'X') && (a[n][m1+2] == 'X') && (a[n][m1+3] == 'X') && (a[n][m1+4] == 'X') && ((a[n][m1+5] != 'O') || (a[n][m1-1] != 'O')) ) return 1; else 
    if ((a[n][m1] == 'X') && (a[n][m1-1] == 'X') && (a[n][m1-2] == 'X') && (a[n][m1-3] == 'X') && (a[n][m1-4] == 'X') && ((a[n][m1-5] != 'O') || (a[n][m1+1] != 'O')) ) return 1; else
    if ((a[n][m1] == 'X') && (a[n][m1+1] == 'X') && (a[n][m1+2] == 'X') && (a[n][m1+3] == 'X') && (a[n][m1+4] == 'X') && ((a[n][m1+5] == 'O') && (a[n][m1-1] == 'O')) ) return 2; else 
    if ((a[n][m1] == 'X') && (a[n][m1-1] == 'X') && (a[n][m1-2] == 'X') && (a[n][m1-3] == 'X') && (a[n][m1-4] == 'X') && ((a[n][m1-5] == 'O') && (a[n][m1+1] == 'O')) ) return 2;


    m1 = m; n1 = n;
    while (a[n1][m1] == 'X')
    {
        m1++; n1++;
    }
    m1--; n1--;
    if ((a[n1][m1] == 'X') && (a[n1+1][m1+1] == 'X') && (a[n1+2][m1+2] == 'X') && (a[n1+3][m1+3] == 'X') && (a[n1+4][m1+4] == 'X') && ((a[n1+5][m1+5] != 'O') || (a[n1-1][m1-1] != 'O')) ) return 1; else 
    if ((a[n1][m1] == 'X') && (a[n1-1][m1-1] == 'X') && (a[n1-2][m1-2] == 'X') && (a[n1-3][m1-3] == 'X') && (a[n1-4][m1-4] == 'X') && ((a[n1-5][m1-5] != 'O') || (a[n1+1][m1+1] != 'O')) ) return 1; else
    if ((a[n1][m1] == 'X') && (a[n1+1][m1+1] == 'X') && (a[n1+2][m1+2] == 'X') && (a[n1+3][m1+3] == 'X') && (a[n1+4][m1+4] == 'X') && ((a[n1+5][m1+5] == 'O') && (a[n1-1][m1-1] == 'O')) ) return 2; else 
    if ((a[n1][m1] == 'X') && (a[n1-1][m1-1] == 'X') && (a[n1-2][m1-2] == 'X') && (a[n1-3][m1-3] == 'X') && (a[n1-4][m1-4] == 'X') && ((a[n1-5][m1-5] == 'O') && (a[n1+1][m1+1] == 'O')) ) return 2;


    m1 = m; n1 = n;
    while (a[n1][m1] == 'X')
    {
        n1++; m1--;
    }
    n1--; m1++;
    if ((a[n1][m1]) == 'X' && (a[n1+1][m1-1]) == 'X' && (a[n1+2][m1-2]) == 'X' && (a[n1+3][m1-3]) == 'X' && (a[n1+4][m1-4] == 'X' ) && ((a[n1+5][m1-5] != 'O') || (a[n1+1][m1+1] != 'O')) ) return 1; else 
    if ((a[n1][m1]) == 'X' && (a[n1-1][m1+1]) == 'X' && (a[n1-2][m1+2]) == 'X' && (a[n1-3][m1+3]) == 'X' && (a[n1-4][m1+4] == 'X' ) && ((a[n1-5][m1+5] != 'O') || (a[n1-1][m1-1] != 'O')) ) return 1; else
    if ((a[n1][m1]) == 'X' && (a[n1+1][m1-1]) == 'X' && (a[n1+2][m1-2]) == 'X' && (a[n1+3][m1-3]) == 'X' && (a[n1+4][m1-4] == 'X' ) && ((a[n1+5][m1-5] == 'O') && (a[n1+1][m1+1] == 'O')) ) return 2; else 
    if ((a[n1][m1]) == 'X' && (a[n1-1][m1+1]) == 'X' && (a[n1-2][m1+2]) == 'X' && (a[n1-3][m1+3]) == 'X' && (a[n1-4][m1+4] == 'X' ) && ((a[n1-5][m1+5] == 'O') && (a[n1-1][m1-1] == 'O')) ) return 2;
        
    return 0;
}

void ChienThang()
{
    TextColor(12);
    if ((DKOChienThang()==1) || DKXChienThang()==2)
    {
        Goto(36,16);  TextColor(11); cout << " O)oooo     W)      ww I)iiii N)n   nn";
        Goto(36,17);  TextColor(11); cout << "O)    oo    W)      ww   I)   N)nn  nn";
        Goto(36,18);  TextColor(11); cout << "O)    oo    W)  ww  ww   I)   N) nn nn";
        Goto(36,19);  TextColor(11); cout << "O)    oo    W)  ww  ww   I)   N)  nnnn";
        Goto(36,20);  TextColor(11); cout << "O)    oo    W)  ww  ww   I)   N)   nnn";
        Goto(36,21);  TextColor(11); cout << " O)oooo      W)ww www  I)iiii N)    nn\n\n Press L to save game.";

        if (LuaChon == '1') diemO15++; 
        else diemO++;

        key = getch();
        if (key == 'l' || key == 'L') SaveGame();
        if (key == 'r' || key == 'R')
            {
                if (LuaChon == '1') ChoiLai15();
                else if (LuaChon == '2') ChoiLai();
            }
            else
                if (key == 'q' || key == 'Q') Thoat(); else MoDau(50);
    }
    else
        if ((DKXChienThang()==1) || DKOChienThang()==2)
        {
            Goto(36,16);  TextColor(12); cout << "X)    xx    W)      ww I)iiii N)n   nn";
            Goto(36,17);  TextColor(12); cout << " X)  xx     W)      ww   I)   N)nn  nn";
            Goto(36,18);  TextColor(12); cout << "  X)xx      W)  ww  ww   I)   N) nn nn";
            Goto(36,19);  TextColor(12); cout << "  X)xx      W)  ww  ww   I)   N)  nnnn";
            Goto(36,20);  TextColor(12); cout << " X)  xx     W)  ww  ww   I)   N)   nnn";
            Goto(36,21);  TextColor(12); cout << "X)    xx     W)ww www  I)iiii N)    nn\n\n Press L to save game.";

            if (LuaChon == '1') diemX15++; 
            else diemX++;

            key = getch();
            if (key == 'l' || key == 'L') SaveGame();
            if (key == 'r' || key == 'R') 
            {
                if (LuaChon == '1') ChoiLai15();
                else if (LuaChon == '2') ChoiLai();
            }
                else
                    if (key == 'q' || key == 'Q') Thoat(); else MoDau(50);
        }
}

void ChoiLai()
{ //Khoi phuc nguyen hien trang
    GanDL();
    i = 0; x = 13; y = 3;
    system("cls");
    ThongTinTranDau();
    VeKhung(0);
}

void ChoiLai15()
{ //Khoi phuc nguyen hien trang
    GanDL();
    i = 0; x = 18; y = 3;
    system("cls");
    ThongTinTranDau15();
    VeKhung15(0);
}

void TuongTacPhim()
{
    key = getch();
    if (key == 'a' || key == 'A' || int (key == 75)) AnSangTrai(); else
    if (key == 'd' || key == 'D' || int (key == 77)) AnSangPhai(); else
    if (key == 'w' || key == 'W' || int (key == 72)) AnLenTren(); else
    if (key == 's' || key == 'S' || int (key==80)) AnXuongDuoi(); else
    if (key == 'e' || key == 'E' || key == 'm' || key == 'M') VeOX(n,m); else
    if (key == 'l' || key == 'L') SaveGame(); else
    if (key == 'r' || key == 'R') {  if (LuaChon == '1') ChoiLai15(); else if (LuaChon == '2') ChoiLai(); }
    if (key == 'b' || key == 'B') MoDau(50);
}

void TuongTacPhim15()
{
    key = getch();
    if (key == 'a' || key == 'A' || int (key == 75)) AnSangTrai15(); else
    if (key == 'd' || key == 'D' || int (key == 77)) AnSangPhai(); else
    if (key == 'w' || key == 'W' || int (key == 72)) AnLenTren(); else
    if (key == 's' || key == 'S' || int (key == 80)) AnXuongDuoi15(); else
    if (key == 'e' || key == 'E' || key == 'm' || key == 'M') VeOX(n,m); else
    if (key == 'l' || key == 'L') SaveGame(); else
    if (key == 'r' || key == 'R') { if (LuaChon == '1') ChoiLai15(); else if (LuaChon == '2') ChoiLai();}
    if (key == 'b' || key == 'B') MoDau(50);
}


void MoDau(short n)
{
    system("cls");
    TextColor(13);
    Goto(31,7); cout << "1. 15x15 "<< endl;
    Goto(31,8); cout << "2. 20x20 ";
    Sleep(n); Goto(31,9); cout << "3. Huong Dan "<< endl;
    Sleep(n); Goto(31,10); cout << "4. Thong Tin "<< endl;
    Sleep(n); Goto(31,11); cout << "5. Khoi phuc tro choi "<< endl;
    Sleep(n); Goto(31,12); cout << "6. EXIT "<< endl;

    CRGXO();

    Sleep(n); 
    Goto(31,13); 
    TextColor(11);
    cout << "Menu: ";

    LuaChon = getch();
    cout << char (LuaChon);
    Sleep(200);
    if (LuaChon == '1') Choi2Nguoi15(); else
    if (LuaChon == '2') Choi2Nguoi(); else
    if (LuaChon == '3') HuongDan(1); else
    if (LuaChon == '4') ThongTin(); else
    if (LuaChon == '5') restore(); else 
    if (LuaChon == '6') Thoat(); else MoDau(0);
    


}

void VeKhung(short n)
{
    TextColor(15);
    short i;

    Goto(12,2);
    for (i = 0; i <= 20; i++)
    {
        cout << "*"; Sleep(n);
    }
    Goto(13,1);
    for (i = 1; i <= 9; i++)
    {
        cout << i;
    }
    cout << 0;
    Goto(23,1);
    for (i = 1; i <= 9; i++)
    {
        cout << i;
    }
    cout << 0;
    for (i = 0; i <= 21; i++) 
    {
        Goto(12,i + 2);
        Sleep(n);
        cout << "*";
    }
    for (i = 1; i <= 9; i++)
    {
        Goto(11,i + 2);
        Sleep(n);
        cout << i;
    }
    for (i = 10; i <= 20; i++)
    {
        Goto(10,i + 2);
        Sleep(n);
        cout << i;
    }
    Goto(12,23);
    for (i = 0; i <= 20; i++) 
    {
        cout << "*"; Sleep(n);
    }
    for (i = 0; i <= 21; i++) 
    {
        Goto(33,i + 2);
        Sleep(n);
        cout << "*";
    }
}

void BatDau()
{
    system("cls");
    HuongDan(2);
    system("cls");
    VeKhung(3);
}

void BatDau15()
{
    system("cls");
    HuongDan(2);
    system("cls");
    VeKhung15(3);
}

void VeKhung15(short n)
{
    TextColor(15);
    short i;



    Goto(17,2);
    for (i = 0; i <= 15; i++)
    {
        cout << "*"; Sleep(n);
    }
    Goto(18,1);
    for (i = 1; i <= 9; i++)
    {
        cout << i;
    }
    cout << 0;
    Goto(28,1);
    for (i = 1; i <= 5; i++)
    {
        cout << i;
    }
    for (i = 0; i <= 16; i++) 
    {
        Goto(17,i + 2);
        Sleep(n);
        cout << "*";
    }
    for (i = 1; i <= 9; i++)
    {
        Goto(16,i+2);
        Sleep(n);
        cout << i;
    }
    for (i=10; i<=15; i++)
    {
        Goto(15,i + 2);
        Sleep(n);
        cout << i;
    }
    Goto(17,18);
    for (i = 0; i <= 15; i++) 
    {
        cout << "*"; Sleep(n);
    }
    for (i = 0; i <= 16; i++) 
    {
        Goto(33,i+2);
        Sleep(n);
        cout << "*";
    }
}
void Choi2Nguoi15()
{
    BatDau15();
    x = n = 18; y = m =3;
    i = 0;
    do{
        ThongTinTranDau15();
        ConTro(x,y);
        ChienThang();
        TuongTacPhim15();
    } while (key != 'q' && key != 'Q');
    Thoat();
}


void Choi2Nguoi()
{
    BatDau();
    x = n = 13; y = m = 3;
    i = 0;
    do {
        ThongTinTranDau();
        ConTro(x,y);
        ChienThang();
        TuongTacPhim();
    } while (key != 'q' && key != 'Q');
    Thoat();
}

void HuongDan(short k)
{
    TextColor(12); cout << endl << endl << "                             HUONG DAN" << endl << endl;
    TextColor(15); cout << "\n" << "             Dung phim "; TextColor(12); cout << "mui ten"; TextColor(15); cout << " va"; TextColor(11); cout << " A D S W "; TextColor(15); cout << " de di chuyen,"; TextColor(11); cout <<" E"; TextColor(15); cout <<" va"; TextColor(12); cout <<" M"; TextColor(15); cout <<" de danh.\n\n\n\n\n\n";
    system("pause");
    if (k == 1) MoDau(0);
}

void Thoat()
{
    system("cls");
    TextColor(13);
    Goto(5,9); cout <<".___________. __    __       ___      .__   __.  __  ___        ";
    Goto(5,10); cout <<"|           ||  |  |  |     /   \\     |  \\ |  | |  |/  /    ";
    Goto(5,11); cout <<"`---|  |----`|  |__|  |    /  ^  \\    |   \\|  | |  '  /      ";
    Goto(5,12); cout <<"    |  |     |   __   |   /  /_\\  \\   |  . `  | |    <        ";
    Goto(5,13); cout <<"    |  |     |  |  |  |  /  _____  \\  |  |\\   | |  .  \\      ";
    Goto(5,14); cout <<"    |__|     |__|  |__| /__/     \\__\\ |__| \\__| |__|\\__\\      ";

    Goto(9,16); cout <<"____    ____  ______    __    __ ";
    Goto(9,17); cout <<"\\   \\  /   / /  __  \\  |  |  |  |";
    Goto(9,18); cout <<" \\   \\/   / |  |  |  | |  |  |  |";
    Goto(9,19); cout <<"  \\_    _/  |  |  |  | |  |  |  |";
    Goto(9,20); cout <<"    |  |    |  `--'  | |  `--'  |";
    Goto(9,21); cout <<"    |__|     \\______/   \\______/ ";

    Goto(9,23); cout <<"     ___      .__   __.  _______  ";
    Goto(9,24); cout <<"    /   \\     |  \\ |  | |       \\ ";
    Goto(9,25); cout <<"   /  ^  \\    |   \\|  | |  .--.  |";
    Goto(9,26); cout <<"  /  /_\\  \\   |  . `  | |  |  |  |";
    Goto(9,27); cout <<" /  _____  \\  |  |\\   | |  '--'  |";
    Goto(9,28); cout <<"/__/     \\__\\ |__| \\__| |_______/ ";

    Goto(3,31); cout <<"  _______   ______     ______    _______  .______   ____    ____  _______ ";
    Goto(3,32); cout <<" /  _____| /  __  \\   /  __  \\  |       \\ |   _  \\  \\   \\  /   / |   ____|";
    Goto(3,33); cout <<"|  |  __  |  |  |  | |  |  |  | |  .--.  ||  |_)  |  \\   \\/   /  |  |__   ";
    Goto(3,34); cout <<"|  | |_ | |  |  |  | |  |  |  | |  |  |  ||   _  <    \\_    _/   |   __|  ";
    Goto(3,35); cout <<"|  |__| | |  `--'  | |  `--'  | |  '--'  ||  |_)  |     |  |     |  |____ ";
    Goto(3,36); cout <<" \\______|  \\______/   \\______/  |_______/ |______/      |__|     |_______|\n\n\n";
                                                                          
    getch();
    ExitProcess(0);
}

void ThongTin() 
{
    system("cls");
    Goto(22,16); TextColor(2); cout << "// Nguyen Ngoc Thien An";
    Goto(22,17); TextColor(2); cout << "// e-mail: admin@thienan138.com";
    Goto(22,18); TextColor(2); cout << "// Website: https://thienan138.com/";
    getch();
    MoDau(100);
}

int main()
{
    fixConsoleWindow(); // co dinh console
    SetWindow(105, 50); // console's size
    GanDL();
    MoDau(100);
}
