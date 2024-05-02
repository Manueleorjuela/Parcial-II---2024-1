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
    bool Validacion_Error1(string &Nombre_Estacion);
    bool Validacion_Error2(int &Posicion_Estacion);
    bool Validacion_Error3(bool &Transferencia);
    bool Validacion_SeleccionarAnadir_Error4(int &Posicion);
    bool Validacion_SeleccionarEliminar_Error4(int &Posicion);
    bool Validacion_Linea_Vacia(int Case);

    //Funciones de manejo
    void Mostrar_Estaciones();

    //Errores

    void Error1_EstacionRepetida();
    void Error2_EstacionDeTransferenciaEncontrada();
    void Error3_RequerimientoTransferenciaInvalido();
    void Error4_PosicionInvalida();

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
