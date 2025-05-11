import os

# Criar estrutura de pastas e arquivos para o projeto
base_path = "/Users/luismalaquias/Documents/Documentos - MacBook Air de Luís - 1/AED 2/TRABALHO/Simulador-de-Banco/REFEITO"

folders = [
    base_path,
    f"{base_path}/src",
    f"{base_path}/include"
]

files = {
    f"{base_path}/src/main.c": "",              # Arquivo principal
    f"{base_path}/src/banco.c": "",             # Implementações do banco
    f"{base_path}/src/fila.c": "",              # Fila de atendimento
    f"{base_path}/src/pilha.c": "",             # Pilha de operações
    f"{base_path}/src/ordenacao.c": "",         # Algoritmos de ordenação
    f"{base_path}/include/banco.h": "",         # Header do banco
    f"{base_path}/include/fila.h": "",          # Header da fila
    f"{base_path}/include/pilha.h": "",         # Header da pilha
    f"{base_path}/include/ordenacao.h": "",     # Header de ordenação
    f"{base_path}/README.txt": "Projeto Banco - Estrutura de Dados 2\nInclui: Structs, Ponteiros, Alocação Dinâmica, TADs, Fila, Pilha, Ordenação e Arquivos.\n"
}

# Criar pastas
for folder in folders:
    os.makedirs(folder, exist_ok=True)

# Criar arquivos vazios
for file_path, content in files.items():
    with open(file_path, "w") as f:
        f.write(content)

# Listar para o usuário
os.listdir(base_path)
