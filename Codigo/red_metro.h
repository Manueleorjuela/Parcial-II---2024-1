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

    //Funciones de manejo
    int Seleccionar_();


    //Errores
    void Error1_LineaVacia();
    void Error2_EstacionTransferenciaEncontrada();
    void Error3_RedVacia();

public:

    Red_Metro();
    void Añadir_Linea();
    void Eliminar_Linea();
    void Mostrar_Lineas();

    //Operaciones con estaciones
    void Añadir_Estacion();
    void Eliminar_Estacion();


    int Get_Tamaño();
};

#endif // RED_METRO_H
