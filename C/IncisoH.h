#ifndef INCISOG_H_INCLUDED
#define INCISOG_H_INCLUDED

int IncisoG();

struct NumerosQ leerNumeros();
struct NumerosQ calcularY(struct NumerosQ m, struct NumerosQ b, struct NumerosQ x);
void imprimirValores(struct NumerosQ m, struct NumerosQ b, struct NumerosQ x);

#endif // INCISOG_H_INCLUDED
