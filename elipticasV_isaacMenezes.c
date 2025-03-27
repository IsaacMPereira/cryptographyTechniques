/*
 * C program to implement the elliptic curve cryptography
 * Isaac Menezes Pereira, 190088885 - feb, 2025
 *
 * Compile: $ gcc -Wall elipticas_isaacMenezes.c -lgmp -o elipticas_isaacMenezes.x 
 * Run: $ ./elipticas_isaacMenezes.x a b p
 * Downloading GMP (GNU) library: 
 *  $ sudo apt update
 *  $ sudo apt install libgmp-dev
 *
 * Interesting observation:
 * Using the curve y^2 = 4x^3 + 4 (mod 103) and the point (94, 28), generated the this curve, it's order is
 * 268435455
 * */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gmp.h>

typedef struct{
  long long int xr, yr, s; 
} PointDoubling;

typedef struct{
  long long int xr, yr, s;
}PointAdding;

//Assignments for all the functions
void generatingPoints(long long int a, long long int b, long long int p, long long int n);
void choosingPoints(long long int n, long long int a, long long int p);
void findOrder(long long int a, long long int p);
PointDoubling pointDoubling(long long int xp, long long int yp, long long int a, long long int p);
long long int modInverse(long long int a, long long int p);
long long int gcdExtended(long long int a, long long int b, long long int *x, long long int *y);
void encrypting(long long int a, long long int p);
PointAdding pointAdding(long long int xp, long long int xq, long long int yp, long long int yq, long long int p);

int main(int argc, char *argv[4]){
  if(argc != 4){
    printf("Error! Run: $ ./elipticas_isaacMenezes.x a b p\n");
    printf("These arguments satisfy: y^2 = x^3 + ax + b (mod p)\n");
    exit(1);
  }
  
  int a = atoi(argv[1]), 
      b = atoi(argv[2]),
      p = atoi(argv[3]),
      n = 0;
      
  generatingPoints(a, b, p, n);
  
  system("open pointsElliptics.dat");
  system("rm choosedPoints_ellipticCurve.dat");
  system("open 2choosedPoints_ellipticCurve.dat");
  
  //Encrypting function
  encrypting(a, p);
  
  return 0;
}

//Generating the points
void generatingPoints(long long int a, long long int b, long long int p, long long int n){
  FILE *file1 = fopen("pointsElliptics.dat", "w");
  if(!file1){
    printf("Error on openning pointsElliptics.dat in 'w' mode in generatingPoints()\n");
    exit(1);
  }
  
  //Generating the points with a limit of the quantitie 
  for(long long int x=0; x<p; x++){
    for(long long int y=0; y<p; y++){
      if(y*y % p == (x*x*x + a*x + b) % p){
        n++;
        fprintf(file1, "%lld\t%lld\n", x, y);
        if(n > 1000){
          break;
        }
      }
    }
  }
  
  fclose(file1);
  
  printf("All points created!\n");
  
  choosingPoints(n, a, p); 
} 

