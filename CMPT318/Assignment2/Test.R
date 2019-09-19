library("depmixS4")
require( lubridate )
library("ggplot2")

# Get the dataset
dataset <- read.table("Dataset2.txt", header = TRUE, sep = ",")
##dataset <- na.omit(dataset) #521860 with na values omitted.

dates <- as.POSIXlt(dataset$Date, na.rm = T, format = "%d/%m/%Y") # get date format
dataset$Day <- weekdays(as.Date(dates)) # add corresponding days to the dataset
day <- dataset$Day
weekday <- day == "Monday" | day == "Tuesday" | day == "Wednesday" | day == "Thursday" | day == "Friday"
weekend <- day == "Saturday" | day == "Sunday"
sunday <- dataset[which(dataset$Day == "Sunday"),]

##########
sunday$Time <- hms(sunday$Time)
sundayEvening <- sunday
sundayMorning <- sunday

sundayMorning <- subset(sundayMorning, as.numeric(Time) >= 28800 & as.numeric(Time) <= 39600)
sundayEvening <- subset(sundayEvening, (as.numeric(Time) >= 75600 & as.numeric(Time) < 86400) |  as.numeric(Time) == 0)

###############################################

ntimes1 <- c(181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181,181)
##sundayMorning <- na.omit(sundayMorning) #521860 with na values omitted.
BICs <- vector("list",10)

##set.seed(1)
##for (i in 2:5){
##  mod <- depmix(response = Voltage ~ 1, data = sundayMorning, nstates = i, ntimes = ntimes1)
##  fm <- fit(mod)
  
##  BICs[i] <- BIC(fm)
##}
##plot(2:5,unlist(BICs),ty = "b")



GAPMorning <- vector("list",181)
GRPMorning <- vector("list",181)
VMorning <- vector("list",181)
GIMorning <- vector("list",181)

GAPEvening <- vector("list",181)
GRPEvening <- vector("list",181)
VEvening <- vector("list",181)
GIEvening <- vector("list",181)


################# Calculate mean of each element on Sunday Mornings and store in lists

for (i in 1:181){
  GAPMorning[i] <- mean(sundayMorning$Global_active_power[which(as.numeric(sundayMorning$Time)==(28800+60*(i-1)))])
  GRPMorning[i] <- mean(sundayMorning$Global_reactive_power[which(as.numeric(sundayMorning$Time)==(28800+60*(i-1)))])
  VMorning[i] <- mean(sundayMorning$Voltage[which(as.numeric(sundayMorning$Time)==(28800+60*(i-1)))])
  GIMorning[i] <- mean(sundayMorning$Global_intensity[which(as.numeric(sundayMorning$Time)==(28800+60*(i-1)))]) 
}



################# Calculate mean of each element on Sunday Evening and store in lists

for (i in 1:181){
  if (i == 181){
    GAPEvening[i] <- mean(sundayEvening$Global_active_power[which(as.numeric(sundayEvening$Time)==0)])
    GRPEvening[i] <- mean(sundayEvening$Global_reactive_power[which(as.numeric(sundayEvening$Time)==0)]) 
    GIEvening[i] <- mean(sundayEvening$Global_intensity[which(as.numeric(sundayEvening$Time)==0)]) 
    VEvening[i] <- mean(sundayEvening$Voltage[which(as.numeric(sundayEvening$Time)==0)]) 
  }else{
    GAPEvening[i] <- mean(sundayEvening$Global_active_power[which(as.numeric(sundayEvening$Time)==(75600+60*(i-1)))]) 
    GRPEvening[i] <- mean(sundayEvening$Global_reactive_power[which(as.numeric(sundayEvening$Time)==(75600+60*(i-1)))]) 
    GIEvening[i] <- mean(sundayEvening$Global_intensity[which(as.numeric(sundayEvening$Time)==(75600+60*(i-1)))]) 
    VEvening[i] <- mean(sundayEvening$Voltage[which(as.numeric(sundayEvening$Time)==(75600+60*(i-1)))]) 
  } 
}

