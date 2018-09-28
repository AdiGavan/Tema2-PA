"Copyright [2018] Gavan Adrian-George, 324CA"
Nume, prenume: Gavan, Adrian-George
Grupa, seria: 324CA

Tema 2 PA - Grafuri
===================

Problema 1
==========

- S-a pornit de la scheletul din laborator.
- Tot ce trebuia facut era sa aplicam BFS, doar ca trebuia ca vecinii unui nod sa fie luati in
ordine crescatoare. Asadar, inainte sa se inceapa parcurgerea, s-a sortat lista de adiacenta
a fiecarui nod.
- S-a aplicat BFS si mereu cand se extragea un nod din coada, acesta era introdus in vectorul
in care se retin elementele in ordinea parcurgerii.
- O alta varianta optima ar fi fost ca listele de adiacenta sa fie minheap-uri, pentru ca dupa
introducerea elementelor acestea sa fie deja sortate.
- Complexitatea este: n * O(n * logn) (daca graful ar fi complet => n sortari a cate n-1 noduri)
+ O(n + m) (BFS).

Problema 2 (prima idee, destul de ineficienta dar trecea testele... disjcnt.cpp)
==========

- S-a pornit de la scheletul din laborator.
- Ca si idee, trebuia sa se gaseasca muchiile critice, apoi se puteau gasi componentele conexe,
iar toate nodurile care fac parte dintr-o componenta formeaza perechi valide.
- Numarul de perechi valide dintr-o componenta poate fi dedus cu formula:
numar_perechi = nr_elem * (nr_elem - 1) / 2.
- Pentru a se gasi muchiile critie se aplica algoritmul lui Tarjan, iar pentru a afla componentele
conexe se aplica BFS din fiecare nod nevizitat.
- Problema cea mai mare era faptul ca muchiile puteau fi duplicate (se putea primii de ori cate
ori muchia 3-4 de exemplu). Solutia gasita a fost ca pentru muchiile duplicat sa se "simuleze" o
muchie utilizand 2 noduri suplimentare. Astfel, sa spuneam ca avem muchia 3-4 in graf:

                              ------3--------4------

- Daca de la tastatura se citeste iar muchia 3-4, atunci se vor crea 2 noduri noi suplimentare si
se vor conecta cu nodurile 3-4 astfel:

                                    3'-------4'
                                    |        |
                                    |        |
                              ------3--------4------

- In acest fel, se simuleaza muchia duplicata si nu mai apar probleme (un exemplu de problema ar fi
faptul ca in acest exemplu, daca nu simulam o alta muchie si lasam doar muchia 3-4 simplu, aceasta
ar fi fost muchie critica, ceea ce nu este ok pentru ca ea era duplicat si nu ar trebui sa fie
muchie critica).
- Complexitatea este: O(n + m) pentru Tarjan + O(m) pentru eliminare muchii (in cel mai rau caz toate
muchiile initiale sunt muchii critice, ceea ce inseamna ca nu a fost nevoie de noduri suplimentare si
alte muchii) + O(n+m) pentru BFS.

Problema 2 (disjcntNou.cpp)
==========

- S-a pornit de la scheletul din laborator.
- Aceeasi idee ca si in varianta mai ineficienta. Trebuiau sa se gaseasca muchiile critice, apoi se
puteau gasi componentele conexe, iar toate nodurile care fac parte dintr-o componenta formeaza perechi
valide.
- Fata de algoritmul anterior, doar se modifica putin algoritmul lui tarjan => nu mai este nevoie sa se
creeze toate nodurile si muchiile suplimentare. De asemenea, am modificat si cautarea componentelor 
conexe ca sa nu mai fie nevoie sa eliminam muchiile critice din graf.

Problema 4
==========

- S-a pornit de la scheletul din laborator.
- Pentru a rezolva aceasta problema, s-a utilizat urmatoarea idee:
- Fiecarui arc al grafului dat din problema i se va asocia costul 0.
- Pentru fiecare arc creat al grafului, se va creea si arcul orientat in sens invers, iar
acestuia i se va asocia costul 1.
- Dupa ce vom avea matricea ponderilor, se aplica Roy-Floyd pentru a se calcula distantele minime
din orice nod in orice nod. Numarul de arce a caror orientare trebuie schimbata pentru a avea
drum de la un nod X la un nod Y este dat chiar de valoarea drumului minim. Acest fapt se datoreaza
faptului ca arcele grafului initial au cost 0 si cele create de noi cost 1. Daca drumul minim nu
este 0, inseamna ca nu exista drum direct si s-a utilizat un arc creat de noi de cost 1.
- Complexitatea este: O(n ^ 3) pentru Roy-Floyd + O(q) pentru interogari.
