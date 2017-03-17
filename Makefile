OUTPUT := output/

all: $(OUTPUT)tcf

PHONY: tags clean

tags:
	etags *.[ch]

clean:
	$(RM) -r $(OUTPUT)

-include $(OUTPUT)tcf.d

$(OUTPUT)tcf-rom.c: tcf.fth fth2c
	mkdir -p $(OUTPUT)
	./fth2c 64 little-endian $< > $@

$(OUTPUT)tcf: tcf.c $(OUTPUT)tcf-rom.c
	mkdir -p $(OUTPUT)
	gcc -std=c89 -Wall -Wextra -Werror $< -MMD -MF $(@).d -o $@
