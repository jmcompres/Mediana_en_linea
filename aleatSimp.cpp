#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>

using namespace std;

int main ( int argc, char * argv[]) {
   int i,j, num = 10, limit = 100, inic = 0;
   if( argc > 1) num =  stoi( argv[1] );
   if( argc > 2)  limit =  stoi( argv[2] );
   if( argc > 3)  inic =  stoi( argv[3] );
   srand( (unsigned)time( NULL ) );

   for( i = 0; i < num; i++ ) {
      j = inic + rand() % limit;
      cout  << j << endl;
   }

   return 0;
}
