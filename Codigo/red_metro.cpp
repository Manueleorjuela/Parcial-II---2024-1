#include "red_metro.h"

bool Red_Metro::Validacion_Error5(string &Nombre_Linea)
{
    bool Validacion = false;
    cout << endl << "Ingrese el nombre de la nueva linea: ";
    getline(cin, Nombre_Linea);
    if (!Validacion_Error3(0)){
        for (int i = 0; i < Tamaño; i++) {
            if (Metro[i].Get_Nombre() == Nombre_Linea){
                Validacion = true;
                Error5_NombreLineaRepetido();
                }
            }
    }
    return Validacion;
}

bool Red_Metro::Validacion_Error1(Linea &Evaluar)
{
    bool Validacion = false;
    Estacion *Estaciones = Evaluar.Get_Linea();
    if (Estaciones == nullptr || Evaluar.GetTamaño() == 0){
        Error1_LineaVacia();
        Validacion = true;
    }
    return Validacion;
}

bool Red_Metro::Validacion_Error2(int Posicion_Linea)
{
    bool Existe = false;
    int Dimension_Linea = Metro[Posicion_Linea].GetTamaño();
    Estacion *Evaluar = Metro[Posicion_Linea].Get_Linea();

    for (int i = 0; i < Dimension_Linea; i++){
        if (Evaluar[i].Get_Transferencia() == true){
            Existe = true;
            Error2_EstacionTransferenciaEncontrada();
            break;
        };
    }

    return Existe;
}

bool Red_Metro::Validacion_Error3(int Case)
{
    bool Validacion = false;
    if (Metro == nullptr || Tamaño == 0){
        switch(Case){
            case 0:
            cout << "Por el momento, la linea que anadira es la unica en la red." << endl;
            break;
            case 1:
            Error3_RedVacia();
            break;
        }
        Validacion = true;
    }
    return Validacion;
}

void Red_Metro::Mostrar_Lineas()
{
    if (!Validacion_Error3(1)){
        cout <<endl << "Lineas presentes en la red: " << endl;
        for (int i = 0; i < Tamaño; i++){
        cout << i+1 << ". " << Metro[i].Get_Nombre() << endl;
        }
    }
}

void Red_Metro::Añadir_Estacion()
{
    if (!Validacion_Error3(1)){
        int Posicion;
        if(!Validacion_Errror4(Posicion)){
            Metro[Posicion].Añadir_Estacion();
        }
    }
}

void Red_Metro::Eliminar_Estacion()
{;

    if (!Validacion_Error3(1)){
        int Posicion ;
        if (!Validacion_Errror4(Posicion)){
            if (!Validacion_Error1(Metro[Posicion])){
                Metro[Posicion].Eliminar_Estacion();
            }
        }
    }
}

bool Red_Metro::Validacion_Errror4(int &Posicion)
{
    Mostrar_Lineas();
    cout << endl<<"Seleccione la posicion en la cual quiere realizar los cambios: ";
    cin >> Posicion;
    if (Posicion < 1 || Posicion > Tamaño){
        Error4_PosicionInvalida();
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Posicion -=1;
    return Posicion;
}

Red_Metro::Red_Metro()
{
    Tamaño = 0;
    Metro = nullptr;
}

void Red_Metro::Añadir_Linea()
{
    string Nombre_Linea;

    if(!Validacion_Error5(Nombre_Linea)){
        Tamaño += 1;
        Linea *Actualizacion = new Linea[Tamaño];
        for (int i = 0; i < Tamaño - 1; i++) {
        Actualizacion[i] = Metro[i];
        }
        delete[] Metro;
        Actualizacion[Tamaño - 1] = Linea(Nombre_Linea, 0);
        Metro = Actualizacion;
    }
}

void Red_Metro::Eliminar_Linea()
{
    Linea * Actualizacion;
    if (!Validacion_Error3(1)){
        int Posicion;
        if(!Validacion_Errror4(Posicion)){
            if (!Validacion_Error2(Posicion)){
                Tamaño -=1;
                Actualizacion = new Linea[Tamaño];
                for (int j = 0; j < Tamaño; j++){
                    if (j < Posicion){
                        Actualizacion[j] = Metro[j];
                    }else if (j >= Posicion){
                        Actualizacion[j] = Metro[j+1];
                    }
                }
                delete [] Metro;
                Metro = Actualizacion;
            }
        }
    }
}

int Red_Metro::Get_Tamaño()
{
    return Tamaño;
}

void Red_Metro::Error1_LineaVacia()
{
    try {
        throw runtime_error("La linea ingresada no contiene ninguna estacion.");
    } catch (const runtime_error& ex) {
        cout << "Error: " << ex.what() << endl;
    }
}

void Red_Metro::Error2_EstacionTransferenciaEncontrada()
{
    try {
        throw runtime_error("La linea ingresada contiene una estacion de transferencia, no puede eliminarse.");
    } catch (const runtime_error& ex) {
        cout << "Error: " << ex.what() << endl;
    }
}

void Red_Metro::Error3_RedVacia()
{
    try {
        throw runtime_error("No existen lineas en la red.");
    } catch (const runtime_error& ex) {
        cout << "Error: " << ex.what() << endl;
    }
}

void Red_Metro::Error4_PosicionInvalida()
{
    try {
        throw runtime_error("Linea escogida invalida.");
    } catch (const runtime_error& ex) {
        cout << "Error: " << ex.what() << endl;
    }
}

void Red_Metro::Error5_NombreLineaRepetido()
{
    try {
        throw runtime_error("El nombre ingresado ya existe en la red.");
    } catch (const runtime_error& ex) {
        cout << "Error: " << ex.what() << endl;
    }
}
