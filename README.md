# Tema A — Servidor de Chat Multiusuário (Etapa 1)

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

## 📌 Próximos Passos (Etapa 2)
- Implementar **protótipo CLI de comunicação** (cliente-servidor mínimo).
- Integrar logging no servidor e clientes.
- Criar scripts de teste com múltiplos clientes simulados.

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
