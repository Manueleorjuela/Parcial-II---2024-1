#ifndef RED_METRO_H
#define RED_METRO_H
#include "linea.h"

class Red_Metro
{
private:

    Linea *Metro;
    int Tamaño;
        bool Primer_Conexion;

    //Validaciones
    bool Validacion_Error1(Linea &Evaluar);
    bool Validacion_Error2(Linea &Linea);
    bool Validacion_Error3(int Case);
    bool Validacion_Error4(int &Posicion);
    bool Validacion_Error5(string &Nombre_Linea);
    bool Validacion_Error6(int &Posicion_Estacion, Linea &Linea);
    bool Validacion_Error7(string &Nombre_LineaConectar, int& Posicion_Estacion, Linea &Linea, string &Nombre_LineaActual);
    void Validacion_Error9(Linea &Linea, bool& Transferencia, int &Posicion_Estacion, bool& Termina_Proceso);


    //Errores
    void Error1_LineaVacia();
    void Error2_EstacionTransferenciaEncontrada();
    void Error3_RedVacia();
    void Error4_PosicionInvalida();
    void Error5_NombreLineaRepetido();
    void Error6_CrearEstacionTransConUnaSolaLinea();
    void Error7_LineaIngresadaNoHaceParteDeLaRed();
    void Error8_LineaInvalida();
    void Error9_AñadirEstacion_En_LineaAislada();
    void Error10_LinaaSinEstacionesDeTransferencia();

    //Funciones de Manejo
    void Mostrar_Lineas();
    void Mostrar_Lineas_Para_Conectar(string &Nombre_Linea_Actual);
    void Mostrar_Estaciones_Transferencia(Linea &Conexion);

    //Para añadirEstacionesTransferencia
    int Buscar_Posicion_Linea(string &Nombre_Linea);
    void ModificarNombreEstacion(string &Nombre_Estacion);
    void Estacion_Transferencia_Establecida(Linea &Actual, int& PosicionEstacionActual, string& Nombre_LineaActual);
    void Validacion_Estacion_Transferencia(Linea &Actual, Linea &Conectar, int &Pos_Estacion);
    void Realizar_Conexion(Linea &Actual, Linea &Conectar, int &Pos_Estacion_Actual);
    void Conectar_EstacionNueva(Estacion* Estaciones, int &Posicion_Actual, Linea &Conectar,  Linea &Actual);
    void Conectar_EstacionExistente(Estacion* Estaciones, int &Posicion_Actual, Linea &Conectar, Linea &Actual);

public:

    Red_Metro();

    //Operacion con Lineas
    void Añadir_Linea();
    void Eliminar_Linea();

    //Operaciones con estaciones
    void Añadir_Estacion();
    void Eliminar_Estacion();


    int Get_Tamaño();
};

#endif // RED_METRO_H
