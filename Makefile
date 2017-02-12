OUTPUT := output/

all: $(OUTPUT)tcf

TCF_SRC := tcf.c tcf_f.c

-include $(OUTPUT)tcf.d

$(OUTPUT)tcf: $(TCF_SRC)
	mkdir -p $(OUTPUT)
	gcc -Wall $(TCF_SRC) -MMD -MF $(@).d -o $@
