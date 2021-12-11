//Memorama
//Equipongo

#include <iostream>
#include <string.h>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>

using namespace std;

string palabra(int,int); //Esta función va a dar las palabras
int nums[12]; //Guarda números del 0 al 11 en orden aleatorio
int tema; //El tema del memorama

int main() {
setlocale(LC_CTYPE,"Spanish");
bool continuar=true;

while(continuar==true){

//El tablero tapado (va a mostrar puras X); se llena antes para usarlo en el tutorial y el juego
string coord[5]={" "," 1 "," 2 "," 3 "," 4 "};
string tablero[4][5];
for(int c=1;c<5;c++) { tablero[0][c]=coord[c]; } //coordenadas de la columna
for(int f=1;f<4;f++) { tablero[f][0]=coord[f]; } //coordenadas de la fila
for(int i=1;i<4;i++) {
for(int j=1;j<5;j++)
tablero[i][j]=" x ";
}

#ifdef _linux_  //Aquí limpia la pantalla por si vuelven a iniciar el juego
system("clear");
#else
system("cls");
#endif

//Aquí el menú
int op1;
system("color 0F");
cout<<"\nMemorama\n\n1: Jugar\n2: Tutorial\n3: Salir\n\nSeleccione una opción: ";
do{
cin>>op1;
if(op1<1||op1>3){ cout<<"\n\nOpción inválida. Intenta de nuevo: ";}
} while(op1<1||op1>3);


//Inicia el switch
switch(op1){
	
//Juego (caso 1)
case 1:{
//Generador de números
srand(time(NULL)); //Esta parte se va a encargar de generar números sin que se repitan y los guarda en un arreglo.
nums[0]=rand()%12;
for(int i=1;i<12;i++) {
int v;
do {
v=rand()%12;
for (int k=i;k>0;k--) {
if(v==nums[i-k]) { v=99; }
}
}
while(v==99);

nums[i]=v;
}
//Aquí acaba el generador


//for(int k=0;k<12;k++){ cout<<nums[k]<<" "; } //Esto es para ver qué números generó


//Una tabla de verdad para que no se repitan las entradas
bool taverdad[3][4];
for (int vi=0;vi<3;vi++){
for(int vj=0;vj<4;vj++)
taverdad[vi][vj]=false;
} //Está todo en false; cuando se destapen las cartas, se mueve a true


cout<<"\n\nSeleccione un tema:\n";
cout<<"1: Colores\n2: Estados\n3: Letras\n4: Menú Principal\n\n";

//Aquí pide el tema y valida que esté en las opciones
do{
cin>>tema;
if(tema<1||tema>4){cout<<"\n\nOpción inválida. Intenta de nuevo: ";}
}
while(tema<1 || tema>4);

if(tema!=4){ //Si pone 4, se salta todo el juego y vuelve al menú principal

//Aquí hace un sonido, pero se tarda un montón
#ifdef _linux_
echo -e "\007" >/dev/tty10;
#else
Beep(300,300); // 523 hertz (C5) for 500 milliseconds
cin.get(); // wait
#endif

string jugador;
do{
cout<<"\nJugador: ";
fflush(stdin);
cin>>jugador; //Le puse que fuera un nombre completo
fflush(stdin);
if( jugador.size()<4 || jugador.size()>12){ cout<<"Nombre muy largo o muy corto (debe tener de 4 a 12 caracteres).\n\n";}
 } while(jugador.size()<4 || jugador.size()>12);

#ifdef _linux_
system("clear");
#else
system("cls");
#endif

int turno=0;
int fili,colj;
int aciertos=0;
bool rendicion=false;
int tiemp_ant;
tiemp_ant=time(NULL);	//Iniciamos el reloj aquí


//Aquí empieza el juego como tal;
while(turno<=2 && aciertos<6){

int lafila,lacolumna,prex,prey;

//Turnos 0 y 1
if(turno<=1) {
if(turno==0){cout<<"Introduce '0' en Fila para rendirte.\n";}
if(turno==1){cout<<"Espera al siguiente turno para rendirte.\n";}
cout<<"\n Jugador:"<<jugador<<"\n Aciertos: "<<aciertos<<"\n Tiempo: "<<time(NULL)-tiemp_ant<<" s\n\n";
for(fili=0;fili<4;fili++){ //Esto muestra el tablero cada turno
for(colj=0;colj<5;colj++){
cout<<tablero[fili][colj]<<"\t";
}
cout<<endl<<endl;
}

do{
cout<<"Fila: ";
cin>>lafila;
cout<<"Columna: ";
cin>>lacolumna;
if(lafila<0 || lafila>3 || lacolumna<1 || lacolumna>4 || taverdad[lafila-1][lacolumna-1]==true){cout<<"\nCoordenada inválida. Intenta de nuevo.\n\n";}
}
while(lafila<0 || lafila>3 || lacolumna<1 || lacolumna>4 || taverdad[lafila-1][lacolumna-1]==true);

if(lafila!=0){ //Verifica que no se haya rendido
if(turno==0){
prex=lafila;
prey=lacolumna;
}
tablero[lafila][lacolumna]=palabra(lafila,lacolumna); //Llama a la función para llenar la casilla con una palabra
taverdad[lafila-1][lacolumna-1]=true;
turno=turno+1;
}

//Aquí es por si se rinden y quieren ver la solución
if(turno==0 && lafila==0){
for(int rendi=1;rendi<=3;rendi++){
for(int rendj=1;rendj<=4;rendj++){
tablero[rendi][rendj]=palabra(rendi,rendj);
}
}
rendicion=true;
turno=2;
}

#ifdef _linux_
system("clear");
#else
system("cls");
#endif
}

//Turno final de la jugada
if(turno==2){
cout<<"\n\n Jugador:"<<jugador<<"\n Aciertos: ";
if(rendicion==false){cout<<aciertos<<"\n Tiempo: "<<time(NULL)-tiemp_ant<<" s\n\n";}
if(rendicion==true){cout<<"0\n\n\n"; } //Sacan 0 Los que se rinden
for(fili=0;fili<4;fili++){
for(colj=0;colj<5;colj++){
cout<<tablero[fili][colj]<<"\t";
}
cout<<endl<<endl;
}

if(rendicion==false){
if(tablero[lafila][lacolumna]!=tablero[prex][prey]){ //Aquí ve si son iguales las tarjetas y resetea los valores si no lo son
tablero[lafila][lacolumna]=" x ";
tablero[prex][prey]=" x ";
taverdad[lafila-1][lacolumna-1]=false;
taverdad[prex-1][prey-1]=false;
}
else {
aciertos=aciertos+1;
}
turno=0;
}

//Acabar la jugada a los que se rindan:
if(rendicion==true){aciertos=6;}


system("pause");

#ifdef _linux_
system("clear");
#else
system("cls");
#endif
}

}

if(rendicion==false){
system("color 0a");
cout<<"\n\n¡Felicidades! ¡Ganaste!\n\n(Tiempo: "<<time(NULL)-tiemp_ant<<" segundos).\n\n\n\n";

//Aquí hace un sonido, pero se tarda un montón
#ifdef _linux_
echo -e "\007" >/dev/tty10;
#else
Beep(400,300); // 523 hertz (C5) for 500 milliseconds
cin.get(); // wait
#endif

system("pause");
}
}
//continuar=true;
break;
}//Acaba el caso 1 (juego)



//Tutorial (caso 2)
case 2:{
for(int turno2=1;turno2<=3;turno2++){

#ifdef _linux_
system("clear");
#else
system("cls");
#endif
cout<<"\n\n";
for(int fili=0;fili<4;fili++){ //Esto muestra el tablero cada turno
for(int colj=0;colj<5;colj++){
cout<<tablero[fili][colj]<<"\t";
}
cout<<endl<<endl;
}

Sleep(1500);

if(turno2==1){
cout<<"Fila: 1\nColumna: 3";
tablero[1][3]="EdoMex ";
}
if(turno2==2){
cout<<"Fila: 3\nColumna: 4";
tablero[3][4]="EdoMex ";
}
if(turno2==3) { system("pause"); }

Sleep(1500);
}
break;
}//Acaba el tutorial


default: {
#ifdef _linux_
system("clear");
#else
system("cls");
#endif
continuar=false;
cout<<"\n\n Saliendo...\n\n\n";
}

}//acaba el switch
}//Acaba el while

return 0;
}


