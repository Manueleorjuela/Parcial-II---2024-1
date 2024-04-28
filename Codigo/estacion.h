#ifndef ESTACION_H
#define ESTACION_H
#include <iostream>
#include <string>
using namespace std;


class Estacion
{
private:
    string Nombre;
    bool Transferencia;

    int Tiempo_Anterior;
    int Tiempo_Posterior;

public:

    Estacion(string Nombre_Estacion, bool Es_No_De_Transferencia);
    Estacion();

    string Get_Nombre();
    bool Get_Transferencia();

    int Get_Tiempo_Anterior();
    int Get_Tiempo_Posterior();

    void Set_Tiempo_Anterior(int Nuevo_Tiempo);
    void Set_Tiempo_Posterior(int Nuevo_Tiempo);

};

#endif // ESTACION_H
