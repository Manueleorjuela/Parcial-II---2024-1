#ifndef RED_METRO_H
#define RED_METRO_H
#include "linea.h"

class Red_Metro
{
private:

    Linea *Metro;
    int Tamaño;

    //Validaciones
    bool Validacion_Error1(Linea &Evaluar);
    bool Validacion_Error2(int Posicion_Linea);
    bool Validacion_Error3(int Case);
    bool Validacion_Errror4(int &Posicion);
    bool Validacion_Error5(string &Nombre_Linea);


    //Errores
    void Error1_LineaVacia();
    void Error2_EstacionTransferenciaEncontrada();
    void Error3_RedVacia();
    void Error4_PosicionInvalida();
    void Error5_NombreLineaRepetido();

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
