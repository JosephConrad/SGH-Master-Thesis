import pandas as pd
import sys


def latexTable(caption, ref, filename, sep='\t'):
    print r'\begin{table}[htbp]' 
    print r'\centering'     
    print r'\resizebox{\textwidth}{!}{'
    print r'\begin{tabular}{lrrrrr}'
    print r'\toprule'
    with open(filename,'r') as f:
        for line in f:
            words = line.split(sep)
            if words[0] == '':
                print r'\midrule'
                print r'{} & {} & {} & {} & ' + words[1].rstrip() + r' \\'
                print r'\midrule'
            else:
                print ' & '.join(filter(None, line.rstrip().split(sep))) + r' \\'  
    #sys.stdout.write(df.to_latex())
    
    
    print r'\bottomrule'
    print r'\end{tabular}'
    print r'}'
    print r'\caption{{{0}}}'.format(caption)
    print r'\label{{tab:{0}}}'.format(ref)
    print r'\end{table}'


#latexTable("caption", "ref", '../../../output/hestonSimulation.txt')
calibration = "/Users/konrad/Dropbox/MastersTheses/SGH-Master-Thesis/input/inputmatlab/calibration.txt"
latexTable("caption", "ref", calibration, ';')
