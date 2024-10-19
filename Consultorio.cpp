#include <iostream>
#include <queue>
#include <list>

class Paciente {
public:
	std::string nombre;
	int edad;
	std::string padecimiento;
	float costo;
};

void ingresarDatos(std::queue<Paciente> &cola) {
	Paciente p;
	std::cout << "Ingrese los datos del paciente:\n";
	std::cout << "Nombre: ";
	std::cin >> p.nombre;
	std::cout << "Edad: ";
	std::cin >> p.edad;
	std::cout << "Padecimiento: ";
	std::cin >> p.padecimiento;
	std::cout << "Costo: ";
	std::cin >> p.costo;
	cola.push(p);
}

void mostrarPaciente(Paciente &p) {
	std::cout << "Nombre: " << p.nombre << ", Edad: " << p.edad << ", Padecimiento: " << p.padecimiento << ", Costo: " << p.costo << std::endl;
}

void mostrarSiguiente(std::queue<Paciente> &p) { // Mostrar el siguiente paciente sin eliminar al primero
	if (p.size() > 1) { // Verificamos que en la cola haya mas de un paciente
		std::queue<Paciente> temp = p; // Cola temporal
		temp.pop(); // Eliminamos al primer paciente de la cola temporal
		mostrarPaciente(temp.front()); //Mostramos al paciente siguiente
	}
	else {
		std::cout << "No hay paciente siguiente al primero de la cola.\n";
	}
}

void mostrarCola(std::queue<Paciente> &p) {
	std::queue<Paciente> temp = p; // Cola temporal que se usara para mostrar cada paciente
	if (p.empty()) {
		std::cout << "La cola esta vacia.\n";
	}
	while (!temp.empty()) {
		Paciente m = temp.front(); // Variable de tipo Paciente que tomara el valor del primer elemento de la cola temporal
		mostrarPaciente(m); // Mostramos este paciente en cada ciclo
		temp.pop(); // Eliminamos este paciente de la cola temporal
	}
}

void infoPaciente(std::queue<Paciente> &p, int posicion) {
	std::queue<Paciente> temp = p; // Cola temporal
	int i = 1; // Iniciamos el contador en 1 y no en 0 por ser la manera natural de contar numeros (a partir del primero == 1)
	bool encontrado = false; // De mantenerse en "false", se mostrara un error "paciente no encontrado"
	
	if (posicion < 1 || posicion >= p.size()+1) { // Manera natural de contar numeros en contraposicion a como se cuenta en arrays (de 0 a .length()-1)
		std::cout << "Posicion no valida." << std::endl;
		return;
	}
	
	while (!temp.empty()) {
		Paciente actual = temp.front(); // Tomara el valor del primer elemento de la cola en cada ciclo
		temp.pop(); // Se elimina dicho elemento
		
		if (i == posicion) { // Si el parametro de posicion de infoPaciente() y el contador coinciden...
			mostrarPaciente(actual); // ...se muestra el elemento actual
			encontrado = true; // ...y cambiamos la booleana a True
			break;
		}
		i++;
	}
	
	if (!encontrado) {
		std::cout << "Paciente en la posicion " << posicion << " no encontrado." << std::endl;
	}
}

void atenderPaciente(std::queue<Paciente> &p, std::list<Paciente> &historial, float &saldo) {
	if (!p.empty()) {
		Paciente siguiente = p.front(); // Por "siguiente" se entiende el paciente actual en ser atendido, "siguiente pase"
		std::cout << "Atendiendo siguiente paciente:\n";
		mostrarPaciente(siguiente); // Paciente en ser atendido
		saldo += siguiente.costo; // Se suma el costo al saldo
		historial.push_back(siguiente); // Aniadimos sus datos al historial
		p.pop(); // Se elimina al paciente ya atendido
	}
	else {
		std::cout << "No hay pacientes en la cola para atender." << std::endl;
	}
}

