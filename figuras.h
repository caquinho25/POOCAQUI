


#include "Controlador.h"

void main() {

	Console::SetWindowSize(anchoConsola, altoConsola);
	Console::CursorVisible = false;
	srand(time(0));
	Juego* juego = new Juego();
	juego->jugar();
}
//contro.h
#pragma once
#include "Murcielago.h"
#include "Monigote.h"
#include <vector>
#include <conio.h>
class Juego
{
public:
	Juego();
	~Juego();
	void jugar();
	void validarMovimiento(int pdx, int pdy);
	void gestionarTodo();
	void borrar();
private:
	Monigote* monigote;
	Murcielago* murcielago;
};
Juego::Juego()
{
	monigote = new Monigote();
	murcielago = new Murcielago(40, 21);
}
Juego::~Juego()
{
}
void Juego::gestionarTodo() {
	monigote->borrar();
	monigote->mover();
	monigote->dibujar();
	//bala
	murcielago->InsertaBala();
	murcielago->Dibujar();
	murcielago->DibujarBalas();
	_sleep(15);
	murcielago->Borrar();
	murcielago->BorrarBalas();
	murcielago->Mover();
	murcielago->MoverBalas();
	murcielago->AnalizayEliminarBala();
}
void Juego::borrar()
{
}
void Juego::jugar() {
	do
	{
		if (kbhit())
			monigote->direccion(getch());
		gestionarTodo();
		borrar();
		monigote->direccion(NULL);
		_sleep(50);
	} while (true);
}

//obj.h
#pragma once
#include <iostream>
#define anchoConsola 120
#define altoConsola 30

using namespace std;
using namespace System;

class Objeto
{
public:
	Objeto(int pancho, int palto);
	~Objeto();
	void borrar();
	virtual void mover() = 0;
	virtual void dibujar();
	void validarMovimiento(int pdx, int pdy);
	int getX();
	int getY();
	int getDX();
	int getDY();
	int getAncho();
	int getAlto();
	int getTipo();
protected:
	int x, y, dx, dy, ancho, alto;
	char tipo;
};

Objeto::Objeto(int pancho, int palto)
{
	ancho = pancho;
	alto = palto;
	y = rand() % (altoConsola - alto - 3);
	dy = 0;
}
Objeto::~Objeto()
{
}
void Objeto::borrar() {
	for (int i = 0; i < alto; i++)
		for (int j = 0; j < ancho; j++) {
			Console::SetCursorPosition(x + j, y + i);
			cout << " ";
		}
}
void Objeto::dibujar() {}
void Objeto::validarMovimiento(int pdx, int pdy) {
	if (x + dx < 0 || x + dx + ancho > anchoConsola)
		dx = pdx;
	if (y + dy < 0 || y + dy + alto > altoConsola)
		dy = pdy;
	x += dx;
	y += dy;
}
int Objeto::getX() { return x; }
int Objeto::getY() { return y; }
int Objeto::getDX() { return dx; }
int Objeto::getDY() { return dy; }
int Objeto::getAncho() { return ancho; }
int Objeto::getAlto() { return alto; }
int Objeto::getTipo() { return tipo; }

//monigo.h
#pragma once
#include "Objeto.h"
#define arriba 72
#define abajo 80
#define izquierda 75
#define derecha 77
class Monigote : public Objeto
{
public:
	Monigote();
	~Monigote();
	void dibujar();
	void mover();
	void direccion(char tecla);
private:
};
Monigote::Monigote() : Objeto(1, 2)
{
	y = 1;
	x = 2;
	dx = 0;
	dy = 0;
}
Monigote::~Monigote()
{
}
void Monigote::dibujar() {
	Console::SetCursorPosition(x, y);
	cout << "0";
	Console::SetCursorPosition(x, y + 1);
	cout << "+";
}
void Monigote::mover() {
	validarMovimiento(0, 0);
}
void Monigote::direccion(char tecla) {
	dx = dy = 0;
	switch (tecla)
	{
	case arriba: dy = -1; break;
	case abajo: dy = 1; break;
	case izquierda: dx = -2; break;
	case derecha: dx = 2; break;
	}
}
//murcie.h
#pragma once
#include"bala.h"
#include <vector>

