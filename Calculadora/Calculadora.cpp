// Calculadora.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "conio.h"//Biblioteca que habilita la entra de datos en la terminal.
#include "stdio.h"
#include "stdlib.h"
#include "iostream"

const int zero = 0;

using namespace std;

float sumar(float a, float b) {
	float valor;
	__asm {
		movss xmm0, a  //movemos el valor de a al eax
		addss xmm0, b //sumamos los valores del eax y el valor de b
		movss valor, xmm0 // y movemos el resultado del eax a la varible valor
	}
	return valor;
}
float restar(float a, float b) {
	float valor;
	__asm {
		movss xmm0, a  //movemos el valor de a al eax
		subss xmm0, b //restar los valores del eax y el valor de b
		movss valor, xmm0 // y movemos el resultado del eax a la varible valor
	}
	return valor;
}
float multiplicar(float a, float b) {
	float valor;
	__asm {
		movss xmm0, a  //movemos el valor de a al eax
		mulss xmm0 ,b //multiplicar los valores del xmm0 y el valor de b
		movss valor, xmm0 // y movemos el resultado del eax a la varible valor
	}
	return valor;
}
float dividir(float a, float b) {
	float valor;
	__asm {
		movss xmm0, a  //movemos el valor de a al eax
		divss xmm0, b //dividimos los valores del eax y el valor de b
		movss valor, xmm0 // y movemos el resultado del eax a la varible valor
	}
	return valor;
}

float pot(float base, int exp) {
	float res = 1;
	__asm {
 		finit;
		mov ecx, exp; //cargar exp en cx
	ciclo: fld dword ptr[res]; //cargar resultado en ax
		fmul dword ptr[base]; // multiplico
		fst dword ptr[res]; // muevo el resultado a res
		dec ecx; //decremento cx
		cmp ecx, zero; //comparo si es igual a 0
		jne ciclo; //loop si no son iguales
	}
	return res;
}

int main()
{   
inicio: int n;
	float a, b;
	cout << "Bienvenido a la calcuadora Remasterizada" << endl;
	cout << "Teclee la operacion a realizar" << endl;
	cout << "Suma(1)" << endl;
	cout << "Resta(2)" << endl;
	cout << "Multiplicacion(3)" << endl;
	cout << "Division(4)" << endl;
	cout << "Potenciacion(5)" << endl;
	cin >> n;
	cout << "" << endl;

	if (n == 1) {
		cout << "Operacion Suma activada" << endl;
		cout << "Digite primer numero: " << endl;
		cin >> a;
		cout << "Digite segundo numero: " << endl;
		cin >> b;
		cout << "Resultado = " << sumar(a,b) << endl;
		cout << endl;
		goto continuacion;
	}
	if (n == 2) {
		cout << "Operacion Resta activada" << endl;
		cout << "Digite primer numero: " << endl;
		cin >> a;
		cout << "Digite segundo numero: " << endl;
		cin >> b;
		cout << "Resultado = " << restar(a,b) << endl;
		cout << endl;
		goto continuacion;
	}
	if (n == 3) {
		cout << "Operacion Multiplicacion activada" << endl;
		cout << "Digite primer numero: " << endl;
		cin >> a;
		cout << "Digite segundo numero: " << endl;
		cin >> b;
		cout << "Resultado = " << multiplicar(a,b) << endl;
		cout << endl;
		goto continuacion;
	}
	if (n == 4) {
		cout << "Operacion Division activada" << endl;
		cout << "Digite primer numero: " << endl;
		cin >> a;
		cout << "Digite segundo numero: " << endl;
		cin >> b;
		cout << "Resultado = " << dividir(a, b) << endl;
		cout << endl;
		goto continuacion;
	}
	if (n == 5) {
		cout << "Digite base, entera o decimal" << endl;
		float b;
		cin >> b;
		cout << "Ingrese exponente." << endl << "ADVERTENCIA: SOLO SE ADMITEN EXPONENTES ENTEROS" << endl;
		cin >> a;
		cout << "Resultado = " << pot(b,a) << endl;
		cout << endl;
		goto continuacion;
	}
continuacion: n = 0;
	cout << "Operacion finalizada, Desea continuar" << endl;
	cout << "1 para SI o 2 para NO" << endl;
	cin >> n;
	if (n == 1) {
		goto inicio;
	}
	return 0;
}

