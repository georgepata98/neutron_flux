// G4PSFlatSurfaceFlux vs. G4PSFlatSurfaceCurrent pt. mai multe distante (G4 v11.3.2)
{
    TCanvas *c1 = new TCanvas("c1", "canvas", 1000, 700);
    TLegend *leg = new TLegend(.6, .7, .9, .9);
    TMultiGraph *mg = new TMultiGraph();
    TGraph *gr1 = new TGraph();  // G4PSFlatSurfaceFlux
    TGraph *gr2 = new TGraph();  // G4PSFlatSurfaceCurrent

    // Tinta pt. scoring este subtire, grosime 2 mm, din aer
    // Distanta fata de sursa este in cm
    // Punctele contin: point number, x (distanta), y (fluxul/curentul)
    
    // G4PSFlatSurfaceFlux:
    gr1->SetPoint(0, 1, 0.00314923);
    gr1->SetPoint(1, 2, 0.00223075);
    gr1->SetPoint(2, 3, 0.00172843);
    gr1->SetPoint(3, 5, 0.00114205);
    gr1->SetPoint(4, 7.5, 0.000742066);
    gr1->SetPoint(5, 10, 0.000515183);
    gr1->SetPoint(6, 12.5, 0.00037472);
    gr1->SetPoint(7, 15, 0.000283078);
    gr1->SetPoint(8, 20, 0.000174598);
    gr1->SetPoint(9, 24, 0.000125568);

    // G4PSFlatSurfaceCurrent:
    gr2->SetPoint(0, 1, 0.00114784);
    gr2->SetPoint(1, 2, 0.0010388);
    gr2->SetPoint(2, 3, 0.000935212);
    gr2->SetPoint(3, 5, 0.000746185);
    gr2->SetPoint(4, 7.5, 0.000559012);
    gr2->SetPoint(5, 10, 0.000419642);
    gr2->SetPoint(6, 12.5, 0.000322337);
    gr2->SetPoint(7, 15, 0.000252157);
    gr2->SetPoint(8, 20, 0.000161872);
    gr2->SetPoint(9, 24, 0.000119008);

// CONCLUZIE: cu cat distanta creste cu atat unghiul solid scade deci neutronii care ajung ~perpendicular pe tinta sunt cam toti neutronii care ajung
// (curentul e mai mult cu cei perpendiculari, iar fluxul e pt. toate unghiurile sub care ajung la tinta).
// Prin urmare, la distante mari, curentul (neutronii ~perpendiculari pe tinta) si fluxul (neutronii din toate directiile) se egaleaza.
    
    c1->SetGrid();
    gr1->SetMarkerStyle(21);
    gr1->SetLineWidth(2);
    gr1->SetLineColor(kRed);
    gr2->SetMarkerStyle(22);
    gr2->SetLineWidth(2);
    gr2->SetLineColor(kBlue);
    mg->Add(gr1);
    mg->Add(gr2);
    mg->SetTitle("Tinta subtire, 2 mm grosime, din aer");
    mg->GetXaxis()->SetTitle("Distanta [cm]");
    mg->GetYaxis()->SetTitle("Flux si curent [n/cm^2/NPS]");
    leg->AddEntry(gr1, "G4PSFlatSurfaceFlux", "l");
    leg->AddEntry(gr2, "G4PSFlatSurfaceCurrent", "l");
    mg->Draw("APL");
    leg->Draw("SAME");
    c1->Update();
}
