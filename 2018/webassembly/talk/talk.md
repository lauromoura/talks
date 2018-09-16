# Apresentação

## Quem sou

- Desenvolvedor de software desde 2008
- Recife/Pernambuco
- 2008~15 Instituto Nokia de Tecnologia
- 2015~ Expertise Solutions
- Projetos:
    - PySide
    - Webkit
    - EFL (JS, C#)

# No começo, era o Javascript

## Javascript

- Hack de 10 dias em 1995
- Que virou um dos pilares da web
\note{Agilidade: Por exemplo, tempo de compilação}
- Alto nível, prototypes, sintaxe que lembra C/Java
- Principais implementações
    - V8 - Blink (Chrome) e Node
    - JavascriptCore - Webkit (Safari)
    - Spidermonkey - Gecko (Firefox)
    - Chakra - Edge

## Problemas

![](js_good_parts.jpeg){ width=100% }


## Problemas

- Ficar preso a uma única linguagem
    - Transpilers e afins
\note{Mas ainda assim estamos presos ao JS}
- TOO MUCH JS
- Alto nível demais
\note{Vira um problema ao usar JS como assembly}

## Problemas

```js
!function(e,t){"use strict";"object"==typeof
module&&"object"==typeofmodule.exports?
module.exports=e.document?t(e,!0):function(e){
if(!e.document)throw new Error("jQuery
requires a window with a document");
return t(e)}:t(e)}("undefined"!=typeof
window?window:this,function(e,t){"use strict";
var n=[],r=e.document,i=Object.getPrototypeOf,
o=n.slice,a=n.concat,s=n.push,u=n.indexOf,l={},
...
```

## Porque é tão pesado?

- Parsear
- Gerar bytecode
- Otimizar (JIT e afins)
- Rodar

# asm.js

# WebAssembly Text Format

```wast
(module
        (func $addTwo (param $lhs i32) (param $rhs i32) (result i32)
                get_local $lhs
                get_local $rhs
                i32.add)
        (export "addTwo" (func $addTwo))
)
```

# WebAssembly

# Processador hipotético

- 8-bit bytes
- Granularidade de memória byte a byte
- Suporte a acessos não-alinhados
- Inteiros de 32bits e opcionalmente 64bits
- IEEE 754-2008 para floats de 32 e 64bits
    - Mas sem exceções p/ NaN por enquanto
- Little endian
- Ponteiros de 32bits
    - wasm64 suporta ponteiros de 64bits
- Operações atômicas sem lock para acessos alinhados de 8, 16 e 32 bits

# Syscalls

- Não existem
- Opcionalmente, importar funções a partir do Host

# Demos

# Hoje

- C/C++/Rust
- 

# Futuro

## Referências

- https://webassembly.org
- WebAssembly and the Death of Javascript
    - https://www.youtube.com/watch?v=pBYqen3B2gc 
- https://medium.com/@addyosmani/the-cost-of-javascript-in-2018-7d8950fbb5d4

# Perguntas
