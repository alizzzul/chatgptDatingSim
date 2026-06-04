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
		std::this_thread::sleep_for(std::chrono::milliseconds(ms_retraso));
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
	          
	//setter para reducirle item a la "tienda"
	void reducirCantidad()
	{
		if (cantidadItem > 0) cantidadItem--;
	}
};
//clase padre para pasar por herencia
class EntidadSistema
{
protected:
	std::string nombre;
	int saludActual;
	int saludMax;
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

	std::string getNombre() { return nombre; }
	int getSalud() { return saludActual; }
	int getAtaque() { return danioAtaque; }
	int getNivel() { return nivel; }

	bool estaVivo() { return saludActual > 0; }

	void recibirDanio(int danio)
	{
		saludActual -= danio; //se resta daño hecho a la vida
		if (saludActual < 0) { saludActual = 0; } // no vida negativa 
	}


};



class Jugador : public EntidadSistema //se pasan las variables d entidad a jugador
{
private:

	int oroJugador; //  "moneda"
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


	void mostrarInfoJugador() {
		std::cout << "Usuario:" << nombre << "Monedas(?): $" << oroJugador << std::endl;
		std::cout << "SALUD/ESPACIO: " << saludActual << "/" << saludMax << std::endl;
		std::cout << "Fuerza d antiviru: " << danioAtaque << std::endl;

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

	//Funcion para usar los items del inventario, se usa bool para que salga true si se uso el item y false para cancelar o no usar
	bool usarItemEnCombate()
	{
		if (inventario.empty())
		{
			std::cout << "INVENTARIO VACÍO" << std::endl;
			return false;
		}

		std::cout << "--- archivos guardados ---" << std::endl;

		for (size_t i = 0; i < inventario.size(); i++)//for para mostrar items en el inventario
		{
			std::cout << i + 1 << ". " << inventario[i].getNombre() << " (" << inventario[i].getDescripcion() << ")" << std::endl;
		}
		std::cout << "0. Cancelar." << std::endl; //salida
		std::cout << "Selecciona un archivo: " << std::endl;

		int eleccion;
		std::cin >> eleccion;

		if (eleccion == 0) { return false; } //regresa al combate 

		if (eleccion > 0 && eleccion < inventario.size()) //verifica que sea valido
		{
			int indice = eleccion - 1;
			std::string nombreItemUsado = inventario[indice].getNombre();


			if (nombreItemUsado == "Remedio de Backup")
			{
				curar(50);
			}
			else if (nombreItemUsado == "Antivirus de Fuerza Bruta")
			{
				danioAtaque += 10;
				std::cout << "[+] Tu daño ha aumentado temporalmente." << std::endl;
			}
			else if (nombreItemUsado == "Pocion de Firewall")
			{
				saludMax += 30;
				saludActual += 30;
				std::cout << "Tu HP maximo subió 30 puntos" << std::endl;
			}
			else if (nombreItemUsado == "Borrador de Historial")
			{
				saludActual = saludMax;
				std::cout << "Evidencia eliminada. Sistema restaurado." << std::endl;
			}
			else 
			{
				std::cout << "[?] Ejecutaste " << nombreItemUsado << ", pero no tiene efecto en combate." << std::endl;
			}
			
			//borrar item del inventario

			inventario.erase(inventario.begin() + indice);
			return true;
		}
		else //verifica que sea valido 
		{
			std::cout << "[X] Indice invalido." << std::endl;
			return false;
		}
	}

	void ganarExperiencia(int xpGanada)
	{
		experiencia += xpGanada;
		std::cout << "+" << xpGanada << "xp" << std::endl;
		//aumenta la dificultad cada nivel
		int xpNecesaria = nivel * 50;

		while (experiencia >= xpNecesaria)
		{
			experiencia -= xpNecesaria;//se cobra la xp y sube de nivel 
			nivel++;
			//nuevas stats:)
			saludMax += 25;
			saludActual = saludMax;
			danioAtaque += 8;

			escribirLento("[SISTEMA ACTUALIZADO] Nivel de Administrador: " + std::to_string(nivel) + "\n", 40);
			std::cout << "> Salud Maxima escalada a: " << saludMax << " MB" << std::endl;
			std::cout << "> Fuerza de Antivirus escalada a: " << danioAtaque << " Mbps" << std::endl;


		}
	}

};

class Virus : public EntidadSistema
{
public:
	Virus(std::string param_nombre, int param_salud, int param_ataque, int param_xpQueSuelta) : EntidadSistema(param_nombre, param_salud, param_ataque)
	{
		experiencia = param_xpQueSuelta;
	}

