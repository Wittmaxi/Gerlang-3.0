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

```funktion``` defines a later usable function. It has a name, variable declarations for input a return type which are indicated like so: ```funktion [name] ([variables]) gibt [type] zurück```.
It implies a scope.

Example:
```
funktion sinus (ganzzahl variable input, ganzzahl variable input2) gibt fliesskomma zurück
	#code
ende
```

==============================

```gebe [variable] zurück```

This enables the programmer to return a variable or rvalue out of a function. May not be used in anonymous scopes. Stops execution of the current scope.
Example:
```
funktion sinus (fliesskomma variable input) gibt fliesskomma zurück
	fliesskomma variable output
	#calculate output
	gebe output zurück
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

Inline C++ can be called with 

```
C++
	#code
ende
```

Variables defined in the same scope can be called in the C++ call.

=============================

VARIABLE TYPES

```boolesche``` - possible rvalues: ```wahr``` or ```falsch``` - equivalent to bool in C++

```ganzzahl``` - possible rvalues: any 4bit (positive or negative) integral value - equivalent to int in C++

```charakter``` - possible rvalues: any 1bit integral value or single characters - equivalent to char in C++

```fliesskomma``` - possible rvalues: any 8bit (positive or negative) value - equivalent to "double" in C++ 

Arrays: arrays can be implied with [] and the length. Leave empty for no special length. They can be instantly defined by a "{"
example: 

```
fliesskomma variable array [4] = {1, 3, 4, 6}
fliesskomma variable array [] 
```

Pointers:

If you want to declare a variable, you add in ```zeiger``` after the type.

Example:
```
charakter zeiger variable text = "HALLO"
```

The variable has as value its location in memory and can be assigned any rvalue.
To get its real value, it has to be dereferenced with ```*```.

============================

function calls

To call a function it has to be given statements as inputs. Its output may be used as a normal lvalue.

Example:

```
funktion sinus_times_pi (ganzzahl variable input) gibt fliesskomma zurück
	gebe (sinus (input) * 3.14) zurück
ende


sinus_times_pi (24) #nothing happens

ganzzahl variable something = sinus_times_pi (24)

function_that_prints_stuff (something)

```

============================

ASSIGNMENTS

a variable can be assigned any r or lvalue with the = operator.

example: 
```[name] = [rvalue]```

============================


MATHEMATICAL OPERATORS

```*``` multiplication

```-``` subtraction

```/``` division

```+``` addition

adds two lvalues, two rvalues or one rvalue and one lvalue together, gets replaced as the output of the calculation for later.

example: 

```
ganzzahl variable hi2 = 2
ganzzahl variable hi3 = 1

ganzzahl variable hi5 = hi2 + hi3

hi2 = hi3 / hi5
``` 

## Context Free Grammar

precompiler statements, comments and white space are not accounted for, always for the latest version

### BEGIN OF FILE: 
-Infinite amount of ```functions``` and exactly one ```main function```<br>
-infinitely: variable declaration
-End of File<br>

### functions
-"funktion" + identifier + "(" + variable declaration + "," + ... + ")" + "gibt" + type_identifier + "zurück" + scope + "ende" <br>
OR<br>
-"funktion" + identifier + "()" + "gibt" + type_identifier + "zurück" + scope + "ende"

### main function
-"anfang" + scope + "ende"

### scope
-infinitely: operations <br>
-infinitely: "wenn" + "(" + boolean statement + ")" + nameless_scope + "ende"<br>
-infinitely: "solange" + "(" + boolean statement + ")" + nameless_scope + "ende"<br>
-infinitely: functions<br>
-infinitely: variable declaration <br>
-once: "gebe" + value + "zurück"

### nameless scope
-infinitely: operations <br>
-infinitely: "wenn" + "(" + boolean statement + ")" + nameless_scope + "ende"<br>
-infinitely: "solange" + "(" + boolean statement + ")" + nameless_scope + "ende"<br>
-infinitely: functions<br>
-infinitely: variable declaration <br>

### operations

identifier + "=" + value + operator + value
OR
identifier + "=" + value + operator + operation

### boolean statement
value + "==" + value
OR
value + "!=" + value 
OR
boolean_litteral

### variable declaration
type_identifier + "variable" + identifier 
OR
type_identifier + "variable" + identifier + "=" + value

### value
identifier
OR
character_litteral
OR
float_litteral
OR
integer_litteral
OR
boolean_litteral

### identifier

name with only letters and numbers

### boolean statement

## Standard - Library

### Version 1

No stl

## Conventions

### Indentation
Both tabs and spaces are understood by the compiler - it is discouraged though to use spaces for indentation

### formatting
Every keyword and operator should be separated by a space. 

### C++ calls
C++ should ONLY be called inside of the standard library and in other projects. The C++ may require external libraries.

### Scopes
Variables should be declared in the smallest possible scope.

### Pointers 
Pointers are discouraged because of the problems they can produce [vulnerabilities, runtime errors, etc].