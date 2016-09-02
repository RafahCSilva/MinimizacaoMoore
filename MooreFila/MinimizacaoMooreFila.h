#ifndef MINIMIZACAOMOOREFILA_H
#define MINIMIZACAOMOOREFILA_H
#include <string>

class MinimizacaoMooreFila
{
    public:
        MinimizacaoMooreFila();
        virtual ~MinimizacaoMooreFila();
        void lerAlfabeto();
        void lerResposta();
        void lerGabarito();
        void unirDFA();
        void Minimizar();
        bool Resultado();
        std::string distinguirPalavra();
        void deletarTudo();
    protected:
    private:
        struct pares;
        pares* novoPar(int p, int q);
};

#endif // MINIMIZACAOMOOREFILA_H
