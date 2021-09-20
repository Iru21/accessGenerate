#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <regex>
#include <ctime>
#include <time.h>

using namespace std;

vector<string> get_nazwiska() {
    ifstream fNazwiska("nazwiska.txt");
    vector<string> vn;
    string ln;
    while(getline(fNazwiska, ln)) {
        vn.push_back(ln);
    }
    return vn;
}

vector<string> get_imiona_m() {
    ifstream fImionaM("imiona-m.txt");
    vector<string> vim;
    string lim;
    while(getline(fImionaM, lim)) {
        vim.push_back(lim);
    }
    return vim;
}

vector<string> get_imiona_f() {
    ifstream fImionaF("imiona-f.txt");
    vector<string> vif;
    string lif;
    while(getline(fImionaF, lif)) {
        vif.push_back(lif);
    }
    return vif;
}

vector<string> full_m(int n) {
    vector<string> nazwiska = get_nazwiska();
    vector<string> imiona_m = get_imiona_m();
    vector<string> inp_m;
    srand(time(0));
    for(int i = 0; i < n; i++) {

        string pesel = to_string(rand() % 99999 + 11111) + to_string(rand() % 999999 + 111111);

        string in = imiona_m[rand() % imiona_m.size()] + " " + nazwiska[rand() % nazwiska.size()] + " " + (string) pesel;
        inp_m.push_back(in);
    }
    return inp_m;
}

vector<string> full_f(int n) {
    vector<string> nazwiska = get_nazwiska();
    vector<string> imiona_f = get_imiona_f();
    vector<string> inp_f;
    srand(time(0));
    for(int j = 0; j < n; j++) {
        string selected = nazwiska[rand() % nazwiska.size()];
        string n = regex_replace(selected, regex("ski$"), "ska");
        n = regex_replace(n, regex("cki$"), "cka");
        n = regex_replace(n, regex("dzki$"), "dzka");

        string pesel = to_string(rand() % 99999 + 11111) + to_string(rand() % 999999 + 111111);

        string inf = imiona_f[rand() % imiona_f.size()] + " " + n + " " + (string) pesel;
        inp_f.push_back(inf);
    }
    return inp_f;
}

void write(vector<string> m, vector<string> f, int hm) {
    ofstream d;
    d.open("data.txt");
    string chonk;
    for(int k = 0; k < m.size(); k++) {
        //cout << to_string(k) + " / " + to_string(hm) + " " << m[k] << endl;
        chonk += m[k] + "\n";
    }
    for(int l = 0; l < f.size(); l++) {
        //cout << to_string(f.size() + l + 1) + " / " + to_string(hm) + " " << f[l] << endl;
        chonk +=  f[l] + "\n";
    }
    if(hm % 2 != 0) {
        string gen = f[rand() % f.size()];
        //cout << to_string(hm) + " / " + to_string(hm) + " " << gen << endl;
        chonk +=  gen + "\n";
    }
    d << chonk;
	d.close();
}

int main() {
    cout << "How many? ";
    int hm;
    cin >> hm;
    system("cls");
    const clock_t begin_time = clock();
    vector<string> inp_m = full_m(hm / 2);
    vector<string> inp_f = full_f(hm / 2);
    write(inp_m, inp_f, hm);
    cout << float( clock() - begin_time) /  CLOCKS_PER_SEC << "s" << endl;
    system("pause");
    return 0;
}