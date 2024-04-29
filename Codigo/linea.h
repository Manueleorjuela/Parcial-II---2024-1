#ifndef LINEA_H
#define LINEA_H
#include "estacion.h"
#include <limits>

class Linea
{
private:

    string Nombre;
    int Tamaño;
    Estacion *Linea_;

    //Validar
    string Existencia_Estacion();
    bool Verificacion_Transferencia();
    bool Verificacion_Estacion_Transferencia(int Posicion_Estacion);

    int Mostrar_Estaciones();

public:

    Linea();
    Linea(string Nombre_Linea, int Tamaño_Linea);
    ~Linea();

    void Añadir_Estacion();
    void Eliminar_Estacion();

    int GetTamaño();
    string Get_Nombre();
    Estacion *Get_Linea();

};

#endif // LINEA_H
