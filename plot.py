import os
import matplotlib.pyplot as plt

# Função para ler os dados do arquivo e converter em lista de floats
def read_data_from_file(file_path):
    with open(file_path, 'r') as file:
        data = file.read().splitlines()
        data = [float(i) for i in data if i]
    return data

# Função para plotar o gráfico
def plot_data(data, title, save_path):
    plt.title(title)
    plt.xlabel('Threads')
    plt.ylabel('Tempo médio (s)')
    plt.xticks(range(1, len(data)+1))
    plt.xlim(0, len(data)+1)
    plt.plot(range(1, len(data)+1), data)
    
    if not os.path.exists('fig'):
        os.makedirs('fig')
    
    # Salva o gráfico na pasta 'fig'
    plt.savefig(save_path)
    plt.close()

# Caminho para o arquivo de dados
file_path = 'data//times.txt'

# Ler os dados do arquivo
data_count = read_data_from_file(file_path)
data_block = read_data_from_file('data//block.txt')
data_total = [data_count[i] + data_block[i] for i in range(len(data_count))]

# Plotar os dados
plot_data(data_count, 'Tempo necessário para contar as palavras com threads em paralelo', 'fig/grafico_count.png')
plot_data(data_total, "Tempo total necessário para executar diferentes threads em paralelo", "fig/grafico_total.png")