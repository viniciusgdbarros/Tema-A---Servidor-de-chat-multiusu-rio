# 🧾 Relatório Técnico Final — Tema A  
## Servidor de Chat Multiusuário em C++ (Etapa 3 — Sistema Completo)

**Disciplina:** Linguagem de Programação II — Programação Concorrente  
**Aluno:** Vinícius Germano de Barros 
**Matrícula:** 20220096650
**Tag:** v3-final  
**Data:** [05/10/2025]  

---

## 1️⃣ Objetivo

Implementar um **sistema completo de chat multiusuário**, com:
- servidor concorrente TCP em C++;  
- clientes CLI que trocam mensagens em tempo real;  
- logging thread-safe em todas as operações;  
- arquitetura modular e reutilizável;  
- documentação, diagrama de sequência e mapeamento de requisitos.

O sistema foi desenvolvido incrementalmente em 3 etapas:
| Etapa | Foco | Tag |
|-------|------|-----|
| 1 | Logging thread-safe (biblioteca `logger.h`) | `v1-logging` |
| 2 | Protótipo cliente-servidor CLI funcional | `v2-cli` |
| 3 | Sistema completo com logging e relatório final | `v3-final` |

---

## 2️⃣ Arquitetura do Sistema

### Componentes principais
+-----------------------------+
| CLIENTE |
| CLI simples (TCP socket) |
| envia/recebe mensagens |
+-------------+---------------+
|
v
+-----------------------------+
| SERVIDOR |
| aceita conexões |
| usa threads p/ clientes |
| retransmite mensagens |
| logging integrado |
+-------------+---------------+
|
v
+-----------------------------+
| LOGGER |
| thread-safe (mutex) |
| escreve logs em arquivo |
| níveis: INFO/WARN/ERROR |
+-----------------------------+

---

## 3️⃣ Diagrama de Sequência Cliente-Servidor

### PlantUML
```plantuml
@startuml
actor Cliente
participant Servidor
participant Logger

Cliente -> Servidor: conecta via TCP
Servidor -> Logger: registra conexão
Cliente -> Servidor: envia mensagem
Servidor -> Logger: registra mensagem
Servidor -> OutrosClientes: broadcast
Servidor -> Logger: registra broadcast
Cliente -> Servidor: envia /quit
Servidor -> Logger: registra desconexão
@enduml


4️⃣ Mapeamento de Requisitos → Código
Requisito	Implementação
R1. Servidor aceita múltiplos clientes simultaneamente |	server.cpp — threads independentes via std::thread e vector<int> clients
R2. Mensagens trocadas em tempo real |	send() e recv() em client.cpp e server.cpp
R3. Logging thread-safe integrado |	logger.h com std::mutex e níveis de log
R4. Comando /quit encerra cliente |	client.cpp — detecta comando e fecha conexão
R5. Servidor remove clientes desconectados |	server.cpp — erase no vetor clients
R6. Diagrama de sequência |	sequence_chat.puml e sequence_chat.md
R7. Compilação automatizada |	Makefile com targets server e client
R8. Relatório técnico final |	relatorio_final.pdf (este documento)

5️⃣ Análise com IA

-A análise automatizada (usando modelo de linguagem) destaca que:

-O projeto atende todos os requisitos funcionais propostos no Tema A.

-O uso de std::thread e std::mutex assegura concorrência controlada.

-O logger foi corretamente desacoplado, permitindo reuso em outros projetos.

-A arquitetura cliente-servidor é modular e extensível (suporta futuras melhorias como autenticação e mensagens privadas).

-O código é portável (usa apenas POSIX + C++ padrão, sem dependências externas).

Conclusão da análise:

O sistema é funcional, robusto e escalável, atendendo plenamente às exigências. O uso de logging e threads foi implementado de forma correta e bem estruturada, demonstrando domínio dos conceitos de programação concorrente.