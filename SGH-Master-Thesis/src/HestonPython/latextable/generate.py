import pandas as pd
import numpy as np
import sys

def latexTable(caption, ref):  
    print r'\begin{table}[htbp]'
    print r'\centering'
    df = pd.DataFrame(np.random.random((5, 5)))
    sys.stdout.write(df.to_latex())
    print r'\caption{{{0}}}'.format(caption)
    print r'\label{{tab:{0}}}'.format(ref)
    print r'\end{table}'

latexTable("caption", "ref")  