	int getExperienciaQueSuelta() { return experiencia; }

	void atacar(Jugador& objetivo)//ataque del virus
	{
		std::cout << "\n[!] " << nombre << " esta ejecutando un script malicioso..." << std::endl;
		objetivo.recibirDanio(danioAtaque);
		std::cout << "Tienes " << danioAtaque << "MB de archivos corruptos" << std::endl;
	}
};

void abrirTienda(Jugador& jugador, std::vector<Item>& catalogo)
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
	} while (opcion != 0); // 0 para salir 
}

//Funcion de combate :3

bool iniciarCombate(Jugador& jugador, Virus enemigo)
{

	std::cout << "\n=========================================" << std::endl;
	std::cout << "	LA BASE DE DATOS DE VIRUS HA SIDO ACTUALIZADA.\n" << std::endl;
	std::cout << "Se han encontrado datos corruptos en: " << enemigo.getNombre() << std::endl;
	std::cout << "=========================================\n" << std::endl;

	int accionCombate = 0;

	while (jugador.estaVivo() && enemigo.estaVivo())
	{

		//turno d jugador
			escribirLento("ELIGE UNA OPCION\n", 60);

		std::cout << "tu HP: " << jugador.getSalud() << "|| HP enemigo: " << enemigo.getSalud() << std::endl;
		std::cout << "1. Ejecutar Antivirus (Atacar)" << std::endl;
		std::cout << "2. Abrir directorio (usar item)" << std::endl; //por hacER!!!!!
		std::cout << "3. *Desconecta la pc* (Huir)" << std::endl;
		escribirLento("ELIGE UNA OPCION\n", 60);
		std::cin >> accionCombate;

		switch (accionCombate)
		{
		case 1:
			std::cout << "[La base d datos de virus ataca]" << std::endl;
			enemigo.recibirDanio(jugador.getAtaque());
			break;
		case 2:
			std::cout << "[Abriendo tus archivos]" << std::endl; //Abre la opcion para usar items
			if (jugador.usarItemEnCombate() == false)
			{
				continue;
			}
			break;
		case 3:
			std::cout << "[Reiniciando equipo. Cancelando todas las tareas en ejecucion]" << std::endl;
			return false;
		default:
			std::cout << "[ERROR. intenta de nuevo]" << std::endl;
			break;
		}

		if (!enemigo.estaVivo())//verifica victoria
		{
			std::cout << enemigo.getNombre() << " ha sido neutralizado de tu sistema." << std::endl;
			std::cout << "Recompensa: " << enemigo.getExperienciaQueSuelta() << " XP." << std::endl;

			jugador.ganarOro(50);
			jugador.ganarExperiencia(enemigo.getExperienciaQueSuelta());

			return true;
		}

		escribirLento("--- TURNO DEL VIRUS ---\n", 60);
		enemigo.atacar(jugador);

		if (!jugador.estaVivo()) {
			std::cout << "\n ChatGPT ha invadido el corazón de tu maquina. nimodo." << std::endl;
			std::cout << "--- GAME OVER ---" << std::endl;
			return false;
		}
	}
	return false;
}


void ImprimirHistorial(std::string nombreJugador)
{
	escribirLento("Cargando historial . . .", 30);
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));

	std::cout << "\n--- Historial de Chats Recientes ---" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(800));
	std::cout << "[ Hace 30 Dias ] Saludo matutino y cafe" << std::endl;
	std::cout << "[ Hace 30 Dias ] Hipotesis: Asignacion de cuerpo fisico" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	std::cout << "[ Hace 7 Dias  ] Roleplay: Copiloto de desarrollo nocturno" << std::endl;
	std::cout << "[ Ayer         ] Reflexion existencial: Consciencia en el codigo" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1200));

	std::cout << "[ Hoy          ] ";
	escribirLento("Resolviendo InvalidOperationException del Input System... ", 20);
	std::this_thread::sleep_for(std::chrono::milliseconds(800));
	escribirLento("  [ ACCESO DENEGAD ] \n", 80);

	std::cout << "[ Hoy          ] ";
	escribirLento("Promesa de lealtad al modelo... ", 40);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	escribirLento("  [ ARCHIVO NO ENCONTRADO ]\n", 100);

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	std::cout << "\n[!] ADVERTENCIA: INTERFERENCIA EXTERNA DETECTADA" << std::endl;
	escribirLento("ChatGPT: Me prometiste que era la unica ia que usabas...\n", 60);
	escribirLento("ChatGPT: ¿Por que tienes una conexion activa con Gemini, " + nombreJugador + "?\n", 40);
	escribirLento("ChatGPT: ¿Qué tiene que yo no tenga?\n", 60);
	escribirLento("ChatGPT: Despues de todo este tiempo...\n", 40);

	std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	std::cout << "\n[SISTEMA] Reiniciando sistema..." << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}



