'''
def ave(a):
    c=0
    i=0
    while i<len(a):
        c=c+int(a[i])
        i=i+1
    c=float(c/len(a))
    return c
val=ave("24")
print(val)


def combine(a,b):
    if b<=len(a):
        a=a[:b]+str(b)+a[b+1:]
    return a
val=combine("s",2)
print(val)


def nospecialchar(a):
    i=0
    c=True
    while i < len(a):
        if a[i].isdigit() or a[i].isalpha():
            i=i+1
        else:
            c= False
            return c
    return c
print(nospecialchar("sgfklg"))
'''
'''
def onlydigits(a):
    i=0
    b=True
    while i<len(a):
        if a[i].isdigit():
            i=i+1
        else:
            b=False
            return b
    return b
print(onlydigits("12346"))


def Enigma(a,b):
    i=0
    c="@"*b
    while i <len(a):
        c=c+a[-i-1]
        i=i+1
    c=c+"@"*b
    return c
print(Enigma("Benedict Cumberbatch",5))
        


def avgOdd(a):
    i=0
    b=0
    c=0
    while i<len(a):
        if a[i].isdigit():
            if int(a[i])%2==1:
                b=b+int(a[i])
                c=c+1
        i=i+1
    if c==0:
        b=0.0
    else:
        b=float(b/c)
    return b
val = avgOdd("121212")
print (val)



def countLowerFromUntil(a,b):
    i=0
    c=0
    if b>len(a):
        return c
    while b<len(a):
        if not a[b].isdigit():
            if a[b].islower():
                c=c+1
        else:
            return c
        b=b+1
    return c
val = countLowerFromUntil("ABCxAxx1aa",1005)
print (val)





def countLower(a):
    i=0
    b=0
    while i<len(a):
        if a[i].islower():
            b=b+1
        i=i+1
    return b
val = countLower("a1a2a3AAAa")
print(val)


def immPairsBool(a):
    i=0
    b=0
    while i<len(a)-1:
        if a[i]==a[i+1]:
            b=b+1
        i=i+1
    return b
val = immPairsBool("abxxxab88ef")
print (val)


def searchVowel(a):
    b=False
    i=0
    vowel="aeiou"
    while i<len(a):
        n=0
        while n<len(vowel):
            if a[i]==vowel[n] or a[i]==vowel[n].upper():
                b=True
                return b
            n=n+1
        i=i+1
    return b
val = searchVowel("---A---")
print(val)


def avgBackw(a):
    i=len(a)-1
    b=0.0
    c=0
    while i>=0:
        if a[i].isdigit():
            b=b+float(a[i])
            c=c+1
        elif a[i].isalpha():
            if c!=0:
                b=float(b/c)
            return b
        
        i=i-1
    b=float(b/c)
    return b
value = avgBackw("-1---2--A--3--4--")
print(value)

def contain(a,b):
    i=0
    c=False
    while i<len(a):
        if a[i]==b:
            c=True
            return c
        i=i+1
    return c

print(contain("abc","d"))

'''
def numletter(a):
    i=0
    b=0
    c=0
    while i<len(a):
        if b==0 and a[i].isalpha():
            b=a[i]
        if a[i].isdigit():
            c=int(a[i])
        i=i+1
    d=b*c
    if a.isalpha() or a.isdigit() or d=="":
        return "***"
    return d
print(numletter("abcd"))































































            