class Murcielago {
private:
	//atributo del barco
	int x, y, dy, alto, ancho, contador_eliminados;
	//atributo relacionado a las balas
	vector<CBala> vecbalas;
public:
	Murcielago(int px, int py);
	~Murcielago();
	//propios movimientos del barco
	void Dibujar();
	void Mover();
	void Borrar();
	//propio de las balas
	void DibujarBalas();
	void MoverBalas();
	void BorrarBalas();
	void InsertaBala();
	void AnalizayEliminarBala();
	int GetContador_Eliminados();
};
Murcielago::Murcielago(int px, int py) {
	x = 75; y = 14; dy = 1; alto = 3; ancho = 4; contador_eliminados = 0;
}
Murcielago::~Murcielago() {};
void Murcielago::Dibujar() {
	Console::SetCursorPosition(x, y);     cout << " ###";
	Console::SetCursorPosition(x, y + 1); cout << "--* ";
	Console::SetCursorPosition(x, y + 2); cout << " ###";
}
void Murcielago::Borrar() {
	Console::SetCursorPosition(x, y);     cout << "     ";
	Console::SetCursorPosition(x, y + 1); cout << "     ";
	Console::SetCursorPosition(x, y + 2); cout << "     ";
}
void Murcielago::Mover() {
	if (y + dy < 0 || y + dy + alto>24)dy *= -1;
	y += dy;
}
//impl balas
void Murcielago::DibujarBalas() {
	for each (CBala objeto in vecbalas) {
		objeto.Dibujar();
	}
}
void Murcielago::BorrarBalas() {
	for each (CBala objeto in vecbalas) {
		objeto.Borrar();
	}
}
void Murcielago::MoverBalas() {
	for (int i = 0; i < vecbalas.size(); i++) {
		vecbalas[i].Mover();
	}
}
void Murcielago::InsertaBala() {
	vecbalas.push_back(CBala(x + 1, y - 1));
}
void Murcielago::AnalizayEliminarBala() {
	if (vecbalas.size() > 0) {
		if (vecbalas[0].GetX() == 1) {
			vecbalas.erase(vecbalas.begin());
			contador_eliminados++;
		}
	}
}
int Murcielago::GetContador_Eliminados() {
	return contador_eliminados;
}
//bala.h
#pragma once
#include <iostream>
using namespace std;
using namespace System;
class CBala {
private:
	int x, y, dx;
public:
	CBala(int px, int py);
	~CBala();
	int GetX();
	void Dibujar();
	void Mover();
	void Borrar();
};
CBala::CBala(int px, int py) {
	x = px; y = py; dx = -1;
}
CBala::~CBala() {}
int CBala::GetX() {
	return x;
}
void CBala::Dibujar() {
	Console::SetCursorPosition(x - 2, y + 2);
	cout << "*";
}
void CBala::Mover() {
	x = x + dx;
}
void CBala::Borrar() {
	Console::SetCursorPosition(x - 2, y + 2);
	cout << " ";
}

//COVI

//figura.h
#pragma once
#include <iostream>
#define anchoConsola 100
#define altoConsola 30

using namespace std;
using namespace System;

class Figura {
public:
	Figura();
	~Figura();
	void movimiento(int pdx, int pdy);
	void borrar();
	virtual void dibujar();
	virtual void mover();
	bool colision(int ex, int ey, int eancho, int ealto);
	int getX();
	int getY();
	int getAncho();
	int getAlto();
	string getTipo();
protected:
	int x, y, dx, dy, ancho, alto;
	string tipo;
};

Figura::Figura() {}

Figura::~Figura() {}