//Choosing the points for the Finding Order Algorithm
void choosingPoints(long long int n, long long int a, long long int p){
  srand(time(NULL));  
  int totalLines = 0;
  char buffer[100];
  
  FILE *file2 = fopen("pointsElliptics.dat", "r");
  if(!file2){
    printf("Error on openning pointsElliptics.dat in 'r' mode in choosingPoints()\n");
    exit(1);
  }
  
  FILE *file3 = fopen("choosedPoints_ellipticCurve.dat", "w");
  if(!file3){
    printf("Error on openning choosedPoints_ellipticCurve.dat in 'w' mode in choosingPoints()\n");
    exit(1);
  }
  
  //Checking the number of lines in file2
  while(fgets(buffer, sizeof(buffer), file2)){
    totalLines++;
  }
  printf("Total of points: %d\n", totalLines);
  rewind(file2);
  
  //Creating the vector with a specific size depending on the number of lines in file2
  int tamVetor;
  if(n > 50){
    tamVetor = 50;
  }else{
    tamVetor = n;
  }
  
  int v_random[tamVetor];
  //Assigning random values to the vector depending on its size and the number of lines in file2
  for(int i=0; i<tamVetor; i++){
    int aux = rand() % n;
    v_random[i] = aux;
  }  
  
  //Printing the specific line in file2 depending on the index of the vector
  for(int i=0; i<tamVetor; i++){
    int desiredLine = v_random[i];
    rewind(file2); //Comes back to tho first line of the file
    int currentLine = 1;
    while(fgets(buffer, sizeof(buffer), file2)){
      if(currentLine == desiredLine){
        fprintf(file3, "%s", buffer);
        break;
      }
      currentLine++;
    }
  } 
  
  fclose(file2);
  fclose(file3);
  
  //Checking the number of lines in file4
  FILE *file4 = fopen("choosedPoints_ellipticCurve.dat", "r");
  if(!file4){
    printf("Error on openning choosedPoints_ellipticCurve.dat in 'r' mode in choosingPoints()\n");
    exit(1);  
  }
  
  totalLines = 0;
  while(fgets(buffer, sizeof(buffer), file4)){
    totalLines++;
  }
  printf("Total of points choosed: %d\n", totalLines);
  
  //Using the Finding Order Algorithm to find the order of all points choosed
  findOrder(a, p);
  fclose(file4);
}

//Finding order
void findOrder(long long int a, long long int p){
  long long int order=0, value1, value2;
  
  FILE *file5 = fopen("choosedPoints_ellipticCurve.dat", "r") ;
  if(!file5){
    printf("Error on openning choosedPoints_ellipticCurve.dat in 'r' mode in findOrder()\n");
    exit(1);
  }
  
  FILE *file6 = fopen("2choosedPoints_ellipticCurve.dat", "w");
  if(!file6){
    printf("Error on openning 2choosedPoints_ellipticCurve.dat in 'w' mode in findOrder()\n");
    exit(1);
  }
  
  //Applying PointDoubling in ever single point until find it's order
  PointDoubling pd;
  while(fscanf(file5, "%lld %lld", &value1, &value2) == 2){
    int flag = 0; //This is for controlling the recurrence
    //printf("\n\nP = (%lld, %lld)\n", value1, value2);
    while(1){
      if(flag == 0){
        pd = pointDoubling(value1, value2, a , p);
        //printf("%lldP = (%lld, %lld)\n", order, pd.xr, pd.yr);
      }else{
        int aux1 = pd.xr;
        int aux2 = pd.yr;
        pd = pointDoubling(aux1, aux2, a, p);
        //printf("%lldP = (%lld, %lld)\n", order, pd.xr, pd.yr);
        if(pd.xr == value1 && pd.yr == value2) //Point in the infinit found!
          break;
      }
      order++;
      flag++;
    };
    //printf("Order: %lld\n", order+2);
    fprintf(file6, "%lld\t%lld\t%lld\n", value1, value2, order+2); 
    order = 0;
    flag = 0;
  }
  
  fclose(file5);
  fclose(file6);
}

//Point doubling 
PointDoubling pointDoubling(long long int px, long long int py, long long int a, long long int p){
  PointDoubling result;
  
  long long int s, xr, yr;
  
  //Find the slope (s)
  s = ((3 * px*px + a) % p) * (modInverse(2*py, p)) % p;
  if(s < 0){ //Just for ensurrement
    do{
      s += p;
    }while(s < 0);
  }
  
  //Finding xr
  xr = (s*s - 2*px) % p;
  if(xr < 0){
    do{
      xr += p;
    }while(xr < 0);
  }
  
  //Finding yr
  yr = (s*(px - xr) - py) % p;
  if(yr < 0){
    do{
      yr += p;
    }while(yr < 0);
  }
  
  result.xr = xr;
  result.yr = yr;
  result.s = s;
  
  return result;
}

//Modular inverse of a number mod p
long long int modInverse(long long int a, long long int p){
  long long int x, y;
  
  long long int gcd = gcdExtended(a, p, &x, &y);
  
  if(gcd != 1){
    printf("Modular inverse does not exists!\n"); //In this case, it always exist if p is prime
    exit(1);
  }
  
  long long int inverse = (x % p + p) % p;
  
  return inverse;
}

