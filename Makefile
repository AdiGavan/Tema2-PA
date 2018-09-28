build: minlexbfs revedges disjcnt

minlexbfs: minlexbfs.cpp
	g++ -Wall -Wextra minlexbfs.cpp -o minlexbfs

disjcnt: disjcnt.cpp
	g++ -std=c++11 -Wall -Wextra disjcnt.cpp -o disjcnt

revedges: revedges.cpp
	g++ -Wall -Wextra revedges.cpp -o revedges

run-p1:
	./minlexbfs

run-p2:
	./disjcnt

run-p4:
	./revedges

clean:
	rm -f minlexbfs revedges disjcnt *.o
