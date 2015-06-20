  template<class InputIt, class T, class BinaryOperation>
      T accumulate(InputIt first, InputIt last, T init, BinaryOperation op)
  {
      for (; first != last; ++first) {
          init = op(init, *first);
      }
      return init;
  }
