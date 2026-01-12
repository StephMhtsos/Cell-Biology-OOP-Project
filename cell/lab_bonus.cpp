#include <iostream>
#include <vector>
#include <string>

using namespace std;


// Sequence (DNA, RNA, Protein)

class Sequence {
protected:
    string data;
public:
    Sequence(const string& d) : data(d) {

    }
    virtual ~Sequence() {

    }
    virtual bool isValid() const = 0;
    string getData() const { 
        return data; 
    }
    void print() const { 
        cout << data << " (length=" << data.size() << ")"; 
    }
};

// DNA sequence
class DNA : public Sequence {
public:
    DNA(const string& d) : Sequence(d) {

    }
    bool isValid() const override {
        for(char c : data) if(c!='A' && c!='C' && c!='G' && c!='T') return false;
        return true;
    }
};

// RNA sequence
class RNA : public Sequence {
public:
    RNA(const string& d) : Sequence(d) {

    }
    bool isValid() const override {
        for(char c : data) if(c!='A' && c!='C' && c!='G' && c!='U') return false;
        return true;
    }
};

// Protein sequence
class Protein : public Sequence {
public:
    Protein(const string& d) : Sequence(d) {

    }
    bool isValid() const override {
        string allowed = "ARNDCQEGHILKMFPSTWYV";
        for(char c : data) if(allowed.find(c) == string::npos) return false;
        return true;
    }
};


// Gene

class Gene {
    DNA dna;
public:
    Gene(const string& seq) : dna(seq) {

    }
    RNA transcribe() const {
        string rna;
        for(char c : dna.getData()) {
            if(c=='A') rna+='U';
            else if(c=='T') rna+='A';
            else if(c=='C') rna+='G';
            else if(c=='G') rna+='C';
        }
        return RNA(rna);
    }
    void print() const { 
        cout << "DNA: "; dna.print(); cout << endl; 
    }
};


// Nucleus

class Nucleus {
    vector<Gene> genes;
public:
    Nucleus(const vector<string>& dnaSeqs) {
        for(const auto& s : dnaSeqs) genes.emplace_back(s);
        cout << "Nucleus created with " << genes.size() << " genes\n";
    }
    vector<RNA> transcribeAll() const {
        vector<RNA> rnas;
        for(const auto& g : genes) {
            RNA r = g.transcribe();
            cout << "Transcribed RNA: "; r.print(); 
            cout << " Valid? " << (r.isValid()?"Yes":"No") << endl;
            rnas.push_back(r);
        }
        return rnas;
    }
    void print() const {
        cout << "Nucleus Genes:\n";
        for(const auto& g : genes) g.print();
    }
};


// Ribosome

class Ribosome {
    vector<Protein> proteins;

    char codonToAA(const string& c) const {
        if(c=="GCU"||c=="GCC"||c=="GCA"||c=="GCG") return 'A';
        if(c=="CGU"||c=="CGC"||c=="CGA"||c=="CGG"||c=="AGA"||c=="AGG") return 'R';
        if(c=="AAU"||c=="AAC") return 'N';
        if(c=="GAU"||c=="GAC") return 'D';
        if(c=="UGU"||c=="UGC") return 'C';
        if(c=="GAA"||c=="GAG") return 'E';
        if(c=="CAA"||c=="CAG") return 'Q';
        if(c=="GGU"||c=="GGC"||c=="GGA"||c=="GGG") return 'G';
        if(c=="CAU"||c=="CAC") return 'H';
        if(c=="AUU"||c=="AUC"||c=="AUA") return 'I';
        if(c=="UUA"||c=="UUG"||c=="CUU"||c=="CUC"||c=="CUA"||c=="CUG") return 'L';
        if(c=="AAA"||c=="AAG") return 'K';
        if(c=="AUG") return 'M';
        if(c=="UUU"||c=="UUC") return 'F';
        if(c=="CCU"||c=="CCC"||c=="CCA"||c=="CCG") return 'P';
        if(c=="UCU"||c=="UCC"||c=="UCA"||c=="UCG"||c=="AGU"||c=="AGC") return 'S';
        if(c=="ACU"||c=="ACC"||c=="ACA"||c=="ACG") return 'T';
        if(c=="UGG") return 'W';
        if(c=="UAU"||c=="UAC") return 'Y';
        if(c=="GUU"||c=="GUC"||c=="GUA"||c=="GUG") return 'V';
        return '?'; 
    }

public:
    void translate(const RNA& rna) {
        string p;
        string s = rna.getData();
        for(size_t i=0;i+2<s.size();i+=3){
            string codon = s.substr(i,3);
            char aa = codonToAA(codon);
            if(aa!='?') p+=aa;  
        }
        Protein protein(p);
        cout << "Produced Protein: "; protein.print(); 
        cout << " Valid? " << (protein.isValid()?"Yes":"No") << endl;
        proteins.push_back(protein);
    }
    void print() const {
        cout << "Ribosome Proteins:\n";
        for(const auto& p : proteins) { 
            cout << "  "; p.print(); cout << endl; 
        }
    }
};


// Cytoplasm

class Cytoplasm {
    vector<Ribosome> ribosomes;
public:
    Cytoplasm(int L) { ribosomes.resize(L); }
    vector<Ribosome>& getRibosomes() { 
        return ribosomes; 
    }
    void print() const { 
        cout << "Cytoplasm Ribosomes:\n";
        for(const auto& r : ribosomes) r.print();
    }
};


// Cell

class Cell {
    Nucleus nucleus;
    Cytoplasm cytoplasm;
public:
    Cell(const vector<string>& dnaSeqs, int L) 
        : nucleus(dnaSeqs), cytoplasm(L) {

        }
    void proteinSynthesis() {
        vector<RNA> rnas = nucleus.transcribeAll();
        int idx = 0;
        auto& ribosomes = cytoplasm.getRibosomes();
        for(const auto& r : rnas){
            ribosomes[idx].translate(r);
            idx = (idx + 1) % ribosomes.size();
        }
    }
    void print() const {
        cout << "--- CELL STATE ---\n";
        nucleus.print();
        cytoplasm.print();
        cout << "-----------------\n";
    }
};


// Main

int main(int argc,char* argv[]){
    if(argc!=4){ cout << "Usage: ./program K L M\n"; return 1; }
    int K = stoi(argv[1]);
    int L = stoi(argv[2]);
    int M = stoi(argv[3]);

    for(int cycle=1; cycle<=M; cycle++){
        cout << "\n=== Cycle " << cycle << " ===\n";
        vector<string> dnaSeqs;
        while(dnaSeqs.size() < size_t(K)){
            string s;
            cout << "Enter DNA sequence: ";
            cin >> s;
            DNA d(s);
            if(d.isValid()) dnaSeqs.push_back(s);
            else cout << "Invalid DNA rejected\n";
        }
        Cell cell(dnaSeqs,L);
        cell.proteinSynthesis();
        cell.print();
    }
}