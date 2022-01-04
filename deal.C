void deal() {
	auto t = (TTree*)TFile::Open("data_R0004_W1000.root")->Get("t");

	UShort_t adc[3][16];
	Bool_t outofr[3][16];

	TH1F *hbgo[8];
	for (int i = 0; i < 8; ++i)
	{
		hbgo[i] = new TH1F(TString::Format("h%d", i), TString::Format("h%d", i), 500, 100, 5100);
	}

	t->SetBranchAddress("adc", adc);
	t->SetBranchAddress("outofr", outofr);

	long nn = t->GetEntries();

	for (long i = 0; i < nn / 100; ++i)
	{
		t->GetEntry(i);
		for (int j = 0; j < 8; ++j)
		{
			hbgo[j]->Fill(adc[1][j + 8]);
		}
	}

	TCanvas *c = new TCanvas();

	c->Divide(2, 4);

	for (int i = 0; i < 8; ++i)
	{
		gPad->SetLogy();
		c->cd(i + 1);
		hbgo[i]->Draw();
	}

}