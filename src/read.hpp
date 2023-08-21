#ifndef READ_HPP
#define READ_HPP

#include <bits/stdc++.h>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <vector>
#define endl '\n'

using namespace std;

void fn_principal();
void leitor_principal(unordered_map<string, int> &hash,unordered_map<string, int> &stopWords,unordered_map<char, bool> &pontos,string filename, int &k);
void preencheMapPontos(unordered_map<char, bool> &pontos);
void readStopWords(unordered_map<string, int> &stopWords);

bool existe_numero(string palavra);

string converterAcentuadasParaMinusculas(string num);
string removePontuacao(string num, unordered_map<char, bool>pontos);
#endif