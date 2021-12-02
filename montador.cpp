#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include "preprocess.h"
int montar(const std::string &file,int argc){
    std::vector<std::string> Instrucao;
    std::vector<std::string> Diretivas;
    std::vector<std::string> Simbols;
    std::vector<std::string> frase;
    std::vector<std::string> space;
    std::vector<int> SimbolsValor;
    std::vector<int> SimbolsValid;
    std::vector<int> rotulolinha;
    std::vector<int> Objeto;
    std::vector<int> errosem;
    std::vector<int> constante;
    std::vector<int> divisao;
    std::vector<int> memoria;
    std::vector<int> pulo;
    std::vector<int> spaceval;
    std::vector<std::string> tabeladef;
    std::vector<int> tabeladefval;
    std::vector<std::string> tabelauso;
    std::vector<std::string> tabelausoaux;
    std::vector<int> tabelausoval;
    char *end;
    int secao[4];
    int aux,aux2,linha = 0,label,copyval,linhacod = 0,soma = 0;
    std::string ajuda;
    PreProcess::TabInstDirect(Instrucao,Diretivas);
    secao[0] = linhacod;
    secao[1] = linhacod;
    std::ifstream entrada(strdup((file+".pre").c_str()));
    std::ofstream saida(strdup((file+".calvo").c_str()));
    if (!entrada || !saida) {
        std::cout << "Erro ao abrir arquivos\n";
    }
    while(getline(entrada,ajuda)){
        frase.clear();
        PreProcess::token(ajuda,frase);
        aux = 0;
        aux2 = 0;
        label = 0;
        copyval = 0;
        soma = 0;
        linhacod++;
        PreProcess::errolexico(linhacod,frase);
        if(((frase[0]).find(':')) != frase[0].npos){
            aux = 15;
            label = 1;
            for(auto i = Simbols.begin(); i != Simbols.end(); ++i){//for pra lista
                if( (*i) == frase[0].substr(0,frase[0].find(':'))){
                    if(SimbolsValid[(i - Simbols.begin())] == 0){
                        if(PreProcess::compstring(frase[1],Diretivas[1]) && frase.size() > 2){
                            if(PreProcess::convertnumero(frase[2]) <= Objeto[SimbolsValor[(i - Simbols.begin())] - 1]){
                                errosem.push_back(rotulolinha[(i - Simbols.begin())]);
                            }
                        }
                        if(PreProcess::compstring(frase[1],Diretivas[1]) && frase.size() == 2){
                            if(Objeto[SimbolsValor[(i - Simbols.begin())] - 1] != 0){
                                errosem.push_back(rotulolinha[(i - Simbols.begin())]);
                            }
                        }
                        if((PreProcess::compstring(frase[1],Diretivas[2])) && (Objeto[SimbolsValor[(i - Simbols.begin())] - 1] != 0)){
                            errosem.push_back(rotulolinha[(i - Simbols.begin())]);
                        }
                        if(!(PreProcess::compstring(frase[1],Diretivas[1])) && !(PreProcess::compstring(frase[1],Diretivas[2])) && Objeto[SimbolsValor[(i - Simbols.begin())] - 1] != 0){
                            errosem.push_back(rotulolinha[(i - Simbols.begin())]);
                        }
                        Objeto[SimbolsValor[(i - Simbols.begin())] - 1] = Objeto[SimbolsValor[(i - Simbols.begin())] - 1] + linha;
                    }
                    if(SimbolsValid[(i - Simbols.begin())] == 2){
                        if(PreProcess::compstring(frase[1],Diretivas[1]) && frase.size() > 2){
                            if(PreProcess::convertnumero(frase[2]) <= Objeto[SimbolsValor[(i - Simbols.begin())] - 2]){
                                errosem.push_back(linhacod);
                            }
                        }
                        if(PreProcess::compstring(frase[1],Diretivas[1]) && frase.size() == 2){
                            if(Objeto[SimbolsValor[(i - Simbols.begin())] - 2] != 0){
                                errosem.push_back(linhacod);
                            }
                        }
                        if((PreProcess::compstring(frase[1],Diretivas[2])) && (Objeto[SimbolsValor[(i - Simbols.begin())] - 2] != 0)){
                            errosem.push_back(rotulolinha[(i - Simbols.begin())]);
                        }
                        if(!(PreProcess::compstring(frase[1],Diretivas[1])) && !(PreProcess::compstring(frase[1],Diretivas[2])) && Objeto[SimbolsValor[(i - Simbols.begin())] - 2] != 0){
                            errosem.push_back(rotulolinha[(i - Simbols.begin())]);
                        }
                        Objeto[SimbolsValor[(i - Simbols.begin())] - 2] = Objeto[SimbolsValor[(i - Simbols.begin())] - 2] + linha;
                    }
                    if(SimbolsValid[(i - Simbols.begin())] == 1){
                        errosem.push_back(linhacod);
                    }
                    aux = 16;
                }
            }
            for(auto i = Simbols.begin(); i != Simbols.end(); ++i){//for pra lista
                if( (*i) == frase[0].substr(0,frase[0].find(':'))){
                    SimbolsValor[(i - Simbols.begin())] = linha;
                    SimbolsValid[(i - Simbols.begin())] = label;
                    aux = 16;
                }
            }
            if(aux == 15){
                if(frase[1] != Diretivas[6]) {
                    Simbols.push_back(frase[0].substr(0, frase[0].find(':')));
                    SimbolsValor.push_back(linha);
                    SimbolsValid.push_back(label);
                    rotulolinha.push_back(linhacod);
                }
            }
        }
        PreProcess::errosintatico(linhacod,label,frase,Instrucao,Diretivas,ajuda);
        if(PreProcess::compstring(frase[label],Instrucao[0])){
            aux = 1;
            Objeto.push_back(aux);
            linha = linha + 2;
            PreProcess::secaoerrada(secao,linhacod,errosem);
        }
        if(PreProcess::compstring(frase[label],Instrucao[1])){
            aux = 2;
            Objeto.push_back(aux);
            linha = linha + 2;
            PreProcess::secaoerrada(secao,linhacod,errosem);
        }
        if(PreProcess::compstring(frase[label],Instrucao[2])){
            aux = 3;
            Objeto.push_back(aux);
            linha = linha + 2;
            PreProcess::secaoerrada(secao,linhacod,errosem);
        }
        if(PreProcess::compstring(frase[label],Instrucao[3])){
            aux = 4;
            Objeto.push_back(aux);
            linha = linha + 2;
            divisao.push_back(linha);
            divisao.push_back(linhacod);
            PreProcess::secaoerrada(secao,linhacod,errosem);
        }
        if(PreProcess::compstring(frase[label],Instrucao[4])){
            aux = 5;
            Objeto.push_back(aux);
            linha = linha + 2;
            PreProcess::secaoerrada(secao,linhacod,errosem);
            pulo.push_back(linha);
            pulo.push_back(linhacod);
            if(label == 1){
                if(frase[0].substr(0,frase[0].find(':')) == frase[label+1]){
                    errosem.push_back(linhacod);
                }
            }
        }
        if(PreProcess::compstring(frase[label],Instrucao[5])){
            aux = 6;
            Objeto.push_back(aux);
            linha = linha + 2;
            PreProcess::secaoerrada(secao,linhacod,errosem);
            pulo.push_back(linha);
            pulo.push_back(linhacod);
            if(label == 1){
                if(frase[0].substr(0,frase[0].find(':')) == frase[label+1]){
                    errosem.push_back(linhacod);
                }
            }
        }
        if(PreProcess::compstring(frase[label],Instrucao[6])){
            aux = 7;
            Objeto.push_back(aux);
            linha = linha + 2;
            PreProcess::secaoerrada(secao,linhacod,errosem);
            pulo.push_back(linha);
            pulo.push_back(linhacod);
            if(label == 1){
                if(frase[0].substr(0,frase[0].find(':')) == frase[label+1]){
                    errosem.push_back(linhacod);
                }
            }
        }
        if(PreProcess::compstring(frase[label],Instrucao[7])){
            aux = 8;
            Objeto.push_back(aux);
            linha = linha + 2;
            PreProcess::secaoerrada(secao,linhacod,errosem);
            pulo.push_back(linha);
            pulo.push_back(linhacod);
            if(label == 1){
                if(frase[0].substr(0,frase[0].find(':')) == frase[label+1]){
                    errosem.push_back(linhacod);
                }
            }
        }
        if(PreProcess::compstring(frase[label],Instrucao[8])){
            aux = 9;
            Objeto.push_back(aux);
            linha = linha + 3;
            copyval = 1;
            memoria.push_back(linha);
            memoria.push_back(linhacod);
            for(int j = 0;(unsigned)j < ajuda.size(); j++){
                if(frase.size() == (unsigned)(label + 4) && PreProcess::digito(frase[label + 2])){
                    copyval = 2;
                }
                if(frase.size() == (unsigned)(label + 4) && PreProcess::digito(frase[label + 3])){
                    copyval = 3;
                }
                if(frase.size() == (unsigned)(label + 5)){
                    copyval = 4;
                }
            }
            PreProcess::secaoerrada(secao,linhacod,errosem);
        }
        if(PreProcess::compstring(frase[label],Instrucao[9])){
            aux = 10;
            Objeto.push_back(aux);
            linha = linha + 2;
            PreProcess::secaoerrada(secao,linhacod,errosem);
        }
        if(PreProcess::compstring(frase[label],Instrucao[10])){
            aux = 11;
            Objeto.push_back(aux);
            linha = linha + 2;
            memoria.push_back(linha);
            memoria.push_back(linhacod);
            PreProcess::secaoerrada(secao,linhacod,errosem);
        }
        if(PreProcess::compstring(frase[label],Instrucao[11])){
            aux = 12;
            Objeto.push_back(aux);
            linha = linha + 2;
            memoria.push_back(linha);
            memoria.push_back(linhacod);
            PreProcess::secaoerrada(secao,linhacod,errosem);
        }
        if(PreProcess::compstring(frase[label],Instrucao[12])){
            aux = 13;
            Objeto.push_back(aux);
            linha = linha + 2;
            PreProcess::secaoerrada(secao,linhacod,errosem);
        }
        if(PreProcess::compstring(frase[label],Instrucao[13])){
            aux = 14;
            Objeto.push_back(aux);
            linha = linha + 1;
            PreProcess::secaoerrada(secao,linhacod,errosem);
            continue;
        }
        if(PreProcess::compstring(frase[label],Diretivas[0])){
            if(frase[1] == "text"){
                if(secao[0] == 0){
                    secao[0] = linhacod;
                    secao[2] = linha;
                }else{
                    errosem.push_back(linhacod);
                }
            }
            if(frase[1] == "data"){
                if(secao[1] == 0){
                    secao[1] = linhacod;
                    secao[3] = linha;
                }
            }
            continue;
        }
        if(PreProcess::compstring(frase[label],Diretivas[1])){
            Objeto.push_back(0);
            int j = 0;
            aux = 1;
            if(frase.size() > 2){
                aux = strtol(frase[label+1].c_str(), &end,10);
                if(aux > 1){
                    linha = linha + aux;
                    while(aux - 1 > j){
                        Objeto.push_back(0);
                        j++;
                    }
                }else{
                    linha = linha + 1;
                }
            }else{
                linha = linha + 1;
            }
            space.push_back(frase[0].substr(0,frase[0].find(':')));
            spaceval.push_back(aux);
            if(secao[1] == 0){
                errosem.push_back(linhacod);
            }else if(secao[1] < linhacod){
                if(secao[0] > secao[1] && secao[0] < linhacod){
                    errosem.push_back(linhacod);
                }
            }
            continue;
        }
        if(PreProcess::compstring(frase[label],Diretivas[2])){
            Objeto.push_back(PreProcess::convertnumero(frase[label+1]));
            constante.push_back(linha);
            linha = linha + 1;
            if(secao[1] == 0){
                errosem.push_back(linhacod);
            }else if(secao[1] < linhacod){
                if(secao[0] > secao[1] && secao[0] < linhacod){
                    errosem.push_back(linhacod);
                }
            }
            continue;
        }
        if(PreProcess::compstring(frase[label],Diretivas[3])){
            continue;
        }
        if(PreProcess::compstring(frase[label],Diretivas[4])){
            continue;
        }
        if(PreProcess::compstring(frase[label],Diretivas[5])){
            tabeladef.push_back(frase[label+1]);
            tabeladefval.push_back(0);
            continue;
        }
        if(PreProcess::compstring(frase[label],Diretivas[6])){
            tabelausoaux.push_back(frase[0].substr(0,frase[0].find(':')));
            continue;
        }
        int j = 0;
        for(auto i = Simbols.begin(); i != Simbols.end(); ++i){//for pra lista
            if((*i) == frase[label+1] && SimbolsValid[i - Simbols.begin()] == 1 && j == 0 && copyval == 0){
                if((((ajuda).find('+')) != std::string::npos) && (frase.size() > (unsigned)(label+2))){
                    soma = PreProcess::convertnumero(frase[label + 2]);
                }
                for(auto k = space.begin(); k != space.end(); ++k){
                    if((*i) == (*k)){
                        if(spaceval[(k - space.begin())] <= soma){
                            errosem.push_back(linhacod);
                            aux2 = -1;
                        }else{
                            aux2 = 1;
                        }
                    }
                }
                if(aux2 == 0 && frase.size() > (unsigned)(label+2)){
                    errosem.push_back(linhacod);
                }
                Objeto.push_back((SimbolsValor[i - Simbols.begin()]) + soma);
                aux = 0;
                j++;
            }
        }
        if(copyval > 0){
            if(copyval == 1){
                for(auto i = Simbols.begin(); i != Simbols.end(); ++i){//for pra lista
                    if((*i) == frase[label+1] && SimbolsValid[i - Simbols.begin()] == 1 && j == 0){
                        Objeto.push_back((SimbolsValor[i - Simbols.begin()]));
                        j++;
                    }
                }
                if(j == 0){
                    Simbols.push_back(frase[label+1]);
                    SimbolsValor.push_back(linha);
                    SimbolsValid.push_back(2);
                    rotulolinha.push_back(linhacod);
                    Objeto.push_back(0);
                }
                j = 0;
                for(auto i = Simbols.begin(); i != Simbols.end(); ++i){//for pra lista
                    if((*i) == frase[label+2] && SimbolsValid[i - Simbols.begin()] == 1 && j == 0){
                        Objeto.push_back((SimbolsValor[i - Simbols.begin()]));
                        j++;
                    }
                }
                if(j == 0){
                    Simbols.push_back(frase[label+2]);
                    SimbolsValor.push_back(linha);
                    SimbolsValid.push_back(0);
                    rotulolinha.push_back(linhacod);
                    Objeto.push_back(0);
                }
            }
            if(copyval == 2){
                soma = PreProcess::convertnumero(frase[label + 2]);
                for(auto i = Simbols.begin(); i != Simbols.end(); ++i){//for pra lista
                    if((*i) == frase[label+1] && SimbolsValid[i - Simbols.begin()] == 1 && j == 0){
                        for(auto k = space.begin(); k != space.end(); ++k){
                            if((*i) == (*k)){
                                if(spaceval[(k - space.begin())] <= soma){
                                    errosem.push_back(linhacod);
                                    aux2 = -1;
                                }else{
                                    aux2 = 1;
                                }
                            }
                        }
                        if(aux2 == 0 ){
                            errosem.push_back(linhacod);
                        }
                        Objeto.push_back((SimbolsValor[i - Simbols.begin()] + soma));
                        j++;
                    }
                }
                if(j == 0){
                    Simbols.push_back(frase[label+1]);
                    SimbolsValor.push_back(linha);
                    SimbolsValid.push_back(2);
                    rotulolinha.push_back(linhacod);
                    Objeto.push_back(soma);
                }
                j = 0;
                for(auto i = Simbols.begin(); i != Simbols.end(); ++i){//for pra lista
                    if((*i) == frase[label+3] && SimbolsValid[i - Simbols.begin()] == 1 && j == 0){
                        Objeto.push_back((SimbolsValor[i - Simbols.begin()]));
                        j++;
                    }
                }
                if(j == 0){
                    Simbols.push_back(frase[label+3]);
                    SimbolsValor.push_back(linha);
                    SimbolsValid.push_back(0);
                    rotulolinha.push_back(linhacod);
                    Objeto.push_back(0);
                }
            }
            if(copyval == 3){
                soma = PreProcess::convertnumero(frase[label + 3]);
                for(auto i = Simbols.begin(); i != Simbols.end(); ++i){//for pra lista
                    if((*i) == frase[label+1] && SimbolsValid[i - Simbols.begin()] == 1 && j == 0){
                        Objeto.push_back((SimbolsValor[i - Simbols.begin()]));
                        j++;
                    }
                }
                if(j == 0){
                    Simbols.push_back(frase[label+1]);
                    SimbolsValor.push_back(linha);
                    SimbolsValid.push_back(2);
                    rotulolinha.push_back(linhacod);
                    Objeto.push_back(0);
                }
                j = 0;
                for(auto i = Simbols.begin(); i != Simbols.end(); ++i){//for pra lista
                    if((*i) == frase[label+2] && SimbolsValid[i - Simbols.begin()] == 1 && j == 0){
                        for(auto k = space.begin(); k != space.end(); ++k){
                            if((*i) == (*k)){
                                if(spaceval[(k - space.begin())] <= soma){
                                    errosem.push_back(linhacod);
                                    aux2 = -1;
                                }else{
                                    aux2 = 1;
                                }
                            }
                        }
                        if(aux2 == 0){
                            errosem.push_back(linhacod);
                        }
                        Objeto.push_back((SimbolsValor[i - Simbols.begin()]) + soma);
                        j++;
                    }
                }
                if(j == 0){
                    Simbols.push_back(frase[label+2]);
                    SimbolsValor.push_back(linha);
                    SimbolsValid.push_back(0);
                    rotulolinha.push_back(linhacod);
                    Objeto.push_back(soma);
                }
            }
            if(copyval == 4){
                soma = PreProcess::convertnumero(frase[label + 2]);
                for(auto i = Simbols.begin(); i != Simbols.end(); ++i){//for pra lista
                    if((*i) == frase[label+1] && SimbolsValid[i - Simbols.begin()] == 1 && j == 0){
                        for(auto k = space.begin(); k != space.end(); ++k){
                            if((*i) == (*k)){
                                if(spaceval[(k - space.begin())] <= soma){
                                    errosem.push_back(linhacod);
                                    aux2 = -1;
                                }else{
                                    aux2 = 1;
                                }
                            }
                        }
                        if(aux2 == 0){
                            errosem.push_back(linhacod);
                        }
                        Objeto.push_back((SimbolsValor[i - Simbols.begin()] + soma));
                        j++;
                    }
                }
                if(j == 0){
                    Simbols.push_back(frase[label+1]);
                    SimbolsValor.push_back(linha);
                    SimbolsValid.push_back(2);
                    rotulolinha.push_back(linhacod);
                    Objeto.push_back(soma);
                }
                aux2 = 0;
                j = 0;
                soma = PreProcess::convertnumero(frase[label + 4]);
                for(auto i = Simbols.begin(); i != Simbols.end(); ++i){//for pra lista
                    if((*i) == frase[label+3] && SimbolsValid[i - Simbols.begin()] == 1 && j == 0){
                        for(auto k = space.begin(); k != space.end(); ++k){
                            if((*i) == (*k)){
                                if(spaceval[(k - space.begin())] <= soma){
                                    errosem.push_back(linhacod);
                                    aux2 = -1;
                                }else{
                                    aux2 = 1;
                                }
                            }
                        }
                        if(aux2 == 0){
                            errosem.push_back(linhacod);
                        }
                        Objeto.push_back((SimbolsValor[i - Simbols.begin()]) + soma);
                        j++;
                    }
                }
                if(j == 0){
                    Simbols.push_back(frase[label+3]);
                    SimbolsValor.push_back(linha);
                    SimbolsValid.push_back(0);
                    rotulolinha.push_back(linhacod);
                    Objeto.push_back(soma);
                }
            }
            aux = 0;
        }
        if(aux > 0){
            aux = 0;
            if((((ajuda).find('+')) != std::string::npos) && (copyval < 1)){
                aux = PreProcess::convertnumero(frase.back());
            }
            Simbols.push_back(frase[label+1]);
            SimbolsValor.push_back(linha);
            SimbolsValid.push_back(0);
            rotulolinha.push_back(linhacod);
            Objeto.push_back(aux);
        }
    }
    PreProcess::errosemantico(errosem,secao,SimbolsValid,rotulolinha,Objeto,pulo,constante,divisao,memoria,argc);
    saida << "H: " << file << std::endl;
    saida << "H: " << Objeto.size() << std::endl;
    saida << "H: ";
    int instrucao = 0;
    for(auto i = Objeto.begin(); i != Objeto.end(); ++i) {//for pra lista
        if (instrucao == 0) {
            saida << "0";
            instrucao = *i;
        }else if (instrucao != 9 && instrucao != 14) {
            saida << "1";
            instrucao = 0;
        }else if(instrucao == 9){
            saida << "1 " << "1";
            instrucao = 0;
        }else if(instrucao == 14){
            saida << "0";
        }
        if(i != Objeto.end()-1){
            saida << " ";
        }else{
            saida << std::endl;
        }

    }
    saida << "T: ";
    if(secao[1] > secao[0]){
        for(auto i = Objeto.begin(); i != Objeto.end(); ++i){//for pra lista
            if((*i) != Objeto.back() || i != Objeto.end()){
                saida << (*i) << " ";
            }else{
                saida << (*i);
            }
        }
    }else{
        int j = 0;
        for(auto i : Objeto){//for pra lista
            if(j > secao[2]-1){
                saida << i << " ";
            }
            j++;
        }
        j = 0;
        for(auto i : Objeto){//for pra lista
            if(j < secao[2]){
                saida << i << " ";
            }
            j++;
        }
    }
    saida << std::endl;
    saida << "T: ";
    auto k = 0,f = 0;
    for(auto &i : Simbols) {
        f = 0;
        for(auto &j : tabeladef) {
            if(i == j){
                tabeladefval[f] = SimbolsValor[k];
            }
            f++;
        }
        for(auto &l : tabelausoaux) {
            if(i == l){
                if(SimbolsValid[k] == 0) {
                    tabelauso.push_back(i);
                    tabelausoval.push_back(SimbolsValor[k] - 1);
                }
                if(SimbolsValid[k] == 2) {
                    tabelauso.push_back(i);
                    tabelausoval.push_back(SimbolsValor[k] - 2);
                }
            }
        }
        k++;
    }
    for(auto i = tabeladef.begin(); i != tabeladef.end(); ++i) {
        saida << *i;
        if(i != tabeladef.end()-1){
            saida << ' ';
        }else{
            saida << std::endl;
        }
    }
    saida << "T: ";
    for(auto i = tabeladefval.begin(); i != tabeladefval.end(); ++i) {
        saida << *i;
        if(i != tabeladefval.end()-1){
            saida << ' ';
        }else{
            saida << std::endl;
        }
    }
    saida << "T: ";
    for(auto i = tabelauso.begin(); i != tabelauso.end(); ++i) {
        saida << *i;
        if(i != tabelauso.end()-1){
            saida << ' ';
        }else{
            saida << std::endl;
        }
    }
    saida << "T: ";
    for(auto i = tabelausoval.begin(); i != tabelausoval.end(); ++i) {
        saida << *i;
        if(i != tabelausoval.end()-1){
            saida << ' ';
        }else{
            saida << std::endl;
        }
    }
    return 0;
}

int main(int argc, char** argv){
    if (argc < 2 || argc > 3) {
		std::cout << "E necessario 1 ou 2 argumentos para executar o tradutor:" << std::endl;
		std::cout << "./montador <Arquivo de Entrada>.asm" << std::endl;
		return 0;
	}
	std::string file1(argv[1]);
    file1 = file1.substr(0,file1.find('.'));
    PreProcess::pre(file1,argc);
    montar(file1,argc);
    if(argc == 3) {
        std::string file2(argv[2]);
        file2 = file2.substr(0, file2.find('.'));
        PreProcess::pre(file2,argc);
        montar(file2,argc);
    }
    return 0;
}