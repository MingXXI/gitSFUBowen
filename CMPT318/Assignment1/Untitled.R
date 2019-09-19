dataset <- read.table("Dataset1.txt", header=TRUE, sep=",") #525600 with NA values
require( lubridate )
library("depmixS4")

dataset <- na.omit(dataset) #521860 with na values omitted.
dataset$Date <- as.POSIXlt(dataset$Date, na.rm = TRUE, format ="%d/%m/%y")$wday
sunday <- dataset[which(dataset$Date == 0),]
sunday$Time <- hms(sunday$Time)

sundayEvening <- sunday
sundayMorning <- sunday

sundayMorning <- subset(sundayMorning, as.numeric(Time) >= 28800 & as.numeric(Time) <= 43200)
sundayEvening <- subset(sundayEvening, (as.numeric(Time) >= 75600 & as.numeric(Time) < 86400) |  as.numeric(Time) == 0)