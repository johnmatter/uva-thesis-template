void cal_goodNegAdcTdcDiffTime() {
    TString filename ="/Volumes/ssd750/ct/pass5_official/coin_replay_production_C12_thick_8.0_smallcoll.root";
    TFile *file = new TFile(filename.Data(),"read");
    TTree *T = (TTree*)file->Get("T");

    std::vector<TH1*> histograms;

    // color-blind-friendly palette
    // source - https://jacksonlab.agronomy.wisc.edu/2016/05/23/15-level-colorblind-friendly-palette/
    std::vector<Int_t> myPalette;
    myPalette.push_back(TColor::GetColor("#000000")); // 1
    // myPalette.push_back(TColor::GetColor("#004949")); // 1
    myPalette.push_back(TColor::GetColor("#009292")); // 3
    myPalette.push_back(TColor::GetColor("#ff6db6")); // 4
    // myPalette.push_back(TColor::GetColor("#ffb6db")); // 5
    myPalette.push_back(TColor::GetColor("#490092")); // 6
    myPalette.push_back(TColor::GetColor("#006ddb")); // 7
    // myPalette.push_back(TColor::GetColor("#b66dff")); // 8
    // myPalette.push_back(TColor::GetColor("#6db6ff")); // 9
    // myPalette.push_back(TColor::GetColor("#b6dbff")); // 10
    myPalette.push_back(TColor::GetColor("#920000")); // 11
    // myPalette.push_back(TColor::GetColor("#924900")); // 12
    // myPalette.push_back(TColor::GetColor("#db6d00")); // 13
    myPalette.push_back(TColor::GetColor("#24ff24")); // 14
    myPalette.push_back(TColor::GetColor("#ffff6d")); // 15

    // one pad per PMT
    Double_t w = 600;
    Double_t h = 300;
    auto c = new TCanvas("c", "c", w, h);

    Int_t pmtLo=3;
    Int_t pmtHi=8;
    Int_t pmts = pmtHi+1-pmtLo;
    c->Divide(4,4);

    Int_t pad = 0;
    TString histoName, drawStr, cutStr;
    for (int pmt=pmtLo; pmt<pmtHi+1; pmt++) {
        std::cout << pmt << std::endl;

        histoName = Form("h_neg_pmt%d", pmt);

        drawStr = Form("H.cal.2ta.goodNegAdcTdcDiffTime[%d]>>%s(300,-100,-70)", pmt, histoName.Data());
        cutStr  = Form("H.cal.2ta.goodNegAdcMult[%d]==1", pmt);

        c->cd(pad++);
        T->Draw(drawStr.Data(), cutStr.Data());

        TH1* histo = (TH1*)gDirectory->Get(histoName.Data());
        histo->SetLineColor(myPalette[pmt%pmts]);
        histo->SetLineWidth(1);

        histograms.push_back(histo);
    }

    // stacked
    auto c2 = new TCanvas("c2", "c2", w, h);
    c2->cd();
    THStack *hs = new THStack("hs","Differences between fADC pulse time and TDC time for six representative PMTs in the HMS Cherenkov; [ns]; Count");
    for (const auto histo: histograms) {
        hs->Add(histo);
    }
    hs->Draw("nostack");

    gStyle->SetOptStat(0);
    c2->Print("cal_goodNegAdcTdcDiffTime.pdf");

}