plot(1:181, unlist(GAPEvening), ty = "o")




#################### 3.B

sundaydate <- unique(sundayMorning$Date)


weekeveningmin <- vector()
weekeveningmax <- vector()
weekeveningavg <- vector()
weekeveningsd  <- vector()  
weekmorningmin <- vector()
weekmorningmax <- vector()
weekmorningavg <- vector()
weekmorningsd  <- vector()  ###defining weekly statistical measurements

monthmorningmin <- vector()
monthmorningmax <- vector()
monthmorningavg <- vector()
monthmorningsd  <- vector()
montheveningmin <- vector()
montheveningmax <- vector()
montheveningavg <- vector()
montheveningsd  <- vector() ###defining monthly statistical measurements

seasonmorningmin <- vector()
seasonmorningmax <- vector()
seasonmorningavg <- vector()
seasonmorningsd  <- vector()  
seasoneveningmin <- vector()
seasoneveningmax <- vector()
seasoneveningavg <- vector()
seasoneveningsd  <- vector()  ##defining seasonal statistical measurements

i = 0
for (Date in sundaydate){
  i <- i + 1
  minlist <- sort(sundayMorning$Global_active_power[which(sundayMorning$Date == Date)])
  maxlist <- sort(minlist,decreasing = T)
  weekmorningmin[i] <- minlist[1]
  weekmorningmax[i] <- maxlist[1]
  weekmorningavg[i] <- mean(minlist)
  weekmorningsd[i]  <- sd(minlist)
  
  minlist <- sort(sundayEvening$Global_active_power[((181*i)-180):(181*i)])
  maxlist <- sort(minlist,decreasing = T)
  weekeveningmin[i] <- minlist[1]
  weekeveningmax[i] <- maxlist[1]
  weekeveningavg[i] <- mean(minlist)
  weekeveningsd[i]  <- sd(minlist)
}

months <- (1:12)

for (i in 1:12){
  targetmon <- subset(sundayMorning, month(sundayMorning$Date) == i)
  minlist <- sort(targetmon$Global_active_power)
  maxlist <- sort(minlist,decreasing = T)
  monthmorningmin[i] <- minlist[1]
  monthmorningmax[i] <- maxlist[1]
  monthmorningavg[i] <- mean(minlist)
  monthmorningsd[i]  <- sd(minlist)
  
  targetmon <- subset(sundayEvening, month(sundayEvening$Date) == i)
  minlist <- sort(targetmon$Global_active_power)
  maxlist <- sort(minlist,decreasing = T)
  montheveningmin[i] <- minlist[1]
  montheveningmax[i] <- maxlist[1]
  montheveningavg[i] <- mean(minlist)
  montheveningsd[i]  <- sd(minlist)
}


for (i in 1:4){
  
  if (((3*i)+2) < 12){
    targetseason <- subset(sundayMorning, month(sundayMorning$Date) >= (3*i) & month(sundayMorning$Date) <= ((3*i)+2))
    minlist <- sort(targetseason$Global_active_power)
    maxlist <- sort(minlist,decreasing = T)
    seasonmorningmin[i] <- minlist[1]
    seasonmorningmax[i] <- maxlist[1]
    seasonmorningavg[i] <- mean(minlist)
    seasonmorningsd[i]  <- sd(minlist)
    
    targetseason <- subset(sundayEvening, month(sundayEvening$Date) >= (3*i) & month(sundayEvening$Date) <= ((3*i)+2))
    minlist <- sort(targetseason$Global_active_power)
    maxlist <- sort(minlist,decreasing = T)
    seasoneveningmin[i] <- minlist[1]
    seasoneveningmax[i] <- maxlist[1]
    seasoneveningavg[i] <- mean(minlist)
    seasoneveningsd[i]  <- sd(minlist)
  }else{
    targetseason <- subset(sundayMorning, month(sundayMorning$Date) == 1 | month(sundayMorning$Date) == 12 | month(sundayMorning$Date) == 2)
    minlist <- sort(targetseason$Global_active_power)
    maxlist <- sort(minlist,decreasing = T)
    seasonmorningmin[i] <- minlist[1]
    seasonmorningmax[i] <- maxlist[1]
    seasonmorningavg[i] <- mean(minlist)
    seasonmorningsd[i]  <- sd(minlist)
    
    targetseason <- subset(sundayEvening, month(sundayEvening$Date) == 1 | month(sundayEvening$Date) == 12 | month(sundayEvening$Date) == 2)
    minlist <- sort(targetseason$Global_active_power)
    maxlist <- sort(minlist,decreasing = T)
    seasoneveningmin[i] <- minlist[1]
    seasoneveningmax[i] <- maxlist[1]
    seasoneveningavg[i] <- mean(minlist)
    seasoneveningsd[i]  <- sd(minlist)
  }
}


