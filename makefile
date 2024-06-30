CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SERVER_SRC = server.cpp log.cpp
CLIENT_SRC = client.cpp

SERVER_EXE = server
CLIENT_EXE = client

all: $(SERVER_EXE) $(CLIENT_EXE)

$(SERVER_EXE): $(SERVER_SRC)
	$(CXX) $(CXXFLAGS) -o $(SERVER_EXE) $(SERVER_SRC)

$(CLIENT_EXE): $(CLIENT_SRC)
	$(CXX) $(CXXFLAGS) -o $(CLIENT_EXE) $(CLIENT_SRC)

clean:
	rm -f $(SERVER_EXE) $(CLIENT_EXE)

.PHONY: all clean
