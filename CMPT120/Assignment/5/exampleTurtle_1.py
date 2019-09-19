### CMPT 120
###  turtles - first example for lab
###  not defining our own functions yet
###  but probably you may want to define
###  a function to draw a square
###
###  author: Diana Cukierman

#####

def  square():
    # draw a square
    # do not return anything
    #
    # to call or invoke the function: just use in the top level:
    #
    # square()
    #
    return



# TOP LEVEL

import turtle as t


# black  square Version 1
t.forward (100)
t.left(90)
t.forward (100)
t.left(90)
t.forward (100)
t.left(90)
t.forward (100)
t.left(90)

# advancing pen forward
t.penup()
t.forward(150)
t.pendown()

# black square V2
for i in range(4):
    t.forward (100)
    t.left(90)

# moving  pen higher
t.penup()
t.left(90)
t.forward(150)
t.pendown()
t.right(90)  # it's again facing forward

# red square V2
t.pencolor("red")
for i in range(4):
    t.forward (100)
    t.left(90)

# advancing pen backward
t.penup()
t.backward(150)
t.pendown()

t.width(3) # thicker line

# blue square 
t.pencolor("blue")
for i in range(4):
    t.forward (100)
    t.left(90)

# advancing pen backward
t.penup()
t.backward(150)
t.pendown()

# filling the square with a color 
t.pencolor("green")
t.fillcolor("violet")
t.begin_fill()
for i in range(4):
    t.forward (100)
    t.left(90)
t.end_fill()

### end of program

    




    
    

