#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

class PreProcess{
    public:
    static void pre(const std::string &file,int argc);
    static std::string comentarios(std::string &s);
    static std::vector<std::string> token(const std::string &s,std::vector<std::string> &vetor);
    static std::vector<std::string> lowervetor(std::vector<std::string> &vetor);
    static bool compstring(std::string &a,std::string &b);
    static void TabInstDirect(std::vector<std::string> &inst,std::vector<std::string> &direc);
    static std::vector<std::string> arrumalinha(std::vector<std::string> &frase,std::string &ajuda);
    static int convertnumero(std::string &s);
    static int errolexico(int linha,std::vector<std::string> &frase);
    static int errosintatico(int linha,int label,std::vector<std::string> &frase, std::vector<std::string> Instrucao , std::vector<std::string> Diretivas,std::string &ajuda);
    static bool digito(std::string &frase);
    static bool digitohex(std::string &frase);
    static void errosemantico(std::vector<int> &errosem,const int *secao,std::vector<int> &SimbolsValid,std::vector<int> &rotulolinha,std::vector<int> &Objeto,std::vector<int> &pulo,std::vector<int> &constante,std::vector<int> &divisao,std::vector<int> &memoria,int argc);
    static void secaoerrada(const int *secao,int linhacod,std::vector<int> &errosem);
};

void PreProcess::pre(const std::string &file,int argc){
    std::vector<std::string> Instrucoes;
    std::vector<std::string> Diretivas;
    std::vector<std::string> Simbols;
    std::vector<std::string> frase;
    std::vector<int> SimbolsValor;
    int begin = 0,end = 0,linha = 0;
    int secao[2];
    secao[0] = 0;
    std::vector<std::string> data;
    std::vector<std::string> sdata;
    std::string ajuda;
    PreProcess::TabInstDirect(Instrucoes,Diretivas);
    std::ifstream entrada(strdup((file+".asm").c_str()));
    std::ofstream pre(strdup((file+".pre").c_str()));

    if (!entrada || !pre) {
        std::cout << "Erro ao abrir arquivos\n";
    }
    while(getline(entrada,ajuda)) {
        frase.clear();
        frase = PreProcess::arrumalinha(frase, ajuda);
        linha++;
        if (frase.empty()) {//if pra linha VAZIA
            continue;
        }
        if(frase[0] == Diretivas[0]){
            if(frase[1] == "text"){
                secao[0] = linha;
            }
            if(frase[1] == "data") {
                secao[1] = linha;
                if (secao[0] == 0) {
                    auto g = 0;
                    ajuda.clear();
                    for (auto &i : frase) {//for pra lista
                        if (g != frase.size() - 1) {
                            ajuda += i;
                            ajuda += ' ';
                        } else {
                            ajuda += i;
                            ajuda += '\n';
                        }
                        g++;
                    }
                    data.push_back(ajuda);
                    do {
                        getline(entrada, ajuda);
                        linha++;
                        frase.clear();
                        frase = PreProcess::arrumalinha(frase, ajuda);
                        auto g = 0;
                        ajuda.clear();
                        for (auto &i : frase) {//for pra lista
                            if (g != frase.size() - 1) {
                                ajuda += i;
                                ajuda += ' ';
                            } else {
                                ajuda += i;
                                ajuda += '\n';
                            }
                            g++;
                        }
                        data.push_back(ajuda);
                    } while (frase[0] != Diretivas[0]);
                    if(frase[1] == "text"){
                        secao[0] = linha;
                    }
                }
            }
        }
        if (frase.size() == 1 && ((frase[0]).find(':')) != frase[0].npos) {//if pra linha COM APENAS LABEL
            getline(entrada, ajuda);//fazer depois caso tiver simbolo: e na outra linha tiver nada
            frase = PreProcess::arrumalinha(frase, ajuda);
        }
        if (argc == 3) {
            if (frase.size() == 1) {
                if (frase[0] == Diretivas[3]) {
                    begin++;
                    if (begin > 1) {
                        std::cout << "ERRO(MAIS DE 1 BEGIN)!" << std::endl;
                    }
                }
                if(frase[0] == Diretivas[4]){
                    end++;
                    if(end > 1){
                        std::cout << "ERRO!(MAIS DE 1 END)" << std::endl;
                    }
                }
            }
            if(frase.size() == 2){
                if (frase[1] == Diretivas[3]) {
                    begin++;
                    if (begin > 1) {
                        std::cout << "ERRO(MAIS DE 1 BEGIN)!" << std::endl;
                    }
                }
                if(frase[1] == Diretivas[4]){
                    end++;
                    if(end > 1){
                        std::cout << "ERRO!(MAIS DE 1 END)" << std::endl;
                    }
                }
            }
        }
        if(((frase.size() == 1 && (frase[0] == Diretivas[3])) || (frase.size() == 2 && (frase[1] == Diretivas[3]))) && argc == 2){
            std::cout << "ERRO!(BEGIN EM UM PROGRAMA COM 1 ARQUIVO DE ENTRADA)" << std::endl;
        }
        if(((frase.size() == 1 && (frase[0] == Diretivas[4])) || (frase.size() == 2 && (frase[1] == Diretivas[4]))) && argc == 2){
            std::cout << "ERRO!(END EM UM PROGRAMA COM 1 ARQUIVO DE ENTRADA)" << std::endl;
        }
        auto f = 0;
        ajuda.clear();
        for(auto & i : frase){//for pra lista
            if(f != frase.size()-1){
                ajuda += i;
                ajuda += ' ';
            }else{
                ajuda += i;
                ajuda += '\n';
            }
            f++;
        }
        pre << ajuda;
    }
    auto h = 0;
    if(secao[1] < secao[0]){
        for(auto & i : data) {
            if(h != data.size()-1) {
                pre << i;
            }
            h++;
        }
    }
    if(argc == 3 && (begin != 1 || end != 1)){
        std::cout << "ERRO!(FALTA OU BEGIN OU END OU OS DOIS EM UM PROGRAMA COM 2 ARQUIVOS DE ENTRADA)" << std::endl;
    }

    entrada.close();
    pre.close();
}

