//============================================================================
// Name        : spacex.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : Ready to rocket
//============================================================================

#include <iostream>
using namespace std;

#include <fstream>
#include <ios>
#include <iostream>
#include <ostream>
#include <sstream>
#include <functional>
#include <initializer_list>
#include <limits>
#include <new>
#include <cctype>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <string>

/*
 * Communication feedback from Derek Bronish:
 *
 * "Some follow-up questions on your approach: why would using a binary search tree for lookups provide worst case O(n) runtime?
 *  What about the requirement to give the output in sorted order, and with a numeric count of each unique gene -- can you describe
 *  how you'll handle that?"
 */

using namespace std;


/*
 * This is the primary data structure to process the input data string.
 * A protein is a string of amino acids.
 */
typedef struct CODON_TABLE_S {
	const int	listIndex;
	const char	*aminoAcidName;
	const int	letter_symbol;
	int			numCondons;
	const char	*codonGroups[6];
	int			codonHash[6];
} CODON_TABLE_T;

const int CT_SIZE = 21;
struct CODON_TABLE_S CT[CT_SIZE] =
{
		{0, "Isoleucine",		'I',	3,	{"ATT", "ATC", "ATA", "", "", ""}, {0,0,0,0,0,0}},
		{1, "Leucine",			'L',	6,	{"CTT", "CTC", "CTA", "CTG", "TTA", "TTG"}, {0,0,0,0,0,0}},
		{2, "Valine",			'V',	4,	{"GTT", "GTC", "GTA", "GTG", "5", "6"}, {0,0,0,0,0,0}},
		{3, "Phenylalanine",	'F',	2,	{"TTT", "TTC", "", "", "", ""}, {0,0,0,0,0,0}},
		{4, "Methionine",		'M',	1,	{"ATG", "", "", "", "", ""}, {0,0,0,0,0,0}},
		{5, "Cysteine",        	'C',	2,	{"TGT", "TGC", "", "", "", ""}, {0,0,0,0,0,0}},
		{6, "Alanine",         	'A',	4,	{"GCT", "GCC", "GCA", "GCG", "", ""}, {0,0,0,0,0,0}},
		{7, "Glycine",         	'G',	4,	{"GGT", "GGC", "GGA", "GGG", "", ""}, {0,0,0,0,0,0}},
		{8, "Proline",         	'P',	4,	{"CCT", "CCC", "CCA", "CCG", "", ""}, {0,0,0,0,0,0}},
		{9, "Threonine",       	'T',	4,	{"ACT", "ACC", "ACA", "ACG", "", ""}, {0,0,0,0,0,0}},
		{10, "Serine",          'S',	6,	{"TCT", "TCC", "TCA", "TCG", "AGT", "AGC"}, {0,0,0,0,0,0}},
		{11, "Tyrosine",        'Y',	2,	{"TAT", "TAC", "", "", "", ""}, {0,0,0,0,0,0}},
		{12, "Tryptophan",		'W',	1,	{"TGG", "", "", "", "", ""}, {0,0,0,0,0,0}},
		{13, "Glutamine",       'Q',	2,	{"CAA", "CAG", "", "", "", ""}, {0,0,0,0,0,0}},
		{14, "Asparagine",      'N',	2,	{"AAT", "AAC", "", "", "", ""}, {0,0,0,0,0,0}},
		{15, "Histidine",       'H',	2,	{"CAT", "CAC", "", "", "", ""}, {0,0,0,0,0,0}},
		{16, "Glutamic acid",   'E',	2,	{"GAA", "GAG", "", "", "", ""}, {0,0,0,0,0,0}},
		{17, "Aspartic acid",   'D',	2,	{"GAT", "GAC", "", "", "", ""}, {0,0,0,0,0,0}},
		{18, "Lysine",          'K',	2,	{"AAA", "AAG", "", "", "", ""}, {0,0,0,0,0,0}},
		{19, "Arginine",        'R',	6,	{"CGT", "CGC", "CGA", "CGG", "AGA", "AGG"}, {0,0,0,0,0,0}},
		//{"Start codon",     '>',	1,	{"ATG", "", "", "", "", ""}, {0,0,0,0,0,0}},
		{20, "Stop codons",     '#',	3,	{"TAA", "TAG", "TGA", "", "", ""}, {0,0,0,0,0,0}},
};

