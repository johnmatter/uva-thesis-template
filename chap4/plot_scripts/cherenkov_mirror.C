{
    Double_t w = 500;
    Double_t h = 500;
    auto c = new TCanvas("c", "c", w, h);
    c->cd();

    TString filename = "/Volumes/ssd750/ct/pass5/hms_replay_production_all_1327_-1.root";
    TFile *file = new TFile(filename.Data(),"read");
    TTree *T = (TTree*)file->Get("T");

    T->Draw("H.cer.xAtCer:H.cer.yAtCer>>hShould(320,-80,80,320,-80,80)","abs(H.cal.etotnorm-1)<0.2 && H.cer.xAtCer!=0 && H.cer.yAtCer!=0","colz");
    T->Draw("H.cer.xAtCer:H.cer.yAtCer>>hDid(320,-80,80,320,-80,80)","abs(H.cal.etotnorm-1)<0.2 && H.cer.xAtCer!=0 && H.cer.yAtCer!=0 && H.cer.npeSum>0","colz");

    TH2* hDid    = (TH2*)gDirectory->Get("hDid");
    TH2* hShould = (TH2*)gDirectory->Get("hShould");

    TH2F* hEff = new TH2F("hEff","hEff",320,-80,80,320,-80,80);
    hEff->Divide(hDid,hShould);

    hDid->GetXaxis()->SetTitle("y_{cer} [cm]");
    hDid->GetYaxis()->SetTitle("x_{cer} [cm]");
    hShould->GetXaxis()->SetTitle("y_{cer} [cm]");
    hShould->GetYaxis()->SetTitle("x_{cer} [cm]");
    hEff->GetXaxis()->SetTitle("y_{cer} [cm]");
    hEff->GetYaxis()->SetTitle("x_{cer} [cm]");

    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);

    // print
    hDid->Draw("colz");
    c->Print("hCer_did.pdf");
    hShould->Draw("colz");
    c->Print("hCer_should.pdf");
    hEff->Draw("colz");
    c->Print("hCer_eff.pdf");

    // and now print an hEff that we can overlay other distributions on
    TPaletteAxis* pal = (TPaletteAxis*) hEff->GetListOfFunctions()->FindObject("palette");
    pal->SetY1NDC(0.10);
    pal->SetY2NDC(0.45);
    hEff->Draw("colz");
    c->Print("hCer_eff_short_pal.pdf");
}
