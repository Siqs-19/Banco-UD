# Banco-UD  Sistema de Gestión de Cuentas Bancarias

Proyecto 8 — Programación

Integrantes: Eilen Restrepo, Valentina Umbarila, Sara Quiñonez<br/>

# Programa:
Sistema de consola que permite gestionar cuentas bancarias básicas. Con él se puede crear cuentas, depositar, retirar, transferir dinero entre cuentas e invertir en productos financieros (Alto Rendimiento y CDT), aplicando interés compuesto.

Toda la información se guarda automáticamente en archivos de texto para que no se pierda al cerrar el programa.

# Requisitos: 

-Compilador de C++ (g++ recomendado).

-Sistema operativo: Windows, Linux o macOS.

-No requiere librerías externas.

-Instalar compilador MinGW (Windows) o g++ (Linux/macOS) y la extensión C/C++ (para ejecutar con Visual Studio Code) 	

# Ejecución: 
### OPCION 1 - EJECUCION MEDIANTE UNA TERMINAL:

  Abrir una terminal en la carpeta donde está el archivo BancoUD.cpp y ejecutar:
        
	bashg++ BancoUD.cpp -o banco -lm
        
  Si no hay errores, se crea el ejecutable banco.exe (o banco en Linux).
  
  Ejecutar el archivo creado:
  
  Windows:                                               
      
	banco.exe  
			 
Linux / macOS: 

	./banco  

<br/>

### OPCION 2 - EJECICION EN DEV++:
  1. Descargar y abrir el programa de Dev++.
  
  2. Ir a Archivo → Abrir proyecto o archivo y seleccionar proyecto_banco_v2.cpp.
  
  3. Ir a Archivo → Nuevo → Proyecto, elegir Aplicación de consola, marcar C++ y darle un nombre (ej. Banco). Confirmar con Aceptar.
  
  4. En el panel izquierdo, clic derecho sobre el proyecto → Agregar al proyecto → seleccionar BancoUD.cpp. Si ya había un main.cpp de ejemplo, eliminarlo del proyecto.
  
  5. Presionar F9 (Compilar y ejecutar) o ir a Ejecutar → Compilar y ejecutar.

<br/>

### OPCION 3 - VISUAL STUDIO CODE:
  1. Descargar y abrir VS Code.
  
  2. Ir a Archivo → Abrir carpeta y seleccionar la carpeta que contiene BancoUD.cpp.
  
  3. Abrir el archivo BancoUD.cpp desde el explorador lateral.

  4. Ejecutar el programa con la opcion "run C/C++ File", luego, si es necesario elegir el compilador "C/C++: g++ -15 build and debug active file"

  En caso de que no logre ejecutar el programa intente usar alguna de las otras opciones de ejecucion o consulte el [manual de VSCode](https://code.visualstudio.com/docs/languages/cpp)
