#ifndef RED_METRO_H
#define RED_METRO_H
#include "linea.h"

class Red_Metro
{
private:

    Linea *Metro;
    int Tamaño;

    //Validaciones
    string Verificar_Nombre_Linea();
    bool Verificar_Estacion_Transferencia(int Posicion_Linea);
    //int Mostrar_Lineas();

public:
    Red_Metro();
    int Mostrar_Lineas();
    void Añadir_Linea();
    void Eliminar_Linea();

    int Get_Tamaño();
};

#endif // RED_METRO_H
