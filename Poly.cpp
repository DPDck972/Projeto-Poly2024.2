#include <iostream> //Para entrada e saida de dados
#include <cmath> //Para x^i
#include <fstream> //Para gravação e leitura em arquivos
#include <string> //Para operar strings

#include "Poly.h"

using namespace std;

//Construtores

//Construtor default;
Poly::Poly(): grau(-1), coeficientes(nullptr){}
//Construtor especifico;
Poly::Poly(int i): grau(i), coeficientes(nullptr){
  //Caso o grau do polinomio seja inferior a 0, gerar o polinomio vazio;
  if(grau < 0){
    grau = -1;
  }
  //Caso o grau do polinomio seja exatamente 0, gerar o polinomio nulo;
  else if(grau == 0){
    coeficientes = new double[grau+1];
    coeficientes[grau] = 0.0;
  }
  else{
    //Caso o grau do polinomio seja maior que 0, gerar polinomio x^n;
    coeficientes = new double[grau+1];
    for(int i=0;i<grau;i++) coeficientes[i] = 0.0;
    coeficientes[grau] = 1.0;
  }
}
//Construtor por copia;
Poly::Poly(const Poly &P): grau(P.grau), coeficientes(nullptr){
  if(grau>=0) coeficientes = new double[grau+1];
  for(int i=0;i<grau+1;i++) coeficientes[i] = P.coeficientes[i];
}
//Construtor por movimento;
Poly::Poly(Poly &&P) noexcept: grau(P.grau), coeficientes(P.coeficientes){
  P.grau = -1;
  P.coeficientes = nullptr;
}

//Destrutor
Poly::~Poly(){
  delete[] coeficientes;
  grau = -1;
}
//Sobrecarga de operadores;

//Operador atribuição por copia;
Poly &Poly::operator=(const Poly &P){
  //Proteção de apagar area desejada
  if(this == &P) return *this; ///OTIMIZAR
  //Realocação de memoria em caso de grau diferente;
  if(this->grau != P.grau){
    this->recriar(P.getGrau());
    /*
    alternativo;
    delete[] coeficientes;
    grau = P.grau;
    if(grau>=0) coeficientes = new double[grau+1];
    else coeficientes = nullptr;
    */
  }
  //Copiar dados;
  for(int i=0;i<=grau;i++) coeficientes[i] = P.coeficientes[i];
  return *this;
}
//Operador atribuição por movimento;
Poly &Poly::operator=(Poly &&P) noexcept{
  delete[] coeficientes;
  grau = P.grau;
  coeficientes = P.coeficientes;
  P.grau = -1;
  P.coeficientes = nullptr;
  return *this;
}
//Metodo de consulta de  grau;
int Poly::getGrau() const{
  return grau;
}
//Metodo de consulta de coeficiente;
double Poly::getCoef(int i) const{
  if(i < 0 || i > this->grau) return 0.0;
  return coeficientes[i];
}
//Metodo de alteração de coeficiente;
void Poly::setCoef(int i, double valor){
  if(i < 0 || i > this->grau){
    cerr << "Indice invalido (i<0 ou i>grau)" << endl << endl;
  }
  else if(valor==0.0 && i==this->grau && this->grau>0){
    cerr << "Valor invalido: valor nulo para o coeficiente de maior grau em um polinomio nao nulo (valor==0.0 e i==grau e grau>0)." << endl << endl;
  }else{
    this->coeficientes[i] = valor;
  }
  return;
}
//Metodo de consulta de coeficientes por operador[];
double Poly::operator[](int i) const{
  return this->getCoef(i);
}
//Metodo de aumento de grau de polinomio;
void Poly::recriar(int i){
  if(this->getGrau() != i){
    *this = Poly(i);
  }
}
//Metodo de igualdade de polinomio usando o operador==;
bool Poly::operator==(const Poly &P) const{
  if(this->grau == P.grau){
    for(int i=0;i<=P.grau;i++){
      if(this->coeficientes[i] != P.coeficientes[i]) return false;
    }
    return true;
  }
  return false;
}
//Metodo de igualdade de polinomio usando o operador!=;
bool Poly::operator!=(const Poly &P) const{
  if(*this == P){
    return false;
  }
  return true;
}
//Metodo de consulta se o polinomio é vazio;
bool Poly::empty() const{
  Poly P; ///OTIMIZAR
  if(*this==P) return true;
  return false;
}
//Metodo de consulta se o polinomio é nulo;
bool Poly::isZero() const{
  Poly P(0); ///OTIMIZAR
  if(*this==P) return true;
  return false;
}
//Metodo de substituição de valor de x no polinimio;
double Poly::getValor(double x) const{
  //Teste se o polinimio é vazio;
  if(this->empty()) return 0.0;

  double valor(0.0);
  //Calculo de valor com substituição x = valor;
  for(int i=this->getGrau();i>=0;i--){
    valor += pow(x,i)*coeficientes[i];
  }
  ///Não entendo a diferença mas é diferente!;
  /*
  for(int i=0;i<=this->getGrau();i++){
    valor += pow(x,i)*coeficientes[i];
  }
  */
  return valor;
}
//Metodo de substituição de x pelo operador ();
double Poly::operator()(double x) const{
  return this->getValor(x);
}
//Metodo de sobrecarga de operador <<;
ostream &operator<<(ostream& X, const Poly &P){
  int g = P.getGrau(); //variavel com grau do polinomio para facilitar compreensão do codigo (inves de P.getGrau());
  //Teste para não impressão do polinomio vazio;
  if(P.empty()) return X;

  for(int i=g;i>=0;i--){
    //impressão do termo a[0]==0;
    if(P[i]==0.0){
      if(i==0 && g==0){
        X << 0.0; /// ou P[i] é redundante ?;
      }
    }
    // Imprime sinal do coeficiente;
    else{
      if(P[i]<0){
        X << '-';
      }
      else{
        if(i != g){
          X << '+';
        }
      }
      // Imprime módulo do coeficiente;
      if(abs(P[i]) != 1.0 || i==0){
        X << abs(P[i]);
      }
      // Imprime termo que depende de x
      if(i!=0){
        if(abs(P[i]) != 1.0){
          X << '*';
        }
        X << 'x';
        if(i>1){
          X << '^';
          X << i;
        }
      }
    }
  }
  return X;
}
//Metodo de sobrecarga de operador >>;
istream &operator>>(istream& X, Poly &P){
  if(P.empty()) return X;

  for(int i=P.getGrau();i>=0;i--){
    cout << "x^" << i << ": ";
    X >> P.coeficientes[i];
    while((P.coeficientes[i] == 0.0 && i==P.getGrau()) && P.getGrau() != 0){
      cout << "x^" << i << ": ";
      X >> P.coeficientes[i];
    }
  }

  return X;
}
//Metodo para salvar polinomio em arquivo;
bool Poly::salvar(const string &name) const{
  //Criação de um arquivo de nome name;
  ofstream arquivo(name);

  //Teste para verificação de o arquivo foi aberto (if true apenas se o arquivo não abrir);
  if(!arquivo.is_open()) return false;

  arquivo << "POLY" << " " << grau << endl;
  if(grau>=0){
    for(int i = 0; i<=grau; i++){
      arquivo << coeficientes[i] << " ";
    }
    arquivo << endl;
  }
  return true;
}
//Metodo de leitura de polinomio por arquivo;
bool Poly::ler(const string &name){
  //Abrindo um arquivo e testando se ele foi aberto;
  ifstream arquivo(name);
  if(!arquivo.is_open()) return false;

  //Ler e testar o cabeçalho;
  string cabecalho;
  arquivo >> cabecalho;
  if(!arquivo || cabecalho!="POLY") return false;

  //Ler e testar o grau;
  int poly_grau;
  arquivo >> poly_grau;
  //Caso arquivo não seja lido ou não exista parametro dentro de poly_grau(não é um numero inteiro);
  if(!arquivo || !(poly_grau < 0 || poly_grau >= 0)) return false; ///Questionar sobre como testar se o numero é valido;

  //Ler e testar coeficientes;
  Poly prov(poly_grau);

  for(int i=0;i<=poly_grau;i++){
    arquivo >> prov.coeficientes[i];
    //Teste se o arquivo foi lido corretamente, se o coeficiente do maior grau não é zero e se o numero é valido (intervalo infinito do reais);
    if(!arquivo || (prov.coeficientes[poly_grau]==0.0 && poly_grau!=0) || !(prov.coeficientes[i] < 0.0 || prov.coeficientes[i] >= 0.0) ) return false;
  }
  *this = move(prov);
  return true;
}

