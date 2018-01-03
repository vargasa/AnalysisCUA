/***********************
  File "LYHisto.csv" contains colums CrystalID|LY
  **********************/

Int_t LYHisto(){
  
  TString filename = "LYHisto.csv";
    
  TTree *tr1 = new TTree("tr1","tr1");
  Int_t ndata = tr1->ReadFile(filename,"id:ly");

  tr1->Draw("id:ly","","goff");
  Double_t *ly = tr1->GetV2();

  TCanvas *c0 = new TCanvas("c0","c0",970,600);
  c0->SetTicks(1,1);
  TH1F *hist = new TH1F("hist","LY",80,0,40);

  for(Int_t i = 0; i < ndata; i++){
    hist->Fill(ly[i]);
  }

  gPad->SetGrid();
  hist->Draw("HIST");
  hist->SetFillColor(kBlue);
  hist->SetTitle("LY;LY;#Crystals");
  
  c0->Print("LY.png");

  return 0;

}
