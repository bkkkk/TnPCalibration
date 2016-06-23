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

A tag is defined as any *Good* muon with transverse momentum higher than 4 GeV located in the pseudorapidity range of less than 2.5. Additional requirements are made on the Impact Paramters of the ID track as follows:
 * d0 < 0.3 mm
 * z0 < 1.5 mm
 * d0 Significance < 3 (Where significance is the IP parameter scaled by it's uncertainty)
 * z0 Significance < 3

A probe is defined as any ID track with transverse momentum less than 4 located in a pseudorapidity range of less than 2.5

A tag can form a pair with a probe if the two have opposite charge, the distance between them in dR is in the range 0.2 < dR(t, p) < 3.5. In addition, the invariant mass of the tag and probe pair must be around the J/Psi mass (2 GeV < Minv < 4 GeV).

The 2011 calibration also required that the tag and probe tracks had a common origin vertex. The dataset however lacks the necessary information to carry out a revertexing of the tag and probe candidates. In lieu of this information a cut is applied on the distance in z0 of the two tracks (dz0 < 0.2) if there is more than one pair, the one with the lowest dz0 is selected.

A muon is tagged as an SMT muon if the |z0*sin(Theta)| < 2 and it's d0 IP is less than 3 mm. Finally, the normalized fit Chi2 is used to define an SMT muon with an operating point cut at 3.2

Once the pairs are formed, the muon selection efficiency is estimated. The number of probes which match a "Good Combined" muon is used as a numerator and the total number of probes in the event is the denominator. Probes which are matched to combined Muons are known as Muon Probes.

The SMT muon selection efficiency is then estimated using the Muon Probes and is defined as the number of Muon Probes that pass the above SMT selection, out of the total number of Muon Probes.


Skimming and Slimming
----
The skimming procedure is based on NTupleSvc and keeps only events which have a single tagged muon. Additionally, only those tracks which have passed the MCP selection are kept in order to reduce filesize.

