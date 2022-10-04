#include "hashmap.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct {
  char id[10];
  char ciudad[50];
  char direccion[50];
  char tipo[50];
  int capacidad;
  int valor;
} Propiedades;

void menu();
void opciones();
void archivo(HashMap *, HashMap *, HashMap *);
void ImportarPropiedades(HashMap *, HashMap *, HashMap *, char *);
char *get_csv_field(char *, int);
int archivos(char *);
Propiedades *generarPropiedades(char *, char *, char *, char *, int, int);
void MapaId(HashMap *, char *);
void id(HashMap *, HashMap *, HashMap *);
void MostrarPropiedades(HashMap *, HashMap *);
void lista(HashMap *, Propiedades *, int);
void llenarLista(HashMap *, Propiedades *, int);
void verificarLista(HashMap *, HashMap *, Propiedades *);
void AgregarPropiedad(HashMap *, HashMap *, HashMap *);
void AgregarFavorito(HashMap *, List *);
void MostrarFavoritos(HashMap *, List *);
void MostrarTodasPropiedades(HashMap*);
//void MostrarPropiedadesCapMin(HashMap *);
void Exportar(HashMap *, List*);

int main() 
{
  //crearMapas
  HashMap* MapId = createMap(100);
  HashMap* MapCiudad = createMap(100);
  HashMap* MapTipo = createMap(100);
  List* lista = createList();

  Propiedades * prop = (Propiedades *)malloc(sizeof(Propiedades));
  
  int op;
  while(op!=10){
  
    printf("------------------  MENÚ  ------------------\n");
    printf("1. Importar propiedades \n");
    printf("2. Agregar Propiedad \n");
    printf("3. Mostrar todas las propiedades \n");
    printf("4. Mostrar propiedades de cierta ciudad \n");
    printf("5. Mostrar propiedades según su tipo \n");
    printf("6. Mostrar propiedades con capacidad mínima  \n");
    printf("7. Agregar a favoritos \n");
    printf("8. Mostrar Favoritos  \n");
    printf("9. Exportar base de datos actualizada\n");
    printf("10. Salir del programa\n");
    printf("--------------------------------------------\n");
    printf("\n¿Que operación desea realizar?\n");
    scanf("%d", &op);
    printf("\n");
    
    
    switch(op)
    {
      case 1 : 
      {
        printf("1. --- Importar Propiedades ---\n");
        archivo(MapId,MapCiudad, MapTipo);
        break;
      }
      case 2 : 
      {
        printf("2. --- Agregar Propiedad --- \n");
        AgregarPropiedad(MapId, MapCiudad, MapTipo);
        break;
      }
      case 3 :
      {
        printf("3. --- Mostrar todas las propiedades ---\n");
        MostrarTodasPropiedades(MapId);
        break;
          
      }
      case 4 :
      {
        printf("4. --- Mostrar propiedades de cierta ciudad ---\n");
        MostrarPropiedades(MapId, MapCiudad);
        break;
          
      }
      case 5 :
      {
        printf("5. --- Mostrar propiedades según su tipo ---\n");
        MostrarPropiedades(MapId, MapTipo);
        break;
      }
      case 6 :
      {
        printf("6. --- Mostrar propiedades con capacidad mínima ---\n");
        ////MostrarPropiedadesCapMin();
        break;
          
      } 
      case 7 :
      {
        printf("7. --- Agregar a favoritos ---\n");
        AgregarFavorito(MapId, lista);
        break;
        
      }
      case 8 : 
      {
        printf("8. --- Mostrar Favoritos ---\n");
        MostrarFavoritos(MapId, lista);
        break;
          
      }
      case 9 : 
      {
        printf("9. --- Exportar base de datos actualizada ---\n");
        Exportar(MapId,lista);   
        break;
      }
      case 10 :
      {
        printf("10. --- Salir del programa ---\n");
        break;
      }
    }
    printf("\n");
  }
  return 0;
}


void archivo(HashMap *Mapid, HashMap *Maptipo, HashMap * Mapciudad) {
  char archivo[30];
  
  printf("Ingrese el nombre del Archivo:\n");
  getchar();
  scanf("%100[^\n]s", archivo);
  getchar();
  
  while (1) {
    if (archivos(archivo)) {
      printf("\nArchivo importado con éxito!!");
      break;
    } 
    else {
      printf("Archivo no encontrado");
      return;
    }
  }
  ImportarPropiedades(Mapid, Maptipo, Mapciudad, archivo);
}
 