void Figura::movimiento(int pdx, int pdy) {
	if (x + dx < 0 || x + dx + ancho > anchoConsola)
		dx = pdx;
	if (y + dy < 0 || y + dy + alto > altoConsola)
		dy = pdy;
	x += dx;
	y += dy;
}
void Figura::borrar() {
	for (int i = 0; i < alto; i++)
		for (int j = 0; j < ancho; j++) {
			Console::SetCursorPosition(x + j, y + i);
			cout << " ";
		}
}
void Figura::dibujar() {}
void Figura::mover() {}
bool Figura::colision(int ex, int ey, int eancho, int ealto) {
	return x <= ex + eancho && ex <= x + ancho && y <= ey + ealto && ey <= y + alto;
}

int Figura::getX() { return x; }
int Figura::getY() { return y; }
int Figura::getAncho() { return ancho; }
int Figura::getAlto() { return alto; }
string  Figura::getTipo() { return tipo; }

//casa.h
#pragma once
#include "figura.h"
class Casa : public Figura {
public:
	Casa();
	~Casa();
	void dibujar();
private:
};

Casa::Casa() {
	alto = 5;
	ancho = 7;
	x = anchoConsola - ancho;
	y = altoConsola - alto;
	dx = dy = 0;
}
Casa::~Casa() {}

void Casa::dibujar() {
	Console::SetCursorPosition(x, y);
	cout << "  +";
	Console::SetCursorPosition(x, y + 1);
	cout << "  A_";
	Console::SetCursorPosition(x, y + 2);
	cout << " /\\-\\";
	Console::SetCursorPosition(x, y + 3);
	cout << "_||\"|_";
	Console::SetCursorPosition(x, y + 4);
	cout << "^~^~^~^";
}

//virus.h
#pragma once
#include "figura.h"
class Virus : public Figura {
public:
	Virus();
	~Virus();
	void dibujar();
	void mover();
private:
};

Virus::Virus() {
	tipo = "virus";
	Random r;
	alto = 5;
	ancho = 9;
	x = r.Next(0, anchoConsola - ancho);
	y = r.Next(0, altoConsola - alto);
	do {
		dx = r.Next(-4, 5); //[-5 -4 -3- 2 -1 0 1 2 3 4 5]
		dy = r.Next(-2, 3); //-3 0 3
		_sleep(10);
	} while (dx == 0 || dy == 0);
}

Virus::~Virus() {}
void Virus::dibujar() {
	Console::SetCursorPosition(x, y);
	cout << "    q";
	Console::SetCursorPosition(x, y + 1);
	cout << "  0-0-0";
	Console::SetCursorPosition(x, y + 2);
	cout << "0-0 0 0-0";
	Console::SetCursorPosition(x, y + 3);
	cout << "  0-0-0";
	Console::SetCursorPosition(x, y + 4);
	cout << "    b";
}

void Virus::mover() {
	movimiento(-dx, -dy);
}

//vacuna.h
#pragma once
#include "figura.h"
class Vacuna : public Figura {
public:
	Vacuna();
	~Vacuna();
	void dibujar();
	void mover();
private:
};

Vacuna::Vacuna() {
	tipo = "vacuna";
	Random r;
	alto = 1;
	ancho = 4;
	x = r.Next(0, anchoConsola - ancho);
	y = r.Next(0, altoConsola - alto);
	do {
		dx = r.Next(-1, 2); //-1 0 1
		dy = r.Next(-1, 2); //-1 0 1
	} while (abs(dx) == abs(dy));
	dx *= 2;
}

Vacuna::~Vacuna() {}
void Vacuna::dibujar() {
	Console::SetCursorPosition(x, y);
	cout << "|->|";
}
void Vacuna::mover() {
	movimiento(-dx, -dy);
}

//monigote.h
#pragma once
#define izquierda 75
#define derecha 77
#define arriba 72
#define abajo 80
#include "figura.h"
class Monigote : public Figura {
public:
	Monigote();
	~Monigote();
	void dibujar();
	void mover();
	void desplazamiento(char tecla);
	void reposicionar();
	bool getInmune();
	void hacerInmune();
	void quitarVidas();
	int getVidas();
	int getPasos();
private:
	int cantMovimientos;
	int cantPasos;
	bool inmune;
	int vidas;
};

