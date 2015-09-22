// Calculadora.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "conio.h"//Biblioteca que habilita la entra de datos en la terminal.
#include "stdio.h"
#include "stdlib.h"
#include "iostream"

const int zero = 0;
const int minus1 = -1;

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
float square_root(float base) {
	const float uno = 1.0, dos = 2.0;
	float zero = (float)::zero, minus1 = (float)::minus1, res = 0.0, tmp = 0.0, tmp1, tmp2;
	__asm {
		finit;
		fld[zero];
		fld[base];
		fcomip st(0), ST(1);
		fstp st(0);
		jb menor;
		fld[base];
		fst[res];

	ciclo:
		movss xmm0, dword ptr[res]
			comiss xmm0, dword ptr[tmp]
			je fin;
		movss xmm0, res;
		movss tmp, xmm0; //tmp = res
		movss xmm0, base; //base en xmm0
		divss xmm0, res; //base/res;
		addss xmm0, res; // (base/res) + res
		divss xmm0, dos; // ((base/res)+res)/2
		movss res, xmm0;
		jmp ciclo;

	menor:	fld dword ptr[minus1];
		fst dword ptr[res];
		jmp fin;

	}

fin: return res;
}
float pot(float base, float exp) {
	float res;
	__asm {
		fld dword ptr[exp];
		fld dword ptr[base];
		fyl2x;
		fld st;
		frndint;
		fsub st(1), st;
		fxch st(1);
		f2xm1;
		fld1;
		fadd;
		fscale;
		fstp dword ptr[res];
	}
	return res;
}
int factorial(int n) {
	const int zero = 0, one = 1, minusone=-1;
	int res = 1;
	__asm {
		mov eax, n;
		cmp eax, zero;
		jl menor; //si n<0 salte
		je igual; //si n=0 salte
		mov ecx, one;
		cmp ecx, n;
		je igual;
	ciclo: inc ecx; //i++
		mov eax, res; // cargar resultado
		mul ecx; //multiplicar por el iterador
		mov res, eax; //res = res*i
		cmp ecx, n; // ecx == n
		je fin; 
		jmp ciclo;

	menor: mov eax, minusone 
		mov res, eax;
		jmp fin;

	igual: mov eax, one;
		mov res, eax;
		jmp fin;
	}
fin: return res;
}
float _exp(float n) {
	float res;
	const float e = 2.7182818284590452353;
	__asm {
		push ecx;
		movss xmm0, dword ptr[n];
		movss dword ptr[esp], xmm0;
		push ecx;
		movss xmm0, dword ptr[e];
		movss dword ptr[esp], xmm0;
		call pot;
		add esp, 8;
		fstp dword ptr[res];
	}
	return res;
}

