#include <iostream>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double OMEGA = 1;   // Frequenz
double T = 30;      // Zeit
double H = 0.1;     // Schrittweite
double X0 = 1;      // Anfangsauslenkung
double V0 = 0;      // Anfangsgeschwindigkeit
double K = 1;       // Richtgröße
double GAMMA = 0;   // Dämpfungskonstante
double OMEGA_t = 0; // Anregende Kreisfrequenz


std::ofstream fileT;

/**
 * Implementiert die Euler Methode und schreibt die Abweichung der
 * errechneten Datenpunkte zur idealen Lösung in eine Datei.
 *
 */
void euler() {
    double t , x = X0 , v = V0 , xp , vp ;
    std::ofstream fileX;
    std::ofstream fileE;
    fileX.open("xEuler.txt");
    fileE.open("eEuler.txt");

    for( t = 0 ; t < T; t += H) {
        xp = x + H*v ;
        vp = v-OMEGA*OMEGA*H*x ;
        fileX << abs(cos(t)-x) << endl;
        fileE << abs((v*v)/2 + (OMEGA*OMEGA*x*x)/2 -0.5) << endl;
        x = xp ;
        v = vp ;
    }
    fileX.close();
    fileE.close();
}

/**
 * Implementiert die LeapFrog Methode und schreibt die Abweichung der
 * errechneten Datenpunkte zur idealen Lösung in eine Datei.
 */
void leapFrog () {
    double t , x = X0 , v = V0 , xp , vp ;
    std::ofstream fileX;
    std::ofstream fileE;
    fileX.open("xleapFrog.txt");
    fileE.open("eleapFrog.txt");
    xp = x + v*H/2;
    x=xp;
    fileX << x << endl;

    for(t = 0; t<T; t+=H) {
    vp= v-H*OMEGA*OMEGA*x;
    xp = x+H*vp;
    fileX << abs(cos(t)-x)  << endl;
    fileE << abs((v*v)/2 + (OMEGA*OMEGA*x*x)/2 - 0.5) << endl;
    fileT << t << endl;
    x = xp;
    v = vp;
    }
    fileX.close();
    fileE.close();
}




/**
 * Implementiert Runge-Kutta Verfahren und schreibt die Abweichung der
 * errechneten Datenpunkte zur idealen Lösung in eine Datei.
 */
void rungeKutta2() {
    double t , x = X0 , v = V0 , xp , vp ;
    std::ofstream fileX;
    std::ofstream fileV;
    std::ofstream fileE;
    fileX.open("xRungeKutta2.txt");
    fileV.open("vRungeKutta2.txt");
    fileE.open("eRungeKutta2.txt");

    for(t = 0; t<T; t+=H) {
        double k1x,k1v,k2x,k2v;
        k2x = H*(v-OMEGA*OMEGA*x*(H/2));
        k2v = H*(-OMEGA*OMEGA)*(x+v*(H/2));
        xp = x+k2x;
        vp = v+k2v;
        fileX << abs(cos(t)-x) << endl;
        fileE << abs((v*v)/2 + (OMEGA*OMEGA*x*x)/2 -0.5 ) << endl;
        x=xp;
        v=vp;
    }
    fileX.close();
    fileE.close();
    fileV.close();
}

/**
 * Funktion der äußeren anregenden Kraft
 * @param t Zeit
 * @return F(t)
 */
double F(double t) {
    return 0;
    return sin(OMEGA_t*t);
}
/**
 * Implementiert die Verlet Methode und schreibt die Abweichung der
 * errechneten Datenpunkte zur idealen Lösung in eine Datei.
 *
 * Weiterhin wird die maximale Auslenkung nach dem Einschwingvorgang
 * der Oszillation bestimmt.
 */
void verlet() {
    double t , x = X0 , v = V0 , xp , vp ;
    std::ofstream fileE;
    std::ofstream fileVX;
    fileVX.open("xVerlet.txt");
    fileE.open("eVerlet.txt");
    double x_max = 0;
    for(t = 0; t<T; t+=H) {
        xp = x + v*H + (v/2)*H*H;
        vp = v + 0.5 * H * ( (F(t)-GAMMA*v-K*x) + (F(t+H)-GAMMA*(v+(F(t)-GAMMA*v-K*x)*H)-K*xp));
        fileE << abs((v*v)/2 + (OMEGA*OMEGA*x*x)/2 -0.5) << endl;
        fileVX <<  abs(cos(t)-x) <<  endl;
        x = xp;
        v = vp;

    }
    fileE.close();
    fileVX.close();
}

/**
 * Durchläuft  verschiedene Dämpfungen und bestimmt für jede davon
 * die Amplitude in Abhängigkeit der Anregenden Frequenz, indem
 * die DGL stets neu gelöst wird. Die zusammengehörenden Werte der Dämpfung,
 * Anregefrequenz und
 * Amplitude werden in jedem Schritt einer Textdatei angehängt.
 */
void resonanz() {
    double t , x = X0 , v = V0 , xp , vp ;
    std::ofstream fileRes;
    fileRes.open("res.txt");
    for(double gamma = 0.1; gamma < 2; gamma += 0.05) {
        while(OMEGA_t < 2.2) {
            double x_max = 0;
            for(t = 0; t<T; t+=H) {
                xp = x + v * H + (v / 2) * H * H;
                vp = v + 0.5 * H * ((F(t) - gamma * v - K * x) +
                        (F(t + H) - gamma * (v + (F(t) - gamma * v - K * x) * H) - K * xp));
                x = xp;
                v = vp;
                // Bestimmung des Maximums
                if (t > 0.8 * T) {
                    if (x > x_max) {
                        x_max = x;
                    }
                }
            }
            fileRes << OMEGA_t << "  " << x_max << "  " << gamma << endl;
            OMEGA_t += 0.01;
        }
        OMEGA_t = 0;
    }
    fileRes.close();
}

/**
 * Erhöht so lange die Dämpfung (bei Null beginnend) bis kein Nulldurchgang
 * mehr auftritt. In diesem Fall ist der aperiodische Grenzfall erreicht und
 * die momentane Dämpfung wird zurückgegeben.
 *
 * Wichtig ist, dass die Anfangsgeschwindigkeit Null ist und die
 * Angfangsauslenkung größer Null ist!
 *
 * @return Dämpfung des aperiodischen Grenzfall gamma.
 */
double aperiod() {
    double gamma = 0;
    while(true) {
        double t , x = X0 , v = V0 , xp , vp ;
        for(t = 0; t<T; t+=H) {
            xp = x + v*H + (v/2)*H*H;
            vp = v + 0.5 * H * ( (F(t)-gamma*v-K*x) + (F(t+H)-gamma*(v+(F(t)-gamma*v-K*x)*H)-K*xp));
            x = xp;
            v = vp;
            if(x<0) {  // Falls Nulldurchgang auftritt fahre fort mit nächst größerer Dämpfung
               break;
            }
            if(t+2*H>T) {
                // Dieser Punkt wird nur erreicht, falls der Oszillator bei der aktuellen Dämpfung
                // keinen Nulldurchgang besitzt.
                return gamma;
            }
        }
        gamma+=0.01;
    }
}


int main() {
    leapFrog();
    euler();
    rungeKutta2();
    verlet();
    resonanz();
    cout << aperiod()  << endl;
    return 0;
}