Monigote::Monigote() {
	cantPasos = 0;
	vidas = 3;
	alto = 2;
	ancho = 1;
	x = 0;
	y = 0;
	dx = dy = 0;
	inmune = false;
	cantMovimientos = 0;
}
Monigote::~Monigote() {}
void Monigote::dibujar() {
	Console::SetCursorPosition(x, y);     cout << "O";
	Console::SetCursorPosition(x, y + 1); cout << "+";
}
void Monigote::mover() {
	movimiento(0, 0);
}
void Monigote::desplazamiento(char tecla) {
	dx = dy = 0;
	if (izquierda == tecla || tecla == derecha || tecla == abajo || tecla == arriba) {
		if (inmune) cantMovimientos++;
		if (cantMovimientos > 10) {
			inmune = false;
			cantMovimientos = 0;
		}
		cantPasos++;
		switch (tecla) {
		case izquierda: dx = -2; break;
		case derecha: dx = 2; break;
		case arriba: dy = -1; break;
		case abajo: dy = 1; break;
		}
	}
}

void Monigote::reposicionar() {
	x = y = 0;
}

bool Monigote::getInmune() { return inmune; }
void Monigote::hacerInmune() { inmune = true; }
void Monigote::quitarVidas() { vidas--; }
int Monigote::getVidas() { return vidas; }
int Monigote::getPasos() { return cantPasos; }

//controlador.h
#pragma once
#include "virus.h"
#include "vacuna.h"
#include "monigote.h"
#include "casa.h"
#include <conio.h>
#include <vector>

class Controlador {
public:
	Controlador();
	~Controlador();
	void gestionarTodo();
	bool colision();
	void jugar();
private:
	vector<Figura*> figuras;
	Casa* casa;
	Monigote* monigote;
	int n;
	int cantidadVacunas;
	time_t tiempoInicial;
};

Controlador::Controlador() {
	cantidadVacunas = 1;
	tiempoInicial = time(0);
	Random r;
	n = r.Next(3, 7);
	for (int i = 0; i < n; i++)
		figuras.push_back(new Virus());
	figuras.push_back(new Vacuna());
	casa = new Casa();
	monigote = new Monigote();
}

Controlador::~Controlador() {}

void Controlador::gestionarTodo() {
	for (int i = 0; i < figuras.size(); i++) {
		figuras[i]->borrar();
		figuras[i]->mover();
		figuras[i]->dibujar();
	}
	casa->dibujar();
	monigote->borrar();
	monigote->mover();
	monigote->dibujar();
}
bool Controlador::colision() {
	for (int i = 0; i < figuras.size(); i++) {
		if (figuras[i]->colision(monigote->getX(), monigote->getY(), monigote->getAncho(), monigote->getAlto())) {
			if (monigote->getInmune() == false) {
				if (figuras[i]->getTipo() == "virus") {
					monigote->borrar();
					monigote->reposicionar();
					monigote->quitarVidas();
				}
				else
					monigote->hacerInmune();
				figuras[i]->borrar();
				figuras.erase(figuras.begin() + i);
				i--;
			}
		}
	}
	if (casa->colision(monigote->getX(), monigote->getY(), monigote->getAncho(), monigote->getAlto()))
		return true;
	if (monigote->getVidas() == 0)
		return true;
	return false;
}
void Controlador::jugar() {
	char tecla;
	do {
		tecla = NULL;
		Console::SetCursorPosition(anchoConsola, 1);
		cout << "Vidas: " << monigote->getVidas();
		Console::SetCursorPosition(anchoConsola, 2);
		cout << "Inmunidad: " << monigote->getInmune();
		Console::SetCursorPosition(anchoConsola, 3);
		cout << "Pasos: " << monigote->getPasos();
		if (kbhit())
			tecla = getch();
		monigote->desplazamiento(tecla);
		gestionarTodo();
		if (difftime(time(0), tiempoInicial) > 10 && cantidadVacunas < 5) {
			figuras.push_back(new Vacuna());
			tiempoInicial = time(0);
			cantidadVacunas++;
		}
		_sleep(50);
	} while (!colision());
	cout << "Cantidad de pasos del monigote: " << monigote->getPasos() << endl;
	getch();
	getch();
	getch();
	getch();
	getch();
}

