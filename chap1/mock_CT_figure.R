x   <- seq(0,22,0.1)
yCT <- tanh((x-16)/3)/5 + 0.7
yGlauber <- rep(0.5,length(x))
yFullCT <- rep(1.0,length(x))

model <- c(rep("CT Onset",     length(x)),
           rep("Glauber",      length(x)),
           rep("Complete CT",  length(x)))

df <- data.frame(Q2=rep(x,3), T=c(yCT,yGlauber,yFullCT),model=model)

p <- ggplot(df,aes(x=Q2,y=T,color=model)) +
        geom_line() +
        scale_y_continuous(limits=c(0,1.1), breaks=c(0,1)) +
        scale_x_continuous(breaks=c(12,22), labels=c(TeX("$$Q_0^2$$"),TeX("$$Q^2$$"))) +
        ylab("T") +
        xlab(TeX("$$Q^2$$")) +
        theme_bw() +
        theme(panel.grid.major = element_blank(),
              panel.grid.minor = element_blank(),
              axis.title.x=element_blank(),
              axis.ticks.x=element_blank(),
              axis.title.y=element_text(hjust=1.0, angle=0)) +
        guides(color=F) +
        annotate("text", x=22, y=0.45, label="Glauber", hjust=1) +
        annotate("text", x=22, y=1.05, label="Complete transparency", hjust=1) +
        annotate("text", x=16, y=0.75, label="CT onset", hjust=1)

ggsave("CT_toy_prediction.pdf",plot=p,height=2.5,width=4)
