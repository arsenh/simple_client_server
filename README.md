# Echo tcp client/server

Simple client server application does not depends on third party libraries. Application used only Windows and GNU/Linux native sockets API.

Run following commands to build the project.

#### For GNU/Linux operation system
- `cd simple_client_server`
- `mkdir build`
- `cmake .. -G "Unix Makefiles"`
- `make`

#### For Windows operation system
- `cd simple_client_server`
- `mkdir build`
- `cmake .. -G "Visual Studio 16 2019"`
- `Open simple_client_server.sln file from Visual Studio 2019.`


#### Usage

Windows
- `server.exe --address 127.0.01 --port 8080`
- `client.exe --address 127.0.01 --port 8080`

GNU/Linux
- `./server --address 127.0.01 --port 8080`
- `./client --address 127.0.01 --port 8080`
