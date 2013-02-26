<!-- -·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-
 Fichero:  buscapal.php (simplificado para mostrar sólo el código,
           No funcionará correctamente en un servidor real)
 Objetivo: Interfaz PHP del Buscador de palabras
 Fecha:    L.28.10.2002
 Autor:    Pedro Reina <pedro@pedroreina.org>
-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-· -->

<!-- -·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-
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
-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-· -->

<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 3.2//EN">

<HTML>

<HEAD>
<TITLE>Buscador de palabras</TITLE>
</HEAD>

<H1 ALIGN="CENTER">Buscador de palabras</H1>
<P ALIGN="CENTER">Pedro Reina</P>

<TABLE WIDTH="80%" BORDER="0" CELLPADDING="10" ALIGN="CENTER">

<!-- -·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-
 Programa PHP
-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-· -->

<?php

// Programa principal
if ( empty ($PrimeraVez) )
  { MuestraFormulario(); }
else
  { MuestraRespuesta ($Problema); }
// Fin del programa principal

// ----------------------------

// Rutina para mostrar el formulario
function MuestraFormulario()
  {
  global $Color, $PHP_SELF;

  $CodigoHTML=<<<HTML
  <TR><TD>

  <TABLE WIDTH="100%" BORDER="2" CELLPADDING="10" ALIGN="CENTER">

  <TR ALIGN="CENTER" BGCOLOR="$Color">
  <TD><B>Introducción de datos</B></TD>
  </TR>

  <FORM ACTION=$PHP_SELF METHOD="POST">
  <INPUT TYPE="HIDDEN" NAME="PrimeraVez" VALUE="No">
  <TR><TD>
  <TABLE WIDTH="100%" ALIGN="CENTER" CELLPADDING="5">
    <TR ALIGN="CENTER"><TD>
      Letras de partida: <INPUT NAME="Problema" SIZE="9">
      (exactamente 9 letras)
    </TD></TR>
    <TR ALIGN="CENTER"><TD>
      <TABLE ALIGN="CENTER" CELLPADDING="5">
      <TR ALIGN="LEFT">
      <TD VALIGN="CENTER">Palabras<BR>deseadas</TD>
      <TD>
      <LABEL><INPUT TYPE="CHECKBOX" NAME="P9" CHECKED>
      Palabras de 9 letras</LABEL>
      <BR><LABEL><INPUT TYPE="CHECKBOX" NAME="P8" CHECKED>
      Palabras de 8 letras</LABEL>
      <BR><LABEL><INPUT TYPE="CHECKBOX" NAME="P7" CHECKED>
      Palabras de 7 letras</LABEL>
      <BR><LABEL><INPUT TYPE="CHECKBOX" NAME="P6">
      Palabras de 6 letras</LABEL>
      <BR><LABEL><INPUT TYPE="CHECKBOX" NAME="P5">
      Palabras de 5 letras</LABEL>
      </TD></TR></TABLE>
    </TD></TR>
    <TR ALIGN="CENTER"><TD>
      <INPUT TYPE="submit" VALUE=" Buscar ">
      <INPUT TYPE="reset" VALUE=" Borrar ">
    </TD></TR>
  </TD></TR>
  </TABLE>
  </FORM>

  </TABLE>
  </TD></TR>

HTML;
  print $CodigoHTML;
  }

// ----------------------------

// Rutina para mostrar la respuesta
function MuestraRespuesta ($Problema)
  {
  global $Color, $REMOTE_ADDR, $P9, $P8, $P7, $P6, $P5;

  if ( strlen ($Problema) != 9 )
    { $Mensaje = "Error: el número de letras no es 9"; }

  elseif ( empty($P9) AND empty($P8) AND empty($P7) AND
           empty($P6) AND empty($P5) )
    { $Mensaje = "Aviso: no has pedido palabras de ninguna longitud"; }

  else
    {
    $NumConsulta = Consulta();
    $Problema = strtolower ($Problema);
    $Respuesta = "";

    if ( isset ($P9) )  { $Respuesta .= Busca ($Problema, 9); }
    if ( isset ($P8) )  { $Respuesta .= Busca ($Problema, 8); }
    if ( isset ($P7) )  { $Respuesta .= Busca ($Problema, 7); }
    if ( isset ($P6) )  { $Respuesta .= Busca ($Problema, 6); }
    if ( isset ($P5) )  { $Respuesta .= Busca ($Problema, 5); }

    $Mensaje=<<<HTML
    Consulta número <B>$NumConsulta</B>
    <P>Letras de partida: $Problema
    <P>Palabras obtenidas: $Respuesta
HTML;
    }

  $CodigoHTML=<<<HTML

  <TR><TD>

  <TABLE WIDTH="100%" BORDER="2" CELLPADDING="10" ALIGN="CENTER">
  <TR ALIGN="CENTER" BGCOLOR="$Color">
  <TD><B>Resultado de la búsqueda</B></TD></TR>
  <TR><TD>$Mensaje</TD></TR>
  </TABLE>

  </TD></TR>

HTML;
  print $CodigoHTML;
  }

// ----------------------------

// Rutina para buscar palabras en la base de datos
function Busca ($Problema, $Longitud)
  {
  $Respuesta = "<P><B>Palabras de $Longitud letras</B>: ";
  $Orden = "/usr/local/bin/subconjuntos " . $Problema . " " . $Longitud .
           " | sort | uniq ";
  $Clave = explode ("\n", rtrim(`$Orden`));
  $Total = count ($Clave);

  $Condicion = "clave='$Clave[0]'";
  for ( $i=1 ; $i<$Total ; $i++ )
    { $Condicion .= " OR clave='$Clave[$i]'"; }

  $Conexion = @pg_pconnect ("dbname=ciflet user=pedro port=5432");
  if ( ! $Conexion )
    { $Respuesta .= "(error accediendo a la base de datos)."; }
  else
    {
    $Tabla = "palabra" . $Longitud;
    $Consulta = "SELECT palabra FROM $Tabla WHERE $Condicion";
    $Resultado = @pg_exec ($Conexion, $Consulta);
    if ( ! $Resultado )
      { $Respuesta .= "(error accediendo a la tabla $Tabla)."; }
    else
      {
      $NumRegistros = pg_numrows ($Resultado);
      if ( $NumRegistros == 0 )
        { $Respuesta .= "(no se ha encontrado ninguna de esta longitud)."; }
      else
        {
        for ( $i=0 ; $i<$NumRegistros ; $i++ )
          { $Respuesta .= " " . pg_result ($Resultado, $i, 0); }
        }
      }
    }

  return $Respuesta;
  }

// ----------------------------

// Rutina para mostrar vínculos a otras páginas
function EscribeFinal()
  {
  }

php?>

<!-- -·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-
 Fin de todo
-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-·-· -->

</BODY>

</HTML>