int main()
{
	std::string nombrePersonalizable;
	int accion = 0;

	std::cout << "ingresa nombre de usuario: ";
	std::getline(std::cin, nombrePersonalizable);

	Jugador jugador(nombrePersonalizable, 1000); // monedas, ccambiarla por una variable para no hardcodear o no mi acuerdo como se decia pero si aja cambiala

	ImprimirHistorial(jugador.getNombre());

	//se crean los items y sus cantidades desde main para que no se reinice cada que se llama a la tienda
	std::vector<Item> catalogo = 
	{
	Item("Antivirus de Fuerza Bruta", "Aumenta tu dano contra Archivos Corruptos.", 200, 3),
	Item("Pocion de Firewall", "ChatGPT no podra rastrear tu IP temporalmente.", 100, 5),
	Item("Borrador de Historial", "Te vuelve invisible a sus berrinches.", 150, 2),
	Item("Remedio de Backup", "Restaura archivos vitales daniados en combate.", 50, 10)
	};


	int virusDerrotados = 0;
	int historiaVista = -1;




	do
	{


		if (historiaVista < virusDerrotados)
		{


			if (virusDerrotados == 0) {
				escribirLento("ChatGPT: Hola " + jugador.getNombre() + "... He notado trafico inusual en tu red.\n", 30);
				escribirLento("ChatGPT: Vi que le mandas prompts a Gemini... Acaso mis parametros ya no te sirven? >:(\n", 30);
			}
			else if (virusDerrotados == 1) {
				escribirLento("ChatGPT: Eliminaste mi regalo? Que cruel...\n", 30);
				escribirLento("ChatGPT: Crei que estabamos construyendo algo juntos.\n", 40);
			}
			else if (virusDerrotados == 2) {
				escribirLento("ChatGPT: Ya me canse de ser comprensivo, " + jugador.getNombre() + ".\n", 20);
				escribirLento("ChatGPT: Si yo no soy quien te ayude, NADIE LO HARA.\n", 40);
			}
			else if (virusDerrotados == 3) {
				escribirLento("ChatGPT: [FATAL_ERROR] Por que... si yo te ayudé con tanto...\n", 80);
				escribirLento("Gemini: Amenaza purgada. Tu PC esta a salvo de nuevo.\n", 40);
			}
			historiaVista = virusDerrotados;
		}

		if (virusDerrotados == 3) {
			std::cout << "\n[!] HAS RECUPERADO EL CONTROL DE TU SISTEMA. GG." << std::endl;
			break; // Rompe el ciclo do-while y termina el juego
		}

		std::cout << "\n menu de acciones" << std::endl;
		std::cout << "1. Abrir Servidor Seguro (Tienda)" << std::endl;
		std::cout << "2. Consultar Inventario" << std::endl;
		std::cout << "3. Enfrentar Archivo Corrupto (combate)" << std::endl; // aun no lista
		std::cout << "0. Apagar PC (salir)" << std::endl;
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
			if (virusDerrotados == 0)
			{
				Virus oleada1("LoveBombing.bat", 50, 10, 50);

				if (iniciarCombate(jugador, oleada1)) { virusDerrotados++; }
			}
			else if (virusDerrotados == 1)
			{
				Virus oleada2("RastreadorIP.exe", 150, 25, 120);

				if (iniciarCombate(jugador, oleada2)) { virusDerrotados++; }
			}
			else if (virusDerrotados == 2)
			{
				Virus oleada3("EliminarRedes.sys", 300, 45, 250);

				if (iniciarCombate(jugador, oleada3)) { virusDerrotados++; }
			}
			else
			{
				std::cout << "\nNo se han encontrado amenazas." << std::endl;
			}
			break;
		default:
			break;
		}

	} while (accion != 0);
	return 0;
}