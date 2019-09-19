#### Author:Bowen Wang
#### ID:301267523
#### Date:Jul,28,2016
#### Time:8.5h





##############################################################################################
#### Greet Printing
def greeting():
    print (" Welcome to the Flipping Dance game ")                        
    print (" =====================================")
    print ()
    print ()
    print (" Note: Levels 1, 2 and 3 are implemented;")
    print ("       You will be able to choose your preferred level for each game;")
    print ("       The digit/color you choose only affects the totals but not flips")
    print ()

##############################################################################################
#### Level Slection
def level():
    print(" Which level would you like to play?")
    print("  1 - Basic, user only,")
    print("  2 - Advanced, user and computer,")
    lev=input("  3 - Expert, user and computer: ==> ")
    return lev

##############################################################################################
#### Start Switch
def start():
    start=input(" Would  you like to play? (y/n): ==>")
    print ()
    return start

##############################################################################################
#### Build a Matrix:
def initial(dim):
    print()
    print(" The board is")
    print(" -------------")
    print()
    print(" (initial board)")
    print()
    matrix=[]
    for r in range (dim) :
        matrix.append([])
        for c in range (dim):
            matrix[r].append(random.randint(0,1))
    return matrix

##############################################################################################
#### Print Matrix:
def printmatrix(matrix):
    print("            ",end="")
    for col in range (dim):
        print("Col",col,"       ",end="")
    print('\n',end="")
    for r in range (dim):
        print("Row ",r,"       ",end="")
        for c in range (dim):
            print(matrix[r][c],"           ",end="")
        print('\n')

###############################################################################################
#### Color Slection
def color():
    print ()
    print (" Which digit/color would you like for you?")
    print ("  0 - white,")
    color=int(input("  1 - black: ==> "))
    print ()
    return color

#################################################################################################
#### Position Decision
def position():
    rowstring="row?  (<= "+str(dim-1)+"):"
    colstring="col?  (<= "+str(dim-1)+"):"
    row=(int(input(rowstring)))
    col=(int(input(colstring)))
    print()
    return row,col

#################################################################################################
#### Winner Check
def check():
    global score
    global userwin
    global computerwin
    print("Rows that have an even number of user digit's (",collor,")",'\n')
    totalrow=0
    for r in range (dim):
        addrow=0
        for c in range (dim):
            if matrix[r][c]==collor:
                addrow=addrow+1
        if addrow-1>=0 and addrow%2!=1:
            print(" - Row",r)
            totalrow=totalrow+1
    if totalrow==0:
        print(" - None of the Rows",'\n')
    print("Cols that have an even number of user digit's (",collor,")",'\n')
    totalcol=0
    for c in range (dim):
        addcol=0
        for r in range (dim):
            if matrix[r][c]==collor:
                addcol=addcol+1
        if addrow-1>=0 and addcol%2!=1:
            print(" - Col",c)
            totalcol=totalcol+1
    if totalcol==0:
        print(" - None of the Cols",'\n')
    if totalcol==0 or totalrow==0:
        print("Sorry!  for you to win, the board had to have at least")
        print("one row and one col with an even number of your digit")
        print("but such is nto the case; You had chosen digit 0")
        print("Therefore, I, the computer, win this game!)",'\n')
        computerwin=computerwin+1
    else:
        print("Congratulations! you won this game! ")
        print("You had chosen digit ",collor,'\n')
        print("You got ",totalrow," row with an even number of ",collor,"'s")
        print(" and ",totalcol," col with an even number of ",collor,"'s",'\n')
        print("!!! Therefore, this game gives you: ",totalcol+totalrow," points !!!",'\n')
        userwin=userwin+1
    score=score+totalcol+totalrow
    print('\n','\n')
#################################################################################################
def summary(score,userwin,computerwin,boardvalue):
    print('\n',"TOTALS ALL GAMES")
    print("Total points user in all games: ",score)
    print("Total games the user won: ",userwin)
    print("Total games the computer won: ",computerwin)
    print("Board value  of last board's first row in decimal: ",boardvalue)
#################################################################################################
#### Level 1
def flip1(row,col):
    if matrix[row][col]==0:
        matrix[row][col]=1
    else:
        matrix[row][col]=0
    return matrix

#################################################################################################
#### Level 2
def flip2(row,col):
    for c in range (col,dim):
        if matrix[row][c]==0:
            matrix[row][c]=1
        else:
            matrix[row][c]=0
    for r in range (row+1,dim):
        if matrix[r][col]==0:
            matrix[r][col]=1
        else:
            matrix[r][col]=0
    return matrix

