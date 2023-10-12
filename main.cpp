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

	if (argc != 3)
	{
		usage();
		exit(0);
	}

	// read formula
	ifstream fin;
	fin.open(argv[1], ios::in);
	if (!fin.is_open())
	{
		cout << "cannot open file " << argv[1] << endl;
		return 0;
	}
	string input_f, tmp;
	unordered_set<string> env_var;
	getline(fin, input_f);
	fin.close();
	// === read formula END ===

	// read variables partition
	fin.open(argv[2], ios::in);
	if (!fin.is_open())
	{
		cout << "cannot open file " << argv[2] << endl;
		return 0;
	}
	fin >> tmp;
	while (fin >> tmp)
	{
		if (tmp[0] != '.')
			env_var.insert(tmp);
		else
			break;
	}
	fin.close();
	// === read variables partition END ===

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

	af = xnf::xnf0(af);

	// TODO: perform synthesis
	cout << af->to_string() << endl;

	aalta_formula::destroy();

	gettimeofday(&t2, NULL);
	endTime = clock();
	timeuse = (t2.tv_sec - t1.tv_sec) * 1000000 + t2.tv_usec - t1.tv_usec;
	cout << "CPU time: " << 1000 * double(endTime - startTime) / CLOCKS_PER_SEC << " ms" << endl;
	cout << "total time: " << timeuse / 1000.0 << " ms" << endl;

	return 0;
}