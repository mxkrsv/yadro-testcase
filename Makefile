OUTDIR ?= .
DOCKER ?= docker
CC ?= gcc

dockerbuild:
	$(DOCKER) build . -t yadro-testcase

dockerrun:
	$(DOCKER) run --rm localhost/yadro-testcase:latest

dockerclean:
	$(DOCKER) rmi localhost/yadro-testcase:latest

build:
	mkdir -p $(OUTDIR)
	$(CC) write.c -o $(OUTDIR)/write
	$(CC) read.c -o $(OUTDIR)/read

run:
	./write | ./read

clean:
	rm $(OUTDIR)/write $(OUTDIR)/read
