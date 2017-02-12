all: tcf

tcf: tcf.c tcf_f.c tcf_f.h
	gcc -Wall tcf.c tcf_f.c -o $@
