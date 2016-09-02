#include "MinimizacaoMooreFila.h"
#include <iostream>
#include <queue>
#include <string>

using namespace std;

#define Mat(A, B) ( ((A) > (B)) ? M[(A)][(B)] : M[(B)][(A)] )

MinimizacaoMooreFila::MinimizacaoMooreFila() {
    //ctor
}

MinimizacaoMooreFila::~MinimizacaoMooreFila() {
    //dtor
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
int **M;

// entrutura para a FILA
struct MinimizacaoMooreFila::pares {
    int p;
    int q;
};
MinimizacaoMooreFila::pares* MinimizacaoMooreFila::novoPar(int p, int q) {
    pares *par = new MinimizacaoMooreFila::pares();
    par->p = p;
    par->q = q;
    return par;
}




// 1 - funcao para ler do STDIN o alfabeto
void MinimizacaoMooreFila::lerAlfabeto() {
    int i;
    cin >> numE;
    alfabeto = new char[numE];
    for (i = 0; i<numE; i++) {
        cin >> alfabeto[i];
    }
}

// 2 - funcao para ler do STDIN a 5-tupla do DFA gabarito
void MinimizacaoMooreFila::lerGabarito() {
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
void MinimizacaoMooreFila::lerResposta() {
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
void MinimizacaoMooreFila::unirDFA() {
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
void MinimizacaoMooreFila::Minimizar() {
    int p, q, w;
    // cria e inicializa a Matriz de pares com -1
    M = new int*[Qtotal];
    for(int i = 0; i < Qtotal; i++) {
        M[i] = new int[Qtotal];
        for(int j = 0; j < Qtotal; j++) {
            M[i][j] = -1; // vazio
        }
    }


    // preence de -2 os pares q de distingue em EPS
    for( p = 1; p<Qtotal; p++) {
        for( q = 0; q<p; q++) {
            if ( (F[p] + F[q]) == 1) {
                M[p][q] = -2;  // eps
            }
        }
    }

    // fila de pares para otimizacao
    queue<pares*> fila;
    // enfila os vazios
    for( p = 1; p<Qtotal; p++) {
        for( q = 0; q<p; q++) {
            if( M[p][q] == -1) { // eps
                fila.push(novoPar(p, q));
            }
        }
    }

    // par chave = sera o reinicio dos pares numa fila circular
    fila.push(novoPar(-1, -1));

int bench=0;
    // algoritmo de minimizacao de moore
    bool distinguiuRodada = false;
    bool distinguiuPar;
    do {
        pares *par = fila.front();
        fila.pop();
        p = par->p;
        q = par->q;

        if(p == -1 && q == -1) { //se eh par chave
            if(!distinguiuRodada) break; // se eh par chave e distinguiuRodada enta acaba o MinimizaMoore

            distinguiuRodada = false;
            fila.push(par);
        } else { // se eh par qlqr
            // aqui eh certeza q M[p][q]== -1
            distinguiuPar = false;
            for (w=0; w < numE; w++) {
  bench++;
                if (Mat(Delta[p][w], Delta[q][w]) != -1) {
                    M[p][q] = w;
                    distinguiuRodada = true;
                    distinguiuPar = true;
                    break;
                }
            }
            // se nao distinguiu este par, enfila novamente
            if (!distinguiuPar) fila.push(par);
        }
    } while (true);
cout<<bench;
}

// 6 - funcao q retorna se g_q0 e r_q0 sao indistinguiveis (M[][] == -1)
bool MinimizacaoMooreFila::Resultado() {
    if (M[r_q0 + g_numQ][g_q0] == -1) return true;
    return false;
}

// 7 - funcao q encontra palavra q distingue dos dois DFA
std::string MinimizacaoMooreFila::distinguirPalavra() {
    string palavra = "";
    int p, q, w;
    p = r_q0 + g_numQ; // q0 da resposta
    q = g_q0;          // q0 do gabarito
    w = Mat (p, q);
    while (w > -1) {
        palavra += alfabeto[w];
        p = Delta[p][w];
        q = Delta[q][w];
        w = Mat (p, q);
    }
    palavra += "#"; // vazio
    return palavra;
}

// 8 - Delete todas as variaveis alocadas
void MinimizacaoMooreFila::deletarTudo(){
    int i;

    delete alfabeto;

    for (i=0; i<g_numQ; i++){
        delete g_D[i];
    }
    delete g_D;

    for (i=0; i<r_numQ; i++){
        delete r_D[i];
    }
    delete r_D;

    delete g_F;
    delete r_F;

    for (i=0; i<g_numQ+r_numQ; i++){
        delete Delta[i];
    }
    delete Delta;

    delete F;

    for (i=0; i<g_numQ+r_numQ; i++){
        delete M[i];
    }
    delete M;

}
