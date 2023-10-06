void draw_event() {
  _file0->cd("analyzer");
}

void plot_crystals(TTree* tree,int philo,int phihi,bool posEta) {
  TString cut = string("(crystal_iEta") + (posEta ? ">" : "<") + "0&&" + to_string(philo) + "<=crystal_iPhi&&crystal_iPhi<=" + to_string(phihi) + ")";
  TString binning = "(" + to_string(phihi-philo+1) + ","+to_string(philo)+","+to_string(phihi+1)+",85,"+(posEta ? "1,86" : "-86,-1") + ")";
  tree->Draw("crystal_iEta:crystal_iPhi>>"+binning,"crystal_Et*"+cut,"COLZ",1);
  gPad->SetGrid();
}

void plot_towers(TTree* tree,int philo,int phihi) {
  TString cut = "(" + to_string(philo) + "<=tower_iPhi&&tower_iPhi<=" + to_string(phihi) + "&&tower_Et>1)";
  TString binning = "(" + to_string(phihi-philo+1) + ","+to_string(philo)+","+to_string(phihi+1)+",34,-17,17)";
  tree->Draw("tower_iEta:tower_iPhi>>"+binning,"tower_Et*"+cut,"COLZ TEXT",1);
  gPad->SetGrid();
}
