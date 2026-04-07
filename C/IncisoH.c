#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "Exportador.c"

// IMPORTANTE
#define A 16
#define B 15

#define ESCALA16     (1 << B)
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
int aproximarLinea(struct NumerosQ m, struct NumerosQ b);

/*  h. Escriba un programa que permita el ingreso de los valores de m, b y x en forma decimal y muestre su representaciónen
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
    printf("\n -  5: aproximar recta con N valores de x y exportarlos a txt (reutiliza m y b).");
    printf("\n -  0: Salir.");
    printf("\nIngrese una opcion:");

    scanf("%d", &act);
    getchar();

    switch (act) {
    case 0:
      break;
    case 1:
      m = leerNumeros();
      printf("\nResultado decimal: %c%d.%d", m.valores.signo<0 ? '-' : '+', m.valores.entera, m.valores.fraccion);
      printf("\nResultado Q(16,15): 0x%08X", (uint32_t)m.valores.repreQ);
      break;
    case 2:
      b = leerNumeros();
      printf("\nResultado decimal: %c%d.%d", b.valores.signo<0 ? '-' : '+', b.valores.entera, b.valores.fraccion);
      printf("\nResultado Q(16,15): 0x%08X", (uint32_t)b.valores.repreQ);
      break;
    case 3:
      x = leerNumeros();
      printf("\nResultado decimal: %c%d.%d", x.valores.signo<0 ? '-' : '+', x.valores.entera, x.valores.fraccion);
      printf("\nResultado Q(16,15): 0x%08X", (uint32_t)x.valores.repreQ);
      break;
    case 4:
      y.valores = calcularY(m.valores, b.valores, x.valores);
      imprimirValores(m.valores, b.valores, x.valores, y.valores);
      break;
    case 5:
      if (aproximarLinea(m.valores,b.valores))
        printf("\nERROR APROXIMACION");
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

    // Calcular en 64 bits para evitar overflow intermedio
  int64_t temp = ((int64_t)m.repreQ * x.repreQ >> B) + b.repreQ;

    // Chequeo de overflow antes de usar el valor
  if (temp > INT32_MAX || temp < INT32_MIN) {
    printf("Overflow en calculo de y\n");

    y.repreQ = 0;
    y.signo = 1;
    y.entera = 0;
    y.fraccion = 0;
    y.divisor = 1 << B;

    return y;
  }

    // Ahora sí es seguro usarlo
  y.repreQ = (int)temp;

    // Determinar signo
  y.signo = (y.repreQ < 0) ? -1 : 1;

    // Valor absoluto
  int valor = (y.repreQ < 0) ? -y.repreQ : y.repreQ;

    // Parte entera
  y.entera = valor >> B;

    // Parte fraccionaria
  y.fraccion = valor & ((1 << B) - 1);

    // Divisor (escala)
  y.divisor = 1 << B;

  return y;
}

void imprimirValores(struct NumerosQ m, struct NumerosQ b, struct NumerosQ x, struct NumerosQ y) {
  printf("\n - Y = m * x + b:");
  printf("\n --- Decimal: %c%d.%d = %c%d.%d * %c%d.%d + %c%d.%d",
   y.signo < 0 ? '-' : '+', y.entera, y.fraccion,
   m.signo < 0 ? '-' : '+', m.entera, m.fraccion,
   x.signo < 0 ? '-' : '+', x.entera, x.fraccion,
   b.signo < 0 ? '-' : '+', b.entera, b.fraccion);
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
    }

    /* valida el rango*/
    if (num.entera > 65535) {
      printf("\nError: fuera de rango");
      continuar = 0;
    }
  } while (!continuar);


  num.repreQ = convertidorQ(num);
  res.valores = num;

  for (int i=0; i<50; i++){
    res.input[i] = input[i];
  }


  return res;
}

// Q(16,15)
int convertidorQ(struct NumerosQ n){ 

  printf("\nDEBUG:");
  printf("\nentera = %d", n.entera);
  printf("\nfraccion = %d", n.fraccion);
  printf("\ndivisor = %d", n.divisor);
  printf("\nescala = %d", ESCALA16);


  int resultado = n.entera * ESCALA16;

  if (n.divisor > 1) {
    int num = n.fraccion * ESCALA16;

    if (n.signo >= 0)
      num += n.divisor / 2;
    else
      num -= n.divisor / 2;

    resultado += num / n.divisor;
  }

    // aplicar signo al final
  resultado *= n.signo;

  return resultado;
}

int aproximarLinea(struct NumerosQ m, struct NumerosQ b){
  int cant = 0;
  printf("\n Ingrese el valor de N: ");
  scanf("%d", &cant);
  getchar();
  struct Datos aux;
  struct NumerosQ xAct, yAct;

  int mB, mD,
  bB, bD,
  xB[cant], xD[cant],
  yB[cant], yD[cant];

  mB = (m.signo < 0 ? -1 : 1) * m.entera;
  mD = m.fraccion;
  bB = (b.signo < 0 ? -1 : 1) * b.entera;
  bD = b.fraccion;


  for (int i=0; i<cant; i++){
    aux = leerNumeros();
    
    xAct = aux.valores;
    yAct = calcularY(m, b, xAct);;
    
    xB[i] = (xAct.signo < 0 ? -1 : 1) * xAct.entera;
    xD[i] = xAct.fraccion;
    yB[i] = (yAct.signo < 0 ? -1 : 1) * yAct.entera;
    yD[i] = yAct.fraccion;
  }

  // int exportador(int mi, int md, int bi, int bd, int dataXi[], int dataXd[], int dataYi[], int dataYd[], int size)
  exportador(mB, mD, bB, bD, xB, xD, yB, yD, cant);
  return 0;
}