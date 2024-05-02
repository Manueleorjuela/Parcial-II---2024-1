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

bool Red_Metro::Validacion_Error6(int& Posicion_Estacion, Linea &Linea)
{
    bool Validacion = false;
    if (Tamaño == 1){
        Linea.Eliminar_Estacion(Posicion_Estacion);
        Error6_CrearEstacionTransConUnaSolaLinea();
        Validacion = true;
    }
    return Validacion;
}

bool Red_Metro::Validacion_Error7(string &Nombre_LineaConectar, int& Posicion_Estacion, Linea &Linea, string &Nombre_LineaActual)
{
    cout << "Ingrese el nombre de la linea que desea conectar: ";
    cin >> Nombre_LineaConectar;
    bool Validacion = false;
    for (int i = 0; i < Tamaño; i++){
        if (Nombre_LineaConectar == Metro[i].Get_Nombre() && Nombre_LineaConectar != Nombre_LineaActual){
            Validacion = true;
            break;
        }
    }
    if (!Validacion){
        Error7_LineaIngresadaNoHaceParteDeLaRed();
        Linea.Eliminar_Estacion(Posicion_Estacion);
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return Validacion;
}

bool Red_Metro::Validacion_Linea_Conectar_Ya_Conectada(string &Nombre_Linea_Actual, string &Nombre_LineaConectar, int Case, Linea &Linea, int& Posicion_Estacion)
{
    bool Validacion = false;
    cout << Nombre_LineaConectar << endl;
    if (Lineas_Conectadas == nullptr){
        Validacion = false;
    }else{
        switch (Case){
        case 1:
            for (int i = 0; i < Cantidad_Conexiones; i++){
                if (Nombre_LineaConectar == Lineas_Conectadas[i]){
                    Validacion = true;
                }
            }
        break;
        case 2:
        for (int i = 0; i < Cantidad_Conexiones; i++){
                if (Nombre_LineaConectar == Lineas_Conectadas[i] && Nombre_Linea_Actual != Nombre_LineaConectar){
                    Error7_LineaIngresadaNoHaceParteDeLaRed();
                    Linea.Eliminar_Estacion(Posicion_Estacion);
                    Validacion = true;
                }
            }
        break;
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

bool Red_Metro::Validacion_Error2(Linea &Linea)
{
    bool Existe = false;
    int Dimension_Linea = Linea.GetTamaño();
    Estacion *Evaluar = Linea.Get_Linea();

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
            case 2:
            delete[] Metro;
            Metro = nullptr;
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

    int Posicion_Estacion;
    int Posicion_Linea_Transferencia;
    bool Transferencia;
    string Nombre_LineaActual;
    string Nombre_LineaConectar;
    string Nombre_Estacion_Conexion;

    if (!Validacion_Error3(1)){
        int Posicion;
        if(!Validacion_Error4(Posicion)){
            Metro[Posicion].Añadir_Estacion(Nombre_Estacion_Conexion, Transferencia, Posicion_Estacion);
            Nombre_LineaActual = Metro[Posicion].Get_Nombre();
            if(Transferencia){
                if(!Validacion_Error6(Posicion_Estacion, Metro[Posicion])){
                    Mostrar_Lineas_Para_Conectar(Nombre_LineaActual);
                    if(Validacion_Error7(Nombre_LineaConectar, Posicion_Estacion, Metro[Posicion], Nombre_LineaActual)){

                        if(Validacion_Linea_Conectar_Ya_Conectada(Nombre_LineaConectar, Nombre_LineaActual,1, Metro[Posicion_Estacion], Posicion_Estacion)){

                            if(!Validacion_Linea_Conectar_Ya_Conectada(Nombre_LineaActual, Nombre_LineaConectar, 2, Metro[Posicion_Estacion], Posicion_Estacion)){
                                Posicion_Linea_Transferencia = Buscar_Posicion_Linea(Nombre_LineaConectar);
                                Metro[Posicion_Linea_Transferencia].Añadir_Estacion(Transferencia, Nombre_Estacion_Conexion);
                            }
                        }else{
                            cout << "No esta" << endl;
                            Posicion_Linea_Transferencia = Buscar_Posicion_Linea(Nombre_LineaConectar);
                            Metro[Posicion_Linea_Transferencia].Añadir_Estacion(Transferencia, Nombre_Estacion_Conexion);
                        }

                        if (Lineas_Conectadas == nullptr){
                            Cantidad_Conexiones +=2;
                            string *Actualizacion = new string[Cantidad_Conexiones];
                            Actualizacion[0] = Nombre_LineaActual;
                            Actualizacion[1] = Nombre_LineaConectar;
                            delete[] Lineas_Conectadas;
                            Lineas_Conectadas = Actualizacion;
                            cout << Lineas_Conectadas[0] << endl;
                            cout << Lineas_Conectadas[1] << endl;

                        }else{
                            cout << Cantidad_Conexiones << endl;
                            Cantidad_Conexiones +=1;
                            string *Actualizacion = new string[Cantidad_Conexiones];
                            for (int i = 0; i < Cantidad_Conexiones-1; i++){
                                Actualizacion[i] = Lineas_Conectadas[i];
                                cout << Actualizacion[i] << endl;

                            }
                            Actualizacion[Cantidad_Conexiones-1] = Nombre_LineaActual;
                            cout << Actualizacion[Cantidad_Conexiones-1] << endl;
                            delete[] Lineas_Conectadas;
                            Lineas_Conectadas = Actualizacion;
                        }
                    }
                }
            }
        }
    }
}

int Red_Metro::Buscar_Posicion_Linea(string &Nombre_Linea)
{
    int Pos = 0;
    for (int j = 0; j < Tamaño; j++){
        if (Nombre_Linea == Metro[j].Get_Nombre()){
            Pos = j;
            break;
        }
    }
    return Pos;
}

void Red_Metro::Mostrar_Lineas_Para_Conectar(string &Nombre_Linea_Actual)
{
    int Cont = 1;
    cout << endl << "Lineas presentes para una transferencia: " << endl;
    for (int i = 0; i < Tamaño; i++){
        if (Nombre_Linea_Actual != Metro[i].Get_Nombre()){
            cout << Cont <<". " << Metro[i].Get_Nombre() << endl;
            Cont++;
        }
    }
}

void Red_Metro::Eliminar_Estacion()
{;

    if (!Validacion_Error3(1)){
        int Posicion ;
        if (!Validacion_Error4(Posicion)){
            if (!Validacion_Error1(Metro[Posicion])){
                Metro[Posicion].Eliminar_Estacion();
            }
        }
    }
}

bool Red_Metro::Validacion_Error4(int &Posicion)
{
    bool Validacion = false;
    Mostrar_Lineas();
    cout << endl<<"Seleccione la posicion en la cual quiere realizar los cambios: ";
    cin >> Posicion;
    if (Posicion < 1 || Posicion > Tamaño){
        Error4_PosicionInvalida();
        Validacion = true;
    }
    Posicion -=1;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return Validacion;
}

Red_Metro::Red_Metro()
{
    Tamaño = 0;
    Metro = nullptr;
    Lineas_Conectadas = nullptr;
    Cantidad_Conexiones = 0;
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
        if(!Validacion_Error4(Posicion)){
            if (!Validacion_Error2(Metro[Posicion])){
                Tamaño -=1;
                if(!Validacion_Error3(2)){
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

void Red_Metro::Error6_CrearEstacionTransConUnaSolaLinea()
{
    try {
        throw runtime_error("No puede crearse una estacion de transferencia si hay una sola linea.");
    } catch (const runtime_error& ex) {
        cout << "Error: " << ex.what() << endl;
    }
}

void Red_Metro::Error7_LineaIngresadaNoHaceParteDeLaRed()
{
    try {
        throw runtime_error("La linea ingresada para crear la transferencia no es valida.");
    } catch (const runtime_error& ex) {
        cout << "Error: " << ex.what() << endl;
    }
}


