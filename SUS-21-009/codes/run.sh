#!/bin/sh


rm *limit*.txt
for i in T5bbbbZg T5qqqqHg T5ttttZg T6ttZg
do
    for j in exp obs 
    do
	root -l -q 'limittoText.C("../rootfiles/'${i}'_sigsys_new2.root","Excl_'${j}'limit_'${i}'.txt","'${j}'")'
    done
done
for i in TChiWG TChiNG TChiNGnn
do
    for j in exp obs
    do
        root -l -q 'limittoText.C("../rootfiles/limitPlotter_'${i}'.root","Excl_'${j}'limit_'${i}'.txt","'${j}'")'
    done
    
done

python3.10 limitPlotToYaml.py

rm *.yaml
for i in T5bbbbZg T5qqqqHg T5ttttZg T6ttZg                                                                                                                                 
do   
    root -l -q 'convertTH2ToYAML_Remove0Val.C("../rootfiles/'${i}'_sigsys_new2.root","mGlmNLSP_XsecUL_fb")' 
done
for i in T5bbbbZg T5qqqqHg T5ttttZg T6ttZg
do
    root -l -q 'convertTH3ToYAML_Remove0Val.C("../rootfiles/accxeff_3D_'${i}'v2.root","'${i}'v2_Accxeff")'  
done

cp *_xsec_obs.yaml example_output/.
cp *_Accxeff.yaml example_output/.

#grep -v "Processing" 1.txt > tmp && mv tmp 1.txt
#grep -v "nX" 1.txt > tmp && mv tmp 2dhist.txt
#rm 1.txt

####### Content of this textfile will be added to the example_output/submission.yaml
#hepdata-validate -d example_output/
#tar czf submission.tar.gz example_output/

