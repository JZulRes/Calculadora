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

float pot(float base, int exp) {
	float res = 1;
	__asm {
 		finit;
		mov ecx, exp; //cargar exp en cx
	ciclo: fld dword ptr[res]; // meto a res en la pila
		fmul dword ptr[base]; // multiplico por base
		fst dword ptr[res]; // muevo el resultado a res
		dec ecx; //decremento cx
		cmp ecx, zero; //comparo si es igual a 0
		jne ciclo; //loop si no son iguales
	}
	return res;
}

float square_root(float base) {
	const float uno = 1.0, dos=2.0;
	float zero = (float)::zero, minus1 = (float)::minus1, res=0.0, tmp=0.0;
	__asm {
		finit;
		fld dword ptr[zero];
		fld dword ptr[base];
		fcomip ST(0), ST(1);
		jb menor;
		fld dword ptr[base];
		fst dword ptr[res];

ciclo:  fld dword ptr[res];
		fld dword ptr[tmp];
		fcomip ST(0), ST(1);
		je fin;
		fld dword ptr[res];
		fst dword ptr[tmp]; //tmp = res
		fld dword ptr[base]; //meto res en el stack
		fdiv dword ptr[res]; //   base/res
		fadd dword ptr[res]; // base/res + res
		fdiv dword ptr[dos]; // (base/res + res)/2
		fst dword ptr[res]; //res = (base/res + res)/2
		jmp ciclo;

menor:	fld dword ptr[minus1];
		fst dword ptr[res];
		jmp fin;
	}
fin: return res;
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
	cout << "Raiz cuadrada(6)" << endl;
	cout << "Factorial(7)" << endl;
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
	if (n == 6) {
		cout << "Digite el numero al cual le desea sacar la raiz" << endl;
		float b,r;
		cin >> b;
		r = square_root(b);
		printf(r < 0 ? "No se puede sacar raiz de numeros negativos\n" : "%s %d", "El resultado es: \n", r);
		goto continuacion;
	}
	if (n == 7) {
		cout << "ATENCION: Solo se admite el factorial de ENTEROS NO-NEGATIVOS" << endl << "Digite el numero" << endl;
		int b=0;
		cin >> b;
		b = factorial(b);
		printf(b < 0 ? "No se puede hallar el factorial de numeros negativos" : "%s %d", "El resultado es: \n", b);
		goto continuacion;
	}
continuacion: n = 0;
	printf("Desea realizar otra operacion?(s/n) \n");
	char o;
	cin >> o;
	if (o == 's') {
		goto inicio;
	}
	return 0;
}

