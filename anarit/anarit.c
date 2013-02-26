/*-------------------------------------------------------------------------
 * Fichero:  anarit.c
 * Autor:    Pedro Reina <pedro@pedroreina.org>
 * Fecha:    X.27.3.2002 (adaptación del código original de 1992)
 *           Correcciones J.13.5.2004
 * Objetivo: Averiguar si es posible obtener un número Meta usando N números
 *           (cada uno una vez o ninguna) y las cuatro operaciones elementales;
 *           si no se puede, el programa debe dar el número más aproximado
 *           posible (por exceso o por defecto). En cualquier caso se debe dar
 *           la operación que hay que realizar para obtener el número
 * Entradas: Los N números y el número Meta
 * Salidas:  Primera línea: número de nodos de 4 números diferentes
 *           Segunda línea: número de nodos de 4 números generados
 *           Tercera línea: número obtenido
 *           Resto: las operaciones
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Licencia
 *
 * (c) 1992 Pedro Reina y EQ Sistemas Inteligentes
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation, version 2
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307 USA
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Ficheros de cabecera
 *-----------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*-------------------------------------------------------------------------
 * Tipos de usuario
 *-----------------------------------------------------------------------*/

typedef char           logico;
typedef unsigned long  entero;
typedef char           cadena[50];
typedef short int      contador;
typedef entero        *nodo;

/*-------------------------------------------------------------------------
 * Definición de constantes
 *-----------------------------------------------------------------------*/

#define N 6                     /* Debe estar entre 3 y 6                */
#define NOD_MAXIMO 2400         /* Máximo número de nodos con 4 elementos
                                   que se pueden generar a partir de un
                                   nodo con 6 elementos                  */

#define SI  1
#define NO  0

#define NULO '\0'

#define SUMA      0
#define RESTA     1
#define PRODUCTO  2
#define COCIENTE  3

#define SEPARADOR ","

/*-------------------------------------------------------------------------
 * Definición de macros
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * MACRO:    Distancia()
 * OBJETIVO: Calcular la distancia entre dos enteros
 * ENTRADAS: Los dos enteros
 * SALIDAS:  La diferencia
 * ALGORITMO: Devolver la diferencia entre el mayor y el menor
 *-----------------------------------------------------------------------*/

#define Distancia(a,b) ( (a)>(b) ? ((a)-(b)) : ((b)-(a)) )

/*-------------------------------------------------------------------------
 * MACRO:    Cad_ConvierteEntero()
 * OBJETIVO: Convertir un número entero en una cadena
 * ENTRADAS: La cadena y el número
 * SALIDAS:  La cadena
 *-----------------------------------------------------------------------*/

#define Cad_ConvierteEntero(c,n) sprintf((c),"%ul",(n))

/*-------------------------------------------------------------------------
 * MACRO:    Cad_Copia()
 * OBJETIVO: Copiar una cadena en otra
 * ENTRADAS: La cadena destino y la cadena origen
 * SALIDAS:  La cadena destino
 *-----------------------------------------------------------------------*/

#define Cad_Copia(d,o) strcpy((d),(o))

/*-------------------------------------------------------------------------
 * MACRO:    Cad_Une()
 * OBJETIVO: Unir una cadena con otra
 * ENTRADAS: La cadena destino y la cadena origen
 * SALIDAS:  La cadena destino
 *-----------------------------------------------------------------------*/

#define Cad_Une(d,o) strcat((d),(o))

/*-------------------------------------------------------------------------
 * MACRO:    CadenaAEntero()
 * OBJETIVO: Convertir una cadena en un número entero
 * ENTRADAS: La cadena
 * SALIDAS:  El número
 *-----------------------------------------------------------------------*/

#define CadenaAEntero(c)  ((entero)(atoi(c)))

/*-------------------------------------------------------------------------
 * MACRO:    EsOperacion()
 * OBJETIVO: Decidir si un carácter representa una operación
 * ENTRADAS: El carácter
 * SALIDAS:  Lógica: SI si lo es, NO en caso contrario
 *-----------------------------------------------------------------------*/

