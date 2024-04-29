#include "red_metro.h"

string Red_Metro::Verificar_Nombre_Linea()
{
    string Nombre_Linea;
    bool Existe = true;

    while (Existe) {
        cout << "Ingrese el nombre de la nueva linea: ";
        getline(cin, Nombre_Linea);

        if (Tamaño == 0){
            cout << "Por el momento, la linea que anadira es la unica en la red" << endl;
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
        if (Evaluar[i].Get_Transferencia() == true) break;
    }

    return Existe;
}

int Red_Metro::Mostrar_Lineas()
{
    int Posicion;

    cout <<endl << "Lineas presentes en la red: " << endl;

    if (Tamaño == 0){
        cout << "La red no tiene lineas por el momento." << endl;
        Posicion = 1;

    }else{
        for (int i = 0; i < Tamaño; i++){
            cout << i+1 << ". " << Metro[i].Get_Nombre() << endl;
        }
        while (true){
            cout << "Seleccione la posicion en la cual quiere realizar los cambios: ";
            cin >> Posicion;
            if (Posicion < 1 || Posicion > Tamaño){
                cout <<endl<<"Ubicacion no valida, intente de nuevo."<< endl;
            }else break;
        }
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

    for (int i = 0; i < Tamaño-1; i++){
        Actualizacion[i] = Metro[i];
    }
    Actualizacion[Tamaño-1] =  Linea(Nombre_Linea, 0);

    delete[] Metro;
    Metro = Actualizacion;
}

void Red_Metro::Eliminar_Linea()
{
    int Posicion = Mostrar_Lineas();
    bool Existencia_Transferencia = Verificar_Estacion_Transferencia(Posicion);
    Linea * Actualizacion;

    if (Existencia_Transferencia) cout << endl << "No se puede eliminar la linea, existe una estacion de transferencia asociada." << endl;
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

int Red_Metro::Get_Tamaño()
{
    return Tamaño;
}

