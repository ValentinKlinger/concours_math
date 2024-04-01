import turtle

def frise(lst, position):
    """
    affiche le résultat grâce à turtle
    """
    turtle.ht()
    turtle.tracer(False)
    turtle.penup()
    if position == 'n':
        turtle.setpos((-50*5,20*5))
    else:
        turtle.setpos((-50*5,-20*5))
    turtle.setheading(0)

    turtle.pendown()
    for note in range(len(lst) -1):
        taille = len(lst) -1
        turtle.pendown()
        
        if position == 'm':
            turtle.forward(500 / (taille * 2))
            turtle.left(90)
            turtle.color('red')
            turtle.fd(100)
            turtle.backward(100)
            turtle.color('black')
            turtle.right(90)
            turtle.forward(500 / (taille * 2))
        else:
            turtle.forward(500 / taille)
        turtle.right(90)
        turtle.forward(20*5)
        turtle.right(90)

        turtle.forward(500 / taille)
        turtle.right(90)
        turtle.forward(20*5)
        turtle.right(90)

        turtle.penup()
        x, y = turtle.xcor(), turtle.ycor()
        turtle.goto(turtle.xcor()+5, turtle.ycor()-20 )
        turtle.pendown()
        turtle.write(str(lst[note][1]), font=("Arial", 10, "bold"), align="center")
        turtle.penup()
        turtle.goto(x, y)
        turtle.setheading(0)
        turtle.forward(500 / taille)


def make_n(n):
    """
    créé une liste de n élément, chaque élément strictement différent des 
    autres. La valeur représente la couleur
    """
    out = []
    color = 1
    place = 0
    for i in range(n):
        out.append([place, color])
        place += 100 / n
        color += 1
    out.append([100, None])
    return out


def make_m(m, lst_n):
    """
    Donne une liste avec les couleur de la nouvelle partition
    """
    out = []
    place = 0
    for i in range(m):
        out.append([place, what_color(place+( 100 / (2 * m)), lst_n)])
        place += 100 / m
    out.append([100,None])
    return out

def what_color(number, lst_n):
    '''
    donne une couleur de la liste de départ par rapport à un moment 
    de la partition
    '''
    i = 0
    while round(number, 3) > round(lst_n[i][0], 3):
        i += 1
        if round(number, 3) == round(lst_n[i][0], 3):
            return 0
    return lst_n[i-1][1]


n= input('n ?\n')

while n != '':
    
    m = int(input('m ?\n'))
    if n == 'n':
        n = len(lst_n) - 1
    elif n == 'm':
        lst_n = lst_m
        n = len(lst_m) - 1
    else:
        n = int(n)
        lst_n = make_n(n) # liste des couleurs de la partition de départ
    
    lst_m = make_m(m, lst_n) # liste des couleurs de la partition d'arrivé

    for i in range(len(lst_n)-1):
        if i != len(lst_n)-2:
            print(lst_n[i][1], end=' - ')
        else:
            print(lst_n[i][1], '\n\n')
            

    for i in range(len(lst_m)-1):
        if i != len(lst_m)-2:
            print(lst_m[i][1], end=' - ')
        else:
            print(lst_m[i][1], '\n------------\n')
    
    frise(lst_n, 'n')
    frise(lst_m, 'm')
    
    n= input('n ?\n')
    turtle.clear()
    
