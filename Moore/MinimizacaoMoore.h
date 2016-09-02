#ifndef MINIMIZACAOMOORE_H
#define MINIMIZACAOMOORE_H

class MinimizacaoMoore {
    public:
        MinimizacaoMoore();
        virtual ~MinimizacaoMoore();
        void lerAlfabeto();
        void lerResposta();
        void lerGabarito();
        void unirDFA();
        void Minimizar();
        bool Resultado();
        void distinguirPalavra();
        void deletarTudo();
    protected:
    private:
        void imprime(int rodada);
        int letra (char c);
        //void editMatriz(int a, int b, char c);
        //char getCelula(char** D, int p, int q);
};

#endif // MINIMIZACAOMOORE_H
