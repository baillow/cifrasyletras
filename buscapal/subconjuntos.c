/*--------------------------------------------------------------------
 * Fichero:  subconjuntos.c
 * Objetivo: Generar subconjuntos de palabras
 * Fecha:    J.28.3.2002
 * Autor:    Pedro Reina <pedro@pedroreina.org>
 *------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Licencia
 *
 * (c) 2002 Pedro Reina
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

/*--------------------------------------------------------------------
 * Ficheros de cabecera
 *------------------------------------------------------------------*/

 /* Ninguno */

/*-------------------------------------------------------------------------
 * Declaración de macros constantes
 *-----------------------------------------------------------------------*/

#define NULO '\0'
#define N 9

/*-------------------------------------------------------------------------
 * Declaración de funciones
 *-----------------------------------------------------------------------*/

void Genera9();
void Genera8();
void Genera7();
void Genera6();
void Genera5();
void OrdenaPalabra (char *, int);

/*-------------------------------------------------------------------------
 * Variables globales
 *-----------------------------------------------------------------------*/

 /* Ninguna */

/*-------------------------------------------------------------------------
 * Definición de macros funciones
 *-----------------------------------------------------------------------*/

 /* Ninguno */

/*-------------------------------------------------------------------------
 * Programa principal
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Función:  main()
 * Objetivo: Generar subconjuntos de letras con las
 *           letras de un problema
 * Entradas: Una cadena y el número de letras del subconjunto
 * Salidas:  Se sacan por salida estándar las palabras encontradas
 *-----------------------------------------------------------------------*/
int main (int Narg, char *Arg[])
  {
  int Longitud;
  char Problema[N+1];

  strcpy (Problema, Arg[1]);
  Longitud = atoi(Arg[2]);

  switch ( Longitud )
    {
    case 9: Genera9 (Problema); break;
    case 8: Genera8 (Problema); break;
    case 7: Genera7 (Problema); break;
    case 6: Genera6 (Problema); break;
    case 5: Genera5 (Problema); break;
    }

  return ( 0 );
  }

/*-------------------------------------------------------------------------
 * Definición de funciones
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Función:  Genera9()
 * Objetivo: Generar las posibles claves que se pueden obtener
 *           de un problema que tengan longitud 9
 * Entradas: Una cadena con el problema
 * Salidas:  Por salida estándar
 *-----------------------------------------------------------------------*/
void Genera9 (char *Problema)
  {
  OrdenaPalabra (Problema,9);
  printf ("%s\n", Problema);
  }

/*-------------------------------------------------------------------------
 * Función:  Genera8()
 * Objetivo: Generar las posibles claves que se pueden obtener
 *           de un problema que tengan longitud 8
 * Entradas: Una cadena con el problema
 * Salidas:  Por salida estándar
 *-----------------------------------------------------------------------*/
void Genera8 (char *Problema)
  {
  int Quita1, i, j;
  char Palabra[N];

  for ( Quita1=0 ; Quita1<N ; Quita1++ )
    {
    for ( i=0 , j=0 ; Problema[i] ; i++ )
      {
      if ( i != Quita1 )
        { Palabra[j++] = Problema[i]; }
      }
    Palabra[j] = NULO;
    OrdenaPalabra (Palabra, 8);
    printf ("%s\n", Palabra);
    }
  }

/*-------------------------------------------------------------------------
 * Función:  Genera7()
 * Objetivo: Generar las posibles claves que se pueden obtener
 *           de un problema que tengan longitud 7
 * Entradas: Una cadena con el problema
 * Salidas:  Por salida estándar
 *-----------------------------------------------------------------------*/
void Genera7 (char *Problema)
  {
  int Quita1, Quita2, i, j;
  char Palabra[N];

  for ( Quita1=0        ; Quita1<N-1 ; Quita1++ ) {
  for ( Quita2=Quita1+1 ; Quita2<N   ; Quita2++ )
    {
    for ( i=0 , j=0 ; Problema[i] ; i++ )
      {
      if ( i != Quita1 && i != Quita2 )
        { Palabra[j++] = Problema[i]; }
      }
    Palabra[j] = NULO;
    OrdenaPalabra (Palabra, 7);
    printf ("%s\n", Palabra);
    }}
  }

/*-------------------------------------------------------------------------
 * Función:  Genera6()
 * Objetivo: Generar las posibles claves que se pueden obtener
 *           de un problema que tengan longitud 6
 * Entradas: Una cadena con el problema
 * Salidas:  Por salida estándar
 *-----------------------------------------------------------------------*/
void Genera6 (char *Problema)
  {
  int Quita1, Quita2, Quita3, i, j;
  char Palabra[N];

  for ( Quita1=0        ; Quita1<N-2 ; Quita1++ ) {
  for ( Quita2=Quita1+1 ; Quita2<N-1 ; Quita2++ ) {
  for ( Quita3=Quita2+1 ; Quita3<N   ; Quita3++ )
    {
    for ( i=0 , j=0 ; Problema[i] ; i++ )
      {
      if ( i != Quita1 && i != Quita2 && i!= Quita3 )
        { Palabra[j++] = Problema[i]; }
      }
    Palabra[j] = NULO;
    OrdenaPalabra (Palabra, 6);
    printf ("%s\n", Palabra);
    }}}
  }

/*-------------------------------------------------------------------------
 * Función:  Genera5()
 * Objetivo: Generar las posibles claves que se pueden obtener
 *           de un problema que tengan longitud 5
 * Entradas: Una cadena con el problema
 * Salidas:  Por salida estándar
 *-----------------------------------------------------------------------*/
void Genera5 (char *Problema)
  {
  int Quita1, Quita2, Quita3, Quita4, i, j;
  char Palabra[N];

  for ( Quita1=0        ; Quita1<N-3 ; Quita1++ ) {
  for ( Quita2=Quita1+1 ; Quita2<N-2 ; Quita2++ ) {
  for ( Quita3=Quita2+1 ; Quita3<N-1 ; Quita3++ ) {
  for ( Quita4=Quita3+1 ; Quita4<N   ; Quita4++ )
    {
    for ( i=0 , j=0 ; Problema[i] ; i++ )
      {
      if ( i != Quita1 && i != Quita2 && i!= Quita3 && i!=Quita4 )
        { Palabra[j++] = Problema[i]; }
      }
    Palabra[j] = NULO;
    OrdenaPalabra (Palabra, 5);
    printf ("%s\n", Palabra);
    }}}}
  }

/*-------------------------------------------------------------------------
 * Función:  OrdenaPalabra()
 * Objetivo: Ordenar en orden creciente los caracteres de una palabra
 * Entradas: Una palabra y su longitud
 * Salidas:  La palabra queda modificada.
 * Algoritmo: Por inserción
 *-----------------------------------------------------------------------*/
void OrdenaPalabra (char *Palabra, int Longitud)
  {
  int i, j;
  char c;

  for ( i=1 ; i<Longitud ; i++ )
    {
    c = Palabra[i];
    for ( j=i-1 ; j>=0 && (Palabra[j]>c) ; j-- )
      { Palabra[j+1] = Palabra[j]; }
    Palabra[j+1] = c;
    }
  }