void PreProcess::TabInstDirect(std::vector<std::string> &inst,std::vector<std::string> &direc){
    std::string a = "add";
    inst.push_back(a);
    a = "sub";
    inst.push_back(a);
    a = "mult";
    inst.push_back(a);
    a = "div";
    inst.push_back(a);
    a = "jmp";
    inst.push_back(a);
    a = "jmpn";
    inst.push_back(a);
    a = "jmpp";
    inst.push_back(a);
    a = "jmpz";
    inst.push_back(a);
    a = "copy";
    inst.push_back(a);
    a = "load";
    inst.push_back(a);
    a = "store";
    inst.push_back(a);
    a = "input";
    inst.push_back(a);
    a = "output";
    inst.push_back(a);
    a = "stop";
    inst.push_back(a);

    a = "section";
    direc.push_back(a);
    a = "space";
    direc.push_back(a);
    a = "const";
    direc.push_back(a);
    a = "begin";
    direc.push_back(a);
    a = "end";
    direc.push_back(a);
    a = "public";
    direc.push_back(a);
    a = "extern";
    direc.push_back(a);
}

std::vector<std::string> PreProcess::token(const std::string &s,std::vector<std::string> &vetor){
    char *copia = strdup(s.c_str());
    char *tokens = strtok(copia," \t;");

    while(tokens != nullptr){// colocar na lista strings do strtok
        vetor.emplace_back(tokens);
        tokens = strtok(nullptr," \t;");
    }
    return vetor;
}
std::vector<std::string> PreProcess::lowervetor(std::vector<std::string> &vetor){
    int j,cont = 0;
    for(auto i : vetor){//for pra lista
        for(j = 0;(unsigned)j < (i).size(); j++){
            i[j] = tolower(i[j]);
        }
        vetor[cont] = i;
        cont++;
    }
    return vetor;
}

std::string PreProcess::comentarios(std::string &s){
    size_t pos = s.find(';');

	if (pos != std::string::npos) {
		s = s.substr(0, pos);
	}
	return s;
}

bool PreProcess::compstring(std::string &a,std::string &b){
    return a == b;
}

