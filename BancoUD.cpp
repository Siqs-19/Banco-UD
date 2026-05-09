/*
 * PROYECTO 8 - SISTEMA DE GESTION DE CUENTAS BANCARIAS
 * Integrantes: Eilen Restrepo, Valentina Umbarila, Sara Quiñonez
 * Fecha: Mayo 9 2026
 * Version: 1.0
 *
 * Descripcion: programa para manejar cuentas bancarias
 * por ahora solo creamos cuentas, consultamos, y hacemos depositos y retiros
 */


//LIBRERIAS
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

//CONSTANTES
#define MAX_CUENTAS 50   

//Tasas de interes
#define TASA_ALTO 0.0925
#define TASA_CDT  0.11

//Estructura de cuenta
struct Cuenta {
    int numero;
    string nombre;
    double saldo;
};

//VARIABLES GLOBALES
Cuenta cuentas[MAX_CUENTAS];
int totalCuentas = 0;

//PROTOTIPOS DE FUNCIONES
void crearCuenta();
void verCuentas();
void depositar();
void retirar();
void transferir();
void invertir();
void guardarEnArchivo();
void cargarDeArchivo();
int buscarCuenta(int num);


//PROGRAMA PRINCIPAL
int main() {

    //Cargar cuentas
    cargarDeArchivo();

    int opcion;

    cout << "--------------------------------------" << endl;
    cout << "   SISTEMA BANCARIO - PROYECTO 8" << endl;
    cout << "--------------------------------------" << endl;

    // ciclo principal del menu
    do {
        cout << endl;
        cout << "---- MENU PRINCIPAL ----" << endl;
        cout << "1. Crear cuenta" << endl;
        cout << "2. Ver cuentas" << endl;
        cout << "3. Depositar" << endl;
        cout << "4. Retirar" << endl;
        cout << "5. Transferir" << endl;
        cout << "6. Invertir" << endl;
        cout << "0. Salir" << endl;
        cout << "Elija una opcion: ";
        cin >> opcion;

        
        if (opcion == 1) {
            crearCuenta();
        } else if (opcion == 2) {
            verCuentas();
        } else if (opcion == 3) {
            depositar();
        } else if (opcion == 4) {
            retirar();
        } else if (opcion == 5) {
            transferir();
        } else if (opcion == 6) {
            invertir();
        } else if (opcion == 0) {
            cout << "Gracias por usar nuestros servicios." << endl;
        } else {
            cout << "Opcion no valida, intente de nuevo" << endl;
        }

    } while (opcion != 0);

    return 0;
}


// GUARDAR CUENTAS EN ARCHIVO
void guardarEnArchivo() {
    ofstream archivo("cuentas.txt");

    // Error
    if (!archivo) {
        cout << "Error: no se pudo guardar el archivo" << endl;
        return;
    }

    for (int i = 0; i < totalCuentas; i++) {
        archivo << cuentas[i].numero << endl;
        archivo << cuentas[i].nombre << endl;
        archivo << cuentas[i].saldo << endl;
    }

    archivo.close();
}



//  CARGAR CUENTAS DESDE ARCHIVO
void cargarDeArchivo() {
    ifstream archivo("cuentas.txt");

    //Errer no hay archivo
    if (!archivo) {
        return;
    }

    totalCuentas = 0;

    //Leer
    while (archivo >> cuentas[totalCuentas].numero) {
        archivo.ignore();
        getline(archivo, cuentas[totalCuentas].nombre);
        archivo >> cuentas[totalCuentas].saldo;
        archivo.ignore();
        totalCuentas++;

        
        if (totalCuentas >= MAX_CUENTAS) {
            break;
        }
    }

    archivo.close();
    cout << "Se cargaron " << totalCuentas << " cuentas." << endl;
}


//  BUSCAR CUENTA POR NUMERO
//  retorna el indice o -1 si no existe
int buscarCuenta(int num) {
    for (int i = 0; i < totalCuentas; i++) {
        if (cuentas[i].numero == num) {
            return i;
        }
    }
    return -1;  // no encontrada
}



