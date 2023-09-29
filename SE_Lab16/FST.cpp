#include"stdafx.h";

using namespace std;

FST::RELATION::RELATION(char c, short ns)
{
	this->symbol = c;
	this->nnode = ns;
}

FST::NODE::NODE(short n, RELATION rel, ...) {
	n_relation = n;
	RELATION* p = &rel;
	relations = new RELATION[n];
	for (int i = 0; i < n; i++)
	{
		relations[i] = p[i];
	}
}

FST::NODE::NODE() {
	this->n_relation = 0;
	relations = NULL;
}

FST::FST::FST(const char* s, short ns, NODE n, ...) {
	this->string = s;
	this->nstates = ns;
	this->nodes = new NODE[ns];
	NODE* p = &n;
	for (int i = 0; i < ns; i++)
	{
		nodes[i] = p[i];
	}
	rstates = new short[nstates];
	memset(rstates, 0xff, sizeof(short) * nstates);
	rstates[0] = 0;
	position = -1;
}



bool FST::step(FST& fst, short*& rstates)
{
	bool rc = false;
	std::swap(rstates, fst.rstates);
	for (short i = 0; i < fst.nstates; i++)
	{
		if (rstates[i] == fst.position)
		{
			for (short j = 0; j < fst.nodes[i].n_relation; j++)
			{
				if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
				{
					fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
					rc = true;
				}
			}
		}
	}

	return rc;
}

bool FST::execute(FST& fst)
{
	short* rstates = new short[fst.nstates];
	memset(rstates, 0xff, sizeof(short) * fst.nstates);
	bool lstring = strlen(fst.string);
	bool rc = true;
	for (short i = 0; i < lstring && rc ; i++)
	{
		fst.position++;
		rc = step(fst, rstates);
	}
	delete[] rstates;
	return rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc;
}


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	FST::FST fst1(
		"aaabbbaba",
		4,
		FST::NODE(3, FST::RELATION('a', 0), FST::RELATION('b', 0), FST::RELATION('a', 1)),
		FST::NODE(1, FST::RELATION('b', 2)),
		FST::NODE(1, FST::RELATION('a', 3)),
		FST::NODE()
		);

	if (FST::execute(fst1))
	{
		cout << "Цепочка " << fst1.string << " распознана" << endl;
	}
	else
	{
		cout << "Цепочка " << fst1.string << " не распознана" << endl;
	}

	FST::FST fst2(
		"aaabbbabba",
		4,
		FST::NODE(3, FST::RELATION('a', 0), FST::RELATION('b', 0), FST::RELATION('a', 1)),
		FST::NODE(1, FST::RELATION('b', 2)),
		FST::NODE(1, FST::RELATION('a', 3)),
		FST::NODE()
	);

	if (FST::execute(fst2))
	{
		cout << "Цепочка " << fst2.string << " распознана" << endl;
	}
	else
	{
		cout << "Цепочка " << fst2.string << " не распознана" << endl;
	}

	// 1
	
	FST::RELATION rel1('a', 1); 
	FST::RELATION rel2('b', 2); 

	FST::NODE state1(1, rel1); 
	FST::NODE state2(1, rel2); 

	FST::FST myFST("ab", 2, state1, state2); 

	const char* strings[] = { "ab", "aabb", "aaaab", "bbb", "a", "b", "abab" };

	for (int i = 0; i < 7; i++) {
		myFST.position = -1;
		myFST.string = strings[i];
		bool result = execute(myFST);

		if (result) {
			std::cout << "Цепочка " << strings[i] << " распознана!" << std::endl;
		}
		else {
			std::cout << "Цепочка " << strings[i] << " не распознана!" << std::endl;
		}
	}
	// 2

	const char* inputString = "acb";

	myFST.position = -1; 
	myFST.string = inputString;
	bool result = execute(myFST);

	if (result) {
		std::cout << "Цепочка " << myFST.string << " распознана!" << std::endl;
	}
	else {
		std::cout << "Цепочка " << myFST.string << " не распознана!" << std::endl;
	}


	inputString = "abb";

	myFST.position = -1;
	myFST.string = inputString;
	result = execute(myFST);

	if (result) {
		std::cout << "Цепочка " << myFST.string << " распознана!" << std::endl;
	}
	else {
		std::cout << "Цепочка " << myFST.string << " не распознана!" << std::endl;
	}

	FST::RELATION r1('1', 1); 
	FST::RELATION r2('4', 2); 
	FST::RELATION r3('3', 3);

	FST::NODE stat1(2, r1,r2); 
	FST::NODE stat2(2, r1,r2); 
	FST::NODE stat3(2, r1,r2);

	const char* inputString2 = "143";

	FST::FST FST413(inputString, 3, stat1, stat2, stat3); 

	FST413.position = -1;
	FST413.string = inputString2;
	bool result1 = execute(FST413);

	if (result1) {
		cout << "Цепочка " << inputString2 << " распознана!" << endl;
	}
	else {
		cout << "Цепочка " << inputString2 << " не распознана!" << endl;
	}

	return 0;

}