int main()
{   
inicio: int n;
	float a, b;
	cout << "..::..::..::..::..::..::..::..::..::..::..\n..::..Bienvenido a la calculadora..::..::.\n..::..¿Qué operación desea realizar ? ..::..\n.::. = > Sumar dos números(1) ..::..::..::..\n.::. = > Restar dos números(2) ..::..::..::.\n.::. = > Multiplicar dos números(3) ..::..::\n.::. = > Dividir dos números(4) ..::..::..::\n.::. = > Elevar un número a una potencia(5) :\n.::. = > Raíz cuadrada de un número(6) ..::\n.::. = > Factorial de un número(7) ..::..::\n..::..::..::..::..::..::..::..::..::..::..\n..::..Por favor digite el número de ..::..\n..::..la operación que desea realizar ::..\n.::.-->";
	cin >> n;

	if (n == 1) {
		cout << "..::..::..::..::..::..::..::..::..::..::..\n";
		cout << "..::..::..::Ha seleccionado sumar.::..::..\n"
			<< "..::..Por favor, digite el primer.::..::..\n"
			<< "..::..número de la operación     .::..::..\n"
			<< ".::.-->";
		cin >> a;
		cout << "..::..Por favor, digite el segundo.::..::.\n"
			<< "..::..número de la operación     .::..::..\n"
			<< ".::.-->";
		cin >> b;
		cout << "..::..::..::..::..::..::..::..::..::..::.."
			<< endl << "..::..El resultado de la operación es.::..\n"
			<< ".::.=>" << sumar(a, b) << endl
			<< "..::..::..::..::..::..::..::..::..::..::..";
		goto continuacion;
	}
	if (n == 2) {
		cout << "..::..::..::..::..::..::..::..::..::..::..\n";
		cout << "..::..::..::Ha seleccionado restar.::..::.\n"
			<< "..::..Por favor, digite el primer.::..::..\n"
			<< "..::..número de la operación     .::..::..\n"
			<< ".::.-->";
		cin >> a;
		cout << "..::..Por favor, digite el segundo.::..::.\n"
			<< "..::..número de la operación     .::..::..\n"
			<< ".::.-->";
		cin >> b;
		cout << "..::..::..::..::..::..::..::..::..::..::.."
			<< endl << "..::..El resultado de la operación es.::..\n"
			<< ".::.=>" << restar(a, b) << endl
			<< "..::..::..::..::..::..::..::..::..::..::..";
		goto continuacion;
	}
	if (n == 3) {
		cout << "..::..::..::..::..::..::..::..::..::..::..\n";
		cout << "..::..Ha seleccionado multiplicar.::..::.\n"
			<< "..::..Por favor, digite el primer.::..::..\n"
			<< "..::..número de la operación     .::..::..\n"
			<< ".::.-->";
		cin >> a;
		cout  << "..::..Por favor, digite el segundo.::..::.\n"
			<< "..::..número de la operación     .::..::..\n"
			<< ".::.-->";
		cin >> b;
		cout << endl << "..::..::..::..::..::..::..::..::..::..::.."
			<< endl << "..::..El resultado de la operación es.::..\n"
			<< ".::.=>" << multiplicar(a, b) << endl
			<< "..::..::..::..::..::..::..::..::..::..::..";
		goto continuacion;
	}
	if (n == 4) {
		cout << "..::..::..::..::..::..::..::..::..::..::..\n";
		cout << "..::..Ha seleccionado dividir.::..::..::.\n"
			<< "..::..Por favor, digite el primer.::..::..\n"
			<< "..::..número de la operación     .::..::..\n"
			<< ".::.-->";
		cin >> a;
		cout << "..::..Por favor, digite el segundo.::..::.\n"
			<< "..::..número de la operación     .::..::..\n"
			<< ".::.-->";
		cin >> b;
		cout << "..::..::..::..::..::..::..::..::..::..::.."
			<< endl << "..::..El resultado de la operación es.::..\n"
			<< ".::.=>" << dividir(a, b) << endl
			<< "..::..::..::..::..::..::..::..::..::..::..";
		goto continuacion;
	}
	if (n == 5) {
		cout << "..::..::..::..::..::..::..::..::..::..::..\n";
		cout << "..::..Ha seleccionado potenciación::..::..\n"
			<< "..::..Por favor, digite la base::..::..::..\n"
			<< ".::.-->";
		cin >> a;
		cout 
			<< "..::..Por favor, digite el exponente.::..::\n"
			<< ".::.-->";
		cin >> b;
		cout  << "..::..::..::..::..::..::..::..::..::..::.."
			<< endl << "..::..El resultado de la operación es.::..\n"
			<< ".::.=>" << pot(a, b) << endl
			<< "..::..::..::..::..::..::..::..::..::..::..";
		goto continuacion;
	}
	if (n == 6) {
		cout << "..::..::..::..::..::..::..::..::..::..::..\n";
		cout << "..::..Ha seleccionado radicación:..::..::.\n"
			<< "..::..Por favor, digite el       .::..::..\n"
			<< "..::..radicando    .::..::..\n"
			<< ".::.-->";
		cin >> a;
		float r = square_root(a);
		if (r < 0) {
			cout << "..::..::..::..::..::..::..::..::..::..::..\n..::..ERROR, no se puede sacar raíz de::..\n..::..números negativos               ::..\n";
			goto continuacion;
		}
		cout << "..::..::..::..::..::..::..::..::..::..::.."
			<< endl << "..::..El resultado de la operación es.::..\n"
			<< ".::.=>" << r << endl
			<< "..::..::..::..::..::..::..::..::..::..::..";
		goto continuacion;
	}
	if (n == 7) {
		cout << "..::..::..::..::..::..::..::..::..::..::..\n";
		cout << "..::..Ha seleccionado factorial:..::..::.\n"
			<< "..::..ATENCION: Solo esta permitido:..::..\n"
			<< "..::..El uso de enteros positivos  :..::..\n"
			<< "..::..Por favor, digite el número.::..::..\n"
			<< ".::.-->";
		int b=0;
		cin >> b;
		b = factorial(b);
		if (b < 0) {
			cout << "..::..::..::..::..::..::..::..::..::..::..\n..::..ERROR, no se puede sacar factorail de::..\n..::..números negativos               ::..\n";
			goto continuacion;
		}
		cout << "..::..::..::..::..::..::..::..::..::..::.."
			<< endl << "..::..El resultado de la operación es.::..\n"
			<< ".::.=>" << b << endl
			<< "..::..::..::..::..::..::..::..::..::..::..";
		goto continuacion;
	}
continuacion: n = 0;
	cout << "..::..::..::..::..::..::..::..::..::..::.."
		<< "..::..Desea realizar otra operacion? (s/n)..::.."
		<< ".::.-->";
	char o;
	cin >> o;
	if (o == 's') {
		goto inicio;
	}
	return 0;
}