// Questionable variable names is not intentional
// I'm just unfamiliar with DNA nomenclature
typedef struct UNIQUE_GENE_S {
	string aminoAcidSymbols;	// A protein is string of amino acids. This will be the sorting key
	string codonSequence;		// The amino acid string from the start and stop codons
	int sequenceCount;			// How many sequences are found
} UNIQUE_GENE_T;
void createSortedNode(UNIQUE_GENE_T *pug);
void displaySortedList();
void writeSortedList(ofstream& fout);

const int HASH_TABLE_SIZE = 1000;	// rounding up
struct CODON_TABLE_S *CHT[HASH_TABLE_SIZE];
struct CODON_TABLE_S InvalidCodon = {0, "Invalid codon",   '!',	1,	{"XXX", "", "", "", "", ""}, {0,0,0,0,0,0}};

int AsciiArray[26];
const int ASCII_A_VAL=65;

/* */
struct CODON_TABLE_S *hashIndexToCodonTable(int hashIndex)
{
	if(hashIndex >= HASH_TABLE_SIZE || hashIndex < 0) {
		cout << endl << "Invalid hash lookup index " << hashIndex << endl;
		return CHT[HASH_TABLE_SIZE - 1];
	}
	return CHT[hashIndex];
}

/* */
int codonToHashIndex(const char *pCodon)
{
	int hashIndex = 0;
	int index = 0;
	int msval = 0;
	if(pCodon == nullptr)
	{
		return (-1);
	}
	// Convoluted for a reason - to debug output.  This could be refactored
	index = (int) pCodon[0] - ASCII_A_VAL;
	msval = AsciiArray[index];
	hashIndex = msval << 8;
	index = (int) pCodon[1] - ASCII_A_VAL;
	int midval = AsciiArray[index];
	hashIndex |= midval << 4;
	index = (int) pCodon[2] - ASCII_A_VAL;
	int lsval = AsciiArray[index];
	hashIndex |= lsval;

	if(hashIndex < 0 || hashIndex >= HASH_TABLE_SIZE ) {
		return (-1);
	}
	return hashIndex;
}

/* */
char *hashIndexToCodon(int hashIndex)
{
	char *pcon = new char[4];
	int asciiOffset[3]  = {((hashIndex >> 8) & 0xF), ((hashIndex >> 4) & 0xF), (hashIndex & 0xF)};
	const char hashToAscii[] = {'A', 'C', 'G', 'T'};
	pcon[0] = hashToAscii[asciiOffset[0]];
	pcon[1] = hashToAscii[asciiOffset[1]];
	pcon[2] = hashToAscii[asciiOffset[2]];
	pcon[3] = 0;
	return pcon;
}

/* */
void initCodonHashTable()
{
	CODON_TABLE_T *pcht;
	int hashVal = 0;

	// setup a smaller hash table by using only valid DNA letters
	// the largest hash index will be TTT, which will correspond to 0x0333 or 819
	fill( AsciiArray, AsciiArray + sizeof( AsciiArray ), 0 );
	AsciiArray[0] = 0;		// A
	AsciiArray[2] = 1;		// C
	AsciiArray[6] = 2;		// G
	AsciiArray[19] = 3;		// T

	for(int h=0; h<HASH_TABLE_SIZE; h++) {
		// initialize to invalid
		pcht = &InvalidCodon;
		CHT[h] = pcht;
	}

	for(int i=0; i <CT_SIZE; i++) {
		pcht = &CT[i];
		for(int j=0; j<pcht->numCondons; j++) {
			const char *pCodon = pcht->codonGroups[j];
			hashVal = codonToHashIndex(pCodon);


			pcht->codonHash[j] = hashVal;
			CHT[hashVal] = pcht;
		}
	}
}

/* */
bool isStartCodon(char *p)
{
	if( strcmp(p,"ATG") == 0 )
		return true;
	return false;
}

/* */
bool isStopCodon(char *p)
{
	if( (strcmp(p,"TAA") == 0 ) ||
		(strcmp(p,"TAG") == 0 ) ||
		(strcmp(p,"TGA") == 0 ) )
		return true;
	return false;
}

/* */
bool isValidCodonChar(int c) {

	if(!isalpha(c))
		return false;
	switch(tolower(c)) {
	case 'a':
	case 'g':
	case 't':
	case 'c':
		return true;
	default:
		return false;
	}
}

