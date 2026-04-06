#include <ctype.h>
#include <stdio.h>
#include <string.h>

// IMPORTANTE
#define A 16
#define B 15

#define RANGO_ENTERO 65535
#define RANGO_DECIMAL 99996948242
#define DEFINICION 000030517578125
#define RANGO_INF -32768
#define RANGO_SUP 32767
#define ERROR 999

struct NumerosQ {
  int signo;
  int entera;
  int fraccion;
  int divisor;
};

struct Datos{
  struct NumerosQ valores;
  char input[50];
};

struct Datos leerNumeros();
struct NumerosQ calcularY(struct NumerosQ m, struct NumerosQ b, struct NumerosQ x);
void imprimirValores(struct NumerosQ m, struct NumerosQ b, struct NumerosQ x);

/* 

    h. Escriba un programa que permita el ingreso de los valores de m, b y x en forma decimal y muestre su representaciónen
  punto fijo en formato hexadecimal validando la entrada como en los puntos anteriores. Luego realizando todas las operacioes
  en punto fijo con las representaciones adoptadas calcule el valor de la ordenada y y lo muestre en punto fjo
  en forma hexadecimal y en decimal.

*/

int IncisoH() {

  int act = -1;
  struct Datos m, b, x;

  m.valores.signo = 0;
  m.valores.entera = 0;
  m.valores.fraccion = 0;
  
  b.valores.signo = 0;
  b.valores.entera = 0;
  b.valores.fraccion = 0;
  
  x.valores.signo = 0;
  x.valores.entera = 0;
  x.valores.fraccion = 0;

  do {
    printf("\n Operaciones disponibles:");
    printf("\n -  1: ingresar pendiente (m).");
    printf("\n -  2: ingresar ordenada (b).");
    printf("\n -  3: ingresar valor de x.");
    printf("\n -  4: imprimir valores actuales.");
    printf("\n -  5: aproximar recta con 20 valores de x.");
    printf("\n -  6: Exportar resultados a txt.");
    printf("\n -  7: limpiar historial de resultados.");
    printf("\n -  0: Salir.");
    printf("\nIngrese una opcion:");

    scanf("%d", &act);  // <-- corregido
    getchar(); // Deja el buffer listo para la sig operacion.

    switch (act) {
    case 0:
      break;
    case 1:
      m = leerNumeros();
      printf("Resultado decimal: %c%d.%d", m.valores.signo ? '-' : '+', m.valores.entera, m.valores.fraccion);
      break;
    case 2:
      b = leerNumeros();
      printf("Resultado decimal: %c%d.%d", b.valores.signo ? '-' : '+', b.valores.entera, b.valores.fraccion);
      break;
    case 3:
      x = leerNumeros();
      printf("Resultado decimal: %c%d.%d", x.valores.signo ? '-' : '+', x.valores.entera, x.valores.fraccion);
      break;
    case 4:
      printf("DEBUG - POR IMPLEMENTAR");
      break;
    case 5:
      printf("DEBUG - POR IMPLEMENTAR");
      break;
    case 6:
      printf("DEBUG - POR IMPLEMENTAR");
      break;
    case 7:
      printf("DEBUG - POR IMPLEMENTAR");
      break;
    default:
      printf("Error valor no valido.");
    }

  } while (act != 0);

  return 0;  // <-- agregado
}

struct NumerosQ calcularY(struct NumerosQ m, struct NumerosQ b, struct NumerosQ x){
  struct NumerosQ res;

  return res;
}

void imprimirValores(struct NumerosQ m, struct NumerosQ b, struct NumerosQ x) {

}

struct Datos leerNumeros() {
  struct Datos res;
  struct NumerosQ num;
  char input[50];

  res.valores.signo = 1;
  res.valores.entera = 0;
  res.valores.fraccion = 0;
  res.valores.divisor = 1;
  res.input[0] = 1;

  num.signo = 1;
  num.entera = 0;
  num.fraccion = 0;
  num.divisor = 1;

  printf("\nIngrese un numero (+/-eee.ffff): ");

  if (!fgets(input, sizeof(input), stdin)) {
    printf("Error de entrada\n");
    num.signo = ERROR;
    return res;
  }

  int i = 0;

  if (input[i] == '-') {
    num.signo = -1;
    i++;
  } else if (input[i] == '+') {
    i++;
  }

  if (!isdigit(input[i])) {
    printf("Formato invalido\n");
    num.signo = ERROR;
    return res;
  }

  while (isdigit(input[i]) && i < sizeof(input)) {
    num.entera = num.entera * 10 + (input[i] - '0');
    i++;
  }

  if (input[i] == '.') {
    i++;
    if (!isdigit(input[i])) {
      printf("Formato invalido\n");
      num.signo = ERROR;
      return res;
    }

    while (isdigit(input[i]) && i < sizeof(input)) {
      num.fraccion = num.fraccion * 10 + (input[i] - '0');
      num.divisor *= 10;
      i++;
    }
  }

  
  res.valores = num;
  for (int i=0; i<50; i++){
    res.input[i] = input[i];
  }

  return res;
}
