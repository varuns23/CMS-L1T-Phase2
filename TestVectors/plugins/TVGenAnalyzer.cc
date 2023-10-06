// -*- C++ -*-
//
// Package:    L1Trigger/TVGenAnalyzer
// Class:      TVGenAnalyzer
//
/**\class TVGenAnalyzer TVGenAnalyzer.cc L1Trigger/TVGenAnalyzer/plugins/TVGenAnalyzer.cc

   Description: [one line class summary]

   Implementation:
   [Notes on implementation]
*/
//
// Original Author:  Evan Koenig
//         Created:  Mon, 29 Jun 2020 20:07:16 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"// system include files

// user include files
#include "L1Trigger/L1TCalorimeter/interface/CaloTools.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "DataFormats/L1Trigger/interface/L1EmParticle.h"
#include "DataFormats/L1Trigger/interface/L1EmParticleFwd.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "SimDataFormats/CaloHit/interface/PCaloHitContainer.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "Geometry/CaloEventSetup/interface/CaloTopologyRecord.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/EcalAlgo/interface/EcalBarrelGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "Geometry/HcalTowerAlgo/interface/HcalTrigTowerGeometry.h"
#include "Geometry/HcalTowerAlgo/interface/HcalGeometry.h"
#include <iostream>
#include "DataFormats/Phase2L1CaloTrig/interface/L1EGCrystalCluster.h"
#include "Geometry/CaloTopology/interface/CaloTopology.h"
#include "Geometry/CaloTopology/interface/HcalTopology.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TTree.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "DataFormats/Phase2L1CaloTrig/interface/L1EGCrystalCluster.h"
#include "DataFormats/Phase2L1CaloTrig/src/classes.h"

#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"

#include "DataFormats/L1Trigger/interface/L1EmParticle.h"
#include "DataFormats/L1Trigger/interface/L1EmParticleFwd.h"

#include "L1Trigger/L1CaloTrigger/interface/L1TkElectronTrackMatchAlgo.h"

#include "DataFormats/L1TrackTrigger/interface/TTTypes.h"
#include "DataFormats/L1TrackTrigger/interface/TTCluster.h"
#include "DataFormats/L1TrackTrigger/interface/TTStub.h"
#include "DataFormats/L1TrackTrigger/interface/TTTrack.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertex.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimTracker/TrackTriggerAssociation/interface/TTClusterAssociationMap.h"
#include "SimTracker/TrackTriggerAssociation/interface/TTStubAssociationMap.h"
#include "SimTracker/TrackTriggerAssociation/interface/TTTrackAssociationMap.h"
#include "Geometry/Records/interface/StackedTrackerGeometryRecord.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "DataFormats/HcalDigi/interface/HcalTriggerPrimitiveDigi.h"
#include "CalibFormats/CaloTPG/interface/CaloTPGTranscoder.h"
#include "CalibFormats/CaloTPG/interface/CaloTPGRecord.h"
#include "DataFormats/L1TrackTrigger/interface/L1TkPrimaryVertex.h"
#include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"
#include "SimCalorimetry/EcalEBTrigPrimProducers/plugins/EcalEBTrigPrimProducer.h"
#include "DataFormats/EcalDigi/interface/EcalEBTriggerPrimitiveDigi.h"
#include "DataFormats/L1Trigger/interface/BXVector.h"
#include "DataFormats/L1Trigger/interface/EGamma.h"
#include "DataFormats/L1Trigger/interface/Tau.h"
#include "DataFormats/L1Trigger/interface/L1Candidate.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/EcalAlgo/interface/EcalBarrelGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "Geometry/HcalTowerAlgo/interface/HcalTrigTowerGeometry.h"
#include "Geometry/HcalTowerAlgo/interface/HcalGeometry.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "DataFormats/HcalDetId/interface/HcalSubdetector.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"


#include "Geometry/Records/interface/IdealGeometryRecord.h"

// ECAL TPs
#include "SimCalorimetry/EcalEBTrigPrimProducers/plugins/EcalEBTrigPrimProducer.h"
#include "DataFormats/EcalDigi/interface/EcalEBTriggerPrimitiveDigi.h"

// HCAL TPs
#include "DataFormats/HcalDigi/interface/HcalTriggerPrimitiveDigi.h"
//
// class declaration
//

// Stage2
#include "DataFormats/L1Trigger/interface/BXVector.h"
#include "DataFormats/L1Trigger/interface/Jet.h"
#include "DataFormats/L1Trigger/interface/Tau.h"
#include "DataFormats/L1Trigger/interface/L1Candidate.h"

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.


using reco::TrackCollection;

int getCrystal_etaID(float eta){
   float size_cell=2*1.4841/(5*34);
   int etaID=int((eta+1.4841)/size_cell);
   return etaID;
}

int getCrystal_phiID(float phi){
   float size_cell=2*3.14159/(5*72);
   int phiID=int((phi+3.14159)/size_cell);
   return phiID;
}

class TVGenAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
  explicit TVGenAnalyzer(const edm::ParameterSet&);
  ~TVGenAnalyzer();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;

  // ----------member data ---------------------------
  void initTree();
  bool CrystalInfo();
  bool TowerInfo();

  TTree* tree;
  int nCrystal;
  vector<float> crystalEt;
  vector<int> crystalEta;
  vector<int> crystalPhi;

  int nTower;
  vector<float> towerEt;
  vector<int> towerPhi;
  vector<int> towerEta;
  vector<float> clusterEt;
  vector<int> peakPhi;
  vector<int> peakEta;
  vector<float> peakTime;
  vector<float> tower_hOe;

  float crystalCut;
  
  edm::EDGetTokenT<EcalEBTrigPrimDigiCollection> ecalTPEBToken_;
  edm::Handle<EcalEBTrigPrimDigiCollection> pcalohits;
  edm::EDGetTokenT< edm::SortedCollection<HcalTriggerPrimitiveDigi> > hcalTPToken_;
  edm::ESHandle<CaloTPGTranscoder> decoder_;
  
  edm::EDGetTokenT< L1CaloTowerCollection > l1TowerToken_;
  edm::Handle< L1CaloTowerCollection > l1CaloTowerHandle;
  
  edm::ESHandle<CaloGeometry> caloGeometry_;
  const CaloSubdetectorGeometry * ebGeometry;
  const CaloSubdetectorGeometry * hbGeometry;
  edm::ESHandle<HcalTopology> hbTopology;
  const HcalTopology * hcTopology_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TVGenAnalyzer::TVGenAnalyzer(const edm::ParameterSet& iConfig)
  :
  crystalCut(iConfig.getUntrackedParameter<double>("crystalCut", 50)),
  ecalTPEBToken_(consumes<EcalEBTrigPrimDigiCollection>(iConfig.getParameter<edm::InputTag>("ecalTPEB"))),
  hcalTPToken_(consumes< edm::SortedCollection<HcalTriggerPrimitiveDigi> >(iConfig.getParameter<edm::InputTag>("hcalTP"))),
  l1TowerToken_(consumes< L1CaloTowerCollection >(iConfig.getParameter<edm::InputTag>("l1CaloTowers")))
{
  //now do what ever initialization is needed
   edm::Service<TFileService> fs;
   tree = fs->make<TTree>("tree","TV Gen Values");
   tree->Branch("nCrystal",&nCrystal);
   tree->Branch("crystal_Et",&crystalEt);
   tree->Branch("crystal_iEta",&crystalEta);
   tree->Branch("crystal_iPhi",&crystalPhi);

   tree->Branch("nTower",&nTower);
   tree->Branch("tower_Et",&towerEt);
   tree->Branch("tower_iPhi",&towerPhi);
   tree->Branch("tower_iEta",&towerEta);
   tree->Branch("cluster_Et",&clusterEt);
   tree->Branch("peak_iPhi",&peakPhi);
   tree->Branch("peak_iEta",&peakEta);
   tree->Branch("peak_Time",&peakTime);
   tree->Branch("hOe",&tower_hOe);
}

void TVGenAnalyzer::initTree() {
  nCrystal = 0;
  crystalEt.clear();
  crystalEta.clear();
  crystalPhi.clear();

  nTower = 0;
  towerEt.clear();
  towerPhi.clear();
  towerEta.clear();
  clusterEt.clear();
  peakPhi.clear();
  peakEta.clear();
  peakTime.clear();
  tower_hOe.clear();
}


TVGenAnalyzer::~TVGenAnalyzer()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
TVGenAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  
  initTree();
  
  // Get all the ECAL hits
  iEvent.getByToken(ecalTPEBToken_,pcalohits);
  bool pass_crystal = CrystalInfo();

  iEvent.getByToken(l1TowerToken_,l1CaloTowerHandle);
  bool pass_tower = TowerInfo();
  
  if ( pass_crystal && pass_tower )
    tree->Fill();
}

bool TVGenAnalyzer::TowerInfo() {
  for (auto& hit : *l1CaloTowerHandle.product()) {
      if (!hit.isBarrel) continue; // Current algorithm only works for barrel
      float cluster_et = hit.l1eg_tower_et;
      float tower_et = hit.ecal_tower_et + cluster_et;
      int tower_iPhi = hit.tower_iPhi;
      int tower_iEta = hit.tower_iEta;
      int peak_iPhi = hit.l1eg_peak_iPhi;
      int peak_iEta = hit.l1eg_peak_iEta;
      float peak_time = 0;
      float hOe = hit.hcal_tower_et/tower_et;

      clusterEt.push_back(cluster_et);
      towerEt.push_back(tower_et);
      towerPhi.push_back(tower_iPhi);
      towerEta.push_back(tower_iEta);
      peakPhi.push_back(peak_iPhi);
      peakEta.push_back(peak_iEta);
      peakTime.push_back(peak_time);
      tower_hOe.push_back(hOe);
      nTower++;
    }
  return true;
}

bool TVGenAnalyzer::CrystalInfo() {
  float max_et = 0;
  for (auto& hit : *pcalohits.product()) {
    auto& id = hit.id();
    
    float et = hit.encodedEt()/8.; // Et is 10 bit, by keeping the ADC saturation Et at 120 GeV it means that you have to divide by 8
    int ieta = id.ieta();
    int iphi = id.iphi();

    if ( et > max_et ) max_et = et;
    
    crystalEt.push_back(et);
    crystalEta.push_back(ieta);
    crystalPhi.push_back(iphi);
    nCrystal++;
  }
  return max_et > crystalCut;
}


// ------------ method called once each job just before starting event loop  ------------
void
TVGenAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
TVGenAnalyzer::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TVGenAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TVGenAnalyzer);
