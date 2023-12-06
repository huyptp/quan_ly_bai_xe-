#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include <ctime>
#include <string>
#include <ctype.h>
#include <fstream>
#include <chrono>
#include <iomanip> 

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

/*-------------------------------HAM SU DUNG------------------------------------*/
int Random(int min, int max);
string taoBiensoxe();
bool isEmpty(Baixe baixe[4][5]);
void park_lot();
void nhapXe(Baixe baixe[4][5]);
void luuFile();
void khoiphuc();
void luu_Baocao(Baixe bx[4][5], int& m, int& n);
void doc_Baocao();
void output_arr();
bool isHople(string car);
void timXe();
void menu();
void select();
/*-----------------CTRL + Click DE NHAY TOI HAM DINH NGHIA----------------------*/


// GET RANDOM //
int Random(int min, int  max)
{
    return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

// BIEN SO XE //
string taoBiensoxe()
{
    string bienso;
    // reset o nho cua Random
    srand((unsigned int)time(NULL));
    // tao bien so 
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


/*---------------------------------------------------BAI DO XE-------------------------------------------------------------*/
bool isEmpty(Baixe baixe[4][5])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (baixe[i][j].biensoxe == "")
                return true;
        }
    }
    return false;
}

void park_lot()
{
    int x;
retry:
    cout << "Chon bai xe muon gui (1/2/3): ";
    cin >> x;
    switch (x)
    {
    case 1:
        nhapXe(baixe1);
        break;
    case 2:
        nhapXe(baixe2);
        break;
    case 3:
        nhapXe(baixe3);
        break;
    default:
        cout << "Khong co bai xe nay, hay chon lai!" << endl;
        goto retry;
    }
}

/* OPTION 1 */
void nhapXe(Baixe baixe[4][5])
{
    bool isParked = false;
    if (isEmpty(baixe))
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (baixe[i][j].biensoxe == "")
                {
                    baixe[i][j].biensoxe = taoBiensoxe();
                    baixe[i][j].timein = time(0);
                    cout << "Gui xe thanh cong!" << endl;
                    cout << "Bien so xe: " << baixe[i][j].biensoxe << endl;
                    cout << "Xe duoc gui vao vi tri " << (char)(i + 65) << j + 1 << endl;
                    cout << "Thoi gian gui xe: " << ctime(&baixe[i][j].timein) << endl;
                    isParked = true;
                    break;
                }
            }
            if (isParked == true)
            {
                break;
            }
        }
    }
    else
    {
        cout << "Bai xe da day, khong the gui! \n";
    }
}
/*----------------------------------------------------------------------------------------------------------------------------*/

void output_arr()
{
    cout << "Bai xe 1" << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << baixe1[i][j].biensoxe << " ";
        }
        cout << endl;
    }
    cout << endl << "Bai xe 2" << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << baixe2[i][j].biensoxe << " ";
        }
        cout << endl;
    }
    cout << endl << "Bai xe 3" << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << baixe3[i][j].biensoxe << " ";
        }
        cout << endl;
    }
}

// TINH TIEN XE
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
/*---------------------------------------------------------------------------------------------*/

// BIEN SO XE HOP LE
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
        cout << "Bien so xe khong hop le! Chi duoc ton tai 1 ki tu '-' va 1 chu cai in hoa \n";
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

/* OPTION 2 */
void deleteCar(Baixe baixe[4][5], int& m, int& n)
{
    baixe[m][n].biensoxe = "";
    baixe[m][n].timein = 0;
    baixe[m][n].timeout = 0;
    baixe[m][n].tienxe = 0;
}


// Hàm chuyển đổi thời gian thành time_t
time_t convertToTimeT(int year, int month, int day, int hour, int minute, int second) {
    // Tạo một struct tm để lưu trữ thông tin về thời gian
    std::tm timeInfo = {};

    // Gán giá trị vào struct tm
    timeInfo.tm_year = year - 1900; // Năm tính từ 1900
    timeInfo.tm_mon = month - 1;    // Tháng tính từ 0 (0 - 11)
    timeInfo.tm_mday = day;
    timeInfo.tm_hour = hour;
    timeInfo.tm_min = minute;
    timeInfo.tm_sec = second;

    // Chuyển struct tm thành time_t
    std::time_t time = std::mktime(&timeInfo);

    return time;
}

time_t customTime()  
{
    // Nhập thông tin về thời gian từ người dùng
    int year, month, day, hour, minute, second;
    std::cout << "nhap ngay : ";
    std::cin >> day;
    std::cout << "nhap thang:  ";
    std::cin >> month;
    std::cout << "nhap nam : ";
    std::cin >> year;
    std::cout << "nhap gio  ";
    std::cin >> hour;
    std::cout << "nhap phut : ";
    std::cin >> minute;
    std::cout << "nhap giay: ";
    std::cin >> second;

    // Gọi hàm chuyển đổi thời gian và in ra kết quả
    time_t result = convertToTimeT(year, month, day, hour, minute, second);
    return result;
}