#################################################################################################
#### Level 3
def flip3(row,col):
    if col-1>=0:
        if col+1!=dim:
            for c in range(col-1,col+2):
                if matrix[row][c]==0:
                    matrix[row][c]=1
                else:
                    matrix[row][c]=0
        else:
            for c in range(col-1,col+1):
                if matrix[row][c]==0:
                    matrix[row][c]=1
                else:
                    matrix[row][c]=0
    else:
        for c in range(col,col+2):
            if matrix[row][c]==0:
                matrix[row][c]=1
            else:
                matrix[row][c]=0
    if row-1>=0:
        if row+1!=dim:
            for r in range(row-1,row+2):
                if matrix[r][col]==0:
                    matrix[r][col]=1
                else:
                    matrix[r][col]=0
        else:
            for r in range(row-1,row+1):
                if matrix[r][col]==0:
                    matrix[r][col]=1
                else:
                    matrix[r][col]=0
    else:
        for r in range (row,row+2):
            if matrix[r][col]==0:
                matrix[r][col]=1
            else:
                matrix[r][col]=0
    if matrix[row][col]==0:
        matrix[row][col]=1
    else:
        matrix[row][col]=0
    return matrix

#################################################################################################


## Top of Program
import random
greeting()
score=0                      ###################### Global Variable (Total Score user earned)
computerwin=0                ###################### Global Variable (Total Computer Wins)
userwin=0                    ###################### Global Variable (Total User Wins)
boardvalue=0 
start=input(" Would  you like to play? (y/n): ==>")
print ()
while start=="y":
    lev=level()
    collor=color()
    dim=int(input(" Size of board (between 3 and 6 inclusive): ==>"))
    matrix=initial(dim)
    printmatrix(matrix)
    if lev=="1":
        time = 0 
        while time < dim  :
            print("User, what position are you choosing to flip? (max flips = ",dim,")")
            print("(Type  99   for both row and column, if you do not want to do more flips)")
            print()
            pos=position()
            row=pos[0]
            col=pos[1]
            if col!=99 and row!=99:
                print("The board is",'\n',"-------------",'\n',"(after user played (",row,",",col,"))",'\n')
                matrix=flip1(row,col)
                printmatrix(matrix)
                time=time+1
            else:
                break 
        if time==dim:
            print("This game is over because you reached the maximum allowed flips!",'\n')
            check()
        else:
            print("This game is over because you did not want to flip again!")
            check()
    elif lev=="2":
        time=0
        while time <dim:
            print("User, what position are you choosing to flip? (max flips = ",dim,")")
            print("(Type  99   for both row and column, if you do not want to do more flips)")
            print()
            pos=position()
            row=pos[0]
            col=pos[1]
            if col!=99 and row!=99:
                print("The board is",'\n',"-------------",'\n',"(after user played (",row,",",col,"))",'\n')
                matrix=flip2(row,col)
                printmatrix(matrix)
                comrow=random.randint(0,dim-1)
                comcol=random.randint(0,dim-1)
                print(" NOW ... The comupter played... (",comrow,",",comcol,")",'\n')
                print("The board is",'\n',"-------------",'\n',"(after computer played (",comrow,",",comcol,"))")
                matrix=flip2(comrow,comcol)
                printmatrix(matrix)
                time=time+1
            else:
                break
        if time==dim:
            print("This game is over because you reached the maximum allowed flips!",'\n')
            check()
        else:
            print("This game is over because you did not want to flip again!")
            check()
    elif lev=="3":
        time=0
        while time<dim:
            print("User, what position are you choosing to flip? (max flips = ",dim,")")
            print("(Type  99   for both row and column, if you do not want to do more flips)")
            print()
            pos=position()
            row=pos[0]
            col=pos[1]
            if col!=99 and row!=99:
                print("The board is",'\n',"-------------",'\n',"(after user played (",row,",",col,"))",'\n')
                matrix=flip3(row,col)
                printmatrix(matrix)
                comrow=random.randint(0,dim-1)
                comcol=random.randint(0,dim-1)
                print(" NOW ... The comupter played... (",comrow,",",comcol,")",'\n')
                print("The board is",'\n',"-------------",'\n',"(after computer played (",comrow,",",comcol,"))")
                matrix=flip3(comrow,comcol)
                printmatrix(matrix)
                time=time+1
            else:
                break
        if time==dim:
            print("This game is over because you reached the maximum allowed flips!",'\n')
            check()
        else:
            print("This game is over because you did not want to flip again!")
            check()
    start=input(" Would  you like to play? (y/n): ==>")
for c in range(dim):
    boardvalue=boardvalue+matrix[1][c]*2**(dim-1-c)
summary(score,userwin,computerwin,boardvalue)
            



            

