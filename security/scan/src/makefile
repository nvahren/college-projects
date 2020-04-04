EXEC = syn_scan

all: syn_scan.cpp
	g++ syn_scan.cpp -o $(EXEC) -lcrafter -lpcap -lpthread -lresolv
debug: syn_scan.cpp
	g++ syn_scan.cpp -o $(EXEC) -lcrafter -lpcap -lpthread -lresolv -DDEBUG
clean:
	rm -f $(EXEC)