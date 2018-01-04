/*
  Keep in mind the format of the filename is:
  
  * "Sample"+before+".Sample.Raw.csv"
  * "Sample"+after+".Sample.Raw.csv"

  Execute the script by running:

  $ root -l 'RHardness.C("before","after","CrystalID")'

 */

Int_t RHardness(TString before, TString after, TString crystalID = "0000"){

  TString fbefore = "Sample"+before+".Sample.Raw.csv";
  TString fafter = "Sample"+after+".Sample.Raw.csv";

  TTree *tbefore = new TTree("tbefore","tbefore");
  TTree *tafter = new TTree("tafter","tafter");

  Int_t n = tbefore->ReadFile(fbefore,"w:t");
  tbefore->Draw("w:t","","goff");
  tafter->ReadFile(fafter,"w:t");
  tafter->Draw("w:t","","goff");

  Double_t *lambda = tbefore->GetV1();
  Double_t *tt = tbefore->GetV2();

  TGraph *gbefore = new TGraph(n,lambda,tt);  
  gbefore->SetLineColor(kBlue);
  gbefore->SetLineWidth(2);

  lambda = tafter->GetV1();
  tt = tafter->GetV2();
  
  TGraph *gafter = new TGraph(n,lambda,tt);
  gafter->SetLineColor(kRed);
  gafter->SetLineWidth(2);

  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gbefore,"AC*");
  mg->Add(gafter,"AC*");
  mg->SetTitle("Radiation Hardness: "+crystalID+";#lambda;TT");

  TCanvas *c0 = new TCanvas("c0","c0",970,600);
  mg->Draw("A");
  mg->GetYaxis()->SetRangeUser(0,100);
  mg->GetXaxis()->SetRangeUser(200,700);

  TLegend *legend = new TLegend(0.1,0.7,0.35,0.9);
  legend->AddEntry(gbefore,"Before Irradiation","l");
  legend->AddEntry(gafter,"After Irradiation","l");
  legend->Draw();
  gPad->SetGrid();

  c0->Print("RH.png");

  return 0;

}
