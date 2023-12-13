#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <string>
#include <ctype.h>
#include <fstream>
#include <conio.h>
using namespace std;

const string chucai = "QWERTYUIOPASDFGHJKLZXCVBNM1234567890";

struct Baixe
{
    string biensoxe = "";
    time_t timein = 0;
    time_t timeout = 0;
    double tienxe = 0;
};

Baixe baixe1[4][5];
Baixe baixe2[4][5];
Baixe baixe3[4][5];

/*--------------------------------FUNCTIONS-------------------------------------*/
int Random(int min, int  max);
string taoBiensoxe();
bool isEmpty(Baixe bx[4][5]);
void park(Baixe bx[4][5]);
double tien_xe(time_t secs);
bool isHople(string car);
void showArr();
void deleteCar(Baixe bx[4][5], int& m, int& n);
time_t convertTime(int year, int month, int day, int hour, int minute, int second);
time_t customTime();
void time_xuatxe(Baixe bx[4][5], int& m, int& n);
void luuFile();
void khoiphuc();
void luuBaocao(Baixe bx[4][5], int& m, int& n);
/*                                 OPTIONS                                      */
void nhapXe();
void xuatXe();
void docBaocao();
void timXe();
/*                                  MAIN                                        */
void menu();
void select();
/*------------------------------------------------------------------------------*/


// Lay so ngau nhien
int Random(int min, int  max)
{
    return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

// Khoi tao bien so xe
string taoBiensoxe()
{
    string bienso;
    // Cung cap o nho moi cho Random()
    srand((int)time(0));
    // Tao bien so xe
    for (int i = 0; i < 9; i++)
    {
        if (i == 2)
        {
            bienso += '-';
            continue;
        }
        if (i == 3)
            bienso += chucai[Random(0, 25)];
        else
            bienso += chucai[Random(26, 35)];
    }
    return bienso;
}


// Kiem tra bai xe con vi tri
bool isEmpty(Baixe bx[4][5])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (bx[i][j].biensoxe == "")
                return true;
        }
    }
    return false;
}

/* OPTION 1 */
void nhapXe()
{
    int x;
retry:
    cout << "Chon bai xe muon gui (1/2/3): ";
    cin >> x;
    switch (x)
    {
    case 1:
        park(baixe1);
        break;
    case 2:
        park(baixe2);
        break;
    case 3:
        park(baixe3);
        break;
    default:
        cout << "Khong co bai xe nay, hay chon lai!" << endl;
        goto retry;
    }
}

// Gui xe vao bai
void park(Baixe bx[4][5])
{
    if (isEmpty(bx))
    {
    retry:
        int i = Random(0, 3);
        int j = Random(0, 4);
        if (bx[i][j].biensoxe == "")
        {
            bx[i][j].biensoxe = taoBiensoxe();
            bx[i][j].timein = time(0);
            cout << "Gui xe thanh cong!" << endl;
            cout << "Bien so xe: " << bx[i][j].biensoxe << endl;
            cout << "Xe duoc gui vao vi tri " << (char)(i + 65) << j + 1 << endl;
            cout << "Thoi gian gui xe: " << ctime(&bx[i][j].timein);
        }
        else
        {
            goto retry;
        }
    }
    else
    {
        cout << "Bai xe da day, khong the gui!" << endl;
    }
}

// Tinh tien xe
double tien_xe(time_t secs)
{
    double sum = 50000, dem = -1;
    while (secs > 0)
    {
        secs -= 1800;
        dem++;
    }
    sum += dem * 30000;
    return sum;
}

// Kiem tra bien so xe hop le
bool isHople(string car)
{
    // Du 9 ki tu
    int count = 0;
    if (car.length() != 9)
    {
        cout << "Bien so xe khong hop le! Bien so xe phai co 9 ki tu \n";
        return false;
    }
    // So ki tu hop le
    for (char x : car)
    {
        if (isdigit(x))
        {
            count++;
        }
    }
    if (count < 7)
    {
        cout << "Bien so xe khong hop le! Chi duoc ton tai 7 chu so, 1 ki tu '-' va 1 chu cai in hoa \n";
        return false;
    }
    // Ki tu so 3 la '-'
    if (car[2] != '-')
    {
        cout << "Bien so xe khong hop le! Can 1 ki tu '-' o vi tri so 3 \n";
        return false;
    }
    // Ki tu so 4 la chu cai in hoa
    if (!isupper(car[3]))
    {
        cout << "Bien so xe khong hop le! Can 1 chu cai in hoa o vi tri so 4 \n";
        return false;
    }
    return true;
}

