void cer_plots(TString filename="") {

    if (filename.IsNull()) {
        filename ="/Volumes/ssd750/ct/pass5/hms_replay_production_all_1327_-1_hdc_uncalibrated.root";
        // filename ="/Volumes/ssd750/ct/pass5_official/coin_replay_production_C12_thick_14.3_smallcoll.root";
        // filename ="/Volumes/ssd750/ct/pass5_official/coin_replay_production_LH2_8.0_smallcoll.root";
    }

    TFile *file = new TFile(filename.Data(),"read");
    TTree *T = (TTree*)file->Get("T");

    // create file for output
    TObjArray* tokenizedFilename = filename.Tokenize("/");
    Int_t numTokens = tokenizedFilename->GetEntries();
    TString basename = (TString) ((TObjString *)tokenizedFilename->At(numTokens-1))->String();
    TString fWriteFilename = Form("cherenkov_plots_%s", basename.Data());

    std::cout << fWriteFilename << std::endl;

    TFile fWrite(fWriteFilename.Data(), "recreate");


    // TCut electronCut = "abs(H.gtr.beta-1.0)<0.2 && abs(H.gtr.dp)<8 && H.hod.goodstarttime==1 && abs(H.cal.etottracknorm-1)<0.2";
    // TCut pionCut     = "abs(H.gtr.beta-1.0)<0.2 && abs(H.gtr.dp)<8 && H.hod.goodstarttime==1 && H.cal.etottracknorm<0.8";

    TCut electronCut = "abs(H.gtr.beta-1.0)<0.2 && abs(H.gtr.dp)<8 && H.hod.goodstarttime==1 && abs(H.cal.etotnorm-1)<0.1";
    TCut pionCut     = "abs(H.gtr.beta-1.0)<0.2 && abs(H.gtr.dp)<8 && H.hod.goodstarttime==1 && H.cal.etotnorm<0.7";


    TString drawStr, cutStr, histoName, histoTitle;

    // NPE vs etottracknorm
    histoName = "h_npe_vs_etottracknorm";
    drawStr = Form("H.cer.npeSum:H.cal.etottracknorm>>%s(150,0,1.5,400,0,40)", histoName.Data());

    T->Draw(drawStr.Data(),"H.cal.etottracknorm>0 && H.cer.npeSum>0","colz");

    histoTitle = "HMS Cherenkov NPE Sum vs Track-Normalized Energy; HMS E_{dep}/p; HMS NPE";
    ((TH2*)gDirectory->Get(histoName.Data()))->SetTitle(histoTitle.Data());
    gDirectory->Get(histoName.Data())->Write();

    // NPE TH1
    histoName = "h_npesum";
    drawStr = Form("H.cer.npeSum>>%s(400,0,40)", histoName.Data());

    T->Draw(drawStr.Data(),"","colz");

    histoTitle = "HMS Cherenkov NPE Sum; NPEs; Counts";
    ((TH1*)gDirectory->Get(histoName.Data()))->SetTitle(histoTitle.Data());
    gDirectory->Get(histoName.Data())->Write();

    // NPE TH1 ELECTRON
    histoName = "h_npesum_electron";
    drawStr = Form("H.cer.npeSum>>%s(400,0,40)", histoName.Data());

    T->Draw(drawStr.Data(),"" && electronCut,"colz");

    histoTitle = "HMS Cherenkov Photoelectron Sum; HMS NPE; Counts";
    TH1* hElec = (TH1*)gDirectory->Get(histoName.Data());
    hElec->SetTitle(histoTitle.Data());
    hElec->SetFillStyle(3004);
    hElec->SetFillColor(4);

    hElec->Write();

    // NPE TH1 PION
    histoName = "h_npesum_pion";
    drawStr = Form("H.cer.npeSum>>%s(400,0,40)", histoName.Data());

    T->Draw(drawStr.Data(),"" && pionCut,"colz");

    histoTitle = "HMS Cherenkov Photoelectron Sum; HMS NPE; Counts";
    TH1* hPi = (TH1*)gDirectory->Get(histoName.Data());
    hPi->SetTitle(histoTitle.Data());
    hPi->SetFillStyle(3005);
    hPi->SetFillColor(2);
    hPi->SetLineColor(2);

    hPi->Write();

    fWrite.Close();
}
