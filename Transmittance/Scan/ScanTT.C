/*

  Plot Transverse transmittance scan for three different wavelenghts,
  provided the CSV files, it automatically looks for the edges of the crystal
  and shifts the time data so the comparison at each point for different wavelenghts
  can be done

  Sample name:
  * IDScanWavelent (5022Scan320)

 */


Double_t Getdt( Double_t t[], Double_t T[]){
  
  Double_t dt;

  Int_t i = 0;
  while(true){
    Double_t dT = (T[i+1]-T[i]);
    if (dT > 10.0) {
      dt = t[i+1];
      break;
    }
    i++;
  }

  return dt;
  
}

int ScanTT(TString fSample = "5021") {

  TString fWl1 = "360";
  TString fWl2 = "420";
  TString fWl3 = "620";
  
  TString filename1 = fSample+"Scan"+fWl1+".Sample.Raw.Sample.Raw.csv";
  TString filename2 = fSample+"Scan"+fWl2+".Sample.Raw.Sample.Raw.csv";
  TString filename3 = fSample+"Scan"+fWl3+".Sample.Raw.Sample.Raw.csv";
  
  TTree *tr1 = new TTree("tr1","tr1");
  TTree *tr2 = new TTree("tr2","tr2");
  TTree *tr3 = new TTree("tr3","tr3");

  tr1->ReadFile(filename1,"t:T");
  tr2->ReadFile(filename2,"t:T");
  tr3->ReadFile(filename3,"t:T");
  
  Int_t ndata1 = tr1->Draw("t:T","T>20&&T<90","goff");
  Double_t *t1 = tr1->GetV1();
  Double_t *T1 = tr1->GetV2();
  tr1->Draw(Form("t-%f:T",Getdt(t1,T1)),"T>20&&T<90","goff");
  t1 = tr1->GetV1();
  
  Int_t ndata2 = tr2->Draw("t:T","T>20&&T<90","goff");
  Double_t *t2 = tr2->GetV1();
  Double_t *T2 = tr2->GetV2();
  tr2->Draw(Form("t-%f:T",Getdt(t2,T2)),"T>20&&T<90","goff");
  t2 = tr2->GetV1();
  
  Int_t ndata3 = tr3->Draw("t:T","T>20&&T<90","goff");
  Double_t *t3 = tr3->GetV1();
  Double_t *T3 = tr3->GetV2();
  tr3->Draw(Form("t-%f:T",Getdt(t3,T3)),"T>20&&T<90","goff");
  t3 = tr3->GetV1();
  
  TCanvas *c0 = new TCanvas("c0","c0",970,600);
  c0->SetTicks(1,1);
  TGraph *gr0a = new TGraph(ndata1,t1,T1);
  TGraph *gr0b = new TGraph(ndata2,t2,T2);
  TGraph *gr0c = new TGraph(ndata3,t3,T3);
  
  gr0a->SetLineColor(2);
  gr0b->SetLineColor(3);
  gr0c->SetLineColor(4);
  gr0a->SetLineWidth(2);
  gr0b->SetLineWidth(2);
  gr0c->SetLineWidth(2);
  gr0a->GetYaxis()->SetRangeUser(40,90);
  gr0a->GetXaxis()->SetRangeUser(0,200);
  gr0a->SetTitle(fSample+" Transmittance Scan;Crystal Position (Arbitrary Units);Transmittance (%)");
  gr0a->Draw("al");
  gr0b->Draw("SAME");
  gr0c->Draw("SAME");
  
  TLegend *l0 = new TLegend(0.2,0.2,0.3,0.3);
  l0->AddEntry(gr0a,fWl1+"nm","l");
  l0->AddEntry(gr0b,fWl2+"nm","l");
  l0->AddEntry(gr0c,fWl3+"nm","l");
  l0->Draw();
  
  c0->Print("ScanTT_"+fSample+".png");

  
  
  return 0;
}