void eliminarPaciente(std::queue<Paciente> &p, int posicion) {
	std::queue<Paciente> temp; // Cola temporal para almacenar los elementos restantes
	int i = 1;
	bool encontrado = false; // De mantenerse en "false", se mostrara un error "paciente no encontrado"
	
	if (posicion < 1 || posicion >= p.size()+1) { // verificar que la posicion es valida (manera natural de contar numeros)
		std::cout << "Posicion no valida." << std::endl;
		return;
	}
	
	while (!p.empty()) { // Recorremos la cola original
		Paciente actual = p.front(); // primer elemento de la cola temporal
		p.pop(); // Se elimina dicho elemento
		
		if (i == posicion) { // Si el parametro de posicion de eliminarPaciente() y el contador coinciden...
			encontrado = true;
			std::cout << "Paciente en la posicion " << posicion << " eliminado de la cola." << std::endl; // ...no se agrega a la cola temporal
		}
		else {
			temp.push(actual); // Si no coinciden, aniadimos el elemento a la cola temporal
		}
		i++;
	}
	
	if (!encontrado) {
		std::cout << "Paciente en la posicion " << posicion << " no encontrado en la cola." << std::endl;
	}
	
	p = temp; // Reemplazamos la cola original por la cola temporal (que no contendra el elemento eliminado, si se hubiese hallado)
}

void mostrarHistorial(std::list<Paciente> &historial) {
	if (historial.empty()) {
		std::cout << "Historial vacio." << std::endl;
	}
	else {
		for (Paciente &p : historial) { // contenedor = coleccion ordenada del mismo tipo de datos en la que cada elemento se almacena en una posicion especifica
			mostrarPaciente(p);
		}
	}
}

int main() {
	std::queue<Paciente> cola;
	float saldo = 0;
	std::list<Paciente> historial;
	int op;
	
	do {
		system("cls");
		std::cout << "+++ Consultorio +++\n\n";
		std::cout << "Seleccione una opcion:\n";
		std::cout << "1. Registrar paciente.\n";
		std::cout << "2. Atender paciente.\n";
		std::cout << "3. Consultar proximo paciente.\n";
		std::cout << "4. Mostrar la cola entera de pacientes.\n";
		std::cout << "5. Buscar paciente por posicion en cola.\n";
		std::cout << "6. Eliminar paciente por posicion en cola.\n";
		std::cout << "7. Consultar saldo.\n";
		std::cout << "8. Consultar historial de atencion.\n";
		std::cout << "9. Salir.\n\n";
		std::cout << "Opcion (1-9): ";
		std::cin >> op;
		
		switch (op) {
		case 1:
			ingresarDatos(cola);
			break;
		case 2:
			atenderPaciente(cola, historial, saldo);
			std::cout << "Oprima una tecla para continuar...\n";
			std::cin.ignore();	// Limpiar el buffer de entrada
			std::cin.get();		// Esperar a que el usuario presione una tecla
			break;
		case 3:
			mostrarSiguiente(cola);
			std::cout << "Oprima una tecla para continuar...\n";
			std::cin.ignore();
			std::cin.get();
			break;
		case 4:
			mostrarCola(cola);
			std::cout << "Oprima una tecla para continuar...\n";
			std::cin.ignore();
			std::cin.get();
			break;
		case 5:
			int posicion;
			std::cout << "Ingrese la posicion del paciente a buscar: ";
			std::cin >> posicion;
			infoPaciente(cola, posicion);
			std::cout << "Oprima una tecla para continuar...\n";
			std::cin.ignore();
			std::cin.get();
			break;
		case 6:
			int posElim;
			std::cout << "Ingrese la posicion del paciente a eliminar: ";
			std::cin >> posElim;
			eliminarPaciente(cola, posElim);
			std::cout << "Oprima una tecla para continuar...\n";
			std::cin.ignore();
			std::cin.get();
			break;
		case 7:
			std::cout << "Saldo total: " << saldo << std::endl;
			std::cout << "Oprima una tecla para continuar...\n";
			std::cin.ignore();
			std::cin.get();
			break;
		case 8:
			mostrarHistorial(historial);
			std::cout << "Oprima una tecla para continuar...\n";
			std::cin.ignore();
			std::cin.get();
			break;
		}
	} while (op != 9);
	
	return 0;
}
