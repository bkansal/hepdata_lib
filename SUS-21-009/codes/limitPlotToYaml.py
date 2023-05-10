from __future__ import print_function
import sys
import ROOT
from ROOT import TFile, TH3F
import hepdata_lib
from hepdata_lib import Submission, Table, RootFileReader, Variable
from hepdata_lib import Uncertainty
import numpy as np


submission = Submission()
submission.title = "Search for new physics in multijet events with at least one photon and large missing transverse momentum in proton-proton collisions at 13 TeV"
submission.read_abstract("abstract.txt")
submission.add_link("Webpage with all figures and tables", "http://cms-results.web.cern.ch/cms-results/public-results/preliminary-results/SUS-21-009/index.html")



table = Table("Figure 8 Predicted background events")
table.description ="SM background predictions, data observations and signal yields in the signal region."
table.location = "Data from Figure 8, located on page 15."
table.keywords["cmenergies"] = ["13000"]
table.keywords["observables"] = ["NEvents/bin"]
table.keywords["phrases"] = ["SUSY","GMSB","Supersymmetry"]
table.keywords["reactions"] = ["P P"]
table.add_image("../rootfiles/AllSBins_v6_CD_EW_50bin_unblind_prefit.pdf")
data = np.loadtxt("pred.txt", skiprows=0)
d = Variable("Bin index", is_independent=True, is_binned=False, units="")
LL= Variable("Lost lepton", is_independent=False, is_binned=False, units="")
FR= Variable("e fakes $\\gamma$", is_independent=False, is_binned=False, units="")
Zin= Variable("Z invisible", is_independent=False, is_binned=False, units="")
QCD= Variable("Multijet + $\\gamma$", is_independent=False, is_binned=False, units="")
hd= Variable("Number of data events", is_independent=False, is_binned=False, units="")
s1= Variable("T5bbbbZg ($M_{\\tilde{g}}=2200$ , $M_{\\tilde{\\chi}_{1}^{0}}=200$)", is_independent=False, is_binned=False, units="")
s2= Variable("T5bbbbZg ($M_{\\tilde{g}}=2200$ , $M_{\\tilde{\\chi}_{1}^{0}}=2100$)", is_independent=False, is_binned=False, units="")
s3= Variable("TChiWG ($M_{NLSP}=1000$)", is_independent=False, is_binned=False, units="")
d.values = data[:,0]
LL.values = data[:,1]
FR.values = data[:,3]
Zin.values = data[:,5]
QCD.values = data[:,7]
s1.values = data[:,12]
s2.values = data[:,14]
s3.values = data[:,16]
hd.values= data[:,11]


unc_LL = Uncertainty("unc.", is_symmetric=True)
unc_FR = Uncertainty("unc.", is_symmetric=True)
unc_Zin = Uncertainty("unc.", is_symmetric=True)
unc_QCD = Uncertainty("unc.", is_symmetric=True)
unc_s1 = Uncertainty("unc.", is_symmetric=True)
unc_s2 = Uncertainty("unc.", is_symmetric=True)
unc_s3 = Uncertainty("unc.", is_symmetric=True)

#unc_LL = Uncertainty("lost lepton uncertainty", is_symmetric=True)
#unc_FR = Uncertainty(" e fakes $\\gamma$ uncertainty", is_symmetric=True)
#unc_Zin = Uncertainty("Z invisible uncertainty", is_symmetric=True)
#unc_QCD = Uncertainty("Multijet + $\\gamma$ uncertainty", is_symmetric=True)
#unc_s1 = Uncertainty("T5bbbbZg (2200,200) uncertainty", is_symmetric=True)
#unc_s2 = Uncertainty("T5bbbbZg (2200,2100) uncertainty", is_symmetric=True)
#unc_s3 = Uncertainty("TChiWG (1000) uncertainty", is_symmetric=True)

unc_LL.values = data[:,2]
unc_FR.values = data[:,4]
unc_Zin.values = data[:,6]
unc_QCD.values = data[:,8]
unc_s1.values = data[:,13]
unc_s2.values = data[:,15]
unc_s3.values = data[:,17]


table.add_variable(d)
table.add_variable(LL)
LL.add_uncertainty(unc_LL)
table.add_variable(FR)
FR.add_uncertainty(unc_FR)
table.add_variable(Zin)
Zin.add_uncertainty(unc_Zin)
table.add_variable(QCD)
QCD.add_uncertainty(unc_QCD)
table.add_variable(hd)
table.add_variable(s1)
s1.add_uncertainty(unc_s1)
table.add_variable(s2)
s2.add_uncertainty(unc_s2)
table.add_variable(s3)
s3.add_uncertainty(unc_s3)