plot(1:12,monthmorningmin, xlab ='Month', ylab = 'Monthly Min on Sunday Morning', type = "o")
plot(1:12,monthmorningmax, xlab ='Month', ylab = 'Monthly Max on Sunday Morning', type = "o")
plot(1:12,monthmorningavg, xlab ='Month', ylab = 'Monthly Avg on Sunday Morning', type = "o")
plot(1:12,monthmorningsd,  xlab ='Month', ylab = 'Monthly Sd on Sunday Morning',  type = "o")
plot(1:12,montheveningmin, xlab ='Month', ylab = 'Monthly Min on Sunday Evening', type = "o")
plot(1:12,montheveningmax, xlab ='Month', ylab = 'Monthly Max on Sunday Evening', type = "o")
plot(1:12,montheveningavg, xlab ='Month', ylab = 'Monthly Avg on Sunday Evening', type = "o")
plot(1:12,montheveningsd,  xlab ='Month', ylab = 'Monthly Sd on Sunday Evening',  type = "o")


plot(1:52,weekmorningmin, xlab ='Week', ylab = 'Weekly Min on Sunday Morning', type = "o")
plot(1:52,weekmorningmax, xlab ='Week', ylab = 'Weekly Max on Sunday Morning', type = "o")
plot(1:52,weekmorningavg, xlab ='Week', ylab = 'Weekly Avg on Sunday Morning', type = "o")
plot(1:52,weekmorningsd,  xlab ='Week', ylab = 'Weekly Sd on Sunday Morning',  type = "o")
plot(1:52,weekeveningmin, xlab ='Week', ylab = 'Weekly Min on Sunday Evening', type = "o")
plot(1:52,weekeveningmax, xlab ='Week', ylab = 'Weekly Max on Sunday Evening', type = "o")
plot(1:52,weekeveningavg, xlab ='Week', ylab = 'Weekly Avg on Sunday Evening', type = "o")
plot(1:52,weekeveningsd,  xlab ='Week', ylab = 'Weekly Sd on Sunday Evening',  type = "o")



plot(1:4,seasonmorningmin, xlab ='Season', ylab = 'Seasonal Min on Sunday Morning', type = "o")
plot(1:4,seasonmorningmax, xlab ='Season', ylab = 'Seasonal Max on Sunday Morning', type = "o")
plot(1:4,seasonmorningavg, xlab ='Season', ylab = 'Seasonal Avg on Sunday Morning', type = "o")
plot(1:4,seasonmorningsd,  xlab ='Season', ylab = 'Seasonal Sd on Sunday Morning',  type = "o")
plot(1:4,seasoneveningmin, xlab ='Season', ylab = 'Seasonal Min on Sunday Evening', type = "o")
plot(1:4,seasoneveningmax, xlab ='Season', ylab = 'Seasonal Max on Sunday Evening', type = "o")
plot(1:4,seasoneveningavg, xlab ='Season', ylab = 'Seasonal Avg on Sunday Evening', type = "o")
plot(1:4,seasoneveningsd,  xlab ='Season', ylab = 'Seasonal Sd on Sunday Evening',  type = "o")


