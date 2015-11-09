ssh -t ubuntu_parallels 'cd  /media/psf/Dropbox/MastersTheses/UW-Master-Thesis/praca && xelatex -shell-escape -synctex=1 -interaction=nonstopmode uw.tex'
ssh -t ubuntu_parallels 'cd  /media/psf/Dropbox/MastersTheses/UW-Master-Thesis/praca && bibtex uw.aux'
#ssh -t ubuntu_parallels 'cd  /media/psf/Home/Dropbox/MastersTheses/SGH-Master-Thesis/praca && makeindex masterThesisSGH.idx'
ssh -t ubuntu_parallels 'cd  /media/psf/Dropbox/MastersTheses/UW-Master-Thesis/praca && xelatex -shell-escape -synctex=1 -interaction=nonstopmode uw.tex'
open praca/uw.pdf
