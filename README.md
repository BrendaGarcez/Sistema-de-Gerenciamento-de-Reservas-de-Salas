# Sistema de Gerenciamento de Reservas de Salas  

## 📌 Sobre o Projeto  
Este projeto implementa um **Sistema de Gerenciamento de Reservas de Salas**, utilizando as estruturas de dados **Árvore AVL**, **Heap** e **Tabela Hash** para otimizar a criação, consulta e cancelamento de reservas de salas.  

O sistema recebe operações via arquivos `.txt`, processa as informações e gera um arquivo de saída detalhando as ações executadas.  

## 🎯 Objetivos  
- Implementar um sistema eficiente para **gerenciamento de reservas de salas**.  
- Utilizar **Árvore AVL** para organizar e armazenar salas.  
- Utilizar **Heap** para gerenciar prioridades de reservas.  
- Utilizar **Tabela Hash** para armazenar e consultar estados das salas.  

## 🔧 Estruturas de Dados Implementadas  
- **Árvore AVL**: Armazena e organiza salas, garantindo operações eficientes de busca, inserção e remoção.  
- **Heap (Máximo)**: Gerencia reservas priorizadas, garantindo que as mais urgentes sejam atendidas primeiro.  
- **Tabela Hash**: Armazena e controla o estado das salas, permitindo consultas rápidas.  

## 📥 Entrada de Dados  
O sistema recebe comandos de um arquivo `entrada.txt`, contendo operações como:  
```txt
CRIAR_SALA <código> <capacidade>
RESERVAR_SALA <código_sala> <prioridade>
BLOQUEAR_SALA <código_sala>
DESBLOQUEAR_SALA <código_sala>
CANCELAR_RESERVA <código_sala>
CONSULTAR_SALA <código_sala>
LISTAR_SALAS
```

## 📤 Saída de Dados  
O resultado das operações é salvo no arquivo `saida.txt`, contendo logs detalhados das ações realizadas.  

## 🛠 Requisitos Técnicos  
- Linguagem: **C**  
- Manipulação de arquivos `.txt` para entrada e saída de dados  
- Implementação modular com funções separadas para cada operação  
- Código bem documentado para facilitar entendimento e manutenção  

## 🚀 Como Executar  
1. Compile o código:  
   ```bash
   gcc -o reservas reservas.c
   ```  
2. Execute o programa passando o arquivo de entrada:  
   ```bash
   ./reservas entrada.txt
   ```  
3. O resultado será gerado no arquivo `saida.txt`.  
