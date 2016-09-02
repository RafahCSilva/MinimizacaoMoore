#include <iostream>
#include "MinimizacaoMoore.h"


using namespace std;

int main() {

    MinimizacaoMoore M;

//    cout<<"lerAlfabeto" << endl;
    M.lerAlfabeto(); // le o conj do alfabeto (o msm para ambos)
//    cout<<"lerGabarito" << endl;
    M.lerGabarito(); // le primiero o gabarito
//    cout<<"lerResposta" << endl;
    M.lerResposta(); // le depois a resposta
//    cout<<"inirDFA" << endl;
    M.unirDFA();    // uni os dois DFA em uma unica delta"

//    cout << endl<<endl<< "INICIO da MINIMIZACAO DE MOORE"<<endl<<endl;

    M.Minimizar();

//    cout << endl<<endl<< "Fim da MINIMIZACAO DE MOORE"<<endl<<endl;

//    if( M.Resultado() ) {
//        cout << "SAO EQUIVALENTES!!!";
//    } else {
//        cout << "NAO SAO EQUIVALENTES!!!"<<endl;
//        M.distinguirPalavra();
//        cout<<endl<<endl<<"FIIIM";
//    }
//    //M.deletarTudo();

    return 0;
}
//const clock_t begin_time = clock();
//cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC;
