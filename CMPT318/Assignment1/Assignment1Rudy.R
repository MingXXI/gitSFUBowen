# Get the dataset
Dataset1 <- read.table("Dataset1.txt", header = TRUE, sep = ",")

# Set the variables
A <- Dataset1$Global_active_power
B <- Dataset1$Global_reactive_power
C <- Dataset1$Voltage
D <- Dataset1$Global_intensity

# Set the weekdays and weekend days
dates <- as.POSIXlt(Dataset1$Date, na.rm = T, format = "%d/%m/%Y") # get date format
Dataset1$Day <- weekdays(as.Date(dates)) # add corresponding days to the dataset
day <- Dataset1$Day
weekday <- day == "Monday" | day == "Tuesday" | day == "Wednesday" | day == "Thursday" | day == "Friday"
weekend <- day == "Saturday" | day == "Sunday"

# Geometric Mean function
geomean <- function (x, na.rm = FALSE) {
  if (na.rm == T) {
    x <- x[x > 0]
  }
  return(exp(mean(log(x), na.rm = na.rm)))
}

# Mode function
getmode <- function (x, na.rm = FALSE) {
  uniqx <- unique(x)
  uniqx[which.max(tabulate(match(x, uniqx)))]
}

# Output the results
print("1.")
print(paste("Arithmetic Mean of Global_active_power =", mean(A, na.rm = T)))
print(paste("Arithmetic Mean of Global_reactive_power =", mean(B, na.rm = T)))
print(paste("Geometric Mean of Global_active_power =", geomean(A, na.rm = T)))
print(paste("Geometric Mean of Global_reactive_power =", geomean(B, na.rm = T)))
print(paste("Median of Global_active_power =", median(A, na.rm = T)))
print(paste("Median of Global_reactive_power =", median(B, na.rm = T)))
print(paste("Mode of Global_active_power =", getmode(A, na.rm = T)))
print(paste("Mode of Global_reactive_power =", getmode(B, na.rm = T)))
print(paste("Standard Deviation of Global_active_power =", sd(A, na.rm = T)))
print(paste("Standard Deviation of Global_reactive_power =", sd(B, na.rm = T)))

print("2.")
print(paste("Correlation between Global_active_power and Global_reactive_power =", cor(A, B, use = "complete", method = "pearson")))
print(paste("Correlation between Global_active_power and Voltage =", cor(A, C, use = "complete", method = "pearson")))
print(paste("Correlation between Global_active_power and Global_intensity =", cor(A, D, use = "complete", method = "pearson")))
print(paste("Correlation between Global_reactive_power and Voltage =", cor(B, C, use = "complete", method = "pearson")))
print(paste("Correlation between Global_reactive_power and Global_intensity =", cor(B, D, use = "complete", method = "pearson")))
print(paste("Correlation between Voltage and Global_intensity =", cor(C, D, use = "complete", method = "pearson")))

print("3.")
print(paste("Minimum of Global_active_power on weekdays =", min(A[weekday], na.rm = T)))
print(paste("Minimum of Global_active_power on weekends =", min(A[weekend], na.rm = T)))
print(paste("Maximum of Global_active_power on weekdays =", max(A[weekday], na.rm = T)))
print(paste("Maximum of Global_active_power on weekends =", max(A[weekend], na.rm = T)))
print(paste("Minimum of Global_reactive_power on weekdays =", min(B[weekday], na.rm = T)))
print(paste("Minimum of Global_reactive_power on weekends =", min(B[weekend], na.rm = T)))
print(paste("Maximum of Global_reactive_power on weekdays =", max(B[weekday], na.rm = T)))
print(paste("Maximum of Global_reactive_power on weekends =", max(B[weekend], na.rm = T)))