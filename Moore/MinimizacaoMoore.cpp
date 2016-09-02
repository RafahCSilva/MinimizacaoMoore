#include "MinimizacaoMoore.h"
#include <iostream>
//#include <iomanip>
//#include <chrono>
//#include <ctime>
//#include <sys/time.h>

using namespace std;

#define Mat(A, B) ( ((A) > (B)) ? M[(A)][(B)] : M[(B)][(A)] )


MinimizacaoMoore::MinimizacaoMoore() {
    //ctor
}

MinimizacaoMoore::~MinimizacaoMoore() {
    //dtor // delete [] var
}

// numero de simbolos |E| (somente o INgabarito)
int numE;
char *alfabeto;


// numero de estado |Q|
int g_numQ, r_numQ;
//string* Qr, Qg; //< nao necessita os nomes dos estados

// delta: tabela de trasnsicao
int **g_D, **r_D;

// indice do q0
int g_q0, r_q0;

// estados de aceitacao
int g_numF, r_numF;
int *g_F, *r_F;


// variaveis globais da UNIAO

int Qtotal = 0;
// delta da uniao dos DFA gabarito e resposta
int **Delta;

// conjunto F da unia DFA
int *F;

// Matriz de pares de estados
char **M;



// 1 - funcao para ler do STDIN o alfabeto
void MinimizacaoMoore::lerAlfabeto() {
    int i;
    cin >> numE;
    alfabeto = new char[numE];
    for (i = 0; i<numE; i++) {
        cin >> alfabeto[i];
    }
}

// 2 - funcao para ler do STDIN a 5-tupla do DFA gabarito
void MinimizacaoMoore::lerGabarito() {
    int i, j;

    cin >> g_numQ;

    g_D = new int*[g_numQ];
    for (i = 0; i<g_numQ; i++) {
        g_D[i] = new int[numE];
        for (j = 0; j<numE; j++) {
            cin >> g_D[i][j];
        }
    }

    cin >> g_q0;

    cin >> g_numF;
    g_F = new int[g_numF];
    for (i = 0; i<g_numF; i++) {
        cin >> g_F[i];
    }
}

// 3 - funcao para ler do STDIN a 5-tupla do DFA resposta
void MinimizacaoMoore::lerResposta() {
    int i, j;

    cin >> r_numQ;

    r_D = new int*[r_numQ];
    for (i = 0; i<r_numQ; i++) {
        r_D[i] = new int[numE];
        for (j = 0; j<numE; j++) {
            cin >> r_D[i][j];
        }
    }

    cin >> r_q0;

    cin >> r_numF;
    r_F = new int[r_numF];
    for (i = 0; i<r_numF; i++) {
        cin >> r_F[i];
    }
}


// 4 - uni as duas tabelas de transicao delta em uma unica
void MinimizacaoMoore::unirDFA() {
    // matriz Delta de tamanho |Qtotal|*|Qtotal|
    Qtotal = g_numQ + r_numQ;
    Delta = new int*[Qtotal];

    // uni o delta gabarito
    for(int i = 0; i < g_numQ; i++) {
        Delta[i] = new int[numE];
        for(int j = 0; j < numE; j++) {
            Delta[i][j] = g_D[i][j];
        }
    }
    // uni o delta resposta
    for(int i = 0; i < r_numQ; i++) {
        Delta[i+g_numQ] = new int[numE];
        for(int j = 0; j < numE; j++) {
            Delta[i+g_numQ][j] = r_D[i][j]+g_numQ;
        }
    }

    // uni o conjunto F
    F = new int[Qtotal];
    for(int i = 0; i < Qtotal; i++) {
        F[i] = 0;
    }
    for(int i = 0; i < g_numF; i++) {
        F[g_F[i]] = 1;
    }
    for(int i = 0; i < r_numF; i++) {
        F[r_F[i]+g_numQ] = 1;
    }

}

