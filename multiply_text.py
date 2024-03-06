n_mult = 10

with open("data/original_books.txt", "r", encoding = "utf-8") as file:
    data = file.read()
    data = data.replace("’", "'")

with open("data/multiplied.txt", "w", encoding = "utf-8") as file:
    for i in range(n_mult):
        file.write(data)