#define EsOperacion(c) ((c=='+')||(c=='-')||(c=='*')||(c=='/'))

/*-------------------------------------------------------------------------
 * MACRO:    EsSeparador()
 * OBJETIVO: Decidir si un carácter es el separador
 * ENTRADAS: El carácter
 * SALIDAS:  Lógica: SI si lo es, NO en caso contrario
 *-----------------------------------------------------------------------*/

#define EsSeparador(c)  (SEPARADOR[0]==c)

/*-------------------------------------------------------------------------
 * Declaración de funciones
 *-----------------------------------------------------------------------*/

logico Busca();                   /* Busca la solución del problema      */
logico BuscaEnDos();              /* Busca la solución del problema
                                     en los nodos con dos elementos      */
void   CambiaMejor();             /* Almacena la solución más aproximada */
char  *Cam_Concatena();           /* Une dos caminos con una operación   */
nodo   Nod_Ordena();              /* Ordena un nodo                      */
logico Nod_Pertenece();           /* Informa si un nodo está ya anotado  */
void   Nod_Inserta();             /* Anota un nodo                       */
char  *Explica();                 /* Da las operaciones de la solución   */

char *Cad_Trozo();                /*  Extrae una cadena de otra          */

/*-------------------------------------------------------------------------
 * Variables globales
 *-----------------------------------------------------------------------*/

entero Meta;            /*  El número que hay que alcanzar               */
entero Mejor;           /*  El número más aproximado encontrado hasta
                            el momento                                   */
cadena MejorCamino;     /*  Las operaciones que hay que realizar para
                            obtener el número Mejor                      */
entero Diferencia;      /*  El valor absoluto de la diferencia entre
                            Meta y Mejor                                 */

contador Nod_Total;     /*  N£mero total de nodos generados              */
contador Nod_Visto;     /*  N£mero de nodos distintos almacenados        */
                        /*  Estos contadores toman el valor inicial -1,
                            y el valor 0 ya indica que hay un nodo       */

entero Comprobado[NOD_MAXIMO][N-2];       /* Para almacenar los nodos
                                             comprobados                 */

/*-------------------------------------------------------------------------
 * Definición del objeto Calculadora (Cal)
 *-----------------------------------------------------------------------*/

entero Cal_Pila[N];      /*  Almacena los números                        */

/*-------------------------------------------------------------------------
 * Declaración de funciones del objeto Calculadora
 *-----------------------------------------------------------------------*/

entero Cal_Inicia();      /*  Prepara la calculadora                     */
entero Cal_Opera();       /*  Realiza una operación                      */
entero Cal_Inserta();     /*  Inserta un número                          */

/*-------------------------------------------------------------------------
 * Programa principal
 *
 * Entradas: El usuario introduce los N números y el número Meta
 * Salidas:  El número más aproximado que se haya encontrado y las opera-
 *           ciones para obtenerlo
 * Algoritmo: Pedir N números y rellenar Lista con ellos
 *            Pedir el Meta
 *            Ordenar Lista
 *            Rellenar Camino con los N números como tiras de caracteres
 *            Considerar como mejor hasta el momento el primer número
 *            Dar valor inicial a Nod_Total y Nod_Visto
 *            Si Diferencia no es cero
 *              Hacer Exito = Busca (Lista,Camino)
 *            Si es cero, hacer Exito SI
 *            Mostrar Exito
 *            Mostrar Mejor y MejorCamino
 *-----------------------------------------------------------------------*/

int main (int Narg, char *Arg[])
  {
  contador i;
  entero Lista[N];
  cadena Camino[N];
  logico Exito;

  for ( i=0 ; i<N ; i++ )
    { Lista[i] = CadenaAEntero (Arg[i+1]); }
  Meta = CadenaAEntero (Arg[N+1]);

  Nod_Ordena (Lista);
  for ( i=0 ; i<N ; i++ )
    { Cad_ConvierteEntero(Camino[i],Lista[i]); }

  CambiaMejor (Lista[0],Camino[0]);
  Nod_Total = -1;
  Nod_Visto = -1;

  if ( Diferencia )
    { Exito = Busca (Lista,Camino); }
  else
    { Exito = SI; }

  printf ( "%d\n%d\n%lu", Nod_Visto+1, Nod_Total+1, Mejor);
  printf ( "\n" );
  Explica (MejorCamino);
  printf ( "\n" );

  return (0);
  }

