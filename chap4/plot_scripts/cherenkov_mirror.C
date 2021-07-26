// /Volumes/ssd750/ct/pass5/hms_replay_production_all_1327_-1.root
T->Draw("H.cer.xAtCer:H.cer.yAtCer>>h(160,-80,80,160,-80,80)","abs(H.cal.etotnorm-1)<0.2 && H.cer.xAtCer!=0 && H.cer.yAtCer!=0","colz")
T->Draw("H.cer.xAtCer:H.cer.yAtCer>>h(160,-80,80,160,-80,80)","abs(H.cal.etotnorm-1)<0.2 && H.cer.xAtCer!=0 && H.cer.yAtCer!=0 && H.cer.npeSum>0","colz")
