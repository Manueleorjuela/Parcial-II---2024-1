#ifndef RED_METRO_H
#define RED_METRO_H
#include "linea.h"

class Red_Metro
{
private:

    Linea *Metro;
    int Tamaño;
    string *Lineas_Conectadas;
    int Cantidad_Conexiones;

    //Validaciones
    bool Validacion_Error1(Linea &Evaluar);
    bool Validacion_Error2(Linea &Linea);
    bool Validacion_Error3(int Case);
    bool Validacion_Error4(int &Posicion);
    bool Validacion_Error5(string &Nombre_Linea);
    bool Validacion_Error6(int &Posicion_Estacion, Linea &Linea);
    bool Validacion_Error7(string &Nombre_LineaConectar, int& Posicion_Estacion, Linea &Linea, string &Nombre_LineaActual);
    bool Validacion_Linea_Conectar_Ya_Conectada(string &Nombre_Linea_Actual, string &Nombre_Linea_Conectar, int Case, Linea &Linea, int& Posicion_Estacion);

    //Errores
    void Error1_LineaVacia();
    void Error2_EstacionTransferenciaEncontrada();
    void Error3_RedVacia();
    void Error4_PosicionInvalida();
    void Error5_NombreLineaRepetido();
    void Error6_CrearEstacionTransConUnaSolaLinea();
    void Error7_LineaIngresadaNoHaceParteDeLaRed();

    //Funciones de Manejo
    int Buscar_Posicion_Linea(string &Nombre_Linea);
    void Mostrar_Lineas_Para_Conectar(string &Nombre_Linea_Actual);
    void Mostrar_Lineas();

public:

    Red_Metro();
    void Añadir_Linea();
    void Eliminar_Linea();

    //Operaciones con estaciones
    void Añadir_Estacion();
    void Eliminar_Estacion();


    int Get_Tamaño();
};

#endif // RED_METRO_H
