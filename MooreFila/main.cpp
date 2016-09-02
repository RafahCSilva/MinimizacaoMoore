#include <iostream>
#include "MinimizacaoMooreFila.h"
#include<ctime>

using namespace std;

int main() {

    MinimizacaoMooreFila M;

    M.lerAlfabeto(); // le o conj do alfabeto (o msm para ambos)

    M.lerGabarito(); // le primiero o gabarito

    M.lerResposta(); // le depois a resposta

    M.unirDFA(); // uni os dois DFA em uma unica delta"

    M.Minimizar();  // executa o algoritmo de Minimizacao de Moore otimizado com fila de pares

//    if( M.Resultado() ) {
//        cout << "1";
//    } else {
//        cout << "2"<<endl;
//        cout << M.distinguirPalavra();
//    }
    M.deletarTudo();
    return 0;
}
