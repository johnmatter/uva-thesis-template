# Masses in GeV
mElec <- 0.000510998
mPi   <- 0.13957
mKaon <- 0.493677
mProt <- 0.938272

# Index of refraction at 101.325 kPa, 0 deg C, for wavelength of 589.3 nm
nAero  <- 1.03
nC4F8O <- 1.00137 # https://userweb.jlab.org/~hcf/shmsnim/shmsNIM.pdf
nCO2   <- 1.000449
nNe    <- 1.000298
nAr    <- 1.000281
nH2    <- 1.000132
nOneAtm<-c(nCO2,nNe,nAr,nH2)
nOneAtm<-nC4F8O

# What about at operating pressure?
# n-1 is proportional to number density, and therefore pressure
nMinus1 <- nOneAtm-1
nMinus1AtPressure <- nMinus1*.45
nAtPressure <- nMinus1AtPressure+1

n <- c(nAtPressure)
cherenkovThresh <- 1-1/n

# Momentum
pStep <- 0.01
pMin  <- pStep
pMax  <- 9
p <- seq(pMin,pMax,pStep)
p <- c(0, p)

numSteps <- length(p)

# Beta
betaElec <- p/sqrt(p^2+mElec^2)
betaPi   <- p/sqrt(p^2+mPi^2)
betaKaon <- p/sqrt(p^2+mKaon^2)
betaProt <- p/sqrt(p^2+mProt^2)
beta     <- c(betaElec, betaPi, betaKaon, betaProt)

# PID
pid <- c(rep("electron", numSteps),
         rep("pion", numSteps),
         rep("kaon", numSteps),
         rep("proton", numSteps)
        )

# Data frame for ggplot
plotMe <- data.frame("pid"=pid, "p"=p, "beta"=beta)

pCer <- ggplot(plotMe,
               aes(
                   x=p,
                   y=1-beta,
                   color=pid
                   )
               ) +
        geom_line() +
        geom_hline(yintercept=cherenkovThresh) +
        scale_x_continuous(breaks = seq(0,pMax,1)) +
        scale_y_log10(breaks = trans_breaks("log10", function(x) 10^x),
                      labels = trans_format("log10", math_format(10^.x))) +
        annotation_logticks(sides = "lr") +
        guides(color=guide_legend(title="Particle Type")) +
        ylab(TeX('$1-\\beta$')) +
        xlab('p [GeV]') +
        theme_bw()

ggsave("hms_cer_threshold.pdf", pCer, width=7, height=3.5)
