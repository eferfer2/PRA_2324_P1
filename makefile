bin/testListArray: testListArray.cpp listArray.h list.h
	mkdir -p bin
	g++ -o bin/testListArray testListArray.cpp listArray.h

clean:
	rm -r *.o *.gch bin
bin/testNode: testNode.cpp node.h
	mkdir -p bin
	g++ -o bin/testNode testNode.cpp node.h

bin/testListLinked: testListLinked.cpp ListLinked.h list.h
	mkdir -p bin
	g++ -o bin/testListLinked testListLinked.cpp ListLinked.h
