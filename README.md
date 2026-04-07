# IDL - Trabajos Practicos

Facultad de Ingeniería - UNLP
E1301 – E0301 Introducción a los Sistemas Lógicos y Digitales
Curso 2026 - Trabajo Entregable 0

### Fecha de entrega- La presente tarea tiene fecha de entrega el próximo 8 de abril
Lineamientos generales- Se sugiere realizar la entrega como un informe donde se contesten las preguntas realizadas junto con los detalles de la explicación, diagramas, gráficos, cuentas, demostraciones, etc. Por otra parte deben entregar los programas fuente en un formato que pueda ser fácilmente revisado, editado, compilado y ejecutado en el aula. Evaluación- La tarea será evaluada y los alumnos deberán defender el trabajo realizado frente a los docentes asignados

## Descripción
Sabemos que la ecuación de una recta es y=mx+b.
En este caso queremos explorar la precisión y rango de valores que pueden obtenerse al trabajar con la ecuación de la recta con representación en punto fijo. Se adopta para m una representación Q (0,15) y para b una representación Q (7,8) mientras que x e y se van a representar en variables de punto fijo de 32 bits con signo

#### a. ¿cuál es el rango de representación de valores de m ?

La representación de $m$ es $Q(0,15)$. Siendo $a = 0$ y $b = 15$, su rango es:

$$-2^a ≤ x ≤ +2^a-2^{-b}$$
$$-2^0 ≤ x ≤ +2^0-2^{-15}$$
$$-1 ≤ x ≤ +1-2^{-15}$$

$m$ tiene un rango de representación que va de $-1$ a $+(1-2^{-15}) ≈ +0.999969482421875$

#### b. ¿cuál es el rango de representaciones de valores de b?

La representación de $b$ es $Q(7,8)$. Siendo $a = 7$ y $b = 8$, su rango es:

$$-2^a ≤ x ≤ +2^a-2^{-b}$$
$$-2^7 ≤ x ≤ +2^7-2^{-8}$$
$$-128 ≤ x ≤ +128-0,00390625$$

$b$ tiene un rango de representación que va de $-128$ a $+127,99609375$.
  
#### c. Elija una representación Q ( c, d ) para x y para y tal que tanto m como b puedan representarse usando la misma representación sin pérdida de cifras significativas. Indique cuáles serían los desplazamientos y/o máscaras que debe utilizar para ubicar las variables.

Dado que almacenaremos $x$ e $y$ en variables de 32 bits con signo, tenemos $N=31$ bits para la representación. Queremos no perder cifras significativas al convertir $m$ y $b$ a $Q(c,d)$.  
La mayor cantidad de bits enteros que necesitamos viene dada por $c=\text{Máx}(a_m,a_b)=\text{Máx}(0,7)=7$.  
La mayor cantidad de bits fraccionarios que necesitamos viene dada por $d=\text{Máx}(b_m,b_b)=\text{Máx}(15,8)=15$.  
$7+15=22<31$, por lo que nos sobran $31-22=9$ bits, los cuales aprovecharemos para extender el rango de la parte entera, quedando $c=7+9=16$ y entonces $Q(16,15)$.

$m$ tiene la misma cantidad de bits menos significativos que $Q(16,15)$, por lo que la conversión puede hacerse de manera directa, sin desplazamientos, únicamente cuidando de conservar el signo.

Para convertir $b$ a $Q(16,15)$, dado que tiene solo 8 bits fraccionarios, es necesario desplazarlo 7 bits a la izquierda luego de convertirlo a 32 bits portando el signo.
  
#### d. ¿Cuál va a ser el rango de valores que pueden representarse en x y en y?

La representación de $x$ e $y$ es $Q(16,15)$. Siendo $a = 16$ y $b = 15$, su rango es:

$$-2^a ≤ x ≤ +2^a-2^{-b}$$
$$-2^{16} ≤ x ≤ +2^{16}-2^{-15}$$
$$-65536 ≤ x ≤ +65536-2^{-15}$$

$x$ e $y$ tienen un rango de representación que va de $-65536$ a $+(65536-2^{-15})$.
  
#### e. De acuerdo con la ecuación de la recta y tomando casos límites respecto a los valores de las constantes m y b, por ejemplo el mínimo valor negativo o el máximo valor positivo, a qué valores debería acotarse x para que usando la representación elegida los valores de y obtenidos no produzcan overflow.

Operando para despejar $x$ desde la ecuación de la recta:

$$y=m·x+b$$
$$x=\dfrac{y-b}{m}$$