//De aquí van a salir las palabras:
string palabra(int x, int y){

string pals[12];
string tab1[3][4];

//Aquí llenamos la lista de palabras con las que correspondan al tema (no se me ocurrió una forma más fácil)
switch(tema){
case 1:{
string colores[12]={"Rojo ","Rojo ","Azul ","Azul ","Verde","Verde","Negro","Negro","Rosa ","Rosa ","Café ","Café "};
for(int i=0;i<12;i++) { pals[i]=colores[i]; }
break;
}
case 2: {
string estados[12]={"Ags ","Ags ","Zac ","Zac ","CDMX ","CDMX ","Colima ","Colima ","EdoMex ","EdoMex ","Jalisco","Jalisco"};
for(int i=0;i<12;i++) { pals[i]=estados[i]; }
break;
}
case 3: {
string personajes[12]={" A "," A "," B "," B "," C "," C "," D "," D "," E "," E "," F "," F "};
for(int i=0;i<12;i++) { pals[i]=personajes[i]; }
break;
}
}

int fil,col; //Vamos a llenar la tabla
int n;

n=0;

for(int fil=0;fil<3;fil++) {
for(int col=0;col<4;col++){
tab1[fil][col]=pals[nums[n]];
n++;
}
}
//Ya debería quedar llena

string plbr=tab1[x-1][y-1];

return plbr;
}
