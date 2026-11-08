# HOW TO EXECUTE (tested in a linux OS)
---
All the header files, C files and .txt files are required to run the tokenizer
run in a terminal inside the folder where resides all of the files in the repository the following commands:


gcc utils.c tokenizer.c -o x


./x


# CONVENCIONES
  ε = <alpha> (cadena vacía)
  Símbolo inicial = Programa
  E = { -, ~, NUM, STR, true, false, (, ID }
  S = { if, while, for, print, println, ret, local } ∪ E
  F = { ), ",", ;, then, do }   (= FOLLOW(Expresion))

======================================================
# FIRST
======================================================
Expresion            = E
Asignacion           = E
AsignacionOpc        = { :=, ε }
ExprOr               = E
ColaOr               = { or, ε }
ExprAnd              = E
ColaAnd              = { and, ε }
ExprIgualdad         = E
ColaIgualdad         = { ==, ~=, ε }
ExprComparacion      = E
ColaComparacion      = { <, <=, >, >=, ε }
ExprSuma             = E
ColaSuma             = { +, -, ε }
ExprProducto         = E
ColaProducto         = { *, /, ε }
ExprModulo           = E
ColaModulo           = { %, ε }
ExprUnaria           = E
ExprPotencia         = { NUM, STR, true, false, (, ID }
ColaPotencia         = { ^, ε }
Primario             = { NUM, STR, true, false, (, ID }
LlamadaOpc           = { (, ε }
Argumentos           = E ∪ { ε }
ColaArgumentos       = { ",", ε }
Programa             = { func } ∪ S ∪ { ε }
ElementoPrograma     = { func } ∪ S
DeclaracionFuncion   = { func }
Parametros           = { ID, ε }
ColaParametros       = { ",", ε }
Bloque               = S ∪ { ε }
Sentencia            = S
SentenciaSimple      = { print, println, ret, local } ∪ E
SentenciaIf          = { if }
PartesElse           = { else, ε }
SentenciaWhile       = { while }
SentenciaFor         = { for }
PasoOpc              = { ",", ε }

======================================================
FOLLOW
======================================================
Expresion            = { ), ",", ;, then, do }
Asignacion           = { ), ",", ;, then, do }
AsignacionOpc        = { ), ",", ;, then, do }

ExprOr               = { ), ",", ;, then, do, := }
ColaOr               = { ), ",", ;, then, do, := }

ExprAnd              = { ), ",", ;, then, do, :=, or }
ColaAnd              = { ), ",", ;, then, do, :=, or }

ExprIgualdad         = { ), ",", ;, then, do, :=, or, and }
ColaIgualdad         = { ), ",", ;, then, do, :=, or, and }

ExprComparacion      = { ), ",", ;, then, do, :=, or, and, ==, ~= }
ColaComparacion      = { ), ",", ;, then, do, :=, or, and, ==, ~= }

ExprSuma             = { ), ",", ;, then, do, :=, or, and, ==, ~=, <, <=, >, >= }
ColaSuma             = { ), ",", ;, then, do, :=, or, and, ==, ~=, <, <=, >, >= }

ExprProducto         = { ), ",", ;, then, do, :=, or, and, ==, ~=, <, <=, >, >=, +, - }
ColaProducto         = { ), ",", ;, then, do, :=, or, and, ==, ~=, <, <=, >, >=, +, - }

ExprModulo           = { ), ",", ;, then, do, :=, or, and, ==, ~=, <, <=, >, >=, +, -, *, / }
ColaModulo           = { ), ",", ;, then, do, :=, or, and, ==, ~=, <, <=, >, >=, +, -, *, / }

ExprUnaria           = { ), ",", ;, then, do, :=, or, and, ==, ~=, <, <=, >, >=, +, -, *, /, % }
ExprPotencia         = { ), ",", ;, then, do, :=, or, and, ==, ~=, <, <=, >, >=, +, -, *, /, % }
ColaPotencia         = { ), ",", ;, then, do, :=, or, and, ==, ~=, <, <=, >, >=, +, -, *, /, % }

Primario             = { ), ",", ;, then, do, :=, or, and, ==, ~=, <, <=, >, >=, +, -, *, /, %, ^ }
LlamadaOpc           = { ), ",", ;, then, do, :=, or, and, ==, ~=, <, <=, >, >=, +, -, *, /, %, ^ }

Argumentos           = { ) }
ColaArgumentos       = { ) }

Programa             = { $ }
ElementoPrograma     = { func } ∪ S ∪ { $ }
DeclaracionFuncion   = { func } ∪ S ∪ { $ }

Sentencia            = { func } ∪ S ∪ { $, end, else }
SentenciaIf          = { func } ∪ S ∪ { $, end, else }
SentenciaWhile       = { func } ∪ S ∪ { $, end, else }
SentenciaFor         = { func } ∪ S ∪ { $, end, else }
SentenciaSimple      = { ; }

Parametros           = { ) }
ColaParametros       = { ) }
Bloque               = { end, else }
PartesElse           = { end }
PasoOpc              = { do }


