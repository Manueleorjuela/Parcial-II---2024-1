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

    int Seleccionar_();


public:

    Red_Metro();
    void Añadir_Linea();
    void Eliminar_Linea();
    void Mostrar_Lineas();

    int Get_Tamaño();
};

#endif // RED_METRO_H
