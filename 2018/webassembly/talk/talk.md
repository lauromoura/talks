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
    - Ainda assim, é Javascript
\note{Mas ainda assim estamos presos ao JS}
- TOO MUCH JS
    - node_modules e afins
- Alto nível demais
    - Problema ao usar JS normal como "assembly"

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

- Javascript
    - Parsear
    - Gerar bytecode
    - Otimizar (JIT e afins)
    - Re-Otimizar
    - Rodar

# "Assembly" da Web

## asm.js

- Subset de Javascript
- Dicas para o interpretador do código que vai ser executado
- Permite otimizações mais certeiras e eficientes

## asm.js - C

```c
size_t strlen(char *ptr) {
  char *curr = ptr;
  while (*curr != 0) {
    curr++;
  }
  return (curr - ptr);
}
```

## asm.js - js


```javascript
function strlen(ptr) {
  ptr = ptr|0;
  var curr = 0;
  curr = ptr;
  while (MEM8[curr]|0 != 0) {
    curr = (curr + 1)|0;
  }
  return (curr - ptr)|0;
}
```

## asm.js

- Ainda é javascript
- Ainda precisa ser parseado
- Pode ser melhorado

# WebAssembly

## WebAssembly

- Formato binário
    - Mais compacto
    - Não precisa ser parseado, apenas decodado
- VM em pilha
- Suporte a uma versão MVP nos 4 principais navegadores

## WebAssembly Text Format

```wast
(module
        (func $addTwo (param $lhs i32)
                      (param $rhs i32)
                      (result i32)
                get_local $lhs
                get_local $rhs
                i32.add)
        (export "addTwo" (func $addTwo))
)
```

## Processador hipotético

- 8-bit bytes
- Memória byte a byte
- Suporte a acessos não-alinhados
- Inteiros de 32bits e opcionalmente 64bits
- IEEE 754-2008 para floats de 32 e 64bits
    - Mas sem exceções p/ NaN por enquanto
- Little endian
- Ponteiros de 32bits
    - wasm64 suporta ponteiros de 64bits

## Syscalls

- Não existem
- Opcionalmente, importar funções a partir do host


# emscripten

## emscripten

- Backend LLVM
- clang como frontend
- Gera código asm.js ou WebAssembly
- Usos
    - Unity
    - Qt
    - DOSBox

## emscripten runtime environment

- SDL 2.0
- OpenGL ES 2.0
- Sistema de arquivos virtual
- Arquivos
    - MEMFS
    - IDBFS
    - NODEFS (node.js)
- Main loop function
- Linkagem estática
    - Módulos JS dinamicamente

# Demos

# Hoje

- C/C++/Rust
- MVP nos principais navegadores.

# Futuro

- Threads
- C#/.Net (ilasm)

## Referências

- https://webassembly.org
- WebAssembly and the Death of Javascript
    - https://www.youtube.com/watch?v=pBYqen3B2gc 
- https://kripken.github.io/emscripten-site/index.html
- https://medium.com/@addyosmani/the-cost-of-javascript-in-2018-7d8950fbb5d4
- https://hacks.mozilla.org/2017/03/why-webassembly-is-faster-than-asm-js/

# Perguntas
