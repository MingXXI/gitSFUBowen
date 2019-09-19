##  CMPT 120
##  author: Diana Cukierman
##
##  some useful functions that can be used with turtles
##
##  
## notice:
##     - first line of documentation: USEFUL!! (is shown when typying to call
##       the function)
##
##     - including in the documentation the TYPE OF THE FUNCTION
##       (type of parameter/s and of what is returned)
##
##     - defining functions with or without paramenters
##     - defining productive and non-productive (or void) functions
##     - calling functions more than once, and with different values for
##       the parameters
##     - creating and using colors with the red,green, blue code
##     - importing the turtle and random modules in the top level
         #( the t which is used inside the functions is the same as
         #  the one outside the function, coming from
         #  import turtle as t)


def square_side100_noloop():
    '''
    draws a square of side 100 version noloop
    it is much better if we do a for loop instead!
    
    it is a non-productive function (no values are returned)
    also, it does not have any parameter
    (hence the type of the function is: 
    () --> ()
    '''
    
    t.fd(100)
    t.left(90)
    t.fd(100)
    t.left(90)
    t.fd(100)
    t.left(90)
    t.fd(100)
    t.left(90)
    return

def square_side100():
    '''
    draws a square of side 100.
    it uses a for loop which is much more reasonable
    
    it is a non-productive function (no values are returned)
    also, it does not have any parameter
    (hence the type of the function is: 
    () --> ()
    '''
    for i in range(4):
        t.forward(100)
        t.left(90)
    return

def square(side):
    '''
    draws a square of side size
    non-productive function
    it only draws
    it receives one parameter: the side for the square.
    This makes the function more flexible, allowing
    to draw a square of differnt side size depending on the
    value in the parameter variable.
    TYPE:  int --> ()
    '''
    for i in range(4):
        t.forward(side)
        t.left(90)
    return


def startAgain():
    '''
    clears and sends turtle back to original position
    () --> ()
    '''
    t.penup()
    t.home()  ## no drawing will be made when going to the 'home'
              ## position because the pen is up
    t.pendown()
    t.clear()
    return

def randomColor():
    '''
    returns a color (red,green,blue)
    a productive function, returning a 3-tuple, that is, three values
    are returned.  These three values  form a color.
    
    TYPE OF THE FUNCTION: () --> (int,int,int)
    
    NOTICE:
    1) This funciton uses the random module which is imported at
    the top level: import random
   
    2) to use colors coded this way the function t.colormode(255)
    had to be called before once. This is done at the top level
    '''
    red = random.randint(0,255)
    green = random.randint(0,255)
    blue = random.randint(0,255)
    colorToReturn = (red,green,blue)
    return colorToReturn

def square_with_color(side,color):
    '''
    draws square side size filled with color
    non-productive function
    it only draws
    it receives TWO parameters: the side for the square, and a color to fill.

    TYPE:  int x (int,int,int) --> ()
    '''

    t.fillcolor(color)
    t.begin_fill()

    ### CALLING square, A PREVIOUSLY DEFINED FUNCTION!
    ### NOTICE HOW WE USE ONE OF THE PARAMETERS IN THIS FUNCTION
    ### AS AN ARGUMENT TO CALL ANOTHER FUNCTION
    
    square(side)

    t.end_fill()
    return
        

## TOP LEVEL

import turtle as t
import random


# -------------------   CALLING FUNCTIONS:
#                       drawing some squares

## TO TEST - COMMEN AND COMMENT OUT


square_side100_noloop()
t.fd(20)
square_side100()
t.fd(20)
square(100)



# -------------------   cleaning the drawing window and
#                       placing the pen in the origin again
startAgain()

#-------------------- drawing many squares, one after the other

square(100)
square(150)
square(200)
square(250)

# -------------------   
startAgain()


# We can pass to the function any expression, including variables:
#  in this case, size


size = int(input("what size of square side? : "))
square(size)

square(size + 100)


#-------------------- drawing many squares, one after the other
#                     we can use a for loop

for i in range(4):
    distance = i * 50
    square(distance)    # CALLING THE FUNCTION WITH A VARIABLE (distance)
                        # AS AN ARGUMENT 
    t.fd(30)
                

####  COLOR MODE (RED, GREEN, BLUE)  
startAgain()


######-----------  important to be able ot use the
                   # red,green,blue color codes:
                   # SHOULD INCLUDE t.colormode(255)
                   # ONLY ONCE AT THE TOP LEVEL
t.colormode(255)

#### here we are calling the randomColor function
col = randomColor()
square_with_color(100,col)

col = randomColor()  # another random color is returned by the function
t.fd(150)
square_with_color(100,col)


### Another  useful detail for turtles

#### ---------------- changing the width of the pen

startAgain()

print (" the current width is ", t.width())
t.width(3)
print (" after changing it now the  width is ", t.width())

t.fd(200)

square(100)



## notice that there are in fact two possible functions width()
## 
## without arguments, it provides the current width that the turtle pen has
## with an argument, it changes the pen width (or thickness)
## to the values passed as argument

print ("END OF TESTS!")

### END OF PROGRAM



    
    



    
