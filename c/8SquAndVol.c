#include <stdio.h>
#define PI 3.1415926

double Square(int radius, int height)
{
    double square = 0;
    square = 2 * PI * radius * height + 2 * PI * radius * radius;
    return square;
}

double Volume(int radius, int height)
{
    double volume = 0;
    volume = PI * radius * radius * height;
    return volume;
}

int main()
{
    int N = 0;
    int radius = 0;
    int height = 0;

    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
    {
        scanf("%d %d", &radius, &height);
        printf("%.6f %.6f\n", Square(radius, height), Volume(radius, height));
    }


    return 0;
}