// Show bai xe ra man hinh
void showArr()
{
    cout << "Bai xe 1" << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (baixe1[i][j].biensoxe == "")
            {
                cout << "         ";
            }
            cout << baixe1[i][j].biensoxe << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Bai xe 2" << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (baixe2[i][j].biensoxe == "")
            {
                cout << "         ";
            }
            cout << baixe2[i][j].biensoxe << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Bai xe 3" << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (baixe3[i][j].biensoxe == "")
            {
                cout << "         ";
            }
            cout << baixe3[i][j].biensoxe << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Xoa thong tin xe
void deleteCar(Baixe bx[4][5], int& m, int& n)
{
    bx[m][n].biensoxe = "";
    bx[m][n].timein = 0;
    bx[m][n].timeout = 0;
    bx[m][n].tienxe = 0;
}


// Chuyen doi thoi gian nhap vao
time_t convertTime(int year, int month, int day, int hour, int minute, int second)
{
    // Struct luu thong tin ve thoi gian
    tm custom = {};

    // Gan gia tri cho struct
    custom.tm_year = year - 1900; // Nam tinh tu 1900
    custom.tm_mon = month - 1;    // Thang tinh tu 0 - 11
    custom.tm_mday = day;
    custom.tm_hour = hour;
    custom.tm_min = minute;
    custom.tm_sec = second;

    // Chuyen doi thoi gian thanh so giay
    time_t time = mktime(&custom);

    return time;
}

// Nhap thoi gian
time_t customTime()
{
    int year, month, day, hour, minute, second;
    cout << "Nhap ngay: "; cin >> day;
    cout << "Nhap thang: "; cin >> month;
    cout << "Nhap nam: "; cin >> year;
    cout << "Nhap gio: "; cin >> hour;
    cout << "Nhap phut: "; cin >> minute;
    cout << "Nhap giay: "; cin >> second;

    // Chuyen doi thoi gian nhap vao thanh so giay
    time_t result = convertTime(year, month, day, hour, minute, second);

    return result;
}

// Chon thoi gian xuat xe
void time_xuatxe(Baixe bx[4][5], int& m, int& n)
{
retry:
    cout << "1: Lay thoi gian hien tai | 0: Lay thoi gian nhap vao: ";
    switch (_getche())
    {
    case 49:
        cout << endl;
        bx[m][n].timeout = time(0);
        break;
    case 48:
        cout << endl;
    try_again:
        bx[m][n].timeout = customTime();
        if (bx[m][n].timeout < time(0))
        {
            cout << "Vui long nhap thoi gian lon hon thoi gian hien tai!" << endl;
            goto try_again;
        }
        break;
    default:
        cout << endl << "Lua chon khong hop le. Vui long nhap lai" << endl;
        goto retry;
    }
    time_t lech;
    lech = bx[m][n].timeout - bx[m][n].timein;
    bx[m][n].tienxe = tien_xe(lech);
    cout << endl << "Xuat xe thanh cong!" << endl;
    cout << "Xe da ra bai luc: " << ctime(&bx[m][n].timeout);
    cout << "So tien phai tra: " << bx[m][n].tienxe << "VND" << endl;
}

/* OPTION 2 */
void xuatXe()
{
    bool isFound = false;
    int x = 0, m, n; // x - bai xe, m - so hang, n - so cot
    string car;
retry:
    cout << "Nhap bien so xe muon xuat: ";
    cin >> car;
    if (!isHople(car))
    {
        goto retry;
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (baixe1[i][j].biensoxe == car)
            {
                x = 1;
            }
            if (baixe2[i][j].biensoxe == car)
            {
                x = 2;
            }
            if (baixe3[i][j].biensoxe == car)
            {
                x = 3;
            }
            if (x == 0)
            {
                continue;
            }
            m = i;
            n = j;
            isFound = true;
            break;
        }
        if (isFound)
        {
            break;
        }
    }
    if (isFound)
    {
        cout << "Xac nhan xuat xe? (Key/ESC)" << endl;
        if (_getch() != 27)
        {
            switch (x)
            {
            case 1:
                time_xuatxe(baixe1, m, n);
                luuBaocao(baixe1, m, n);
                deleteCar(baixe1, m, n);
                break;
            case 2:
                time_xuatxe(baixe2, m, n);
                luuBaocao(baixe2, m, n);
                deleteCar(baixe2, m, n);
                break;
            case 3:
                time_xuatxe(baixe3, m, n);
                luuBaocao(baixe3, m, n);
                deleteCar(baixe3, m, n);
                break;
            }
        }
        else
        {
            cout << "Ban da tu choi xuat xe ra bai!" << endl;
        }
    }
    else
    {
        cout << "Xe khong co trong bai! Ban co muon nhap lai khong? (Key/ESC)" << endl;
        if (_getch() != 27)
        {
            goto retry;
        }
        else
        {
            cout << "Ban da tu choi nhap lai!" << endl;
        }
    }
}

/* OPTION 4 */
void timXe()
{
    int x = 0;
    bool isFound = false;
    string car;
retry:
    cout << "Nhap bien so xe muon tim: ";
    cin >> car;
    if (!isHople(car))
    {
        goto retry;
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (baixe1[i][j].biensoxe == car)
            {
                x = 1;
            }
            if (baixe2[i][j].biensoxe == car)
            {
                x = 2;
            }
            if (baixe3[i][j].biensoxe == car)
            {
                x = 3;
            }
            if (x == 0)
            {
                continue;
            }
            cout << "Tim thay xe o bai xe so " << x << ", vi tri " << (char)(i + 65) << j + 1 << endl;
            isFound = true;
            break;
        }
        if (isFound)
        {
            break;
        }
    }
    if (!isFound)
    {
        cout << "Khong tim thay xe trong bai!" << endl;
    }
}

