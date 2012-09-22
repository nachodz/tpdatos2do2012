#Nombre del ejecutable 
target = TpDatos

extension = cpp

#CFLAGS Variable para agregar argumentos al compilador
CFLAGS = -g
CXXFLAGS += $(CFLAGS)

LD = $(CXX)
LDFLAGS =  
LOADLIBS = 
LDLIBS = 

# Path del main
main = src/TpDatos.cpp

#Variables para mensajes por consola
ocxx := $(CXX)
orm := $(RM)
old := $(LD)

CXX = @echo "  CXX $@"; $(ocxx)
RM =  @echo "  CLEAN"; $(orm)
LD =  @echo "  LD  $@"; $(old)

#Ruta de los .cpp
fuentes_common += $(wildcard src/Normalizador/*.$(extension))
fuentes_common += $(wildcard src/Aleatorizador/*.$(extension))

.PHONY: all clean

#Target por default
all: $(target) 

o_common_files = $(patsubst %.$(extension),%.o,$(fuentes_common))

%.deps: %.$(extension)
	@set -e; rm -f $@; \
		$(old) -MM -MG -MP $(CXXFLAGS) $(CFLAGS) $< -MF $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

-include $(o_common_files:.o=.deps)

#Comando para compilar
$(target): $(o_common_files)
	@if [ -z "$(o_common_files)" ]; \
	then \
		echo "No hay archivos de entrada, recuerde que la extension debe ser '.$(extension)'."; \
		false; \
	fi >&2
	$(LD) $(LDFLAGS) $(main) $(o_common_files) $(LOADLIBS) $(LDLIBS) -o $(target)

#Comando para realizar clean
clean:
	$(RM) $(o_common_files) $(o_common_files:.o=.deps)

#Comando para correr el ejecutable
run:
	./$(target)


