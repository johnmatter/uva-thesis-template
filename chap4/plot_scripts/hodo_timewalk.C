T->Draw("P.hod.1x.GoodNegAdcTdcDiffTime[7]:P.hod.1x.GoodNegAdcPulseAmp[7]>>h(250,0,250,100,-40,-10)","P.hod.goodstarttime","colz")
T->Draw("(P.hod.1x.GoodNegAdcPulseTime[7]-P.hod.1x.GoodNegTdcTimeCorr[7]):P.hod.1x.GoodNegAdcPulseAmp[7]>>h(250,0,250,100,0,50)","P.hod.goodstarttime==1","colz")
