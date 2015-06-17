% Klasa dokumentow do skladu prac magisterskich i~licencjackich
% na wydziale Matematyki, Mechaniki i~Informatyki UW.
%
% Copyright (c) 2001 by Wydzial Matematyki, Informatyki i Mechaniki.
%
% Zmiany 05.05.2006 by Seweryn Karlowicz

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{pracamgr}[2006/05/05 v0.5.0 Praca magisterska]




% Required packages
\RequirePackage{graphicx}
\RequirePackage{hyperref}
\hypersetup{
	linktocpage,
    colorlinks,
    citecolor=Crimson,
    filecolor=black,
    linkcolor=black,
    urlcolor=Crimson,
}

\RequirePackage[centertags]{amsmath}
\RequirePackage{amssymb}
\RequirePackage[numbers, comma, sort&compress]{natbib}
\RequirePackage[small, md, sc]{titlesec}
\RequirePackage[tight,nice]{units}
\RequirePackage{verbatim}

% colors
\RequirePackage{color}
\definecolor{Crimson}{rgb}{0.6471, 0.1098, 0.1882}

\RequirePackage{url}
\RequirePackage[titles]{tocloft}
\setcounter{tocdepth}{1}
\renewcommand{\cftchapfont}{\normalsize \scshape}






\def\@baseclass{report}
\def\@rodzajpracy{magisterska}
\DeclareOption{licencjacka}{\def\@rodzajpracy{licencjacka}}
\DeclareOption*{\PassOptionsToClass{\CurrentOption}{\@baseclass}}
\PassOptionsToClass{a4paper,twoside,openright,11pt}{\@baseclass}
\ProcessOptions

\LoadClass{\@baseclass}

\textwidth\paperwidth
\advance\textwidth -55mm
\oddsidemargin-1in
\advance\oddsidemargin 30mm
\evensidemargin-1in
\advance\evensidemargin 25mm
\topmargin -1in
\advance\topmargin 2cm
\setlength\textheight{48\baselineskip}
\addtolength\textheight{\topskip}
\marginparwidth15mm