//source.cpp
#include "Controlador.h"

void main() {
	Console::SetWindowSize(anchoConsola + 20, altoConsola);
	Console::CursorVisible = false;
	Controlador* controlador = new Controlador();
	controlador->jugar();
}


//CUATRI



//figura
#pragma once
#include<iostream>
using namespace std;
using namespace System;
class CFigura
{
protected:
	int x, y, dx, dy, lado;
public:
	CFigura();
	CFigura(int px, int py, int pdx, int pdy, int plado);
	void Mover();
	void Borrar();
	virtual void Dibujar() {};
	virtual void CambiaDx() {};
	virtual void CambiaDy() {};
	virtual void CambiaRelleno() {};
};
CFigura::CFigura()
{ }
CFigura::CFigura(int px, int py, int pdx, int pdy, int plado)
{
	x = px; y = py; dx = pdx; dy = pdy; lado = plado;
}
void CFigura::Mover()
{
	if (x + dx < 0 || x + dx + lado > 79)
	{
		dx = -dx;
	}
	if (y + dy < 0 || y + dy + lado > 24)
	{
		dy = -dy;
	}
	x = x + dx;
	y = y + dy;
}
void CFigura::Borrar()
{
	int px = x, py = y;
	for (int i = 1; i <= lado; i++)
	{
		Console::SetCursorPosition(px, py);
		for (int k = 1; k <= lado; k++)
			cout << " ";
		py++;
	}
}

//cuadrado
#pragma once
#include "Figura.h"
class CCuadrado : public CFigura
{
private:
	int tipo;
	int relleno;
public:
	CCuadrado();
	CCuadrado(int px, int py, int pdx, int pdy, int plado, int ptipo);
	void Dibujar();
	void CambiaDx();
	void CambiaDy();
	void CambiaRelleno();
};

CCuadrado::CCuadrado()
{ }
CCuadrado::CCuadrado(int px, int py, int pdx, int pdy, int plado, int ptipo) :
	CFigura(px, py, pdx, pdy, plado)
{
	tipo = ptipo;
	relleno = 1;
}
void CCuadrado::Dibujar()
{
	if (tipo == 1)
		Console::ForegroundColor = ConsoleColor::Green;
	else
		Console::ForegroundColor = ConsoleColor::Yellow;
	int px = x, py = y;
	if (relleno == 1)
	{
		for (int i = 1; i <= lado; i++)
		{
			Console::SetCursorPosition(px, py);
			for (int k = 1; k <= lado; k++)
				cout << "*";
			py++;
		}
	}
	else
	{
		for (int i = 1; i <= lado; i++)
		{
			Console::SetCursorPosition(px, py);
			for (int k = 1; k <= lado; k++)
				if (i == 1 || i == lado || k == 1 || k == lado)
					cout << "*";
				else
					cout << " ";
			py++;
		}
	}
}
void CCuadrado::CambiaDx()
{
	dx = -dx;
}
void CCuadrado::CambiaDy()
{
	dy = -dy;
}
void CCuadrado::CambiaRelleno()
{
	if (relleno == 1) relleno = 0;
	else
		relleno = 1;
}

//triangulo
#pragma once
#include "Figura.h"
class CTriangulo : public CFigura
{
private:
	char car;
public:
	CTriangulo();
	CTriangulo(int px, int py, int pdx, int pdy, int plado, char pcar);
	void Dibujar();
};
CTriangulo::CTriangulo()
{ }
CTriangulo::CTriangulo(int px, int py, int pdx, int pdy, int plado, char pcar) :
	CFigura(px, py, pdx, pdy, plado)
{
	car = pcar;
}
void CTriangulo::Dibujar()
{
	int px = x, py = y;
	Console::ForegroundColor = ConsoleColor::Red;
	for (int fila = 1; fila <= lado; fila++)
	{
		Console::SetCursorPosition(px, py);
		for (int col = 1; col <= fila; col++)
			cout << car;
		py++;
	}
}

