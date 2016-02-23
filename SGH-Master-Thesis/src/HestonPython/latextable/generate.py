import pandas as pd
import sys


def latexTable(caption, ref, filename):
    print r'\begin{table}[htbp]'
    print r'\centering'
    df = pd.read_csv(filename, sep='\t\t', engine='python')
    sys.stdout.write(df.to_latex())
    print r'\caption{{{0}}}'.format(caption)
    print r'\label{{tab:{0}}}'.format(ref)
    print r'\end{table}'


latexTable("caption", "ref", '../../../output/hestonSimulation.txt')
