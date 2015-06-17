ssh -t ubuntu_parallels 'cd  /media/psf/Dropbox/MastersTheses/SGH-Master-Thesis/praca && pdflatex -synctex=1 -interaction=nonstopmode masterThesisSGH.tex'
ssh -t ubuntu_parallels 'cd  /media/psf/Dropbox/MastersTheses/SGH-Master-Thesis/praca && bibtex masterThesisSGH.aux'
ssh -t ubuntu_parallels 'cd  /media/psf/Dropbox/MastersTheses/SGH-Master-Thesis/praca && pdflatex -synctex=1 -interaction=nonstopmode masterThesisSGH.tex'
open masterThesisSGH.pdf