std::vector<std::string> PreProcess::arrumalinha(std::vector<std::string> &frase,std::string &ajuda){
    ajuda = PreProcess::comentarios(ajuda);
    frase = PreProcess::token(ajuda,frase);
    frase = PreProcess::lowervetor(frase);
    return frase;
}

int PreProcess::convertnumero(std::string &s){
    int numero;
    std::stringstream ajuda;

    if(s.find("0x") != std::string::npos){
        if(s.find('-') != std::string::npos){
            s= s.replace(1,2,"");
        }else{
            s = s.replace(0, 2, "");
        }
        ajuda << std::hex << s;
        ajuda >> numero;
        return numero;
    }

    if(!(std::istringstream(s) >> numero)){
        numero = 0;
    }
    return numero;
}

int PreProcess::errolexico(int linha,std::vector<std::string> &frase){
    std::string aux;
    int i,lex = 0;

    aux = frase[0].substr(0,frase[0].find(':'));
    if(aux.size() > 50){
        lex = 1;
    }
    if(aux[0] >= '0' && aux[0] <= '9'){
        lex = 1;
    }
    for(i = 0; (unsigned)i != aux.size(); i++){
        if((aux[i] < '0' || aux[i] > '9') && (aux[i] < 'a' || aux[i] > 'z') && aux[i] != '_'){
            lex = 1;
        }
    }
    if(lex == 1){
        std::cout << "Erro Lexico : Linha " << linha << "." << std::endl;
    }

return lex;
}