//Extended Euclidian Algorithm
long long int gcdExtended(long long int a, long long int b, long long int *x, long long int *y){
  if(a == 0){
    *x = 0;
    *y = 1;
    return b;
  }
  
  long long int x1, y1;
  long long int gcd = gcdExtended(b % a, a, &x1, &y1);
  
  *x = y1 - (b / a) * x1;
  *y = x1;
  
  return gcd;
}

void encrypting(long long int a, long long int p){
	PointDoubling pd;
	PointAdding pa;
	
	mpz_t zd_alfa, zd_beta, zd_r, zd_s;
	long long int gx, gy, order, auxALFA_xr, auxALFA_yr, auxBETA_xr, auxBETA_yr, auxR_xr, auxR_yr, auxS_xr, auxS_yr; 
	char alfa[100], beta[100];
	
	mpz_init(zd_alfa);
	mpz_init(zd_beta);
	mpz_init(zd_r);
	mpz_init(zd_s);
	
	printf("\nChoose a generator and it's order: ");
	scanf("%lld %lld %lld", &gx, &gy, &order);
	
	printf("Choose alfa: ");
	scanf("%s", alfa);
	mpz_set_str(zd_alfa, alfa, 10);
	
	printf("Choose beta: ");
	scanf("%s", beta);
	mpz_set_str(zd_beta, beta, 10);
	
	//gmp_printf("%Zd, %Zd\n", zd_alfa, zd_beta); //Just for checking
	
	char *binAlfa = mpz_get_str(NULL, 2, zd_alfa);
	char *binBeta = mpz_get_str(NULL, 2, zd_beta);
	//printf("Alfa bin: %s\nBeta bin: %s\n", binAlfa, binBeta); //Just for checking
	//printf("Alfa bin: %c\nBeta bin: %c\n", binAlfa[1], binBeta[1]); //"A string is a array of characteres"
	
	//Binary algorithm for alfa
	for(size_t i=0; i<strlen(binAlfa); i++){
		if(i > 0){
			if(binAlfa[i] == '1'){
				if(i == 1){
					pd = pointDoubling(gx, gy, a, p);
					
					pa = pointAdding(pd.xr, gx, pd.yr, gy, p);
					
					auxALFA_xr = pa.xr;
					auxALFA_yr = pa.yr;
				}else{
					pd = pointDoubling(auxALFA_xr, auxALFA_yr, a, p);
					
					pa = pointAdding(pd.xr, gx, pd.yr, gy, p);
					
					auxALFA_xr = pa.xr;
					auxALFA_yr = pa.yr;
				}
			}else{
				if(i == 1){
					pd = pointDoubling(gx, gy, a, p);
					
					auxALFA_xr = pd.xr;
					auxALFA_yr = pd.yr;
				}else{
					pd = pointDoubling(auxALFA_xr, auxALFA_yr, a, p);
					
					auxALFA_xr = pd.xr;
					auxALFA_yr = pd.yr;
				}
			}
		}
	}
	printf("A: (%lld, %lld)\n", auxALFA_xr, auxALFA_yr);
	
	//Binary algorithm for beta
	for(size_t j=0; j<strlen(binBeta); j++){
		if(j > 0){
			if(binBeta[j] == '1'){
				if(j == 1){
					pd = pointDoubling(gx, gy, a, p);
					
					pa = pointAdding(pd.xr, gx, pd.yr, gy, p);
					
					auxBETA_xr = pa.xr;
					auxBETA_yr = pa.yr;
				}else{
					pd = pointDoubling(auxBETA_xr, auxBETA_yr, a, p);
					
					pa = pointAdding(pd.xr, gx, pd.yr, gy, p);
					
					auxBETA_xr = pa.xr;
					auxBETA_yr = pa.yr;
				}
			}else{
				if(j == 1){
					pd = pointDoubling(gx, gy, a, p);
					
					auxBETA_xr = pd.xr;
					auxBETA_yr = pd.yr;
				}else{
					pd = pointDoubling(auxBETA_xr, auxBETA_yr, a, p);
					
					auxBETA_xr = pd.xr;
					auxBETA_yr = pd.yr;
				}
			}
		}
	}
	printf("B: (%lld, %lld)\n", auxBETA_xr, auxBETA_yr);
	
	
	long long int a_b = atoi(alfa) * atoi(beta);
	long long int b_a = atoi(beta) * atoi(alfa);
	
	if(a_b > order){
		a_b = a_b % order;
	}
	if(b_a > order){
		b_a = b_a % order;
	}
	
	mpz_set_ui(zd_r, a_b);
	mpz_set_ui(zd_s, b_a);
	
	char *bin_ab = mpz_get_str(NULL, 2, zd_r);
	char *bin_ba = mpz_get_str(NULL, 2, zd_s);
	
	//Binary for R
	for(size_t k=0; k<strlen(bin_ab); k++){
		if(k > 0){
			if(bin_ab[k] == '1'){ 
				if(k == 1){
					pd = pointDoubling(gx, gy, a, p);
					
					pa = pointAdding(pd.xr, gx, pd.yr, gy, p);
					
					auxR_xr = pa.xr;
					auxR_yr = pa.yr;
				}else{
					pd = pointDoubling(auxR_xr, auxR_yr, a, p);
					
					pa = pointAdding(pd.xr, gx, pd.yr, gy, p);
					
					auxR_xr = pa.xr;
					auxR_yr = pa.yr;
				}
			}else{
				if(k == 1){
					pd = pointDoubling(gx, gy, a, p);
					
					auxR_xr = pd.xr;
					auxR_yr = pd.yr;
				}else{
					pd = pointDoubling(auxR_xr, auxR_yr, a, p);
					
					auxR_xr = pd.xr;
					auxR_yr = pd.yr;
				}
			}
		}
	}
	printf("R: (%lld, %lld)\n", auxR_xr, auxR_yr);
	
	//Binary for S
	for(size_t l=0; l<strlen(bin_ba); l++){
		if(l > 0){
			if(bin_ba[l] == '1'){ 
				if(l == 1){
					pd = pointDoubling(gx, gy, a, p);
					
					pa = pointAdding(pd.xr, gx, pd.yr, gy, p);
					
					auxS_xr = pa.xr;
					auxS_yr = pa.yr;
				}else{
					pd = pointDoubling(auxS_xr, auxS_yr, a, p);
					
					pa = pointAdding(pd.xr, gx, pd.yr, gy, p);
					
					auxS_xr = pa.xr;
					auxS_yr = pa.yr;
				}
			}else{
				if(l == 1){
					pd = pointDoubling(gx, gy, a, p);
					
					auxS_xr = pd.xr;
					auxS_yr = pd.yr;
				}else{
					pd = pointDoubling(auxS_xr, auxS_yr, a, p);
					
					auxS_xr = pd.xr;
					auxS_yr = pd.yr;
				}
			}
		}
	}
	printf("S: (%lld, %lld)\n", auxS_xr, auxS_yr);
	
	mpz_clear(zd_alfa);
	mpz_clear(zd_beta);
	mpz_clear(zd_r);
	mpz_clear(zd_s);
	free(binAlfa);
	free(binBeta);
	free(bin_ab);
	free(bin_ba);
}

//Point adding
PointAdding pointAdding(long long int xp, long long int xq, long long int yp, long long int yq, long long int p){
  PointAdding result;
  
  long long int s, xr, yr;
  
  //Finding the slope (s)
  s = ((yp - yq) % p) * (modInverse((xp-xq), p) % p);
  if(s < 0){ //Just for ensurrement
	  do{
		s += p;
	  }while(s < 0);
  }
  
  //Finding xr
  xr = (s*s - (xp + xq)) % p;
  if(xr < 0){
	  do{
			xr += p;
	  }while(xr < 0);
  }
  
  //Finding yr
  yr = (s*(xp - xr)) % p;
  if(yr < 0){
	  do{
		  yr += p;
	  }while(yr < 0);
  }
  
  result.s = s;
  result.xr = xr;
  result.yr = yr;
  
  return result;
}
