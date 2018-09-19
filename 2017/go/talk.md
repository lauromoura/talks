# Apresentação

## Quem sou

- Desenvolvedor de software desde 2008
- Recife/Pernambuco
- 2008~15 Instituto Nokia de Tecnologia
- 2015~ Expertise Solutions
- Projetos:
    - PySide
    - Webkit
    - EFL

# A linguagem Go

## A linguagem Go

- Lançada em 2009 pelo Google
- Foco em agilidade no desenvolvimento
\note{Agilidade: Por exemplo, tempo de compilação}
- Primitivas de concorrência
- Garbage collected
- Não, não tem generics...

## Hello, Go!

```golang
package main

import "fmt"

func main() {
    fmt.Println("Hello, Go!")
}

```

## Pacotes e nomes

- Todo arquivo tem que estar dentro de um pacote
- Nomes dentro de um pacote são privados por padrão
- Nomes começando com maiúsculas são públicos

## Ponteiros e valores

```golang
package main

import "fmt"

func zero(ival int, iptr *int) {
    ival = 0
    *iptr = 0
}

func main() {
    var a int = 13
    b := 42

    zero(a, &b)
    fmt.Println(a, b);
}
```
\note{Mostrar a inicializacao com := }

## Structs

```golang
type person struct {
    name string
    age int
}

func main() {
    a := person{"Lauro", 32}
    b := person{name: "Kid", age: 13}
    a.name = "Neto"
}
```

## Receiver methods

```golang

type rect struct {
    width, height int
}

func (r rect) area {
    return r.width * r.height
}

func (r *rect) grow {
    r.width *= 2
    r.height *= 2
}
```

## Receiver methods - cont.

- Definidos para ponteiros ou valores
- Converte automaticamente entre ambas variantes
\note{Usar o método em ponteiros para evitar cópia ou modificar o argumento}

## Interfaces

```golango
import "math"

type geometry interface {
    area() float64
    perim() float64
}

type rect struct {
    width, height float64
}

type circle struct {
    radius float64
}
```

## Interfaces - 2

```golang
func (r rect) area() {
    return r.width * r.height
}

func (r rect) perim() {
    return r.width * 2 + r.height * 2
}

func (c circle) area() {
    return math.Pi * c.radius * c.radius
}

func (c circle) perim() {
    return 2 * math.Pi * c.radius
}
```

## Interfaces - 3

```golang
func measure(g geometry) {
    fmt.Println(g)
    fmt.Println(g.perim())
    fmt.Println(g.area())
}
func main() {
    r := rect{3, 4}
    c := circle{2}

    measure(r)
    measure(c)
}
```

## Embedding ao invés de herança

```golang

type Reader interface {
    Read(p []byte) (n int, err error)
}

type Writer interface {
    Write(p []byte) (n int, err error)
}

type ReadWriter interface {
    Reader
    Writer
}
```

## Embedding structs

```golang

// pacote bufio implementa Writer e Reader
// do slide anterior

type ReadWriter struct {
    *Reader // *bufio.Reader
    *Writer // *bufio.Writer
}
```

## Embedding structs

- Ao invés de herança, composição
- Go em geral cuida de pegar o campo correto
- Exceção: campos embutidos com nome de variável


## Garbage collector

- Fonte de muitas críticas
- Melhorou bastante depois do Go 1.5
- Latência abaixo de 10ms
\note{Apesar das melhorias, continua recebendo algumas críticas}

## goroutines

```golang

go funcion_invocation(args)

go func(arg int) {
    fmt.Println("Got ", arg)
}(42)

```

- Executa mesmo depois de quem chamou sair
    - Menos do main()

## goroutines - cont

- Espaço de memória compartilhado
- Lightweight
- Nãõ se comunique compartilhando memória,
  compartilhe memória se comunicando
- Multiplexados em poucas threads do SO
- LockOsThread

## Canais

```golang
package main

import "fmt"

func main() {
    messages := make(chan string)

    go func() { messages <- "ping" }()

    msg := <- messages
    fmt.Println(msg)
}
```


# O comando cgo

## Enter cgo

- pseudo-pacote "C"
- Gera código que faz a ponte entre C e Go
- Expõe tipos C através do namespace "C"
- Desvantagens
    - Limitações devido ao garbage collector
    - Tempo de compilação mais demorado
    - Segurança

