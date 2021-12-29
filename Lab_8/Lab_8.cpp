#include <iostream>
#include <locale.h>
#include <stdio.h>
#include <conio.h>
using namespace std;

int arrA[], arrB[];

void enter_and_format( int n)
{
    for (int i = 0;; i++)
    {
        cin >> n;
        arrA[i] = n;
    }
    _getch();
    for (int i = 0;; i++)
    {
        cin >> n;
        arrB[i] = n;
    }
}

void print()
{
    for (int i = 0;; i++)
    {
        cout << arrA[i];
    }
    cout << endl;
    for (int i = 0;; i++)
    {
        cout << arrB[i];
    }
}

int multiplication(int arrA[], int b)
{
    const maxsize = 105;
    int arrA[maxsize], b, c = 0;

    for (int i = 0 ; i < 10; i++)
    {
      arrA[i] = arrA[i] * arrB[i] + c;
      c = arrA[i] / 10;
      arrA[i] = arrA[i] % 10;
    }
    while (c > 0) 
    {
        arrA[0] = arrA[0] + 1;
        arrA[arrA[0]] = c % 10;
         c = c / 10;
    }
}

int sum(int arrA[], int arrB[])
{
    int m,c;
    const maxsize = 102;
    int arrA[maxsize], arrB[maxsize];
    m = max(arrA[0], arrB[0]);

    c = 0;
    for (int i = 0; i < m;i++) 
    {
      c = c + arrA[i] + arrB[i];
      arrA[i] = c % 10;
      c = c / 10;
    }
    if (c > 0) {
        m = m + 1;
        arrA[m] = c;
    }
    arrA[0] = m;
}

int minus()
{
    const maxsize = 1001;
    int arrA[maxsize], arrB[maxsize]; c;

    if (complong(a, b) < 0) {
        write('-');
        a <--> b;
    }

    c = 0;
    for (int i = 0;;i++) 
    {
      c = c + a[i] - b[i] + 10;
      a[i] = c % 10;
      if (c < 10) c = -1; 
      else c = 0;
    }
    while (a[a[0]] = 0 and a[0] > 1) a[0] = a[0] - 1;
}

int div()
{
    const maxsize = 101;
    int arrA[maxsize], b , x, k;
    x = 0; k = 0;
    for (int i = 0;;i++) 
    {
        x = x * 10 + arrA[i];
        if (x < b and k = 0 and i > 1) continue;
        k = 1;
        cout << (x / b);
        x = x % b;
    }
}

int mod()
{
    const maxsize = 101;
    int arrA[maxsize], b;
    int64 x = 0;
    for (int i = 0;; i++)
    {
        x = (x * 10 + arrA[i]) % b;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "Введите а:";
    enter_and_format();
    cout << "Введите b:";
    enter_and_format();
    cout << "a+b";
    cout << "a-b";
    cout << "b-a";
    cout << "a*b";
    cout << "a div b";
    cout << "b div a";
    cout << "a mod b";
    cout << "b mod a";

}

