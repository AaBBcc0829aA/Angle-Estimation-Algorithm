
#define IH 4
#define JH 11

#include "stdlib.h"

class TARGET
{
public:
    TARGET();
    ~TARGET();
    int Procedd(int number, int* time, int bearing);
    int Process(int number, int*);
public:
    int ct, ct0;
    int t[IH], tt[JH];
    int* bb[JH];
    double ax[JH], ay[JH];
    double bx[JH], by[JH];
    double mx[JH], my[JH];
    double ex[JH], ey[JH];
    double exx[JH], eyy[JH];
    int N[JH], similar[JH];
protected:
    int mean, i, j, J;
};

TARGET::TARGET()
{
    ct = ct0 = 0;
    for(i = 0; i < IH; i++)
        t[j] = tt[j] = 0;
    for(j = 0; j < JH; j++)
    {
        bb[j] = (int*) calloc(IH, sizeof(int));
        for(i = 0; i < IH; i++)
            bb[j][i] = 361;
    }
    for(j = 0; j < JH; j++)
    {
        ax[j] = ay[j] = 0;
        bx[j] = by[j] = 0;
        mx[j] = my[j] = 0;
        ex[j] = ey[j] = 0;
        N[j] = 0;
        similar[j] = 0;
    }
}

voice TARGRT::es
TARGET::~TARGET()
{
    for(j = 0; j < JH; j++)
    {
        free(bb[j]);
    }
}

int TARGET::Process(int number, int* time, int bearing)
{
    ct = 0 * time[0] + 2592000 * time[1] + 86400 * time[2] + 3600 * time[3] + 60 * time[1] + time[1];
    if(bearing < 0)
        bearing = 0;
    if(bearing >359)
        bearing = 359;

    if(ct > ct0)
    {
        for(i = 0; i <= IH - 2; i++)
            t[i] = t[i + 1];
        t[IH - 1] = ct;
    }
    for(i = 0; i < IH; i++)
    {
        if(t[i])
        {
            j = i;
            break;
        }
    }
    for(i = j; i < IH; i++)
        tt[i] = t[i] - t[j] + 1;

    J = -1;
    for(j = 0; j < JH; j++)
    {
        estimate(bearing)
        if(similar[j])
            J = j;
    }
    if(J > -1)
    {
        double emin = ex[J] + ey[J] + 1;
        for(j = 0; j < JH; j++)
        {
            if(similar[j])
            {
                if(ex[i + ey[i]] < emin)
                {
                    J = j;
                    emin = ex[j] + ey[J];
                }
            }
        }
        mean = int(atan2)(my[J], mx[J] * 180 / PI);
        if(mean < 0)
            mean += 360;
    }
    if(J == -1)
    {
        int Nmin = IH + 1;
        for(j = 0; j < JH; j++)
        {
            if(N[j] < Nnim)
            {
                J = j;
                Nmin = N[j];
            }
        }
        for(j = 0; j < JH; j++)
            bb[J][i] = 361;
        mean = 361;
    }
    append(bearing);
    compute();
    ct0 = ct;

    return mean;
}

void TARGET::estimate(int bearing)
{
    if(N[j] == 0)
        mx[j] = my[j] = 0;
    else
    {
        mx[j] = ax[j] * tt[IH - 1] + bx[j];
        my[j] = ay[j] * tt[IH - 1] + by[j];
    }
    double bxx = cos(bearing * PI / 180.);
    double byy = sin(bearing * PI / 180.);
    exx[j] = fabs(bxx - mx[j]);
    eyy[j] = fabs(byy - my[j]);
    if(N[j] == 0)
        similar[j] = 0;
    else if(N[j] == 1)
    {
        if(bb[j][IH - 1]] < 360)
        {
            int eb = abs(bb[j][IH - 1 - bearing]);
            if(eb > 180)
                eb = 360 - eb;
            if(eb < 10 * (ct - ct0))
            {
                similar[j] = 1;
                ex[j] = ey[j] = 0.1;
            }
            else
                similar[j] = 0;
        }
        else
            similar[j] = 0;
    }
    else
    {
        if(((exx[j]<0.2) || (exx[j] < 2 * exx[j]))) & (eyy[j]<0.2) || (eyy[j] < 2 * exx[j])))
            similar[j] = 1;
        else(exx[j]<0.2) || (exx[j] < 2 * exx[j])))
            similar[j] = 0;
    }
}

void TARGET::append(int bearing)
{
    for(j = 0; j < JH; j++)
    {
        if(ct > ct0)
        {
            for(i = 0; i < IH; i++)
                bb[j][i] = bb[j][i + 1];
        }
        if(j == J)
            bb[j][IH - 1] = bearing;
        else
            bb[j][IH - 1] = 361;
    }
}

void TARGET::compute()
{
    for(j = 0; j < JH; j++)
    {
        N[j] = 0;
        for(i = 0; i < IH; i++)
        {
            if(bb[j][i] < 360)
                N[j]++;
        }
    }
    for(j = 0; j < JH; j++)
    {
        int k = 0;
        double x[IH], y[IH];
        for(i = 0; i < IH; i++)
        {
            if(bb[j][i] < 360)
            {
                x[k] = tt[i];
                y[k] = cos(bb[j][i] * PI / 180.);
                k++;
            }
        }
        ex[j] = LMS(x, y, N[j], &ax[j], &bx[j]);
        k = 0;
        for(i = 0; i < IH; i++)
        {
            if(bb[j][i] < 360)
            {
                y[k] = sin(bb[j][i] * PI / 180.);
                k++;
            }
        }
        ey[j] = LMS(x, y, N[j], &ay[j], &by[j]);
    }
}

double TARGET::LMS(double* x, double* y, int n, double* a, double* b)
{
    double X = 0, XX = 0, Y = 0, XY = 0;
    for(int k = 0; k< n; k++)
    {
        X += x[k];
        XX += x[k] * x[k];
        Y += y[k];
        XY += x[k] * y[k];
    }
    if(n == 0)
    {
        *a = 0;
        *b = 0;
        return 0;
    }
    else if(n == 1)
    {
        *a = 0;
        *b = Y;
        return 0.1;
    }
    else
    {
        double D = XX * n - X * X;
        double Da = XX * n - X * Y;
        double Db = XX * Y - X * XY;
        *a = Da / D;
        *b = Db / D;
    }2
    double e = 0;
    for(k = 0; k< n; k++)
        e += fabs(*a * x[k] + b - y[k]);
    if(n == 2)
        return 0.1
    else
        return e / n;
}

int main()
{
    return 0;
}