//Metodo de sobrecarga do operador - unario;
Poly Poly::operator-() const{
  //Teste se poly é vazia;
  if(this->empty()) return *this;

  int g = this->getGrau(); //Variavel com grau de this para melhor compreensão de codigo;

  Poly prov(g);
  for(int i = 0; i<=g; i++){
    prov.coeficientes[i] = -coeficientes[i];
  }
  return prov;
}
//Metodo de sobrecarga do operador + binario;
Poly Poly::operator+(const Poly &P) const{
  //Teste se algum polinomio é vazio;
  if(this->empty()) return P;
  if(P.empty()) return *this; ///Perguntar se redundancia;
  //Testes para evitar execução atoa;
  if(this->isZero()) return P;
  if(P.isZero()) return *this;

  int maior_grau = max(this->getGrau(),P.getGrau());
  Poly prov(maior_grau);

  //Soma de valores;
  for(int i = 0; i<=maior_grau; i++){
    prov.coeficientes[i] = this->getCoef(i) + P[i]; //Usando metodo getCoef;
  }
  //Teste se polinomio tem coeficiente do maior grau nulo;
  Poly aux(maior_grau); //objeto auxiliar
  while(prov.getGrau() > 0 && prov[maior_grau] == 0.0){
    maior_grau--;
    aux.recriar(maior_grau);
    //Copiar os dados de prov antes de recriar denovo;
    for(int i = 0; i <= maior_grau; i++){
      aux.coeficientes[i] = prov[i];
    }
    prov = aux;
  }
  return prov;
}
//Metodo de sobrecarga do operador - binario;
Poly Poly::operator-(const Poly &P) const{
  return this->operator+(-P);
}
//Metodo de sobrecarga do operador * binario;
Poly Poly::operator*(const Poly &P) const{
  //Teste com polinomios vazios e nulos;
  if(this->empty() || P.empty()) return Poly();
  if(this->isZero() || P.isZero()) return Poly(0);
  if(P.getGrau() == 0 && P.coeficientes[0] == 1) return *this;
  if(this->getGrau() == 0 && this->coeficientes[0] == 1) return P;

  Poly prov(this->getGrau() + P.getGrau());

  //Inicializando prov com todos os coeficientes em 0.0;
  for(int k = 0; k<=prov.getGrau(); k++) prov.coeficientes[k] = 0.0;

  for(int i = 0; i<=this->getGrau(); i++){
    for(int j = 0; j<=P.getGrau(); j++){
      //Atribuindo a multiplicação de a[i] e b[j] em prov;
      prov.coeficientes[i+j] += this->getCoef(i)*P[j];
    }
  }
  return prov;
}
