// By Marco Carmignotto
// version of 2016/12/13
	
int GetLY(Int_t run=0) {

	// SICCA J25
	if(run==0) run = 3149;
	//
	TString dirname = ".";
	Int_t ADCchannel = 1;
	Double_t pedRange[] = {25,35};
	Double_t sepRange[] = {70,110};
	Double_t sigRange[] = {250,600};

	// One gain - all together
	TCanvas *c00 = new TCanvas("c00","c00",970,600);
	c00->SetTicks(1,1);
	gPad->SetLogy();
	TH1F *hh0 = new TH1F("hh0",Form("%d;ADC channel;counts",run),1201,0,1200);
	TChain *T0 = new TChain("T");
	T0->Add(dirname+Form("/%d.root",run));
	T0->Draw(Form("ch%d>>hh0",ADCchannel));
	TF1 *ped00 = new TF1("ped00","gaus",pedRange[0],pedRange[1]);
	TF1 *sep00 = new TF1("sep00","gaus",sepRange[0],sepRange[1]);
	TF1 *sig00 = new TF1("sig00","gaus",sigRange[0],sigRange[1]);
	sig00->SetLineColor(2);
	sep00->SetLineColor(3);
	ped00->SetLineColor(4);
	hh0->Fit("ped00","RM+");
	hh0->Fit("sep00","RM+");
	hh0->Fit("sig00","RM+");
	Double_t PED = ped00->GetParameter(1);
	Double_t sPED = ped00->GetParError(1);
	Double_t SEP = sep00->GetParameter(1);
	Double_t sSEP = sep00->GetParError(1);
	Double_t SIG = sig00->GetParameter(1);
	Double_t sSIG = sig00->GetParError(1);
	c00->Print(dirname+Form("/%d_c00.png",run));

	// LY
	Double_t LY = (SIG-PED)/(SEP-PED)/0.511;
	Double_t sLY = LY*sqrt((sSIG/(SIG-PED))**2+(sSEP/(SEP-PED))**2+(sPED*(1.0/(SEP-PED)-1.0/(SIG-PED)))**2);

	cout << endl << endl;
	cout << "- Pedestal position:       " << PED << " +/- " << sPED << endl; 
	cout << "- Single e- peak position: " << SEP << " +/- " << sSEP << endl; 
	cout << "- Signal position:         " << SIG << " +/- " << sSIG << endl; 
	cout << "===================================================" << endl;
	cout << "=> LY: " << (SIG-PED)/(SEP-PED)/0.511 << " +/- " << sLY << " pe/MeV" << endl << endl;

	return 0;
}
