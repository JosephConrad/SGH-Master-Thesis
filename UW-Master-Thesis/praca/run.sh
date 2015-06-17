ssh -t ubuntu_parallels 'cd  /media/psf/Dropbox/MastersTheses/UW-Master-Thesis/praca && pdflatex -synctex=1 -interaction=nonstopmode uw.tex'
ssh -t ubuntu_parallels 'cd  /media/psf/Dropbox/MastersTheses/UW-Master-Thesis/praca && bibtex uw.aux'
ssh -t ubuntu_parallels 'cd  /media/psf/Dropbox/MastersTheses/UW-Master-Thesis/praca && pdflatex -synctex=1 -interaction=nonstopmode uw.tex'
open uw.pdf
