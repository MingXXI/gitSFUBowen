
def abc( ):
    global player_level
    player_level= input("1st")
    a= player_level.isdigit()
    b= player_level.isalpha()
    c= False
    if a == True:
        if int(player_level)<=3 and int(player_level)>=0:
            c=True
    d[0]=a
    d[1]=b
    d[2]=c
    return d

d=[False,False,False]
while d!=[True,False,True]:
    abc()
print(player_level)
        
