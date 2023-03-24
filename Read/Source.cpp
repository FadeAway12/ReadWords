#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <string>
#include <string_view>

using namespace std;

struct Word {
	Word(int p, string wo) {
		pos = p;
		w = wo;
	}
	int pos;
	string w;
};

class bookStream {
public:
	bookStream(string fileName, int s, int e, initializer_list<string> wrds){ 
		f.open(fileName);
		lnSt = s;
		lnEn = e;
		currentLine = 0;
		for (string s : wrds) {
			for (int i = 0; i < s.size(); i++) {
				s[i] = tolower(s[i]);
			}
			words.push_back(s);
		}
	}
	void exclude(initializer_list<string> wrds) {
		for (string s : wrds) excluded.push_back(s);
	}
	void open(string file) {
		f.open(file);
	}
	vector<Word> getWords() {
		while (currentLine < lnSt-1) {
			string k;
			getline(f, k);
			currentLine++;
		}
		while (currentLine < lnEn-1) {
			string line;
			getline(f, line);
			currentLine++;
			istringstream is{ line };
			for (string s; is >> s;) {
				string final;
				istringstream ist{ s };
				for (char ch; ist >> ch;) {
					if (ch == 'á') ch = 'a';
					if (ch == 'é') ch = 'e';
					if (ch == 'ñ') ch = 'n';
					if (ch == 'í') ch = 'i';
					if (ch == 'ó') ch = 'o';
					if (ch == 'ú') ch = 'u';
					if (ch == 'À') ch = 'a';
					if (ch == 'É') ch = 'e';
					if (ch == 'Ñ') ch = 'n';
					if (ch == 'Í') ch = 'i';
					if (ch == 'Ó') ch = 'o';
					if (ch == 'Ú') ch = 'u';
					if (ch == '¿' || ch == '¡' || ch == '—') continue;
					ch = abs(ch);
					if (isalpha(ch)) {
						ch = tolower(ch);
						final += ch;
					}
				}
				for (string word : words) {
					if (final.find(word) != string::npos || final == word) {
						bool ex{};
						for (string exc : excluded) {
							if (exc == final) ex = true;
						}
						if (!ex) wordsFound.push_back(Word(currentLine, final));
					}
				}
			}
		}
		return wordsFound;
	}
	istream& operator>>(string& s) {
		if (!f) return f;
		string str;
		f >> str;
		istringstream is{str};
		string final;
		for (char ch; is >> ch;) {
			//if (ch == '!'  || ch == '?' || ch == '¿' || ch == ';' || ch == '(' || ch == ')')
			ch = tolower(ch);
			if (ch == 'á') ch = 'a';
			if (ch == 'ñ') ch = 'n';
			if (ch == 'í') ch = 'i';
			if (ch == 'ó') ch = 'o';
			if (ch == 'ú') ch = 'u';
			if (isalpha(ch)) final += ch;
		}
		s = final;
		return f;
	}
	int getLnSt() { return lnSt; }
private:
	ifstream f;
	vector<string> words;
	vector<string> excluded;
	vector<Word> wordsFound;
	int lnSt;
	int lnEn;
	int currentLine;
};

vector<Word> operator+ (vector<Word> v1, vector<Word>v2) {
	for (int i = 0; i < v2.size(); i++) {
		v1.push_back(v2[i]);
	}
	return v1;
}

int main() {

	bookStream C1("Text.txt", 13, 27, { "aunque", "capa", "cuenta", "deb", "dej", "buho", "moto", "parec", "raro", "rara", "embargo",
		"taladro"});

	bookStream C2("Text.txt", 28, 39, { "advi", "adve", "aquel", "alacena", "desapar", "desvan", "escalera", "grit", "guin", "odi", "peg",
		"sobrino", "quej", "vidrio"});

	bookStream C3("Text.txt", 40, 53, { "buzon", "choza", "cog", "correo", "prisa", "divertid", "guard", "juguete", "pergamino", "decir", "tapar"});

	bookStream C4("Text.txt", 54, 66, { "bruja", "disculp", "equivocado", "hechizo", "lado oscuro", "mago", "mundo", "rio", "ries", "rie", "rei",
		"rind", "rendimos", "rendis", "rend", "rostro", "sobrev", "sonr", "tem", "varita"});

	C4.exclude({ "abrio" });

	bookStream C5("Text.txt", 67, 90, { "acab", "asignatura", "callejon", "camara", "cicatriz", "consejo", "contra", "duende", "elige", "elijo", "eleg",
		"elij", "escoba", "preocupes", "periodico", "seguro"});

	bookStream C6("Text.txt", 91, 113, {"anden", "baul", "castillo", "deprim", "derrot", "encont", "encuent", "gemel", "grande", "grun", "oscuro",
		"sapo", "teneb", "razon"});
	
	C6.exclude({ "corazon" });

	vector<Word> words = C1.getWords() + C2.getWords() + C3.getWords() + C4.getWords() + C5.getWords() + C6.getWords();

	ofstream os{ "Text1.txt" };

	for (Word w : words) {
		os << w.pos;
		os << " " << w.w;
		os << endl;
	}


}