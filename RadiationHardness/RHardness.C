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
  Double_t *ttbefore = tbefore->GetV2();

  TGraph *gbefore = new TGraph(n,lambda,ttbefore);  
  gbefore->SetLineColor(kBlue);
  gbefore->SetLineWidth(2);

  lambda = tafter->GetV1();
  Double_t *ttafter = tafter->GetV2();
  
  TGraph *gafter = new TGraph(n,lambda,ttafter);
  gafter->SetLineColor(kRed);
  gafter->SetLineWidth(2);

  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gbefore,"AC*");
  mg->Add(gafter,"AC*");
  mg->SetTitle("Radiation Hardness: "+crystalID+";#lambda;TT");

  TCanvas *c0 = new TCanvas("c0","c0",600,700);
  c0->Divide(1,2);
  c0->cd(1);
  mg->Draw("A");
  mg->GetYaxis()->SetRangeUser(0,100);
  mg->GetXaxis()->SetRangeUser(200,700);

  TLegend *legend = new TLegend(0.1,0.7,0.35,0.9);
  legend->AddEntry(gbefore,"Before Irradiation","l");
  legend->AddEntry(gafter,"After Irradiation","l");
  legend->Draw();
  gPad->SetGrid();

  c0->cd(2);

  const Double_t length = 200.0;
  TGraph *gdk = new TGraph();

  for (Int_t i = 0; i < n; i++){

    Double_t dk = TMath::Log(ttbefore[i]/ttafter[i])/length;
    gdk->SetPoint(i,lambda[i],dk);

  }

  gdk->SetTitle("Induced Absorption"+crystalID+";#lambda;dk");
  gdk->SetLineColor(kGreen);
  gdk->SetLineWidth(2);
  gdk->Draw("AC*");
  gPad->SetGrid();
  gdk->GetXaxis()->SetRangeUser(200,700);
  
  c0->Print("RH"+crystalID+".png");

  return 0;

}
