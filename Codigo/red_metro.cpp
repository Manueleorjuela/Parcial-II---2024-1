#include "red_metro.h"

string Red_Metro::Verificar_Nombre_Linea()
{
    string Nombre_Linea;
    bool Existe = true;

    while (Existe) {
        cout << endl << "Ingrese el nombre de la nueva linea: ";
        getline(cin, Nombre_Linea);

        if (Tamaño == 0){
            cout << endl << "Por el momento, la linea que anadira es la unica en la red" << endl;
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

    if (Evaluar != nullptr){
        for (int i = 0; i < Dimension_Linea; i++){
            if (Evaluar[i].Get_Transferencia() == true) break;
        }
    }else{
        cout << "La linea no tiene estaciones aun." << endl;
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

int Red_Metro::Seleccionar_()
{
    Mostrar_Lineas();

    int Posicion;

    while (true){
           cout << "Seleccione la posicion en la cual quiere realizar los cambios: ";
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

    if (Tamaño == 0){
        cout << endl << "No puedes eliminar lineas, no existe ninguna." << endl;
    }
    else{

        Posicion = Seleccionar_();

        Existencia_Transferencia = Verificar_Estacion_Transferencia(Posicion);

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
}

int Red_Metro::Get_Tamaño()
{
    return Tamaño;
}

