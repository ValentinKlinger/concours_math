import turtle
from time import sleep


def frise(lst, posission):
    turtle.ht()
    turtle.penup()
    if posission == "n":
        turtle.setpos((-50 * 2, 20 * 2))
    else:
        turtle.setpos((-50 * 2, -20 * 2))
    turtle.setheading(0)

    turtle.pendown()
    for note in range(len(lst) - 1):
        taille = len(lst) - 1
        turtle.pendown()

        if posission == "m":
            turtle.forward(200 / (taille * 2))
            turtle.left(90)
            turtle.color("red")
            turtle.fd(20 * 2)
            turtle.backward(20 * 2)
            turtle.color("black")
            turtle.right(90)
            turtle.forward(200 / (taille * 2))
        else:
            turtle.forward(200 / taille)
        turtle.right(90)
        turtle.forward(40)
        turtle.right(90)

        turtle.forward(200 / taille)
        turtle.right(90)
        turtle.forward(40)
        turtle.right(90)
        if posission == "m":
            turtle.penup()
            turtle.right(90)
            turtle.forward(60)
            turtle.write(str(lst[note][1]))
            turtle.backward(60)
            turtle.setheading(0)
            turtle.pendown()
        else:
            turtle.write(str(lst[note][1]))
        turtle.forward(200 / taille)


def make_n(n):
    """
    créé une liste de n élément, chaque élément strictement différent des
    autres. La valeur représente la couleur
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
        out.append([place, what_color(place + (100 / (2 * m)), lst_n)])
        place += 100 / m
    out.append([100, None])
    return out


def what_color(number, lst_n):
    """
    donne une couleur de la liste de départ par rapport à un moment
    de la partition
    """
    i = 0
    while round(number, 3) > round(lst_n[i][0], 3):
        i += 1
        if round(number, 3) == round(lst_n[i][0], 3):
            return 0
    return lst_n[i - 1][1]


n = input("n ?\n")

while n != "":
    if n == "f":
        frise(lst_n, "n")
        frise(lst_m, "m")
        sleep(10)
        n = input("n ?\n")
        turtle.reset()

    else:
        m = int(input("m ?\n"))
        if n == "n":
            n = len(lst_n) - 1
        elif n == "m":
            lst_n = lst_m.copy()
            n = len(lst_m) - 1

        else:
            n = int(n)
            lst_n = make_n(n)  # liste des couleurs de la partition de départ

        lst_m = make_m(m, lst_n)  # liste des couleurs de la partition d'arrivé

        for i in range(len(lst_n) - 1):
            if i != len(lst_n) - 2:
                print(lst_n[i][1], end=" - ")
            else:
                print(lst_n[i][1], "\n\n")

        for i in range(len(lst_m) - 1):
            if i != len(lst_m) - 2:
                print(lst_m[i][1], end=" - ")
            else:
                print(lst_m[i][1], "\n------------\n")
    n = input("n ?\n")