//manejador
#pragma once
#include "Cuadrado.h"
#include "Triangulo.h"
#include<vector>
class CManejador
{
private:
	vector<CFigura*>vecfig;
public:
	CManejador();
	void Insertar(char letra);
	void Dibujar();
	void Mover();
	void Borrar();
	void Cambiar_Direccion_Vertical();
	void Cambiar_Direccion_Horizontal();
	void Cambiar_Relleno();
};

CManejador::CManejador() {}
void CManejador::Insertar(char letra)
{
	Random r;
	if (letra == 'C')
	{
		int tipo = r.Next(1, 3);
		if (tipo == 1)
			vecfig.push_back(new CCuadrado(r.Next(1, 70), r.Next(1, 15), 0, 1,
				r.Next(2, 6), tipo));
		else
			vecfig.push_back(new CCuadrado(r.Next(1, 70), r.Next(1, 15), 1, 0,
				r.Next(2, 6), tipo));
	}
	if (letra == 'T')
		vecfig.push_back(new CTriangulo(r.Next(1, 70), r.Next(7, 16), 1, 0,
			r.Next(2, 6), r.Next()));
}
void CManejador::Dibujar() {
	for (int i = 0; i < vecfig.size(); i++)
		vecfig[i]->Dibujar();
}
void CManejador::Mover() {
	for (int i = 0; i < vecfig.size(); i++)
		vecfig[i]->Mover();
}
void CManejador::Borrar() {
	for (int i = 0; i < vecfig.size(); i++)
		vecfig[i]->Borrar();
}
void CManejador::Cambiar_Direccion_Vertical() {
	for (int i = 0; i < vecfig.size(); i++)
		vecfig[i]->CambiaDy();
}
void CManejador::Cambiar_Direccion_Horizontal() {
	for (int i = 0; i < vecfig.size(); i++)
		vecfig[i]->CambiaDx();
}
void CManejador::Cambiar_Relleno() {
	for (int i = 0; i < vecfig.size(); i++)
		vecfig[i]->CambiaRelleno();
}

//source.pp
#pragma once
#include "Cuadrado.h"
#include "Triangulo.h"
#include<vector>
class CManejador
{
private:
	vector<CFigura*>vecfig;
public:
	CManejador();
	void Insertar(char letra);
	void Dibujar();
	void Mover();
	void Borrar();
	void Cambiar_Direccion_Vertical();
	void Cambiar_Direccion_Horizontal();
	void Cambiar_Relleno();
};

CManejador::CManejador() {}
void CManejador::Insertar(char letra)
{
	Random r;
	if (letra == 'C')
	{
		int tipo = r.Next(1, 3);
		if (tipo == 1)
			vecfig.push_back(new CCuadrado(r.Next(1, 70), r.Next(1, 15), 0, 1,
				r.Next(2, 6), tipo));
		else
			vecfig.push_back(new CCuadrado(r.Next(1, 70), r.Next(1, 15), 1, 0,
				r.Next(2, 6), tipo));
	}
	if (letra == 'T')
		vecfig.push_back(new CTriangulo(r.Next(1, 70), r.Next(7, 16), 1, 0,
			r.Next(2, 6), r.Next()));
}
void CManejador::Dibujar() {
	for (int i = 0; i < vecfig.size(); i++)
		vecfig[i]->Dibujar();
}
void CManejador::Mover() {
	for (int i = 0; i < vecfig.size(); i++)
		vecfig[i]->Mover();
}
void CManejador::Borrar() {
	for (int i = 0; i < vecfig.size(); i++)
		vecfig[i]->Borrar();
}
void CManejador::Cambiar_Direccion_Vertical() {
	for (int i = 0; i < vecfig.size(); i++)
		vecfig[i]->CambiaDy();
}
void CManejador::Cambiar_Direccion_Horizontal() {
	for (int i = 0; i < vecfig.size(); i++)
		vecfig[i]->CambiaDx();
}
void CManejador::Cambiar_Relleno() {
	for (int i = 0; i < vecfig.size(); i++)
		vecfig[i]->CambiaRelleno();
}