txt-files   := $(wildcard 9x9/*.txt)
smt-files   := $(foreach file,$(txt-files),$(patsubst %.txt,%.smt,$(file)))
txt16-files := $(wildcard 16x16/*.txt)
smt16-files := $(foreach file,$(txt16-files),$(patsubst %.txt,%.smt,$(file)))

clean:
	rm -f $(smt-files) $(smt16-files) 9x9.zip 16x16.zip sudoku-smt sudoku16-smt

sudoku16-smt: sudoku16-smt.c
	$(CC) $< $(CFLAGS) -o $@

sudoku-smt: sudoku-smt.c
	$(CC) $< $(CFLAGS) -o $@

9x9/%.smt: 9x9/%.txt sudoku-smt
	./sudoku-smt < $< > $@

16x16/%.smt: 16x16/%.txt sudoku16-smt
	./sudoku16-smt < $< > $@

9x9.zip: $(smt-files)
	zip -9DX $@ $^

16x16.zip: $(smt16-files)
	zip -9DX $@ $^
