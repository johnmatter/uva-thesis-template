d <- read.csv("edtm_p3of4_rate.csv")

# calculate statistical uncertainty
# Should really be corrected the way Dave Mack Describes
# because the EDTM can't block itself, so this isn't really Poisson
# https://hallcweb.jlab.org/DocDB/0010/001001/002/EDTMnonPoissonBiasCorrectionv2.pdf
d <- d %>% transform(live_time_statistical_uncertainty=live_time*sqrt(1/edtm_scaler+1/edtm_accepted))

maxRate <- 100

fitDf = d %>% filter(complete.cases(d), SHMS_3of4_rate<maxRate) %>% select(SHMS_3of4_rate, live_time) %>% rename("x"="SHMS_3of4_rate", "y"="live_time")

fit <- lm(y~x, fitDf)

x <- seq(0,maxRate,1)
fitted.data <- data.frame(x=x, y=predict(fit, list(x=x)))
fitted.data = fitted.data %>% rename("SHMS_3of4_rate"="x", "live_time"="y")

# Predict Q2=8
q2_8_rates <- c(d %>% filter(Q2==8.01))$SHMS_3of4_rate
q2_8_livetimes <- predict(fit, list(x=q2_8_rates))
d[d$Q2==8.01,]$live_time <- q2_8_livetimes

# Plot
p <- ggplot(d,
            aes(x=SHMS_3of4_rate,
                y=live_time,
               )) +
     geom_smooth(method='lm', color='black') +
     geom_pointrange(alpha=0.5, size=0.25, aes(shape=target, color=as.factor(Q2), fill=as.factor(Q2),
                ymin=live_time-live_time_statistical_uncertainty,
                ymax=live_time+live_time_statistical_uncertainty)) +
     geom_line(data=fitted.data) +
     scale_shape_manual(values=c(21,23,24)) +
     theme_bw() +
     coord_cartesian(ylim=c(0.92,1.00)) +
     scale_x_continuous(breaks=seq(0,100,10)) +
     scale_y_continuous(breaks=seq(0.9,1.0,0.01))