int PreProcess::errosintatico(int linha,int label,std::vector<std::string> &frase, std::vector<std::string> Instrucao , std::vector<std::string> Diretivas,std::string &ajuda){
    int sint = 0;

    if(!(PreProcess::compstring(frase[label],Instrucao[0]) || PreProcess::compstring(frase[label],Instrucao[1]) || PreProcess::compstring(frase[label],Instrucao[2]) || PreProcess::compstring(frase[label],Instrucao[3]) || PreProcess::compstring(frase[label],Instrucao[4]) || PreProcess::compstring(frase[label],Instrucao[5]) || PreProcess::compstring(frase[label],Instrucao[6]) || PreProcess::compstring(frase[label],Instrucao[7]) || PreProcess::compstring(frase[label],Instrucao[8])|| PreProcess::compstring(frase[label],Instrucao[9]) || PreProcess::compstring(frase[label],Instrucao[10]) || PreProcess::compstring(frase[label],Instrucao[11]) || PreProcess::compstring(frase[label],Instrucao[12])|| PreProcess::compstring(frase[label],Instrucao[13]) || PreProcess::compstring(frase[label],Diretivas[0]) || PreProcess::compstring(frase[label],Diretivas[1]) || PreProcess::compstring(frase[label],Diretivas[2]) || PreProcess::compstring(frase[label],Diretivas[3]) || PreProcess::compstring(frase[label],Diretivas[4]) || PreProcess::compstring(frase[label],Diretivas[5]) || PreProcess::compstring(frase[label],Diretivas[6]))){
        sint = 1;
    }
    if(PreProcess::compstring(frase[label],Instrucao[0]) || PreProcess::compstring(frase[label],Instrucao[1]) || PreProcess::compstring(frase[label],Instrucao[2]) || PreProcess::compstring(frase[label],Instrucao[3]) || PreProcess::compstring(frase[label],Instrucao[4]) || PreProcess::compstring(frase[label],Instrucao[5]) || PreProcess::compstring(frase[label],Instrucao[6]) || PreProcess::compstring(frase[label],Instrucao[7]) || PreProcess::compstring(frase[label],Instrucao[9]) || PreProcess::compstring(frase[label],Instrucao[10]) || PreProcess::compstring(frase[label],Instrucao[11]) || PreProcess::compstring(frase[label],Instrucao[12]) ){
        frase.clear();
        char *copia = strdup(ajuda.c_str());
        char *tokens = strtok(copia,"+ ");
        while(tokens != nullptr){
            frase.emplace_back(tokens);
            tokens = strtok(nullptr,"+ ");
        }
        if(frase.size() < (unsigned) (label + 2)){
            sint = 1;
        }
        if(frase.size() == (unsigned) (label + 2)){
            if((((frase.back()).find(',')) != std::string::npos) || (PreProcess::compstring(frase[label+1],Instrucao[0]) || PreProcess::compstring(frase[label+1],Instrucao[1]) || PreProcess::compstring(frase[label+1],Instrucao[2]) || PreProcess::compstring(frase[label+1],Instrucao[3]) || PreProcess::compstring(frase[label+1],Instrucao[4]) || PreProcess::compstring(frase[label+1],Instrucao[5]) || PreProcess::compstring(frase[label+1],Instrucao[6]) || PreProcess::compstring(frase[label+1],Instrucao[7]) || PreProcess::compstring(frase[label+1],Instrucao[8])|| PreProcess::compstring(frase[label+1],Instrucao[9]) || PreProcess::compstring(frase[label+1],Instrucao[10]) || PreProcess::compstring(frase[label+1],Instrucao[11]) || PreProcess::compstring(frase[label+1],Instrucao[12])|| PreProcess::compstring(frase[label+1],Instrucao[13]) || PreProcess::compstring(frase[label+1],Diretivas[0]) || PreProcess::compstring(frase[label+1],Diretivas[1]) || PreProcess::compstring(frase[label+1],Diretivas[2]))){
                sint = 1;
            }
        }
        if(frase.size() > (unsigned) (label + 2)){
            if(!(PreProcess::digito(frase[label + 2])) || frase.size() > (unsigned) label + 3){
                sint = 1;
            }
        }
    }
    if(PreProcess::compstring(frase[label],Instrucao[13])){
        if(frase.size() == (unsigned) (label + 1)){
            if((((frase.back()).find(',')) != std::string::npos) || (PreProcess::compstring(frase[label],Instrucao[0]) || PreProcess::compstring(frase[label],Instrucao[1]) || PreProcess::compstring(frase[label],Instrucao[2]) || PreProcess::compstring(frase[label],Instrucao[3]) || PreProcess::compstring(frase[label],Instrucao[4]) || PreProcess::compstring(frase[label],Instrucao[5]) || PreProcess::compstring(frase[label],Instrucao[6]) || PreProcess::compstring(frase[label],Instrucao[7]) || PreProcess::compstring(frase[label],Instrucao[8])|| PreProcess::compstring(frase[label],Instrucao[9]) || PreProcess::compstring(frase[label],Instrucao[10]) || PreProcess::compstring(frase[label],Instrucao[11]) || PreProcess::compstring(frase[label],Instrucao[12]) || PreProcess::compstring(frase[label],Diretivas[0]) || PreProcess::compstring(frase[label],Diretivas[1]) || PreProcess::compstring(frase[label],Diretivas[2]))){
                sint = 1;
            }
        }
        if(frase.size() > (unsigned) (label +1)){
                sint = 1;
            }
    }
    if(PreProcess::compstring(frase[label],Instrucao[8])){
        if(frase.size() < (unsigned) (label + 2)){
            sint = 1;
        }
        frase.clear();
        char *copia = strdup(ajuda.c_str());
        char *tokens = strtok(copia,", +");
        while(tokens != nullptr){
            frase.emplace_back(tokens);
            tokens = strtok(nullptr,", +");
        }
        if(frase.size() < (unsigned)(label + 3) || frase.size() > (unsigned)(label + 5)){
            sint = 1;
        }
        if((PreProcess::compstring(frase[label+1],Instrucao[0]) || PreProcess::compstring(frase[label+1],Instrucao[1]) || PreProcess::compstring(frase[label+1],Instrucao[2]) || PreProcess::compstring(frase[label+1],Instrucao[3]) || PreProcess::compstring(frase[label+1],Instrucao[4]) || PreProcess::compstring(frase[label+1],Instrucao[5]) || PreProcess::compstring(frase[label+1],Instrucao[6]) || PreProcess::compstring(frase[label+1],Instrucao[7]) || PreProcess::compstring(frase[label+1],Instrucao[8])|| PreProcess::compstring(frase[label+1],Instrucao[9]) || PreProcess::compstring(frase[label+1],Instrucao[10]) || PreProcess::compstring(frase[label+1],Instrucao[11]) || PreProcess::compstring(frase[label+1],Instrucao[12])|| PreProcess::compstring(frase[label+1],Instrucao[13]) || PreProcess::compstring(frase[label+1],Diretivas[0]) || PreProcess::compstring(frase[label+1],Diretivas[1]) || PreProcess::compstring(frase[label+1],Diretivas[2]))){
            sint = 1;
        }
        if(frase.size() == (unsigned)(label + 3)){
            if((PreProcess::compstring(frase[label+2],Instrucao[0]) || PreProcess::compstring(frase[label+2],Instrucao[1]) || PreProcess::compstring(frase[label+2],Instrucao[2]) || PreProcess::compstring(frase[label+2],Instrucao[3]) || PreProcess::compstring(frase[label+2],Instrucao[4]) || PreProcess::compstring(frase[label+2],Instrucao[5]) || PreProcess::compstring(frase[label+2],Instrucao[6]) || PreProcess::compstring(frase[label+2],Instrucao[7]) || PreProcess::compstring(frase[label+2],Instrucao[8])|| PreProcess::compstring(frase[label+2],Instrucao[9]) || PreProcess::compstring(frase[label+2],Instrucao[10]) || PreProcess::compstring(frase[label+2],Instrucao[11]) || PreProcess::compstring(frase[label+2],Instrucao[12])|| PreProcess::compstring(frase[label+2],Instrucao[13]) || PreProcess::compstring(frase[label+2],Diretivas[0]) || PreProcess::compstring(frase[label+2],Diretivas[1]) || PreProcess::compstring(frase[label+2],Diretivas[2]))){
                sint = 1;
            }
        }
        if(frase.size() == (unsigned)(label + 4)){
            if(PreProcess::compstring(frase[label+1],Instrucao[0]) || PreProcess::compstring(frase[label+1],Instrucao[1]) || PreProcess::compstring(frase[label+1],Instrucao[2]) || PreProcess::compstring(frase[label+1],Instrucao[3]) || PreProcess::compstring(frase[label+1],Instrucao[4]) || PreProcess::compstring(frase[label+1],Instrucao[5]) || PreProcess::compstring(frase[label+1],Instrucao[6]) || PreProcess::compstring(frase[label+1],Instrucao[7]) || PreProcess::compstring(frase[label+1],Instrucao[8])|| PreProcess::compstring(frase[label+1],Instrucao[9]) || PreProcess::compstring(frase[label+1],Instrucao[10]) || PreProcess::compstring(frase[label+1],Instrucao[11]) || PreProcess::compstring(frase[label+1],Instrucao[12])|| PreProcess::compstring(frase[label+1],Instrucao[13]) || PreProcess::compstring(frase[label+1],Diretivas[0]) || PreProcess::compstring(frase[label+1],Diretivas[1]) || PreProcess::compstring(frase[label+1],Diretivas[2])){
                sint = 1;
            }

            if(PreProcess::digito(frase[label + 2])){
                if(PreProcess::compstring(frase[label+3],Instrucao[0]) || PreProcess::compstring(frase[label+3],Instrucao[1]) || PreProcess::compstring(frase[label+3],Instrucao[2]) || PreProcess::compstring(frase[label+3],Instrucao[3]) || PreProcess::compstring(frase[label+3],Instrucao[4]) || PreProcess::compstring(frase[label+3],Instrucao[5]) || PreProcess::compstring(frase[label+3],Instrucao[6]) || PreProcess::compstring(frase[label+3],Instrucao[7]) || PreProcess::compstring(frase[label+3],Instrucao[8])|| PreProcess::compstring(frase[label+3],Instrucao[9]) || PreProcess::compstring(frase[label+3],Instrucao[10]) || PreProcess::compstring(frase[label+3],Instrucao[11]) || PreProcess::compstring(frase[label+3],Instrucao[12])|| PreProcess::compstring(frase[label+3],Instrucao[13]) || PreProcess::compstring(frase[label+3],Diretivas[0]) || PreProcess::compstring(frase[label+3],Diretivas[1]) || PreProcess::compstring(frase[label+3],Diretivas[2])){
                    sint = 1;
                }
            }

            if(PreProcess::digito(frase[label + 3])){
                if(PreProcess::compstring(frase[label+2],Instrucao[0]) || PreProcess::compstring(frase[label+2],Instrucao[1]) || PreProcess::compstring(frase[label+2],Instrucao[2]) || PreProcess::compstring(frase[label+2],Instrucao[3]) || PreProcess::compstring(frase[label+2],Instrucao[4]) || PreProcess::compstring(frase[label+2],Instrucao[5]) || PreProcess::compstring(frase[label+2],Instrucao[6]) || PreProcess::compstring(frase[label+2],Instrucao[7]) || PreProcess::compstring(frase[label+2],Instrucao[8])|| PreProcess::compstring(frase[label+2],Instrucao[9]) || PreProcess::compstring(frase[label+2],Instrucao[10]) || PreProcess::compstring(frase[label+2],Instrucao[11]) || PreProcess::compstring(frase[label+2],Instrucao[12])|| PreProcess::compstring(frase[label+2],Instrucao[13]) || PreProcess::compstring(frase[label+2],Diretivas[0]) || PreProcess::compstring(frase[label+2],Diretivas[1]) || PreProcess::compstring(frase[label+2],Diretivas[2])){
                    sint = 1;
                }
            }
            if(!(PreProcess::digito(frase[label + 2])) && !(PreProcess::digito(frase[label + 3]))){
                sint = 1;
            }

        }
         if(frase.size() == (unsigned)(label + 5)){
            if((PreProcess::compstring(frase[label+3],Instrucao[0]) || PreProcess::compstring(frase[label+3],Instrucao[1]) || PreProcess::compstring(frase[label+3],Instrucao[2]) || PreProcess::compstring(frase[label+3],Instrucao[3]) || PreProcess::compstring(frase[label+3],Instrucao[4]) || PreProcess::compstring(frase[label+3],Instrucao[5]) || PreProcess::compstring(frase[label+3],Instrucao[6]) || PreProcess::compstring(frase[label+3],Instrucao[7]) || PreProcess::compstring(frase[label+3],Instrucao[8])|| PreProcess::compstring(frase[label+3],Instrucao[9]) || PreProcess::compstring(frase[label+3],Instrucao[10]) || PreProcess::compstring(frase[label+3],Instrucao[11]) || PreProcess::compstring(frase[label+3],Instrucao[12])|| PreProcess::compstring(frase[label+3],Instrucao[13]) || PreProcess::compstring(frase[label+3],Diretivas[0]) || PreProcess::compstring(frase[label+3],Diretivas[1]) || PreProcess::compstring(frase[label+3],Diretivas[2]))){
                sint = 1;
            }
            if(!(PreProcess::digito(frase[label + 2]))){
                sint = 1;
            }
            if(!(PreProcess::digito(frase[label + 4]))){
                sint = 1;
            }
        }
    }
    if(PreProcess::compstring(frase[label],Diretivas[0])){
        if(label == 1){
            sint = 1;
        }
        if(frase.size() < (unsigned) (label + 2)){
            sint = 1;
        }
        if(frase.size() == (unsigned) (label + 2)){
            if(frase[label + 1] != "text" && frase[label + 1] != "data"){
                sint = 1;
            }
        }
        if(frase.size() > (unsigned) (label +2)){
            sint = 1;
        }
    }
    if(PreProcess::compstring(frase[label],Diretivas[1])){
        if(label == 0){
            sint = 1;
        }
        if(frase.size() == (unsigned) (label + 2)){
            if(!(PreProcess::convertnumero(frase[label + 1]))){
                sint = 1;
            }
        }
        if(frase.size() > (unsigned) (label + 2)){
            sint = 1;
        }
    }
    if(PreProcess::compstring(frase[label],Diretivas[2])){
        if(label == 0){
            sint = 1;
        }
        if(frase.size() < (unsigned) (label + 2)){
            sint = 1;
        }
        if(frase.size() == (unsigned) (label + 2)){
            if(!(PreProcess::digito(frase[label + 1])) && !(PreProcess::digitohex(frase[label+1]))){
                sint = 1;
            }
        }
        if(frase.size() > (unsigned) (label + 2)){
            sint = 1;
        }
    }

    int doispontos = 0;
    std::size_t found = ajuda.find_first_of(':');
    while (found!=std::string::npos){
        doispontos++;
        found=ajuda.find_first_of(':',found+1);
    }
    if(doispontos > 1){
        sint = 1;
    }
    if(sint == 1){
        std::cout << "Erro Sintatico : Linha " << linha << "." << std::endl;
    }
return sint;
}

