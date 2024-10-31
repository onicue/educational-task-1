class RealNumber {
  public:
    RealNumber(double value) : value(value) {}

    double operator ()(){
      int integerPart = static_cast<int>(value);
      return value - integerPart;
    }

    double operator [](int){
      return static_cast<int>(value);
    }
  private:
    double value;
};
