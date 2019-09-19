

Ass1data <- read.table("Dataset1.txt", header = T, sep = ",")

Ass1data$Date <- as.POSIXlt(Ass1data$Date, na.rm=T, format = "%d/%m/%Y")$wday ## Modify date to 

WDdata <- Ass1data[which(Ass1data$Date>=1 & Ass1data$Date<=5),] ## Weekday data
WEdata <- Ass1data[which(Ass1data$Date==0 | Ass1data$Date==6),] ## Weekend data

gm_mean = function(x, na.rm=TRUE){    #### Geometric mean function
  exp(mean(log(x[x > 0]), na.rm=na.rm))
}
modecal = function(x, na.rm = True){  #### Mode function
  uniqx <- unique(x)
  uniqx[which.max(tabulate(match(x, uniqx)))]
}

GAP<- Ass1data[,3]
GRP<- Ass1data[,4]
V <- Ass1data[,5]
GI <- Ass1data[,6]
date<- Ass1data[,1]


meana = mean(GAP, na.rm=T)
meanb = mean(GRP, na.rm = T)
geoa = gm_mean(GAP, na.rm = T)
geob = gm_mean(GRP, na.rm = T)

mediana = median(GAP, na.rm=T)
medianb = median(GRP, na.rm = T)

modea = modecal(GAP)
modeb = modecal(GRP)


## Part 2

corab = cor(GAP,GRP,use = "complete.obs", method="pearson")
corac = cor(GAP,V,use = "complete.obs", method="pearson")
corad = cor(GAP,GI,use = "complete.obs", method="pearson")
corbc = cor(GRP,V,use = "complete.obs", method="pearson")
corbd = cor(GRP,GI,use = "complete.obs", method="pearson")
corcd = cor(V,GI,use = "complete.obs", method="pearson")

##Part 3

WDmaxa = max(WDdata$Global_active_power,na.rm = T)
WDmaxb = max(WDdata$Global_reactive_power,na.rm = T)
WDmina = min(WDdata$Global_active_power,na.rm = T)
WDminb = min(WDdata$Global_reactive_power,na.rm = T)

WEmaxa = max(WEdata$Global_active_power,na.rm = T)
WEmaxb = max(WEdata$Global_reactive_power,na.rm = T)
WEmina = min(WEdata$Global_active_power,na.rm = T)
WEminb = max(WEdata$Global_reactive_power,na.rm = T)

## Part1 output
print(meana)
print(meanb)
print(geoa)
print(geob)
print(mediana)
print(medianb)
print(modea)
print(modeb)

## Part2 output
print(corab)
print(corac)
print(corad)
print(corbc)
print(corbd)
print(corcd)

## Part3 output
print(WDmaxa)
print(WDmaxb)
print(WDmina)
print(WDminb)

print(WEmaxa)
print(WEmaxb)
print(WEmina)
print(WEminb)





