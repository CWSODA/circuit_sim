#include <stdio.h>
#include <math.h>

#define PI 3.1415926535897932384f
#define WIDTH 200
#define HARMONIC_COUNT 10

void plotval(float val, int width);

int main() {
    int x = 0;

    float y;

    // loop forever
    // increment x then print with fixed width of 10
    while (x <= 500) {
        x += 1;
        float dx = x * 0.01;
        printf("x: %10.3f| ", dx);

        // reset y to 0
        // add all harmonics to y
        // simplified formula from https://www.geogebra.org/m/wUanseCs
        y = 0.0;
        for (int n = 0; n < HARMONIC_COUNT; n++) {
            int k = 2 * n + 1;
            y += (1.0 / k) * sin(PI * dx * k);
        }

        // square currently from -1-->1 so scaling to 0-->1
        y = (y + 1.0) / 2;

        // print y with 3 decimal places and fixed width 10
        printf("y: %10.3f |", y);

        // for every multiple of 10, insert tickmarks
        // else insert blank spaces equal to tickmark width so the offset is the
        // same
        if (x % 10 == 0) {
            printf("---");
        } else {
            printf("   ");
        }

        plotval(y, WIDTH);
    }

    return 0;
}

void plotval(float val, int width) {
    // scale 0-->1 to 1-->width
    // since 1 is the smallest size
    // then rounds the value to integer
    // prints '*' at offset and print new line
    int offset = round(val * (width - 1)) + 1;
    printf("%*c\n", offset, '*');
}