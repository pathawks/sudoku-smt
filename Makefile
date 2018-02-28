txt-files   := $(wildcard 9x9/*.txt)
smt-files   := $(foreach file,$(txt-files),$(patsubst %.txt,%.smt,$(file)))
txt16-files := $(wildcard 16x16/*.txt)
smt16-files := $(foreach file,$(txt16-files),$(patsubst %.txt,%.smt,$(file)))

clean:
	rm -f $(smt-files) $(smt16-files) 9x9.zip 16x16.zip sudoku-smt sudoku16-smt

sudoku16-smt: sudoku16-smt.c
	gcc sudoku16-smt.c -O2 -o sudoku16-smt

sudoku-smt: sudoku-smt.c
	gcc sudoku-smt.c -O2 -o sudoku-smt

define smt9
$(1).smt: $(1).txt sudoku-smt
	./sudoku-smt < $(1).txt > $(1).smt
endef

define smt16
$(1).smt: $(1).txt sudoku-smt
	./sudoku16-smt < $(1).txt > $(1).smt
endef

$(foreach file,$(txt-files),  $(eval $(call smt9, $(patsubst %.txt,%,$(file)))))
$(foreach file,$(txt16-files),$(eval $(call smt16,$(patsubst %.txt,%,$(file)))))

9x9.zip: $(smt-files)
	zip -9DX 9x9.zip $(smt-files)

16x16.zip: $(smt16-files)
	zip -9DX 16x16.zip $(smt16-files)
