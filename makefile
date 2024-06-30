CFLAGS = -std=c++17
OUTDIR = out

.PHONY: all
all: $(OUTDIR)/client $(OUTDIR)/server

$(OUTDIR)/client: client.cpp client.h | $(OUTDIR)
	g++ $(CFLAGS) -o $@ client.cpp

$(OUTDIR)/server: server.cpp server.h | $(OUTDIR)
	g++ $(CFLAGS) -o $@ server.cpp

$(OUTDIR):
	mkdir -p $(OUTDIR)

.PHONY: clean
clean:
	rm -rf $(OUTDIR)
