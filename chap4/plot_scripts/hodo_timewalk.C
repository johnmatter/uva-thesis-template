void hodo_timewalk() {
    TString filename ="/Volumes/ssd750/ct/pass5/hms_replay_production_all_1327_-1_hdc_uncalibrated.root";
    // TString filename ="/Volumes/ssd750/ct/pass5_official/coin_replay_production_C12_thick_8.0_smallcoll.root";
    TFile *file = new TFile(filename.Data(),"read");
    TTree *T = (TTree*)file->Get("T");

    // keys are plane, paddle, and pmt side
    std::map<TString, std::map<Int_t, std::map<TString, TH2*>>> walked_histograms;
    std::map<TString, std::map<Int_t, std::map<TString, TH2*>>> unwalked_histograms;

    std::vector<TString> planes = {"1x"};//, "1y", "2x", "2y"};

    TString spectrometer = "H";

    std::map<TString, Int_t> num_paddles;

    // HMS
    num_paddles["1x"] = 16;
    num_paddles["1y"] = 10;
    num_paddles["2x"] = 16;
    num_paddles["2y"] = 10;

    // // SHMS
    // num_paddles["1x"] = 13;
    // num_paddles["1y"] = 13;
    // num_paddles["2x"] = 14;
    // num_paddles["2y"] = 21;

    TString drawStr, cutStr, histoName, histoTitle;
    TString AdcTdcDiffTime;
    TString PulseAmp;
    TString PulseTime;
    TString TdcTimeCorr;
    TString basename;

    for (auto plane: planes) {
        basename = Form("%s.hod.%s", spectrometer.Data(), plane.Data());

        for (int paddle = 0; paddle < num_paddles[plane]; paddle++) {
            std::cout << "Histogramming " << basename << " paddle #" << paddle << std::endl;

            for (TString pmt: {"Pos", "Neg"}) {


                AdcTdcDiffTime = Form("%s.Good%sAdcTdcDiffTime", basename.Data(), pmt.Data());
                PulseAmp       = Form("%s.Good%sAdcPulseAmp",    basename.Data(), pmt.Data());
                PulseTime      = Form("%s.Good%sAdcPulseTime",   basename.Data(), pmt.Data());
                TdcTimeCorr    = Form("%s.Good%sTdcTimeCorr",    basename.Data(), pmt.Data());

                histoName = Form("unwalked_plane%s_paddle%d_pmt%s", plane.Data(), paddle, pmt.Data());
                histoTitle = Form("TDC-ADC Time versus Pulse Amplitude (Plane %s, %s Side, Paddle %d); [mV]; [ns]", plane.Data(), pmt.Data(), paddle);
                drawStr = Form("%s[%d]:%s[%d]>>%s(500,0,500,100,-65,-45)", AdcTdcDiffTime.Data(), paddle, PulseAmp.Data(), paddle, histoName.Data());
                T->Draw(drawStr.Data(),"H.hod.goodstarttime==1","colz");
                unwalked_histograms[plane][paddle][pmt] = (TH2*)gDirectory->Get(histoName.Data());
                unwalked_histograms[plane][paddle][pmt]->SetTitle(histoTitle.Data());

                // // I think this one is wrong. I forget what branches I'm
                // // supposed to be looking at here.
                // histoName = Form("walked_plane%s_paddle%d_pmt%s", plane.Data(), paddle, pmt.Data());
                // drawStr = Form("(%s[%d]-%s[%d]):%s[%d]>>%s(350,0,350,90,-80,-50)", TdcTimeCorr.Data(), paddle, PulseTime.Data(), paddle, PulseAmp.Data(), paddle, histoName.Data());
                // T->Draw(drawStr.Data(),"H.hod.goodstarttime==1","colz");
                // walked_histograms[plane][paddle][pmt] = (TH2*)gDirectory->Get(histoName.Data());

            }
        }
    }

    TFile fWrite("hodo_timewalk_histograms.root", "recreate");
    for (auto plane: planes) {
        for (int paddle = 0; paddle < num_paddles[plane]; paddle++) {
            for (TString pmt: {"Pos", "Neg"}) {
                unwalked_histograms[plane][paddle][pmt]->Write();
                // walked_histograms[plane][paddle][pmt]->Write();
            }
        }
    }
    fWrite.Close();
}
