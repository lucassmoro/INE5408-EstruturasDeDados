// Copyright [2022] <Lucas de Souza Moro>
#include "./array_stack.h"

bool verificaChaves(std::string trecho_programa) {
    bool resposta = true;
    int  tamanho  = trecho_programa.length();
    structures::ArrayStack<char> pilha(500);
    for (int i = 0; i < tamanho; i++) {
        if (trecho_programa[i] == '}' || trecho_programa[i] == '{') {
          pilha.push(trecho_programa[i]);  
        } 
        std::size_t x;
        x = static_cast<std::size_t>(1);
        if(!pilha.empty() && pilha.top() == '}' && pilha.size() == x){
            resposta = false;
        } else if (trecho_programa[i] == '}' && !pilha.empty()) {
            pilha.pop();
            pilha.pop();
        }
    }
    return resposta;
}
