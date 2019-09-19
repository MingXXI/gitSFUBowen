#### Author:Bowen Wang
#### ID:301267523



### Welcome message
print("Welcome to the CMPT 120 Password Generator!","\n","Please follow the system prompts","\n"*2)
### Input
name=input("Please type your first and last names,(separated with a space):")
age=int(input("Please type your age:"))
course=input("Please type the name of one course,(first and second part separated by a dash (-) :")
str1=" "
str2="-"
print("")
print("Processing...","\n"*2)
### Caculations
a=name[1].upper()
lastname=name.find(str1)
b=name[lastname+1]+name[lastname+2]
c=name[-1]
tens=int(age//10)
d=str("*"*tens)
integer=int(course.find(str2))
e=str("$"* int(int(age)**0.5))
f=course[integer-1]
second=course[integer+1:]

if second.isdigit()==True:
    g=second[-1]
else:
    g=""
code=a+b+c+d+e+f+g
num=int(len(code))
if num%2==0:
    h="E"
else:
    h=""
code=code+h
###Trace
print("    TRACE - square root of age is:",int(age)**0.5,"\n"*2)
### Result
print("The final result is ready! Your password is:",code,"\n"*2,"Bye!")

