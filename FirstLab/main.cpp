#include "func.cpp"

#define A 0
#define B 7
#define EPS 0.1
#define X0 0

// TODO: 
// 1) Написать метод Пауэла
// 2) разобраться с шагом h 
// 3) Вручную вывести несколько итераций
// 4) Разобраться в смыслах методов  
// 5) Улучшить архитектуру кода

void showDirectMethodTable(int N) {
  std::cout << "-----------------------------------------\n";
  std::cout << "Прямой метод" << std::endl;
  std::cout << "-----------------------------------------\n";
  std::cout << std::setw(2) << "N" << " | " << std::setw(10) << "x_k"  << " | " << std::setw(10) << "f_xk" << std::endl;
  std::cout << "-----------------------------------------\n";
  double f_min = pow(10, 6);
  double x_min = pow(10, 6);
  for (int i = 3; i < N; i++) {
    if (directMethod(A, B, i).second < f_min) {
      f_min = directMethod(A, B, i).second;
      x_min = directMethod(A, B, i).first;
    }
    std::cout << std::setw(2) << i << " | " << std::setw(10) << directMethod(A, B, i).first << " | " << std::setw(10) << directMethod(A, B, i).second << std::endl;
  }
  std::cout << "Точка минимума: " << x_min << std::endl;
  std::cout << "Значение функции в этой точке = " << f_min << std::endl;

}

void showDerivativesUsingMethodTable() {
  std::cout << "-----------------------------------------\n";
  std::cout << "-----------------------------------------\n";
  std::cout << "Метод, основанный на использовании производных" << std::endl;
  std::cout << "-----------------------------------------\n";
  std::cout << std::setw(3) << "k" << " | " << std::setw(8) << "z_k" << " | " << std::setw(6) << "f_zk" << std::endl;
  std::cout << "-----------------------------------------\n";
  derivativesUsingMethod(A, B, EPS);
} 

int main(int argc, char **argv) {
  showDirectMethodTable(10);
  showDerivativesUsingMethodTable();
  return 0;
}