#include <stdio.h>
#include <math.h>
#define S(a, b, c) (((a) + (b) + (c)) * 0.5)
#define AREA(a, b, c, s) (sqrt((s) * (s - a) * (s - b) * (s - c)))

int main() {
    double a = 0, b = 0, c = 0;
    printf("Input the triangle's three sides:");
    scanf("%lf %lf %lf", &a, &b, &c);
    float s = S(a, b, c);
    if (s - a > 0 && s - b > 0 && s - c > 0){
        printf("the area is %f\n", AREA(a, b, c, S(a, b, c)));
    }
    else{
        printf("Numbers is illegal.\n");
    }

    return 0;
}