/*-------------------------------------------------------------------------
 * Función:  Busca (L,C)
 * Objetivo: Decidir si es posible alcanzar el número Meta
 *           Durante la b£squeda, almacenar el más aproximado
 * Entradas: Una lista L de números de partida y una lista de cadenas C
 *           que indican las operaciones que se han realizado para obtener
 *           los números (los "caminos")
 * Nota:     Un cero en la lista L indica que en esa posición no hay número
 * Salidas:  Lógica, seg£n sea posible alcanzar Meta o no. Las variables
 *           globales Mejor, MejorCamino, Diferencia y Nod_Visto pueden quedar
 *           modificadas
 * Algoritmo: Dar a Exito el valor inicial NO
 *            Dar a Elemento el valor inicial 0
 *            Mientras no haya Exito, para cada elemento de L
 *              Si es más proximo a Meta que Mejor
 *                Cambiar Mejor
 *                Si es igual a Meta, hacer Exito SI
 *              Incrementar Elemento
 *            Hacer Comprobado NO
 *            Si Elemento es N-2
 *              Si L ha sido comprobado ya, hacer Comprobado SI
 *            Si no ha habido Exito y Elemento es 2
 *              Hacer Exito = BuscaEnDos (L,C)
 *            Si no ha habido Exito, en L hay más de dos elementos
 *                                   y Comprobado es NO
 *              Mientras no haya Exito, para cada pareja de L2
 *                Copiar L en L2 y C en C2
 *                Hacer A primer elemento de la pareja, CaminoA su camino
 *                Hacer B segundo elemento de la pareja, CaminoB su camino
 *                Borrar B de la lista L2 y de C2
 *                Mientras no haya Exito, para cada operación (+,-,*,/)
 *                  Si es posible realizar la operación entre A y B
 *                    Sustituir en L2 el elemento A por el resultado de
 *                                   operar A y B
 *                    Sustituir en C2 CaminoA por la cadena formada con
 *                                   CaminoA, CaminoB, operación
 *                    Hacer Exito = Busca (L2,C2)
 *            Si Elemento es N-2, almacenar el nodo
 *            Devolver el valor de Exito
 *-----------------------------------------------------------------------*/
