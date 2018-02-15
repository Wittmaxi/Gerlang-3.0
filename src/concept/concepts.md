# Concept for the compiler

Mainly used as a memo so I dont have to rely on my sheet of paper where I made some notes. 

## Language

### Version 1

-) Scopes start with a statement implying a scope and end with ```ende``` <br>
-) Anything can be declared inside of any scope, yet is only reachable in the same scope <br>
-) The entirity of the program is wrapped inside of the "program - scope" <br>
-) Comments to the code are started in any line with "#"

PRECOMPILER: 

=================================

Precompiler directives are implyed by a tilde (~).

```~einfügen```

copies an external file into the currently compiled file. Is first searched in the standard folder, then relatively from the compiler file. <br>
example: 

```~einfügen funktion1.dh```

=================================

```~definieren```

defines a constant variable of either "char" or "int". <br>
example:

```~definieren pi = 31415```
```~definieren hallo = "HALLO"```

================================

```~schreiben```

prints out a constant string or a variable defined by ```~definieren```. No concatenation possible. <br>
example: ```~schreiben "hallo"```

================================

STATEMENTS:

================================

```anfang```

```anfang``` implies a scope; it is the function where the execution of the program starts, and is required exactly once. <br>

example: 
```
anfang
	#code
ende
```

===============================

```funktion```

```funktion``` defines a later usable function. It has a name and a return type which are indicated like so: ```funktion [name] gibt [type] zurück```.
It implies a scope.

Example:
```
funktion sinus gibt fliesskomma zurück
	#code
ende
```

==============================

```wenn```

```wenn``` is used for conditional execution. It implies a scope and requires a boolean as operator. 

example: 
```
wenn (wahr)
	#code
ende
```

==============================

Variable declarations

Variables are declared like so:

```[type] variable [name] (= [rvalue])```

it has not to be assigned an rvalue. 

example: 

```boolesche variable hallo = wahr```

=============================

```solange```

```solange``` is used for multiple executions of code. It requires a boolean operator and implies a scope.

example: 
```
solange (wahr) 
	#code
ende
```

=============================

Inline C++

In order to use inline C++, you use ```c++```. It implies a scope although it is solely to be used for C++ code. If variables from the outside scope are to be used, they have <br>
to be marked by a $.

example: 

```
boolesche variable hallo = wahr
c++
	somefunction ($hallo)
	#more code
ende
```

=============================

Variable types

```boolesche``` - possible rvalues: ```wahr``` or ```falsch``` - equivalent to bool in C++
```integer``` - possible rvalues: any 4bit (positive or negative) integral value - equivalent to int in C++
```charakter``` - possible rvalues: any 1bit integral value or single characters - equivalent to char in C++
```fliesskomma``` - possible rvalues: any 8bit (positive or negative) value - equivalent to "double" in C++ 

## Standard - Library

### Version 1

No stl