int archivos(char *file) {
  struct stat buffer;
  
  int x = stat(file, &buffer);
  if (x == 0){
    return 1;
  }
  else{
    return 0;
  }
}

//con esta persona generamos una nueva propiedad con los datos correspondientes y se retorna un puntero al dato que acabamos de crear
Propiedades * generarPropiedades(char *id, char *ciudad, char *direccion, char *tipo, int capacidad, int valor) {
  
  Propiedades *propiedad = (Propiedades *)malloc(sizeof(Propiedades));
  strcpy(propiedad->id, id);
  strcpy(propiedad->ciudad, ciudad);
  strcpy(propiedad->direccion, direccion);
  strcpy(propiedad->tipo, tipo);
  propiedad->capacidad = capacidad;
  propiedad->valor = valor;
  
  return propiedad;
}

void lista(HashMap *map, Propiedades *propiedad, int opcion){
  List *list =createList();
  
  pushBack(list, propiedad->id);
  if (opcion == 1)
  {
    insertMap(map, propiedad->tipo, list);
  }
  else
  {
    insertMap(map, propiedad->ciudad, list);
  }
}
//Llenamos la lista dependiendo de la opcion que se le envio 1 o 2 guardando la lista con "tipo" o "ciudad".
void llenarLista(HashMap *map, Propiedades *propiedad, int opcion){
  List *list = (List *)malloc(sizeof(List));
  
  if (opcion == 1)
  {
    list = searchMap(map, propiedad->tipo)->value;
  }
  else
  {
    list = searchMap(map, propiedad->ciudad)->value;
  pushBack(list, propiedad->id);
    
  }

}

void verificarLista(HashMap *Maptipo, HashMap *Mapciudad, Propiedades *propiedad)
{
  if(searchMap(Maptipo, propiedad->tipo) == NULL)
  {
    lista(Maptipo, propiedad, 1);
  } 
  else
  {
    llenarLista(Maptipo, propiedad, 1);
  }
  
  if(searchMap(Mapciudad, propiedad->ciudad) == NULL)
  {
    lista(Mapciudad, propiedad, 2);
  } 
  else
  {
    llenarLista(Mapciudad, propiedad, 2);
  } 
}

void ImportarPropiedades(HashMap *Mapid, HashMap *Maptipo, HashMap *Mapciudad, char * file) {
  FILE *fp = fopen(file, "r");

  char line[1024];

  fgets(line, 1023, fp);
  while (fgets(line, 1023, fp) != NULL) 
  {
    Propiedades *propiedad = generarPropiedades(
        get_csv_field(line, 0), get_csv_field(line, 1), get_csv_field(line, 2),
        get_csv_field(line, 3), atoi(get_csv_field(line, 4)),
        atoi(get_csv_field(line, 5)));

    insertMap(Mapid, propiedad->id, propiedad);

    verificarLista(Maptipo, Mapciudad, propiedad);
  }
}
//Dependiendo del tipo de dato de la propiedad,se le enviara e imprimira el mapa llamando a la funcion "MapaId".

void MostrarPropiedades(HashMap *Mapid, HashMap *map){
  char tipo[50];
  
  printf("Ingrese el dato de la propiedad: \n");
  getchar();
  scanf("%100[^\n]s",tipo);
  getchar();
  
  List *list = searchMap(map, tipo)->value;
  char *id = firstList(list);
  
  do{
    MapaId(Mapid, id);
    id = nextList(list);
  }while (id != NULL);
}
  


void AgregarPropiedad(HashMap *Mapid, HashMap *Maptipo, HashMap *Mapciudad){
  char id[10];
  char ciudad[100];
  char direccion[100];
  char tipo[50];
  int capacidad;
  int valor;

  printf("Ingrese el Id: \n");
  getchar();
  scanf("%10[^\n]s",id);
  getchar();
  printf("Ingrese la ciudad: \n");
  scanf("%100[^\n]s", ciudad);
  getchar();
  printf("Ingrese la direccion: \n");
  scanf("%100[^\n]s", direccion);
  getchar();
  printf("Ingrese el tipo de propiedad: \n");
  scanf("%50[^\n]s", tipo);
  getchar();
  printf("Ingrese la capacidad de la propiedad: \n");
  scanf("%d",&capacidad);
  getchar();
  printf("Ingrese el valor de la propiedad: \n"); 
  scanf("%d",&valor);
  getchar();
  
  Propiedades *propiedad = generarPropiedades(id, ciudad, direccion, tipo, capacidad, valor);
  insertMap(Mapid, propiedad->id, propiedad);
  verificarLista(Maptipo, Mapciudad, propiedad);
}

