#ifndef ESTACION_H
#define ESTACION_H
#include <iostream>
#include <string>
#include <limits>
using namespace std;


class Estacion
{
private:

    string Nombre;
    bool Transferencia;

    int Tiempo;

    void Inicializar_Tiempo();


public:

    Estacion(string Nombre_Estacion, bool Es_No_De_Transferencia);
    Estacion(string Nombre_Estacion, bool Es_No_De_Transferencia, int Tiempo);

    Estacion();

    string Get_Nombre();
    bool Get_Transferencia();

    int Get_Tiempo();

    void Set_Tiempo(int Nuevo_Tiempo);
    void Set_Tiempo_Eliminar(int Nuevo_Tiempo);
    void Set_Transfrencia(bool Cambio);
    void Set_Nombre(string Nuevo_Nombre);

};

#endif // ESTACION_H
