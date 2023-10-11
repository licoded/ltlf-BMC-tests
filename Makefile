FORMULAFILES	=	formula/aalta_formula.cpp
PARSERFILES		=	ltlparser/ltl_formula.c ltlparser/ltllexer.c ltlparser/ltlparser.c ltlparser/trans.c
UTILFILES		=	util/utility.cpp

ALLFILES		=	main.cpp $(FORMULAFILES) $(PARSERFILES) $(UTILFILES)


CC				=   g++ -std=c++11
DIS_WARN_FLAGS	=	-Wno-deprecated
FLAG			=	$(DIS_WARN_FLAGS) -I./ -D __STDC_LIMIT_MACROS -D __STDC_FORMAT_MACROS -fpermissive #-fsanitize=address -fno-omit-frame-pointer
DEBUGFLAG		=	-D DEBUG -g -pg
RELEASEFLAG		=	-O3

ltlfsyn-bmc :	release

ltlparser/ltllexer.c :
	ltlparser/grammar/ltllexer.l
	flex ltlparser/grammar/ltllexer.l

ltlparser/ltlparser.c :
	ltlparser/grammar/ltlparser.y
	bison ltlparser/grammar/ltlparser.y
	
	

.PHONY :    release debug clean

release :   $(ALLFILES)
	    $(CC) $(FLAG) $(RELEASEFLAG) $(ALLFILES) -lm -lz -o ltlfsyn-bmc

debug :	$(ALLFILES)
	$(CC) $(FLAG) $(DEBUGFLAG) $(ALLFILES) -lm -lz -o ltlfsyn-bmc

clean :
	rm -f *.o *~ ltlfsyn-bmc