logico Busca (L,C)
entero L[N];
cadena C[N];
  {
  entero   L2[N];
  entero   Lo[N];
  cadena   C2[N];
  logico   Exito;
  logico   Comprobado;
  contador Elemento, Operacion, i, j, k;
  entero   A, B;
  cadena   CaminoA, CaminoB;

  Exito = NO;
  Elemento = 0;

  for ( i=0 ; i<N && !Exito ; i++ )
    {
    if ( L[i] )
      {
      if ( Distancia ( L[i],Meta ) < Diferencia )
        {
        CambiaMejor ( L[i], C[i] );
        if ( L[i]==Meta )
          { Exito = SI; }
        }
      Elemento++;
      }
    }

  Comprobado = NO;
  if ( Elemento == N-2 )
    {
    for ( k=0 ; k<N ; k++ )
      { Lo[k] = L[k]; }
    Nod_Ordena(Lo);
    Comprobado = Nod_Pertenece(Lo);
    }

  if ( !Exito && Elemento == 2 )
    { Exito = BuscaEnDos (L,C); }

  if ( !Exito && Elemento>2 && !Comprobado )
    {
    for ( i=0 ; i<N-1 && !Exito ; i++ )
      {
      if ( L[i] )
        {
        for ( j=i+1 ; j<N && !Exito ; j++ )
          {
          if ( L[j] )
            {
            for ( k=0 ; k<N ; k++ )
              {
              L2[k] = L[k];
              Cad_Copia(C2[k],C[k]);
              }

            A = L2[i]; Cad_Copia(CaminoA,C2[i]);
            B = L2[j]; Cad_Copia(CaminoB,C2[j]);
            L2[j] = 0; C2[j][0] = NULO;
            for ( Operacion=SUMA ; Operacion<=COCIENTE && !Exito ;
                                   Operacion++ )
              {
              switch ( Operacion )
                {
                case SUMA:
                  L2[i] = A+B;
                  Cam_Concatena ( C2[i], CaminoA, "+", CaminoB );
                  Exito = Busca (L2,C2);
                  break;
                case RESTA:
                  if ( A>B )
                    {
                    L2[i] = A-B;
                    Cam_Concatena ( C2[i], CaminoA, "-", CaminoB );
                    Exito = Busca (L2,C2);
                    }
                  else if ( B>A )
                    {
                    L2[i] = B-A;
                    Cam_Concatena ( C2[i], CaminoB, "-", CaminoA );
                    Exito = Busca (L2,C2);
                    }
                  break;
                case PRODUCTO:
                  L2[i] = A*B;
                  Cam_Concatena ( C2[i], CaminoA, "*", CaminoB );
                  Exito = Busca (L2,C2);
                  break;
                case COCIENTE:
                  if ( (A % B) == 0 )
                    {
                    L2[i] = A/B;
                    Cam_Concatena ( C2[i], CaminoA, "/", CaminoB );
                    Exito = Busca (L2,C2);
                    }
                  else if ( (B % A) == 0 )
                    {
                    L2[i] = B/A;
                    Cam_Concatena ( C2[i], CaminoB, "/", CaminoA );
                    Exito = Busca (L2,C2);
                    }
                  break;
                } /* Fin del switch        */
              } /* Fin del for Operacion */
            } /* Fin del if    */
          } /* Fin del for j */
        } /* Fin del if    */
      } /* Fin del for i */
    } /* Fin del if    */

  if ( Elemento == N-2 )
    {
    if ( !Comprobado )
      { Nod_Inserta(Lo); }
    Nod_Total++;
    }

  return ( Exito );
  }

/*-------------------------------------------------------------------------
 * Funcion:  BuscaEnDos (L,C)
 * Objetivo: Decidir si es posible alcanzar el número Meta partiendo de un
 *             nodo con dos elementos
 *           Durante la b£squeda, almacenar el más aproximado
 * Entradas: Una lista L de números de partida y una lista de cadenas C
 *           que indican las operaciones que se han realizado para obtener
 *           los números (los "caminos")
 * Nota:     Un cero en la lista L indica que en esa posición no hay número
 * Salidas:  Lógica, seg£n sea posible alcanzar Meta o no. Las variables
 *           globales Mejor, MejorCamino y Diferencia pueden quedar
 *           modificadas
 * Algoritmo: Dar a Exito el valor inicial NO
 *            Hallar Primero y Segundo, ¡ndices de los elementos
 *            Mientras no haya Exito, para cada operación (+,-,*,/)
 *              Si es posible realizar la operación entre los elementos
 *                Si es más proxima a Meta que Mejor
 *                  Cambiar Mejor, hallando el nuevo camino
 *                  Si es igual a Meta, hacer Exito SI
 *            Devolver el valor de Exito
 *-----------------------------------------------------------------------*/