void MostrarTodasPropiedades(HashMap *Mapid){
  Pair *aux = firstMap(Mapid);
  do{
    Propiedades *data = aux->value;
    MapaId(Mapid, data->id);
    aux = nextMap(Mapid);
  }while(aux != NULL);
}

//Imprime el mapa que se recibe de otra funcion.
void MapaId(HashMap *Mapid, char *key) {
  Pair *dato = searchMap(Mapid, key);
  
  Propiedades *aux = dato->value;
  printf("%s %s %s %s %d %i\n", aux->id, aux->ciudad, aux->direccion,
          aux->tipo, aux->capacidad, aux->valor);
}

//No logramos realizar la funcion de mostrar propiedades con capacidad minima
//Por ello decidimos comentar la funcion, para no tener problemas de compilación.

/**
void MostrarPropiedadesCapMin(HashMap *Mapid){
  int capacidadMin;
  printf("Ingrese capacidad minima a buscar propiedad\n");
  scanf("%d",&minCapacity);

} 
**/


//En esta función se le pide el usuario el Id para luego buscarlo en el mapa para verificar si se encuentra
void AgregarFavorito(HashMap *Mapid, List *lista_){
  int op; 
  char id[30];
  
  while(1){
    printf("Ingrese el id: \n");
    getchar();
    scanf("%100[^\n]s", id);
    getchar();
    if(searchMap(Mapid, id) != NULL){
      Propiedades *pr = searchMap(Mapid, id)->value;
      pushBack(lista_, pr->id);
    }else printf("No se encuentra\n");


    printf("Ingrese 1 para seguir agregando, y 2 para salir: \n");
    scanf("%i",&op);
    if (op == 2){
      break;
    }else if (op == 1){
      
    }
  }
}

void MostrarFavoritos(HashMap *Mapid, List *lista_){
  char *aux = firstList(lista_);
  
  do{
    MapaId(Mapid, aux);
    aux = nextList(lista_);
  }while(aux != NULL);
}



char *get_csv_field(char *tmp, int k) {
  int open_mark = 0;
  char *ret = (char *)malloc(100 * sizeof(char));
  int ini_i = 0, i = 0;
  int j = 0;
  while (tmp[i + 1] != '\0') {

    if (tmp[i] == '\"') {
      open_mark = 1 - open_mark;
      if (open_mark)
        ini_i = i + 1;
      i++;
      continue;
    }

    if (open_mark || tmp[i] != ',') {
      if (k == j)
        ret[i - ini_i] = tmp[i];
      i++;
      continue;
    }

    if (tmp[i] == ',') {
      if (k == j) {
        ret[i - ini_i] = 0;
        return ret;
      }
      j++;
      ini_i = i + 1;
    }

    i++;
  }

  if (k == j) {
    ret[i - ini_i] = 0;
    return ret;
  }

  return NULL;
}

void Exportar(HashMap *Mapid, List* list_){
  char Narchivo[30];
  
  printf("Ingrese el nombre del archivo: ");
  getchar();
  scanf("%100[^\n]s", Narchivo);
  getchar();

  FILE *x = fopen(Narchivo, "w");
  if(x == NULL){
    printf("Error\n");
  } 
  else{
    fprintf(x,"Id,Ciudad,Direccion,Tipo,Capacidad,Valor\n");
    Pair *aux = firstMap(Mapid);
    while(aux != NULL)
    {
      Propiedades *data = aux->value;
      fprintf(x,"%s,%s,%s,%s,%d,%d", data->id,data->ciudad,data->direccion,data->tipo,data->capacidad,data->valor);
      fprintf(x,"\n");
      aux = nextMap(Mapid);
    }
    
  }
  fclose(x);
}