/* */
int initTest() {
    for(int i=0; i <CT_SIZE; i++) {
    	CODON_TABLE_T *pctInit = &CT[i];

    	for(int n=0; n<6; n++) {
    		int testIndex = codonToHashIndex(pctInit->codonGroups[n]);
    		//printf("Found hash index %d\n", hashIndex);
    		if(testIndex != (-1)) {
    			CODON_TABLE_T *pctHashLookup = hashIndexToCodonTable(testIndex);
    			printf("Codon %s, protein %s, symbol %c, maps to hash index %d, list index %d\n",
    				pctHashLookup->codonGroups[n], pctHashLookup->aminoAcidName,
					pctHashLookup->letter_symbol, testIndex, pctHashLookup->listIndex);
    		}
    	}
    }
    return 0;
}

/* */
int main(int argc, char* argv[]) {
	initCodonHashTable();

    /*
     * Verify init
     */
    //initTest();

//#define OUTPUT_TEST
#ifdef OUTPUT_TEST
	// Only one input argument found. No output file specified.
	//cout << "arg = " << argc << endl;
	//cout << "argv[1] = " << argv[1] << endl;
	ofstream ftestout;
	// Open a test file and truncate the data for new output data
	ftestout.open("input.txt", ios::out | ios::trunc);
	if(ftestout.is_open()) {
		ftestout << "aca aca gaa atg atg aaa taa atg caa tag" << endl;
		ftestout << endl;
		ftestout << "atgcagtag" << endl;
		ftestout << "A;   Ttttttttttttt A, t." << endl;
		ftestout << "Gcagtagggggggatatat" << endl;
		ftestout << "atatgatgaaat" << endl;
		ftestout.close();
	}
#endif
	string filename;

	if(argc > 1) {
		filename = argv[1];
	}
	else {
		filename = "input.txt";
	}
	ifstream ifile(filename);

	if(ifile.fail()) {
		cout << "Unable to open file " << filename << endl;
		return -1;
	}

	char c;
	int codonCounter = 0;
	string codonCharData;
	while((ifile.get(c), ifile.eof()) == false) {
		if(isValidCodonChar((int)c)) {
			codonCharData += toupper(c);
		}
	}
	ifile.close();

	// No access to problem info. Default to a negative return, no error output.
	if(codonCharData.length() < 3) {
		return (-1);
	}

	/* */
	// cout << "Reading file found " << codonCharData.length() << " characters" << endl;
	// cout << "Parsed input data: " << codonCharData << endl;
	CODON_TABLE_T *pct;
	int dataCounter=0;
	int endOfSequence = 0;
	do {
		// look for a valid start sequence
		size_t atgOffset = codonCharData.find("ATG", dataCounter);
		if(atgOffset == codonCharData.npos) {
			break;
		}
		dataCounter = atgOffset;

		// look for a valid stop sequence
		atgOffset = codonCharData.find("TAA", dataCounter);
		if(atgOffset == codonCharData.npos) {
			atgOffset = codonCharData.find("TAG", dataCounter);
			if(atgOffset == codonCharData.npos) {
				atgOffset = codonCharData.find("TGA", dataCounter);
					break;
			}
		}
		endOfSequence = atgOffset+3;

		// Ugh.  The use of subst here create a copy of the gene substring.  I would prefer to refactor the code and use string_view.
		// Otherwise my design plan is to use a single pass of the data.
		UNIQUE_GENE_T *pug = new UNIQUE_GENE_T;		// create on the heap to reduce risk to stack usage
		pug->codonSequence = codonCharData.substr(dataCounter, endOfSequence-dataCounter);
		//printf("Gene sequence [%d - %d]: %s\n", dataCounter, endOfSequence, pug->codonSequence.c_str());
		codonCounter = 0;

		// testing which method may be better, string or cstring
		string codon_string;
		codon_string.assign(codonCharData, atgOffset, 3);
		char codon[4];

		// At this point a major assumption is being made.
		// The data is valid until the stop sequence is encountered.
		// If this assumption is not correct, then more work (and time)
		// is needed to verify the codons between the detected start
		// codons.  We know that a valid start and stop sequence frames
		// a string length.  If the length is incorrect or bogus sequences
		// are included, then at minimum how should I store a sequence
		// with only a start and stop sequence? The hash lookup on the
		// codon string will skip over invalid 3 character conditions,
		// but what if a codon string can be read two different ways
		// within the same string?  ATG CATA TAG. That is my reasoning
		// for the assumption that finding a condition of a valid start
		// and stop sequence verifies the codon data within is valid.
		do {  // stop sequence not yet found
			codonCharData.copy(codon, 3, dataCounter);

			int hashIndex = codonToHashIndex(codon);
			if(hashIndex != (-1)) {
				pct = hashIndexToCodonTable(hashIndex);
				codonCounter++;
				//printf("Found '%c' codon[%d] %s, protein %s with hash index %d\n", pct->letter_symbol, codonCounter, codon, pct->aminoAcidName, hashIndex);
				char codonSymbol = pct->letter_symbol;


				if(isStopCodon(codon)) {
					// After the stop sequence the data is invalid until the next start sequence
					break;
				}
				else if(codonCounter > 1) {
					pug->aminoAcidSymbols += codonSymbol;
				}
				dataCounter+=3;
			}
		} while(dataCounter < endOfSequence);

		createSortedNode(pug);

		delete pug;

	} while(dataCounter < (int) codonCharData.length()-3);


	displaySortedList();

	// Prepare for output file
	ofstream fout;

	// Open a test file and truncate the data for new output data
	fout.open("output.txt", ios::out | ios::trunc);
	if(!fout.is_open()) {
		return -2;
	}
	writeSortedList(fout);

	fout.close();


	return 0;
}

