# APx Gen2 Phase2 GCT Sum

- Takes input from 3-barrel GCT and 6 endcap GCT (3each for positive and negative side)

Checkout existing GCT code and APx Core Firmware connector from:
```
git clone git@github.com:varuns23/CMSPhase2GCTSum.git
cd CMSPhase2GCTSum
source setEnv.sh #(uwlogin/beck independent)
```
## Algorithms:
```
export algo = METAlgo
```

## Simulation and Synthesis:

For HLS simulation
```bash
cd $AP_FW_BASE_DIR/CMSPhase2GCTSum/$algo/hls/vivado_hls/
vivado_hls -f run_hls.tcl csim=1 tv_in=$PWD/data/test_in.txt tv_out=$PWD/data/test_out.txt tv_ref=$PWD/data/test_out_ref.txt
```

Synthesis and exporting RTL
```bash
cd $AP_FW_BASE_DIR/CMSPhase2GCTSum/$algo/hls/vivado_hls/
vivado_hls -f run_hls.tcl synth=1 export=1

```
Simulation, Synthesis, Verification and RTL generation in Vivado HLS:
```bash
cd $AP_FW_BASE_DIR/CMSPhase2GCTSum/$algo/hls/vivado_hls/
vivado_hls -f run_hls.tcl csim=1 synth=1 cosim=1 export=1 tv_in=$PWD/data/test_in.txt tv_out=$PWD/data/test_out.txt tv_ref=$PWD/data/test_out_ref.txt
```

## Making bit file for APd:
```
cd $AP_FW_BASE_DIR
git clone --recursive ssh://git@gitlab.cern.ch:7999/asvetek/phase2-gct.git
cd $AP_FW_BASE_DIR/phase2-gct/
mkdir build
make
```

## GUI access
 
Follow instructions at twiki - adapt suitably for usage on beck.hep.wisc.edu:
https://twiki.cern.ch/twiki/bin/viewauth/CMS/L1TriggerPhase2HLSProjects
