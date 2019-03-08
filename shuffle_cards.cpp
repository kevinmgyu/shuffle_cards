#include "shuffle_cards.h"
using namespace std;
using namespace fc;
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */

/* initializes mt[N] with a seed */
void init_genrand(unsigned long s)
{
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<N; mti++) {
        mt[mti] = 
	    (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti); 
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void init_by_array(unsigned long init_key[], int key_length)
{
    int i, j, k;
    init_genrand(19650218UL);
    i=1; j=0;
    k = (N>key_length ? N : key_length);
    for (; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
          + init_key[j] + j; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++; j++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=N-1; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
          - i; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
    }

    mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */ 
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* generate N words at one time */
        int kk;

        if (mti == N+1)   /* if init_genrand() has not been called, */
            init_genrand(5489UL); /* a default initial seed is used */

        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }
  
    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

short genrand_short(void) {
    return (short)(genrand_int32()>>16);
}

/* generates a random number on [0,0x7fffffff]-interval */
long genrand_int31(void)
{
    return (long)(genrand_int32()>>1);
}

/* generates a random number on [0,1]-real-interval */
double genrand_real1(void)
{
    return genrand_int32()*(1.0/4294967295.0); 
    /* divided by 2^32-1 */ 
}

/* generates a random number on [0,1)-real-interval */
double genrand_real2(void)
{
    return genrand_int32()*(1.0/4294967296.0); 
    /* divided by 2^32 */
}

/* generates a random number on (0,1)-real-interval */
double genrand_real3(void)
{
    return (((double)genrand_int32()) + 0.5)*(1.0/4294967296.0); 
    /* divided by 2^32 */
}

/* generates a random number on [0,1) with 53-bit resolution*/
double genrand_res53(void) 
{ 
    unsigned long a=genrand_int32()>>5, b=genrand_int32()>>6; 
    return(a*67108864.0+b)*(1.0/9007199254740992.0); 
}
string generate_seed()
{
        /* Decleration and initialization of static constant string type variable */
        const string charList = "0123456789abcdef";

        /* srand() initialize random number generator */
        /* time() for get current time */
        srand(time(0));
		string  result ="";
        for(int i = 0; i < 40; i++) {
                /* rand() generate random number */
              result += charList [rand() % charList.size()];
        }
	return result;

}
uint32_t mersennetwister(const string&  sha) {

    unsigned long init[8];

    for (size_t  s = 0; s < 8; s++) {
        unsigned long v = 0;

        string ss = sha.substr(s*8 , 8);
        sscanf(ss.c_str(),"%lx",&v);
     
        init[s] = v;
	}

    init_by_array(init, 8);

    //return genrand_short();

    return genrand_short();
}


string get_sha256(const string&  t) {
    int len = t.size() / 2;
    char a[len];
    from_hex(t,a, len);
    //cout << len1 << endl;

    vector<uint8_t> c;
    for( size_t i = 0; i < len; ++i) {
        c.push_back(a[i]);
    }

    sha256::encoder e;
    e.write(c.data(),c.size());

    //vector<uint8_t> d  = sha2561(c);
    //cout << "random " << to_hex1(d.data(),d.size()) << endl;
    string res = e.result().str();
    //cout << "random " << res << endl;

    return res;
}

/*
 * example input-output:
 * ee1771173466cfe0cfebba93148e4fb787fe8a538e0f6d98047d9ad68e15f8ea
 * 
 */
 
struct test_data {
    
    uint16_t n;
	uint32_t r;

};


bool compare(const test_data& x,const test_data& y)
{
	if(x.r == y.r)
		return x.n < y.n;
	else
		return x.r < y.r;
}
void shuffle_cards(vector<int> &desk_cards,string &seed,int card_num)
{
	desk_cards.clear();
	vector<test_data> cards;
	string tmp = seed;
	string test_sha256;
	for (int i=1;i<card_num+1;++i)
        {
                test_sha256 = get_sha256(tmp);
                uint32_t r = mersennetwister(test_sha256);
		tmp = test_sha256;
                test_data t1 ;
                t1.n = i;
                t1.r = r;
                cards.push_back(t1);
        }
	std::sort (cards.begin(), cards.end(), compare);
	for(std::vector<test_data>::iterator it=cards.begin();it!=cards.end();it++)
        {
        	desk_cards.push_back((*it).n);
        }
	
	
}

/*int main(int argc, char** argv) {
	FILE *fp = fopen("result", "a+");

	fc::ecc::private_key priv = fc::ecc::private_key::generate();
	fc::sha256 secret = priv.get_secret();
	string priv_key = secret.str();
	cout << "priv_key" << priv_key.c_str() << endl;
	timespec start_query;
	clock_gettime(CLOCK_MONOTONIC, &start_query);
	vector<int> desk_cards;
	shuffle_cards(desk_cards,priv_key,52);	
	timespec end_query;
	clock_gettime(CLOCK_MONOTONIC, &end_query);
	int took = (int)((end_query.tv_sec - start_query.tv_sec)*1000 + (end_query.tv_nsec - start_query.tv_nsec)/1000000);
	cout << "took ms:" << took << endl;
	int j=0;	
	for(std::vector<int>::iterator it=desk_cards.begin();it!=desk_cards.end();it++)
	{
		if(j>0)
		{	
			fprintf(fp,"\t");
		}
		fprintf(fp, "%d", *it);
		++j;
	}
	fprintf(fp,"\r\n");
	
	

	fflush(fp);
    	fclose(fp);
   
}*/
