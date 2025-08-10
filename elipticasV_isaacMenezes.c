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
//#include <gmp.h>

typedef struct{
  int xr, yr, s; 

} PointDoubling;

//Assignments for all the functions
void generatingPoints(int a, int b, int p, int n);
void choosingPoints(int n, int a, int p);
void findOrder(int a, int p);
PointDoubling pointDoubling(int xp, int yp, int a, int p);
int gcd(int a, int b);
int modInverse(int a, int p);
int gcdExtended(int a, int b, int *x, int *y);

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
  system("open choosedPoints_ellipticCurve.dat");
  //system("open 2choosedPoints_ellipticCurve.dat");

  return 0;
}

//Generating the points
void generatingPoints(int a, int b, int p, int n){
  FILE *file1 = fopen("pointsElliptics.dat", "w");
  if(!file1){
    printf("Error on openning pointsElliptics.dat in 'w' mode in generatingPoints()\n");
    exit(1);
  }

  //Generating the points with a limit of the quantitie 
  for(int x=0; x<p; x++){
    for(int y=0; y<p; y++){
      if(y*y % p == (x*x*x + a*x + b) % p){
        n++;
        fprintf(file1, "%d\t%d\n", x, y);
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
void choosingPoints(int n, int a, int p){
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
  if(n > 100){
    tamVetor = 100;
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

void findOrder(int a, int p){
  int order = 2, value1, value2;

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
  while(fscanf(file5, "%d %d", &value1, &value2) == 2){
    int flag = 0; //This is for controlling the recurrence
    printf("\n\nP = (%d, %d)\n", value1, value2);
    while(1){
      if(flag == 0){
        pd = pointDoubling(value1, value2, a , p);
        printf("%dP = (%d, %d)\n", order, pd.xr, pd.yr);
      }else{
        int aux1 = pd.xr;
        int aux2 = pd.yr;

        pd = pointDoubling(aux1, aux2, a, p);
        printf("%dP = (%d, %d)\n", order, pd.xr, pd.yr);
        if(pd.xr == value1 && pd.yr == value2) //Point in the infinit found!
          break;

      }
      order *= 2;
      flag++;;
    };
    printf("Order: %d\n", order-1);
    fprintf(file6, "%d\t%d\t%d\n", value1, value2, order-1); 
    order = 2;
    flag = 0;
  }

  fclose(file5);
  fclose(file6);

  system("open 2choosedPoints_ellipticCurve.dat"); //Apagar depois
  //system("rm choosedPoints_ellipticCurve.dat"); //Descomentar depois
}

//Point doubling 
PointDoubling pointDoubling(int px, int py, int a, int p){
  PointDoubling result;

  int s, xr, yr;

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

int gcd(int a, int b){
  int rest, count=1, aux;

  if(a < b){
    aux = a;
    a = b;
    b = aux;
  }

  while(b != 0){
    rest = a % b;
    a = b;
    b = rest;
    count++;
  }

  return a;
}

int modInverse(int a, int p){
  int x, y;
  int gcd = gcdExtended(a, p, &x, &y);

  if(gcd != 1){
    printf("Modular inverse does not exists!\n"); //In this case, it always exist if p is prime
    exit(1);
  }

  int inverse = (x % p + p) % p;

  return inverse;
}

int gcdExtended(int a, int b, int *x, int *y){
  if(a == 0){
    *x = 0;
    *y = 1;

    return b;
  }

  int x1, y1;
  int gcd = gcdExtended(b % a, a, &x1, &y1);

  *x = y1 - (b / a) * x1;
  *y = x1;

  return gcd;
}
