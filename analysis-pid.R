library(jsonlite)
library(data.table)
library(ggplot2)

tracker.p <- stream_in(file("src/tracker_P.json"))
tracker.pd <- stream_in(file("src/tracker_PD.json"))
tracker.pid <- stream_in(file("src/tracker_PID.json"))

setDT(tracker.p)
setDT(tracker.pd)
setDT(tracker.pid)

tracker.p[, controler := "P"]
tracker.pd[, controler := "PD"]
tracker.pid[, controler := "PID"]

tracker = rbind(
  tracker.p, 
  tracker.pd,
  tracker.pid
)

p <- ggplot(tracker[counter < 1700], aes(x = counter, y = error, colour = controler))
p <- p + geom_line()
p <- p + theme_bw()
p <- p + labs(
  title = "Plot of errors along the timeline",
  subtitle = "While PD controler diverges quicker, PID has no bias in the longer term"
)
p

p <- ggplot(tracker[counter > 500 & controler != "P"], aes(x = counter, y = rmse, colour = controler))
p <- p + geom_line()
p <- p + theme_bw()
p <- p + labs(
  title = "Improved of controler with introduction of Integral into the feeback loop",
  subtitle = "Once enough history of errors is accumulated, PID controller has lower errors",
  caption = "Begining of the path is excluded to focus on the acheived improvement"
)
p