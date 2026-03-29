# IDL - Trabajos Practicos

Facultad de Ingeniería - UNLP
E1301 – E0301 Introducción a los Sistemas Lógicos y Digitales
Curso 2026 - Trabajo Entregable 0

### Fecha de entrega- La presente tarea tiene fecha de entrega el próximo 8 de abril
Lineamientos generales- Se sugiere realizar la entrega como un informe donde se contesten las preguntas realizadas junto con los detalles de la explicación, diagramas, gráficos, cuentas, demostraciones, etc. Por otra parte deben entregar los programas fuente en un formato que pueda ser fácilmente revisado, editado, compilado y ejecutado en el aula. Evaluación- La tarea será evaluada y los alumnos deberán defender el trabajo realizado frente a los docentes asignados

## Descripción
Sabemos que la ecuación de una recta es y=mx+b
En este caso queremos explorar la precisión y rango de valores que pueden obtenerse al trabajar con la ecuación de la recta con representación en punto fijo. Se adopta para m una representación Q (0,15) y para b una representación Q (7,8) mientras que x e y se van a representar en variables de punto fijo de 32 bits con signo

  a. ¿cuál es el rango de representación de valores de m ?

  b. ¿cuál es el rango de representaciones de valores de b?
  
  c. Elija una representación Q ( c ,d ) para x y para y tal que tanto m como b puedan representarse usando la misma representación sin pérdida de cifras significativas. Indique cuáles serían los desplazamientos y/o máscaras que debe utilizar para ubicar las variables.
  
  d. ¿Cuál va a ser el rango de valores que pueden representarse en x y en y?
  
  e. De acuerdo con la ecuación de la recta y tomando casos límites respecto a los valores de las constantes m y b, por ejemplo el mínimo valor negativo o el máximo valor positivo, a qué valores debería acotarse x para que usando la representación elegida los valores de y obtenidos no produzcan overflow.
  
---

  f. Escriba un programa en lenguaje de programación C que permita el ingreso de un valor expresado en notación decimal ±eee.ffff y lo convierta a representación en punto fijo de 16 bits Q(7,8). El programa debe validar la entrada y determinar si el número ingresado está dentro del rango representable. La salida debe expresarse en Hexadecimal (0xHHHH)
  
  g. Escriba otro programa que dado un número expresado en punto fijo de 16 bits Q(7,8) exprese el valor decimal equivalente eee.ffff. La entrada debe ser un numero hexadecimal expresado en la forma 0xHHHH que debe ser validada.
  
  h. Escriba un programa que permita el ingreso de los valores de m, b y x en forma decimal y muestre su representación en punto fijo en formato hexadecimal validando la entrada como en los puntos anteriores. Luego realizando todas las operaciones en punto fijo con las representaciones adoptadas calcule el valor de la ordenada y y lo muestre en punto fijo en forma hexadecimal y en decimal.

---

### Todos los programas se deben escribir en lenguaje de programación C

En ninguno de los casos se pueden utilizar variables de tipo float o double ni funciones incluidas en math.h o float.h
