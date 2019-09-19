library("depmixS4")


train <- read.table("Train Data.txt", header = T, sep = ",")
test1 <- read.table("test1.txt", header = T, sep = ",")
test2 <- read.table("test2.txt", header = T, sep = ",")
test3 <- read.table("test3.txt", header = T, sep = ",")
test4 <- read.table("test4.txt", header = T, sep = ",")
test5 <- read.table("test5.txt", header = T, sep = ",")


dates1 <- as.POSIXlt(test1$Date, na.rm = T, format = "%d/%m/%Y") # get date format
test1$Day <- weekdays(as.Date(dates1)) # add corresponding days to the dataset
sunday1 <- test1$Day == "Sunday"
monday1 <- test1$Day == "Monday"
times <- format(test1$Time, na.rm = T, format = "%H:%M:%S")
sundayMornings1 <- subset(test1, sunday1 & times >= "08:00:00" & times <= "11:00:00")
sundayNights1 <- subset(test1, (sunday1 & times >= "21:00:00" & times <= "23:59:00") | (monday1 & times == "00:00:00"))
sundayNights1 <- sundayNights1[-1,]

dates2 <- as.POSIXlt(test2$Date, na.rm = T, format = "%d/%m/%Y") # get date format
test2$Day <- weekdays(as.Date(dates2)) # add corresponding days to the dataset
sunday2 <- test2$Day == "Sunday"
monday2 <- test2$Day == "Monday"
times <- format(test2$Time, na.rm = T, format = "%H:%M:%S")
sundayMornings2 <- subset(test2, sunday2 & times >= "08:00:00" & times <= "11:00:00")
sundayNights2 <- subset(test2, (sunday2 & times >= "21:00:00" & times <= "23:59:00") | (monday2 & times == "00:00:00"))
sundayNights2 <- sundayNights2[-1,]

dates3 <- as.POSIXlt(test3$Date, na.rm = T, format = "%d/%m/%Y") # get date format
test3$Day <- weekdays(as.Date(dates3)) # add corresponding days to the dataset
sunday3 <- test3$Day == "Sunday"
monday3 <- test3$Day == "Monday"
times <- format(test3$Time, na.rm = T, format = "%H:%M:%S")
sundayMornings3 <- subset(test3, sunday3 & times >= "08:00:00" & times <= "11:00:00")
sundayNights3 <- subset(test3, (sunday3 & times >= "21:00:00" & times <= "23:59:00") | (monday3 & times == "00:00:00"))
sundayNights3 <- sundayNights3[-1,]

dates4 <- as.POSIXlt(test4$Date, na.rm = T, format = "%d/%m/%Y") # get date format
test4$Day <- weekdays(as.Date(dates4)) # add corresponding days to the dataset
sunday4 <- test4$Day == "Sunday"
monday4 <- test4$Day == "Monday"
times <- format(test4$Time, na.rm = T, format = "%H:%M:%S")
sundayMornings4 <- subset(test4, sunday4 & times >= "08:00:00" & times <= "11:00:00")
sundayNights4 <- subset(test4, (sunday4 & times >= "21:00:00" & times <= "23:59:00") | (monday4 & times == "00:00:00"))
sundayNights4 <- sundayNights4[-1,]

dates5 <- as.POSIXlt(test5$Date, na.rm = T, format = "%d/%m/%Y") # get date format
test5$Day <- weekdays(as.Date(dates5)) # add corresponding days to the dataset
sunday5 <- test5$Day == "Sunday"
monday5 <- test5$Day == "Monday"
times <- format(test5$Time, na.rm = T, format = "%H:%M:%S")
sundayMornings5 <- subset(test5, sunday5 & times >= "08:00:00" & times <= "11:00:00")
sundayNights5 <- subset(test5, (sunday5 & times >= "21:00:00" & times <= "23:59:00") | (monday5 & times == "00:00:00"))
sundayNights5 <- sundayNights5[-1,]




sunmgap1<- sundayMornings1[,3]
sunmgap2<- sundayMornings2[,3]
sunmgap3<- sundayMornings3[,3]
sunmgap4<- sundayMornings4[,3]
sunmgap5<- sundayMornings5[,3]


smmean1 <- mean(sunmgap1)
smsd1 <- sd(sunmgap1)
smupperbound1 <- smmean1 + 2.81*smsd1
smlowerbound1 <- smmean1 - 2.81*smsd1

smmean2 <- mean(sunmgap2)
smsd2 <- sd(sunmgap2)
smupperbound2 <- smmean2 + 2.81*smsd2
smlowerbound2 <- smmean2 - 2.81*smsd2

smmean3 <- mean(sunmgap3)
smsd3 <- sd(sunmgap3)
smupperbound3 <- smmean3 + 2.81*smsd3
smlowerbound3 <- smmean3 - 2.81*smsd3

smmean4 <- mean(sunmgap4)
smsd4 <- sd(sunmgap4)
smupperbound4 <- smmean4 + 2.81*smsd4
smlowerbound4 <- smmean4 - 2.81*smsd4

smmean5 <- mean(sunmgap5)
smsd5 <- sd(sunmgap5)
smupperbound5 <- smmean5 + 2.81*smsd5
smlowerbound5 <- smmean5 - 2.81*smsd5

print(paste("the interval of Sunday morning in test1 is: (",smlowerbound1,",",smupperbound1,")"))
print(paste("the interval of Sunday morning in test2 is: (",smlowerbound2,",",smupperbound2,")"))
print(paste("the interval of Sunday morning in test3 is: (",smlowerbound3,",",smupperbound3,")"))
print(paste("the interval of Sunday morning in test4 is: (",smlowerbound4,",",smupperbound4,")"))
print(paste("the interval of Sunday morning in test5 is: (",smlowerbound5,",",smupperbound5,")"))






sngap1<- sundayNights1[,3]
sngap2<- sundayNights2[,3]
sngap3<- sundayNights3[,3]
sngap4<- sundayNights4[,3]
sngap5<- sundayNights5[,3]


snmean1 <- mean(sngap1)
snsd1 <- sd(sngap1)
snupperbound1 <- snmean1 + 2.81*snsd1
snlowerbound1 <- snmean1 - 2.81*snsd1

snmean2 <- mean(sngap2)
snsd2 <- sd(sngap2)
snupperbound2 <- snmean2 + 2.81*snsd2
snlowerbound2 <- snmean2 - 2.81*snsd2

snmean3 <- mean(sngap3)
snsd3 <- sd(sngap3)
snupperbound3 <- snmean3 + 2.81*snsd3
snlowerbound3 <- snmean3 - 2.81*snsd3

snmean4 <- mean(sngap4)
snsd4 <- sd(sngap4)
snupperbound4 <- snmean4 + 2.81*snsd4
snlowerbound4 <- snmean4 - 2.81*snsd4

snmean5 <- mean(sngap5)
snsd5 <- sd(sngap5)
snupperbound5 <- snmean5 + 2.81*snsd5
snlowerbound5 <- snmean5 - 2.81*snsd5

print(paste("the interval of Sunday night in test1 is: (",snlowerbound1,",",snupperbound1,")"))
print(paste("the interval of Sunday night in test2 is: (",snlowerbound2,",",snupperbound2,")"))
print(paste("the interval of Sunday night in test3 is: (",snlowerbound3,",",snupperbound3,")"))
print(paste("the interval of Sunday night in test4 is: (",snlowerbound4,",",snupperbound4,")"))
print(paste("the interval of Sunday night in test5 is: (",snlowerbound5,",",snupperbound5,")"))





###############################################