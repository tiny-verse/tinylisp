# tinyLISP

*tinyLISP* is an extremely minimal implementation of a lisp-like language.

> Please note that tinyLISP is work in progress and does contain rough edges, such as uncommented and often inefficient code, and even occassional segfaults.

## Language Reference

*tinyLISP* supports integers and their basic binary operations (`+`, `-`, `*`, `/`). Equality of numbers (`eq`) and relations (`<`, `>`) can be tested as well. Result of all relational operators is either `1` (identical to symbol `t`) or `0`. 

Being LISP-like language, it of course supports list `()` and basic operations on them: `car`, `cdr`, `cons` and `consp`. `nil` denotes an empty list.

### If Statement

*tinyLISP* understands the `if` statement in the common form `(if X Y Z)`, which evaluates `X` first and if `X` evaluates to `nil` or `0` executes `Z`, otherwise executes `Y`.

### Code sequence

Code sequences are supported using the `progn` function which evaluates all its arguments and returns the result of the last one. 

### Closures

`lambda` statement is supported in the common form:

```
(lambda (args) body)
```

### `apply`

`apply` can be used to apply arbitrary functions to list of their arguments (similar to Common LISP):

```
(apply fun (args))
```

### Quoting

*tinyLISP* only understands the simple `quote` function which returns its argument unevaluated. Quote accepts only one argument.

### Defining Functions

Named functions can be defined only at global scope (top-level statements). The definition is similar to Common LISP:

```
(defun name (args) body)
```

### `let` and `letrec`

*tinyLISP* also supports the `let` and `letrec` (for recursive functions) statements as defined by the SECD machine, i.e.:

```
(let (names) (values) body)
(letrec (names) (values) body)
```

### Syntactic Sugar

Syntactic sugar for *tinyLISP* is very minimal, the following shorthands are supported:

`( X . Y )` is transpiled into `(cons X Y)` where `X` and `Y` are valid tinyLISP expressions. 

`'X` is transpiled into `(quote X)` where `X` can be any valid tinyLISP expression. 

> Binary operators in tinyLISP (`+`, `-`, `*`, `/`, `<`, `>`, etc.) only support two arguments. Providing fewer or more arguments to these functions will result in very hard to debug errors. 

### Standard Library

From the functions above, a primitive standard library can be built containing more functionality. 



