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
La mayor cantidad de bits enteros que necesitamos viene dada por $c=\text{Máx}(a_m,a_b)=\text{Máx}(0,7)=7$.  
La mayor cantidad de bits fraccionarios que necesitamos viene dada por $d=\text{Máx}(b_m,b_b)=\text{Máx}(15,8)=15$.  
$7+15=22<31$, por lo que nos sobran $31-22=9$ bits, los cuales aprovecharemos para extender el rango de la parte entera, quedando $c=7+9=16$ y entonces $Q(16,15)$.

$m$ tiene la misma cantidad de bits menos significativos que $Q(16,15)$, por lo que la conversión puede hacerse de manera directa, sin desplazamientos, únicamente cuidando de conservar el signo.

Para convertir $b$ a $Q(16,15)$, dado que tiene solo 8 bits fraccionarios, es necesario desplazarlo 7 bits a la izquierda luego de convertirlo a 32 bits portando el signo.
  
#### d. ¿Cuál va a ser el rango de valores que pueden representarse en x y en y?

La representación de $x$ e $y$ es $Q(16,15)$. Siendo $a = 16$ y $b = 15$:

$$2^a-2^{-b}=2^{16}-2^{-15}=65536-2^{-15}$$

$x$ e $y$ tienen un rango de representación que va de $-(65536-2^{-15})$ a $+(65536-2^{-15})$.
  
#### e. De acuerdo con la ecuación de la recta y tomando casos límites respecto a los valores de las constantes m y b, por ejemplo el mínimo valor negativo o el máximo valor positivo, a qué valores debería acotarse x para que usando la representación elegida los valores de y obtenidos no produzcan overflow.

La ecuación de la recta, reemplazando por los valores máximos, es la siguiente:

$$y_{máx}=m_{máx}·x_{máx}+b_{máx}$$

Donde:
* $y_{máx}=2^{16}-2^{-15}=65.535,999969482421875$
* $m_{máx}=1-2^{-15}=0,999969482421875$
* $b_{máx}=2^{7}-2^{-8}=127,99609375$

Operando para despejar $x_{máx}$:

$$x_{máx}=\dfrac{y_{máx}-b_{máx}}{m_{máx}}=\dfrac{(2^{16}-2^{-15})-(2^{7}-2^{-8})}{1-2^{-15}}=65.410,000030518509475...$$

El resultado puede truncarse para ser representado en $Q(16,15)$ como:

$$x_{máx}=2^{16}-2^7+2+2^{-15}=65.410,000030517578125$$
$$x_{máx}=0\\:1111\\:1111\\:1000\\:0010·0000\\:0000\\:0000\\:001$$

Y como un entero con signo de 32 bits: $x_{máx}=\text{0x7FC1\\:0001}$.

Tanto la ecuación de la recta como las representaciones utilizadas son simétricas respecto al eje de las abscisas, es decir, los valores máximos y mínimos que pueden tomar $m$, $b$, $x$ e $y$ son iguales en módulo. Si se usan los valores mínimos para $m$ y $b$, y atendiendo a la regla de los signos para el producto $m·x$, se demuestra que se puede vuelve a obtener $x_{máx}$:

Siendo:
* $y_{mín}=2^{16}-2^{-15}=-65.535,999969482421875$
* $m_{máx}=1-2^{-15}=-0,999969482421875$
* $b_{máx}=2^{7}-2^{-8}=-127,99609375$

$$y_{mín}=m_{mín}·x_{máx}+b_{mín}$$
$$|y_{mín}|=y_{máx}$$
$$|m_{mín}·x_{máx}+b_{mín}|=|m_{mín}·x_{máx}|+|b_{mín}|=|m_{mín}|·x_{máx}+|b_{mín}|=m_{máx}·x_{máx}+b_{máx}$$

Atendiendo al producto $m·x$ y al signo de $b$, si se quiere obtener $x_{mín}$ se lo debe conjugar con $m_{máx}$ y $b_{mín}$.

$$y_{mín}=m_{máx}·x_{mín}+b_{mín}$$

Y como $|y_{mín}|=y_{máx}$, entonces $x_{mín} = -x_{máx}$:

$$x_{mín}=-(2^{16}-2^7+2+2^{-15})=-65.410,000030517578125$$
$$x_{mín}=1\\:1111\\:1111\\:1000\\:0010·0000\\:0000\\:0000\\:001$$

Como un entero con signo de 32 bits: $x_{mín}=\text{0xFFC1\\:0001}$.

Las otras combinaciones arrojan valores menores en módulo para $y$ debido a que los términos $m·x$ y $b$ se oponen en signo, y por lo tanto no producen overflow.

---

  f. Escriba un programa en lenguaje de programación C que permita el ingreso de un valor expresado en notación decimal ±eee.ffff y lo convierta a representación en punto fijo de 16 bits Q(7,8). El programa debe validar la entrada y determinar si el número ingresado está dentro del rango representable. La salida debe expresarse en Hexadecimal (0xHHHH)
  
  g. Escriba otro programa que dado un número expresado en punto fijo de 16 bits Q(7,8) exprese el valor decimal equivalente eee.ffff. La entrada debe ser un numero hexadecimal expresado en la forma 0xHHHH que debe ser validada.
  
  h. Escriba un programa que permita el ingreso de los valores de m, b y x en forma decimal y muestre su representación en punto fijo en formato hexadecimal validando la entrada como en los puntos anteriores. Luego realizando todas las operaciones en punto fijo con las representaciones adoptadas calcule el valor de la ordenada y y lo muestre en punto fijo en forma hexadecimal y en decimal.

---

### Todos los programas se deben escribir en lenguaje de programación C

En ninguno de los casos se pueden utilizar variables de tipo float o double ni funciones incluidas en math.h o float.h
