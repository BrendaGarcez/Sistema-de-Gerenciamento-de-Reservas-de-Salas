# Sistema de Gerenciamento de Reservas de Salas

Este projeto é uma implementação de um sistema de gerenciamento de reservas de salas utilizando estruturas de dados avançadas. Ele permite realizar operações como criação, consulta, reserva e cancelamento de salas, garantindo eficiência e organização por meio do uso de Árvore AVL, Heap e Tabela Hash.

## 📋 Objetivo

Desenvolver um sistema para:
- Gerenciar informações de salas utilizando **Árvore AVL**.
- Organizar reservas com base em prioridades usando **Heap**.
- Armazenar e consultar estados de salas com **Tabela Hash**.

## 🛠 Funcionalidades

### 1. Gestão de Salas (Árvore AVL)
- **Criar sala:** Adicionar uma sala ao sistema com código e capacidade.
- **Remover sala:** Excluir uma sala do sistema.
- **Consultar sala:** Localizar uma sala pelo código.
- **Listar salas:** Exibir salas ordenadas por código.

### 2. Gestão de Prioridades (Heap)
- **Adicionar reserva:** Inserir reservas com prioridade.
- **Atualizar prioridade:** Alterar a prioridade de uma reserva.
- **Listar reservas:** Visualizar reservas ordenadas por prioridade.

### 3. Gestão de Estados (Tabela Hash)
- **Bloquear sala:** Definir uma sala como indisponível.
- **Desbloquear sala:** Tornar uma sala disponível novamente.
- **Consultar estado:** Verificar e listar salas com base no estado atual.

### 4. Cancelar Reserva
- Remover uma reserva específica de todas as estruturas de dados.

### 5. Logs Detalhados
- Todas as operações geram logs que documentam as ações realizadas.

## 🚀 Tecnologias Utilizadas
- **Linguagem:** C
- **Estruturas de Dados:** Árvore AVL, Heap de Máximo e Tabela Hash.
- **Entrada e Saída:** Arquivos `.txt`.

## 📂 Estrutura dos Arquivos

- **entrada.txt:** Contém comandos como:
  ```txt
  CRIAR_SALA <código> <capacidade>
  RESERVAR_SALA <código_sala> <prioridade>
  BLOQUEAR_SALA <código_sala>
  ```
- **saida.txt:** Gera resultados das operações, incluindo mensagens de sucesso/falha.

## 📝 Requisitos

- Código implementado em **C**.
- Separação clara de funções e módulos.
- Logs detalhados de todas as ações realizadas.
- Documentação do código explicando cada módulo e função.

## 🎯 Exemplo de Uso

1. **Criar uma sala:**
   ```
   CRIAR_SALA 101 50
   ```
2. **Reservar uma sala com prioridade:**
   ```
   RESERVAR_SALA 101 10
   ```
3. **Consultar uma sala:**
   ```
   CONSULTAR_SALA 101
   ```

## 📖 Como Executar

1. Compile o código com um compilador C (ex.: `gcc`).
2. Certifique-se de ter os arquivos de entrada no formato correto.
3. Execute o programa e verifique o arquivo de saída para os logs.


Se precisar de ajustes ou quer adicionar mais detalhes, como instruções específicas de compilação ou exemplo de arquivos, é só avisar! 😊