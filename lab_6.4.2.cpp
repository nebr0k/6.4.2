#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;


void Create(double* a, const int size, const double Low, const double High, int i) {
    if (i < size)
    {
        a[i] = (High - Low) * rand() / RAND_MAX + Low;
        return Create(a, size, Low, High, ++i);
    }
}

void Print(double* a, const int size, int i)
{
    if (i < size) {
        cout << fixed << setprecision(2) << setw(6) << a[i];
        return Print(a, size, ++i);
    }
    cout << endl;
}

double SumOdd(double* a, const int size, double sum, int i) {
    if (i < size) {
        if ((i + 1) % 2 == 1)
            sum += a[i];
        return SumOdd(a, size, sum, ++i);
    }
    return sum;
}

int iFirstNeg(double* a, const int size, int i) {
    if (i < size) {
        if (a[i] < 0)
            return i;
        return iFirstNeg(a, size, ++i);
    } 
    return -1;
}

int iLastNeg(double* a, int i) {
    if (i > 1) {
        if (a[i] < 0)
            return i;
        return iLastNeg(a, --i);
    }
    return -1;
}

//double Sum(double* a, int last, double sum, int i) {
//    if (i < last) {
//        sum += a[i];
//        return Sum(a, last, sum, ++i);
//    }
//    return sum;
//}

double SumBetween(double* a, const int size) {
    int first = iFirstNeg(a, size, 0),
        last = iLastNeg(a, size - 1);

    if (first == -1 || last == -1 || first == last) return 0;

    return Sum(a, last, 0, first + 1);
}

void MoveItems(double* a, const int size, int j, int k) {
    if (j < size - k - 1) {
        a[j] = a[j + 1];
        return MoveItems(a, size, ++j, k);
    }
}

void fillList(double* a, const int size, int i, int k) {
    if (k != 0) {
        a[i] = 0;
        fillList(a, size, --i, --k);
    }
}

void Сompress(double* a, const int size, int i, int k)
{
    if (i < size - k)
    {
        if (fabs(a[i]) > 0 && fabs(a[i]) < 1)
        {
            MoveItems(a, size, i, k);

            return Сompress(a, size, i, ++k);
        }
        else
            return Сompress(a, size, ++i, k);
    }
    return fillList(a, size, size - 1, k);
}

int main()
{
    srand((unsigned)time(NULL));
    int n = 0;
    cout << "N = "; cin >> n;
    double* a = new double[n];

    double Low = -2.;
    double High = 2.;
    Create(a, n, Low, High, 0);
    Print(a, n, 0);

    cout << "Sum Odd = " << SumOdd(a, n, 0, 0) << endl;
    cout << "Sum Between = " << SumBetween(a, n) << endl;

    Сompress(a, n, 0, 0);
    cout << "Compress:" << endl; Print(a, n, 0);

    delete[] a;

    return 0;
}