#include "func.cpp"

void showDirectMethodTable(int N) {
  std::cout << "-----------------------------------------\n";
  std::cout << "Прямой метод" << std::endl;
  std::cout << "-----------------------------------------\n";
  std::cout << std::setw(2) << "N" << " | " << std::setw(10) << "x_k" << std::endl;
  std::cout << "-----------------------------------------\n";
  for (int i = 3; i < N; i++) {
    std::cout << std::setw(2) << i << " | " << std::setw(10) << directMethod(a, b, i) << std::endl;
  }
}

void showDerivativesUsingMethodTable() {
  std::cout << "-----------------------------------------\n";
  std::cout << "-----------------------------------------\n";
  std::cout << "Метод, основанный на использовании производных" << std::endl;
  std::cout << "-----------------------------------------\n";
  std::cout << std::setw(3) << "k" << " | " << std::setw(8) << "z_k" << " | " << std::setw(6) << "f_zk" << std::endl;
  std::cout << "-----------------------------------------\n";
  derivativesUsingMethod(a, b);
} 

int main(int argc, char **argv) {
  showDirectMethodTable(10);
  showDerivativesUsingMethodTable();
  return 0;
}