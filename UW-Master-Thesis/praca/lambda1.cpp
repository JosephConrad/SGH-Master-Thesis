  int liczba = 0;
// błąd - lambda nie ma dostępu do zewnętrznych zmiennych
auto l1 = []() {return liczba;};
// zmienna liczba jest przechwytywana do lambdy przez kopiowanie
auto l2 = [liczba]() {return liczba;};
