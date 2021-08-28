#include <iostream>
#include <cmath>
#include <math.h>
#include <fstream>
#include <limits>


using namespace std;

double H = 0.001;
double XMAX = 20;


double F(double r) {
    return 0;
    return -r * exp(-r);
}


double V(double x) {
    if (x >= 0) {
        return x;
    } else {
        return std::numeric_limits<double>::infinity();
    }
}

double X(double r) {
    return 0;
    return (1 - (1 + r / 2) * exp(-r));
}


double k2(double E, double x) {
    double m = 1;
    double h_quer = 1;
    return m * (E - V(x)) / (h_quer * h_quer);
}

double numerowIn(double E) {
    std::ofstream resultKorrigiert;
    std::ofstream ideal;
    std::ofstream resultUnKorrigiert;

    resultUnKorrigiert.open("numerovUn.txt");
    resultKorrigiert.open("numerovKor.txt");
    ideal.open("ideal.txt");

    double x0 = 20;
    double f_n1;
    double f_n3 = 2;
    double f_n2 = 2;


    for (double x = x0 - 2 * H; x > 0.001; x -= H) {

        f_n1 = ((-f_n3 * (1. + H * H / 12. * k2(E, x + H)))
                + (H * H / 12. * (F(x + H) + 10. * F(x) + F(x - H)))
                + f_n2 * (2. - 5. / 6. * H * H * k2(E, x))) / (1. + H * H / 12. * k2(E, x - H));

        f_n3 = f_n2;
        f_n2 = f_n1;

        ideal << x << "  " << X(x) / x << endl;
        resultKorrigiert << x << "  " << f_n1 / (2 * x) << endl;
        resultUnKorrigiert << x << "  " << f_n1 / (x) << endl;
    }
}


double xEnd = 20;

double numerowIn2(double E) {


    double f_n1;
    double f_n3 = 0;
    double f_n2 = f_n3 + H * H * (V(xEnd - H) - E);


    for (double x = xEnd; x > 0; x -= H) {

        f_n1 = ((-f_n3 * (1. + H * H / 12. * k2(E, x + H)))
                + (H * H / 12. * (F(x + H) + 10. * F(x) + F(x - H)))
                + f_n2 * (2. - 5. / 6. * H * H * k2(E, x))) / (1. + H * H / 12. * k2(E, x - H));

        f_n3 = f_n2;
        f_n2 = f_n1;
    }
    return f_n3;
}


double numerowIn2Print(double E) {
    std::ofstream result2;
    result2.open("result2.txt");

    double f_n1;
    double f_n3 = 0;
    double f_n2 = f_n3 + H * H * (V(xEnd - H) - E);
    int i = 0;
    for (double x = xEnd; x > 0; x -= H) {
        f_n1 = ((-f_n3 * (1. + H * H / 12. * k2(E, x + H)))
                + (H * H / 12. * (F(x + H) + 10. * F(x) + F(x - H)))
                + f_n2 * (2. - 5. / 6. * H * H * k2(E, x))) / (1. + H * H / 12. * k2(E, x - H));
        f_n3 = f_n2;
        f_n2 = f_n1;
        result2 <<  f_n1 << endl;
    }
    return f_n3;
}


double numerowIn2Sum(double E) {
    double f_n1;
    double f_n3 = 0;
    double f_n2 = f_n3 + H * H * (V(xEnd - H) - E);
    int i = 0;
    double sum;
    for (double x = xEnd; x > 0; x -= H) {
        f_n1 = ((-f_n3 * (1. + H * H / 12. * k2(E, x + H)))
                + (H * H / 12. * (F(x + H) + 10. * F(x) + F(x - H)))
                + f_n2 * (2. - 5. / 6. * H * H * k2(E, x))) / (1. + H * H / 12. * k2(E, x - H));
        f_n3 = f_n2;
        f_n2 = f_n1;
        sum += H * f_n1;
        i++;
    }
    return sum;
}




int main() {
    double E = 7.94514;
    numerowIn2Print(E);

    /*
     * for (double E = 7.92; E < 8; E += 0.00001) {
        double n = numerowIn2(E);
        if (abs(n / numerowIn2Sum(E)) < 0.00001) {
            cout << E << endl;
        }
    }
     */


    // plot "E1norm.txt", "E2norm.txt", "E3norm.txt", "E4norm.txt", "E5norm.txt"

    // 2.33912  E1
    // 4.08895  E2
    // 5.52157  E3
    // 6.78771  E4
    // 7.94514  E5







/*
 * double E0 = 1, E1 = 5, E, f0, f1;
    do {
        f1 = numerowIn2(E1);
        f0 = numerowIn2(E0);
        E = (f1 * E0 - f0 * E1) / (f1 - f0);
        //E = E1 - (E1-E0)*f1/(f1-f0);
        E0 = E1;
        E1 = E;
        cout << " E " << E << endl;
        cout << " f0 " << f0 << endl;
    } while (fabs(E1 - E0) > 1 / 10000000);
    cout << " E " << E << endl;
 */


    return 0;
}
