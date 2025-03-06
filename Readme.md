Copyright Szabo Cristina-Andreea 2022-2023

# Image editor

Task 1: "LOAD"

- am utilizat doua structuri, una care sa retina valorile culorilor fiecarui
pixel si una care sa retina caracteristicile unei imagini
- am verificat daca o imagine a fost incarcata anterior, iar daca acesta este
cazul, eliberez memoria acesteia
- aloc memorie pentru o noua imagine
-citesc caracteristicile imaginii (tipul, dimensiunile si intensitatea maxima),
apoi elementele matricei imaginii in functie de tipul acesteia
- pentru imaginile in tonuri de gri am folosit aceeasi valoare pentru toate
culorile unui pixel, iar pentru cele color le-am citit separat
- am introdus valorile si in cele doua copii cu care voi lucra pe parcurs

Task 2: "SELECT"

- aceasta operatie selecteaza o bucata din imagine, iar cateva din urmatoarele
operatii vor fi realizate doar pe aceasta selectie
- imaginea principala (img) va deveni avea elementele selectiei si dimensiunile
acesteia
- verific daca operatia se poate efectua si afisez mesajele de eroare
corespunzatoare
- citesc noile capete ale selectiei si adaug in img, adica in selectie
elementele corespunzatoare

Task 3: "SELECT ALL"

- aceasta operatie face ca img sa redevina intreaga imagine, folosind copia 1
- daca selectia are aceleasi dimensiuni cu copia, selectia totala este deja
efectuata, asa ca ies din functie, deoarece ar fi inutil sa efectuez operatia
- introduc elementele selectiei in copia 1 la locul lor, deoarece elementele
pot avea modificari
- img va primi caracteristicile si elementele copiei, adica ale intregii
imagini

Task 4: "HISTOGRAM"

- am calculat dimensiunea unui interval apoi am calculat aparitiile pentru
valorile din fiecare interval
- calculez, de asemenea, numarul maxim de aparitii de pe un interval
- am calculat numarul de stele pentru fiecare interval cu formula,
utilizand aparitiile, numarul maxim de stele care pot fi folosite
si numarul maxim 
- afisez histograma

Task 5: "EQUALIZE"

- aceasta operatie regleaza valorile pixelilor dupa formula data
- am verificat daca operatia se poate efectua si am afisat mesajele de eroare
corespunzatoare
- am reinitializat capetele daca imaginea si copia au aceleasi dimensiuni
- initializez cu 0 vectorul aparitiilor valorilor pixelilor si apoi am calculat
numarul de aparitii a fiecarei valoare
- am facut acest lucru pentru o singura culoare pentru ca imaginea e in tonuri
de gri
- am calculat aria imaginii si valorile noilor pixeli dupa formula data,
calculand suma aparitiilor valorilor pana la valoarea anterioara a pixelului,
inmultind-o cu 255 si impartind totul la arie
- pun noile valori in selectie si copie pentru dimensiunile corespunzatoare

Task 6: "ROTATE"

- am verificat daca operatia se poate efectua si am afisat mesajele de eroare
corespunzatoare 
- am luat o funcție pentru o singura rotire la -90 de grade care foloseste trei
matrice auxiliare in care retin valorile pixelilor matricei rotite, una pentru
fiecare culoare
- eliberez memoria imaginii si a copiei 1 si le aloc memorie pentru noile
dimensiuni, daca selectia are aceleasi dimensiuni ca si copia
- interschimb valorile dimensiunilor si pun in copie si selectie noile valori,
in functie de dimensiunile lor si pozitia elementelor
- am luat acelasi caz pentru 90 si -270 de grade, la fel pentru -90 si 270
- daca unghiul e 0 sau 360, indiferent de semn, imaginea ajunge in pozitia
initiala, asa ca nu are rost sa efectuez operatia

Task 7: "CROP"

- aceasta operatie aduce copiile la dimensiunile selectiei
- copiile primesc elementele selectiei
- verific daca operatia se poate efectua operatia si afisez mesajele de eroare
corespunzatoare
- eliberez memoria copiilor si le aloc memorie pentru noile dimensiuni
- dupa ce adaug elemenetele selectiei in copii, eliberez memoria imaginii img,
deoarece aceasta are de fapt dimensiunile initiale, chiar daca doar selectia
se modifica
- elementele din afara selectiei sunt ignorate pana cand dimensiunile finale
devin cele ale selectiei
- actualizez noile capete ale selectiei si atribui copiilor dimensiunile
selectiei

Task 8: "APPLY"

- in functie de parametrii primiti, se aplica un filtru pe selectie
- am verificat daca operatia se poate efectua si am afisat mesajele de eroare
corespunzatoare
- am folosit un if pentru fiecare filtru ca sa verific daca pixelul pentru care
calculez noua valoare are destui vecini, iar daca nu are valoarea finala va fi
cea initiala
- pentru parametrul "BLUR" am luat doua foruri ca sa calculez noua valoare
pentru fiecare pixel, apoi alte doua foruri ca sa calculez suma valorilor
pixelilor din jurul pixelului principal, pe care apoi o impart la 9 si va
deveni noua valoare a pixelului principal, apoi adaug selectia in copie
- pe acelasi principiu am facut si "GAUSSIAN BLUR", "SHARPEN" si "EDGE", doar 
ca inainte de suma am inmultit fiecare element cu valoarea corespunzatoare din
kernel
- sumele pentru fiecare culoare a unui pixel le retin in 3 matrice ajutatoare
alocate dinamic, una pentru fiecare culoare

Task 9: "SAVE"

- verific daca este vreo imagine incarcata
- fac selectia totala a imaginii ca sa salvez imaginea totala
- salvez imaginea in functie de tipul ei (color sau in tonuri de gri) si in
functie de modul in care este ceruta savlarea prin comanda (ascii sau binar)
- deschid fisierul, apoi scriu caracteristicile imaginii in functie de cerinta
- scriu elementele matricei imaginii in functie de modul in care trebuie
salvata imaginea (cu fwrite daca e binar si fprintf daca e ascii)
- apoi am refacut selectia cu elementele si dimensiunile anterioare selctarii
totale

Task 10: "EXIT"

- eliberarea tuturor resurselor si iesirea din program
- verific daca a fost alocata vreo imagine inainte, daca nu dealoc doar
vectorii
carora le-am alocat memorie inainte de operatia de incarcare a unei imagini
in memorie
- altfel, dealoc toate resursele pe care le-am alocat anterior dinamic
- opresc bucla "while" de citire a comenzilor cu un break pentru a iesi din
program
