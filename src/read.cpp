#include "read.hpp"

void leitor_principal(unordered_map<string, int> &hash,unordered_map<string, int> &stopWords,unordered_map<char, bool> &pontos,string filename, int &k){
    ifstream input_file(filename, ios::in);
    string line;
    string palavra_analisada;
    preencheMapPontos(pontos); 

    if (!input_file.is_open()) {
            cout << "Nao foi possivel abrir o arquivo" << filename << " " << endl;
    }

        while (!input_file.eof()) {
            while (getline(input_file, line, '\n')) { 
                for (auto &c : line) {
                    c = tolower(c); 
                }
                line = converterAcentuadasParaMinusculas(line);
                line = removePontuacao(line, pontos); 
                istringstream ln(line); 
                  
                if (line.size() > 1) {
                    //decisao = false;

                    while (ln >> palavra_analisada) {  
                        //auto it2 = stopWords.find(palavra_analisada);
                        if(stopWords.count(palavra_analisada)==0){   
                            if (palavra_analisada != "") {   
                                if (!existe_numero(palavra_analisada)) {
                                    auto it3 = hash.find(palavra_analisada);
                                    if (it3 != hash.end()) {
                                        it3->second++; 
                                    }else {
                                        hash.insert({palavra_analisada, 1}); 
                                        k=k+1;
                                    }
                                }
                            }    
                        }
                    }
                    line.clear();
                }
            }
        }
        
    
    
}

void fn_principal(){
    string filename("dataset/DomCasmurro.txt");
    string filename2("dataset/Semana_Machado_Assis.txt");

    int k=0;

    unordered_map<string, int> hash;
    unordered_map<string, int> stopWords;
    unordered_map<char, bool>pontos;
    
    vector<pair<string, int>> heap;

    readStopWords(stopWords);

    leitor_principal(hash,stopWords,pontos,filename,k);    
    leitor_principal(hash,stopWords,pontos,filename2,k);

    // Copiar os primeiros k elementos
    auto it = hash.begin();
    for (int i = 0; i < 20 && it != hash.end(); ++i, ++it) {
        heap.push_back(*it);
    }

    // Transformar os primeiros k elementos em um heap
    make_heap(heap.begin(), heap.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; 
    });

    // Copiar os elementos restantes
    while (it != hash.end()) {
        if (it->second > heap.front().second) {
            pop_heap(heap.begin(), heap.end());
            heap.pop_back();
            heap.push_back(*it);
            make_heap(heap.begin(), heap.end(), [](const auto& a, const auto& b) {
                return a.second > b.second; 
            });
        }
        ++it;
    }

    /*sort(heap.begin(), heap.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; 
    });*/
    
    int contador=1;
    for (const auto& pair : heap) {
        cout << "PALAVRA: " << pair.first << ", QUANTIDADE: " << pair.second <<" "<<contador<<endl;
        contador++;
    }

    cout<<k<<endl;
}

string removePontuacao(string palavra, unordered_map<char, bool>pontos) { // remove pontuacao e char estranho para n aparacer no output
    string palavraSemPonto;
    
    for (char c : palavra) { // percorre cada char da palavar pra ver se eh um ponto
        auto it = pontos.find(c);
        if (it == pontos.end()) { // se o char n for ponto, ele coloca na string palavraSemponto
            palavraSemPonto += c;
        }
    }
    return palavraSemPonto;
}

bool existe_numero(string palavra) {// verifica se tem numero
    for (int i = 0;i < palavra.size();i++) {
        if (isdigit(palavra[i])) return true;
    }

    return false;
}

string converterAcentuadasParaMinusculas(string palavra) {
    string maiuscula = "ÁÀÃÉÈÍÌÓÒÚÙ";
    string minuscula = "áàãéèíìóòúù";

    for (size_t i = 0; i < maiuscula.size(); i++) {
        replace(palavra.begin(), palavra.end(), maiuscula[i], minuscula[i]);
    }
    return palavra;
}

void preencheMapPontos(unordered_map<char, bool> &pontos) {
    pontos.insert({
        {'-', false},
        {'.', false},
        {',', false},
        {';', false},
        {'"', false},
        {'/', false},
        {'(', false},
        {')', false},
        {'[', false},
        {']', false},
        {'+', false},
        {'-', false},
        {'=', false},
        {'$', false},
        {'%', false},
        {'&', false},
        {'*', false},
        {':', false},
        {'^', false},
        {'|', false},
        {'~', false},
        {'_', false},
        });
}

void readStopWords(unordered_map<string, int> &stopWords) {
    string filename("dataset/stopwords.csv");
    ifstream input_file(filename, ios::in);
    string line;

    while (!input_file.eof()) {
        while (getline(input_file, line, '\n')) {
            if (line.size() >= 1) {
                for (auto &c : line) {
                    c = tolower(c);
                }
                stopWords.insert({ line,1});
            }
        }
    }
}

