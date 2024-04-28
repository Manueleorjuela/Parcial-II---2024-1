#include "linea.h"

string Linea::Existencia_Estacion()
{
    string Nombre_Estacion;
    bool Existe = true;

    while (Existe) {
        cout << "Ingrese el nombre de la nueva estacion: ";
        getline(cin, Nombre_Estacion);
        for (int i = 0; i < Tamaño; i++) {
            if (Linea_[i].Get_Nombre() == Nombre_Estacion) {
                cout << "La estacion ya existe en la linea, pruebe con otro." << endl;
                break;

            }else Existe = false;
        }
        if (!Existe) break;
    }

    return Nombre_Estacion;
}

bool Linea::Verificacion_Transferencia()
{
    int Transferencia;
    while (true) {
        cout << endl << "De acuerdo a lo siguiente:" << endl;
        cout << "Ingrese 1 para indicar que la estacion es de transferencia." << endl;
        cout << "Ingrese 0 para indicar que la estacion no es de transferencia." << endl;
        cout << "Ingrese una opcion: ";
        if (!(cin >> Transferencia)) {
            cout << "Entrada invalida. Por favor, ingrese un valor numerico (0 o 1)." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (Transferencia == 0 || Transferencia == 1) {
            break;
        } else {
            cout << "Opcion invalida. Por favor, ingrese 0 o 1." << endl;
        }
    }
    return static_cast<bool>(Transferencia);
}

int Linea::Mostrar_Lineas()
{
    int Posicion;
    //Mostrar las estaciones de la linea

}


Linea::Linea(string Nombre_Linea, int Tamaño_Linea)
{
    Nombre = Nombre_Linea;
    Tamaño = Tamaño_Linea;
    Linea_ = new Estacion[Tamaño];
}

void Linea::Añadir_Estacion()
{
    string Nombre_Estacion = Existencia_Estacion();
    bool Es_De_Transferencia = Verificacion_Transferencia();
    int Posicion = 2;
    Linea_[Posicion] = Estacion(Nombre_Estacion, Es_De_Transferencia);
    cout << Linea_[Posicion].Get_Nombre() << endl;
}


Linea::~Linea()
{
    delete[] Linea_;
}
