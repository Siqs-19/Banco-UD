/*
  PROYECTO 8 - SISTEMA DE GESTIÓN DE CUENTAS BANCARIAS
  Integrantes: Eilen Restrepo, Valentina Umbarila, Sara QuiÃ±onez
  Fecha: Mayo 30 2026
  Version: 2.1
 
  Programa: Maneja cuentas bancarias, permite crear cuentas, depositar, retirar, transferir y realizar inversiones.

 */


// librerías
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

// Constantes
#define MAX_CUENTAS 50   
#define MAX_INVERSIONES 100

// Tasas de interés
#define TASA_ALTO 0.0925
#define TASA_CDT  0.11
#define IMPUESTO_4X1000 0.04

// Estructura de la cuenta
struct Cuenta {
    int numero;
    string nombre;
    double saldo;
};

// Estructura de inversión
struct Inversion {
    int numeroCuenta;
    string tipo;
    double monto;
    int meses;
    double valorFuturo;
    double ganancia;
    double valorNeto;
};

// Variables globales
Cuenta cuentas[MAX_CUENTAS];
Inversion inversiones[MAX_INVERSIONES];
int totalCuentas = 0;
int totalInversiones = 0;

// Prototipos de funciones
void crearCuenta();
void verCuentas();
void depositar();
void retirar();
void transferir();
void invertir();
void guardarEnArchivo();
void cargarArchivo();
void guardarInversion();
void cargarInversiones();
void verInversiones();
int buscarCuenta(int num);


// Programa principal
int main() {
	setlocale(LC_ALL, "Spanish"); //Uso de tildes
    cout << "--------------------------------------" << endl;
    cout << "Este programa permite gestionar cuentas bancarias y\nofrecer a sus usuarios opciones bÃ¡sicas de inversiÃ³n." << endl;
    cout << endl << "--------------------------------------" << endl;

    // Cargar cuentas
    cargarArchivo();

    // Cargar inversiones
    cargarInversiones();

    int opcion;

    cout << endl;
    cout << "  *********************************************" << endl;
    cout << "  *                                           *" << endl;
    cout << "  *              B A N C O   U D              *" << endl;
    cout << "  *       Universidad Distrital F.J.C.        *" << endl;
    cout << "  *                                           *" << endl;
    cout << "  *      Sistema de Gestión de Cuentas        *" << endl;
    cout << "  *         Bancarias con Inversion           *" << endl;
    cout << "  *                                           *" << endl;
    cout << "  *********************************************" << endl;
    cout << endl;

    // Ciclo principal del menú
    do {
        cout << endl;
        cout << " ===========================================" << endl;
        cout << "               MENU PRINCIPAL               " << endl;
        cout << " ===========================================" << endl;
        cout << " [1] Crear cuenta bancaria                  " << endl;
        cout << " [2] Consultar cuentas bancarias            " << endl;
        cout << " [3] Depositar dinero                       " << endl;
        cout << " [4] Retirar dinero                         " << endl;
        cout << " [5] Transferir dinero                      " << endl;
        cout << " [6] Invertir dinero                        " << endl;
        cout << " [7] Consultar inversiones                  " << endl;
        cout << " [0] Salir                                  " << endl;
        cout << " ===========================================" << endl;
        cout << " Seleccione una opcion: ";
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
        } else if (opcion == 7) {
            verInversiones();
        } else if (opcion == 0) {
          	cout << endl;
			cout << "  *********************************************" << endl;
			cout << "  *                                           *" << endl;
			cout << "  *     Gracias por usar nuestros servicios   *" << endl;
			cout << "  *                                           *" << endl;
			cout << "  *              B A N C O   U D              *" << endl;
			cout << "  *       Universidad Distrital F.J.C.        *" << endl;
			cout << "  *                                           *" << endl;
			cout << "  *         Hasta pronto! Vuelva pronto       *" << endl;
			cout << "  *                                           *" << endl;
			cout << "  *********************************************" << endl;
			cout << endl;
        } else {
            cout << "Opcion no válida, por favor intente de nuevo" << endl;
        }

    } while (opcion != 0);

    return 0;
}


