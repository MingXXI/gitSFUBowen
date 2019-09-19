#################### 3.A

for (i in 1:181){
  GAPMorning[i] <- mean(sundayMorning$Global_active_power[which(as.numeric(sundayMorning$Time)==(28740+(60*i)))])
  GRPMorning[i] <- mean(sundayMorning$Global_reactive_power[which(as.numeric(sundayMorning$Time)==(28800+60*(i-1)))])
  VMorning[i] <- mean(sundayMorning$Voltage[which(as.numeric(sundayMorning$Time)==(28800+60*(i-1)))])
  GIMorning[i] <- mean(sundayMorning$Global_intensity[which(as.numeric(sundayMorning$Time)==(28800+60*(i-1)))]) 
}


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

plot(1:181, GAPMorning, xlab = "Minutes from 8AM", ylab = "Global Active Power on Sunday Morning", type = "l")
plot(1:181, GAPEvening, xlab = "Minutes from 9PM", ylab = "Global Active Power on Sunday Evening", type = "l")
 