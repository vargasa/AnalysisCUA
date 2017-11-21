/*
  Given a Crystal ID (Sample) and CSV data, it plots the 
  Transmmitance as a function of wavelenght.
 */

int plotTT(TString Sample = "5022"){
  
  TString filenameTT = Sample+"Center10cm.Sample.Raw.csv";
    
  TTree *tr1 = new TTree("tr1","tr1");
  Int_t ndata = tr1->ReadFile(filenameTT,"w:t");

  tr1->Draw("w:t","","goff");
  Double_t *w1 = tr1->GetV1();
  Double_t *t1 = tr1->GetV2();

  TCanvas *c0 = new TCanvas("c0","c0",970,600);
  c0->SetTicks(1,1);
  TGraph *gr1 = new TGraph(ndata,w1,t1);
  gr1->SetLineColor(2);
  gr1->SetLineWidth(2);
  gr1->GetYaxis()->SetRangeUser(0,100);
  gr1->GetXaxis()->SetRangeUser(200,700);
  gr1->SetTitle(Sample+";nm;T (%)");
  gr1->Draw("al*");
  c0->Print("TT "+Sample+".png");

  // TLegend *legend = new TLegend(0.1,0.7,0.35,0.9);
  // legend->AddEntry(gr1,"Before Irradiation","l");
  // legend->AddEntry(gr2,"After Irradiation","l");
  // legend->Draw();
  
  //c0->Print(Sample+".png");

  return 0;

}
