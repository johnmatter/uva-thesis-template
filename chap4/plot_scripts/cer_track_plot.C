// I used this to plot our production data track positions
// in a way that could be overlaid on the defocused distribution
// The cut used is the full production cut
// void cer_track_plot(TString filename="") {
{
    TString filename="/Volumes/ssd750/ct/pass5_official/coin_replay_production_LH2_8.0_smallcoll.root";
    // TString filename="/Volumes/ssd750/ct/pass5_official/coin_replay_production_C12_thick_8.0_smallcoll.root";
    gStyle->SetPalette(kBlackBody);
    gStyle->SetOptTitle(0);

    TFile *file = new TFile(filename.Data(),"read");
    TTree *T = (TTree*)file->Get("T");

    // create file for output
    TObjArray* tokenizedFilename = filename.Tokenize("/");
    Int_t numTokens = tokenizedFilename->GetEntries();
    TString basename = (TString) ((TObjString *)tokenizedFilename->At(numTokens-1))->String();
    basename.ReplaceAll(".root","");
    basename.ReplaceAll(".","_");
    TString fWriteFilename = Form("cherenkov_plots_%s.pdf", basename.Data());

    TCanvas *c1 = new TCanvas("c1","transparent pad",200,10,500,500);
    c1->SetFillStyle(4000); //will be transparent
    c1->SetFillColorAlpha(1, 0.);
    TPad *pad = new TPad("pad","",0,0,1,1);
    pad->SetFillStyle(4000); //will be transparent
    pad->SetFillColorAlpha(1, 0.);
    pad->Draw();
    // pad->cd();

    // LH2
    if(filename.Contains("LH2"))
        T->Draw("H.cer.xAtCer:H.cer.yAtCer>>h(320,-80,80,320,-80,80)","abs(H.gtr.beta-1.0)<0.4 & abs(P.gtr.beta-1.0)<0.2 && abs(H.gtr.dp)<10 && abs(P.gtr.dp-1)<11 && P.ngcer.npeSum<0.1 && 0.8<H.cal.etottracknorm && H.cal.etottracknorm<1.15 && H.hod.goodstarttime==1 && P.hod.goodstarttime==1 && P.kin.secondary.emiss_nuc<0.1 && abs(P.kin.secondary.pmiss)<0.1","colz");

    // C12
    if(filename.Contains("C12"))
        T->Draw("H.cer.xAtCer:H.cer.yAtCer>>h(320,-80,80,320,-80,80)","abs(H.gtr.beta-1.0)<0.4 & abs(P.gtr.beta-1.0)<0.2 && abs(H.gtr.dp)<10 && abs(P.gtr.dp-1)<11 && P.ngcer.npeSum<0.1 && 0.8<H.cal.etottracknorm && H.cal.etottracknorm<1.15 && H.hod.goodstarttime==1 && P.hod.goodstarttime==1 && P.kin.secondary.emiss_nuc<0.08 && abs(P.kin.secondary.pmiss)<0.3","colz");

    TH2* h = (TH2*) gDirectory->Get("h");

    // Maybe a good idea if you have few events
    // h->SetMaximum(100);

    // make transparent
    h->SetFillStyle(4000);

     // // make the palette axis short so we can overlay it on the efficiency plot
     // TPaletteAxis* pal = (TPaletteAxis*) h->GetListOfFunctions()->FindObject("palette");
     // pal->SetY1NDC(0.55);
     // pal->SetY2NDC(0.90);
    
     // st = (TPaveStats*) h->GetListOfFunctions()->FindObject("stats");
     // st->SetX2NDC(0.90);
     // st->SetY2NDC(0.90);

    h->Draw("colz");

    c1->SaveAs(fWriteFilename);
}
