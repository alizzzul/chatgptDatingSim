//comentarios sobre nomenclaturas usadas a lo largo del código 
//camelCase para variables y métodos, SCREAMING_SNAKE para constantes, Primera mayuscula para clases

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

void escribirLento(std::string texto, int ms_retraso = 25)
{
	for (char letra : texto)
	{
		std::cout << letra << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(ms_retraso))
	}
}

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

	//setter para la "tiendita"
	void reducirCantidad()
	{
		if (cantidadItem > 0) cantidadItem--;
	}
};
//clase padre para pasar por herencia
class EntidadSistema {
protected:
	std::string nombre;
	int saludActual;
	int danioAtaque;
	int nivel;
	int experiencia;

public:
	EntidadSistema(std::string param_nombre, int param_salud, int param_ataque)
	{
		nombre = param_nombre;
		saludActual = param_salud;
		saludMax = param_salud;
		danioAtaque = param_ataque;
		nivel = 1;
		experiencia = 0;
	}

	std::string getNombre() { return nombreVirus; }
	int getSalud() { return saludActual; }
	int getAtaque() { return danio; }
	int getNivel() { return nivel; }

	bool estaVivo() { return saludActual > 0; }

	void recibirDanio(int danio)
	{
		saludActual -= danio; //se resta daño hecho a la vida
		if (saludActual < 0) { saludActual = 0; } //para q no tenga vida negativa 
	}


class Virus : public EntidadSistema
	{
	public:
		Virus(std::string param_nombre, int param_salud, int param_ataque, param_xpQueSuelta) : EntidadSistema(param_nombre, param_salud, param_ataque)
		{
			experiencia = param_xpQueSuelta;
		}

		int getExperienciaQueSuelta() { return experiencia; }

		void atacar(Jugador& objetivo)
		{
			std::cout << "\n[!] " << nombre << " esta ejecutando un script malicioso..." << std::endl;
			objetivo.recibirDanio(danioAtaque);
			std::cout << "Tienes " << danioAtaque << "MB de archivos corruptos" << std::endl;
		}


class Jugador : public EntidadSistema
{
private:

	int oroJugador; // cambiar despues por otra "moneda"
	std::vector<Item> inventario;

	//constructor
public:
	Jugador(std::string param_nombre, int oroInicial) : EntidadSistema(param_nombre, 100, 20)
	{
		oroJugador = oroInicial;
	}

	//getters originales
	int getOro() { return oroJugador; }
	//comprar
	void gastarOro(int cantidad) { oroJugador -= cantidad; }
	void ganarOro(int cantidad) { oroJugador += cantidad; }

	void curar(int cantidad)
	{
		saludActual += cantidad; //se le añade la cantidad a curarse a la vida 
		if (saludActual > saludMax)
		{
			saludActual = saludMax; //para que no se pase de la cantidad max de vida 
		}
	}

	

	/*getters combate
	int getSalud() { return saludActual; }
	int getAtaque() { return danioAtaqueJugador; }

	//Revisa que jugador aún tenga vida 
	bool estaVivo() { return saludActual > 0; } */


	void mostrarInfoJugador() {
		std::cout << "Usuario:" << nombreJugador << "Monedas(?): $" << oroJugador << std::endl;
		std::cout << "SALUD/ESPACIO: " << saludActual << "/" << saludMax << std::endl;
		std::cout << "Fuerza d antiviru: " << danioAtaqueJugador << std::endl;

		std::cout << "--- INVENTARIO ---" << std::endl;

		if (inventario.empty())//Asegura por si el inventario está vacio
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
		std::cin >> opcion;  //opcion del jugador 

		if (opcion > 0 && opcion <= catalogo.size())
		{
			int indice = opcion - 1; //como la maquina lee el indice desde el cero se le resta para que sea la opcion elegida 

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

//Funcion de combate :3

void iniciarCombate(Jugador& jugador)
{
	Virus enemigo("Troyano_Celoso.exe", 50, 10, 25);

	std::cout << "\n=========================================" << std::endl;
	std::cout << "	LA BASE DE DATOS DE VIRUS HA SIDO ACTUALIZADA.\n" << std::endl;
	std::cout << "Se han encontrado datos corruptos en: " << enemigo.getNombre() << std::endl;
	std::cout << "=========================================\n" << std::endl;

	int accionCombate = 0;

	while (jugador.estaVivo() && enemigo.estaVivo())
	{

		//turno d jugador
		std::cout << "tu HP: " << jugador.getSalud() << "|| HP enemigo: " << enemigo.getSalud() << std::endl;
		std::cout << "1. Ejecutar Antivirus (Atacar)" << std::endl;
		std::cout << "2. Abrir directorio (usar item)" << std::endl; //por hacER!!!!!
		std::cout << "3. *Desconecta la pc* (Huir)" << std::endl;
		std::cout << "ELIGE UNA OPCION: " << std::endl;
		std::cin >> accionCombate;

		switch (accionCombate)
		{
		case 1:
			std::cout << "[La base d datos de virus ataca]" << std::endl;
			enemigo.recibirDanio(jugador.getAtaque());
			break;
		case 2:
			std::cout << "[Abriendo tus archivos]" << std::endl; //POR HACER AAAAAAAAAAAAAA
			break;
		case 3:
			std::cout << "[Reiniciando equipo. Cancelando todas las tareas en ejecucion]" << std::endl;
			return;
		default:
			std::cput << "[ERROR. intenta de nuevo]" << std::endl;
			break;
		}

		if (!enemigo.estaVivo())
		{
			std::cout << enemigo.getNombre() << " ha sido neutralizado de tu sistema." << std::endl;
			std::cout << "Recompensa: " << enemigo.getExperienciaQueSuelta() << " XP." << std::endl;
			break;
		}

		std::cout << "\n--- TURNO DEL VIRUS ---" << std::endl;
		enemigo.atacar(jugador);

		if (!jugador.estaVivo()) {
			std::cout << "\n ChatGPT ha invadido el corazón de tu maquina. nimodo." << std::endl;
			std::cout << "--- GAME OVER ---" << std::endl;
			break;
	}


}


int main()
{
	std::string nombrePersonalizable;
	int accion = 0;

	std::cout << "ingresa nombre de usuario: ";
	std::getline(std::cin, nombrePersonalizable);

	Jugador jugador(nombrePersonalizable, 1000); // monedas, ccambiarla por una variable para no hardcodear o no mi acuerdo como se decia pero si aja cambiala

	//se crean los items y sus cantidades desde main para que no se reinice cada que se llama a la tienda
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
			iniciarCombate(jugador);
			break;
		default:
			break;
		}
	} while (accion != 0);

	return 0;
}