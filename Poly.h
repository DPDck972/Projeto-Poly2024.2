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

  //Operador atribui��o por copia;
  Poly &operator=(const Poly &P);
  //Operador atribui��o por movimento;
  Poly &operator=(Poly &&P) noexcept;
  //Getter de consulta de coeficiente usando o operador [];
  double operator[](int i) const;
  //Operador de igualdade;
  bool operator==(const Poly &P) const;
  //Operador de diferen�a;
  bool operator!=(const Poly &P) const;
  //Operador para substitui��o de x por valor real operator();
  double operator()(double x) const;
  //Operador de impress�o por sobrecarga do operator<<;
  friend std::ostream &operator<<(std::ostream &X,const Poly &P);
  //Operador de entrada de dados por sobrecarga do operator>>;
  friend std::istream& operator>>(std::istream& X, Poly &P);

  ///Metodos

  //Getter de consultar grau do polinomio;
  int getGrau() const;
  //Getter de consultar coeficiente de um elemento do polinomio;
  double getCoef(int i) const;
  //Setter de altera��o de valor de coeficiente;
  void setCoef(int i, double valor);
  //Altera��o do grau do polinomio;
  void recriar(int i);
  //Metodo de consulta se � vazio;
  bool empty() const;
  //Metodo de consulta se � nulo;
  bool isZero() const;
  //Metodo para substitui��o de x por valor real;
  double getValor(double x) const;
  //Metodo para salvar em um arquivo um polinomio;
  bool salvar(const std::string &name) const;
  //Metodo de leitura de um arquivo;
  bool ler(const std::string &name);

  ///Operadores Algebricos, sobrecargas;

  //Operador - unario, para multiplica��o do polinomio por -1;
  Poly operator-() const; //const para n�o modificar polinomio original!;
  //Operador + binario, para soma entre polinomios;
  Poly operator+(const Poly &P) const;
  //Operador - binario, para subtra��o entre polinomios;
  Poly operator-(const Poly &P) const;
  //Operador * binario, para multiplica��o entre polinomios;
  Poly operator*(const Poly &P) const;
};

#endif // _POLY_H_