/*-------------------------File----------------------------*/
void luuFile()
{
    ofstream save1, save2, save3;
    save1.open("khoiphucbaixe1.txt", ios::out);
    save2.open("khoiphucbaixe2.txt", ios::out);
    save3.open("khoiphucbaixe3.txt", ios::out);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            //Baixe1
            save1 << baixe1[i][j].biensoxe << endl;
            save1 << baixe1[i][j].timein << endl;
            //Baixe2
            save2 << baixe2[i][j].biensoxe << endl;
            save2 << baixe2[i][j].timein << endl;
            //Baixe3
            save3 << baixe3[i][j].biensoxe << endl;
            save3 << baixe3[i][j].timein << endl;
        }
    }
    save1.close();
    save2.close();
    save3.close();
}

void khoiphuc()
{
    int total = 0, count = 0;
    string xe;
    time_t time;
    ifstream recover1, recover2, recover3;
    recover1.open("khoiphucbaixe1.txt");
    recover2.open("khoiphucbaixe2.txt");
    recover3.open("khoiphucbaixe3.txt");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            //Baixe1
            getline(recover1, xe);
            baixe1[i][j].biensoxe = xe;
            recover1 >> time;
            baixe1[i][j].timein = time;
            recover1.ignore();
            //Baixe2
            getline(recover2, xe);
            baixe2[i][j].biensoxe = xe;
            recover2 >> time;
            baixe2[i][j].timein = time;
            recover2.ignore();
            //Baixe3
            getline(recover3, xe);
            baixe3[i][j].biensoxe = xe;
            recover3 >> time;
            baixe3[i][j].timein = time;
            recover3.ignore();
        }
    }
    recover1.close();
    recover2.close();
    recover3.close();
}

void luuBaocao(Baixe bx[4][5], int& m, int& n)
{
    ofstream save;
    save.open("baocaohangngay.txt", ios::app);
    if (!save.is_open())
    {
        save.open("baocaohangngay.txt", ios::out);
    }
    save << bx[m][n].biensoxe << endl;
    save << ctime(&bx[m][n].timein);
    save << ctime(&bx[m][n].timeout);
    save << bx[m][n].tienxe << endl;
    save << "";
    save.close();
}

/* OPTION 3 */
void docBaocao()
{
    fstream in;
    in.open("baocaohangngay.txt");
    if (!in.is_open())
    {
        in.open("baocaohangngay.txt", ios::out);
    }
    int total_line = 0, count = 0;
    string biensoxe, time_in, time_out, fee, lines;
    while (!in.eof())
    {
        getline(in, lines);
        total_line++;
    }
    in.clear();
    in.seekg(0, ios::beg);
    if (total_line != 1)
    {
        cout << "Bien so xe      |       Thoi gian vao                  |       Thoi gian ra                   |       Tien gui xe" << endl;
        while (!in.eof())
        {
            getline(in, biensoxe);
            getline(in, time_in);
            getline(in, time_out);
            in >> fee;
            in.ignore();
            cout << biensoxe << "       |       " << time_in << "       |       " << time_out << "       |       " << fee << "VND" << endl;
            count += 4;
            if (count >= total_line - 3)
            {
                cout << "Tong so xe da gui: " << total_line / 4 << endl;
                break;
            }
        }
    }
    else
    {
        cout << "Khong co bao cao duoc ghi nhan!" << endl;
    }
    in.close();
}
/*---------------------------------------------------------*/


int main()
{
    khoiphuc();
    do
    {
        system("cls");
        menu();
        select();
        cout << endl << "Nhan phim bat ki de tiep tuc hoac ESC de thoat chuong trinh" << endl;
    } while (_getch() != 27);
    luuFile();
    cout << "Ban da thoat chuong trinh!" << endl;
    return 0;
}

void menu()
{
    cout << "                    QUAN LY 3 BAI XE (4 X 5)                      " << endl;
    cout << " *---------------------------------------------------------------*" << endl;
    cout << " | Option 1 : Gui xe vao bai                                     |" << endl;
    cout << " | Option 2 : Xuat xe ra bai, tinh tien giu xe                   |" << endl;
    cout << " | Option 3 : In bao cao hang ngay                               |" << endl;
    cout << " | Option 4 : Tim vi tri cua xe                                  |" << endl;
    cout << " *---------------------------------------------------------------*" << endl;
}

void select()
{
    int choice;
    cout << "Lua chon cua ban: ";
    cin >> choice;
    system("cls");
    switch (choice)
    {
    case 1: //Nhap xe vao bai
        nhapXe();
        break;
    case 2: //Xuat xe ra bai
        showArr();
        xuatXe();
        break;
    case 3: // In ra bao cao
        docBaocao();
        break;
    case 4: // Tim xe trong bai
        showArr();
        timXe();
        break;
    case 100: // In mang de kiem tra
        showArr();
        break;
    default:
        cout << "Khong co option nay!" << endl;
    }
}