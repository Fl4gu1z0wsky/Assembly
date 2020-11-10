//-------------------
//      ch02.cpp
//-------------------

#include <iostream> //ch02_01
#include <iomanip> //ch02_02
#include <bitset> //ch02_03

using namespace std;

//---ch02_01------------------------

extern "C" int IntegerAddSub_(int a, int b, int c, int d);

static void PrintResultOne(const char* msg, int a, int b, int c, int d, int result)
{
	const char nl = '\n';

	cout << msg << nl;
	cout << "a = " << a << nl;
	cout << "b = " << b << nl;
	cout << "c = " << c << nl;
	cout << "d = " << d << nl;
	cout << "result = " << result << nl;
	cout << nl;
}

//---ch02_01------------------------

//---ch02_02------------------------

extern "C" unsigned int IntegerLogical_(unsigned int a, unsigned int b, unsigned int c,
	unsigned int d);

// Global value from assembly
extern "C" unsigned int g_Val1 = 0;

unsigned int IntegerLogicalCpp(unsigned int a, unsigned int b, unsigned int c,
	unsigned int d)
{
	// Calculate (((a & b) | c ) ^d) + g_Val1
	unsigned int t1 = a & b;
	unsigned int t2 = t1 | c;
	unsigned int t3 = t2 ^ d;
	unsigned int result = t3 + g_Val1;

	return result;
}

void PrintResultTwo(const char* s, unsigned int a, unsigned int b, unsigned int c,
	unsigned int d, unsigned val1, unsigned int r1, unsigned int r2)
{
	const int w = 8;
	const char nl = '\n';

	cout << s << nl;
	cout << setfill('0');
	cout << "a = 0x" << hex << setw(w) << a << " (" << dec << a << ")" << nl;
	cout << "b = 0x" << hex << setw(w) << b << " (" << dec << b << ")" << nl;
	cout << "c = 0x" << hex << setw(w) << c << " (" << dec << c << ")" << nl;
	cout << "d = 0x" << hex << setw(w) << d << " (" << dec << d << ")" << nl;
	cout << "val1 = 0x" << hex << setw(w) << val1 << " (" << dec << val1 << ")" << nl;
	cout << "r1 = 0x" << hex << setw(w) << r1 << " (" << dec << r1 << ")" << nl;
	cout << "r2 = 0x" << hex << setw(w) << r2 << " (" << dec << r2 << ")" << nl;
	cout << nl;

	if (r1 != r2)
		cout << "Compare failed" << nl;
}

//---ch02_02------------------------

//---ch02_03------------------------

extern "C" int IntegerShift_(unsigned int a, unsigned int count, unsigned int* a_shl,
	unsigned int* a_shr);

static void PrintResultThree(const char* s, int rc, unsigned int a, unsigned int count, unsigned
	int a_shl, unsigned int a_shr)
{
	bitset<32> a_bs(a);
	bitset<32> a_shl_bs(a_shl);
	bitset<32> a_shr_bs(a_shr);
	const int w = 10;
	const char nl = '\n';

	cout << s << '\n';
	cout << "count = " << setw(w) << count << nl;
	cout << "a = " << setw(w) << a << " (0b" << a_bs << ")" << nl;

	if (rc == 0)
		cout << "Invalid shift count" << nl;
	else
	{
		cout << "shl = " << setw(w) << a_shl << " (0b" << a_shl_bs << ")" << nl;
		cout << "shr = " << setw(w) << a_shr << " (0b" << a_shr_bs << ")" << nl;
	}
	cout << nl;
}

//---ch02_03------------------------

//---ch02_04------------------------

extern "C" int IntegerMulDiv_(int a, int b, int* prod, int* quo, int* rem);

void PrintResult(const char* s, int rc, int a, int b, int p, int q, int r)
{
	const char nl = '\n';
	cout << s << nl;
	cout << "a = " << a << ", b = " << b << ", rc = " << rc << nl;
	if (rc != 0)
		cout << "prod = " << p << ", quo = " << q << ", rem = " << r << nl;
	else
		cout << "prod = " << p << ", quo = undefined" << ", rem = undefined" << nl;
	cout << nl;
}

//---ch02_04------------------------

int main()
{
	//---ch02_01------------------------

	cout << "---ch02_01------------------------\n\n";
	
	int a, b, c, d, result;

	a = 10; b = 20; c = 30; d = 18;
	result = IntegerAddSub_(a, b, c, d);
	PrintResultOne("Test 1", a, b, c, d, result);

	a = 101; b = 34; c = -190; d = 25;
	result = IntegerAddSub_(a, b, c, d);
	PrintResultOne("Test 2", a, b, c, d, result);

	//---ch02_01------------------------

	//---ch02_02------------------------

	cout << "---ch02_02------------------------\n\n";

	unsigned int e, f, g, h, r1, r2 = 0;
	e = 0x00223344;
	f = 0x00775544;
	g = 0x00555555;
	h = 0x00998877;
	g_Val1 = 7;
	r1 = IntegerLogicalCpp(e, f, g, h);
	r2 = IntegerLogical_(e, f, g, h);
	PrintResultTwo("Test 1", e, f, g, h, g_Val1, r1, r2);
	
	e = 0x70987655;
	f = 0x55555555;
	g = 0xAAAAAAAA;
	h = 0x12345678;
	g_Val1 = 23;
	r1 = IntegerLogicalCpp(e, f, g, h);
	r2 = IntegerLogical_(e, f, g, h);
	PrintResultTwo("Test 2", e, f, g, h, g_Val1, r1, r2);

	//---ch02_02------------------------

	//---ch02_03------------------------

	cout << "---ch02_03------------------------\n\n";

	int rc;
	unsigned int k, count, a_shl, a_shr;

	k = 3119;
	count = 6;
	rc = IntegerShift_(k, count, &a_shl, &a_shr);
	PrintResultThree("Test 1", rc, k, count, a_shl, a_shr);

	k = 0x00800080;
	count = 4;
	rc = IntegerShift_(k, count, &a_shl, &a_shr);
	PrintResultThree("Test 2", rc, k, count, a_shl, a_shr);

	k = 0x80000001;
	count = 31;
	rc = IntegerShift_(k, count, &a_shl, &a_shr);
	PrintResultThree("Test 3", rc, k, count, a_shl, a_shr);

	k = 0x55555555;
	count = 32;
	rc = IntegerShift_(k, count, &a_shl, &a_shr);
	PrintResultThree("Test 4", rc, k, count, a_shl, a_shr);

	//---ch02_03------------------------

	//---ch02_04------------------------

	cout << "---ch02_04------------------------\n\n";

	int l, m;
	int prod, quo, rem;

	l = 47;
	m = 13;
	prod = quo = rem = 0;
	rc = IntegerMulDiv_(l, m, &prod, &quo, &rem);
	PrintResult("Test 1", rc, l, m, prod, quo, rem);

	l = -291;
	m = 7;
	prod = quo = rem = 0;
	rc = IntegerMulDiv_(l, m, &prod, &quo, &rem);
	PrintResult("Test 2", rc, l, m, prod, quo, rem);

	l = 19;
	m = 0;
	prod = quo = rem = 0;
	rc = IntegerMulDiv_(l, m, &prod, &quo, &rem);
	PrintResult("Test 3", rc, l, m, prod, quo, rem);

	l = 247;
	m = 85;
	prod = quo = rem = 0;
	rc = IntegerMulDiv_(l, m, &prod, &quo, &rem);
	PrintResult("Test 4", rc, l, m, prod, quo, rem);

	//---ch02_04------------------------

	return 0;
}