bool PreProcess::digito(std::string &frase){
    if(frase[0] == '-'){
        for(int j = 1;(unsigned)j < frase.size(); j++){
            if(!(isdigit(frase[j]))){
                return false;
            }
        }
    }else{
        for(int j = 0;(unsigned)j < frase.size(); j++){
            if(!(isdigit(frase[j]))){
                return false;
            }
        }
    }
    return true;
}

void PreProcess::errosemantico(std::vector<int> &errosem,const int *secao,std::vector<int> &SimbolsValid,std::vector<int> &rotulolinha,std::vector<int> &Objeto,std::vector<int> &pulo,std::vector<int> &constante,std::vector<int> &divisao,std::vector<int> &memoria,int argc){
    for(auto i : errosem){//for pra lista
        std::cout <<"1Erro Semantico : Linha " <<(i) << std::endl;
    }
    if(argc == 2){
        for (auto i = SimbolsValid.begin(); i != SimbolsValid.end(); ++i) {//for pra lista
            if ((*i) == 0 || (*i) == 2) {
                std::cout << "2Erro Semantico : Linha " << rotulolinha[i - SimbolsValid.begin()] << std::endl;
            }
        }
    }
    int j = 0;
    for(auto i = pulo.begin(); i != pulo.end(); ++i){//for pra lista
        if(secao[2] > secao[3]){
            if(Objeto[(*i) - 1] < secao[2] && j%2 == 0){
                std::cout <<"3Erro Semantico : Linha " <<  *(i + 1)  <<" "<< secao[2] <<" "<< secao[3]  <<" "<< Objeto[(*i)-1] <<" "<< std::endl;
            }
        }
        if(secao[3] > secao[2]){
            if(Objeto[(*i) - 1] > secao[3] && j%2 == 0){
                std::cout <<"4Erro Semantico : Linha " <<  *(i + 1) << std::endl;
            }
        }
        j++;
    }
    j = 0;
    for(auto i = divisao.begin(); i != divisao.end(); ++i){//for pra lista
        if(j%2 == 0){
            for(auto k : constante){
                if(Objeto[Objeto[(*i) - 1]] == 0 && Objeto[k] == 0 && Objeto[(*i) - 1] == k){
                    std::cout <<"5Erro Semantico : Linha " <<  *(i + 1) << std::endl;
                }
            }
        }
        j++;
    }
    j = 0;
    for(auto i = memoria.begin(); i != memoria.end(); ++i){//for pra lista
        if(j%2 == 0){
            for(auto k : constante){
                if(Objeto[(*i) - 1] == k){
                    std::cout << "6Erro Semantico : Linha " <<  *(i + 1) << std::endl;
                }
            }
        }
        j++;
    }
}

void PreProcess::secaoerrada(const int *secao,int linhacod,std::vector<int> &errosem){
    if(secao[0] == 0){
        errosem.push_back(linhacod);
    }else if(secao[0] < linhacod){
        if(secao[1] > secao[0] && secao[1] < linhacod){
            errosem.push_back(linhacod);
        }
    }
}

bool PreProcess::digitohex(std::string &frase){
    if(frase[0] == '0'){
        if(frase[1] == 'x'){
            for(int j = 2;(unsigned)j < frase.size(); j++){
                if(!((frase[j] >= '0' && frase[j] <= '9') || (frase[j] >= 'a' && frase[j] <= 'f'))){
                    return false;
                }
            }
        }else{
            return false;
        }
    }else if(frase[0] == '-'){
            if(frase[1] == '0'){
                if(frase[2] == 'x'){
                    for(int j = 3;(unsigned)j < frase.size(); j++){
                        if(!((frase[j] >= '0' && frase[j] <= '9') || (frase[j] >= 'a' && frase[j] <= 'f'))){
                            return false;
                        }
                    }
                }else{
                    return false;
                }
            }else{
                return false;
            }
    }else{
        return false;
    }
    return true;
}
