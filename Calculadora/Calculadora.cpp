// Calculadora.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "conio.h"//Biblioteca que habilita la entra de datos en la terminal.
#include "stdio.h"
#include "stdlib.h"
#include "iostream"
#include <cmath>

const int zero = 0;
const int minus1 = -1;

using namespace std;

float sumar(float a, float b) {
	float valor;
	__asm {
		movss xmm0, a  //movemos el valor de a al xmm0
		addss xmm0, b //sumamos los valores del xmm0 y el valor de b
		movss valor, xmm0 // y movemos el resultado del xmm0 a la varible valor
	}
	return valor;
}
float restar(float a, float b) {
	float valor;
	__asm {
		movss xmm0, a  //movemos el valor de a al xmm0
		subss xmm0, b //restar los valores del xmm0 y el valor de b
		movss valor, xmm0 // y movemos el resultado del xmm0 a la varible valor
	}
	return valor;
}
float multiplicar(float a, float b) {
	float valor;
	__asm {
		movss xmm0, a  //movemos el valor de a al xmm0
		mulss xmm0 ,b //multiplicar los valores del xmm0 y el valor de b
		movss valor, xmm0 // y movemos el resultado del xmm0 a la varible valor
	}
	return valor;
}
float dividir(float a, float b) {
	float valor;
	__asm {
		movss xmm0, a  //movemos el valor de a al xmm0
		divss xmm0, b //dividimos los valores del xmm0 y el valor de b
		movss valor, xmm0 // y movemos el resultado del xmm0 a la varible valor
	}
	return valor;
}
float square_root(float base) {
	const float uno = 1.0, dos = 2.0;
	float zero = (float)::zero, minus1 = (float)::minus1, res = 0.0, tmp = 0.0;
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
<<<<<<< HEAD
/*float nep_log(float x) {
	float half = 0.5, one = 1, res = 0, it = 1, tmp = 0, n = 1, ten = 10;
	__asm {
		movss xmm0, x;
		comiss xmm0, half;
		ja ciclo2;
	ciclo1:
		//serie para cuando x es menor o igual a 1/2
		//pregunta del ciclo, se harán 10 iteraciones
		movss xmm0, n;
		comiss xmm0, ten;
		jae fin; //si n>=10, fin.
		movss xmm0, x;
		subss xmm0, one; 
		movss tmp, xmm0; //tmp = x - 1
		//hacer tmp^n
		push ecx;
		movss xmm0, dword ptr[n];
		movss dword ptr[esp], xmm0;
		push ecx;
		movss xmm0, dword ptr[tmp];
		movss dword ptr[esp], xmm0; //hasta aqui paso de parametros
		call pot;
		add esp, 8;
		fstp dword ptr[tmp]; //tmp = tmp^n
		movss xmm0, tmp;
		divss xmm0, n;
		movss tmp, xmm0; //tmp = tmp/n
		//incrementar resultado (porque es una sumatoria)
		movss xmm0, res;
		addss xmm0, tmp;
		movss res, xmm0; //res = res + tmp
		//incrementar n
		movss xmm0, n;
		addss xmm0, one;
		movss n, xmm0; //n++
		jmp ciclo1;

	ciclo2:
		movss xmm0, n;
		comiss xmm0, ten;
		jae fin; //si n>=10 goto fin
		//serie para cuando x > 1/2
		movss xmm0, x;
		subss xmm0, one; //x-1 en xmm0
		divss xmm0, x; //(x-1)/x en xmm0
		movss tmp, xmm0; //tmp = xmm0

		//hacer tmp^n
		push ecx;
		movss xmm0, dword ptr[n];
		movss dword ptr[esp], xmm0;
		push ecx;
		movss xmm0, dword ptr[tmp];
		movss dword ptr[esp], xmm0; //hasta aqui paso de parametros
		call pot;
		add esp, 8; //se suman 4 al esp por c/argumento
		fstp dword ptr[tmp]; //tmp = *retorno de la funcion*
		//tmp = tmp/n
		movss xmm0, tmp;
		divss xmm0, n;
		movss tmp, xmm0;//tmp /= n
		//sumar al resultado
		movss xmm0, res;
		addss xmm0, tmp;
		movss res, xmm0; //res += tmp
		//inc n
		movss xmm0, n;
		addss xmm0, one;
		movss n, xmm0; //n++
		jmp ciclo2;
	}
fin:
	return res;
}*/
float nep_log(float x) {
	float res = 0, n = 1, tmp1 = 0, tmp2 = 0;
	const float ten = 1000, one = 1, two = 2;
	/*while (n < 50) {
		tmp1 = x - 1;
		tmp2 = x + 1;
		tmp1 = tmp1 / tmp2;
		tmp2 = 2 * n + 1;
		tmp1 = powf(tmp1, tmp2);
		tmp1 = tmp1 / tmp2;
		res = res + tmp1;
		n = n+1;
	}
	res = res * 2;
	return res;*/
	__asm {
	ciclo:
		movss xmm0, ten;
		comiss xmm0, n;
		jbe finaldelciclo;
		movss xmm0, x;
		subss xmm0, one;
		movss tmp1, xmm0; //tmp1 = x-1
		movss xmm0, x;
		addss xmm0, one;
		movss tmp2, xmm0; //tmp2 = x+1
		movss xmm0, tmp1;
		divss xmm0, tmp2;
		movss tmp1, xmm0; //tmp1 = tmp1/tmp2
		movss xmm0, n;
		mulss xmm0, two;
		addss xmm0, one;
		movss xmm0, tmp2; //tmp2 = 2 * n + 1
		//llamar pot(tmp1, tmp2);
		push ecx;
		movss xmm0, dword ptr[tmp2];
		movss dword ptr[esp], xmm0;
		push ecx;
		movss xmm0, dword ptr[tmp1];
		movss dword ptr[esp], xmm0;
		call powf;
		add esp, 8;
		fstp dword ptr[tmp1]; //tmp1 = pot(tmp1, tmp2)
		movss xmm0, tmp1;
		divss xmm0, tmp2;
		movss tmp1, xmm0; //tmp1 = tmp1 / tmp2
		movss xmm0, res;
		addss xmm0, tmp1;
		movss res, xmm0; //res = res+ tmp1
		movss xmm0, n;
		addss xmm0, one;
		movss n, xmm0; //n++
		jmp ciclo;

	finaldelciclo:
		movss xmm0, res;
		mulss xmm0, two;
		movss res, xmm0;
	}
	return res;

}
float ten_log(float x) {
	float res, ln10, aux;
	const float ten = 10;
	__asm {
		/*//hallar ln(10)
		push ecx;
		movss xmm0, dword ptr[ten];
		movss dword ptr[esp], xmm0; //push de parametros
		call nep_log;
		add esp, 4;
		fstp dword ptr[ln10];
		//hallar ln(x)
		push ecx;
		movss xmm0, dword ptr[x];
		movss dword ptr[esp], xmm0; //push parametros
		call nep_log;
		add esp, 4;
		fstp dword ptr[res];
		//ln(x) / ln(10)
		movss xmm0, res;
		divss xmm0, ln10;
		movss res, xmm0;*/
		fld1;
		fld x;
		fyl2x;
		fstp aux;
		fld aux;
		fldl2t;
		fdivp st(1), st(0);
		fstp res;
	}
	return res;
}
float two_log(float x) {
	float res, ln2;
	const float two = 2;
	__asm {
		/*//hallar ln(2)
		push ecx;
		movss xmm0, dword ptr[two];
		movss dword ptr[esp], xmm0; //push parametro
		call nep_log;
		add esp, 4;
		fstp dword ptr[ln2];
		//hallar ln(x)
		push ecx;
		movss xmm0, dword ptr[x];
		movss dword ptr[esp], xmm0; //push parametro
		call nep_log;
		add esp, 4;
		fstp dword ptr[res]; //res = ln(x)
		movss xmm0, res;
		divss xmm0, ln2;
		movss res, xmm0; //res = ln(x) / ln(2)*/
		fld1;
		fld x;
		fyl2x;
		fst res;
	}
	return res;
}
float seno(float n){
	float radianes = 0.0174532925;
	if (n == 180 || n == 360) {
		return 0;
	}
	float grados = radianes*n;
	__asm {
		fld grados            //guarda losgrados 
			fsin              //la funcion seno
			fst[grados]       // almacenamiento y comparacion
=======
float seno(float n){
	float radianes = 0.0174532925;
	if (n == 180 || n == 360) {
		return 0;
	}
	float grados = radianes*n;
	__asm {
		fld grados            //guarda losgrados 
			fsin              //la funcion seno
			fst[grados]       // almacenamiento y comparacion
>>>>>>> origin/master
	}
		
}
float coseno(float n) {
<<<<<<< HEAD
	float radianes = 0.0174532925;
	if (n == 90 || n == 270) {
		return 0;
	}
	float grados = radianes*n;
	__asm {
		fld grados            //guarda losgrados 
			fcos              //la funcion coseno
			fst[grados]       //almacenamiento y comparacion 
=======
	float radianes = 0.0174532925;
	if (n == 90 || n == 270) {
		return 0;
	}
	float grados = radianes*n;
	__asm {
		fld grados            //guarda losgrados 
			fcos              //la funcion coseno
			fst[grados]       //almacenamiento y comparacion 
>>>>>>> origin/master
	}
}
float tangente(float n) {
	return dividir(seno(n), coseno(n));
}


int main()
{   
inicio: int n;
	float a, b;
	cout << "..::..::..::..::..::..::..::..::..::..::..\n"
		<< "..::..Bienvenido a la calculadora..::..::.\n"
		<<"..::..¿Qué operación desea realizar ? ..::..\n"
		<< ".::. = > Sumar dos números(1) ..::..::..::..\n"
		<<".::. = > Restar dos números(2) ..::..::..::.\n"
		<<".::. = > Multiplicar dos números(3) ..::..::\n"
		<<".::. = > Dividir dos números(4) ..::..::..::\n"
		<<".::. = > Elevar un número a una potencia(5) :\n"
		<<".::. = > Raíz cuadrada de un número(6) ..::\n"
		<<".::. = > Factorial de un número(7) ..::..::\n"
		<<".::. = > El seno de un números(8) se calculara con Funcion..::..::\n"
		<< ".::. = > El coseno de un numero(9) se calculara con Funcion....::\n"
		<< ".::. = > La Tangente de un numero(10)....::\n"
<<<<<<< HEAD
		<< ".::. = > Exponencial de un número(11) ..::\n"
		<< ".::. = > Logaritmo base 10 de un número(12)::\n"
		<< ".::. = > Logaritmo base 2 de un número(13).:\n"
=======
>>>>>>> origin/master
		<<"..::..::..::..::..::..::..::..::..::..::..\n"
		<<"..::..Por favor digite el número de ..::..\n"
		<<"..::..la operación que desea realizar ::..\n"
		<<".::.-->";
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
			<< ".::.=>" << sumar(a,b) << endl
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
	segundonumero:
		cout << "..::..Por favor, digite el segundo.::..::.\n"
			<< "..::..número de la operación     .::..::..\n"
			<< ".::.-->";
		cin >> b;
		if (b == 0) {
			cout << "..::..No se permite dividir entre 0 ..::..\n";
			goto segundonumero;
		}
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
			<< ".::.=> " << b << endl
			<< "..::..::..::..::..::..::..::..::..::..::..";
		goto continuacion;
	}
	if (n == 8) {
		cout << "..::..::..::..::..::..::..::..::..::..::..\n";
		cout << "..::..Ha seleccionado Seno:..::..::.\n"
			<< "..::..ATENCION: El seno se calculara con Funcion:..::..\n"
			<< "..::..Ingrese el angulo.::.-->";
		float n = 0;
	    cin >> n;
		cout << "..::..::..::..::..::..::..::..::..::..::..";
		cout << endl << "..::..El resultado de la operación es.::..\n"
			<< ".::.=> " << seno(n) << endl
<<<<<<< HEAD
			<< "..::..::..::..::..::..::..::..::..::..::..";
		goto continuacion;
	}
	if (n == 11) {
		cout << "..::..::..::..::..::..::..::..::..::..::..\n";
		cout << "..::..Ha seleccionado exponencial.::..::.\n"
			<< "..::..ATENCION: Solo esta permitido:..::..\n"
			<< "..::..El uso de enteros positivos  :..::..\n"
			<< "..::..Por favor, digite el número.::..::..\n"
			<< ".::.-->";
		cin >> a;
		cout << "..::..::..::..::..::..::..::..::..::..::.."
			<< endl << "..::..El resultado de la operación es.::..\n"
			<< ".::.=>" << _exp(a) << endl
			<< "..::..::..::..::..::..::..::..::..::..::..";
		goto continuacion;
	}
	if (n == 12) {
		cout << "..::..::..::..::..::..::..::..::..::..::..\n";
		cout << "..::..Ha seleccionado logaritmo_10::..::.\n"
			<< "..::..ATENCION: Solo esta permitido:..::..\n"
			<< "..::..El uso de enteros positivos  :..::..\n"
			<< "..::..Por favor, digite el número.::..::..\n"
			<< ".::.-->";
		cin >> a;
		cout << "..::..::..::..::..::..::..::..::..::..::.."
			<< endl << "..::..El resultado de la operación es.::..\n"
			<< ".::.=>" << ten_log(a) << endl
			<< "..::..::..::..::..::..::..::..::..::..::..";
		goto continuacion;
	}
	if (n == 13) {
		cout << "..::..::..::..::..::..::..::..::..::..::..\n";
		cout << "..::..Ha seleccionado logaritmo_2::..::.\n"
			<< "..::..ATENCION: Solo esta permitido:..::..\n"
			<< "..::..El uso de enteros positivos  :..::..\n"
			<< "..::..Por favor, digite el número.::..::..\n"
			<< ".::.-->";
		cin >> a;
		cout << "..::..::..::..::..::..::..::..::..::..::.."
			<< endl << "..::..El resultado de la operación es.::..\n"
			<< ".::.=>" << two_log(a) << endl
			<< "..::..::..::..::..::..::..::..::..::..::..";
		goto continuacion;
	}
=======
			<< "..::..::..::..::..::..::..::..::..::..::..";
		goto continuacion;
	}
>>>>>>> origin/master
	if (n == 9) {
		cout << "..::..::..::..::..::..::..::..::..::..::..\n";
		cout << "..::..Ha seleccionado Coseno:..::.\n"
			<< "..::..ATENCION: El Coseno se calculara con Funcion.::..\n"
			<< "..::..Ingrese el angulo.::.-->";
		float n = 0;
		cin >> n;
		cout << "..::..::..::..::..::..::..::..::..::..::..";
		cout << endl << "..::..El resultado de la operación es.::..\n"
			<< ".::.=> " << coseno(n) <<endl
			<< "..::..::..::..::..::..::..::..::..::..::..";
		goto continuacion;
	}
	if (n ==10) {
		cout << "..::..::..::..::..::..::..::..::..::..::..\n";
		cout << "..::..Ha seleccionado Tangente::.\n"
			<< "..::..Ingrese el angulo.::.-->";
		float n = 0;
		cin >> n;
		cout << "..::..::..::..::..::..::..::..::..::..::..";
		cout << endl << "..::..El resultado de la operación es.::..\n"
			<< ".::.=> " << tangente(n) << endl
			<< "..::..::..::..::..::..::..::..::..::..::..";
		goto continuacion;
	}

<<<<<<< HEAD
=======

>>>>>>> origin/master
continuacion: n = 0;
	cout << endl << "..::..::..::..::..::..::..::..::..::..::.." << endl
		<< "..::..Desea realizar otra operacion? (s/n)..::.." << endl
		<< ".::.-->";
	char o;
	cin >> o;
	if (o == 's') {
		goto inicio;
	}
	cout << "|__        ___ " << endl
		<< "|__) (__| (__/_" << endl
		<< "        |      " << endl;
	system("pause");
	return 0;
}

