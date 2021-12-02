#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "preprocess.h"

int main(int argc, char** argv){
    std::string ajuda;
    int aux = 0;
    std::vector<std::string> frase;
    std::vector<std::string> tabeladef1;
    std::vector<int> tabeladefval1;
    std::vector<std::string> tabeladef2;
    std::vector<int> tabeladefval2;
    std::vector<std::string> tabelauso1;
    std::vector<int> tabelausoval1;
    std::vector<std::string> tabelauso2;
    std::vector<int> tabelausoval2;
    std::vector<int> objetos;
    int linha = 0,tamanho1 = 0;
    if (argc < 2 || argc > 3) {
        std::cout << "E necessario 1 ou 2 argumentos para executar o tradutor:" << std::endl;
        std::cout << "./montador <Arquivo de Entrada>.calvo" << std::endl;
        return 0;
    }
    if(argc == 2){
        std::string file1(argv[1]);
        file1 = file1.substr(0, file1.find('.'));
        std::ifstream entrada(strdup((file1 + ".calvo").c_str()));
        std::ofstream saida(strdup((file1 + ".obj").c_str()));
        if (!entrada || !saida) {
            std::cout << "Erro ao abrir arquivos\n";
        }
        while(getline(entrada,ajuda)) {
            linha++;
            frase.clear();
            PreProcess::token(ajuda, frase);
           if(linha == 1){
               continue;
           }else if(linha == 2){
               tamanho1 = PreProcess::convertnumero(frase[1]);
               std:: cout << tamanho1 << std::endl;
           }else if(linha == 3){
               continue;
           }else if(linha == 4){
               for(auto &i : frase){
                   if(i != frase[0]) {
                       aux = PreProcess::convertnumero(i);
                       objetos.push_back(aux);
                   }
               }
           }
        }
        for(auto i = objetos.begin(); i != objetos.end(); ++i){
            saida << (*i);
            if(i != objetos.end()-1){
                saida << ' ';
            }else{
                break;
            }
        }
    }
    if(argc == 3) {
        std::string file1(argv[1]);
        file1 = file1.substr(0, file1.find('.'));
        std::string file2(argv[2]);
        file2 = file2.substr(0, file2.find('.'));
        std::ifstream entrada1(strdup((file1 + ".calvo").c_str()));
        std::ifstream entrada2(strdup((file2 + ".calvo").c_str()));
        std::ofstream saida(strdup((file1 + ".obj").c_str()));
        if (!entrada1 || !saida || !entrada2) {
            std::cout << "Erro ao abrir arquivos\n";
        }
        while (getline(entrada1, ajuda)) {
            linha++;
            frase.clear();
            PreProcess::token(ajuda, frase);
            if(linha == 1) {
                continue;
            }else if(linha == 2) {
                tamanho1 = PreProcess::convertnumero(frase[1]);
            }else if(linha == 3) {
                continue;
            }else if(linha == 4) {
                for (auto &i : frase) {
                    if (i != frase[0]) {
                        aux = PreProcess::convertnumero(i);
                        objetos.push_back(aux);
                    }
                }
            }else if(linha == 5){
                for (auto &i : frase) {
                    if (i != frase[0]) {
                        tabeladef1.push_back(i);
                    }
                }
            }else if(linha == 6){
                for (auto &i : frase) {
                    if (i != frase[0]) {
                        aux = PreProcess::convertnumero(i);
                        tabeladefval1.push_back(aux);
                    }
                }
            }else if(linha == 7){
                for (auto &i : frase) {
                    if (i != frase[0]) {
                        tabelauso1.push_back(i);
                    }
                }
            }else if(linha == 8){
                for (auto &i : frase) {
                    if (i != frase[0]) {
                        aux = PreProcess::convertnumero(i);
                        tabelausoval1.push_back(aux);
                    }
                }
            }
        }
        linha = 0;
        while (getline(entrada2, ajuda)) {
            linha++;
            frase.clear();
            PreProcess::token(ajuda, frase);
            if(linha == 1) {
                continue;
            }else if(linha == 2) {
                continue;
            }else if(linha == 3) {
                continue;
            }else if(linha == 4) {
                for (auto &i : frase) {
                    if (i != frase[0]) {
                        aux = PreProcess::convertnumero(i);
                        objetos.push_back(aux);
                    }
                }
            }else if(linha == 5){
                for (auto &i : frase) {
                    if (i != frase[0]) {
                        tabeladef2.push_back(i);
                    }
                }
            }else if(linha == 6){
                for (auto &i : frase) {
                    if (i != frase[0]) {
                        aux = PreProcess::convertnumero(i);
                        tabeladefval2.push_back(aux);
                    }
                }
            }else if(linha == 7){
                for (auto &i : frase) {
                    if (i != frase[0]) {
                        tabelauso2.push_back(i);
                    }
                }
            }else if(linha == 8){
                for (auto &i : frase) {
                    if (i != frase[0]) {
                        aux = PreProcess::convertnumero(i);
                        tabelausoval2.push_back(aux);
                    }
                }
            }
        }
        for(int & i : tabeladefval2){
            i = i + tamanho1;
        }
        for(int & i : tabelausoval2){
            i = i + tamanho1;
        }
        auto k = 0,l = 0;
        for(const auto& i : tabeladef1){
            k = 0;
            for(const auto& j : tabelauso2){
                if(i == j){
                    objetos[tabelausoval2[k]] = objetos[tabelausoval2[k]] + tabeladefval1[l];
                }
                k++;
            }
            l++;
        }
        l = 0;
        for(const auto& i : tabeladef2){
            k = 0;
            for(const auto &j : tabelauso1){
                if(i == j){
                    objetos[tabelausoval1[k]] = objetos[tabelausoval1[k]] + tabeladefval2[l];
                }
                k++;
            }
            l++;
        }
        for(auto i = objetos.begin(); i != objetos.end(); ++i) {
            saida << *i;
            if(i != objetos.end()-1){
                saida << ' ';
            }
        }
    }

    return 0;
}