int liczba = 0;
 
// błąd - lambda nie ma dostępu do zewnętrznych zmiennych
auto l1 = []() {return liczba;};
 
// zmienna liczba jest przechwytywana do lambdy przez kopiowanie
auto l2 = [liczba]() {return liczba;};
 
// zmienna liczba jest przechwytywana do lambdy przez referencję
auto l3 = [&liczba]() {return liczba;};
 
// jak l2, ale kompilator sam się domyśla jakie zmienne przechwycić (przez wartość)
auto l4 = [=]() {return liczba;};
 
// jak l3, ale kompilator sam się domyśla jakie zmienne przechwycić (przez referencję)
auto l5 = [&]() {return liczba;};
 
// inne kombinacje:
 
// przechwyć liczbę przez referencję, inne zmienne przez wartość
auto l7 = [=, &liczba]() {return liczba;};
 
// na odwrót
auto l8 = [&, liczba]() {return liczba;};
