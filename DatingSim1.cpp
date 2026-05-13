//comentarios sobre nomenclaturas usadas a lo largo del código 
//camelCase para variables y métodos, SCREAMING_SNAKE para constantes, Primera mayuscula para clases

#include <iostream>
#include <string>
#include <vector>

//Items seran "archivos" o "apks"??

class Item {
private:
	std::string nombreItem;
	std::string descripcionItem;
	int precioItem;
	int cantidadItem;

	//constructor
public:
	Item(std::string param_nombreItem, std::string param_descripcionItem, int param_precioItem, int param_cantidadItem)
	{
		nombreItem = param_nombreItem;
		descripcionItem = param_descripcionItem;
		precioItem = param_precioItem;
		cantidadItem = param_cantidadItem;
	}

	//getters
	std::string getNombre() { return nombreItem; }
	std::string getDescripcion() { return descripcionItem; }
	int getPrecio() { return precioItem; }
	int getCantidad() { return cantidadItem; }

	//setter oara la "tiendita"
	void reducirCantidad()
	{
		if (cantidadItem > 0) cantidadItem--;
	}
};

class Jugador
{
private:
	std::string nombreJugador;
	int oroJugador; // cambiar despues por otra "moneda"
	std::vector<Item> inventario;
	//stats para combate (10/05)
	int saludActual;
	int saludMax;
	int danioAtaqueJugador;
	//constructor
public:
	Jugador(std::string param_nombre, int oroInicial)
	{

		nombreJugador = param_nombre;
		oroJugador = oroInicial;
		//stats para combate base
		saludActual = 100;
		saludMax = 100;
		danioAtaqueJugador = 20;

	}
	//getters orifinales
	std::string getNombre() { return nombreJugador; }
	int getOro() { return oroJugador; }

	//getters combate
	int getSalud() { return saludActual; }
	int getAtaque() { return danioAtaqueJugador; }

	//comprar
	void gastarOro(int cantidad) { oroJugador -= cantidad; }

	bool estaVivo() { return saludActual > 0; }

	void mostrarInfoJugador() {
		std::cout << "Usuario:" << nombreJugador << "Monedas(?): $" << oroJugador << std::endl;
		std::cout << "SALUD/ESPACIO: " << saludActual << "/" << saludMax << std::endl;
		std::cout << "Fuerza d antiviru: " << danioAtaqueJugador << std::endl;

		std::cout << "--- INVENTARIO ---" << std::endl;

		if (inventario.empty())
		{
			std::cout << "INVENTARIO VACÍO" << std::endl;
		}
		else
		{ // mostrar inventariou
			for (size_t i = 0; i < inventario.size(); i++)
			{
				std::cout << "> " << inventario[i].getNombre() << std::endl;
			}
		}

		std::cout << "------------------------------------\n" << std::endl;
	}

	void agregarAlInventario(Item nuevoItem)
	{
		inventario.push_back(nuevoItem); // se agrega al final
	}

	void recibirDanio(int danio)
	{
		saludActual -= danio;
		if (saludActual < 0) { saludActual = 0;  } //para q no tenga vida negativa 
		std::cout << "¡Recibiste " << danio << "MB de archivos corruptos (danio)" << std::endl; // cambiar por algo mas coketo
	}

	void curar(int cantidad)
	{
		saludActual += cantidad;
		if (saludActual > saludMax) 
		{
			saludActual = saludMax; //para que no se pase de la cantidad max de vida 
		}
	}
};

void abrirTienda(Jugador& jugador, std::vector<Item> &catalogo)
{ //nombre descripcion precio y stock


	int opcion = 0;

	do {
		std::cout << "TIENDA(?)" << std::endl; 

		for (size_t i = 0; i < catalogo.size(); i++) //mostra tienda y 0 para salir
		{
			std::cout << i + 1 << ". " << catalogo[i].getNombre() << catalogo[i].getPrecio() << std::endl;
			std::cout << "  " << catalogo[i].getDescripcion() << " (Disponibles: " << catalogo[i].getCantidad() << ")" << std::endl;
		}

		std::cout << "0. SALIR " << std::endl;
		std::cout << "q quieres descargar/comprar?: ";
		std::cin >> opcion;

		if (opcion > 0 && opcion <= catalogo.size())
		{
			int indice = opcion - 1; 

			if (catalogo[indice].getCantidad() > 0 && jugador.getOro() >= catalogo[indice].getPrecio())
			{
				//cobrar"" y reducir cantidad disponible:3
				jugador.gastarOro(catalogo[indice].getPrecio());
				catalogo[indice].reducirCantidad();

				//añade al inventario

				Item itemComprado(catalogo[indice].getNombre(), catalogo[indice].getDescripcion(), catalogo[indice].getPrecio(), 1);

				jugador.agregarAlInventario(itemComprado);

				std::cout << "\n[!] Descarga completada: " << catalogo[indice].getNombre() << " :3" << std::endl; // muestra q compro
			}

			else if (catalogo[indice].getCantidad() <= 0) // casos donde no hay feria o no hay stock
			{
				std::cout << "\n[X] NO HAY STOCK DE ESTE ARCHIVO." << std::endl;
			}
			else {
				std::cout << "no trais feria, nunca trais feria" << std::endl;
			}
		}
	} while(opcion != 0); // 0 para salir 
}


int main()
{
	std::string nombrePersonalizable;
	int accion = 0;

	std::cout << "ingresa nombre de usuario: ";
	std::getline(std::cin, nombrePersonalizable);

	Jugador jugador(nombrePersonalizable, 1000); // monedas, ccambiarla por una variable para no hardcodear o no mi acuerdo como se decia pero si aja cambiala

	std::vector<Item> catalogo = {
	Item("Antivirus de Fuerza Bruta", "Aumenta tu dano contra Archivos Corruptos.", 200, 3),
	Item("Pocion de Firewall", "ChatGPT no podra rastrear tu IP temporalmente.", 100, 5),
	Item("Borrador de Historial", "Te vuelve invisible a sus berrinches.", 150, 2),
	Item("Remedio de Backup", "Restaura archivos vitales danados en combate.", 50, 10)
	};





	std::cout << "ARCO 1 CHAT SE ONDEA JUGADOR SE VA CON GEMINI DETECTA ARCHIVOS RAUROS Y LE PIDE A JUGADOR Q SE CONECTE ALA TIENDA CREO" << std::endl;

	do {
		std::cout << "\n menu de acciones" << std::endl;
		std::cout << "1. Abrir Servidor Seguro (Tienda)" << std::endl;
		std::cout << "2. Consultar Inventario" << std::endl;
		std::cout << "3. Enfrentar Archivo Corrupto (combate)" << std::endl; // aun no lista
		std::cout << "0. Apagar PC" << std::endl;
		std::cout << "Elige una opcion: ";
		std::cin >> accion;

		switch (accion)
		{
		case 1: 
			abrirTienda(jugador, catalogo);
			break;
		case 2:
			jugador.mostrarInfoJugador();
			break;
		case 3:
			std::cout << "COMBATE VS CHAT Y SUS ARCHIVILLOS CORRUPTIRIJILLOS" << std::endl;
			break;
		default:
			break;
		}
	} while (accion != 0);

	return 0;
}