logico BuscaEnDos (L,C)
entero L[N];
cadena C[N];
  {
  logico Exito = NO;
  logico TengoElPrimero = NO;
  contador Primero, Segundo;
  entero Num;
  cadena Camino;
  contador i, Operacion;

  Primero = 0; Segundo = 0;
  for ( i=0 ; !Segundo ; i++ )
    {
    if ( L[i] )
      {
      if ( !TengoElPrimero )
        {
        Primero = i;
        TengoElPrimero = SI;
        }
      else
        { Segundo = i; }
      } /* Fin del if   */
    } /* Fin del for i */

  for ( Operacion=SUMA ; Operacion<=COCIENTE && !Exito ;
                         Operacion++ )
    {
    switch ( Operacion )
      {
      case SUMA:
        Num = L[Primero]+L[Segundo];
        if ( Distancia ( Num,Meta ) < Diferencia )
          {
          Cam_Concatena ( Camino, C[Primero], "+", C[Segundo] );
          CambiaMejor ( Num, Camino );
          if ( Num==Meta )
            { Exito = SI; }
          }
        break;
      case RESTA:
        if ( L[Primero]>L[Segundo] )
          {
          Num = L[Primero]-L[Segundo];
          if ( Distancia ( Num,Meta ) < Diferencia )
            {
            Cam_Concatena ( Camino, C[Primero], "-", C[Segundo] );
            CambiaMejor ( Num, Camino );
            if ( Num==Meta )
              { Exito = SI; }
            }
          }
        else if ( L[Segundo]>L[Primero] )
          {
          Num = L[Segundo]-L[Primero];
          if ( Distancia ( Num,Meta ) < Diferencia )
            {
            Cam_Concatena ( Camino, C[Segundo], "-", C[Primero] );
            CambiaMejor ( Num, Camino );
            if ( Num==Meta )
              { Exito = SI; }
            }
          }
        break;
      case PRODUCTO:
        Num = L[Primero]*L[Segundo];
        if ( Distancia ( Num,Meta ) < Diferencia )
          {
          Cam_Concatena ( Camino, C[Primero], "*", C[Segundo] );
          CambiaMejor ( Num, Camino );
          if ( Num==Meta )
            { Exito = SI; }
          }
        break;
      case COCIENTE:
        if ( (L[Primero] % L[Segundo]) == 0 )
          {
          Num = L[Primero]/L[Segundo];
          if ( Distancia ( Num,Meta ) < Diferencia )
            {
            Cam_Concatena ( Camino, C[Primero], "/", C[Segundo] );
            CambiaMejor ( Num, Camino );
            if ( Num==Meta )
              { Exito = SI; }
            }
          }
        else if ( (L[Segundo] % L[Primero]) == 0 )
          {
          Num = L[Segundo]/L[Primero];
          if ( Distancia ( Num,Meta ) < Diferencia )
            {
            Cam_Concatena ( Camino, C[Segundo], "/", C[Primero] );
            CambiaMejor ( Num, Camino );
            if ( Num==Meta )
              { Exito = SI; }
            }
          }
        break;
      } /* Fin del switch        */
    } /* Fin del for Operacion */

  return (Exito);
  }

/*-------------------------------------------------------------------------
 * Función:  CambiaMejor (Nuevo,NuevoCamino)
 * Objetivo: Cambiar los valores de Mejor y MejorCamino
 * Entradas: Los nuevos valores
 * Salidas:  Las variables globales Mejor, MejorCamino y Diferencia quedan
 *           modificadas
 *-----------------------------------------------------------------------*/

void CambiaMejor (Nuevo,NuevoCamino)
entero Nuevo;
cadena NuevoCamino;
  {
  Mejor = Nuevo; Cad_Copia (MejorCamino,NuevoCamino);
  Diferencia = Distancia ( Mejor,Meta );
  }

/*-------------------------------------------------------------------------
 * Función:  Cam_Concatena()
 * Objetivo: Unir dos caminos con el signo de una operación en RPN
 * Entradas: Cadena destino, primer camino, operación, y segundo camino
 * Salidas:  La cadena resultante de unir todo
 * Algoritmo: Copiar en Aux el separador
 *            Añadir a Aux el segundo camino
 *            Añadir a Aux el separador
 *            Añadir a Aux la operacion
 *            Copiar en Destino el primer camino
 *            Añadir a Destino Aux
 *            Devolver Destino
 *-----------------------------------------------------------------------*/
char *Cam_Concatena(Destino,Primero,Operacion,Segundo)
char Destino[];
char Primero[];
char Operacion[];
char Segundo[];
  {
  cadena Aux;

  Cad_Copia (Aux,SEPARADOR);
  Cad_Une (Aux,Segundo);
  Cad_Une (Aux,SEPARADOR);
  Cad_Une (Aux,Operacion);
  Cad_Copia (Destino,Primero);
  Cad_Une (Destino,Aux);

  return (Destino);
  }

