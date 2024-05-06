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

void Red_Metro::Validacion_Error9(Linea &Linea, bool &Transferencia, int &Posicion_Estacion_Actual, bool &Termina_Proceso)
{
    Estacion *Estaciones = Linea.Get_Linea();


    if (Linea.GetTamaño() == 1 && Tamaño > 1 && Transferencia == false && Termina_Proceso == true){
        Error9_AñadirEstacion_En_LineaAislada();
        Transferencia = true;
        Estaciones[Posicion_Estacion_Actual].Set_Transfrencia(true);
    }
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

void Red_Metro::Validacion_Estacion_Transferencia(Linea &Actual, Linea &Conectar, int& Pos_Estacion_Actual)
{
    if (Primer_Conexion == false){
        Realizar_Conexion(Actual, Conectar, Pos_Estacion_Actual);
        Primer_Conexion = true;
    }
    else{
        if (Conectar.Get_LineaConectada() == Actual.Get_LineaConectada()){
            Error8_LineaInvalida();
            Actual.Eliminar_Estacion(Pos_Estacion_Actual);
        }else{
            Realizar_Conexion(Actual, Conectar, Pos_Estacion_Actual);
        }
    }
}

void Red_Metro::Realizar_Conexion(Linea &Actual, Linea &Conectar, int &Pos_Estacion_Actual)
{

    Estacion* Actual_ = Actual.Get_Linea();

    int Opcion;
    cout << "\nDe acuerdo a lo siguiente: ";
    cout << "\n1. Si desea que la estacion de transferencia se cree en la linea para conectar.";
    cout << "\n2. Si desea que la estacion de transferencia este asociada a otra en la linea que desea realizar la conexion." << endl;
    cout << "\nIngrese una opcion: "; cin >> Opcion;
    switch(Opcion){
        case 1:
            Conectar_EstacionNueva(Actual_, Pos_Estacion_Actual, Conectar, Actual);
            break;
        case 2:
            if(Conectar.Cantidad_Estaciones_Transferencia() > 0 && Conectar.GetTamaño() != 0){
                Conectar_EstacionExistente(Actual_, Pos_Estacion_Actual, Conectar, Actual);
            }else{
                Error10_LineaSinEstacionesDeTransferencia();
                cout << "Se agregara como una conexion nueva" << endl;
                Conectar_EstacionNueva(Actual_, Pos_Estacion_Actual, Conectar, Actual);
            }
            break;
        default:
            Conectar_EstacionNueva(Actual_, Pos_Estacion_Actual, Conectar, Actual);
            break;
        }
}

void Red_Metro::Conectar_EstacionNueva(Estacion *Estaciones, int &Pos_Estacion_Actual, Linea &Conectar, Linea &Actual)
{
    string Nombre_EstacionConexion = Estaciones[Pos_Estacion_Actual].Get_Nombre() + " " + Conectar.Get_Nombre();
    Actual.Set_LineaConectada(true);
    Estaciones[Pos_Estacion_Actual].Set_Nombre(Estaciones[Pos_Estacion_Actual].Get_Nombre() +" " + Actual.Get_Nombre());
    Conectar.Añadir_Estacion(true, Nombre_EstacionConexion);
    Conectar.Set_LineaConectada(true);
}

void Red_Metro::Conectar_EstacionExistente(Estacion *Estaciones, int &Pos_Estacion_Actual, Linea &Conectar, Linea &Actual)
{
    string Estacion_Transferencia_Elegida;
    cout << "\nTENGA EN CUENTA QUE: La nueva estacion tendra el nombre de la estacion creada tendra el nombre de la estacion de transferencia conectada.";
    Conectar.Mostrar_Estaciones_Linea();
    ModificarNombreEstacion(Estacion_Transferencia_Elegida);
    Estaciones[Pos_Estacion_Actual].Set_Nombre(Estacion_Transferencia_Elegida +" "+ Actual.Get_Nombre());
    Actual.Set_LineaConectada(true);
}

void Red_Metro::Añadir_Estacion()
{

    int Posicion_Estacion_Actual;
    bool Transferencia = false;
    bool Termina_Proceso = false;

    string Nombre_LineaActual;

    if (!Validacion_Error3(1)){
        int Posicion;
        if(!Validacion_Error4(Posicion)){
            Metro[Posicion].Añadir_Estacion(Termina_Proceso, Transferencia, Posicion_Estacion_Actual);
            Nombre_LineaActual = Metro[Posicion].Get_Nombre();
            Validacion_Error9(Metro[Posicion], Transferencia, Posicion_Estacion_Actual, Termina_Proceso);

            if(Transferencia){
            Estacion_Transferencia_Establecida(Metro[Posicion], Posicion_Estacion_Actual, Nombre_LineaActual);
            }
        }
    }
}

void Red_Metro::Estacion_Transferencia_Establecida(Linea &Actual, int& Posicion_Estacion_Actual, string& Nombre_LineaActual)
{
    int Posicion_Linea_Transferencia;
    string Nombre_Linea_Conectar;

    if (!Validacion_Error6(Posicion_Estacion_Actual, Actual)){
        Mostrar_Lineas_Para_Conectar(Nombre_LineaActual);
        if (Validacion_Error7(Nombre_Linea_Conectar, Posicion_Estacion_Actual, Actual, Nombre_LineaActual)){
            Posicion_Linea_Transferencia = Buscar_Posicion_Linea(Nombre_Linea_Conectar);
            Validacion_Estacion_Transferencia(Actual, Metro[Posicion_Linea_Transferencia], Posicion_Estacion_Actual);
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

void Red_Metro::ModificarNombreEstacion(string &Nombre_Estacion)
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Ingrese el nombre de la estacion de transferencia: ";
    getline(cin, Nombre_Estacion);
    Nombre_Estacion = Nombre_Estacion.substr(0, Nombre_Estacion.size() - 2);
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
{
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
    Primer_Conexion = false;
}

void Red_Metro::Añadir_Linea()
{
    string Nombre_Linea;
    Linea *Actualizacion;

    if(!Validacion_Error5(Nombre_Linea)){
        Tamaño += 1;
        Actualizacion = new Linea[Tamaño];
        copy(Metro, Metro + Tamaño - 1, Actualizacion);
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
        throw runtime_error("\nNo puede crearse una estacion de transferencia si hay una sola linea.");
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

void Red_Metro::Error8_LineaInvalida()
{
    try {
        throw runtime_error("La linea ingresada para crear la transferencia no es valida, ya que se encuentra conectada o es una linea aislada de la red central.");
    } catch (const runtime_error& ex) {
        cout << "Error: " << ex.what() << endl;
    }
}

void Red_Metro::Error9_AñadirEstacion_En_LineaAislada()
{
    try {
        throw runtime_error("La linea ingresada no puede contener una estacion que no sea de transferencia ya que estaria aislada de la red, se asignara como una estacion de transferencia.");
    } catch (const runtime_error& ex) {
        cout << endl << "Error: " << ex.what() << endl;
    }
}

void Red_Metro::Error10_LineaSinEstacionesDeTransferencia()
{
    try {
        throw runtime_error("La linea ingresada no contiene ninguna estacion de transferencia o esta vacia.");
    } catch (const runtime_error& ex) {
        cout << endl << "Error: " << ex.what() << endl;
    }
}



