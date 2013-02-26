#!/usr/bin/perl

#--------------------------------------------------------------------
# Fichero:  clasifica.pl
# Objetivo: Clasificar un archivo de palabras y generar los archivos
#           de texto necesarios para BuscaPalabras
# Autor:    Pedro Reina <pedro@pedroreina.org>
# Fecha:    D.27.10.2002
#--------------------------------------------------------------------

#--------------------------------------------------------------------
# Licencia
#
# (c) 1992 Pedro Reina y EQ Sistemas Inteligentes
#
# This program is free software; you can redistribute it
# and/or modify it under the terms of the GNU General Public
# License as published by the Free Software Foundation, version 2
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public
# License along with this program; if not, write to the
# Free Software Foundation, Inc.,
# 59 Temple Place, Suite 330,
# Boston, MA 02111-1307 USA
#--------------------------------------------------------------------

#---------------------------------
# Módulos necesarios
#---------------------------------

use strict;

#---------------------------------
# Declaración de variables
#---------------------------------

my $NombreEntrada = "";     # Fichero de palabras
my $NombreSalida  = "";     # Nombre del fichero de resultado
my @Texto = ();             # Texto del archivo de palabras
my $Palabra = "";           # Cada palabra del archivo
my $Clave = "";             # Cada clave obtenida de la palabra
my %Lista = ();             # Lista de palabras y claves
my @ListaOrdenada = ();     # Lista ordenada por claves de palabras
my $i = 0;                  # Indice

#---------------------------------
# Programa principal
#---------------------------------

# Presentación
print "\n";
print "clasifica.pl\n";
print "============\n";

# Fichero de palabras
$NombreEntrada = "palabra.txt";

# Abrimos el archivo de palabras
print "Leyendo... ";
open (Entrada, $NombreEntrada);

# Lo leemos
@Texto = <Entrada>;

# Y lo cerramos
close (Entrada);
print " hecho.\n";

# Limpiamos del fin de línea todas las palabras
foreach $Palabra (@Texto)
  { chop ($Palabra); }

for ( $i=5 ; $i<=9 ; $i++ )
  {
  %Lista = ();
  @ListaOrdenada = ();
  print "Estudiando palabras de " . $i . " letras ... ";
  foreach $Palabra (@Texto)
    {
    if ( length ($Palabra) == $i )
      {
      $Clave = estudia ($Palabra);
      $Lista{$Palabra} = $Clave;
      }
    }
  print "hecho.\n";

  print "Ordenando palabras de " . $i . " letras ... ";
  @ListaOrdenada = sort { $Lista{$a} cmp $Lista{$b} } keys %Lista;
  print "hecho.\n";

  # Generamos los archivos de salida
  $NombreSalida = "palabra" . $i . ".txt";

  print "Generando $NombreSalida... ";
  open (Salida, ">$NombreSalida");

  # Lo escribimos
  foreach $Palabra (@ListaOrdenada)
    {
    $Clave = $Lista{$Palabra};
    print Salida $Clave . "," . $Palabra . "\n";
    }

  # Y lo cerramos
  close (Salida);
  print "hecho.\n";
  }

# Despedida
print "Terminado\n";

#---------------------------------
# Función estudia()
#---------------------------------
sub estudia
  {
  my $Caracter = "";
  my @Letras = ();
  my @LetrasOrdenadas = ();
  my $Resultado = "";
  my $PalabraModificada = "";

  my $Palabra = shift;

  @Letras = split (//, $Palabra);
  $PalabraModificada = "";
  foreach $Caracter (@Letras)
    {
    if ( $Caracter eq "á" )  { $Caracter = "a"; }
    if ( $Caracter eq "é" )  { $Caracter = "e"; }
    if ( $Caracter eq "í" )  { $Caracter = "i"; }
    if ( $Caracter eq "ó" )  { $Caracter = "o"; }
    if ( $Caracter eq "ú" )  { $Caracter = "u"; }
    if ( $Caracter eq "ü" )  { $Caracter = "u"; }
    $PalabraModificada .= $Caracter;
    }

  @Letras = ();
  @Letras = split (//, $PalabraModificada);
  @LetrasOrdenadas = sort @Letras;

  foreach $Caracter (@LetrasOrdenadas)
    { $Resultado .= $Caracter; }

  return $Resultado;
  }