/*-------------------------------------------------------------------------
 * Función:  Nod_Ordena()
 * Objetivo: Ordenar en orden decreciente los elementos de un nodo
 * Entradas: Un nodo
 * Salidas:  El nodo de entrada queda modificado. También se devuelve.
 * Algoritmo: Por inserción
 *-----------------------------------------------------------------------*/
nodo Nod_Ordena(L)
entero L[N];
  {
  contador i, j;
  entero   num;

  for ( i=1 ; i<N ; i++ )
    {
    num = L[i];
    for ( j=i-1 ; j>=0 && L[j]<num ; j-- )
      { L[j+1] = L[j]; }
    L[j+1] = num;
    }

  return (L);
  }

/*-------------------------------------------------------------------------
 * Función:  Nod_Pertenece()
 * Objetivo: Informar si un nodo ya ha sido anotado
 * Entradas: Un nodo
 * Salidas:  Lógica: SI si el nodo está anotado; NO, si no
 * Algoritmo:
 *     Hacer Encontrado NO
 *     Para cada elemento de Comprobado, mientras no Encontrado
 *        Hacer VaSiendoIgual SI
 *        Para cada elemento del nodo, mientras VaSiendoIgual
 *           Si no se encuentra en Comprobado[i]
 *              Hacer VaSiendoIgual NO
 *        Hacer Encontrado igual a VaSiendoIgual
 *     Devolver Encontrado
 *-----------------------------------------------------------------------*/
logico Nod_Pertenece(L)
nodo L;
  {
  logico Encontrado = NO;
  logico VaSiendoIgual;
  contador i, j;

  for ( i=0 ; i<=Nod_Visto && !Encontrado ; i++ )
    {
    VaSiendoIgual = SI;
    for ( j=0 ; j<N-2 && VaSiendoIgual ; j++ )
      {
        if ( L[j] != Comprobado[i][j] )
          { VaSiendoIgual = NO; }
      }
    Encontrado = VaSiendoIgual;
    }
  return ( Encontrado );
  }

/*-------------------------------------------------------------------------
 * Función:  Nod_Inserta()
 * Objetivo: Anotar un nodo como ya comprobado
 * Entradas: Un nodo
 * Salidas:  La variable global Nod_Visto queda modificada
 * Algoritmo:
 *     Incrementar Nod_Visto
 *     Hacer Comprobado[Nod_Visto] = nodo de entrada
 *-----------------------------------------------------------------------*/
void Nod_Inserta(L)
nodo L;
  {
  contador i;

  Nod_Visto++;
  for ( i=0 ; i<N-2 ; i++ )
    { Comprobado[Nod_Visto][i] = L[i]; }
  }

/*-------------------------------------------------------------------------
 * Función:  Explica()
 * Entradas: Una cadena en notación RPN
 * Salidas:  La cadena
 * Algoritmo:
 *     Hacer Comienzo 0
 *     Hacer Operacion NO
 *     Iniciar la calculadora
 *     Para cada carácter de la expresión, de ¡ndice i
 *       Si es una operación
 *         Hacer Cal_Opera() con ella
 *         Hacer Operación SI
 *         Hacer Comienzo i+1
 *       Si es el separador
 *         Si Operacion es NO
 *           Hacer Fin i-1
 *           Extraer el número de la expresión
 *           Hacer Cal_Inserta() con el número
 *         Hacer Comienzo i+1
 *       Si es una cifra
 *         Hacer Operacion NO
 *     Devolver la cadena
 *-----------------------------------------------------------------------*/

