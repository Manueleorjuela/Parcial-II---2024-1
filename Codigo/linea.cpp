#include "linea.h"

bool Linea::Validacion_Error1(string &Nombre_Estacion)
{
    bool Existe = false;
    string Nombre;
    cout << endl << "Ingrese el nombre de la nueva estacion: ";
    getline(cin, Nombre_Estacion);

    if(!Validacion_Linea_Vacia(0)) {

        for (int i = 0; i < Tamaño; i++) {
            Nombre = Linea_[i].Get_Nombre();
            if (Linea_[i].Get_Transferencia() == true){
                Nombre = Nombre.substr(0, Nombre.size() - 2);
            }
            if (Nombre == Nombre_Estacion) {
                Existe = true;
                Error1_EstacionRepetida();
                break;
            }
        }
    }
    return Existe;
}

bool Linea::Validacion_Linea_Vacia(int Case)
{
    bool Validacion = false;
    if (Linea_ == nullptr || Tamaño == 0){
        Validacion = true;
        switch (Case){
        case 0:
            cout << "Por el momento, la estacion que anadira es la unica en la linea." << endl;
            break;
        case 1:
        break;
        case 2:
            delete[] Linea_;
            Linea_ = nullptr;
        break;
        }
    }
    return Validacion;
}


bool Linea::Validacion_Error3(bool &Transferencia)
{
    int Opcion;
    bool Validacion = false;

    cout << endl << "De acuerdo a lo siguiente:" << endl;
    cout << "Ingrese 1 para indicar que la estacion es de transferencia." << endl;
    cout << "Ingrese 0 para indicar que la estacion no es de transferencia." << endl;
    cout << "Ingrese una opcion: ";
    cin >> Opcion;
    if (Opcion != 0 && Opcion != 1) {
        Error3_RequerimientoTransferenciaInvalido();
        Validacion = true;
    }else{
        Transferencia = static_cast<bool>(Opcion);
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return Validacion;
}

bool Linea::Validacion_Error4_Añadir(int &Posicion)
{
    bool Validacion = false;
    if (Validacion_Linea_Vacia(1)){
        Posicion = 1;
    }else{
        while (true){
        Mostrar_Estaciones();
        cout << "\nTeniendo en cuenta lo siguiente: \n.Ingrese 1 si desea que la estacion se ubique al inicio de la linea.";
        cout << "\n.Ingrese cualquier indice mostrado si desea que la nueva estacion se ubique en esa posicion.";
        cout << "\n.Ingrese el indice mayor + 1 si desea que la nueva estacion se ubique al final de la linea.";
        cout << "\nSelecciona la ubicacion de la estacion en la linea: ";
        cin >> Posicion;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (Posicion < 1 || Posicion > Tamaño+1){
            Validacion = true;
            Error4_PosicionInvalida();
            }
        else break;
        }
    }
    Posicion -=1;
    return Validacion;
}

bool Linea::Validacion_Error4_Eliminar(int &Posicion)
{
    bool Validacion = false;
    Mostrar_Estaciones();
    cout << "\nSeleccione la ubicacion de la estacion en la linea: ";
    cin >> Posicion;
    if (Posicion < 1 || Posicion > Tamaño) {
        Validacion = true;
        Error4_PosicionInvalida();
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Posicion -= 1;
    return Validacion;
}

bool Linea::Validacion_Error2(int &Posicion)
{
    bool Validacion = false;
    if (Linea_[Posicion].Get_Transferencia() == true){
        Error2_EstacionDeTransferenciaEncontrada();
        Validacion = true;
    }
    return Validacion;
}

void Linea::Mostrar_Estaciones()
{
    cout <<endl << "Estaciones presentes en la linea: " << endl;
    for (int i = 0; i < Tamaño; i++){
        cout << i+1 << ". " << Linea_[i].Get_Nombre() << endl;
    }
}

void Linea::Inicializar_Tiempos(int &Posicion)
{
    int Tiempo_Anterior;
    int Tiempo_Siguiente;


    if (Tamaño-1 == 0){
        Linea_[Posicion].Set_Tiempo_Anterior(0);
        Linea_[Posicion].Set_Tiempo_Siguiente(0);
    }else{
        if (Posicion == 0){
            Tiempo_Siguiente = Ingresar_Cambio_Tiempo(1);
            Linea_[Posicion].Set_Tiempo_Anterior(0);
            Linea_[Posicion].Set_Tiempo_Siguiente(Tiempo_Siguiente);
            Linea_[Posicion+1].Set_Tiempo_Anterior(Tiempo_Siguiente);
        }else if (Posicion == Tamaño-1){
            Tiempo_Anterior = Ingresar_Cambio_Tiempo(2);
            Linea_[Posicion].Set_Tiempo_Siguiente(0);
            Linea_[Posicion].Set_Tiempo_Anterior(Tiempo_Anterior);
            Linea_[Posicion-1].Set_Tiempo_Siguiente(Tiempo_Anterior);
        }
        if (Posicion != 0 && Posicion != Tamaño-1){
        Tiempo_Siguiente = Ingresar_Cambio_Tiempo(1);
        Tiempo_Anterior = Ingresar_Cambio_Tiempo(2);

        Linea_[Posicion-1].Set_Tiempo_Siguiente(Tiempo_Anterior);
        Linea_[Posicion].Set_Tiempo_Anterior(Tiempo_Anterior);
        Linea_[Posicion].Set_Tiempo_Siguiente(Tiempo_Siguiente);
        Linea_[Posicion+1].Set_Tiempo_Anterior(Tiempo_Siguiente);
        }
    }
}

void Linea::Eliminar_Tiempos(int &Posicion)
{
    int Nuevo_Tiempo;

    if (Tamaño == 1){
        Linea_[Posicion].Set_Tiempo_Anterior(0);
        Linea_[Posicion].Set_Tiempo_Siguiente(0);
    }else if (Tamaño > 1){
        Nuevo_Tiempo = (Linea_[Posicion].Get_Tiempo_Siguiente() + Linea_[Posicion].Get_Tiempo_Anterior())/2;
        Linea_[Posicion-1].Set_Tiempo_Siguiente(Nuevo_Tiempo);
        Linea_[Posicion+1].Set_Tiempo_Anterior(Nuevo_Tiempo);
    }
}

int Linea::Ingresar_Cambio_Tiempo(int Case)
{
    int Tiempo;
    switch(Case){
    case 1:
        cout << "Ingrese el tiempo que ahora toma ir hacia la estacion siguiente (En minutos): ";
        break;
    case 2:
        cout << "Ingrese el tiempo que ahora toma ir hacia la estacion anterior (En minutos): ";
        break;
    }
    cin >> Tiempo;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return Tiempo;
}

void Linea::Calcular_Tiempo_Caso(int &Posicion_Inicio, int &Posicion_Llegada, int &Tiempo)
{

    for (int i = Posicion_Inicio; i < Posicion_Llegada; i++){
        Tiempo += Linea_[i].Get_Tiempo_Siguiente();
    }
}

void Linea::Operar_Tiempo(int &Hora, int &Minuto, int &Tiempo)
{
    Minuto += Tiempo;
    if(Minuto >= 60){
        Hora+=1;
        Minuto = Minuto+1 - 60;
    }
}

void Linea::Mostrar_Estaciones_Linea()
{
    cout << endl << "\nEstaciones de transferencia presentes en la linea: "<< endl;
    int Cont = 1;
    for (int i = 0; i < Tamaño; i++){
        if (Linea_[i].Get_Transferencia() == true){
            cout << Cont <<". " << Linea_[i].Get_Nombre()  << endl;
        }
    }
}

void Linea::Calcular_Tiempo_Entre_Estaciones()
{
    int Estacion_Inicio;
    int Estacion_Llegada;
    cout << "\nEstacion de salida. ";
    Validacion_Error4_Eliminar(Estacion_Inicio);
     cout << "\nEstacion de llegada. ";
    Validacion_Error4_Eliminar(Estacion_Llegada);

    int Tiempo_Aproximado = 0;
    if (Estacion_Inicio > Estacion_Llegada){

        int Aux = Estacion_Llegada;
        Estacion_Llegada = Estacion_Inicio;
        Estacion_Inicio = Aux;
    }


    Calcular_Tiempo_Caso(Estacion_Inicio, Estacion_Llegada, Tiempo_Aproximado);


    auto tiempo_actual = chrono::system_clock::now();
    time_t tiempo_actual_t = chrono::system_clock::to_time_t(tiempo_actual);
    tm *tiempo_local = localtime(&tiempo_actual_t);

    int Hora = tiempo_local->tm_hour;
    int Minuto = tiempo_local->tm_min;
    Operar_Tiempo(Hora, Minuto, Tiempo_Aproximado);
    cout << "La hora aproximada de llegada desde estacion " << Linea_[Estacion_Inicio].Get_Nombre();
    cout << " hasta estacion " << Linea_[Estacion_Llegada].Get_Nombre();
    cout << " es " << Hora << ":" << Minuto <<"." << endl;
}

Linea::Linea(string Nombre_Linea, int Tamaño_Linea)
{
    Nombre = Nombre_Linea;
    if (Tamaño_Linea > 0) {
        Linea_ = new Estacion[Tamaño];
    } else {
        Linea_ = nullptr;}
    Tamaño =  Tamaño_Linea;
        Linea_Conectada = false;
}

Linea::~Linea()
{
    if (Tamaño >0) delete[] Linea_;
}


Linea::Linea()
{
    Nombre = "No tiene nombre";
    Tamaño = 0;
    Linea_ = nullptr;
}

void Linea::Añadir_Estacion(bool &Termina_Proceso, bool &Es_De_Transferencia, int& Posicion_Estacion)
{
    string Nombre_Estacion;
    if(!Validacion_Error1(Nombre_Estacion)){
        if(!Validacion_Error3(Es_De_Transferencia)){
            Validacion_Error4_Añadir(Posicion_Estacion);
                Tamaño += 1;
                Estacion *Actualizacion = new Estacion[Tamaño];
                for (int i = 0; i < Tamaño; i++) {
                    if (i < Posicion_Estacion) {
                        Actualizacion[i] = Linea_[i];
                    }else if (i == Posicion_Estacion) {
                        Actualizacion[i] = Estacion(Nombre_Estacion, Es_De_Transferencia,0, 0);
                    }else {
                        Actualizacion[i] = Linea_[i - 1];
                    }
                }                
                delete [] Linea_;
                Linea_ = Actualizacion;
                Inicializar_Tiempos(Posicion_Estacion);
                Termina_Proceso = true;
        }
    }
}

void Linea::Añadir_Estacion(bool Transferencia, string &Nombre_Estacion_Conexion)
{
    int Posicion_Estacion;
    Validacion_Error4_Añadir(Posicion_Estacion);
    Tamaño += 1;
    Estacion *Actualizacion = new Estacion[Tamaño];
    for (int i = 0; i < Tamaño; i++) {
        if (i < Posicion_Estacion) {
        Actualizacion[i] = Linea_[i];
        }else if (i == Posicion_Estacion) {

            Actualizacion[i] = Estacion(Nombre_Estacion_Conexion, Transferencia,0,0);

        }else {
        Actualizacion[i] = Linea_[i - 1];
        }
    }
    delete [] Linea_;
    Linea_ = Actualizacion;
    Inicializar_Tiempos(Posicion_Estacion);
}

void Linea::Eliminar_Estacion()
{
    int Posicion;
    if(!Validacion_Error4_Eliminar(Posicion)){
        if(!Validacion_Error2(Posicion)){ 
            if(!Validacion_Linea_Vacia(2)){
                Tamaño -=1;
                Eliminar_Tiempos(Posicion);
                Estacion *Actualizacion = new Estacion[Tamaño];
                for (int i = 0; i < Tamaño; i++){
                    if (i < Posicion){
                        Actualizacion[i] = Linea_[i];
                    }else if(i >= Posicion){
                        Actualizacion[i] = Linea_[i+1];
                    }
                }
                delete [] Linea_;
                Linea_ = Actualizacion;
            }
        }
    }
}

void Linea::Eliminar_Estacion(int &Posicion_Estacion)
{

    if(!Validacion_Linea_Vacia(2)){
        Tamaño -=1;
        Estacion *Actualizacion = new Estacion[Tamaño];
        for (int i = 0; i < Tamaño; i++){
            if (i < Posicion_Estacion){
            Actualizacion[i] = Linea_[i];
            }else if(i >= Posicion_Estacion){
            Actualizacion[i] = Linea_[i+1];
            }
        }
        delete [] Linea_;
        Linea_ = Actualizacion;
    }
}

int Linea::Cantidad_Estaciones_Transferencia()
{
    int Contador = 0;
    for (int i = 0; i < Tamaño; i++){
        if (Linea_[i].Get_Transferencia() == true){
            Contador++;
        }
    }
    return Contador;
}

int Linea::GetTamaño()
{
    return Tamaño;
}

string Linea::Get_Nombre()
{
    return Nombre;
}

Estacion *Linea::Get_Linea()
{
    return Linea_;
}

bool Linea::Get_LineaConectada()
{
    return Linea_Conectada;
}

void Linea::Set_LineaConectada(bool Cambio)
{
    Linea_Conectada = Cambio;
}

void Linea::Error1_EstacionRepetida()
{
    try {
        throw runtime_error("La estacion ingresada ya esta almacenada en la linea.");
    } catch (const runtime_error& ex) {
        cout << "Error: " << ex.what() << endl;
    }
}

void Linea::Error2_EstacionDeTransferenciaEncontrada()
{
    try {
        throw runtime_error("La estacion ingresada es de transferencia, no puede eliminarse.");
    } catch (const runtime_error& ex) {
        cout << "Error: " << ex.what() << endl;
    }
}

void Linea::Error3_RequerimientoTransferenciaInvalido()
{
    try {
        throw runtime_error("Condicion ingresada invalida.");
    } catch (const runtime_error& ex) {
        cout << "Error: " << ex.what() << endl;
    }
}

void Linea::Error4_PosicionInvalida()
{
    try {
        throw runtime_error("La posicion ingresada es invalida. Intete de nuevo.");
    } catch (const runtime_error& ex) {
        cout << "Error: " << ex.what() << endl;
    }
}


