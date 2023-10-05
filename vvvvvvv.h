#pragma once
#include <iostream>
using namespace std;
using namespace System;

class CFigura {
protected:
	int x, y, dx, dy, ancho, alto;
public:
	CFigura() {};
	~CFigura() {};
	void movimiento(int pdx, int pdy);
	void borrar();
	virtual void dibujar() {};
	virtual void mover() {};
	int getX();
	int getY();
	int getAncho();
	int getAlto();
};

void CFigura::movimiento(int pdx, int pdy) {
	if (x + dx < 0 || x + dx + ancho>79) dx = pdx;
	if (y + dy < 0 || y + dy + alto>24) dy = pdy;
	x = x + dx;
	y = y + dy;
}
void CFigura::borrar() {
	for (int i = 0;i < alto;i++)
		for (int j = 0;j < ancho;j++) {
			Console::SetCursorPosition(x + j, y + i);
			cout << " ";
		}
}
int CFigura::getX() { return x; }
int CFigura::getY() { return y; }
int CFigura::getAncho() { return ancho; }
int CFigura::getAlto() { return alto; }




#pragma once
#include "figura.h"
class CVacuna : public CFigura {
private:
public:
	CVacuna();
	~CVacuna() {};
	void dibujar();
	void mover();
};
CVacuna::CVacuna() {
	Random r;
	alto = 1;
	ancho = 4;
	x = r.Next(0, 79 - ancho);
	y = r.Next(0, 24 - alto);
	do {
		dx = r.Next(-1, 2);//-1,0,1
		dy = r.Next(-1, 2);//-1,0,1
	} while (abs(dx) == abs(dy));
	dx = dx * 2;
}
void CVacuna::dibujar() {
	Console::SetCursorPosition(x, y); cout << "|->|";
}
void CVacuna::mover() {
	movimiento(-dx, -dy);
}




#pragma once
#include "figura.h"
class CCasa :public CFigura {
private:
public:
	CCasa();
	~CCasa() {};
	void dibujar();
};

CCasa::CCasa() {
	alto = 5;
	ancho = 7;
	x = 79 - ancho;
	y = 24 - alto;
	dx = dy = 0;
}
void CCasa::dibujar() {
	Console::SetCursorPosition(x, y); cout << "  +";
	Console::SetCursorPosition(x, y + 1); cout << "  A_";
	Console::SetCursorPosition(x, y + 2); cout << " /\\-\\";
	Console::SetCursorPosition(x, y + 3); cout << "_||\"|_";
	Console::SetCursorPosition(x, y + 4); cout << "^~^~^~^";

}




#pragma once
#include "figura.h"
class CVirus :public CFigura {
private:
public:
	CVirus();
	~CVirus() {};
	void dibujar();
	void mover();
};
CVirus::CVirus() {
	Random r;
	alto = 5;
	ancho = 9;
	x = r.Next(0, 79 - ancho);
	y = r.Next(0, 24 - alto);
	do {
		dx = r.Next(-1, 2);
		dy = r.Next(-1, 2);
		_sleep(10);
	} while (dx == 0 || dy == 0);
}
void CVirus::dibujar() {
	Console::SetCursorPosition(x, y);   cout << "    q";
	Console::SetCursorPosition(x, y + 1); cout << "  0-0-0";
	Console::SetCursorPosition(x, y + 2); cout << "0-0 0 0-0";
	Console::SetCursorPosition(x, y + 3); cout << "  0-0-0";
	Console::SetCursorPosition(x, y + 4); cout << "    q";
}
void CVirus::mover() {
	movimiento(-dx, -dy);
}



#pragma once
#include "figura.h"
class CMonigote :public CFigura {
private:
public:
	CMonigote();
	~CMonigote() {};
	void dibujar();
	void mover();
	void desplazamiento(char tecla);
};
CMonigote::CMonigote() {
	ancho = 1;
	alto = 2;
	x = 0;
	y = 0;
	dx = dy = 0;
}
void CMonigote::dibujar() {
	Console::SetCursorPosition(x, y); cout << "0";
	Console::SetCursorPosition(x, y); cout << "+";

}
void CMonigote::mover() {
	movimiento(0, 0);
}
void CMonigote::desplazamiento(char tecla) {
	dx = dy = 0;
	switch (tecla) {
	case 75:dx = -2;break;//izq
	case 77:dx = 2;break;//derec
	case 72:dy = -1;break;//arriba
	case 80:dy = 1;break;//abajo
	}

}




#pragma once
#include "vacuna.h"
#include "casa.h"
#include "virus.h"
#include "monigote.h"
#include <conio.h>
#include <vector>
class CManejador {
private:
	vector<CFigura*>figuras;
	int n;
	CCasa* casa;
	CMonigote* monigote;
public:
	CManejador();
	~CManejador() {};
	void gestionar();
	void jugar();
};

CManejador::CManejador() {
	Random r;
	n = r.Next(3, 6);
	for (int i = 0;i < n;i++)
		figuras.push_back(new CVirus());
	figuras.push_back(new CVacuna());
	casa = new CCasa();
	monigote = new CMonigote();
}
void CManejador::gestionar() {
	for (int i = 0;i < figuras.size();i++) {
		figuras[i]->borrar();
		figuras[i]->mover();
		figuras[i]->dibujar();
	}
	casa->dibujar();
	monigote->borrar();
	monigote->mover();
	monigote->dibujar();
}
void CManejador::jugar() {
	do {

		if (kbhit())
			monigote->desplazamiento(getch());
		gestionar();
		_sleep(50);
	} while (true);
}




#include "manejador.h"

void main() {
	Console::CursorVisible = false;
	CManejador* manejador;
	manejador = new CManejador();
	manejador->jugar();
}