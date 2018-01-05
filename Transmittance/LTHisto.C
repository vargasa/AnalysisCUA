/***********************
  File "LTHisto.csv" contains colums CrystalID|LT(420nm)|LT(360nm)|LT(620nm)
  **********************/

Int_t DrawHisto(Int_t n, Double_t *y, Int_t lambda,
		Int_t bins = 200, Float_t xmin = 0.,Float_t xmax = 100.){

  TH1F *h = new TH1F("h","h",bins,xmin,xmax);

  TF1 *fit = new TF1("fit","gaus",xmin,xmax);
  fit->SetLineColor(3);
  
  for(Int_t i = 0; i < n; i++){
    h->Fill(y[i]);
  }

  TCanvas *c0 = new TCanvas("c0","c0",970,600);
  gStyle->SetOptFit();
  gPad->SetGrid();

  h->Fit("fit","M");
  h->SetFillColor(kBlue);
  h->SetTitle(Form("LT;LT %dnm;#Crystals",lambda));
  h->Draw();

  c0->Print(Form("LTHisto%dnm.png",lambda));
  
  return 0;

}

Int_t LTHisto(){
  
  TString filename = "LTHisto.csv";
    
  TTree *tr1 = new TTree("tr1","tr1");
  Int_t ndata = tr1->ReadFile(filename,"id:lt420:lt360:lt620");

  // Tweak this values to adjust the range
  tr1->Draw("id:lt420:lt360:lt620","","goff");
  Double_t *y = tr1->GetV2();

  DrawHisto(ndata,y,420,60,50,80);
  y = tr1->GetV3();
  DrawHisto(ndata,y,360,80,10,50);
  y = tr1->GetV4();
  DrawHisto(ndata,y,620,40,60,80);
  
  return 0;
}