char *Explica (Expresion)
char Expresion[];
  {
  contador Comienzo, Fin, i;
  logico   Operacion;
  char     c;
  entero   Num;
  cadena   Aux;

  Comienzo = 0;
  Operacion = NO;
  Cal_Inicia();

  for ( i=0 ; c=Expresion[i] ; i++ )
    {
    if ( EsOperacion(c) )
             {
             Cal_Opera(c);
             Operacion = SI;
             Comienzo = i+1;
             }
    else if ( EsSeparador(c) )
             {
             if ( !Operacion )
               {
               Fin = i-1;
               Cad_Trozo (Aux,Expresion,Comienzo,Fin);
               Num = CadenaAEntero (Aux);
               Cal_Inserta (Num);
               }
             Comienzo = i+1;
             }
    else
             { Operacion = NO; }
    }

  return (Expresion);
  }

/*-------------------------------------------------------------------------
 * Función:  Cad_Trozo()
 * Objetivo: Extraer una cadena de otra
 * Entradas: Cadena destino, cadena origen y puntos de comienzo y fin del
 *           corte
 * Salidas:  La cadena destino queda modificada y se devuelva
 * Algoritmo: Copiar los caracteres entre comienzo y fin y añadir NULO
 *-----------------------------------------------------------------------*/

char *Cad_Trozo (Destino, Origen, Comienzo, Fin)
cadena   Destino;
cadena   Origen;
contador Comienzo;
contador Fin;
  {
  contador i;

  for ( i=Comienzo ; i<=Fin ; i++ )
    {
    Destino[i-Comienzo] = Origen[i];
    }

  Destino[i-Comienzo] = NULO;

  return (Destino);
  }

/*-------------------------------------------------------------------------
 * Funciones del objeto Calculadora
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Función:   Cal_Inicia()
 * Objetivo:  Dar valores iniciales a las pilas de la calculadora
 * Entradas:  Ninguna
 * Salidas:   Las variables globales Cal_Pila y Cal_PilaLit quedan modificadas
 *            Se devuelve la profundidad de las pilas
 * Algoritmo: Poner los números a cero
 *-----------------------------------------------------------------------*/

entero Cal_Inicia()
  {
  contador i;

  for ( i=0 ; i<N ; i++ )
    { Cal_Pila[i] = 0; }

  return ( (entero)N );
  }

/*-------------------------------------------------------------------------
 * Función:  Cal_Inserta()
 * Objetivo: Insertar un número en las pilas
 * Entradas: El número
 * Salidas:  La variable global Cal_Pila queda modificada
 *           Se devuelve el número insertado
 * Algoritmo: Mover todos los niveles hacia arriba
 *            Poner el número en el nivel más bajo
 * Nota: Se pierde el valor más alto de las pilas
 *-----------------------------------------------------------------------*/

entero Cal_Inserta (Num)
entero Num;
  {
  contador i;

  for ( i=N-1 ; i>0 ; i-- )
    { Cal_Pila[i] = Cal_Pila[i-1]; }

  Cal_Pila[0] = Num;

  return (Num);
  }

/*-------------------------------------------------------------------------
 * Función:  Cal_Opera()
 * Objetivo: Realizar una operación
 * Entradas: Un carácter indicando la operación (+,-,*,/)
 * Salidas:  La variable global Cal_Pila queda modificada
 *           Se devuelve el número calculado
 * Algoritmo: Realizar la operación entre los niveles más bajos
 *            Escribir el resultado en el nivel más bajo
 *            Mostrar la operación
 *            Bajar los niveles
 * Nota: Se duplica el valor más alto de las pilas
 *-----------------------------------------------------------------------*/

entero Cal_Opera (Operacion)
char Operacion;
  {
  contador i;
  entero Num;

  switch ( Operacion )
    {
    case '+':
      Num = Cal_Pila[1]+Cal_Pila[0];
      break;
    case '-':
      Num = Cal_Pila[1]-Cal_Pila[0];
      break;
    case '*':
      Num = Cal_Pila[1]*Cal_Pila[0];
      break;
    case '/':
      Num = Cal_Pila[1]/Cal_Pila[0];
      break;
    }

  printf ( "%lu %c %lu = %lu;",
           Cal_Pila[1], Operacion, Cal_Pila[0], Num );

  Cal_Pila[0] = Num;

  for ( i=1 ; i<N-1 ; i++ )
    { Cal_Pila[i] = Cal_Pila[i+1]; }

  return (Num);
  }
