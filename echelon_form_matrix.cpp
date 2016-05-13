#include<iostream>
#include<vector>

using namespace std;

typedef vector<int> Fila;
typedef vector<Fila> Matriu;

void llegir_matriu(Matriu& A) {
    for(int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < A[0].size(); ++j)
	    cin >> A[i][j]; 
    }
}

void escriure_matriu(const Matriu& A) {
    for(int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < A[0].size(); ++j)
	    cout << A[i][j] << " ";
        cout << endl; 
    }
    cout << endl;
}

int abs(int a) {
    if (a >= 0) return a;
    return -a;
}

int mcd(int a, int b) {
    if (b == 0) return a;
    else return mcd(b,a%b);
}

void aplicar_gauss(Matriu& A,int i,int j) {
    int s1, s2; //Controlem el signe per sumar o restar
    s1 = s2 = 1;
    if(A[i][j] < 0) s1 = -1; //Pivot   
    for(int k = i + 1; k < A.size(); ++k) {
        if(A[k][j] != 0) {//si a la casella de sota del pivot (fila k) hi ha numeros diferents de 0 apliquem gauss a fila k amb amb la fila i (fila del pivot)
	    if(A[k][j] < 0) s2 = -1; //Element a eliminar (Posar a 0)
	    if (abs(A[i][j]) == abs(A[k][j])) { //Si els dos son iguals sumem o restem segons signe 
	        if (s1 == s2)  for(int l = j; l < A[0].size(); ++l) A[k][l] = A[k][l] - A[i][l];
                else for(int l = j; l < A[0].size(); ++l) A[k][l] = A[k][l] + A[i][l];
	        }
	    else {//sino els multipliquem entre ells
		int aux = A[k][j];
                for(int l = j; l < A[0].size(); ++l) A[k][l] = A[i][j]*A[k][l] - aux*A[i][l];		  
           }
	/*Comprovar calculs
        cout << endl;
        escriure_matriu(A);
        cout << endl;
        */         
       }
   }
} 

void permutar_files(Matriu& A, int fila1, int fila2) {
    for (int j = 0; j < A[0].size(); ++j) {
        int aux = A[fila1][j];
        A[fila1][j] = A[fila2][j];
        A[fila2][j] = aux;
    }
}

void normalitzar_matriu(Matriu& A) {
    bool mcdt = true;
    for (int i = 0; i < A.size(); ++i) {
        int j = 1;
        int mcd1;    
        while (mcdt and j < A[0].size()) {
            mcd1 = mcd(A[i][j-1],A[i][j]);
	    mcdt = mcd1 == mcd(mcd1,A[i][j+1]);
            ++j;     
        }
        if (mcdt and mcd1 != 1) {
	    for (int j = 0; j < A[0].size(); ++j) A[i][j] /= mcd1;
        }  
    }
}


void escalonar_matriu(Matriu& A) {
    int i = 0;
    int j = 0;
    escriure_matriu(A);
    normalitzar_matriu(A);
    while (i < A.size() and j < A[0].size()) {
        //Si es pivot -> apliquem gauss amb el pivot A[i][j]
        if(A[i][j] != 0) {
	    //Comprovar pivot escollit.
	    //cout << "pivot: " << A[i][j] << endl;      
            aplicar_gauss(A,i,j);
            ++i;
            ++j;
        }
        //Si no -> seguim buscant pivot
        else {
 	    //en cas de zero comprovem si a sota hi ha algun numero per permutar les files.
	    bool perm = false;
            int l = i + 1;
            while (not perm and l < A.size()) {	    
	        if (A[l][j] != 0) {
                    permutar_files(A,i,l);
                    perm = true;
                }
                ++l;
            }
            if (not perm) ++j;
	    if (j == A[0].size()) {
	        j = 0;
                ++i;
            }
        }          
    }
}


int main() {
    int col,fil;
    while (cin >> fil >> col) {
        Matriu A(fil,Fila(col));
        llegir_matriu(A);       
        escalonar_matriu(A);
        escriure_matriu(A);
    }
}