// Guarda cuentas en archivo
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



//  Carga cuentas en archivo
void cargarArchivo() {
    ifstream archivo("cuentas.txt");

    // Error no existe el archivo
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

// Guarda inversiones en archivos
void guardarInversion() {
    ofstream archivo("inversiones.txt");

    if (!archivo) {
        cout << "Error: no se pudo guardar el archivo de inversiones" << endl;
        return;
    }

    for (int i = 0; i < totalInversiones; i++) {
        archivo << inversiones[i].numeroCuenta << endl;
        archivo << inversiones[i].tipo << endl;
        archivo << inversiones[i].monto << endl;
        archivo << inversiones[i].meses << endl;
        archivo << inversiones[i].valorFuturo << endl;
        archivo << inversiones[i].ganancia << endl;
        archivo << inversiones[i].valorNeto << endl;
    }

    archivo.close();
}

// Carga inversiones en archivos
void cargarInversiones() {
    ifstream archivo("inversiones.txt");

    if (!archivo) {
        return;
    }

    totalInversiones = 0;

    while (archivo >> inversiones[totalInversiones].numeroCuenta) {
        archivo.ignore();
        getline(archivo, inversiones[totalInversiones].tipo);
        archivo >> inversiones[totalInversiones].monto;
        archivo >> inversiones[totalInversiones].meses;
        archivo >> inversiones[totalInversiones].valorFuturo;
        archivo >> inversiones[totalInversiones].ganancia;
        archivo >> inversiones[totalInversiones].valorNeto;
        archivo.ignore();
        totalInversiones++;

        if (totalInversiones >= MAX_INVERSIONES) {
            break;
        }
    }

    archivo.close();
    cout << "Se cargaron " << totalInversiones << " inversiones." << endl;
}



//  Busca cuenta por número
int buscarCuenta(int num) {
    for (int i = 0; i < totalCuentas; i++) {
        if (cuentas[i].numero == num) {
            return i;
        }
    }
    return -1;  // Cuenta no encontrada
}



//  1. Crear cuenta bancaria
void crearCuenta() {
    cout << "\n--- CREAR CUENTA BANCARIA ---\n";

    //Verificar el máximo de cuentas
    if (totalCuentas >= MAX_CUENTAS) {
        cout << "Error: límite de cuentas alcanzado" << endl;
        return;
    }

    
    Cuenta newCuenta;


    cout << " Número de cuenta: ";
    cin >> newCuenta.numero;
    cin.ignore();

    //Validación
    while (newCuenta.numero <= 0) {
        cout << " Error: El número de la cuenta tiene que ser positiva. Intente de nuevo (0 para salir): " << endl;
        cin >> newCuenta.numero;
        cin.ignore();
        if (newCuenta.numero == 0) return;
    }

    while (buscarCuenta(newCuenta.numero) != -1) {
        cout << " Ya existe una cuenta con ese número" << endl;
        cin >> newCuenta.numero;
        cin.ignore();
    }

    //Nombre
    cout << " Nombre del titular: ";
    getline(cin, newCuenta.nombre);

    //Saldo
    cout << " Saldo inicial: $";
    cin >> newCuenta.saldo;
    cin.ignore();

    while (newCuenta.saldo < 0) {
        cout << " El saldo no puede ser negativo. Ingrese un saldo válido: $" << endl;
        cin >> newCuenta.saldo;
        cin.ignore();
    }

    // Guardar
    cuentas[totalCuentas] = newCuenta;
    totalCuentas++;
    guardarEnArchivo();

    // Registrar en transacciones
    ofstream trans("transacciones.txt", ios::app);
    trans << "NUEVA CUENTA: " << newCuenta.numero << " - " << newCuenta.nombre << " saldo: " << newCuenta.saldo << endl;
    trans.close();

    cout << " Cuenta creada exitosamente" << endl;
}



//  2. Consultar cuentas bancarias
void verCuentas() {
      cout << endl << " --- LISTA DE CUENTAS ---" << endl;
    if (totalCuentas == 0) {
        cout << " No hay cuentas registradas" << endl;
        return;
    }

    cout << "------------------------------------------------" << endl;
    cout << left
         << setw(12) << "  No.Cuenta"
         << setw(20) << "  Titular"
         << setw(14) << "  Saldo"
         << endl;
    cout << "------------------------------------------------" << endl;

        for (int i = 0; i < totalCuentas; i++) {
        cout << left
             << setw(12) << cuentas[i].numero
             << setw(20) << cuentas[i].nombre
             << "$" << fixed << setprecision(2) << cuentas[i].saldo
             << endl;
    }

    cout << "------------------------------------------------" << endl;
}



//  3. Depositar dinero
void depositar() {
    cout << endl << "--- DEPOSITAR DINERO ---" << endl;

    int num;
    cout << " Número de cuenta: ";
    cin >> num;
    cin.ignore();

    int indice = buscarCuenta(num);

    // ¿Existe?
    while (indice == -1) {
        cout << " Cuenta no encontrada" << endl;
        cout << " Ingrese un número de cuenta válido o ingrese 0 para salir: ";
        cin >> num;
        cin.ignore();
        if (num == 0) return;
        indice = buscarCuenta(num);
    }

    double monto;
    cout << " Monto a depositar: $";
    cin >> monto;
    cin.ignore();

    // Validar
    if (monto <= 0) {
        cout << " El monto debe ser mayor a 0" << endl;
        cout << " Ingrese un monto válido: $";
        cin >> monto;
        cin.ignore();
    }

    
    cuentas[indice].saldo += monto;
    guardarEnArchivo();

    // Guardar
    ofstream trans("transacciones.txt", ios::app);
    trans << "DEPÓSITO cuenta " << num << " monto: " << monto << " saldo nuevo: " << cuentas[indice].saldo << endl;
    trans.close();

    cout << " Depósito exitoso... Nuevo saldo: $" << cuentas[indice].saldo << endl;
}



//  4. Retirar dinero
void retirar() {
    cout << endl << "--- RETIRAR DINERO ---" << endl;

    int num;
    cout << " Número de cuenta: ";
    cin >> num;
    cin.ignore();

    int indice = buscarCuenta(num);

    if (indice == -1) {
        cout << " Cuenta no encontrada" << endl;
        return;
    }

    cout << " Saldo actual: $" << cuentas[indice].saldo << endl;

    double monto;
    cout << " Monto a retirar: $";
    cin >> monto;
    cin.ignore();

    while (monto <= 0) {
        cout << " El monto debe ser mayor a 0" << endl;
        cout << " Ingrese un monto válido (0 para salir): $";
        cin >> monto;
        cin.ignore();
        if (monto == 0) return;
    }

    //Verificar
    while (monto > cuentas[indice].saldo) {
        cout << " Saldo insuficiente. Saldo disponible: $" << cuentas[indice].saldo << endl;
    	cout << " Ingrese otro monto (0 para salir): $";
    	cin >> monto;
    	cin.ignore();
    	if (monto == 0) return;
}


    cuentas[indice].saldo -= monto;
    guardarEnArchivo();

    ofstream trans("transacciones.txt", ios::app);
    trans << "RETIRO cuenta " << num << " monto: " << monto << " saldo nuevo: " << cuentas[indice].saldo << endl;
    trans.close();

    cout << " Retiro exitoso... Saldo restante: $" << cuentas[indice].saldo << endl;
}


//  5. Transferir dinero
void transferir() {
    cout << endl << "--- TRANSFERIR DINERO ---" << endl;

    int numOrigen, numDestino;

    cout << " Cuenta origen (0 para salir): ";
    cin >> numOrigen;
    cin.ignore();
    
    if (numOrigen == 0) return;
	
	int cuentaOrigen  = buscarCuenta(numOrigen);
	
	while (cuentaOrigen == -1) {
        cout << " La cuenta origen no existe. Intente de nuevo (0 para salir): " << endl;
        cin >> numOrigen;
        cin.ignore();
        if (numOrigen == 0) return;
        cuentaOrigen = buscarCuenta(numOrigen);
    }

	
    cout << " Cuenta destino (0 para salir): ";
    cin >> numDestino;
    cin.ignore();
    
    if (numDestino == 0) return;

    int cuentaDestino = buscarCuenta(numDestino);

    while (cuentaDestino == -1) {
        cout << " La cuenta destino no existe. Intente de nuevo (0 para salir):" << endl;
        cin >> numDestino;
        cin.ignore();
        if (numDestino == 0) return;
   		cuentaDestino = buscarCuenta(numDestino);
    }

    if (numOrigen == numDestino) {
        cout << " No se puede transferir a la misma cuenta" << endl;
        return;
    }

    cout << " Saldo disponible: $" << cuentas[cuentaOrigen].saldo << endl;

    double monto;
    cout << " Monto a transferir (0 para salir):  ";
    cin >> monto;
    cin.ignore();
    
    if (monto == 0) return;

    while (monto <= 0) {
        cout << " El monto debe ser mayor a 0 (0 para salir):" << endl;
        cin >> monto;
        cin.ignore();
        if (monto == 0) return;
    }

    while (monto > cuentas[cuentaOrigen].saldo) {
        cout << " Saldo insuficiente. Saldo disponible: $" << cuentas[cuentaOrigen].saldo << endl;
        cout << " Ingrese otro monto (0 para salir): ";
		cin >> monto;
        cin.ignore();
        if (monto == 0) return;
    }

    //Transferir
    cuentas[cuentaOrigen].saldo  -= monto;
    cuentas[cuentaDestino].saldo += monto;

    guardarEnArchivo();

    ofstream trans("transacciones.txt", ios::app);
    trans << "TRANSFERENCIA de " << numOrigen << " a " << numDestino << " monto: " << monto << endl;
    trans.close();

    cout << " Transferencia exitosa!" << endl;
    cout << " Saldo cuenta origen:  $" << cuentas[cuentaOrigen].saldo << endl;
    cout << " Saldo cuenta destino: $" << cuentas[cuentaDestino].saldo << endl;
}



//  6. Invertir dinero
void invertir() {
    cout << endl << "--- INVERTIR DINERO ---" << endl;

    int num;
    cout << " Número de cuenta: ";
    cin >> num;
    cin.ignore();

    int indice = buscarCuenta(num);

    if (indice == -1) {
        cout << " Cuenta no encontrada" << endl;
        cout << " Ingrese un número de cuenta válido o ingrese 0 para salir: ";
        cin >> num;
        if (num == 0){
        	return;
        }
         else {
            cin.ignore();
        }
    }

    cout << " Saldo disponible: $" << cuentas[indice].saldo << endl;

    double monto;
    cout << " Monto a invertir: ";
    cin >> monto;
    cin.ignore();

    while (monto <= 0) {
        cout << " El monto debe ser mayor a 0 (0 para salir): $";
        cin >> monto;
    	cin.ignore();
    	if (monto == 0) return;
    }

    while (monto > cuentas[indice].saldo) {
        cout << " Saldo insuficiente. Saldo disponible: $" << cuentas[indice].saldo << endl;
   	    cout << " Ingrese un monto válido (0 para salir): $";
    	cin >> monto;
    	cin.ignore();
    	if (monto == 0) return;
}

    cout << " --------- Tipo de inversión ---------" << endl;
    cout << " [1] Alto Rendimiento (9.25% anual)   " << endl;
    cout << " [2] CDT (11% anual)                  " << endl;
    cout << " Seleccione una opción: ";
    int tipo;
    cin >> tipo;
    cin.ignore();

    int meses;
    cout << " ¿A cúantos meses quiere dejar la inversión?: ";
    cin >> meses;
    cin.ignore();

    if (meses <= 0) {
        cout << " Los meses deben ser positivos" << endl;
        cout << " Ingrese un número de meses válido: ";
        cin >> meses;
        cin.ignore();
    }

    // Cálculos
    double tasaAnual;

    if (tipo == 1) {
        tasaAnual = TASA_ALTO;
    } else if (tipo == 2) {
        tasaAnual = TASA_CDT;
    } else {
        cout << " Opcion inválida" << endl;
        cout << " Ingrese una opcion válida: ";
        cin >> tipo;
        cin.ignore();
        if (tipo == 1) {
            tasaAnual = TASA_ALTO;
        } else if (tipo == 2) {
            tasaAnual = TASA_CDT;
        } else {
            cout << " Opcion inválida, se cancelará la inversión" << endl;
            return;
        }
    }
	
	// Convierte tasa anual a mensual
    double tasaMensual = pow(1.0 + tasaAnual, 1.0 / 12.0) - 1.0; 

    // Fórmula de interés compuesto: VF = VP * (1 + im)^n
    // Capitalización mensual
	double valorFuturo = monto * pow(1.0 + tasaMensual, meses);
    double ganancia    = valorFuturo - monto;

    // Estructura de inversión
    Inversion inv;
    inv.numeroCuenta = num;
    inv.tipo         = (tipo == 1) ? "Alto rendimiento" : "CDT";
    inv.monto        = monto;
    inv.meses        = meses;
    inv.valorFuturo  = valorFuturo;
    inv.ganancia     = ganancia;
    inv.valorNeto    = 0;

    // Inversiones totales
    cout << " ====================================" << endl;
    cout << "               RESULTADO             " << endl;
    cout << " ====================================" << endl;
    cout << " Monto invertido: $ " << monto << endl;
    cout << " Plazo: " << meses << " meses" << endl;
    cout << " Tasa mensual: " << tasaMensual * 100 << "%" << endl;
    cout << " Valor futuro: $" << valorFuturo << endl;
    cout << " Ganancia: $" << ganancia << endl;

    // Si es CDT aplicar impuesto del 4%
    if (tipo == 2) {
        double impuesto  = ganancia * 0.04;
        inv.valorNeto = valorFuturo - impuesto;
        cout << " Impuesto 4x1000: $" << impuesto << endl;
        cout << " Valor neto final: $" << inv.valorNeto << endl;
    }
	
    // Descontar
    cuentas[indice].saldo -= monto;
	inversiones[totalInversiones] = inv;
	totalInversiones++;
	guardarEnArchivo();
	guardarInversion();

	ofstream trans("transacciones.txt", ios::app);
	trans << "INVERSIÓN cuenta " << num
    	  << " tipo: " << (tipo == 1 ? "Alto rendimiento" : "CDT")
      	  << " monto: " << monto
		  << " meses: " << meses
      	  << " valor futuro: " << valorFuturo << endl;
	trans.close();

	cout << " Inversión realizada... Saldo restante: $" << cuentas[indice].saldo << endl;

}

//  7. Consultar el total de inversiones
void verInversiones() {
    cout << endl << "  LISTA DE INVERSIONES" << endl;
    cout << endl;

    if (totalInversiones == 0) {
        cout << "  No hay inversiones registradas." << endl;
        return;
    }

    cout << "  " << left
         << setw(12) << " N. Cuenta"
         << setw(16) << " Monto"
         << setw(10) << " Meses"
         << setw(18) << " Valor futuro"
         << setw(16) << " Ganancia"
         << endl;

    cout << "  " << string(70, '-') << endl;

    for (int i = 0; i < totalInversiones; i++) {
        cout << "  " << left << fixed << setprecision(2)
             << setw(12) << inversiones[i].numeroCuenta
             << "$" << setw(15) << inversiones[i].monto
             << setw(10) << inversiones[i].meses
             << "$" << setw(17) << inversiones[i].valorFuturo
             << "$" << inversiones[i].ganancia
             << endl;
    }

    cout << "  " << string(70, '-') << endl;
    cout << "  Total de inversiones: " << totalInversiones << endl;
}
