#include "constantes.h"


struct Premios {
	char premio[LONGITUDTEXTO+1];
	int numero, euros;
};

struct PremioGanado {
	int numConsulta, cantidad, totalPremio;
	
	char primerPremio[LONGITUDTEXTO+1];
	int premio1o, premioAproximacion1o, premioReintegro1o, premioDosCifras1o, premioCentenas1o;	
	char aprox1o[LONGITUDTEXTO+1], reintegro1o[LONGITUDTEXTO+1], dosCifras1o[LONGITUDTEXTO+1], centenas1o[LONGITUDTEXTO+1];	
	
	char segundoPremio[LONGITUDTEXTO+1];
	int premio2o, premioAproximacion2o, premioDosCifras2o, premioCentenas2o;	
	char aprox2o[LONGITUDTEXTO+1], dosCifras2o[LONGITUDTEXTO+1];	
	char centenas2o[LONGITUDTEXTO+1];	
	
	char tercerPremio[LONGITUDTEXTO+1];
	int premio3o, premioAproximacion3o, premioDosCifras3o, premioCentenas3o;
	char aprox3o[LONGITUDTEXTO+1], dosCifras3o[LONGITUDTEXTO+1], centenas3o[LONGITUDTEXTO+1];	
	
	char cuartoPremio[LONGITUDTEXTO+1];
	int premio4o, premioCentenas4o;
	char centenas4o[LONGITUDTEXTO+1];
		
	char quintoPremio[LONGITUDTEXTO+1];
	int premio5o;
	
	char menor[LONGITUDTEXTO+1];
	int premioMenor;
};

struct MiembroGrupo {
	char nombre[LONGITUDTEXTO+1];
	int numeroJugado;
	int cantidadJugada;
	int premioIndividual;
};

struct Grupo {
	struct MiembroGrupo amigos[MAXAMIGOS];
	int nAmigos;
	int totalJugado;
	int anyo;
	int premioTotal;
};