# Exemplos Basicos

## Hello cgo

```golang
package main

/*
#include <stdio.h>
#include <stdlib.h>

// Wrapper around variadic printf.
void myprintf(const char *msg) {
    printf("%s", msg);
}
*/
import "C"
```

## Hello cgo

```golang
func main() {
    cstr := C.CString("Hello, cgo!\n")
    defer C.free(unsafe.Pointer(cstr))

    C.myprintf(cstr)
}
```

\note{Por padrão, cgo vai pegar todos os arquivos c/cpp/cxx/etc e compilar.}

## Funções variádicas, #defines

- Variádicas não são suportadas pelo cgo
- Assim como preprocessamento
- Ambas precisam de wrappers

## Exportando funções Go

- comentário "//export NAME"
- Limitação: Preâmbulo copiado para todos os arquivos
- Não permite definições no preâmbulo
- Header "_cgo_export.h"

## Exportando funções Go - .go

```golang
package main

/*
#include "helper.h"
*/
import "C"
import "fmt"

//export Exported_To_C
func Exported_To_C(x int) {
    fmt.Println("Exported_To_C: Received ", x)
}
func main() {
    C.call_exported(42);
    C.call_exported(71);
}
```

## Exportando funções Go - .H

```c

#ifndef HELPER_H
#define HELPER_H

void call_exported(int x);

#endif
```

## Exportando funções Go - .C

```c
#include "helper.h"
#include "_cgo_export.h"

void call_exported(int x) {
    Exported_To_C(x);
}
```

## Ponteiros entre Go e C

- Ponteiro Go: Aponta para alocações do Go
- Ponteiro C: Aponta para alocações do C
- Ponteiros Go que apontem para memória com Go pointers são proibidos
    - Maldito GC...
- C não deve guardar ponteiros Go depois de retornar
- Funções C que recebem ponteiros Go devem retornar
- Funções Go chamadas de C não podem retornar ponteiros Go

## Exportando ponteiros de funções Go

- Funções Go internamente apontam para ponteiros Go
- Não podem ser exportadas diretamente
- Alternativa: Usar um tipo intermediário como "id"
    - Wrappers cuidam de converter entre Go e C

# Caso de uso: Usando EFL em Go

## EFL em Go - preambulo

```golang
package main

/*
#cgo CFLAGS: -DEFL_BETA_API_SUPPORT=1
#cgo CFLAGS: -DEFL_EO_API_SUPPORT=1
#cgo pkg-config: elementary
#include <Elementary.h>

static inline Eo* _efl_new(
        const Efl_Class *klass,
        Eo* parent) {
    return efl_add(klass, parent);
}
*/
import "C"
import "unsafe"
```

## Efl em Go

```golang
func main() {
    C.elm_init(0, nil);
    title := C.CString("Hello, World!");
    defer C.free(unsafe.Pointer(title));
    message := C.CString("Click me!");
    defer C.free(unsafe.Pointer(message));

    win := C._efl_new(
        C.efl_ui_win_standard_class_get(), nil);

    C.elm_policy_set(C.ELM_POLICY_QUIT,
        C.ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

    C.efl_ui_win_autodel_set(win, 1);
    C.efl_text_set(win, title);
...
```

## Efl em Go

```golang
...
    button := C._efl_new(C.elm_button_class_get(),
                         box);
    C.efl_pack(box, button);
    C.efl_gfx_size_hint_weight_set(button, 0, 0);
    C.efl_text_set(button, message);
    C.efl_gfx_visible_set(button, 1);
    C.efl_gfx_size_set(win, 640, 480);
    C.efl_gfx_visible_set(win, 1);
    loop := C.efl_loop_main_get(
            C.efl_loop_class_get());
    C.efl_loop_begin(loop);
}
```

## Idéias futuras

- Código ainda é muito "C"
    - Poderíamos usar interfaces e structs
- Binding do Eolian para geração automática

## Referências

- https://golang.org
- https://golang.org/doc/effective_go.html
- https://gobyexample.com
- http://blog.nindalf.com/how-goroutines-work/
- https://golang.org/cmd/cgo/

# Perguntas
