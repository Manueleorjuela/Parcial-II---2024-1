#ifndef LINEA_H
#define LINEA_H
#include "estacion.h"
#include <limits>

class Linea
{
private:

    string Nombre;
    int Tamaño;
    string *Lineas_Conectadas;
    Estacion *Linea_;

    //Validar
    bool Existencia_Estacion(string &Nombre_Estacion);
    bool Verificacion_Transferencia();
    bool Verificacion_Estacion_Transferencia(int Posicion_Estacion);

    //Funciones de manejo
    void Mostrar_Estaciones();
    int Seleccionar_Añadir();
    int Seleccionar_Eliminar();

    //Errores
    void Error1_EstacionEncontrada();
    void Error2_EstacionDeTransferenciaEncontrada();

public:

    Linea();
    Linea(string Nombre_Linea, int Tamaño_Linea);
    ~Linea();

    //Operaciones con estaciones
    void Añadir_Estacion();
    void Eliminar_Estacion();

    int GetTamaño();
    string Get_Nombre();
    Estacion *Get_Linea();


    //Errores
};

#endif // LINEA_H
