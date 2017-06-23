#include <stdio.h>
#include <math.h>
#define S(a, b, c) (((a) + (b) + (c)) / 2)
#define AREA(a, b, c, s) (sqrt((s) * (s - a) * (s - b) * (s - c)))

int main() {
    int a = 0, b = 0, c = 0;
    while (scanf("%d %d %d", &a, &b, &c) != EOF){
        printf("%d %f\n", S(a, b, c), AREA(a, b, c, S(a, b, c)));
    }
    return 0;
}
