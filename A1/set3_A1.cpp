#include <iostream>
#include <algorithm>

using namespace std;

double x1, r1, x2, y1, y2, r2, x3, y3, r3;

double random_double(double min, double max) {
    return min + (double)rand() / RAND_MAX * (max - min);
}

bool isInsideArea (double x, double y)
{
    double dist1 = (x - x1) * (x - x1) + (y - y1) * (y - y1);
    double dist2 = (x - x2) * (x - x2) + (y - y2) * (y - y2);
    double dist3 = (x - x3) * (x - x3) + (y - y3) * (y - y3);

    return (dist1 <= r1 * r1) && (dist2 <= r2 * r2) && (dist3 <= r3 * r3);
}

double squareMonteCarlo(int n, double x_min, double x_max, double y_min, double y_max)
{
    int countInside = 0;
    for (int i=0; i<n; i++)
    {
        double x = random_double(x_min, x_max);
        double y = random_double(y_min, y_max);

        if (isInsideArea(x, y))
        {
            countInside++;
        }
    }
    double rectangleArea = (x_max - x_min) * (y_max - y_min);

    return (double)countInside / n * rectangleArea;
}

int main()
{
    cin >> x1 >> y1 >> r1;
    cin >> x2 >> y2 >> r2;
    cin >> x3 >> y3 >> r3;

    double x_min = min({x1 - r1, x2 - r2, x3 - r3});
    double x_max = max({x1 + r1, x2 + r2, x3 + r3});
    double y_min = min({y1 - r1, y2 - r2, y3 - r3});
    double y_max = max({y1 + r1, y2 + r2, y3 + r3});

    int n = 10000000;

    double S = squareMonteCarlo(n, x_min, x_max, y_min,y_max);

    cout << S;
}