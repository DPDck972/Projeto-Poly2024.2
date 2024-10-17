#ifndef _POLY_H_
#define _POLY_H_

#include <iostream>
#include <string>

class Poly{
private:
  //Dados de cada objeto;
  int grau; // Grau do polinomio;
  double *coeficientes; //Coeficientes;
public:
  ///Construtores

  //Construtor default;
  Poly();
  //Construtor especifico;
  explicit Poly(int grau);
  //Construtor copia;
  Poly(const Poly &P);
  //Construtor movimento;
  Poly(Poly &&P) noexcept;


  ///Destrutor
  ~Poly();


  ///Sobrecarga de operadores

  //Operador atribuição por copia;
  Poly &operator=(const Poly &P);
  //Operador atribuição por movimento;
  Poly &operator=(Poly &&P) noexcept;
  //Getter de consulta de coeficiente usando o operador [];
  double operator[](int i) const;
  //Operador de igualdade;
  bool operator==(const Poly &P) const;
  //Operador de diferença;
  bool operator!=(const Poly &P) const;
  //Operador para substituição de x por valor real operator();
  double operator()(double x) const;
  //Operador de impressão por sobrecarga do operator<<;
  friend std::ostream &operator<<(std::ostream &X,const Poly &P);
  //Operador de entrada de dados por sobrecarga do operator>>;
  friend std::istream& operator>>(std::istream& X, Poly &P);

  ///Metodos

  //Getter de consultar grau do polinomio;
  int getGrau() const;
  //Getter de consultar coeficiente de um elemento do polinomio;
  double getCoef(int i) const;
  //Setter de alteração de valor de coeficiente;
  void setCoef(int i, double valor);
  //Alteração do grau do polinomio;
  void recriar(int i);
  //Metodo de consulta se é vazio;
  bool empty() const;
  //Metodo de consulta se é nulo;
  bool isZero() const;
  //Metodo para substituição de x por valor real;
  double getValor(double x) const;
  //Metodo para salvar em um arquivo um polinomio;
  bool salvar(const std::string &name) const;
  //Metodo de leitura de um arquivo;
  bool ler(const std::string &name);

  ///Operadores Algebricos, sobrecargas;

  //Operador - unario, para multiplicação do polinomio por -1;
  Poly operator-() const; //const para não modificar polinomio original!;
  //Operador + binario, para soma entre polinomios;
  Poly operator+(const Poly &P) const;
  //Operador - binario, para subtração entre polinomios;
  Poly operator-(const Poly &P) const;
  //Operador * binario, para multiplicação entre polinomios;
  Poly operator*(const Poly &P) const;
};

#endif // _POLY_H_