Se quieren encontrar los valores extremos de $x$ fuera de los cuales se producirá overflow mediante la suma en $y_{máx}$ como por la resta en $y_{mín}$. La metodología consiste en reemplazar en la última ecuación con los valores extremos de $y$, $m$ y $b$, y se determinará como valores para acotar $x$ a los siguientes:
* $x_{máx}$ será el menor valor positivo obtenido
* $x_{mín}$ será el mayor valor negativo (menor en valor absoluto) obtenido

Ambos se truncan al valor inmediatamente menor en módulo que pueda ser representado en $Q(16,15)$, y recordar que el límite de representación de $x$ es el mismo que el de $y$.

Para $y_{máx} = 2^{16} - 2^{-15} = 65.535,999969482421875$:

| $x=\dfrac{y_{máx}-b}{m}$ | $m_{mín} = -1$ | $m_{máx} = 1-2^{-15}$ |
|-------------------------:|----------------|-----------------------|
|       $b_{mín} = -2^{7}$ | Real: -65.536,007781982421875<br>Representado: -65.536 (overflow en $x$) | Real: ≈65.538,007843256935331<br>Representado: Representado: -65.536 (overflow en $x$) |
| $b_{máx} = 2^{7}-2^{-8}$ | Real: -65.408,003875732421875<br>Representado: **-65.408,003875732421875** | Real: ≈65.410,000030518509475<br>Representado: 65.410,000030517578125 |

Para $y_{mín} = -2^{16} = 65.536$:

| $x=\dfrac{y_{mín}-b}{m}$ | $m_{mín} = -1$ | $m_{máx} = 1-2^{-15}$ |
|-------------------------:|----------------|-----------------------|
|       $b_{mín} = -2^{7}$ | Real: 65.408<br>Representado: **65.408** | Real: ≈-65.409,996154667806024 <br>Representado: -65.409,996124267578125 |
| $b_{máx} = 2^{7}-2^{-8}$ | Real: 65.663,99609375<br>Representado: 65.535,999969482421875 (overflow en $x$) | Real: ≈-65.666,000061037018951<br>Representado: -65.536 (overflow en $x$) |

De estas tablas se obtienen las siguientes conclusiones:
* $x$ debe ser acotado entre:
  * $x_{mín} = -2^{16} + 2^7 - 2^{-8} + 2^{-15} =$ $-65.408,003875732421875$
  * $x_{máx} = 2^{16} - 2^7 = 65.408$
* Ambos valores se obtuvieron con $m_{mín}$ dado que $|m_{mín}|>|m_{máx}|$.
* Utilizar los valores extremos de $y$ y $b$ del signo contrario produjo overflow para la variable $x$. Como la operación es $y-b$, y además $x$ e $y$ tienen el mismo rango de representación, si $b$ e $y$ tienen signo contrario entonces $|y-b|>|x|$. Estos casos no aparecerán en la práctica porque representan puntos fuera del dominio de $x$, que es una de las entradas.
* Obedeciendo a la ley de los signos, y teniendo en cuenta la ecuación canónica $y=m·x+b$, se aprecia que los valores extremos para $x$ se obtuvieron cuando los términos $m·x$ y $b$ coincidían en signo, y como en ambos casos $m=$-1, $x_{máx}$ (positivo) se obtuvo con $b$ e $y$ negativos, y viceversa, $x_{mín}$ (negativo) se obtuvo con $b$ e $y$ positivos.

---

  f. Escriba un programa en lenguaje de programación C que permita el ingreso de un valor expresado en notación decimal ±eee.ffff y lo convierta a representación en punto fijo de 16 bits Q(7,8). El programa debe validar la entrada y determinar si el número ingresado está dentro del rango representable. La salida debe expresarse en Hexadecimal (0xHHHH)
  
  g. Escriba otro programa que dado un número expresado en punto fijo de 16 bits Q(7,8) exprese el valor decimal equivalente eee.ffff. La entrada debe ser un numero hexadecimal expresado en la forma 0xHHHH que debe ser validada.
  
  h. Escriba un programa que permita el ingreso de los valores de m, b y x en forma decimal y muestre su representación en punto fijo en formato hexadecimal validando la entrada como en los puntos anteriores. Luego realizando todas las operaciones en punto fijo con las representaciones adoptadas calcule el valor de la ordenada y y lo muestre en punto fijo en forma hexadecimal y en decimal.

---

### Todos los programas se deben escribir en lenguaje de programación C

En ninguno de los casos se pueden utilizar variables de tipo float o double ni funciones incluidas en math.h o float.h
