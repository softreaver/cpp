# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <omp.h>

#define eps 0.000001
#define M 4


void prod_mat_vect(double a[M][M],int n,double x[M],double y[M])
{
 int i,j;
 for(i=0;i<n;i++)
 {
  y[i]=0;
  for(j=0;j<n;j++)
      y[i] += a[i][j]*x[j];
 }
}


void grad_conj(double a[M][M],double b[M],double x[M],int n)
{
  double gamma,alpha0,rho,s;
  int i,j,k;
  double g[n],h[n],u[n],Ah[n];

  prod_mat_vect(a,n,x,g);
  for(i=1;i<=n;i++)
      { g[i] -= b[i];
	h[i] = g[i];
  }
  int rang;
  for(i=1;i<=n;i++){
      
    prod_mat_vect(a,n,h,Ah);
    s = 0;
    alpha0 = 0;
    #pragma omp parallel private(j) 
    {
    #pragma omp for schedule(runtime) nowait reduction(+:s,alpha0)
      for(j=0;j<=n;j++){
	s += h[j]*g[j];
	alpha0 += h[j]*Ah[j];
	rang=omp_get_thread_num();
	printf("Rang : %d ; iteration : %d\n",rang,j);
      }
    }
    rho = -s/alpha0;
    s = 0;
    alpha0 = 0;
    #pragma omp parallel private(j) 
    {
    #pragma omp for schedule(runtime) nowait reduction(+:s,alpha0)
      for(j=0;j<=n;j++) {
	x[j] += rho*h[j];
	alpha0 += g[j]*g[j];
	g[j] += rho*Ah[j];
	s += g[j]*g[j];
      }
    }
    gamma = s/alpha0;
    #pragma omp parallel private(j) 
    {
    #pragma omp for schedule(runtime) nowait
      for(j=0;j<=n;j++){
	h[j] = gamma*h[j] - g[j];
      }
    }
    printf("GradConj: iteration %d\n",i);
    
    if (s < eps) 
      break;
  }

}

int main(int argc, char* argv[])
{ int NN = 4;
  double a[NN][NN];
  double b[NN];
  double x[NN];
  double y[NN];
//   
  float t0,t1;
  int m,k;
  for (m = 0; m < NN; m++ )
	  for (k = 0; k < NN; k++ ){
		  if (m==k)
		    a[m][k] = 1;
		  else 
		    a[m][k] = 0;
	  }
  a[0][1] = 1;
  
  for (m = 0; m < NN; m++ )
	  for (k = 0; k < NN; k++ ){
	    printf("A[%d][%d] = %f\n",m,k,a[m][k]);
	    
	  }
  for (m = 0; m < NN; m++ )
	b[m] = m;
	x[m] = 2*m;

  grad_conj(a,b,x,NN);
  
  for  (m = 0; m < NN; m++ )
    printf("X[%d] = %f\n",m,x[m]);
  
  prod_mat_vect(a,NN,x,y);
  for  (m = 0; m < NN; m++ )
    printf("Diff[%d] = %f\n",m,b[m] - y[m]);

 return 0; 
}






