#include "stdafx.h"
#include "conio.h"//Biblioteca que habilita la entra de datos en la terminal.
#include "stdio.h"
#include "stdlib.h"
#include "iostream"

using namespace std;

float funcion(float x, float y) {
	float retorno = 0;
	__asm {
		fld x;
		fmul y;
		fst retorno;
	}
	return retorno;
}
/*
int main() {
	float x = 0, y = 0;
	cin >> x >> y;
	//y = funcion(x, y);
	// ESTO ES PARA ENTEROS:
	/*__asm {
		mov eax, y; //siempre se deben poner los argumentos en orden inverso, es decir
		push eax; //si es f(x, y), primero hacer push de 'y' y luego de 'x'
		mov eax, x;
		push eax
		call funcion;
		mov z, eax;
		add esp, 8; //siempre sumar al esp 4*numero de args de la fn
	}*/
	//PARA FLOTANTES:
/*	__asm {
		nop;
		push ecx;
		movss xmm0, dword ptr[y];
		movss dword ptr[esp], xmm0;
		push ecx;
		movss xmm0, dword ptr[x];
		movss dword ptr[esp], xmm0;
		call funcion;
		add esp, 8;
		fstp dword ptr[y];
	}
	cout << y << endl;
	system("pause");
	return 0;
}*/