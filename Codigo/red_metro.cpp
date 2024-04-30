#include "red_metro.h"

string Red_Metro::Verificar_Nombre_Linea()
{
    string Nombre_Linea;
    bool Existe = true;


    while (Existe) {
        cout << endl << "Ingrese el nombre de la nueva linea: ";
        getline(cin, Nombre_Linea);

        if (Metro == nullptr){
            cout << "Por el momento, la linea que anadira es la unica en la red." << endl;
            break;
        }else{
            for (int i = 0; i < Tamaño; i++) {
                if (Metro[i].Get_Nombre() == Nombre_Linea) {
                cout << "La linea ya existe en la red, pruebe con otro." << endl;
                break;
                }else Existe = false;
            }
            if (!Existe) break;
        }
    }
    return Nombre_Linea;
}

bool Red_Metro::Verificar_Estacion_Transferencia(int Posicion_Linea)
{
    bool Existe = false;
    int Dimension_Linea = Metro[Posicion_Linea].GetTamaño();
    Estacion *Evaluar = Metro[Posicion_Linea].Get_Linea();




    for (int i = 0; i < Dimension_Linea; i++){
        if (Evaluar[i].Get_Transferencia() == true){
            Existe = true;
            break;
        };
    }

    return Existe;
}

void Red_Metro::Mostrar_Lineas()
{
    cout <<endl << "Lineas presentes en la red: " << endl;

    if (Tamaño == 0){
        cout << "La red no tiene lineas por el momento." << endl;
    }else{
        for (int i = 0; i < Tamaño; i++){
        cout << i+1 << ". " << Metro[i].Get_Nombre() << endl;
        }
    }
}

void Red_Metro::Añadir_Estacion()
{
    if (Metro == nullptr) Error3_RedVacia();
    else{
        int Posicion = Seleccionar_();
        Metro[Posicion].Añadir_Estacion();
    }
}

void Red_Metro::Eliminar_Estacion()
{
    int Posicion = Seleccionar_();
    if (Metro == nullptr) Error3_RedVacia();
    else{
        if (Metro[Posicion].Get_Linea() == nullptr) Error1_LineaVacia();
        else Metro[Posicion].Eliminar_Estacion();
    }
}

int Red_Metro::Seleccionar_()
{
    Mostrar_Lineas();
    int Posicion;
    while (true){
           cout << endl<<"Seleccione la posicion en la cual quiere realizar los cambios: ";
           cin >> Posicion;
           if (Posicion < 1 || Posicion > Tamaño){
                cout <<endl<<"Ubicacion no valida, intente de nuevo."<< endl;
            }else break;
        }

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
    string Nombre_Linea = Verificar_Nombre_Linea();

    Tamaño += 1;
    Linea *Actualizacion = new Linea[Tamaño];

    for (int i = 0; i < Tamaño - 1; i++) {
        Actualizacion[i] = Metro[i];

    }

    delete[] Metro;
    Actualizacion[Tamaño - 1] = Linea(Nombre_Linea, 0);
    Metro = Actualizacion;

}

void Red_Metro::Eliminar_Linea()
{
    int Posicion;
    bool Existencia_Transferencia;
    Linea * Actualizacion;

    if (Metro == nullptr){
        Error3_RedVacia();
    }
    else{
        Posicion = Seleccionar_();
        Existencia_Transferencia = Verificar_Estacion_Transferencia(Posicion);
        if (Existencia_Transferencia) Error2_EstacionTransferenciaEncontrada();
        else{
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
