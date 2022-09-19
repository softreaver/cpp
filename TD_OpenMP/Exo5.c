#include <stdio.h>

double Est_pi_seq ( int n );

int main(int argc, char const *argv[]) {
    printf("=> %.15f\n\n", Est_pi_seq(500000));
    return 0;
}

double Est_pi_seq ( int n ) { 
    double h, sum2, x;
    int i;

    h = 1.0 / ( double ) ( 2 * n );
    sum2 = 0.0;

    for ( i = 1; i <= n; i++ ) {
        x = h * ( double ) ( 2 * i - 1 );
        sum2 += 1.0 / ( 1.0 + x * x );
    }
    return (double) (4.0 * sum2 / ( double ) n );
}
