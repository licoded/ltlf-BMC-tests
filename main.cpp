#include <cstring>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <sys/time.h>

#include "formula/aalta_formula.h"
#include "xnf.h"

using namespace aalta;
using namespace std;

void usage()
{
	cout
		<< "Usage: ./ltlfsyn-bmc <ltlf_file> <part_file>" << endl
		<< "        Example: ./ltlfsyn-bmc example.ltlf example.part" << endl;
}

void test1()
{
	cout << "test case 1" << endl;
	string input_f = string("a U b");

	aalta_formula *f;
	f = aalta_formula::TAIL();
	aalta_formula::TRUE();
	aalta_formula::FALSE();
	cout << "src input formula: " << input_f << endl;
	f = aalta_formula(input_f.c_str(), true).unique();
	f = f->nnf();
	f = f->add_tail();
	f = f->remove_wnext();
	f = f->simplify();
	f = f->split_next();
	cout << "construct checker formula:" << f->to_string() << endl;
}

int main(int argc, char **argv)
{
	// test1();
	// return 0;

	string input_f;
	int k;
	cout << "Please input formula:\n";
	getline(cin, input_f);
	cout << "Please input bounded-k:\n";
	cin >> k;

	clock_t startTime, endTime;
	startTime = clock();
	struct timeval t1, t2;
	double timeuse;
	gettimeofday(&t1, NULL);

	// rewrite formula
	aalta_formula *af;
	// set tail id to be 1
	af = aalta_formula::TAIL();
	aalta_formula::TRUE();
	aalta_formula::FALSE();
	af = aalta_formula(input_f.c_str(), true).nnf();
	af = af->simplify();
	af = af->split_next();
	af = af->unique();

	const char *verboseStr = getenv("VERBOSE");
    int verbose = false;
	if (verboseStr != NULL && strlen(verboseStr) > 0)
		verbose = stoi(verboseStr);

	cout << "==== before xnf:\t" << af->to_string() << endl;

	af = xnf::xnf(af, k);

	cout << "==== after  xnf:\t" << af->to_string() << endl;

	aalta_formula::destroy();

	gettimeofday(&t2, NULL);
	endTime = clock();
	timeuse = (t2.tv_sec - t1.tv_sec) * 1000000 + t2.tv_usec - t1.tv_usec;
	cout << "CPU time: " << 1000 * double(endTime - startTime) / CLOCKS_PER_SEC << " ms" << endl;
	cout << "total time: " << timeuse / 1000.0 << " ms" << endl;

	return 0;
}