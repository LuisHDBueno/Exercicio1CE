import sys

#ler numero pelo terminal
n_mult = int(sys.argv[1])

#ler texto
with open("data/original_books.txt", "r", encoding = "utf-8") as file:
    data = file.read()
    #Substituir caracteres especiais fora do ascii
    data = data.replace("’", "'")

with open("data/multiplied.txt", "w", encoding = "utf-8") as file:
    for i in range(n_mult):
        file.write(data)
