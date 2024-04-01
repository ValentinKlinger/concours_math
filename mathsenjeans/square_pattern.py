def square_pattern(nb_line, nb_column, pattern):
    l = nb_line
    c = nb_column
    while l != c:
        if l < c:
            l += nb_line
        
        else:
            c += nb_column

    delta_l = l / nb_line
    delta_c = c / nb_column
    


    for line in range(len(patern)):
        patern[line] = patern[line] * int(delta_c)
    
    for _ in range(int(delta_l)):
        for line in patern:
            print(line)

            
if __name__ == '__main__':
    nb_l = int(input('Nombre de ligne ?\n'))
    nb_c = int(input('Nobre de colonne ?\n'))
    patern = []
    for l in range(nb_l):
        patern.append(' ' + input(f'Ligne {l}:\n'))
    square_pattern(nb_l, nb_c, patern)