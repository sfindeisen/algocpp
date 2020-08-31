include Makefile.programs

PROGS__=$(addprefix out/test-, $(PROGSBASE))
PROGS=$(addsuffix .out, $(PROGS__))

CCPP=g++
CPPFLAGS+= -Wall -std=c++11
LNFLAGS+= -lboost_unit_test_framework
DIROUT=out

.PHONY : default
default: all

.PHONY : all
all : makedirs $(PROGS)

$(PROGS): $(DIROUT)/%.out: %.cpp
	$(CCPP) $(CPPFLAGS) $(LNFLAGS) $< -o $@

.PHONY : makedirs
makedirs:
	mkdir -p $(DIROUT)

.PHONY : clean
clean:
	-rm $(PROGS)
	-rmdir $(DIROUT)

.PHONY : run
run : all
	out/test-avl.out
	out/test-algebra.out
	out/test-text.out
