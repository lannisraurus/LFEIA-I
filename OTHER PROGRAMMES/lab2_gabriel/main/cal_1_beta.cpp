#include "data_colector.cpp"

int main(){
    
    data_colector beta("cal_1_beta.txt");
    vector<double> x = beta.get_a_certain_col(1);
    vector<double> ex;
    vector<double> y = beta.get_a_certain_col(2);
    vector<double> ey;
    Int_t points_numb = x.size();

    for (int i = 0; i < x.size(); i++){

        ex.push_back(0);
        ey.push_back(0);
    }

    double* x_ptr = &x[0];
    double* ex_ptr = &ex[0];
    double* y_ptr = &y[0];
    double* ey_ptr = &ey[0];

    TApplication* A = new TApplication("A", 0, 0);
    TCanvas* C = new TCanvas("C", "Canvas", 16*70, 9*70);
    TGraphErrors* g = new TGraphErrors(points_numb, x_ptr, y_ptr, ex_ptr, ey_ptr);
    TF1* f = new TF1("f", "[0] * x + [1]");
    TPaveText* pt = new TPaveText(50, 0.7, 150, 1.1, "user");

    pt->SetTextSize(0.03);
    pt->SetFillColor(0);
    pt->SetTextAlign(12);
    pt->SetTextFont(42);
    g->SetMarkerStyle(4);
    g->SetMarkerColor(kBlack);
    g->GetXaxis()->SetTitle("Channels");
    g->GetXaxis()->SetLimits(0, 275);
    g->GetXaxis()->SetNdivisions(-525);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetTitle("Energy (pulser units)");
    g->GetYaxis()->SetRangeUser(0, 1.3);
    g->GetYaxis()->SetNdivisions(-13);
    g->GetYaxis()->SetLabelSize(0.028);
    f->SetLineColor(kCyan);

    g->Draw("AP");
    g->Fit("f");
    pt->AddText(Form("y = ax + b"));
    pt->AddText(Form("a = %.10f %c %.10f", f->GetParameter(0), 0xB1, f->GetParError(0)));
    pt->AddText(Form("b = %.10f %c %.10f", f->GetParameter(1), 0xB1, f->GetParError(1)));
    pt->AddText(Form("#chi^{2} = %.10f", f->GetChisquare()));
    pt->Draw();

    C->Update();
    C->SaveAs("cal_1_beta.png");
    gSystem->ProcessEvents();
    C->WaitPrimitive();

    delete C;
    delete g;
    delete f;
    delete pt;
    delete A;

    return 0;
}