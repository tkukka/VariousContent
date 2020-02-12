# IDE: Visual C++ Express Edition [2005, 2008]. Microsoft Visual C++ Compiler.

# C++ -kielen perusteet 
## Harjoitustyö
### Harjoitustyön 2007 - 2008 määrittely
Lukuvuoden 2007-2008 harjoitustyön aihe on **lyhin kuninkaan reitti shakkilaudalla**;
työn määrittely on [tässä dokumentissa](./Cpp_Harjoitustyo_2007_2008.pdf).

Alla olevassa listassa on tekstitiedostoja, joita voi käyttää testisyötteinä
harjoitustyöohjelmalle. Tiedoston jälkeen on kuvattu ohjelman odotettu tulostus. 
Huomaa, että ainoastaan tiedostoon tehtävä tulostus on kuvattu. 
Varmista, että komentorivi-ikkunan tulostus ja tiedostotulostus vastaavat toisiaan.

1. Tiedosto **err_file_empty.txt**
    on tyhjä ja siten virheellinen syöte.
    Odotettu tulostus tiedostoon:
    -2 -2
2. Tiedosto **err_file_char.txt**
    sisältää väärän merkin ja on siten virheellinen syöte.
    Odotettu tulostus tiedostoon:
    -2 -2
3. Tiedostossa **err_file_short.txt**
    laudan yksi rivi on lyhempi kuin muut. Tiedosto on siis virheellinen syöte.
    Odotettu tulostus tiedostoon:
    -2 -2
4. Tiedostossa **err_file_long.txt**
    laudan yksi rivi on pitempi kuin muut. Tiedosto on siis virheellinen syöte.
    Odotettu tulostus tiedostoon:
    -2 -2
5. Tiedoston **file_nopathsmall.txt**
    kuvaamalla laudalla ei ole etsittävää reittiä.
    Odotettu tulostus tiedostoon:
    -1 -1
6. Tiedoston **file_nopathbig.txt**
    kuvaamalla laudalla ei ole etsittävää reittiä.
    Odotettu tulostus tiedostoon:
    -1 -1
7. Tiedoston **file_path53.txt**
    kuvaamalta laudalta voidaan löytää haluttu reitti.
    Odotettu tulostus tiedostoon:
    0 0
    1 0
    2 0
    3 0
    4 1
    4 2
8. Tiedoston **file_path55.txt**
    kuvaamalta laudalta voidaan löytää haluttu reitti.
    Odotettu tulostus tiedostoon:
    0 0
    1 1
    2 2
    3 3
    4 4
9. Tiedoston **file_path63.txt**
    kuvaamalta laudalta voidaan löytää haluttu reitti.
    Odotettu tulostus tiedostoon:
    0 0
    0 1
    1 2
    2 2
    3 2
    4 2
    5 2
10. Tiedoston **file_path68.txt**
    kuvaamalta laudalta voidaan löytää haluttu reitti.
    Odotettu tulostus tiedostoon:
    0 0
    1 1
    2 0
    3 0
    4 1
    4 2
    5 3
    5 4
    5 5
    5 6
    5 7
11. Tiedoston **file_path86.txt**
    kuvaamalta laudalta voidaan löytää haluttu reitti.
    Odotettu tulostus tiedostoon:
    0 0
    1 1
    2 2
    3 3
    4 4
    5 3
    6 4
    7 5
12. Tiedoston **file_path88.txt**
    kuvaamalta laudalta voidaan löytää haluttu reitti.
    Odotettu tulostus tiedostoon:
    0 0
    0 1
    0 2
    0 3
    1 4
    2 5
    3 4
    4 3
    5 4
    5 5
    6 6
    7 7