void time_xuatxe(Baixe bx[4][5], int& m, int& n)
{
    int x;
    cout << "chon thoi gian hien tai hay thoi gian nhap vao(1/0)  "<< endl ;
    cin >> x;
    if (x == 1)
    {
        bx[m][n].timeout = time(0);
    }
    else
    {
        bx[m][n].timeout = customTime();
    }
    time_t lech;
    lech = bx[m][n].timeout - bx[m][n].timein;
    cout << lech << endl;
    bx[m][n].tienxe = tien_xe(lech);
    cout << "Xe ra bai luc: " << ctime(&bx[m][n].timeout) << endl;
    cout << "So tien phai tra: " << bx[m][n].tienxe << "VND" << endl;
}
void xuatXe()
{
    bool isFound = false;
    int confirm, x = 0, m, n; // x - bai xe, m - so hang, n - so cot
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
            if (baixe1[i][j].biensoxe == car || baixe2[i][j].biensoxe == car || baixe3[i][j].biensoxe == car)
            {
                cout << "Xe dang o trong bai. ";
                m = i;
                n = j;
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
                isFound = true;
                break;
            }
        }
        if (isFound)
        {
            break;
        }
    }
    if (isFound)
    {
        cout << "Xac nhan xuat xe? (1/0): ";
        cin >> confirm;
        if (confirm)
        {
            cout << "OK" << endl;
            switch (x)
            {
            case 1:
                time_xuatxe(baixe1, m, n);
                luu_Baocao(baixe1, m, n);
                deleteCar(baixe1, m, n);
                break;
            case 2:
                time_xuatxe(baixe2, m, n);
                luu_Baocao(baixe2, m, n);
                deleteCar(baixe2, m, n);
                break;
            case 3:
                time_xuatxe(baixe3, m, n);
                luu_Baocao(baixe3, m, n);
                deleteCar(baixe3, m, n);
                break;
            }
        }
    }
    else
    {
        cout << "Xe khong co trong bai!" << endl;
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

/*----------------------File-------------------------*/
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

void luu_Baocao(Baixe bx[4][5], int &m, int &n)
{
    ofstream save;
    save.open("baocaohangngay.txt", ios::app);
    save << bx[m][n].biensoxe << endl;
    save << ctime(&bx[m][n].timein);
    save << ctime(&bx[m][n].timeout);
    save << bx[m][n].tienxe;
    save.close();
}

void doc_Baocao()
{
    ifstream in;
    in.open("baocaohangngay.txt");
    int total_line = 0, count = 0;
    string biensoxe, time_in, time_out, fee, lines;
    while (!in.eof())
    {
        getline(in, lines);
        total_line++;
    }
    in.clear();
    in.seekg(0, ios::beg);
    while (!in.eof())
    {
        getline(in, biensoxe);
        getline(in, time_in);
        getline(in, time_out);
        in >> fee;
        in.ignore();
        cout << biensoxe << "              " << time_in << "              " << time_out << "              " << fee << "VND" << endl;
        count += 4;
        if (count >= total_line - 3)
        {
            break;
        }
    }
    in.close();
}
/*---------------------------------------------------*/


int main()
{
    khoiphuc();
    while (true)
    {
        int n;
        cout << endl << "Ban co muon tiep tuc khong? (1/0): ";
        cin >> n;
        if (n == 1)
        {
            system("cls");
            menu();
            select();
        }
        else
        {
            luuFile();
            cout << "Ket thuc!" << endl;
            break;
        }
    }

    return 0;
  
}

void menu()
{
    cout << "                    QUAN LY 3 BAI XE (4 X 5)                      " << endl;
    cout << " *---------------------------------------------------------------*" << endl;
    cout << " | Option 1 : Gui xe vao bai                                     |" << endl;
    cout << " | Option 2 : Cho xe ra bai, tinh tien gui xe                    |" << endl;
    cout << " | Option 3 : In bao cao hang ngay                               |" << endl;
    cout << " | Option 4 : Tim vi tri cua xe                                  |" << endl;
    cout << " *---------------------------------------------------------------*" << endl;
}

void select()
{
    int choice;
    cout << "Moi chon option: ";
    cin >> choice;
    cout << endl;
    switch (choice)
    {
    case 1: //Nhap xe vao bai
        park_lot();
        break;
    case 2: //Xuat xe ra bai
        output_arr();
        xuatXe();
        break;
    case 3:// in ra bao cao
        cout << "Bien so xe             Thoi gian vao                         Thoi gian ra                          Tien gui xe" << endl;
        doc_Baocao();
        break;
    case 4:// tim xe trong bai
        timXe();
        break;
    case 5: // In mang de kiem tra
        output_arr();
        break;
    default:
        cout << "Khong co option nay!" << endl;
    }
}
