#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// IMPORTANTE
#define A 16
#define B 15

#define ESCALA16     (1 << 15)
#define RESOLUCION (1.0 / ESCALA16)
#define ERROR      999

struct NumerosQ {
  int signo;
  int entera;
  int fraccion;
  int divisor;
  int repreQ;
};

struct Datos{
  struct NumerosQ valores;
  char input[50];
};

struct Datos leerNumeros();
struct NumerosQ calcularY(struct NumerosQ m, struct NumerosQ b, struct NumerosQ x);
void imprimirValores(struct NumerosQ m, struct NumerosQ b, struct NumerosQ x, struct NumerosQ y);
int convertidorQ(struct NumerosQ n);

/* 

    h. Escriba un programa que permita el ingreso de los valores de m, b y x en forma decimal y muestre su representaciónen
  punto fijo en formato hexadecimal validando la entrada como en los puntos anteriores. Luego realizando todas las operacioes
  en punto fijo con las representaciones adoptadas calcule el valor de la ordenada y y lo muestre en punto fjo
  en forma hexadecimal y en decimal.

*/

int IncisoH() {

  int act = -1;
  struct Datos m, b, x, y;

  m.valores.signo = 0;
  m.valores.entera = 0;
  m.valores.fraccion = 0;
  m.valores.repreQ = 0;
  
  b.valores.signo = 0;
  b.valores.entera = 0;
  b.valores.fraccion = 0;
  b.valores.repreQ = 0;
  
  x.valores.signo = 0;
  x.valores.entera = 0;
  x.valores.fraccion = 0;
  x.valores.repreQ = 0;

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

    scanf("%d", &act);
    getchar();

    switch (act) {
    case 0:
      break;
  case 1:
      m = leerNumeros();
      printf("\nResultado decimal: %c%d.%d", m.valores.signo ? '-' : '+', m.valores.entera, m.valores.fraccion);
      printf("\nResultado Q(16,15): 0x%08X", (uint32_t)m.valores.repreQ);
      break;
  case 2:
      b = leerNumeros();
      printf("\nResultado decimal: %c%d.%d", b.valores.signo ? '-' : '+', b.valores.entera, b.valores.fraccion);
      printf("\nResultado Q(16,15): 0x%08X", (uint32_t)b.valores.repreQ);
      break;
  case 3:
      x = leerNumeros();
      printf("\nResultado decimal: %c%d.%d", x.valores.signo ? '-' : '+', x.valores.entera, x.valores.fraccion);
      printf("\nResultado Q(16,15): 0x%08X", (uint32_t)x.valores.repreQ);
      break;
  case 4:
      y.valores = calcularY(m.valores, b.valores, x.valores);
      imprimirValores(m.valores, b.valores, x.valores, y.valores);
      break;
  case 5:
      printf("\nDEBUG - POR IMPLEMENTAR");
      break;
  case 6:
      printf("\nDEBUG - POR IMPLEMENTAR");
      break;
  case 7:
      printf("\nDEBUG - POR IMPLEMENTAR");
      break;
  default:
      printf("\nError valor no valido.");
  }

  printf("\n\n-----------------");
} while (act != 0);

return 0;
}

struct NumerosQ calcularY(struct NumerosQ m, struct NumerosQ b, struct NumerosQ x){
  struct NumerosQ y;

  y.repreQ = ((int64_t)m.repreQ * x.repreQ >> B) + b.repreQ;
  printf("\nDEBUG - Y = %d",y.repreQ);
  printf("\nResultado Q(16,15): 0x%08X", (uint32_t)y.repreQ);

  return y;
}

void imprimirValores(struct NumerosQ m, struct NumerosQ b, struct NumerosQ x, struct NumerosQ y) {
    printf("\n - Y = m * x + b:");
    printf("\n --- Decimal: %c%d.%d = %c%d.%d * %c%d.%d + %c%d.%d",y.signo ? '-' : '+', y.entera, y.fraccion, m.signo ? '-' : '+', m.entera, m.fraccion, x.signo ? '-' : '+', x.entera, x.fraccion, b.signo ? '-' : '+', b.entera, b.fraccion);
    printf("\n --- Resultado Q(16,15): 0x%08X = 0x%08X * 0x%08X + 0x%08X", (uint32_t)y.repreQ, (uint32_t)m.repreQ, (uint32_t)x.repreQ, (uint32_t)b.repreQ);
}

struct Datos leerNumeros() {
  struct Datos res;
  struct NumerosQ num;
  char input[50];
  int continuar;

  do {
    continuar = 1;

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
      printf("\nError de entrada");
      num.signo = ERROR;
      continuar = 0;
  }

  int i = 0;

  if (input[i] == '-') {
      num.signo = -1;
      i++;
  } else if (input[i] == '+') {
      i++;
  }

  if (!isdigit(input[i])) {
      printf("\nFormato invalido");
      num.signo = ERROR;
      continuar = 0;
  }

  while (isdigit(input[i]) && i < sizeof(input)) {
      num.entera = num.entera * 10 + (input[i] - '0');
      i++;
  }

  if (input[i] == '.') {
      i++;
      if (!isdigit(input[i])) {
        printf("\nFormato invalido");
        num.signo = ERROR;
        continuar = 0;
    }

    while (isdigit(input[i]) && i < sizeof(input)) {
        num.fraccion = num.fraccion * 10 + (input[i] - '0');
        num.divisor *= 10;
        i++;
    }

    num.repreQ = convertidorQ(num);

      /* valida el rango*/
      //if (num.repreQ < RANGO_INF || num.repreQ > RANGO_SUP) {
      //  printf("\nError: fuera de rango");
      //  continuar = 0;
      //}
}
} while (!continuar);


res.valores = num;
for (int i=0; i<50; i++){
    res.input[i] = input[i];
}

return res;
}

// Q(16,15)
int convertidorQ(struct NumerosQ n){ 
  // Extraido y modificado del IncisoF
  /* convierte la parte entera a punto fijo multiplicando por la escala16 (2^16) */

  int resultado = n.entera * ESCALA16;

  /* realiza el mismo proceso con la parte fraccionaria (para mejorar precisión realiza un redondeo sumando el divisor/2 al numero antes de hacer la división, ya que si lo haces directo algunos números no se representan bien) */
  if (n.divisor > 1) {

    int num = n.fraccion * ESCALA16;

    if (n.signo > 0)
      num += n.divisor / 2;
  else
      num -= n.divisor / 2;

    /* se suma la parte fraccionaria al resultado (para convertirla de entero a decimales se divide por el divisor) */
  resultado += num / n.divisor;
}

  /* multiplica por +-1 para darle signo al numero */
resultado *= n.signo;

return resultado;
}