typedef struct {
    int idComentario;  /// único, autoincremental
    int idLibro; 
    int idUsuario; 
    char tituloComentario[100]; 
    char descripcion[500]; 
    int puntaje; /// de 0 a 5 "estrellas"
    char fechaComentario[20]; /// o se puede hacer con dia, mes, anio. 
    int eliminado; /// 0 si está activo - 1 si está eliminado
}stComentario; 
