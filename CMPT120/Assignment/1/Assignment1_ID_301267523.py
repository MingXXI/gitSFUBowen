### Bowen Wang
### May,28,2016
### 3 Hours
### Assignment 1(A program which is able to achieve unit conversion and basic comparasion)


print("Please provide the data for the first runner")
kilometers= int(input("Number of kilometers (km):"))
meters= int(input("Number of meters(m)(between 1 and 999 inclusive):"))
centimeters= int(input("Number of centimeters(cm) (between 1 and 99 inclusive):"))
print("")

print("Please provide the data for the second runner")
mile = int(input("Number of miles (mi):"))
yard = int(input("Number of yards (yd) (between 1 and 1759 inclusive):"))
feet = int(input("Number of feet (ft) (between 1 and 99 inclusive):"))
print("")

print("FIRST RESULT:distance of second runner in ft and in cm:")
second_in_feet = mile * 5280 + yard * 3 + feet
second_in_cm = second_in_feet * 30.48
print("The second runner all in ft is:",second_in_feet,"ft")
print("The second runner all in cm (1ft = 30.48 cm) is:",second_in_cm," cm")
print("")

first_in_cm=100000*kilometers+100*meters+centimeters
difference=abs(round(first_in_cm-second_in_cm,2))

print("SECOND RESULT: difference between the two runners in cm is:",difference,"cm")
print("")

dkm=int(difference//100000)
dm=int(difference%100000//100)
dcm=int(difference%100000%100)
print("THIRD RESULT: The difference is also expressible as:",dkm,"km ",dm,"m ",dcm,"cm")
print("")
print("End of the program! Bye! ")

