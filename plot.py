# Primeiro, vamos criar um exemplo de script Python que faz o que você precisa.
# Este script lerá um arquivo de texto contendo floats separados por novas linhas (\n)
# e em seguida plotará um gráfico de linha com esses números.

# Vamos supor que o arquivo de texto se chame 'data.txt' e esteja localizado no mesmo diretório do script.
import os
import matplotlib.pyplot as plt

# Função para ler os dados do arquivo e converter em lista de floats
def read_data_from_file(file_path):
    with open(file_path, 'r') as file:
        data = file.read().splitlines()  # Lê o arquivo e divide em linhas
        data = [float(i) for i in data if i]  # Converte cada linha para float
    return data

# Função para plotar o gráfico
def plot_data(data):
    plt.plot(data)  # Plota os dados
    plt.title('Gráfico de Linha')
    plt.xlabel('Índice')
    plt.ylabel('Valor')
    plt.show()
    
    # Verifica se a pasta 'fig' existe. Se não, cria a pasta.
    if not os.path.exists('fig'):
        os.makedirs('fig')
    
    # Salva o gráfico na pasta 'fig' com o nome 'grafico_linha.png'
    plt.savefig('fig/grafico_linha.png')
    plt.close()  # Fecha a figura após salvar, liberando recursos
    
    print("Gráfico salvo em: fig/grafico_linha.png")

# Caminho para o arquivo de dados
file_path = 'data//times.txt'

# Ler os dados do arquivo
data = read_data_from_file(file_path)

# Plotar os dados
plot_data(data)

# Este script deve ser salvo como um arquivo .py e executado em um ambiente que tenha acesso
# ao matplotlib e seja capaz de exibir gráficos. Certifique-se de que o arquivo 'data.txt' esteja
# no mesmo diretório do script, ou altere o caminho do arquivo conforme necessário.
