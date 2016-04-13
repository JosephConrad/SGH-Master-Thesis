#ssh -t ubuntu_parallels 'cd  /media/psf/Home/Dropbox/MastersTheses/SGH-Master-Thesis/praca && xelatex -shell-escape -synctex=1 -interaction=nonstopmode masterThesisSGH.tex'
ssh -t ubuntu_parallels 'cd  /media/psf/Home/Dropbox/MastersTheses/SGH-Master-Thesis/praca && bibtex masterThesisSGH.aux'
#ssh -t ubuntu_parallels 'cd  /media/psf/Home/Dropbox/MastersTheses/SGH-Master-Thesis/praca && makeindex masterThesisSGH.idx'
ssh -t ubuntu_parallels 'cd  /media/psf/Home/Dropbox/MastersTheses/SGH-Master-Thesis/praca && xelatex -shell-escape -synctex=1 -interaction=nonstopmode masterThesisSGH.tex'
open ~/Dropbox/MastersTheses/SGH-Master-Thesis/praca/masterThesisSGH.pdf