//  1. CREAR CUENTA
void crearCuenta() {
    cout << endl << "-- CREAR CUENTA --" << endl;

    //Verificar
    if (totalCuentas >= MAX_CUENTAS) {
        cout << "Error: ya no hay espacio para mas cuentas" << endl;
        return;
    }

    Cuenta nueva;


    cout << "Numero de cuenta: ";
    cin >> nueva.numero;
    cin.ignore();

    //Validacion
    if (nueva.numero <= 0) {
        cout << "El numero debe ser positivo" << endl;
        return;
    }

    if (buscarCuenta(nueva.numero) != -1) {
        cout << "Ya existe una cuenta con ese numero" << endl;
        return;
    }

    //Nombre
    cout << "Nombre del titular: ";
    getline(cin, nueva.nombre);

    //Saldo
    cout << "Saldo inicial: ";
    cin >> nueva.saldo;
    cin.ignore();

    if (nueva.saldo < 0) {
        cout << "El saldo no puede ser negativo" << endl;
        return;
    }

    //Guardar
    cuentas[totalCuentas] = nueva;
    totalCuentas++;
    guardarEnArchivo();

    // Registrar en transacciones
    ofstream trans("transacciones.txt", ios::app);
    trans << "NUEVA CUENTA: " << nueva.numero << " - " << nueva.nombre << " saldo: " << nueva.saldo << endl;
    trans.close();

    cout << "Cuenta creada con exito!" << endl;
}



//  2. VER CUENTAS
void verCuentas() {
    cout << endl << "-- LISTA DE CUENTAS --" << endl;

    if (totalCuentas == 0) {
        cout << "No hay cuentas registradas" << endl;
        return;
    }

    cout << "--------------------------------------------" << endl;
    cout << "No.Cuenta   | Titular            | Saldo" << endl;
    cout << "--------------------------------------------" << endl;

    for (int i = 0; i < totalCuentas; i++) {
        cout << cuentas[i].numero << "          | ";
        cout << cuentas[i].nombre << "           | ";
        cout << "$" << cuentas[i].saldo << endl;
    }

    cout << "--------------------------------------------" << endl;
}



//  3. DEPOSITAR
void depositar() {
    cout << endl << "-- DEPOSITAR DINERO --" << endl;

    int num;
    cout << "Numero de cuenta: ";
    cin >> num;
    cin.ignore();

    int indice = buscarCuenta(num);

    // Existe ?
    if (indice == -1) {
        cout << "Cuenta no encontrada" << endl;
        return;
    }

    double monto;
    cout << "Monto a depositar: ";
    cin >> monto;
    cin.ignore();

    //Validar
    if (monto <= 0) {
        cout << "El monto debe ser mayor a 0" << endl;
        return;
    }

    
    cuentas[indice].saldo += monto;
    guardarEnArchivo();

    //Guardar
    ofstream trans("transacciones.txt", ios::app);
    trans << "DEPOSITO cuenta " << num << " monto: " << monto << " saldo nuevo: " << cuentas[indice].saldo << endl;
    trans.close();

    cout << "Deposito exitoso. Nuevo saldo: $" << cuentas[indice].saldo << endl;
}



//  4. RETIRAR
void retirar() {
    cout << endl << "-- RETIRAR DINERO --" << endl;

    int num;
    cout << "Numero de cuenta: ";
    cin >> num;
    cin.ignore();

    int indice = buscarCuenta(num);

    if (indice == -1) {
        cout << "Cuenta no encontrada" << endl;
        return;
    }

    cout << "Saldo actual: $" << cuentas[indice].saldo << endl;

    double monto;
    cout << "Monto a retirar: ";
    cin >> monto;
    cin.ignore();

    if (monto <= 0) {
        cout << "El monto debe ser mayor a 0" << endl;
        return;
    }

    //Verificar
    if (monto > cuentas[indice].saldo) {
        cout << "Saldo insuficiente" << endl;
        return;
    }

    cuentas[indice].saldo -= monto;
    guardarEnArchivo();

    ofstream trans("transacciones.txt", ios::app);
    trans << "RETIRO cuenta " << num << " monto: " << monto << " saldo nuevo: " << cuentas[indice].saldo << endl;
    trans.close();

    cout << "Retiro exitoso. Saldo restante: $" << cuentas[indice].saldo << endl;
}


