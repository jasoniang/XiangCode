Dst = proc
Include = -I/usr/local/protobuf/include -I/root/Code/Pro5/Include/
Libs = -L/usr/local/protobuf/lib  -L/usr/lib64/mysql -L./Lib -ljsoncpp -lprotobuf -lmysqlclient -lpthread -lstdc++
Src = main.cpp test.pb.cc taskMemory.cpp shareMemory.cpp

$(Dst) : $(Src)
	g++ $(Src) -o $(Dst)  $(Libs) $(Include)

clean:
	rm -rf $(Dst)