TnPCalibration
==============

This collection of RootCore-based packages perform a full combined muon reconstruction efficiency measurement and soft muon tagger efficiency measurement. These measurements arebased on tag and probe of J/Psi going to two muons. However it can be adapted to any process given appropriate selectors.
The number of tag and probe pairs are extracted from a fit to the invariant mass distribution of the selected pairs. Currently a few fitting approaches are being studied. The yields are extracted and the efficiencies and SF are determined in bins of p_{T} and #eta.

Methodology
-------
The efficiency measurement procedure can be divided into a few distinct stages:
 * Skimming and Slimming
 * Tag and Probe pair selection
 * Construction and fitting of Invariant Mass distributions
 * Extraction of yields, calculation of efficiencies and SF

Tag and Probe Pair Selection
------
Tag Selection:
 * Good Muon
 * pT > 4 GeV, |eta| < 2.5
 * d0 < 0.3 mm
 * z0 < 1.5 mm
 * d0 Significance < 3 (Where Significance = |d0/sigmad0|)
 * z0 Significance < 3

Probe Selection:
 * pT > 4 GeV
 * |eta| < 2.5

Pairing Selection:
 * Tag charge is opposite of the Probe charge
 * 0.2 < dR(t, p) < 3.5 
 * 2 GeV < Minv < 4 GeV
 * Select pair with lowest dz0 in event
 * dz0 < 0.2

MuonProbe Selection:
 * Good Combined Muon

SMT Selection:
 * |z0sin(Theta)| < 2
 * d0 < 3 mm
 * MatchChi^2 / nDoF < 3.2

Skimming and Slimming
----
The skimming procedure is based on NTupleSvc and keeps only events which have a single tagged muon.
Additionally only those tracks which have passed the MCP selection are kept in order to reduce filesize.

