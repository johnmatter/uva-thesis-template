{
    T->Draw("H.cer.goodAdcPulseInt[0]>>h(1400,0,200)","H.cer.goodAdcPulseInt[0]>0 && abs(H.cal.etottracknorm-1)<0.15 && abs(H.gtr.beta-1.0)<0.4 && abs(H.gtr.dp)<10")
}
