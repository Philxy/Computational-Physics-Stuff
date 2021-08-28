#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
using namespace std;

double M = 1;
double K = 0.5;
double G = 0.2;
double H = 60;
double h = 0.01;


double RADIUS = 0.5;
double R1x = 0.5 ;
double R1y = 0;

double R2x = -RADIUS*sin(M_PI/6);
double R2y =  RADIUS*cos(M_PI/6);
double R3x = -RADIUS*sin(M_PI/6);
double R3y = -RADIUS*cos(M_PI/6);

double z = 0.25;


double phi(double x, double y) {
    double R1 = sqrt(pow(x-R1x,2)+ pow(z,2) + pow(y-R1y,2));
    double R2 = sqrt(pow(x-R2x,2)+ pow(z,2) + pow(y-R2y,2));
    double R3 = sqrt(pow(x-R3x,2)+ pow(z,2) + pow(y-R3y,2));
    return +(1/R1 + 1/R2 + 1/R3);
}



double fX(double x, double y, double v) {
    double R1 = sqrt(pow(x-R1x,2)+ pow(z,2) + pow(y-R1y,2));
    double R2 = sqrt(pow(x-R2x,2)+ pow(z,2) + pow(y-R2y,2));
    double R3 = sqrt(pow(x-R3x,2)+ pow(z,2) + pow(y-R3y,2));
    double Fm = (x-R1x)/pow(R1,3) + (x-R2x)/pow(R2,3)  + (x-R3x)/pow(R3,3);
    double Fr = -G*v;
    double Ff = -K*x;
    return (-Fm+Fr+Ff)/M;
}

double fY(double x, double y, double v) {
    double R1 = sqrt(pow(x-R1x,2)+ pow(z,2) + pow(y-R1y,2));
    double R2 = sqrt(pow(x-R2x,2)+ pow(z,2) + pow(y-R2y,2));
    double R3 = sqrt(pow(x-R3x,2)+ pow(z,2) + pow(y-R3y,2));
    double Fm = (y-R1y)/pow(R1,3) + (y-R2y)/pow(R2,3)  + (y-R3y)/pow(R3,3);
    double Fr = -G*v;
    double Ff = -K*y;
    return (-Fm+Fr+Ff)/M;
}


double magnet(double y, double x) {

    double d1, d2, d3;

    d1 = sqrt( (y-R1y)*(y-R1y) + (x-R1x)*(x-R1x));
    d2 = sqrt( (y-R2y)*(y-R2y) + (x-R2x)*(x-R2x));
    d3 = sqrt( (y-R3y)*(y-R3y) + (x-R3x)*(x-R3x));


    if(d1 < d2) {
        if(d3<d1) {
            return 3;
        } else {
            return 1;
        }
    } else {
        if(d3<d2) {
            return 3;
        } else {
            return 2;
        }
    }

    if(abs(y-R1y)< 0.3) {
        return 1;
    }
    if(abs(y-R2y) < 0.3) {
        return 2;
    }
    if(abs(y-R3y) < 0.3) {
        return 3;
    }
}

double leapFrog(double X0, double Y0, double VY0, double VX0) {
    double t , x = X0 , y = Y0  , vx = VX0 ,vy = VY0, rpx, rpy,  vpx, vpy, E;

     //std::ofstream R;
     //std::ofstream V;
     //R.open("X.txt");
     //V.open("V.txt");

    vpx = vx+h*fX(x, y, vx);
    vpy = vy+h*fY(x, y, vy);
    vx = vpx;
    vy = vpy;

     for(double t = 0; t<H; t+=h){



        rpx = x + h*vx;
        rpy = y + h*vy;


        x = rpx;
        y = rpy;
        vx = vpx;
        vy = vpy;



        /*
         * if(abs(E-0.5*M*(vx*vx + vy*vy)) < 0.000001) {
            break;
        }
         */
    }

    cout<< x   <<y   << endl;
    return magnet(y, x);

    //R.close();
    //V.close();
}


double RK2(double X0, double Y0, double VY0, double VX0) {
    double t , x = X0 , y = Y0  , vx = VX0 ,vy = VY0, rpx, rpy,  vpx, vpy, E;
        for(double t = 0; t<H; t+=h) {
        // x
        double k1rx = h*vx;
        double k2rx = h*(vx+ h/2 * fX(x,y,vx));
        // y
        double k1ry = h*vy;
        double k2ry = h*(vy+ h/2 * fY(x,y,vy));
        // vx
        double k1vx = h*fX(x,y,vx);
        double k2vx = h*fX(x+vx * h/2, y+vy * h/2 , vx+k1vx/2);
        // vy
        double k1vy = h*fY(x,y,vy);
        double k2vy = h*fY(x+vx * h/2, y+vy * h/2 , vy+k1vy/2);

        x = x + k2rx;
        y = y + k2ry;
        vx = vx+ k2vx;
        vy = vy+ k2vy;
        }
    return magnet(y,x);
}




int main() {

    double x = 0.5, y =0.43;

    double d = 0.001;

    //leapFrog(0.2, 1, 0, 0);


    cout << RK2(1,-2,0,0) << endl;

    std::ofstream Contour;
    Contour.open("Contour.txt");
    RK2(0.97,0.96,0,0);

     /*
      * for(double i = -1; i<1; i+= d) {
        for(double r = 1; r>-1; r-= d) {
            Contour << i << "    "<<  r <<  "   " << RK2(i, r, 0, 0) << endl;
        }
    }
      */




    Contour.close();

    return 0;
}
