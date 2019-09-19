#### Author:Bowen Wang
#### ID:301267523
#### July 3, 2016
#### 6.5 Hours
#### Assignment 5(Turtle Artist: Drawing with turtle built-in function)

import turtle as t
import math as m
import random
t.speed(10)


def calcos(a):
    cos=m.cos(m.radians(a))
    return cos
def calsin(b):
    cos=m.sin(m.radians(b))           ## Define a function to calculate useful data 
    return cos
a=calcos(18)
b=calsin(18)                          ## Invoke calculation function

### Start Drawing
t.hideturtle()
def star():
    for i in range (5):
        t.forward (2*110*a)
        t.right(144)                  ## Define a function to draw a star
def circle(num,x,y):
    for o in range (num):
        if o%2==0:
            t.fillcolor("red")
            t.begin_fill()
        elif o==1:
            t.fillcolor("white")
            t.begin_fill()
        else :
            t.fillcolor("blue")
            t.begin_fill()
        t.up()
        t.goto(x,y+2*(100-15*o))
        t.down()
        t.circle(-(200-30*o))
        t.end_fill()                   ## Define a function to draw 4 concentric circle

### Add a hat
def hat(x,y,col):
    col=random.randint(col-25,col+25)
    t.colormode(255)
    col=(col,255,0)
    t.pencolor(col)
    t.fillcolor(col)
    
    t.up()
    t.goto(x-200,y+200)
    t.down()
    t.forward(400)
    t.up()
    t.goto(x+100,y+200)
    t.down()
    t.begin_fill()
    for p in range(3):
        if p%2==0:
            t.left(90)
            t.forward(100)
        else :
            t.left (90)
            t.forward(200)
    t.end_fill()                        ## Define a function to draw a hat on concentric circle

circle(4,0,0)                           ## Invoke circle function
t.pencolor("white")
t.right(72)
t.fillcolor("white")
t.begin_fill()
star()                                  ##Invoke star function
t.end_fill()
t.left(72)

t.width(5)
hat(0,0,127)                            ##Invoke hat Function

## End of Drawing
