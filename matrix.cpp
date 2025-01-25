#include<iostream>
#include<cmath>
int getMatrixElimination(double ** matrix,int i,int j,int rows,int columns);
int getDeterminant(double ** matrix,int rows,int columns){
if(rows==2 && columns==2){
    return (matrix[0][0]*matrix[1][1])-(matrix[0][1]*matrix[1][0]);
}
int sum=0;
for(int i=0;i<columns;i++){
   sum+=pow(-1,i)*matrix[0][i]*getMatrixElimination(matrix,0,i,rows,columns);
}
return sum;
}
int getMatrixElimination(double ** matrix,int rowEliminate,int columnEliminate,int rows,int columns){
    double **newMatrix=new double*[rows-1];
    for(int i=0;i<rows-1;i++){
        newMatrix[i]=new double[columns-1];
    }
    int newI=0;
    int newJ=0;
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
          if(i!=rowEliminate && j!=columnEliminate){
            newMatrix[newI][newJ]=matrix[i][j];
            newJ++;
            if(newJ==columns-1){
                newJ=0;
                newI++;
            }
          }
        }
    }
    return getDeterminant(newMatrix,rows-1,columns-1);
};
// here are the gauss operations
void multiplyOneRowToK(double ** matrix,int row,int columns,double k){
for(int i=0;i<columns;i++){
matrix[row][i]=matrix[row][i]*k;
}
}
void substitude(double ** matrix,int originRow,int destinationRow,int columns){
for(int i=0;i<columns;i++){
    int temp=matrix[destinationRow][i];
    matrix[destinationRow][i]=matrix[originRow][i];
    matrix[originRow][i]=temp;
}
}
void addOneRowToAnother(double **matrix,int originRow,int DestinationRow,double k,int columns){
for(int i=0;i<columns;i++){
 matrix[DestinationRow][i]=matrix[DestinationRow][i]+k*matrix[originRow][i];
}
}
void solveTheLinearSystems(double ** matrix,int rows,int columns){
for(int i=0;i<rows;i++){
    multiplyOneRowToK(matrix,i,columns,1/matrix[i][i]);
    for(int j=0;j<rows;j++){
        if(j!=i){
            double k=-1*matrix[j][i]/matrix[i][i];
            addOneRowToAnother(matrix,i,j,k,columns);
        }
    }
}
}
double ** getInverseOfMatrix(double** matrix,int rows,int columns){
    if(getDeterminant(matrix,rows,columns)==0){
       throw "this matrix doesnt have an inverse";
    }
double **intermediateMatrix=new double*[rows];
for(int i=0;i<rows;i++){
    intermediateMatrix[i]=new double[2*columns];
}
for(int i=0;i<rows;i++){
    for(int j=0;j<columns;j++){
        intermediateMatrix[i][j]=matrix[i][j];
    }
}
for(int i=0;i<rows;i++){
    for(int j=columns;j<columns*2;j++){
        if(i==j-columns){
            intermediateMatrix[i][j]=1;
        }
        else{
        intermediateMatrix[i][j]=0;
        }
    }
}
solveTheLinearSystems(intermediateMatrix,rows,2*columns);
double** theInverseMatrix=new double*[rows];
for(int i=0;i<rows;i++){
    theInverseMatrix[i]=new double[columns];
}
for(int i=0;i<rows;i++){
    for(int j=0;j<columns;j++){
       theInverseMatrix[i][j]=intermediateMatrix[i][j+columns];
    }
}
return theInverseMatrix;
}
int main(int length,char * args[]){
double** matrix=new double*[2]{new double[2]{2,0},
                               new double[2]{0,2}};
double** theInverse=getInverseOfMatrix(matrix,2,2);
for(int i=0;i<2;i++){
    for(int j=0;j<2;j++){
        std::cout<<theInverse[i][j]<<' ';
    }
    std::cout<<"\n";
}
}