submission.add_table(table)



strong = ["T5bbbbZg","T5qqqqHg","T5ttttZg","T6ttZg"]
ewk = ["TChiNGnn","TChiNG","TChiWG"]
for sample in strong:
    print(sample)
    arg2=["Excl_obslimit_"+sample,"Excl_explimit_"+sample]
    arg3=["observed","expected"]
    print(arg2,arg3)
    
    for a in range(2):
        if "T5bbbbZg" in sample:
            table = Table("Figure 9 (top left) "+arg3[a])
            table.description ="Gluino - neutralino mass points lying on the "+arg3[a]+" exclusion contour of "+sample+" model."
            table.location = "Data from Figure 9 (top left), located on page 16."
            fname="$pp \\rightarrow \\tilde{g}\\tilde{g}, \\ \\tilde{g} \\rightarrow \\tilde{\\chi}_{1}^{0} b \\bar{b}, \\ \\tilde{\\chi}_{1}^{0} \\rightarrow Z/\\gamma \\tilde{G}$"

        elif "T5qqqqHg" in sample:
            table = Table("Figure 9 (top right) "+arg3[a])
            table.description ="Gluino - neutralino mass points lying on the "+arg3[a]+" exclusion contour of "+sample+" model."
            table.location = "Data from Figure 9 (top right), located on page 16."
            fname = "$pp \\rightarrow \\tilde{g}\\tilde{g}, \\ \\tilde{g} \\rightarrow \\tilde{\\chi}_{1}^{0} q \\bar{q}, \\ \\tilde{\\chi}_{1}^{0} \\rightarrow H/\\gamma \\tilde{G}$"

        elif "T5ttttZg" in sample:
            table = Table("Figure 9 (bottom left) "+arg3[a])
            table.description ="Gluino - neutralino mass points lying on the "+arg3[a]+" exclusion contour of "+sample+" model."
            table.location = "Data from Figure 9 (bottom left), located on page 16."
            fname = "$pp \\rightarrow \\tilde{g}\\tilde{g}, \\ \\tilde{g} \\rightarrow \\tilde{\\chi}_{1}^{0} t \\bar{t}, \\ \\tilde{\\chi}_{1}^{0} \\rightarrow Z/\\gamma \\tilde{G}$"

        elif "T6ttZg" in sample:
            table = Table("Figure 9 (bottom right) "+arg3[a])
            table.description ="Stop - neutralino mass points lying on the "+arg3[a]+" exclusion contour of "+sample+" model."
            table.location = "Data from Figure 9 (bottom right), located on page 16."
            fname = "$pp \\rightarrow \\tilde{t}\\tilde{t}, \\ \\tilde{t} \\rightarrow \\tilde{\\chi}_{1}^{0} t, \\ \\tilde{\\chi}_{1}^{0} \\rightarrow Z/\\gamma \\tilde{G}$"

        table.keywords["cmenergies"] = ["13000"]
        table.keywords["observables"] = ["signal"]
        table.keywords["phrases"] = ["SUSY","GMSB","Supersymmetry"]
        table.keywords["reactions"] = ["P P"]
        table.add_image("../rootfiles/"+sample+"_exclusion.pdf")
        dat = np.loadtxt(arg2[a]+".txt", skiprows=0)
        data = np.where(dat==-1, '-', dat)
        from hepdata_lib import Variable
        if "T6ttZg" in sample:
            d = Variable("$m_{\\tilde{t}}$", is_independent=True, is_binned=False, units="GeV")
        else:
            d = Variable("$m_{\\tilde{g}}$", is_independent=True, is_binned=False, units="GeV")
        d.values = data[:,0]
        y1 = Variable("max $m_{\\tilde{\\chi}_{1}^{0}}$ excluded", is_independent=False, is_binned=False, units="GeV")
        y1.values = data[:,1]

        y2 = Variable("max $m_{\\tilde{\\chi}_{1}^{0}} - 1 \\sigma$ excluded", is_independent=False, is_binned=False, units="GeV")
        y2.values = data[:,2]

        y3 = Variable("max $m_{\\tilde{\\chi}_{1}^{0}} + 1 \\sigma$ excluded", is_independent=False, is_binned=False, units="GeV")
        y3.values = data[:,3]

        #y1.add_qualifier("Process",fname)
        #y1.add_qualifier("$\sqrt s$", 13, "TeV")
        #y1.add_qualifier("LUMINOSITY", 137, "fb$^{-1}$")

        table.add_variable(d)
        table.add_variable(y1)
        table.add_variable(y2)
        table.add_variable(y3)

        submission.add_table(table)

