txt-files   := $(wildcard 9x9/*.txt)
smt-files   := $(patsubst %.txt,%.smt,$(txt-files))
txt16-files := $(wildcard 16x16/*.txt)
smt16-files := $(patsubst %.txt,%int.smt,$(txt16-files)) $(patsubst %.txt,%bv.smt,$(txt16-files)) $(patsubst %.txt,%uffs.smt,$(txt16-files))
zip-flags   := -9DX

clean:
	rm -f $(smt-files) $(smt16-files) 9x9.zip 16x16.zip all.zip sudoku-smt sudoku16-smt

sudoku16-int: sudoku16-int.c
sudoku16-bv: sudoku16-bv.c
sudoku16-uffs: sudoku16-uffs.c
sudoku-smt: sudoku-smt.c
	$(CC) $< $(CFLAGS) -o $@

9x9/%.smt: 9x9/%.txt sudoku-smt
	./sudoku-smt < $< > $@

16x16/%int.smt: 16x16/%.txt sudoku16-int
	./sudoku16-int < $< > $@

16x16/%bv.smt: 16x16/%.txt sudoku16-bv
	./sudoku16-bv < $< > $@

16x16/%uffs.smt: 16x16/%.txt sudoku16-uffs
	./sudoku16-uffs < $< > $@

all-smt: $(smt-files) $(smt16-files)

9x9.zip: $(smt-files)
	zip $(zip-flags) $@ $^

16x16.zip: $(smt16-files)
	zip $(zip-flags) $@ $^

all.zip: $(smt-files) $(smt16-files)
	zip $(zip-flags) $@ $^