\renewcommand\maketitle{%
  \begin{titlepage}%
    \let\footnotesize\small
    \let\footnoterule\relax
    \let \footnote \thanks
    \begin{center}%
     % {\LARGE\textbf{Szko\l{}a G\l{}\'owna Handlowa}\\
%        Wydzia\l{} Matematyki, Informatyki i Mechaniki\par
     % }
         \includegraphics[width=100mm]{sgh.png}\\
      \vspace{5mm plus 1fill} 
      {\Large\bf Master studies}
      \vspace{0.2cm}
      \vspace{8mm plus 1fill}
      \begin{flushleft}\large
        \begin{tabular}{l}
          
          Faculty \bfseries \@kierunek\par\\
        \end{tabular}
      \end{flushleft}
      
      \vspace{8mm plus 1fill}
      \begin{flushright}\large
        \begin{tabular}{l}
          
          Author name: \bfseries \@author\par\\
          Id no.: \bfseries \@nralbumu\par\\
        \end{tabular}
      \end{flushright}
      \vspace{8mm plus 1fill}
      {\Huge\textbf{\@title}\par}
      \vspace{8mm plus 1fill}
      \vspace{1cm plus .1fill}
%----zakres---
      \begin{flushright}\large
        \begin{tabular}{l}
          Praca magisterska\\
          napisana w Instytucie\\
          \bfseries \@instytut\\ 
          pod kierunkiem naukowym\\          
          \bfseries \@opiekun
        \end{tabular}
      \end{flushright}
      \vspace{5mm plus 1fill}
      {\large \@date\par}
    \end{center}
    \@thanks
  \end{titlepage}%
  \setcounter{footnote}{0}%
  \global\let\thanks\relax
  \global\let\maketitle\relax
  \global\let\@thanks\@empty
  \global\let\@author\@empty
  \global\let\@date\@empty
  \global\let\@title\@empty
  \global\let\title\relax
  \global\let\author\relax
  \global\let\date\relax
  \global\let\and\relax
}
\def\nralbumu#1{\gdef\@nralbumu{#1}}
\def\@nralbumu{???\ClassError{pracamgr}{Brak numeru albumu}\@ehc}
\def\kierunek#1{\gdef\@kierunek{#1}}
\def\@kierunek{???\ClassError{pracamgr}{Nie podano kierunku studiow}\@ehc}
%----zakres nie konieczny-----
\def\zakres#1{\gdef\@zakres{w zakresie \MakeUppercase{#1}}}
\def\@zakres{}
\def\instytut#1{\gdef\@instytut{#1}}
\def\@instytut{???\ClassError{pracamgr}{Brak danych o instytucie }\@ehc}
\def\opiekun#1{\gdef\@opiekun{#1}}
\def\@opiekun{???\ClassError{pracamgr}{Brak danych opiekuna pracy}\@ehc}
\def\keywords#1{\gdef\@keywords{#1}}
\def\@keywords{???\ClassError{pracamgr}{Brak slow kluczowych}\@ehc}
\def\dziedzina#1{\gdef\@dziedzina{#1}}
\def\@dziedzina{???\ClassError{pracamgr}{Brak dziedziny Socrates-Erasmus}\@ehc}
\def\klasyfikacja#1{\gdef\@klasyfikacja{#1}}
\def\@klasyfikacja{???\ClassError{pracamgr}{Brak klasyfikacji tematycznej}\@ehc}
%-------------------nowe------------
\def\tytulang#1{\gdef\@tytulang{#1}}
\def\@tytulang{???\ClassError{pracamgr}{Brak tytulu po angielsku}\@ehc}


\renewenvironment{abstract}{%
  \titlepage
  \null\nobreak\vfil
  \@beginparpenalty\@lowpenalty
  \begin{center}%
    \bfseries\large \abstractname
    \@endparpenalty\@M
  \end{center}}%
{\par  
  \vspace*{26pt}%
  \begin{center}%
    \bfseries\large Keywords 
    \@endparpenalty\@M
  \end{center}
  \@keywords\par
  \vspace*{26pt}%
  \begin{center}%
    \bfseries\large Dziedzina pracy (kody wg programu Socrates-Erasmus)
    \@endparpenalty\@M
  \end{center}
   \@dziedzina\par
  \vspace*{26pt}%
  \begin{center}%
    \bfseries\large Klasyfikacja tematyczna
    \@endparpenalty\@M
  \end{center}
  \@klasyfikacja\par
  \vspace*{26pt}%
%-------------------nowosc----------------
  \begin{center}%
    \bfseries\large Tytu{\l} pracy w j¦zyku angielskim
    \@endparpenalty\@M
  \end{center}
  \@tytulang\par
  \nobreak\vfil\null\endtitlepage\cleardoublepage}

\def\cleardoublepage{\clearpage\if@twoside \ifodd\c@page\else
    \hbox{}\thispagestyle{empty}\newpage\if@twocolumn\hbox{}\newpage\fi\fi\fi}

\renewcommand*\@seccntformat[1]{\csname the#1\endcsname.\enspace}
\def\numberline#1{\hb@xt@\@tempdima{#1.\hfil}}
\renewcommand*\l@chapter[2]{%
  \ifnum \c@tocdepth >\m@ne
    \addpenalty{-\@highpenalty}%
    \vskip 1.0em \@plus\p@
    \setlength\@tempdima{1.5em}%
    \begingroup
      \parindent \z@ \rightskip \@pnumwidth
      \parfillskip -\@pnumwidth
      \leavevmode \bfseries
      \advance\leftskip\@tempdima
      \hskip -\leftskip
      #1\nobreak\mdseries
      \leaders\hbox{$\m@th
        \mkern \@dotsep mu\hbox{.}\mkern \@dotsep
        mu$}\hfill
      \nobreak\hb@xt@\@pnumwidth{\hss #2}\par
      \penalty\@highpenalty
    \endgroup
  \fi}

\endinput
