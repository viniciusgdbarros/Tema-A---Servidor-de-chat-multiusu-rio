# Tema A — Servidor de Chat Multiusuário 

## Etapa 1

## ✅ Objetivo da Etapa 1
- Implementar biblioteca de logging **thread-safe** (`libtslog`).
- Criar um teste CLI que simula múltiplas threads gravando logs.
- Definir a **arquitetura inicial** do projeto.

---

## 📂 Estrutura do Projeto
```
temaA_etapa1/
├── logger.h          # Biblioteca de logging thread-safe
├── test_logger.cpp   # Programa de teste CLI com múltiplas threads
├── Makefile          # Compilação automática
└── README.md         # Instruções e arquitetura inicial
```

---

## ⚙️ Compilação e Execução
```bash
make
./test_logger
```

- As mensagens de log serão gravadas no terminal **e** no arquivo `output.log`.

---

## 🧩 Arquitetura Inicial (Tema A)
O sistema completo (nas próximas etapas) terá os seguintes componentes:

```
+---------------------------+
|         Cliente           |
|  - conecta via TCP        |
|  - envia mensagens        |
|  - recebe mensagens       |
+-------------+-------------+
              |
              v
+---------------------------+
|         Servidor          |
|  - aceita múltiplos       |
|    clientes (threads)     |
|  - retransmite mensagens  |
|  - mantém lista clientes  |
+-------------+-------------+
              |
              v
+---------------------------+
|          Logger           |
|  - thread-safe            |
|  - grava logs             |
|  - usado por servidor e   |
|    clientes               |
+---------------------------+
```

---

## Etapa 2
✅ Objetivo da Etapa 2

Implementar cliente e servidor mínimos em rede (protótipo CLI).

Permitir que múltiplos clientes se conectem ao servidor e troquem mensagens.

Integrar logging thread-safe (libtslog) em servidor e clientes.

Definir scripts de teste básicos com múltiplos clientes.

📂 Estrutura do Projeto
temaA_etapa2/
├── logger.h            # Biblioteca de logging thread-safe (Etapa 1)
├── server.cpp          # Servidor TCP concorrente (Etapa 2)
├── client.cpp          # Cliente CLI de chat (Etapa 2)
├── Makefile            # Compilação automática
├── README.md           # Instruções e documentação
├── sequence_chat.puml  # Diagrama de sequência (PlantUML)
├── sequence_chat.md    # Diagrama de sequência (Mermaid)
└── logs: server.log, client.log

⚙️ Compilação e Execução
Compilar
make

Rodar o servidor
./server

Rodar clientes (em outros terminais)
./client


O cliente conecta ao servidor e pode enviar mensagens.

O servidor retransmite as mensagens para todos os clientes conectados (broadcast).

Digite /quit para encerrar o cliente.

Os logs são gravados em server.log e client.log.

📊 Diagrama de Sequência (Etapa 2)
PlantUML
@startuml
actor Cliente
participant Servidor
participant Logger

Cliente -> Servidor: Conectar via TCP
Servidor -> Logger: Registrar conexão
Cliente -> Servidor: Enviar mensagem
Servidor -> Logger: Registrar mensagem
Servidor -> Cliente: Retransmitir (broadcast)
Servidor -> Logger: Registrar broadcast
@enduml

Mermaid
sequenceDiagram
    participant Cliente
    participant Servidor
    participant Logger

    Cliente->>Servidor: Conectar via TCP
    Servidor->>Logger: Registrar conexão
    Cliente->>Servidor: Enviar mensagem
    Servidor->>Logger: Registrar mensagem
    Servidor->>Cliente: Retransmitir (broadcast)
    Servidor->>Logger: Registrar broadcast

## Etapa 3 — Sistema Completo (Final)

### Funcionalidades
- Servidor TCP multiusuário completo (C++).
- Clientes simultâneos com broadcast.
- Logging integrado em todas as operações.
- Tratamento de desconexões e erros.
- Diagrama de sequência atualizado.
- Relatório técnico final (relatorio_final.md / relatorio_final.pdf).

### Teste rápido
1. Compile com `make`
2. Execute o servidor: `./server`
3. Em outros terminais, execute clientes: `./client`
4. Troque mensagens e teste `/quit`.

### Tag
`v3-final`
