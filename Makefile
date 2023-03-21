#opciones de compilacion, muestra todos los warnings (-Wall)
CC=gcc -Wall
#carpeta de las cabeceras (si estan en la actual, ponemos .)
HEADER_FILES_DIR = ./includes/
#opciones de compilacion, indica donde estan los archivos .h
INCLUDES = -I $(HEADER_FILES_DIR)

#nombre del ejecutable o archivo de salida
OUTPUT = Compilador_cmd

#ficheros .h.  Si hay varios, se precede cada uno con $(HEADER_FILES_DIR)/
LIB_HEADERS = $(wildcard $(HEADER_FILES_DIR)/*.h)

#FUENTES: todos los archivos .c necesarios
SRCS = $(wildcard ./src/*c)

#ficheros .o: todos los .o con un analogo .c en SRCS
OBJS = $(SRCS:.c=.o)

#REGLA 1: genera el ejecutable, dependencia de los .o 
#si no hay librerias adicionales, no existe la variable $(LIBS),
#por lo que se elimina $(LIBS) de la regla siguiente
$(OUTPUT): $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS) 

#REGLA 2: genera los .o cuando es necesario, dependencia de los .c y .h
#solo genera los .o necesarios por cambios en los .c o .h
#$@ es el nombre del fichero que se genera con la regla (.o)
#$< es el nombre del primer prerrequisito archivo .c cuyo .o se esta generando
%.o: %.c $(LIB_HEADERS)
	$(CC) -c -o $@ $< $(INCLUDES)
	
# REGLA 3: borra el ejecutable (prerrequisito: clean)
cleanall: clean
	rm   -f $(OUTPUT) 

# REGLA 4: borra los ficheros .o y los de backup (terminan en ~)
clean:
	rm -f ./src/*.o
