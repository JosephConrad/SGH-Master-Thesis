map<const char,function<double(double,double)>> tab;
tab.insert(make_pair('+',[](double a,double b) {
    return a + b;
}));
cout << "3.5+4.5= " << tab['+'](3.5,4.5) << endl;
