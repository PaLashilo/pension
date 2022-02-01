// MENU.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <fstream>
#include <tchar.h>
#include <stdio.h>


using namespace std;
string name;
int success;
const double delay_fixed[] = { 1, 1.056, 1.12, 1.19, 1.27, 1.36, 1.46, 1.58, 1.73, 1.9, 2.11 };
const double delay_unfixed[] = { 1, 1.07, 1.15, 1.24, 1.34, 1.45, 1.59, 1.74, 1.9, 2.09, 2.32 };
const vector <string> years = { "", " год ", " года ", " года ", " года ", " лет ", " лет ", " лет ", " лет ", " лет ", " лет " };

//Полякова Мария
void gotoxy(int x, int y)
{
    COORD p = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

//Полякова Мария
void aboutAuthor()
{
    system("cls");
    cout << " Пашинская Пелагея" << endl;
    cout << " Коваленко Дарья" << endl;
    cout << " Полякова Мария" << endl;
    cout << " Степанычев Артем" << endl;
    system("pause");
}

//Полякова Мария
void showMenu()
{
    system("cls");
    cout << " Расчет пенсии" << endl;
    cout << " Вопросы (после расчета пенсии)" << endl;
    cout << " Разработчики" << endl;
    cout << " Выход";
}

//Полякова Мария
void showQuestions()
{
    system("cls");
    cout << " Изменение фактора" << endl;
    cout << " Хочу такую пенсию" << endl;
    cout << " \nНажмите esc, чтобы вернуться в главное меню";
}

//Полякова Мария
void showChoose()
{
    system("cls");
    cout << " Ввод с клавиатуры" << endl;
    cout << " Ввод из файла" << endl;
}

//Пашинская Пелагея
vector <double> delay_data(int delay_years) {
    return { delay_fixed[delay_years > 10 ? 10 : delay_years], delay_unfixed[delay_years > 10 ? 10 : delay_years] };
}

//Коваленко Дарья
double child_point(int child, int child_years) {
    double sum;
    vector <double> points{ 0, 1.8, 5.4, 10.8, 16.2 };
    if (child_years == 0 || child == 0) {
        return 0;
    }
    return (child < 5 ? points[child] : points[4]);
    return (child < 5 ? points[child] * 1.5 : points[4] * 1.5);
}

//Степанчев Артем
double wage_point(int salary) {
    double points = ((salary * 12 * 0.16) / 234146.341) * 10;
    if (points > 10) return 10;
    else return points;
}

//Степанчев Артем
double dop_point(int army_years, int invalid_years) {
    double add_points = (army_years + invalid_years) * 1.8;
    return add_points;
}

//Коваленко Дарья
double pension(int wage, int work_years, int child, int child_years, int army_years, int inv_years, int delay_years) {
    vector <double> k = delay_data(delay_years);
    double fixed_part = 6044.48 * k[0];
    double unfixed_part = (child_point(child, child_years) + wage_point(wage) * work_years + dop_point(inv_years, army_years)) * 98.86 * k[1];
    return fixed_part + unfixed_part;
}

//Коваленко Дарья
int delay_factor(int desire_pension, int wage, int work_years, int child, int child_years, int army_years, int inv_years) {
    double pension(int wage, int work_years, int child, int child_years, int army_years, int inv_years, int delay_years);
    for (int i = 1; i <= 10; i++) {
        if (pension(wage, work_years, child, child_years, army_years, inv_years, i) >= desire_pension) {
            return i;
        }
    }
    return 0;
}

//Коваленко Дарья
int work_years_factor(int desire_pension, int wage, int work_years, int child, int child_years, int army_years, int inv_years) {
    double pension(int wage, int work_years, int child, int child_years, int army_years, int inv_years, int delay_years);
    for (int i = work_years; i <= 54; i++) {
        if (pension(wage, i, child, child_years, army_years, inv_years, 10) >= desire_pension) {
            return i;
        }
    }
    return 0;
}

//Коваленко Дарья
int wage_factor(int desire_pension, int wage, int work_years, int child, int child_years, int army_years, int inv_years) {
    double pension(int wage, int work_years, int child, int child_years, int army_years, int inv_years, int delay_years);
    for (int i = wage; i <= 123000; i += 1000) {
        if (pension(i, work_years, child, child_years, army_years, inv_years, 10) >= desire_pension) {
            return i;
        }
    }
    return 0;
}

//Коваленко Дарья
vector <int> wage_work_years_factors(int desire_pension, int wage, int work_years, int child, int child_years, int army_years, int inv_years) {
    double pension(int wage, int work_years, int child, int child_years, int army_years, int inv_years, int delay_years);
    for (int i = wage; i <= 123000; i += 1000) {
        for (int j = work_years; j <= 54; j++) {
            if (pension(i, j, child, child_years, army_years, inv_years, 10) >= desire_pension) {
                return { i, j };
            }
        }
    }
    return { 0, 0 };
}

//Коваленко Дарья
int question_change_factors(int wage, int work_years, int child, int child_years, int army_years, int inv_years, int delay_years) {
    double pension(int wage, int work_years, int child, int child_years, int army_years, int inv_years, int delay_years);
    cout << "Ваша прошлая пенсия: " << pension(wage, work_years, child, child_years, army_years, inv_years, delay_years) << endl;
    int desire_pension, k;
    cout << "Введите пенсию, которую хотите иметь: ";
    cin >> desire_pension;
    if (desire_pension > pension(200000, 54, child, child_years, army_years, inv_years, 10)) {
        cout << "\nТакую высокую пенсию невозможно получать\n";
        return 0;
    }
    k = delay_factor(desire_pension, wage, work_years, child, child_years, army_years, inv_years);
    if (k != 0) {
        cout << "\nЖелаемый размер пенсии можно получить, если " << k << years[k] << "после возникновения права на страховую пенсию не обращаться за ней" << endl;
        return 0;
    }
    k = work_years_factor(desire_pension, wage, work_years, child, child_years, army_years, inv_years);
    if (k != 0) {
        cout << "\nЖелаемый размер пенсии можно получить, если стаж составит " << k << years[k % 10] << "и если после возникновения права на страховую пенсию не обращаться за ней 10 лет" << endl;
        return 0;
    }
    k = wage_factor(desire_pension, wage, work_years, child, child_years, army_years, inv_years);
    if (k != 0) {
        cout << "\nЖелаемый размер пенсии можно получить, если зарплата составит " << k << " руб и если после возникновения права на страховую пенсию не обращаться за ней 10 лет" << endl;
        return 0;
    }
    vector <int> a = wage_work_years_factors(desire_pension, wage, work_years, child, child_years, army_years, inv_years);
    cout << "\nЖелаемый размер пенсии можно получить, если зарплата составит " << a[0] << " руб, а стаж составит " << a[1] << years[a[1] % 10] << " и если после возникновения права на страховую пенсию не обращаться за ней 10 лет" << endl;
    return 0;
}

//Пашинская Пелагея
int question_change_pen(int wage, int expir, int child, int child_years, int arm, int inv, int delay) {
    cout << "*Меняем фактор*\n1. зп\n2. стаж\n3. кол-во детей\n4. кол-во лет на уход за каждым из них\n5. армия\n6. инвалиды\n7. не обращаться\n\nВведите номер фактора для изменения: ";
    int num;
    cin >> num;
    vector <int> v = { wage, expir, child, child_years, arm, inv, delay };
    cout << "\nПрошлая величина: " << v[num - 1];
    cout << "\nВведите новую величину выбранного фактора: ";
    cin >> v[num - 1];
    double new_pen = pension(v[0], v[1], v[2], v[3], v[4], v[5], v[6]);
    double prev_pen = pension(wage, expir, child, child_years, arm, inv, delay);
    string ch = new_pen > prev_pen ? "увеличится" : "уменьшится";
    cout << "\nВаша новая пенсия: " << new_pen << "\nВаша пенсия " + ch + " на " << abs(new_pen - prev_pen) << endl;
    return 0;
}

//Пашинская Пелагея
void console(int& wage, int& expir, int& child, int& child_years, int& arm, int& inv, int& delay) {
    system("cls");
    cout << "*Расчет пенсии*";
    cout << "\n\nВведите следующие данные";

    cout << "\nваша зарплата: ";
    cin >> wage;

    cout << "ваш стаж(полных лет): ";
    cin >> expir;

    cout << "кол-во детей: ";
    cin >> child;

    cout << "кол-во лет на уход за каждым из них: ";
    cin >> child_years;

    cout << "сколько лет служили в армии: ";
    cin >> arm;

    cout << "сколько лет вы будуте ухаживать за нетрудоспособными гражданами: ";
    cin >> inv;

    cout << "сколько лет вы готовы не обращаться за пенсией: ";
    cin >> delay;
}

//Степанчев Артем
void output() {
    cout << "Создайте текстовый файл(.txt) в папке, в которую вы сохранили данную программу" << endl << "Далее введите данные в следующем порядке с переходом на новую строку" << endl;
    vector <string> info = { "Ваша зарплата", "Ваш стаж", "Кол-во детей", "Кол-во лет, проведённыых за уходом каждого из них", "Сколько лет служили в армии", "сколько лет вы будуте ухаживать за нетрудоспособными гражданами", "Сколько лет вы готовы не обращаться за пенсией" };
    for (auto i : info) cout << i << endl;
    cout << "Введите имя файла: ";
}


void s(string name, int& wage, int& expir, int& child, int& child_years, int& arm, int& inv, int& delay) {
    ifstream inf(name);
    string num;
    vector <int> a;
    if (inf.is_open()) {
        while (getline(inf, num)) {
            int b;
            b = stoi(num);
            a.push_back(b);
        }
    }
    inf.close();
    if (!(inf.is_open())) success = 1;
    wage = a[0]; expir = a[1]; child = a[2]; child_years = a[3]; arm = a[4]; inv = a[5]; delay = a[6];
}


void file(int& wage, int& expir, int& child, int& child_years, int& arm, int& inv, int& delay, int success = 0) {
    output();
    cin >> name;
    ifstream inf(name);
    do
        try {
        if (!inf) throw 1;
        else throw 2;
    }
    catch (int e) {
        if (e == 1) {
            cout << "Такого файла не существует. Введите новое имя файла:" << endl;
            cin >> name;
            ifstream inf(name);
            if (inf.is_open()) success = 1;
            else continue;
            string num;
            vector <int> a;
            if (inf.is_open()) {
                while (getline(inf, num)) {
                    int b = stoi(num);
                    a.push_back(b);
                }
            }
            inf.close();
            wage = a[0]; expir = a[1]; child = a[2]; child_years = a[3]; arm = a[4]; inv = a[5]; delay = a[6];
        }
        else if (e == 2)
            s(name, wage, expir, child, child_years, arm, inv, delay);
        success = 1;
    }
    while (success == 0);
}

//Полякова Мария
void menu() {
    int wage, expir, child, child_years, arm, inv, delay;
    std::system("color F9");

    system("cls");
    const int NUM_MENU_ITEMS = 4, NUM_QUIZ_ITEMS = 2, NUM_CHOOSE_ITEMS = 2;
    int activequizitem = 0, activemenuitem = 0, activechooseitem = 0;
    int ch = 0, ch2 = 0, ch3 = 0;
    bool exit = false;
loop:
    while (!exit) {
        showMenu();
        gotoxy(0, activemenuitem);
        ch = _getch();
        if (ch == 224)
            ch = _getch();
        switch (ch) {
        case 27: exit = true; break;
        case 72: activemenuitem--; break;
        case 80: activemenuitem++; break;
        case 13:
            if (activemenuitem == 0) {
                while (exit != true) {
                    showChoose();
                    gotoxy(0, activechooseitem);
                    ch3 = _getch();
                    if (ch3 == 224)
                        ch3 = _getch();
                    switch (ch3) {
                    case 27: goto loop;
                        exit = true; break;
                    case 72: activechooseitem--; break;
                    case 80: activechooseitem++; break;
                    case 13:
                        system("cls");
                        activechooseitem == 0 ? console(wage, expir, child, child_years, arm, inv, delay) : file(wage, expir, child, child_years, arm, inv, delay);
                        cout << "\nВаша пенсия составит: " << pension(wage, expir, child, child_years, arm, inv, delay) << " рублей\n" << endl;
                        system("pause");
                        goto loop;

                    }
                    if (activechooseitem < 0) activechooseitem = 0;
                    if (activechooseitem > NUM_CHOOSE_ITEMS - 1) activechooseitem = NUM_CHOOSE_ITEMS - 1;
                }
            }
            else if (activemenuitem == 1) {
                while (exit != true) {
                    showQuestions();
                    gotoxy(0, activequizitem);
                    ch2 = _getch();
                    if (ch2 == 224)
                        ch2 = _getch();
                    switch (ch2) {
                    case 27: goto loop;
                        exit = true; break;
                    case 72: activequizitem--; break;
                    case 80: activequizitem++; break;
                    case 13:
                        system("cls");
                        (activequizitem == 0) ? question_change_pen(wage, expir, child, child_years, arm, inv, delay) : question_change_factors(wage, expir, child, child_years, arm, inv, delay);
                        system("pause");
                    }
                    if (activequizitem < 0) activequizitem = 0;
                    if (activequizitem > NUM_QUIZ_ITEMS - 1) activequizitem = NUM_QUIZ_ITEMS - 1;
                }
            }
            else if (activemenuitem == 2) {
                aboutAuthor();
            }
            else if (activemenuitem == 3) {
                exit = true;
            }
            break;
        }
        if (activemenuitem < 0) activemenuitem = 0;
        if (activemenuitem > NUM_MENU_ITEMS - 1) activemenuitem = NUM_MENU_ITEMS - 1;
    }
}

// Пашинская Пелагея
int main()
{
    setlocale(LC_ALL, "Russian");
    menu();
}