for sample_ in ewk:
#    arg2_=["Excl_obslimit_"+sample_,"Excl_explimit_"+sample_,"Excl_exp84pclimit_"+sample_,"Excl_exp16pclimit_"+sample_]
#    arg3_=["observed","expected","expected +1sigma","expected -1sigma"]
    arg2_=["Excl_obslimit_"+sample_,"Excl_explimit_"+sample_]
    arg3_=["observed","expected"]
    print(arg2_,arg3_)
    for a in range(2):
        if "TChiWG" in sample_:
            table = Table("Figure 10 (top) "+arg3_[a])
            table.description = arg3_[a]+" exclusion limit on the neutralino mass points in the "+sample_+" model."
            table.location = "Data from Figure 10 (top), located on page 17."
            fname="$pp \\rightarrow \\tilde{\\chi}_{1}^{\\pm}\\tilde{\\chi}_{2}^{0} / \\tilde{\\chi}_{1}^{\\pm}\\tilde{\\chi}_{1}^{\\pm}$, $\\tilde{\\chi}_{1}^{\\pm} \\rightarrow W^{\\pm} \\tilde{G} , \\tilde{\\chi}_{2}^{0} \\rightarrow \\gamma \\tilde{G}$"

        elif sample_=="TChiNGnn" :
            table = Table("Figure 10 (bottom right) "+arg3_[a])
            table.description = arg3_[a]+" exclusion limit on the neutralino mass points in the "+sample_+" model."
            table.location = "Data from Figure 10 (bottom right), located on page 17."
            fname="$pp \\rightarrow \\tilde{\\chi}_{1}^{0}\\tilde{\\chi}_{2}^{0}, \\tilde{\\chi}_{1}^{0} \\rightarrow H/Z \\tilde{G} , \\tilde{\\chi}_{2}^{0} \\rightarrow \\gamma \\tilde{G}$"

        elif sample_=="TChiNG":
            table = Table("Figure 10 (bottom left) "+arg3_[a])
            table.description= arg3_[a]+" exclusion limit on the neutralino mass points in the "+sample_+" model."
            table.location = "Data from Figure 10 (bottom left), located on page 17."
            fname="$pp \\rightarrow \\tilde{\\chi}_{1}^{\\pm}\\tilde{\\chi}_{1}^{\\pm} / \\tilde{\\chi}_{1}^{0}\\tilde{\\chi}_{2}^{0} / \\tilde{\\chi}_{1}^{\\pm}\\tilde{\\chi}_{1/2}^{0}, \\tilde{\\chi}_{1}^{0} \\rightarrow \\gamma/H/Z \\tilde{G} , \\tilde{\\chi}_{2}^{0} \\rightarrow \\gamma/H/Z \\tilde{G}$"


        table.keywords["cmenergies"] = ["13000"]
        table.keywords["observables"] = ["signal"]
        table.keywords["phrases"] = ["SUSY","GMSB","Supersymmetry","Electroweakino","EWK","137 $fb^{-1}$"]
        table.keywords["reactions"] = ["P P"]
        table.add_image("../rootfiles/"+sample_+".pdf")
        dat = np.loadtxt(arg2_[a]+".txt", skiprows=0)
        data = np.where(dat==-1, '-', dat)
        d = Variable("$m_{NLSP}$", is_independent=True, is_binned=False, units="GeV")        
        d.values = data[:,0]
        y1 = Variable("$\\sigma_{expected}$", is_independent=False, is_binned=False, units="pb")
        y1.values = data[:,1]
        if arg3_[a] == "expected":
            y2 = Variable("$\\sigma_{expected}$ - 1\\sigma_{experiment}", is_independent=False, is_binned=False, units="pb")
            y2.values = data[:,2]
            y3 = Variable("$\\sigma_{expected}$ + 1\\sigma_{experiment}", is_independent=False, is_binned=False, units="pb")
            y3.values = data[:,3]

        y1.add_qualifier("Process",fname)
        table.add_variable(d)
        table.add_variable(y1)
        if arg3_[a] ==	"expected":
            table.add_variable(y2)
            table.add_variable(y3)

        submission.add_table(table)


submission.create_files("example_output",remove_old=True)
