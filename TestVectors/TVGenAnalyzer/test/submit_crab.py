from collections import OrderedDict
from CRABClient.UserUtilities import config
import os
from datetime import datetime

# https://twiki.cern.ch/twiki/bin/view/CMSPublic/CRAB3ConfigurationFile

config = config()

config.General.transferOutputs = True
config.General.transferLogs    = True

config.JobType.pluginName      = 'Analysis'
config.JobType.maxMemoryMB     = 3500
config.JobType.priority        = 2
config.Data.splitting      = 'FileBased'
config.Data.unitsPerJob        = 3 # events / job when using EventAwareLumiBased
config.Data.publication        = False

#config.Data.totalUnits      = 45 # for tests


config.Site.storageSite        = 'T2_US_Wisconsin'
config.Site.ignoreGlobalBlacklist = True # Needed to add this to process the VBF H125 sample & HLTPhysics & DYJets
#config.Site.whitelist          = ['T2_US_Wisconsin',] # Needed to remove this to process the VBF H125 sample & HLTPhysics & DYJets

config.User.voGroup            = 'uscms'

dataMap = OrderedDict()
dataMap['minBias-PU200'] = {'das' : '/NeutrinoGun_E_10GeV/PhaseIIMTDTDRAutumn18DR-PU200_103X_upgrade2023_realistic_v2-v1/FEVT'}
dataMap['QCD-PU200'] = {'das' : '/QCD_Pt-15To7000_TuneCP5_Flat_14TeV-pythia8/PhaseIIMTDTDRAutumn18DR-PU200_103X_upgrade2023_realistic_v2-v1/FEVT'}
dataMap['ggHTT-PU200'] = {'das' : '/GluGluHToTauTau_M125_14TeV_powheg_pythia8/PhaseIIMTDTDRAutumn18DR-PU200_103X_upgrade2023_realistic_v2-v1/FEVT'}
dataMap['ggHGG-PU200'] = {'das' : '/GluGluHToGG_M125_14TeV_powheg_pythia8/PhaseIIMTDTDRAutumn18DR-PU200_103X_upgrade2023_realistic_v2-v1/FEVT'}
dataMap['ggHBB-PU200'] = {'das' : '/GluGluHToBB_M125_14TeV_powheg_pythia8/PhaseIIMTDTDRAutumn18DR-PU200_103X_upgrade2023_realistic_v2-v1/FEVT'}
dataMap['VBFHTT-PU200'] = {'das' : '/VBFHToTauTau_M125_14TeV_powheg_pythia8/PhaseIIMTDTDRAutumn18DR-PU200_103X_upgrade2023_realistic_v2-v1/FEVT'}
dataMap['VBFHGG-PU200'] = {'das' : '/VBFHToGG_M-125_14TeV_powheg_pythia8/PhaseIIMTDTDRAutumn18DR-PU200_103X_upgrade2023_realistic_v2-v1/FEVT'}
dataMap['VBFHBB-PU200'] = {'das' : '/VBFHToBB_M-125_14TeV_powheg_pythia8_weightfix/PhaseIIMTDTDRAutumn18DR-PU200_103X_upgrade2023_realistic_v2-v1/FEVT'}

# dasgoclient --query="dataset dataset=/*/*PhaseIIMTDTDRAutumn18DR*/FEVT"


if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException as hte:
            print "Failed submitting task: %s" % (hte.headers)
        except ClientException as cle:
            print "Failed submitting task: %s" % (cle)

    datasets = OrderedDict()
    
    base = os.getenv("CMSSW_BASE")
    print "Base: ",base
    for k in dataMap.keys() :

        # Normal eff and rate analysis
        config.General.requestName = '{date}_RCT_TV_{k}'.format(k=k,date=datetime.now().strftime("%Y%m%d"))
        config.JobType.psetName        = 'run_tvgen.py'
        config.Data.inputDataset = dataMap[ k ][ 'das' ]
        if 'PU200' in k or 'PU140' in k :
            #config.Data.unitsPerJob        = 3 # events / job when using EventAwareLumiBased
            config.Data.unitsPerJob        = 5 # files / job, takes ~ 60min based on 10_5_X MTD samples, 90m for QCD PU200
            config.Data.unitsPerJob        = 10
            #config.Data.totalUnits      = 100 # for tests
        else :
            config.Data.unitsPerJob        = 3 # events / job when using EventAwareLumiBased
            #config.Data.totalUnits      = 30 # for tests
            #config.Data.unitsPerJob        = 2 # events / job when using EventAwareLumiBased
            #config.Data.totalUnits      = 10 # for tests

        config.Data.outputDatasetTag   = config.General.requestName
        config.Data.outLFNDirBase = '/store/user/ekoenig/Trigger/RCT_TVGen/'

        print 'submitting config:'
        print config
        submit(config)