struct SortedListNode {
   UNIQUE_GENE_T unique_gene;

   SortedListNode *next;

} *p = nullptr, *head = nullptr, *q = nullptr, *np = nullptr;

bool slnNodeLessThan(SortedListNode *sln_np, SortedListNode *sln_p) {
	return((sln_np->unique_gene.aminoAcidSymbols < sln_p->unique_gene.aminoAcidSymbols) ||
			(sln_np->unique_gene.codonSequence < sln_p->unique_gene.codonSequence));
}
bool slnNodeGreaterThan(SortedListNode *sln_np, SortedListNode *sln_p) {
	return((sln_np->unique_gene.aminoAcidSymbols > sln_p->unique_gene.aminoAcidSymbols) ||
			(sln_np->unique_gene.codonSequence > sln_p->unique_gene.codonSequence));
}
bool slnNodeEqualTo(SortedListNode *sln_np, SortedListNode *sln_p) {
	return((sln_np->unique_gene.aminoAcidSymbols == sln_p->unique_gene.aminoAcidSymbols) &&
			(sln_np->unique_gene.codonSequence == sln_p->unique_gene.codonSequence));
}

/* Simple, but easy to create a bug */
void createSortedNode(UNIQUE_GENE_T *pug) {
	np = new SortedListNode;
//	printf("Storing %s - %s\n", pug->aminoAcidSymbols.c_str(), pug->codonSequence.c_str());
	np->unique_gene.aminoAcidSymbols = pug->aminoAcidSymbols;
	np->unique_gene.codonSequence = pug->codonSequence;
	np->unique_gene.sequenceCount = 1;
	np->next = nullptr;

	if(head == nullptr) {
		head = np;
	}
	else {
		p = head;
		// if equal just increment
		if (p && slnNodeEqualTo(np, p)) {
			p->unique_gene.sequenceCount++;
			delete np;
			return;
		}
		else {
			// find a spot down the line
			while(p) {
				if(slnNodeGreaterThan(np, p)) {
					q = p;
					p = p->next;
				}
				else if (p && slnNodeEqualTo(np, p)) {
					p->unique_gene.sequenceCount++;
					delete np;
					return;
				}
				if(p && slnNodeLessThan(np, p)) {
					break;
				}
			}
			if (p && slnNodeEqualTo(np, p)) {
				p->unique_gene.sequenceCount++;
				delete np;
				return;
			}
			if(p == head) {
				np->next = head;
				head = np;
			}
			else {
				// insert between q and p
				np->next = q->next;
				q->next = np;
			}
		}
	}

}

void writeSortedList(ofstream& fout) {
   SortedListNode *sln = head;
   string lastSymbols;
   while (sln != nullptr ) {
	   if(lastSymbols != sln->unique_gene.aminoAcidSymbols)
		   fout << sln->unique_gene.aminoAcidSymbols << endl;
	   fout << "  " << sln->unique_gene.codonSequence << " ";
	   fout << sln->unique_gene.sequenceCount << endl;
	   lastSymbols = sln->unique_gene.aminoAcidSymbols;
	   sln = sln->next;
   }
}

/* */
void displaySortedList() {
   SortedListNode *sln = head;
   string lastSymbols;
   while (sln != nullptr) {
	   if(lastSymbols != sln->unique_gene.aminoAcidSymbols)
		   cout << sln->unique_gene.aminoAcidSymbols << endl;
	   cout << "  " << sln->unique_gene.codonSequence << " ";
	   cout << sln->unique_gene.sequenceCount << endl;
	   lastSymbols = sln->unique_gene.aminoAcidSymbols;
	   sln = sln->next;
   }
}
