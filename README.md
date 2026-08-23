# 🏓 Pong em C

Um jogo de **Pong desenvolvido em C**, executado diretamente no terminal.

O projeto foi desenvolvido como um exercício prático para estudar e aplicar conceitos fundamentais da linguagem C, como **structs, ponteiros, enumerações, entrada de teclado, manipulação de matrizes e game loop**.

---

## 🎮 Sobre o jogo

O jogo consiste em uma partida de Pong entre dois jogadores.

Cada jogador controla uma raquete vertical e deve impedir que a bola atravesse seu lado da quadra.

O primeiro jogador a alcançar **10 pontos** vence a partida.

### Controles

| Jogador | Subir | Descer |
|:-------:|:-----:|:------:|
| Player 1 | `W` | `S` |
| Player 2 | `8` | `2` |

---

## 🖥️ Funcionamento

O jogo é executado diretamente no terminal e utiliza caracteres para representar os elementos da partida.

A quadra é construída utilizando uma matriz bidimensional:

```c
char camp[h][l];
```

Os principais elementos são representados da seguinte maneira:

- `*` → paredes e raquetes
- `O` → bola
- espaço → área vazia

Exemplo:

```text
**************************************************
*                                                *
*  *                         O                   *
*  *                                             *
*  *                                          *  *
*                                             *  *
*                                             *  *
*                                                *
*                                                *
*                                                *
*                                                *
**************************************************
```

---

## 🧠 Conceitos praticados

Durante o desenvolvimento foram utilizados diversos conceitos da linguagem C:

- `struct`
- `typedef`
- `enum`
- Ponteiros
- Passagem de estruturas por referência
- Matrizes bidimensionais
- Funções
- Manipulação de caracteres
- Entrada de teclado
- Entrada não bloqueante
- `termios`
- `fcntl`
- `usleep`
- Controle do terminal
- Game loop
- Sistema de colisão
- Renderização no terminal

---

## 🏗️ Estruturas utilizadas

### Player

Cada jogador possui uma pontuação e uma raquete.

```c
typedef struct{
    int points;
    Paddle bar;
}Player;
```

### Paddle

Representa a raquete do jogador.

```c
typedef struct{
    int PaddleY;
    int PaddleX;
    int tam;
}Paddle;
```

### Ball

Representa a bola e seu estado atual.

```c
typedef struct{
    int ballPosX;
    int ballPosY;
    int ballDirectionX;
    int ballDirectionY;
    boolean moving;
}Ball;
```

---

## 🔄 Game Loop

O funcionamento do jogo é baseado em um loop contínuo que realiza três etapas principais:

```text
        ┌─────────────┐
        │    INPUT    │
        └──────┬──────┘
               ↓
        ┌─────────────┐
        │   UPDATE    │
        └──────┬──────┘
               ↓
        ┌─────────────┐
        │   RENDER    │
        └──────┬──────┘
               │
               └──────────→ INPUT
```

### Input

O programa verifica se algum jogador pressionou uma tecla de movimento.

Caso uma tecla válida seja detectada, a posição da raquete é atualizada.

### Update

A posição da bola é atualizada de acordo com sua direção.

Também são verificadas:

- Colisões com as paredes;
- Colisões com as raquetes;
- Pontuação;
- Reinício da bola após um ponto.

### Render

A função `render()` transforma o estado atual do jogo em uma representação visual no terminal.

```c
void render(char camp[h][l], Ball *ball, Player *p1, Player *p2){
    createCamp(camp, p1, p2, ball);
    clearScreen();
    printCamp(camp);
}
```

A matriz do campo é reconstruída a cada atualização e então impressa no terminal.

---

## ⚙️ Compilação

O projeto utiliza o **GCC**.

Para compilar:

```bash
gcc main.c -o pong
```

Depois, execute:

```bash
./pong
```

---

## 🐧 Sistema operacional

O projeto foi desenvolvido e testado em **Linux**.

A implementação atual utiliza recursos específicos de sistemas Unix/POSIX, principalmente:

```c
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
```

Essas bibliotecas são utilizadas para permitir a leitura de teclas sem a necessidade de pressionar `Enter` e para realizar a entrada de teclado de forma não bloqueante.

---

## 🚧 Possíveis melhorias

Algumas melhorias que podem ser implementadas futuramente:

- [ ] Permitir múltiplas teclas simultaneamente
- [ ] Melhorar o sistema de entrada de teclado
- [ ] Adicionar tela inicial
- [ ] Adicionar sistema de pausa
- [ ] Adicionar opção de reiniciar a partida
- [ ] Melhorar o sistema de colisão
- [ ] Aumentar progressivamente a velocidade da bola
- [ ] Adicionar diferentes níveis de dificuldade
- [ ] Adicionar modo contra IA
- [ ] Melhorar a renderização do terminal
- [ ] Separar o projeto em arquivos `.c` e `.h`
- [ ] Criar um `Makefile`

---

## 📚 Objetivo do projeto

O objetivo principal deste projeto não é criar uma implementação profissional de Pong, mas utilizar um jogo relativamente simples como forma de **aprender e colocar em prática conceitos da linguagem C**.

O projeto foi desenvolvido de forma incremental, começando com uma implementação simples e evoluindo conforme novos conceitos foram estudados.

A evolução envolveu conceitos como:

```text
Variáveis
    ↓
Funções
    ↓
Structs
    ↓
Ponteiros
    ↓
Matrizes
    ↓
Entrada de teclado
    ↓
Entrada não bloqueante
    ↓
Game Loop
    ↓
Renderização
    ↓
Sistema de colisão
```

---

## 👨‍💻 Autor

**Pedro Alexandre**

Projeto desenvolvido para fins de estudo e aprendizado em programação C.
