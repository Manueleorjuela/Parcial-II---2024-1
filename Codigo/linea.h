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
    int Mostrar_Lineas();

public:
    Linea(string Nombre_Linea, int Tamaño_Linea);
    ~Linea();

    void Añadir_Estacion();
};

#endif // LINEA_H
