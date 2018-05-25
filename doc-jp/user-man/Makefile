# $Id: Makefile,v 1.10 2006/01/25 09:38:12 vdmtools Exp $

LATEX = latex
PLATEX = platex -kanji=utf8
DVIPDFMX = dvipdfmx
DVIPDFM = dvipdfm
BIBTEX = bibtex
JBIBTEX = pbibtex -kanji=sjis
MAKEINDEX = makeindex
MENDEX = mendex -U
EBB = ebb
IFDEFFILT = ../../code/make_tools/ifdeffilt


OUTPUTDOCS = usermansl_a4E usermanpp_a4E usermanvice_a4E \
	usermansl_a4J usermanpp_a4J usermanvice_a4J \
	glossary_en glossary_jp
SUFF = ps aux dvi log bbl blg toc idx ilg ind tex out

FIGDIR=figures

TEXTMP = $(foreach suf,$(SUFF), $(foreach b, $(OUTPUTDOCS), $(b).$(suf))) 

all: alleng alljpn
alljpn: usermansl_a4J.pdf usermanpp_a4J.pdf
alleng: usermansl_a4E.pdf usermanpp_a4E.pdf
#alljpn: usermansl_a4J.pdf usermanpp_a4J.pdf usermanvice_a4J.pdf
#alleng: usermansl_a4E.pdf usermanpp_a4E.pdf usermanvice_a4E.pdf

%J.pdf: %J.tex user_man.bib glossary_jp.tex makebb
	rm -f $*.aux $*.out $*.toc $@
	$(PLATEX) $<
	$(JBIBTEX) $(<:J.tex=J)
	$(MENDEX) $*J.idx
	$(PLATEX) $<
	$(PLATEX) $<
	$(DVIPDFMX) $(<:J.tex=J.dvi)

%E.pdf: %E.tex user_man.bib glossary_en.tex makebb
	rm -f $*.aux $*.out $*.toc $@
	$(PLATEX) $<
	$(BIBTEX) $(<:E.tex=E)
	$(MAKEINDEX) $*E.idx
	$(PLATEX) $<
	$(PLATEX) $<
	$(DVIPDFMX) $(<:E.tex=E.dvi)

usermansl_a4E.tex: user_man.tex
	rm -f $@
	$(IFDEFFILT) -DVDMSL -DENG -DA4Format $< > $@
	chmod a-w $@

usermansl_a4J.tex: user_man.tex
	rm -f $@
	$(IFDEFFILT) -DVDMSL -DJPN -DA4Format $< > $@
	chmod a-w $@

usermanpp_a4E.tex: user_man.tex
	rm -f $@
	$(IFDEFFILT) -DVDMPP -DPPONLY -DENG -DA4Format $< > $@
	chmod a-w $@

usermanpp_a4J.tex: user_man.tex
	rm -f $@
	$(IFDEFFILT) -DVDMPP -DPPONLY -DJPN -DA4Format $< > $@
	chmod a-w $@

usermanvice_a4E.tex: user_man.tex
	rm -f $@
	$(IFDEFFILT) -DVICEMAN -DENG -DVDMPP -DA4Format $< > $@
	chmod a-w $@

usermanvice_a4J.tex: user_man.tex
	rm -f $@
	$(IFDEFFILT) -DVICEMAN -DJPN -DVDMPP -DA4Format $< > $@
	chmod a-w $@

glossary_en.tex: glossary.tex
	rm -f $@
	$(IFDEFFILT) -DENG $< > $@
	chmod a-w $@

glossary_jp.tex: glossary.tex
	rm -f $@
	$(IFDEFFILT) -DJPN $< > $@
	chmod a-w $@

user_man.bib: 
	cp ../../doc/bib/ifad.bib $@

makebb:
	cd $(FIGDIR); $(EBB) *.png

# What to clean. 
clean: 
	rm -f $(TEXTMP) user_man.bib *.pbm $(FIGDIR)/*.bb