//  5. TRANSFERIR
void transferir() {
    cout << endl << "-- TRANSFERIR DINERO --" << endl;

    int numOrigen, numDestino;

    cout << "Cuenta origen: ";
    cin >> numOrigen;
    cin.ignore();

    cout << "Cuenta destino: ";
    cin >> numDestino;
    cin.ignore();

    int iOrigen  = buscarCuenta(numOrigen);
    int iDestino = buscarCuenta(numDestino);

    if (iOrigen == -1) {
        cout << "La cuenta origen no existe" << endl;
        return;
    }

    if (iDestino == -1) {
        cout << "La cuenta destino no existe" << endl;
        return;
    }

    if (numOrigen == numDestino) {
        cout << "No puede transferir a la misma cuenta" << endl;
        return;
    }

    cout << "Saldo disponible: $" << cuentas[iOrigen].saldo << endl;

    double monto;
    cout << "Monto a transferir: ";
    cin >> monto;
    cin.ignore();

    if (monto <= 0) {
        cout << "El monto debe ser mayor a 0" << endl;
        return;
    }

    if (monto > cuentas[iOrigen].saldo) {
        cout << "Saldo insuficiente" << endl;
        return;
    }

    //Transferir
    cuentas[iOrigen].saldo  -= monto;
    cuentas[iDestino].saldo += monto;

    guardarEnArchivo();

    ofstream trans("transacciones.txt", ios::app);
    trans << "TRANSFERENCIA de " << numOrigen << " a " << numDestino << " monto: " << monto << endl;
    trans.close();

    cout << "Transferencia exitosa!" << endl;
    cout << "Saldo cuenta origen:  $" << cuentas[iOrigen].saldo << endl;
    cout << "Saldo cuenta destino: $" << cuentas[iDestino].saldo << endl;
}



//  6. INVERTIR
void invertir() {
    cout << endl << "-- INVERTIR DINERO --" << endl;

    int num;
    cout << "Numero de cuenta: ";
    cin >> num;
    cin.ignore();

    int indice = buscarCuenta(num);

    if (indice == -1) {
        cout << "Cuenta no encontrada" << endl;
        return;
    }

    cout << "Saldo disponible: $" << cuentas[indice].saldo << endl;

    double monto;
    cout << "Monto a invertir: ";
    cin >> monto;
    cin.ignore();

    if (monto <= 0) {
        cout << "El monto debe ser mayor a 0" << endl;
        return;
    }

    if (monto > cuentas[indice].saldo) {
        cout << "Saldo insuficiente" << endl;
        return;
    }

    cout << "Tipo de inversion:" << endl;
    cout << "1. Alto Rendimiento (9.25% anual)" << endl;
    cout << "2. CDT (11% anual)" << endl;
    cout << "Elija: ";
    int tipo;
    cin >> tipo;
    cin.ignore();

    int meses;
    cout << "Cuantos meses?: ";
    cin >> meses;
    cin.ignore();

    if (meses <= 0) {
        cout << "Los meses deben ser positivos" << endl;
        return;
    }

    //CALCULAR
    double tasaAnual;

    if (tipo == 1) {
        tasaAnual = TASA_ALTO;
    } else if (tipo == 2) {
        tasaAnual = TASA_CDT;
    } else {
        cout << "Opcion invalida" << endl;
        return;
    }

    double tasaMensual = pow(1.0 + tasaAnual, 1.0 / 12.0) - 1.0;

    // formula de interes compuesto: VF = VP * (1 + im)^n
    double valorFuturo = monto * pow(1.0 + tasaMensual, meses);
    double ganancia    = valorFuturo - monto;

    cout << endl << "---- RESULTADO ----" << endl;
    cout << "Monto invertido: $" << monto << endl;
    cout << "Plazo: " << meses << " meses" << endl;
    cout << "Tasa mensual: " << tasaMensual * 100 << "%" << endl;
    cout << "Valor futuro: $" << valorFuturo << endl;
    cout << "Ganancia: $" << ganancia << endl;

    // si es CDT aplicar impuesto del 4%
    if (tipo == 2) {
        double impuesto  = ganancia * 0.04;
        double valorNeto = valorFuturo - impuesto;
        cout << "Impuesto 4x1000: $" << impuesto << endl;
        cout << "Valor neto final: $" << valorNeto << endl;
    }

    // Descontar
    cuentas[indice].saldo -= monto;
    guardarEnArchivo();

    cout << "Inversion realizada. Saldo restante: $" << cuentas[indice].saldo << endl;

    // TODO: guardar la inversion y crear un menu para consultar inversiones
}

