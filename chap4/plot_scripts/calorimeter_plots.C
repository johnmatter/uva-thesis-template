void calorimeter_plots(TString filename="") {

    if (filename.IsNull()) {
        // filename ="/Volumes/ssd750/ct/pass5/hms_replay_production_all_1327_-1_hdc_uncalibrated.root";
        filename ="/Volumes/ssd750/ct/pass5_official/coin_replay_production_C12_thick_14.3_smallcoll.root";
    }

    TFile *file = new TFile(filename.Data(),"read");
    TTree *T = (TTree*)file->Get("T");

    // create file for output
    TObjArray* tokenizedFilename = filename.Tokenize("/");
    Int_t numTokens = tokenizedFilename->GetEntries();
    TString basename = (TString) ((TObjString *)tokenizedFilename->At(numTokens-1))->String();
    TString fWriteFilename = Form("calorimeter_plots_%s", basename.Data());

    std::cout << fWriteFilename << std::endl;

    TFile fWrite(fWriteFilename.Data(), "recreate");


    TCut electronCut = "abs(H.gtr.beta-1.0)<0.2 && abs(H.gtr.dp)<8 && H.hod.goodstarttime==1 && H.cer.npeSum>0";
    TCut pionCut     = "abs(H.gtr.beta-1.0)<0.2 && abs(H.gtr.dp)<8 && H.hod.goodstarttime==1 && H.cer.npeSum==0";

    TString drawStr, cutStr, histoName, histoTitle;

    // delta vs etottracknorm
    histoName = "h_delta_vs_etottracknorm";
    drawStr = Form("H.gtr.dp:H.cal.etottracknorm>>%s(300,0,1.5,400,-20,20)", histoName.Data());

    T->Draw(drawStr.Data(),"H.cal.etottracknorm>0","colz");

    histoTitle = "HMS Delta vs Track-Normalized Energy; HMS E_{dep}/p; HMS Delta";
    ((TH2*)gDirectory->Get(histoName.Data()))->SetTitle(histoTitle.Data());
    gDirectory->Get(histoName.Data())->Write();

    // normalized shower vs preshower
    histoName = "h_shower_vs_preshower";
    drawStr = Form("(H.cal.etottracknorm-H.cal.eprtracknorm):H.cal.eprtracknorm>>%s(300,0,1.5,300,0,1.5)", histoName.Data());

    T->Draw(drawStr.Data(),"H.cal.etottracknorm>0","colz");

    histoTitle = "HMS Track-Normalized Shower Energy vs Preshower Energy; HMS E_{pr}/p; HMS E_{sh}/p";
    ((TH2*)gDirectory->Get(histoName.Data()))->SetTitle(histoTitle.Data());
    gDirectory->Get(histoName.Data())->Write();

    // etottracknorm TH1
    histoName = "h_etotracknorm";
    drawStr = Form("H.cal.etottracknorm>>%s(300,0,1.5)", histoName.Data());

    T->Draw(drawStr.Data(),"H.cal.etottracknorm>0","colz");

    histoTitle = "HMS Track-Normalized Energy; HMS E_{dep}/p; Counts";
    ((TH1*)gDirectory->Get(histoName.Data()))->SetTitle(histoTitle.Data());
    gDirectory->Get(histoName.Data())->Write();

    // etottracknorm TH1 ELECTRON
    histoName = "h_etotracknorm_electron";
    drawStr = Form("H.cal.etottracknorm>>%s(300,0,1.5)", histoName.Data());

    T->Draw(drawStr.Data(),"H.cal.etottracknorm>0" && electronCut,"colz");

    histoTitle = "HMS Track-Normalized Energy; HMS E_{dep}/p; Counts";
    ((TH1*)gDirectory->Get(histoName.Data()))->SetTitle(histoTitle.Data());
    gDirectory->Get(histoName.Data())->Write();

    // etottracknorm TH1 PION
    histoName = "h_etotracknorm_pion";
    drawStr = Form("H.cal.etottracknorm>>%s(300,0,1.5)", histoName.Data());

    T->Draw(drawStr.Data(),"H.cal.etottracknorm>0" && pionCut,"colz");

    histoTitle = "HMS Track-Normalized Energy; HMS E_{dep}/p; Counts";
    ((TH1*)gDirectory->Get(histoName.Data()))->SetTitle(histoTitle.Data());
    gDirectory->Get(histoName.Data())->Write();


    fWrite.Close();
}
