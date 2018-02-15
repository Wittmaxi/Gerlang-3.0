# Concept for the compiler

Mainly used as a memo so I dont have to rely on my sheet of paper where I made some notes. 

## Language

### Version 1

-) Scopes start with a statement implying a scope and end with ```ende``` <br>
-) Anything can be declared inside of any scope, yet is only reachable in the same scope <br>
-) The entirity of the program is wrapped inside of the "program - scope" <br>

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

STATEMENTS:



## Standard - Library

### Version 1

No stl