# IDL - Trabajos Practicos

Facultad de Ingeniería - UNLP
E1301 – E0301 Introducción a los Sistemas Lógicos y Digitales
Curso 2026 - Trabajo Entregable 0

### Fecha de entrega- La presente tarea tiene fecha de entrega el próximo 8 de abril
Lineamientos generales- Se sugiere realizar la entrega como un informe donde se contesten las preguntas realizadas junto con los detalles de la explicación, diagramas, gráficos, cuentas, demostraciones, etc. Por otra parte deben entregar los programas fuente en un formato que pueda ser fácilmente revisado, editado, compilado y ejecutado en el aula. Evaluación- La tarea será evaluada y los alumnos deberán defender el trabajo realizado frente a los docentes asignados

## Descripción
Sabemos que la ecuación de una recta es y=mx+b
En este caso queremos explorar la precisión y rango de valores que pueden obtenerse al trabajar con la ecuación de la recta con representación en punto fijo. Se adopta para m una representación Q (0,15) y para b una representación Q (7,8) mientras que x e y se van a representar en variables de punto fijo de 32 bits con signo

#### a. ¿cuál es el rango de representación de valores de m ?

La representación de $m$ es $Q(0,15)$. Siendo $a = 0$ y $b = 15$:

$$2^a-2^{-b}=2^0-2^{-15}=1-2^{-15}$$

$m$ tiene un rango de representación que va de $-(1-2^{-15})$ a $+(1-2^{-15})$.

#### b. ¿cuál es el rango de representaciones de valores de b?

La representación de $b$ es $Q(7,8)$. Siendo $a = 7$ y $b = 8$:

$$2^a-2^{-b}=2^7-2^{-8}=128-0,00390625=127,99609375$$

$b$ tiene un rango de representación que va de $-127,99609375$ a $+127,99609375$.
  
#### c. Elija una representación Q ( c ,d ) para x y para y tal que tanto m como b puedan representarse usando la misma representación sin pérdida de cifras significativas. Indique cuáles serían los desplazamientos y/o máscaras que debe utilizar para ubicar las variables.

Dado que almacenaremos $x$ e $y$ en variables de 32 bits con signo, tenemos $N=31$ bits para la representación. Queremos no perder cifras significativas al convertir $m$ y $b$ a $Q(c,d)$.  
La mayor cantidad de bits enteros que necesitamos viene dada por $c=Máx(a_m,a_b)=Máx(0,7)=7$.  
La mayor cantidad de bits fraccionarios que necesitamos viene dada por $d=Máx(b_m,b_b)=Máx(15,8)=15$.  
$7+15=22<31$, por lo que nos sobran $31-22=9$ bits, los cuales aprovecharemos para extender el rango de la parte entera, quedando $c=7+9=16$ y entonces $Q(16,15)$.

$m$ tiene la misma cantidad de bits menos significativos que $Q(16,15)$, por lo que la conversión puede hacerse de manera directa, sin desplazamientos, únicamente cuidando de conservar el signo.

Para convertir $b$ a $Q(16,15)$, dado que tiene solo 8 bits fraccionarios, es necesario desplazarlo 7 bits a la izquierda luego de convertirlo a 32 bits portando el signo.
  
#### d. ¿Cuál va a ser el rango de valores que pueden representarse en x y en y?

La representación de $x$ e $y$ es $Q(16,15)$. Siendo $a = 16$ y $b = 15$:

$$2^a-2^{-b}=2^{16}-2^{-15}=65536-2^{-15}$$

$x$ e $y$ tienen un rango de representación que va de $-(65536-2^{-15})$ a $+(65536-2^{-15})$.
  
#### e. De acuerdo con la ecuación de la recta y tomando casos límites respecto a los valores de las constantes m y b, por ejemplo el mínimo valor negativo o el máximo valor positivo, a qué valores debería acotarse x para que usando la representación elegida los valores de y obtenidos no produzcan overflow.
  
---

  f. Escriba un programa en lenguaje de programación C que permita el ingreso de un valor expresado en notación decimal ±eee.ffff y lo convierta a representación en punto fijo de 16 bits Q(7,8). El programa debe validar la entrada y determinar si el número ingresado está dentro del rango representable. La salida debe expresarse en Hexadecimal (0xHHHH)
  
  g. Escriba otro programa que dado un número expresado en punto fijo de 16 bits Q(7,8) exprese el valor decimal equivalente eee.ffff. La entrada debe ser un numero hexadecimal expresado en la forma 0xHHHH que debe ser validada.
  
  h. Escriba un programa que permita el ingreso de los valores de m, b y x en forma decimal y muestre su representación en punto fijo en formato hexadecimal validando la entrada como en los puntos anteriores. Luego realizando todas las operaciones en punto fijo con las representaciones adoptadas calcule el valor de la ordenada y y lo muestre en punto fijo en forma hexadecimal y en decimal.

---

### Todos los programas se deben escribir en lenguaje de programación C

En ninguno de los casos se pueden utilizar variables de tipo float o double ni funciones incluidas en math.h o float.h
