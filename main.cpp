#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <regex>
#include <ctime>
#include <time.h>
#include <algorithm>

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

string gen_pesel() {
    string p = to_string(rand() % 99999 + 11111) + to_string(rand() % 999999 + 111111);
    return p;
}

void rep(string& s, string se, string re) {
    size_t pos = 0;
    while((pos = s.find(se, pos)) != string::npos) {
        s.replace(pos, se.length(), re);
        pos += re.length();
    }
}

string gen_nazwisko(bool f, vector<string> &nazwiska) {
    if(f) {
        std::string n = nazwiska[rand() % nazwiska.size()];
        rep(n, "ski", "ska");
        rep(n, "cki", "cka");
        rep(n, "dzki", "dzka");
        return n;
    }
    else {
        string n = nazwiska[rand() % nazwiska.size()];
        return n;
    }
}

vector<string> full_m(int n) {
    vector<string> nazwiska = get_nazwiska();
    vector<string> imiona_m = get_imiona_m();
    vector<string> inp_m;
    for(int i = 0; i < n; i++) {
        string in = imiona_m[rand() % imiona_m.size()] + " " + gen_nazwisko(false, nazwiska) + " " + gen_pesel();
        inp_m.push_back(in);
    }
    return inp_m;
}

vector<string> full_f(int n) {
    vector<string> nazwiska = get_nazwiska();
    vector<string> imiona_f = get_imiona_f();
    vector<string> inp_f;
    for(int i = 0; i < n; i++) {
        string in = imiona_f[rand() % imiona_f.size()] + " " + gen_nazwisko(true, nazwiska) + " " + gen_pesel();
        inp_f.push_back(in);
    }
    return inp_f;
}
//                                                  super slow v
void write(vector<string> m, vector<string> f, int hm, bool counter) {
    ofstream d;
    d.open("data.txt");
    string chonk;
    for(auto k : m) {
        chonk += k + "\n";
        if(counter) cout << to_string(count(chonk.begin(), chonk.end(), '\n')) + " / " + to_string(hm) + " " << k << endl;
    }
    for(auto l : f) {
        chonk += l + "\n";
        if(counter) cout << to_string(f.size() + (count(chonk.begin(), chonk.end(), '\n') / 2)) + " / " + to_string(hm) + " " << l << endl;
    }
    if(hm % 2 != 0) {
        string gen = f[rand() % f.size()];
        chonk += gen;
        if(counter) cout << to_string(hm) + " / " + to_string(hm) + " " << gen << endl;
    }
    d << chonk;
	d.close();
}

int main() {
    cout << "How many? - ";
    int hm;
    cin >> hm;
    cout << "Log? - (y/n) - ";
    char log;
    cin >> log;
    const clock_t begin_time = clock();
    srand(time(0));
    vector<string> m = full_m(hm / 2);
    vector<string> f = full_f(hm / 2);
    write(m, f, hm, log == 'y');
    cout << "Completed in: " << float( clock() - begin_time) /  CLOCKS_PER_SEC << "s" << endl;
    system("pause");
    return 0;
}