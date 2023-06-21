OUTDIR ?= .

build:
	mkdir -p $(OUTDIR)
	gcc write.c -o $(OUTDIR)/write
	gcc read.c -o $(OUTDIR)/read

clean:
	rm $(OUTDIR)/write $(OUTDIR)/read