// 5 - algoritimos de minimizacao de Moore
void MinimizacaoMoore::Minimizar() {
    int p, q, w;
    // cria e inicializa a Matriz de pares
    M = new char*[Qtotal];
    for(int i = 0; i < Qtotal; i++) {
        M[i] = new char[Qtotal];
        for(int j = 0; j < Qtotal; j++) {
            M[i][j] = '-';
        }
    }


    // preence de '#' os pares q de distingue em EPS
    for( p = 1; p<Qtotal; p++) {
        for( q = 0; q<p; q++) {
            if ( (F[p] + F[q]) == 1) {
                M[p][q] = '#';
            }
        }
    }
    //imprime o estado da matriz da rodada 0
//    int rod=0;
//    imprime(rod);

//    clock_t c_start = clock();
//    auto t_start = chrono::high_resolution_clock::now();
//cout << "clock()1:"<<clock();
////    int start = clock();// start

// timeval a;
//    timeval b;
//    gettimeofday(&a, 0);


int bench=0;
    // algoritmo de minimizacao de moore
    bool distinguiuAlgo = true;
    while (distinguiuAlgo) {
        distinguiuAlgo = false;
        for( p = 1; p<Qtotal; p++) {
            for( q = 0; q<p; q++) {
                if(M[p][q] == '-') {
                    for (w=0; w < numE; w++) { bench++;
                        if (Mat(Delta[p][w], Delta[q][w]) != '-') {
                            M[p][q] = alfabeto[w];
                            distinguiuAlgo = true;
                            break;
                        }
                    }
                } else {bench++;}
            }
        }
//        imprime(++rod);
    }


cout<< bench;


//gettimeofday(&b, 0);

//    std::cout << "difference: " << (b.tv_sec - a.tv_sec) << std::endl;

//cout <<"cont"<< cont<<"clock()2:"<<clock();

////    int tmili = (int)((clock()-start)*1000/CLOCKS_PER_SEC);// stop
////     cout << "TIMEEE:" << tmili;
//
//    clock_t c_end = clock();
//    auto t_end = chrono::high_resolution_clock::now();
//
//    cout << std::fixed << std::setprecision(2) << "CPU time used: "
////    cout << "CPU time used: "
//        << 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC << " ms\n"
//        << "Wall clock time passed: "
//        << std::chrono::duration<double, std::milli>(t_end-t_start).count()
//        << " ms\n";
}




void MinimizacaoMoore::imprime(int rodada) {
    int p, q;
    cout << endl << endl << "========= Rodada " << rodada << " =========" << endl;
    for( p = 1; p < Qtotal; p++) {
        cout << p << "  ";
        for( q = 0; q < p; q++) {
            cout << M[p][q] << "\t";
        }
        cout << endl;
    }
    cout << "   ";
    for( q = 0; q < Qtotal-1; q++) {
        cout << q << "\t";
    }
}

// 6 - funcao q retorna se g_q0 e r_q0 sao indistinguiveis
bool MinimizacaoMoore::Resultado() {   //cout << g_q0 << "_" << r_q0 + g_numQ;
    //cout << "=" << M[g_q0][r_q0 + g_numQ] << "=" << Mat(g_q0 , r_q0 + g_numQ);
    if (M[r_q0 + g_numQ][g_q0] == '-') return true;
    return false;
}

// 7 - funcao q encontra palavra q distingue dos dois DFA
void MinimizacaoMoore::distinguirPalavra() {
    string palavra = "";
    int p, q, w;
    p = r_q0 + g_numQ; // q0 da resposta
    q = g_q0;          // q0 do gabarito
    char c = Mat (p, q);
    while (c != '#') {
        palavra += + c;
        w = letra(c);
        p = Delta[p][w];
        q = Delta[q][w];
        c = Mat (p, q);
    }
    palavra += "#"; // vazio
    cout << "O DFAs distinguem na seguinte palavra: " << palavra;
}


int MinimizacaoMoore::letra (char c) {
    int i;
    for (i=0; i<numE; i++) {
        if (alfabeto[i]==c)return i;
    }
    return -1;
}


/*void MinimizacaoMoore::editMatriz(int a, int b, char c) {
    if(a>b) {
        M[a][b]=c;
    } else {
        M[b][a]=c;
    }
}
//if (p==5 && q==0 )cout <<"____" << Delta[p][w] << ":" << Delta[q][w] <<"____"<< endl;
*/


//const clock_t startTime = clock();
//cout << "\n\n\nTIME:" << double( clock() - startTime ) / (double)CLOCKS_PER_SEC/1000<< " seconds." << endl;

